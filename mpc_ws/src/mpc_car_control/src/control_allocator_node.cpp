#include <algorithm>
#include <cmath>
#include <memory>

#include "mpc_car_control/msg/actuator_command.hpp"
#include "mpc_car_control/msg/control_command_body.hpp"
#include "mpc_car_control/msg/vehicle_state.hpp"
#include "rclcpp/rclcpp.hpp"

using std::placeholders::_1;

class ControlAllocatorNode : public rclcpp::Node {
public:
  ControlAllocatorNode() : Node("control_allocator_node") {
    publisher_ = this->create_publisher<mpc_car_control::msg::ActuatorCommand>(
        "/actuator_command", 10);

    subscription_cmd_ =
        this->create_subscription<mpc_car_control::msg::ControlCommandBody>(
            "/control_command_body", 10,
            std::bind(&ControlAllocatorNode::cmd_callback, this, _1));

    subscription_state_ =
        this->create_subscription<mpc_car_control::msg::VehicleState>(
            "/vehicle_state", 10,
            std::bind(&ControlAllocatorNode::state_callback, this, _1));

    RCLCPP_INFO(this->get_logger(),
                "Control Allocator Node (Inverse Pacejka) Started.");
  }

private:
  void state_callback(const mpc_car_control::msg::VehicleState::SharedPtr msg) {
    current_state_ = *msg;
    state_received_ = true;
  }

  // Pacejka Parameters
  const double B_ = 10.0;
  const double C_ = 1.3;
  const double E_ = 0.97;
  const double D_factor_ = 1.1; // D = 1.1 * Fz

  // Inverse Pacejka Solver (Bisection)
  double solve_pacejka(double Fy_cmd, double Fz) {
    double D = D_factor_ * Fz;
    // Saturation
    if (Fy_cmd > D)
      Fy_cmd = D;
    if (Fy_cmd < -D)
      Fy_cmd = -D;

    // Function to zero: Pacejka(alpha) - Fy_cmd = 0
    auto fy_error = [&](double alpha) {
      return D * std::sin(C_ * std::atan(
                                   B_ * alpha -
                                   E_ * (B_ * alpha - std::atan(B_ * alpha)))) -
             Fy_cmd;
    };

    double x1 = -0.6; // -34 deg
    double x2 = 0.6;  // +34 deg

    // Check signs
    if (fy_error(x1) * fy_error(x2) > 0) {
      // Fallback: Linear approximation or boundary
      return (Fy_cmd > 0) ? x2 : x1;
    }

    // Bisection
    for (int i = 0; i < 20; ++i) {
      double mid = (x1 + x2) / 2.0;
      if (fy_error(mid) * fy_error(x1) <= 0) { // Fix: <= 0 to handle exact root
        x2 = mid;
      } else {
        x1 = mid;
      }
    }
    return (x1 + x2) / 2.0;
  }

  void
  cmd_callback(const mpc_car_control::msg::ControlCommandBody::SharedPtr msg) {
    auto cmd = mpc_car_control::msg::ActuatorCommand();
    cmd.header.stamp = this->now();

    // 1. Longitudinal
    if (msg->fx >= 0) {
      cmd.throttle = std::min(std::max(msg->fx / 1000.0, 0.0), 1.0);
      cmd.brake = 0.0;
    } else {
      cmd.throttle = 0.0;
      cmd.brake = std::min(std::max(-msg->fx / 2000.0, 0.0), 1.0);
    }

    // 2. Lateral (Inverse Pacejka)
    // msg->fy is now the COMMANDED LATERAL FORCE (N)
    if (state_received_) {
      double vx = std::max(current_state_.vx, 0.1); // Avoid div by zero
      double vy = current_state_.vy;
      double r = current_state_.yaw_rate;
      double lf = 1.015;

      // Estimate Fz (Static + Weight Transfer ignored for now)
      double Fz_front = (1412.0 * 9.81 * 0.5) / 2.0; // Approx per wheel front

      // Solve for Slip Angle alpha
      // Note: msg->fy is total front axle force? Or per wheel?
      // MPC usually outputs total body force.
      // Let's assume msg->fy is TOTAL front axle force.
      // So per wheel is msg->fy / 2.0.
      double Fy_per_wheel = msg->fy / 2.0;

      double alpha = solve_pacejka(Fy_per_wheel, Fz_front);

      // Calculate Steering Angle
      // delta = alpha + atan2(vy + lf*r, vx)
      // Fix: Disable kinematic term at low speeds to prevent singularity/noise
      if (vx > 1.0) {
        double kin_term = std::atan2(vy + lf * r, vx);
        cmd.steering_angle = alpha + kin_term;
        // Keep debug log for verification
        RCLCPP_INFO_THROTTLE(
            this->get_logger(), *this->get_clock(), 200,
            "Fy: %.1f, Alpha: %.3f, Kin: %.3f, Delta: %.3f, vx: %.1f, vy: %.1f",
            msg->fy, alpha, kin_term, cmd.steering_angle, vx, vy);
      } else {
        cmd.steering_angle = alpha;
      }
      // Store for next run if needed (fallback)
      last_alpha_ = alpha;
    } else {
      cmd.steering_angle = 0.0;
    }

    // Saturation
    cmd.steering_angle = std::min(std::max(cmd.steering_angle, -0.5), 0.5);
    // 3. Suspension
    double fz_per_wheel = msg->fz / 4.0;
    double roll_force = msg->mx / 2.0;
    double pitch_force = msg->my / 2.0;

    // Positive My -> Nose Down -> Front Down (-), Rear Up (+)
    // But wait, F_susp is UPWARD force on body.
    // To pitch Nose Down: Front Force < Rear Force.
    // So Front should decrease, Rear should increase.
    // pitch_force = My/2.
    // FL/FR: -pitch_force
    // RL/RR: +pitch_force
    cmd.active_suspension_force[0] = fz_per_wheel + roll_force - pitch_force;
    cmd.active_suspension_force[1] = fz_per_wheel - roll_force - pitch_force;
    cmd.active_suspension_force[2] = fz_per_wheel + roll_force + pitch_force;
    cmd.active_suspension_force[3] = fz_per_wheel - roll_force + pitch_force;

    publisher_->publish(cmd);
  }

  rclcpp::Publisher<mpc_car_control::msg::ActuatorCommand>::SharedPtr
      publisher_;
  rclcpp::Subscription<mpc_car_control::msg::ControlCommandBody>::SharedPtr
      subscription_cmd_;
  rclcpp::Subscription<mpc_car_control::msg::VehicleState>::SharedPtr
      subscription_state_;

  mpc_car_control::msg::VehicleState current_state_;
  bool state_received_ = false;
  double last_alpha_ = 0.0;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ControlAllocatorNode>());
  rclcpp::shutdown();
  return 0;
}
