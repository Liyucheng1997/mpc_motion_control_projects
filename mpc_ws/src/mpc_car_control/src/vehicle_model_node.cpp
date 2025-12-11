#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "mpc_car_control/msg/actuator_command.hpp"
#include "mpc_car_control/msg/vehicle_state.hpp"
#include "mpc_car_control/msg/wheel_ground_heights.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

// Constants for 14DOF Model
struct VehicleParams {
  double m = 1412.0;     // Vehicle mass [kg]
  double ms = 1270.0;    // Sprung mass [kg]
  double mu = 35.5;      // Unsprung mass per wheel [kg] (approx (m-ms)/4)
  double Ixx = 536.6;    // Roll inertia [kg m^2]
  double Iyy = 1536.7;   // Pitch inertia [kg m^2]
  double Izz = 1536.7;   // Yaw inertia [kg m^2]
  double lf = 1.015;     // Distance CG to front axle [m] (a)
  double lr = 1.9;       // Distance CG to rear axle [m] (b)
  double tf = 1.675;     // Front track width [m]
  double tr = 1.675;     // Rear track width [m]
  double h_cg = 0.54;    // CG height [m]
  double ks = 27000.0;   // Suspension stiffness [N/m] (27 kN/m)
  double cs = 2700.0;    // Suspension damping [N s/m] (27 Ns/cm -> 2700 Ns/m)
  double kt = 268000.0;  // Tire stiffness [N/m] (268 kN/m)
  double Rw = 0.3;       // Wheel radius [m]
  double Iw = 2.0;       // Wheel inertia [kg m^2]
  double C_af = 60000.0; // Front Tire cornering stiffness [N/rad]
  double C_ar = 50000.0; // Rear Tire cornering stiffness [N/rad]
  double C_x = 50000.0;  // Tire longitudinal stiffness [N]
};

struct State14DOF {
  // Chassis (Body Frame)
  double x = 0.0, y = 0.0,
         z = 0.0; // Position (Inertial frame for x,y; z relative to ground
                  // ref?) Actually, usually x,y inertial, z inertial.
  double phi = 0.0, theta = 0.0, psi = 0.0; // Euler angles (Roll, Pitch, Yaw)
  double u = 0.0, v = 0.0, w = 0.0;         // Linear velocities (Body frame)
  double p = 0.0, q = 0.0, r = 0.0;         // Angular velocities (Body frame)
  double w_dot = 0.0; // Vertical acceleration (Body frame)

  // Wheels (4 wheels: FL, FR, RL, RR)
  // Vertical displacement of unsprung mass (relative to inertial ground 0)
  std::array<double, 4> zu = {0.0, 0.0, 0.0, 0.0};
  std::array<double, 4> zu_dot = {0.0, 0.0, 0.0, 0.0};
  std::array<double, 4> omega = {0.0, 0.0, 0.0,
                                 0.0}; // Wheel angular velocities
};

class VehicleModelNode : public rclcpp::Node {
public:
  VehicleModelNode() : Node("vehicle_model_node") {
    publisher_ = this->create_publisher<mpc_car_control::msg::VehicleState>(
        "/vehicle_state", 10);

    subscription_ =
        this->create_subscription<mpc_car_control::msg::ActuatorCommand>(
            "/actuator_command", 10,
            std::bind(&VehicleModelNode::cmd_callback, this, _1));

    subscription_wheels_ =
        this->create_subscription<mpc_car_control::msg::WheelGroundHeights>(
            "/wheel_ground_heights", 10,
            std::bind(&VehicleModelNode::wheels_callback, this, _1));

    subscription_pause_ = this->create_subscription<std_msgs::msg::Empty>(
        "/pause_toggle", 10,
        std::bind(&VehicleModelNode::pause_callback, this, _1));

    // Simulation loop at 100Hz for better stability
    timer_ = this->create_wall_timer(
        10ms, std::bind(&VehicleModelNode::sim_loop, this));

    RCLCPP_INFO(this->get_logger(), "Vehicle Model Node (14DOF) started.");

    // Initialize state
    state_.z = params_.h_cg + 0.3; // Start slightly above ground
    for (int i = 0; i < 4; ++i)
      state_.zu[i] = params_.Rw; // Wheels on ground

    sim_time_ = this->now();
  }

private:
  VehicleParams params_;
  State14DOF state_;

  mpc_car_control::msg::ActuatorCommand last_cmd_;
  mpc_car_control::msg::WheelGroundHeights last_wheels_;
  bool cmd_received_ = false;
  rclcpp::Time sim_time_;

