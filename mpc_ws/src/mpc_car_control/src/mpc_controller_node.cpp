#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
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

    // 100Hz MPC loop - TIMER REMOVED (Use Callback for Sync)
    // timer_ = this->create_wall_timer(
    //    10ms, std::bind(&MPCControllerNode::control_loop, this));

    u_prev_ = Eigen::VectorXd::Zero(nu_);

    // 1. Declare and Get Parameters for Live Tuning
    this->declare_parameter("q_pos", 1000.0);
    this->declare_parameter("q_yaw", 2000.0);
    this->declare_parameter("q_vx", 10.0);
    this->declare_parameter("q_roll", 1500.0);
    this->declare_parameter("q_pitch", 1500.0);
    this->declare_parameter(
        "q_z", 1000.0); // Tuned: 500 -> 1000 (Better Height Tracking)
    this->declare_parameter(
        "q_vz", 200.0); // Tuned: 50 -> 200 (Suppresses Impact Spikes)
    this->declare_parameter("r_accel", 1.0);
    this->declare_parameter("r_steer", 1.0);
    this->declare_parameter("r_suspension",
                            0.005); // Tuned: 0.01 -> 0.005 (Softer Constraint)
    this->declare_parameter("r_yaw_moment", 10000.0);
    this->declare_parameter("deadband_rad", 0.005); // ~0.3 deg

    Ad_ = Eigen::MatrixXd::Identity(nx_, nx_);
    Bd_ = Eigen::MatrixXd::Zero(nx_, nu_);

    RCLCPP_INFO(this->get_logger(),
                "MPC Controller Optimized & Parameterized Started.");
  }

  ~MPCControllerNode() {
    // Save execution times to CSV
    std::string log_path =
        "/home/yucheng/MPC_Projects/mpc_motion_control_projects/mpc_ws/"
        "plot/mpc_execution_times.csv";
    std::ofstream csv_file(log_path);
    if (csv_file.is_open()) {
      csv_file << "Execution Time (ms)\n";
      for (const auto &time : execution_times_) {
        csv_file << time << "\n";
      }
      csv_file.close();
      RCLCPP_INFO(this->get_logger(), "Saved execution times to %s",
                  log_path.c_str());
    } else {
      RCLCPP_ERROR(this->get_logger(), "Failed to open log file: %s",
                   log_path.c_str());
    }
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

  // PID Parameters REMOVED (Parallel Architecture)

  // MPC Parameters
  const int N_ = 20; // Prediction Horizon (0.4s at dt=0.02) - User Selected
  const int Nc_ = 3; // Control Horizon - User Selected (Best Performance)
  const double dt_ = 0.02; // Time step (Stable discretization)
  const int nx_ = 12;      // [x, y, psi, vx, vy, wz, z, phi, theta, vz, p, q]
  const int nu_ = 6;       // [accel, Fyf_kN, dFz_kN, Mx_kNm, My_kNm, Mz_kNm]

  void traj_callback(
      const mpc_car_control::msg::ReferenceTrajectory::SharedPtr msg) {
    current_trajectory_ = *msg;
  }

  void state_callback(const mpc_car_control::msg::VehicleState::SharedPtr msg) {
    current_state_ = *msg;
    state_received_ = true;

    // Trigger Control Loop Synchronously
    control_loop();
  }

  // Get Linearized System Matrices (Jacobian) for Dynamic Bicycle Model +
  // Vertical State: x = [x, y, psi, vx, vy, wz, z, phi, theta, vz, p, q]
  // Control: u = [a, Fyf_kN, dFz_kN, Mx_kNm, My_kNm, Mz_kNm]
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
    // Fyf = Caf * (delta - (vy + lf*wz)/vx)  <-- NEW INPUT: delta

    double dFyr_dvy = -Car_ / vx;
    double dFyr_dwz = Car_ * lr_ / vx;

    // Dynamics from Rear Wheel (Fyr)
    A(4, 3) = -wz;                // dvy/dvx
    A(4, 4) = dFyr_dvy / m_;      // dvy/dvy
    A(4, 5) = dFyr_dwz / m_ - vx; // dvy/dwz
    A(4, 7) = -g_; // dvy/dphi (Gravity: Roll right -> Pull right (-Y))

    // Dynamics from Front Wheel (Fyf) - Control Input: delta
    // Fyf approx = Caf * delta - Caf/vx * vy - Caf*lf/vx * wz
    // We add the STATE terms from Front Wheel to A matrix
    double dFyf_dvy = -Caf_ / vx;
    double dFyf_dwz = -Caf_ * lf_ / vx;

    A(4, 4) += dFyf_dvy / m_;
    A(4, 5) += dFyf_dwz / m_;

    // Input B(4,1): dvy/ddelta = Caf / m
    B(4, 1) = Caf_ / m_;

    // 6. wz_dot = (lf*Fyf - lr*Fyr + Mz)/Iz
    // Rear wheel terms (already accounted for Fyr, but we need to verify...
    // The original code calculated dFyr/dState and put it in A.
    // Now we must also include dFyf/dState in A because Fyf is no longer 'u',
    // 'delta' is 'u'.

    A(5, 4) = (lf_ * dFyf_dvy - lr_ * dFyr_dvy) / Iz_; // dwz/dvy
    A(5, 5) = (lf_ * dFyf_dwz - lr_ * dFyr_dwz) / Iz_; // dwz/dwz

    // Input B(5,1): dwz/ddelta = lf * Caf / Iz
    B(5, 1) = (lf_ * Caf_) / Iz_;
    B(5, 5) = 1000.0 / Iz_; // dwz/dMz_kNm (Direct Yaw Moment)

    // 7. z_dot = vz
    A(6, 9) = 1.0;
    // ... (Lines 138-152 match existing structure usually, but I need to be
    // careful with range) I will just return the modified function block to be
    // safe. Wait, replace_file_content works on chunks. I need to make sure I
    // cover the range correctly. The B matrix changes are the critical part.

    // Let's look at weights too. I should update weights in `control_loop`
    // (separate call or same?) I'll do B matrix first.

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
    auto start_time = std::chrono::high_resolution_clock::now();

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

    // 5. Prediction Matrices (Optimized O(N) Construction)
    int N = N_;
    Eigen::MatrixXd Phi(nx_ * N, nx_);
    Eigen::MatrixXd Gamma(nx_ * N, nu_ * N);
    Gamma.setZero();

    // Precompute powders of Ad and Ad^k * Bd
    std::vector<Eigen::MatrixXd> Ad_pow(N + 1);
    Ad_pow[0] = Eigen::MatrixXd::Identity(nx_, nx_);
    for (int i = 1; i <= N; ++i) {
      Ad_pow[i] = Ad_pow[i - 1] * Ad;
    }

    std::vector<Eigen::MatrixXd> Ad_pow_Bd(N);
    for (int i = 0; i < N; ++i) {
      Ad_pow_Bd[i] = Ad_pow[i] * Bd;
    }

    // Fill Phi and Gamma
    for (int i = 0; i < N; ++i) {
      Phi.middleRows(i * nx_, nx_) = Ad_pow[i + 1];
      for (int j = 0; j <= i; ++j) {
        Gamma.block(i * nx_, j * nu_, nx_, nu_) = Ad_pow_Bd[i - j];
      }
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

    // 6. Dynamic Weights from Parameters
    Eigen::VectorXd Q_diag(nx_);

    // ... (existing params)

    double q_pos = this->get_parameter("q_pos").as_double();
    double q_yaw = this->get_parameter("q_yaw").as_double();
    double q_vx = this->get_parameter("q_vx").as_double();
    double q_roll = this->get_parameter("q_roll").as_double();
    double q_pitch = this->get_parameter("q_pitch").as_double();
    double q_z = this->get_parameter("q_z").as_double();
    double q_vz = this->get_parameter("q_vz").as_double();

    // [x, y, psi, vx, vy, wz, z, phi, theta, vz, p, q]
    Q_diag << q_pos, q_pos, q_yaw, q_vx, 10.0, 10.0, q_z, q_roll, q_pitch, q_vz,
        50.0, 50.0;

    Eigen::VectorXd R_diag(nu_);
    double r_accel = this->get_parameter("r_accel").as_double();
    double r_steer = this->get_parameter("r_steer").as_double();
    double r_susp = this->get_parameter("r_suspension").as_double();
    double r_mz = this->get_parameter("r_yaw_moment").as_double();

    // [accel, delta_rad, dFz_kN, Mx_kNm, My_kNm, Mz_kNm]
    R_diag << r_accel, r_steer, r_susp, r_susp, r_susp, r_mz;

    Eigen::VectorXd R_rate_diag(nu_);
    R_rate_diag << 1.0, 1.0, 0.1, 0.1, 0.1, 1000.0; // 降低悬架变化率惩罚

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

    // Higher Regularization for Stability
    H += Eigen::MatrixXd::Identity(nu_ * N, nu_ * N) * 1.0;

    // Robust Solver: Householder QR decomposition (More stable than LDLT)
    Eigen::VectorXd U = H.colPivHouseholderQr().solve(F);

    // 8. Publish & Saturate
    auto cmd_msg = mpc_car_control::msg::ControlCommandBody();
    cmd_msg.header.stamp = this->now();

    Eigen::VectorXd u0 = U.head(nu_);

    // SAFETY CHECK: NaNs
    if (std::isnan(u0.sum())) {
      RCLCPP_ERROR(this->get_logger(),
                   "MPC SOLVER FAILED (NaN). Emergency Stop.");
      u0.setZero();
      u0(0) = -1.0; // Brake
    }

    // HYBRID OVERRIDE REMOVED - MPC solves for everything, but Allocator only
    // uses Suspension.

    // Store previous input
    u_prev_ = u0;

    // Saturation Limits
    double fx_lim = 5000.0; // 5kN
    double delta_lim = 0.5; // 0.5 rad (~28 deg)
    double mz_lim = 0.0;    // 0kNm (DISABLE DYC)
    double mx_lim = 6.0;    // 6kNm (Approx physical limit of 3000N/wheel)
    double my_lim = 6.0;    // 6kNm

    cmd_msg.fx = std::min(std::max(u0(0) * m_, -fx_lim), fx_lim);

    // NEW: Pass Steering Angle directly in the 'fy' field
    // This is a protocol change between MPC and Allocator
    cmd_msg.fy = std::min(std::max(u0(1), -delta_lim), delta_lim);

    // Fz
    double fz_val = m_ * g_ + u0(2) * 1000.0;
    cmd_msg.fz = std::max(0.0, fz_val); // No negative downforce (flying)

    // Deadband Logic: Avoid jitter on flat ground
    double deadband = this->get_parameter("deadband_rad").as_double();
    if (std::abs(current_state_.roll) < deadband &&
        std::abs(current_state_.pitch) < deadband) {
      // Reduced sensitivity if nearly flat
      cmd_msg.mx =
          std::min(std::max(u0(3), -mx_lim), mx_lim) * 100.0; // 10% force
      cmd_msg.my = std::min(std::max(u0(4), -my_lim), my_lim) * 100.0;
    } else {
      cmd_msg.mx =
          std::min(std::max(u0(3), -mx_lim), mx_lim) * 1000.0; // Normal force
      cmd_msg.my = std::min(std::max(u0(4), -my_lim), my_lim) * 1000.0;
    }

    cmd_msg.mz = std::min(std::max(u0(5) * 1000.0, -mz_lim), mz_lim);

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

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        end_time - start_time);
    double current_execution_time = duration.count() / 1000.0;
    execution_times_.push_back(current_execution_time); // Convert to ms

    RCLCPP_INFO_THROTTLE(
        this->get_logger(), *this->get_clock(), 500,
        "MPC[dFz:%.0f Mx:%.0f My:%.0f] Err[CTE:%.2f Yaw:%.2f] CompTime:%.2fms",
        u0(2), u0(3), u0(4), cte, yaw_err, current_execution_time);
  }

  rclcpp::Publisher<mpc_car_control::msg::ControlCommandBody>::SharedPtr
      publisher_;
  rclcpp::Subscription<mpc_car_control::msg::ReferenceTrajectory>::SharedPtr
      subscription_traj_;
  rclcpp::Subscription<mpc_car_control::msg::VehicleState>::SharedPtr
      subscription_state_;
  // rclcpp::TimerBase::SharedPtr timer_; // REMOVED

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

  // Profiling
  std::vector<double> execution_times_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MPCControllerNode>());
  rclcpp::shutdown();
  return 0;
}
