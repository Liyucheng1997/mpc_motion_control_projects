#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>

#include "mpc_car_control/msg/actuator_command.hpp"
#include "mpc_car_control/msg/control_command_body.hpp"
#include "mpc_car_control/msg/vehicle_state.hpp"
#include "rclcpp/rclcpp.hpp"

using std::placeholders::_1;

class ControlAllocatorNode : public rclcpp::Node {
public:
  ControlAllocatorNode() : Node("control_allocator_node") {
    this->declare_parameter("active_suspension_enabled", true);

    publisher_ = this->create_publisher<mpc_car_control::msg::ActuatorCommand>(
        "/actuator_command", 10);

    // MPC Subscription (Ride Control)
    subscription_mpc_ =
        this->create_subscription<mpc_car_control::msg::ControlCommandBody>(
            "/control_command_body", 10,
            std::bind(&ControlAllocatorNode::mpc_callback, this, _1));

    // PID Subscription (Trajectory Control)
    subscription_pid_ =
        this->create_subscription<mpc_car_control::msg::ActuatorCommand>(
            "/actuator_command_pid", 10,
            std::bind(&ControlAllocatorNode::pid_callback, this, _1));

    subscription_state_ =
        this->create_subscription<mpc_car_control::msg::VehicleState>(
            "/vehicle_state", 10,
            std::bind(&ControlAllocatorNode::state_callback, this, _1));

    // Initialize Cache
    suspension_force_cache_ = {0.0, 0.0, 0.0, 0.0};

    bool active_enabled =
        this->get_parameter("active_suspension_enabled").as_bool();

    RCLCPP_INFO(
        this->get_logger(),
        "Control Allocator Mixer Started (PID+MPC Fusion). Active Susp: %s",
        active_enabled ? "ON" : "OFF");
  }

private:
  void state_callback(const mpc_car_control::msg::VehicleState::SharedPtr msg) {
    current_state_ = *msg;
    state_received_ = true;
  }

  // Linear Tire Parameters (Match Vehicle Model)
  // const double C_af_ = 60000.0; // Front Cornering Stiffness - UNUSED in
  // Steering pass-through mode
  const double wheel_radius = 0.3; // Example value, adjust as needed

  // Cache for MPC commands
  std::array<double, 4> suspension_force_cache_;

  // 1. MPC Callback: Update Suspension Cache ONLY
  void
  mpc_callback(const mpc_car_control::msg::ControlCommandBody::SharedPtr msg) {
    // Calculate Active Suspension Forces from Body Forces (MPC)
    double fz_per_wheel = msg->fz / 4.0;
    double roll_force = msg->mx / 2.0;
    double pitch_force = msg->my / 2.0;

    suspension_force_cache_[0] = std::min(
        std::max(fz_per_wheel + roll_force - pitch_force, -3000.0), 3000.0);
    suspension_force_cache_[1] = std::min(
        std::max(fz_per_wheel - roll_force - pitch_force, -3000.0), 3000.0);
    suspension_force_cache_[2] = std::min(
        std::max(fz_per_wheel + roll_force + pitch_force, -3000.0), 3000.0);
    suspension_force_cache_[3] = std::min(
        std::max(fz_per_wheel - roll_force + pitch_force, -3000.0), 3000.0);
  }

  // 2. PID Callback: Main Trigger. Merge and Publish.
  void
  pid_callback(const mpc_car_control::msg::ActuatorCommand::SharedPtr msg) {
    auto cmd = *msg; // Copy PID commands (Steer, Throttle, Brake)
    cmd.header.stamp =
        this->now(); // Update timestamp for the published command

    // Check Active Suspension Toggle
    bool active_enabled =
        this->get_parameter("active_suspension_enabled").as_bool();

    if (active_enabled) {
      // Merge cached MPC Suspension Forces
      cmd.active_suspension_force = suspension_force_cache_;
    } else {
      // Passive Mode (Zero Active Force)
      cmd.active_suspension_force = {0.0, 0.0, 0.0, 0.0};
    }

    // Ensure Wheel Torque is 0 (Legacy Mode)
    cmd.wheel_torque = {0.0, 0.0, 0.0, 0.0};

    // Publish Final Mixed Command
    publisher_->publish(cmd);

    // Debug: Print Active Suspension Forces
    if (active_enabled) {
      RCLCPP_INFO_THROTTLE(
          this->get_logger(), *this->get_clock(), 500,
          "Active Susp [FL:%.0f FR:%.0f RL:%.0f RR:%.0f]",
          cmd.active_suspension_force[0], cmd.active_suspension_force[1],
          cmd.active_suspension_force[2], cmd.active_suspension_force[3]);
    }
  }

  rclcpp::Publisher<mpc_car_control::msg::ActuatorCommand>::SharedPtr
      publisher_;
  rclcpp::Subscription<mpc_car_control::msg::ControlCommandBody>::SharedPtr
      subscription_mpc_;
  rclcpp::Subscription<mpc_car_control::msg::ActuatorCommand>::SharedPtr
      subscription_pid_;
  rclcpp::Subscription<mpc_car_control::msg::VehicleState>::SharedPtr
      subscription_state_;

  mpc_car_control::msg::VehicleState current_state_;
  bool state_received_ = false;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ControlAllocatorNode>());
  rclcpp::shutdown();
  return 0;
}