  // Smoothing variables
  double smooth_throttle_ = 0.0;
  double smooth_brake_ = 0.0;
  double smooth_delta_ = 0.0;

  rclcpp::Publisher<mpc_car_control::msg::VehicleState>::SharedPtr publisher_;
  rclcpp::Subscription<mpc_car_control::msg::ActuatorCommand>::SharedPtr
      subscription_;
  rclcpp::Subscription<mpc_car_control::msg::WheelGroundHeights>::SharedPtr
      subscription_wheels_;
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr subscription_pause_;
  bool paused_ = false;
  rclcpp::TimerBase::SharedPtr timer_;

  void
  cmd_callback(const mpc_car_control::msg::ActuatorCommand::SharedPtr msg) {
    last_cmd_ = *msg;
    cmd_received_ = true;
  }

  void wheels_callback(
      const mpc_car_control::msg::WheelGroundHeights::SharedPtr msg) {
    last_wheels_ = *msg;
  }

  void pause_callback(const std_msgs::msg::Empty::SharedPtr msg) {
    (void)msg;
    paused_ = !paused_;
    if (paused_) {
      RCLCPP_INFO(this->get_logger(), "PAUSE REQUESTED");
    } else {
      RCLCPP_INFO(this->get_logger(), "RESUME REQUESTED");
    }
  }

  // Helper to get ground z at wheel position
  double get_ground_z(int wheel_idx) {
    // wheel_idx: 0=FL, 1=FR, 2=RL, 3=RR
    if (last_wheels_.wheel_ground_heights.size() == 4) {
      return last_wheels_.wheel_ground_heights[wheel_idx];
    }
    return 0.0;
  }

  void sim_loop() {
    double dt_total = 0.01; // 10ms total step
    sim_time_ += rclcpp::Duration::from_seconds(dt_total);

    if (paused_) {
      // Still publish state to keep visualization alive, but don't integrate
      // physics
      publish_state();
      RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
                           "Simulation Paused. x: %.4f", state_.x);
      return;
    }

    int sub_steps = 20; // 0.5ms sub-step for stability
    double dt = dt_total / sub_steps;

    // Inputs with Smoothing (Low-Pass Filter)
    double alpha = 0.1; // Smoothing factor (0.0 to 1.0, lower is smoother)

    double target_delta = last_cmd_.steering_angle;
    double target_throttle = std::max(0.0, std::min(last_cmd_.throttle, 1.0));
    double target_brake = std::max(0.0, std::min(last_cmd_.brake, 1.0));

    smooth_delta_ = alpha * target_delta + (1.0 - alpha) * smooth_delta_;
    smooth_throttle_ =
        alpha * target_throttle + (1.0 - alpha) * smooth_throttle_;
    smooth_brake_ = alpha * target_brake + (1.0 - alpha) * smooth_brake_;

    double delta = smooth_delta_;
    double throttle = smooth_throttle_;
    double brake = smooth_brake_;

    std::array<double, 4> F_active = {0.0, 0.0, 0.0, 0.0};
    for (int i = 0; i < 4; ++i)
      F_active[i] = last_cmd_.active_suspension_force[i];

