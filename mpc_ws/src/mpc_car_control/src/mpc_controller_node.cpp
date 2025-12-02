#include <algorithm>
#include <chrono>
#include <cmath>
#include <memory>
#include <vector>

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

    timer_ = this->create_wall_timer(
        50ms, std::bind(&MPCControllerNode::control_loop, this));

    RCLCPP_INFO(this->get_logger(), "MPC Controller Node has been started.");
  }

private:
  void traj_callback(
      const mpc_car_control::msg::ReferenceTrajectory::SharedPtr msg) {
    current_trajectory_ = *msg;
  }

  void state_callback(const mpc_car_control::msg::VehicleState::SharedPtr msg) {
    current_state_ = *msg;
    state_received_ = true;
  }

  void control_loop() {
    if (!state_received_ || current_trajectory_.points.empty()) {
      return;
    }

    // Simple MPC / Control Logic Placeholder
    // In a real implementation, this would involve solving a QP.
    // Here we implement a simple error-based feedback to demonstrate the loop.

    // Find closest point on trajectory
    // For simplicity, just take the first point or search for closest
    // This is a simplified logic for demonstration

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

    // Lookahead
    size_t target_idx =
        std::min(closest_idx + 5, current_trajectory_.points.size() - 1);

    double target_x = current_trajectory_.points[target_idx].x;
    double target_y = current_trajectory_.points[target_idx].y;
    double target_yaw = current_trajectory_.yaw_profile[target_idx];
    double target_v = current_trajectory_.velocity_profile[target_idx];

    // Errors
    double ex = target_x - current_state_.x;
    double ey = target_y - current_state_.y;
    double ev = target_v - std::sqrt(current_state_.vx * current_state_.vx +
                                     current_state_.vy * current_state_.vy);
    double eyaw = target_yaw - current_state_.yaw;

    // Normalize yaw error
    while (eyaw > M_PI)
      eyaw -= 2 * M_PI;
    while (eyaw < -M_PI)
      eyaw += 2 * M_PI;

    // Simple P-Control for Body Forces/Moments
    // Fx drives longitudinal velocity
    // Fy drives lateral error (simplified)
    // Mz drives yaw error

    double k_fx = 1000.0;
    double k_fy = 500.0;
    double k_mz = 2000.0;
    double k_fz = 5000.0;  // Stiffness for height
    double k_mx = 10000.0; // Roll stiffness
    double k_my = 10000.0; // Pitch stiffness

    // Rotate error to body frame
    double c_yaw = std::cos(current_state_.yaw);
    double s_yaw = std::sin(current_state_.yaw);

    double e_long = ex * c_yaw + ey * s_yaw;
    double e_lat = -ex * s_yaw + ey * c_yaw;

    auto cmd_msg = mpc_car_control::msg::ControlCommandBody();
    cmd_msg.header.stamp = this->now();
    cmd_msg.fx =
        k_fx * ev + 100.0 * e_long; // Combine velocity and position error
    cmd_msg.fy = k_fy * e_lat;
    cmd_msg.mz = k_mz * eyaw;

    // Vertical / Roll / Pitch Control (Simple P-Control)
    // Target Z = 0, Roll = 0, Pitch = 0 (for now)
    // Fz needs to support weight + correct error
    double mass = 1412.0;
    double g = 9.81;
    double fz_gravity = mass * g;

    cmd_msg.fz = fz_gravity + k_fz * (0.0 - current_state_.z);
    cmd_msg.mx = k_mx * (0.0 - current_state_.roll);
    cmd_msg.my = k_my * (0.0 - current_state_.pitch);

    publisher_->publish(cmd_msg);
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
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MPCControllerNode>());
  rclcpp::shutdown();
  return 0;
}
