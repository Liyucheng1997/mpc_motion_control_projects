#include <algorithm>
#include <cmath>
#include <memory>

#include "mpc_car_control/msg/actuator_command.hpp"
#include "mpc_car_control/msg/reference_trajectory.hpp"
#include "mpc_car_control/msg/vehicle_state.hpp"
#include "rclcpp/rclcpp.hpp"

using std::placeholders::_1;

class PIDControllerNode : public rclcpp::Node {
public:
  PIDControllerNode() : Node("pid_controller_node") {
    // Publishers
    publisher_ = this->create_publisher<mpc_car_control::msg::ActuatorCommand>(
        "/actuator_command_pid", 10);

    // Subscriptions
    sub_state_ = this->create_subscription<mpc_car_control::msg::VehicleState>(
        "/vehicle_state", 10,
        std::bind(&PIDControllerNode::state_callback, this, _1));

    sub_ref_ =
        this->create_subscription<mpc_car_control::msg::ReferenceTrajectory>(
            "/reference_trajectory", 10,
            std::bind(&PIDControllerNode::ref_callback, this, _1));

    // Initialize PID gains
    // Speed
    kp_v_ = 1.0;
    ki_v_ = 0.1;
    kd_v_ = 0.0;

    // Steering (Stanley-like / PD)
    kp_lat_ = 0.5;  // Cross-track gain
    kp_head_ = 2.0; // Heading error gain

    prev_speed_error_ = 0.0;
    integral_speed_error_ = 0.0;
    prev_throttle_ = 0.0;
    prev_steering_ = 0.0;

    RCLCPP_INFO(this->get_logger(), "PID Controller Node has been started.");
  }

private:
  void
  ref_callback(const mpc_car_control::msg::ReferenceTrajectory::SharedPtr msg) {
    ref_traj_ = *msg;
  }

  void state_callback(const mpc_car_control::msg::VehicleState::SharedPtr msg) {
    if (ref_traj_.points.empty()) {
      return;
    }

    auto cmd = mpc_car_control::msg::ActuatorCommand();
    cmd.header.stamp = this->now();

    // 1. Find closest point on reference trajectory
    double min_dist_sq = std::numeric_limits<double>::max();
    size_t closest_idx = 0;

    for (size_t i = 0; i < ref_traj_.points.size(); ++i) {
      double dx = msg->x - ref_traj_.points[i].x;
      double dy = msg->y - ref_traj_.points[i].y;
      double dist_sq = dx * dx + dy * dy;
      if (dist_sq < min_dist_sq) {
        min_dist_sq = dist_sq;
        closest_idx = i;
      }
    }

    auto ref_pt = ref_traj_.points[closest_idx];

    // 2. Speed Control (PID)
    double target_speed = 10.0; // Default target if not in trajectory
    // Ideally ref_traj should have speed, but Point message might not.
    // Assuming constant speed for now or deriving from trajectory if possible.
    // For this simple implementation, let's aim for 10 m/s or use a parameter.

    double current_speed = std::sqrt(msg->vx * msg->vx + msg->vy * msg->vy);
    double speed_error = target_speed - current_speed;

    // Anti-windup clamping
    if (std::abs(integral_speed_error_) < 5.0) {
      integral_speed_error_ += speed_error * 0.01; // Assuming ~100Hz
    }

    double speed_cmd = kp_v_ * speed_error + ki_v_ * integral_speed_error_ +
                       kd_v_ * (speed_error - prev_speed_error_);
    prev_speed_error_ = speed_error;

    // Slew Rate Limiting
    double throttle_cmd = 0.0;
    double brake_cmd = 0.0;

    if (speed_cmd >= 0) {
      throttle_cmd = std::min(std::max(speed_cmd, 0.0), 1.0);
      brake_cmd = 0.0;
    } else {
      throttle_cmd = 0.0;
      brake_cmd = std::min(std::max(-speed_cmd, 0.0), 1.0);
    }

    // Limit Throttle Change (e.g., 1.0 per second -> 0.01 per 10ms step)
    // Assuming ~100Hz callback
    double max_throttle_change = 0.05;
    throttle_cmd =
        std::min(std::max(throttle_cmd, prev_throttle_ - max_throttle_change),
                 prev_throttle_ + max_throttle_change);
    prev_throttle_ = throttle_cmd;

    cmd.throttle = throttle_cmd;
    cmd.brake = brake_cmd;

    // 3. Steering Control (Lateral + Heading)
    // Calculate Cross-Track Error
    // Vector from closest point to vehicle
    double dx = msg->x - ref_pt.x;
    double dy = msg->y - ref_pt.y;

    // Path tangent (approximate using next point if available)
    double path_yaw = 0.0;
    if (closest_idx + 1 < ref_traj_.points.size()) {
      double ddx = ref_traj_.points[closest_idx + 1].x - ref_pt.x;
      double ddy = ref_traj_.points[closest_idx + 1].y - ref_pt.y;
      path_yaw = std::atan2(ddy, ddx);
    } else if (closest_idx > 0) {
      double ddx = ref_pt.x - ref_traj_.points[closest_idx - 1].x;
      double ddy = ref_pt.y - ref_traj_.points[closest_idx - 1].y;
      path_yaw = std::atan2(ddy, ddx);
    }

    // Cross track error magnitude is distance, sign depends on side
    // Rotate vehicle pos into path frame to find y-offset
    double sin_yaw = std::sin(path_yaw);
    double cos_yaw = std::cos(path_yaw);
    // e_y = -sin(psi_path)*(x - x_path) + cos(psi_path)*(y - y_path)
    double cross_track_error = -sin_yaw * dx + cos_yaw * dy;

    // Heading Error
    double heading_error = msg->yaw - path_yaw;
    // Normalize angle to [-pi, pi]
    while (heading_error > M_PI)
      heading_error -= 2.0 * M_PI;
    while (heading_error < -M_PI)
      heading_error += 2.0 * M_PI;

    // Control Law
    double steer_cmd = -kp_lat_ * cross_track_error - kp_head_ * heading_error;

    // Clamp
    double target_steer = std::min(std::max(steer_cmd, -0.5), 0.5);

    // Limit Steering Change (e.g., 2.0 rad/s -> 0.02 rad per step)
    double max_steer_change = 0.05;
    target_steer =
        std::min(std::max(target_steer, prev_steering_ - max_steer_change),
                 prev_steering_ + max_steer_change);
    prev_steering_ = target_steer;

    cmd.steering_angle = target_steer;

    // 4. Suspension (Passive)
    cmd.active_suspension_force = {0.0, 0.0, 0.0, 0.0};

    publisher_->publish(cmd);
  }

  rclcpp::Publisher<mpc_car_control::msg::ActuatorCommand>::SharedPtr
      publisher_;
  rclcpp::Subscription<mpc_car_control::msg::VehicleState>::SharedPtr
      sub_state_;
  rclcpp::Subscription<mpc_car_control::msg::ReferenceTrajectory>::SharedPtr
      sub_ref_;

  mpc_car_control::msg::ReferenceTrajectory ref_traj_;

  // Gains
  double kp_v_, ki_v_, kd_v_;
  double kp_lat_, kp_head_;

  // State
  double prev_speed_error_;
  double integral_speed_error_;
  double prev_throttle_;
  double prev_steering_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PIDControllerNode>());
  rclcpp::shutdown();
  return 0;
}