    for (int step = 0; step < sub_steps; ++step) {
      // 1. Calculate Forces and Moments
      double Fx_total = 0.0, Fy_total = 0.0, Fz_total = 0.0;
      double Mx_total = 0.0, My_total = 0.0, Mz_total = 0.0;

      // Wheel positions in body frame
      double xs[4] = {params_.lf, params_.lf, -params_.lr, -params_.lr};
      double ys[4] = {params_.tf / 2, -params_.tf / 2, params_.tr / 2,
                      -params_.tr / 2};

      for (int i = 0; i < 4; ++i) {
        // a. Suspension Forces
        double z_hardpoint =
            state_.z + (-xs[i] * state_.theta + ys[i] * state_.phi);
        double z_hardpoint_dot =
            state_.w + (-xs[i] * state_.q + ys[i] * state_.p);

        double F_static = params_.ms * 9.81 / 4.0;
        // Spring Force: k * (deflection_from_rest) + F_static
        // At rest: zu - z_hardpoint = -h_cg. We want Force = F_static.
        // So we add h_cg to the term.
        double F_spring =
            params_.ks * (state_.zu[i] - z_hardpoint + params_.h_cg) + F_static;
        double F_damper = params_.cs * (state_.zu_dot[i] - z_hardpoint_dot);

        double F_susp_vert = F_spring + F_damper + F_active[i];

        // b. Tire Forces
        double z_ground = get_ground_z(i);
        double tire_compression = z_ground - (state_.zu[i] - params_.Rw);
        double F_tire_z = 0.0;
        if (tire_compression > 0) {
          // Spring + Damping for Tire (Stabilizes Simulation)
          double tire_damping = 500.0 * state_.zu_dot[i];
          F_tire_z = params_.kt * tire_compression - tire_damping;
          F_tire_z = std::max(0.0, F_tire_z);
        } else {
          F_tire_z = 0.0;
        }

        // Longitudinal/Lateral Slip
        double v_wx = state_.u - ys[i] * state_.r;
        double v_wy = state_.v + xs[i] * state_.r;

        double delta_i = (i < 2) ? delta : 0.0;

        // Tire velocities in wheel frame
        double v_tx = v_wx * std::cos(delta_i) + v_wy * std::sin(delta_i);
        double v_ty = -v_wx * std::sin(delta_i) + v_wy * std::cos(delta_i);

        // Slip angles
        double alpha = 0.0;
        if (std::abs(v_tx) > 0.1) {
          alpha = -std::atan2(v_ty, v_tx);
        }

        // Longitudinal slip
        double kappa = 0.0;
        if (std::abs(v_tx) > 0.1) {
          kappa = (state_.omega[i] * params_.Rw - v_tx) / std::abs(v_tx);
        }

        // Tire Forces (Linear Model)
        double F_tx = params_.C_x * kappa;
        double C_alpha = (i < 2) ? params_.C_af : params_.C_ar;
        double F_ty = C_alpha * alpha;

        // Limit forces to friction circle (simplified)
        double mu_friction = 0.9;
        double F_max = mu_friction * F_tire_z;
        double F_total_plane = std::sqrt(F_tx * F_tx + F_ty * F_ty);
        if (F_total_plane > F_max && F_max > 0) {
          double scale = F_max / F_total_plane;
          F_tx *= scale;
          F_ty *= scale;
        }

        // Forces in Body Frame
        double F_bx = F_tx * std::cos(delta_i) - F_ty * std::sin(delta_i);
        double F_by = F_tx * std::sin(delta_i) + F_ty * std::cos(delta_i);

        // Add to total chassis forces/moments
        Fx_total += F_bx;
        Fy_total += F_by;
        Fz_total += F_susp_vert; // Suspension force acts on body

        Mx_total += ys[i] * F_susp_vert;         // Roll moment from susp
        My_total -= xs[i] * F_susp_vert;         // Pitch moment from susp
        Mz_total += xs[i] * F_by - ys[i] * F_bx; // Yaw moment

        // Unsprung Mass Dynamics (Vertical)
        // m_u * z_u_dd = F_tire_z - F_susp_vert - m_u * g
        double zu_dd =
            (F_tire_z - F_susp_vert - params_.mu * 9.81) / params_.mu;
        state_.zu_dot[i] += zu_dd * dt;
        state_.zu[i] += state_.zu_dot[i] * dt;

        // Wheel Rotation Dynamics
        double T_net_applied = 0.0;

        // Check if direct torque control is active (from Allocator DYC)
        double total_direct_torque = 0.0;
        for (double t : last_cmd_.wheel_torque)
          total_direct_torque += std::abs(t);

        if (total_direct_torque > 1e-3) {
          T_net_applied = last_cmd_.wheel_torque[i];
          // Positive T increases omega (Engine/Motor)
          // Negative T decreases omega (Brake/Regen)
        } else {
          // Powertrain Model (Logic for Throttle->Torque)
          // Allows using simple 'Throttle' commands (e.g. from PID)
          double T_drive = 0.0;
          double T_brake = 0.0;
          if (throttle > 0) {
            // AWD Map
            T_drive = (throttle * 500.0) / 4.0;
          }
          if (brake > 0) {
            T_brake = (brake * 1000.0) / 4.0;
            if (state_.omega[i] > 0)
              T_brake *= 1.0;
            else if (state_.omega[i] < 0)
              T_brake *= -1.0; // Oppose motion
          }
          T_net_applied = T_drive - T_brake;
        }

        double omega_dot = (T_net_applied - F_tx * params_.Rw) / params_.Iw;
        state_.omega[i] += omega_dot * dt;
      }

      // Chassis Dynamics (Newton-Euler)
      double g = -9.81; // Gravity acts DOWN in Z-up frame
      double gx = -g * std::sin(state_.theta); // Nose Down (theta > 0) ->
                                               // Gravity pulls Forward (gx > 0)
      double gy = g * std::cos(state_.theta) *
                  std::sin(state_.phi); // Roll Right (phi > 0) -> Gravity pulls
                                        // Right (gy < 0)
      double gz = g * std::cos(state_.theta) * std::cos(state_.phi);

      double u_dot = (Fx_total / params_.ms) + gx + state_.v * state_.r -
                     state_.w * state_.q;
      double v_dot = (Fy_total / params_.ms) + gy - state_.u * state_.r +
                     state_.w * state_.p;
      double w_dot = (Fz_total / params_.ms) + gz + state_.u * state_.q -
                     state_.v * state_.p;

      // Rotational
      double p_dot =
          (Mx_total - (params_.Izz - params_.Iyy) * state_.q * state_.r) /
          params_.Ixx;
      double q_dot =
          (My_total - (params_.Ixx - params_.Izz) * state_.p * state_.r) /
          params_.Iyy;
      double r_dot =
          (Mz_total - (params_.Iyy - params_.Ixx) * state_.p * state_.q) /
          params_.Izz;

      // Integration
      state_.u += u_dot * dt;
      state_.v += v_dot * dt;
      state_.w += w_dot * dt;
      state_.w_dot = w_dot; // Store for publishing
      state_.p += p_dot * dt;
      state_.q += q_dot * dt;
      state_.r += r_dot * dt;

      // Kinematics (Body to Inertial)
      double c_psi = std::cos(state_.psi), s_psi = std::sin(state_.psi);
      double c_theta = std::cos(state_.theta), s_theta = std::sin(state_.theta);
      double c_phi = std::cos(state_.phi), s_phi = std::sin(state_.phi);

      double x_dot = c_theta * c_psi * state_.u +
                     (s_phi * s_theta * c_psi - c_phi * s_psi) * state_.v +
                     (c_phi * s_theta * c_psi + s_phi * s_psi) * state_.w;
      double y_dot = c_theta * s_psi * state_.u +
                     (s_phi * s_theta * s_psi + c_phi * c_psi) * state_.v +
                     (c_phi * s_theta * s_psi - s_phi * c_psi) * state_.w;
      double z_dot = -s_theta * state_.u + s_phi * c_theta * state_.v +
                     c_phi * c_theta * state_.w;

      state_.x += x_dot * dt;
      state_.y += y_dot * dt;
      state_.z += z_dot * dt;

      // Euler rates
      double phi_dot = state_.p + (state_.q * s_phi + state_.r * c_phi) *
                                      std::tan(state_.theta);
      double theta_dot = state_.q * c_phi - state_.r * s_phi;
      double psi_dot = (state_.q * s_phi + state_.r * c_phi) / c_theta;

      state_.phi += phi_dot * dt;
      state_.theta += theta_dot * dt;
      state_.psi += psi_dot * dt;

      // Prevent Gimbal Lock Singularity
      if (state_.theta > 1.4)
        state_.theta = 1.4;
      if (state_.theta < -1.4)
        state_.theta = -1.4;
    }

