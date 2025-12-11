#include <algorithm>
#include <chrono>
#include <cmath>
#include <memory>
#include <vector>

#include "Eigen/Dense"
#include "mpc_car_control/msg/control_command_body.hpp"
#include "mpc_car_control/msg/reference_trajectory.hpp"
#include "mpc_car_control/msg/vehicle_state.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class MPCControllerNode : public rclcpp::Node {
public:
  MPCControllerNode() : Node("mpc_controller_node") {
    publisher_ =
        this->create_publisher<mpc_car_control::msg::ControlCommandBody>(
            "/control_command_body", 10);

    subscription_traj_ =
        this->create_subscription<mpc_car_control::msg::ReferenceTrajectory>(
            "/reference_trajectory", 10,
            std::bind(&MPCControllerNode::traj_callback, this, _1));

    subscription_state_ =
        this->create_subscription<mpc_car_control::msg::VehicleState>(
            "/vehicle_state", 10,
            std::bind(&MPCControllerNode::state_callback, this, _1));

    // 100Hz MPC loop
    timer_ = this->create_wall_timer(
        10ms, std::bind(&MPCControllerNode::control_loop, this));

    u_prev_ = Eigen::VectorXd::Zero(nu_);

    // Initialize Cache
    Ad_ = Eigen::MatrixXd::Identity(nx_, nx_);
    Bd_ = Eigen::MatrixXd::Zero(nx_, nu_);

    RCLCPP_INFO(
        this->get_logger(),
        "Multi-Rate MPC Controller Started (100Hz Control, 2Hz Model).");
  }