    // Safety check for NaNs
    if (std::isnan(state_.x) || std::isnan(state_.z) || std::isnan(state_.u) ||
        std::isnan(state_.w)) {
      RCLCPP_ERROR(this->get_logger(),
                   "NaN detected! Resetting. x: %f, z: %f, u: %f, w: %f",
                   state_.x, state_.z, state_.u, state_.w);
      state_ = State14DOF();
      state_.z = params_.h_cg + 0.3;
      for (int i = 0; i < 4; ++i)
        state_.zu[i] = params_.Rw;
    }

    // Publish State
    publish_state();
  }

  void publish_state() {
    auto msg = mpc_car_control::msg::VehicleState();
    msg.header.stamp = this->now();
    msg.header.frame_id = "map";
    msg.x = state_.x;
    msg.y = state_.y;
    msg.z = state_.z;
    msg.yaw = state_.psi;
    msg.pitch = state_.theta;
    msg.roll = state_.phi;
    msg.vx = state_.u;
    msg.vy = state_.v;
    msg.vz = state_.w;
    msg.yaw_rate = state_.r;
    msg.pitch_rate = state_.q;
    msg.roll_rate = state_.p;
    msg.az = state_.w_dot; // Vertical acceleration (body frame)

    publisher_->publish(msg);
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VehicleModelNode>());
  rclcpp::shutdown();
  return 0;
}