private:
  // Vehicle Parameters
  const double m_ = 1412.0;
  const double Iz_ = 1536.7;
  const double Ixx_ = 536.6;
  const double Iyy_ = 1536.7;
  const double lf_ = 1.015;
  const double lr_ = 1.9;
  const double Caf_ = 60000.0;
  const double Car_ = 50000.0;
  const double g_ = 9.81;

  // MPC Parameters
  const int N_ = 50;       // Prediction Horizon (0.5s at 100Hz)
  const double dt_ = 0.01; // Time step (100Hz)
  const int nx_ = 12;      // [x, y, psi, vx, vy, wz, z, phi, theta, vz, p, q]
  const int nu_ = 5;       // [accel, Fyf_kN, dFz_kN, Mx_kNm, My_kNm]

  void traj_callback(
      const mpc_car_control::msg::ReferenceTrajectory::SharedPtr msg) {
    current_trajectory_ = *msg;
  }

  void state_callback(const mpc_car_control::msg::VehicleState::SharedPtr msg) {
    current_state_ = *msg;
    state_received_ = true;
  }

  // Get Linearized System Matrices (Jacobian) for Dynamic Bicycle Model +
  // Vertical State: x = [x, y, psi, vx, vy, wz, z, phi, theta, vz, p, q]
  // Control: u = [a, Fyf_kN, dFz_kN, Mx_kNm, My_kNm]
  void get_linearized_matrices(const Eigen::VectorXd &x_ref, Eigen::MatrixXd &A,
                               Eigen::MatrixXd &B) {
    A = Eigen::MatrixXd::Zero(nx_, nx_);
    B = Eigen::MatrixXd::Zero(nx_, nu_);

    double psi = x_ref(2);
    double vx = std::max(x_ref(3), 1.0); // Avoid singularity
    double vy = x_ref(4);
    double wz = x_ref(5);
    // double theta = x_ref(8); // Unused for small angle approx
    // double phi = x_ref(7);   // Unused for small angle approx

    double cos_psi = std::cos(psi);
    double sin_psi = std::sin(psi);

    // 1. x_dot = vx*cos(psi) - vy*sin(psi)
    A(0, 2) = -vx * sin_psi - vy * cos_psi; // dx/dpsi
    A(0, 3) = cos_psi;                      // dx/dvx
    A(0, 4) = -sin_psi;                     // dx/dvy

    // 2. y_dot = vx*sin(psi) + vy*cos(psi)
    A(1, 2) = vx * cos_psi - vy * sin_psi; // dy/dpsi
    A(1, 3) = sin_psi;                     // dy/dvx
    A(1, 4) = cos_psi;                     // dy/dvy

    // 3. psi_dot = wz
    A(2, 5) = 1.0;

    // 4. vx_dot = a - vy*wz - g*sin(theta)
    // Linearized around theta=0: -g*theta -> Wait, Nose Down (theta>0) ->
    // Accel. So vx_dot = ... + g*sin(theta) (if g is 9.81). g_ is 9.81. So
    // +g_*theta.
    B(3, 0) = 1.0; // dvx/da
    A(3, 4) = -wz; // dvx/dvy
    A(3, 5) = -vy; // dvx/dwz
    A(3, 8) = g_;  // dvx/dtheta (Gravity: Nose Down -> Accel)

    // 5. vy_dot = (Fyf + Fyr)/m - vx*wz + g*sin(phi)*cos(theta)
    // Linearized around phi=0: +g*phi
    // Fyr = Car * (-(vy - lr*wz)/vx)

    double dFyr_dvy = -Car_ / vx;
    double dFyr_dwz = Car_ * lr_ / vx;

    A(4, 3) = -wz;                // dvy/dvx
    A(4, 4) = dFyr_dvy / m_;      // dvy/dvy
    A(4, 5) = dFyr_dwz / m_ - vx; // dvy/dwz
    A(4, 7) = -g_;         // dvy/dphi (Gravity: Roll right -> Pull right (-Y))
    B(4, 1) = 1000.0 / m_; // dvy/dFyf_kN

    // 6. wz_dot = (lf*Fyf - lr*Fyr)/Iz
    A(5, 4) = -lr_ * dFyr_dvy / Iz_; // dwz/dvy
    A(5, 5) = -lr_ * dFyr_dwz / Iz_; // dwz/dwz
    B(5, 1) = (lf_ * 1000.0) / Iz_;  // dwz/dFyf_kN

    // 7. z_dot = vz
    A(6, 9) = 1.0;

    // 8. phi_dot = p
    A(7, 10) = 1.0;

    // 9. theta_dot = q
    A(8, 11) = 1.0;

    // 10. vz_dot = dFz/m
    B(9, 2) = 1000.0 / m_;

    // 11. p_dot = Mx/Ixx
    B(10, 3) = 1000.0 / Ixx_;

    // 12. q_dot = My/Iyy
    B(11, 4) = 1000.0 / Iyy_;
  }

  void control_loop() {
    if (!state_received_ || current_trajectory_.points.empty()) {
      return;
    }

    // 1. Current State Vector
    Eigen::VectorXd x0(nx_);
    x0 << current_state_.x, current_state_.y, current_state_.yaw,
        current_state_.vx, current_state_.vy, current_state_.yaw_rate,
        current_state_.z, current_state_.roll, current_state_.pitch,
        current_state_.vz, current_state_.roll_rate, current_state_.pitch_rate;

    // 2. Reference Trajectory
    // Find closest point
    double min_dist = 1e9;
    size_t closest_idx = 0;
    for (size_t i = 0; i < current_trajectory_.points.size(); ++i) {
      double dx = current_trajectory_.points[i].x - current_state_.x;
      double dy = current_trajectory_.points[i].y - current_state_.y;
      double dist = std::sqrt(dx * dx + dy * dy);
      if (dist < min_dist) {
        min_dist = dist;
        closest_idx = i;
      }
    }

    // Linearization Point (Reference at start)
    size_t ref_idx =
        std::min(closest_idx + 5, current_trajectory_.points.size() - 1);
    Eigen::VectorXd x_ref_lin(nx_);
    x_ref_lin.setZero();
    x_ref_lin(2) = current_trajectory_.yaw_profile[ref_idx];
    x_ref_lin(3) = std::max(current_trajectory_.velocity_profile[ref_idx], 1.0);

    // 3. Adaptive MPC: Linearize around Current State (x0)
    // Multi-Rate: Update Linearization every 500ms
    auto current_time = this->now();
    bool need_linearization = false;

    if (first_run_ ||
        (current_time - last_linearization_time_).seconds() >= 0.5) {
      need_linearization = true;
      last_linearization_time_ = current_time;
      first_run_ = false;
    }

    if (need_linearization) {
      Eigen::MatrixXd Ac(nx_, nx_), Bc(nx_, nu_);
      get_linearized_matrices(x0, Ac, Bc); // Linearize around CURRENT STATE

      // 4. Discretize Model (Taylor Series / Matrix Exponential)
      Eigen::MatrixXd I = Eigen::MatrixXd::Identity(nx_, nx_);
      Ad_ = I + Ac * dt_ + 0.5 * Ac * Ac * dt_ * dt_;
      Bd_ = (I + 0.5 * Ac * dt_) * Bc * dt_;
    }

    // Use cached Ad_, Bd_
    Eigen::MatrixXd Ad = Ad_;
    Eigen::MatrixXd Bd = Bd_;

    // 5. Prediction Matrices
    int N = N_; // Horizon
    Eigen::MatrixXd Phi(nx_ * N, nx_);
    Eigen::MatrixXd Gamma(nx_ * N, nu_ * N);
    Gamma.setZero();

    Eigen::MatrixXd A_pow = Ad;
    for (int k = 0; k < N; ++k) {
      Phi.block(k * nx_, 0, nx_, nx_) = A_pow;
      for (int j = 0; j <= k; ++j) {
        Eigen::MatrixXd term = Eigen::MatrixXd::Identity(nx_, nx_);
        if (k > j) {
          for (int p = 0; p < (k - j); ++p)
            term = term * Ad;
        }
        Gamma.block(k * nx_, j * nu_, nx_, nu_) = term * Bd;
      }
      A_pow = A_pow * Ad;
    }

    // 5. Reference Vector
    Eigen::VectorXd R_ref(nx_ * N);
    R_ref.setZero();
    for (int k = 0; k < N; ++k) {
      double current_v = std::max(current_state_.vx, 1.0);
      double dist_ahead = k * dt_ * current_v;
      size_t idx_offset = std::round(dist_ahead / 0.5);
      size_t idx = std::min(closest_idx + idx_offset,
                            current_trajectory_.points.size() - 1);

      R_ref(k * nx_ + 0) = current_trajectory_.points[idx].x;
      R_ref(k * nx_ + 1) = current_trajectory_.points[idx].y;
      R_ref(k * nx_ + 2) = current_trajectory_.yaw_profile[idx];
      R_ref(k * nx_ + 3) = current_trajectory_.velocity_profile[idx];

      // Calculate Reference Yaw Rate (wz_ref)
      if (idx < current_trajectory_.points.size() - 1) {
        double d_yaw = current_trajectory_.yaw_profile[idx + 1] -
                       current_trajectory_.yaw_profile[idx];
        while (d_yaw > M_PI)
          d_yaw -= 2 * M_PI;
        while (d_yaw < -M_PI)
          d_yaw += 2 * M_PI;

        double dx = current_trajectory_.points[idx + 1].x -
                    current_trajectory_.points[idx].x;
        double dy = current_trajectory_.points[idx + 1].y -
                    current_trajectory_.points[idx].y;
        double ds = std::sqrt(dx * dx + dy * dy);

        if (ds > 1e-3) {
          R_ref(k * nx_ + 5) =
              (d_yaw / ds) * current_trajectory_.velocity_profile[idx];
        } else {
          R_ref(k * nx_ + 5) = 0.0;
        }
      } else {
        R_ref(k * nx_ + 5) = 0.0;
      }

      // Vertical Reference
      R_ref(k * nx_ + 6) = 0.54; // Target Height (h_cg)
      R_ref(k * nx_ + 7) = 0.0;  // Target Roll
      R_ref(k * nx_ + 8) = 0.0;  // Target Pitch
    }

    // 6. Weights
    Eigen::VectorXd Q_diag(nx_);
    // [x, y, psi, vx, vy, wz, z, phi, theta, vz, p, q]
    Q_diag << 100.0, 100.0, 50.0, 10.0, 10.0, 10.0, // Planar
        50.0, 100.0, 100.0, 10.0, 10.0, 10.0;       // Vertical/Rotational

    Eigen::VectorXd R_diag(nu_);
    // [accel, Fyf_kN, dFz_kN, Mx_kNm, My_kNm]
    // Increase R for suspension to prevent massive inputs
    R_diag << 1.0, 1.0, 10.0, 10.0, 10.0;

    Eigen::VectorXd R_rate_diag(nu_);
    // [d_accel, d_Fyf_kN, d_dFz, d_Mx, d_My]
    R_rate_diag << 1.0, 0.1, 1.0, 1.0, 1.0;

    Eigen::MatrixXd Q_bar = Eigen::MatrixXd::Zero(nx_ * N, nx_ * N);
    Eigen::MatrixXd R_bar = Eigen::MatrixXd::Zero(nu_ * N, nu_ * N);
    Eigen::MatrixXd R_rate_bar = Eigen::MatrixXd::Zero(nu_ * N, nu_ * N);

    for (int k = 0; k < N; ++k) {
      Q_bar.block(k * nx_, k * nx_, nx_, nx_) = Q_diag.asDiagonal();
      R_bar.block(k * nu_, k * nu_, nu_, nu_) = R_diag.asDiagonal();
      R_rate_bar.block(k * nu_, k * nu_, nu_, nu_) = R_rate_diag.asDiagonal();
    }

    // 7. Solve
    // Yaw unwrap
    double ref_yaw_0 = R_ref(2);
    while (x0(2) - ref_yaw_0 > M_PI)
      x0(2) -= 2 * M_PI;
    while (x0(2) - ref_yaw_0 < -M_PI)
      x0(2) += 2 * M_PI;

    Eigen::VectorXd E = R_ref - Phi * x0;

    // Rate Cost Matrices
    Eigen::MatrixXd P = Eigen::MatrixXd::Zero(nu_ * N, nu_ * N);
    Eigen::MatrixXd I_nu = Eigen::MatrixXd::Identity(nu_, nu_);
    for (int k = 0; k < N; ++k) {
      P.block(k * nu_, k * nu_, nu_, nu_) = I_nu;
      if (k > 0) {
        P.block(k * nu_, (k - 1) * nu_, nu_, nu_) = -I_nu;
      }
    }

    // C vector (Initial input offset)
    Eigen::VectorXd C = Eigen::VectorXd::Zero(nu_ * N);
    C.head(nu_) = u_prev_;

    // H = Gamma' Q Gamma + R + P' R_rate P
    Eigen::MatrixXd H = Gamma.transpose() * Q_bar * Gamma + R_bar +
                        P.transpose() * R_rate_bar * P;

    // F = Gamma' Q E + P' R_rate C
    Eigen::VectorXd F =
        Gamma.transpose() * Q_bar * E + P.transpose() * R_rate_bar * C;

    // Regularization
    H += Eigen::MatrixXd::Identity(nu_ * N, nu_ * N) * 1e-3;

    Eigen::VectorXd U = H.ldlt().solve(F);
    Eigen::VectorXd u0 = U.head(nu_);

    // Store previous input
    u_prev_ = u0;

    // 8. Publish
    auto cmd_msg = mpc_car_control::msg::ControlCommandBody();
    cmd_msg.header.stamp = this->now();
    cmd_msg.fx = u0(0) * m_;     // Accel -> Force
    cmd_msg.fy = u0(1) * 1000.0; // kN -> N
    cmd_msg.fz =
        u0(2) * 1000.0; // dFz -> N (Gravity comp handled in allocator?)
                        // Actually, let's output TOTAL Fz?
                        // Allocator expects Fz per wheel?
                        // Let's output dFz and let allocator add gravity?
                        // No, allocator takes Fz total.
                        // So cmd_msg.fz = m*g + u0(2)*1000.0
    cmd_msg.fz = m_ * g_ + u0(2) * 1000.0;

    cmd_msg.mx = u0(3) * 1000.0; // kNm -> Nm
    cmd_msg.my = u0(4) * 1000.0; // kNm -> Nm
    cmd_msg.mz = 0.0;

    publisher_->publish(cmd_msg);

    // Debug Logging
    double dx = current_trajectory_.points[closest_idx].x - current_state_.x;
    double dy = current_trajectory_.points[closest_idx].y - current_state_.y;
    double cte = std::sqrt(dx * dx + dy * dy);
    double yaw_err =
        current_trajectory_.yaw_profile[closest_idx] - current_state_.yaw;
    while (yaw_err > M_PI)
      yaw_err -= 2 * M_PI;
    while (yaw_err < -M_PI)
      yaw_err += 2 * M_PI;

    RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 500,
                         "CTE: %.3f m, YawErr: %.3f rad, Fy: %.1f N, Acc: %.2f",
                         cte, yaw_err, cmd_msg.fy, u0(0));
  }

  rclcpp::Publisher<mpc_car_control::msg::ControlCommandBody>::SharedPtr
      publisher_;
  rclcpp::Subscription<mpc_car_control::msg::ReferenceTrajectory>::SharedPtr
      subscription_traj_;
  rclcpp::Subscription<mpc_car_control::msg::VehicleState>::SharedPtr
      subscription_state_;
  rclcpp::TimerBase::SharedPtr timer_;

  mpc_car_control::msg::ReferenceTrajectory current_trajectory_;
  mpc_car_control::msg::VehicleState current_state_;
  bool state_received_ = false;

  // Multi-Rate State
  rclcpp::Time last_linearization_time_;
  bool first_run_ = true;
  Eigen::MatrixXd Ad_;
  Eigen::MatrixXd Bd_;

  // Previous Input
  Eigen::VectorXd u_prev_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MPCControllerNode>());
  rclcpp::shutdown();
  return 0;
}
