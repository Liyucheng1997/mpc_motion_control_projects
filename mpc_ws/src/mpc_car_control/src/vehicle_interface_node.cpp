#include <chrono>
#include <cmath>
#include <memory>

#include "mpc_car_control/msg/actuator_command.hpp"
#include "mpc_car_control/msg/vehicle_state.hpp"
#include "mpc_car_control/msg/wheel_ground_heights.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class VehicleInterfaceNode : public rclcpp::Node {
public:
  VehicleInterfaceNode() : Node("vehicle_interface_node") {
    publisher_ = this->create_publisher<mpc_car_control::msg::VehicleState>(
        "/vehicle_state", 10);

    subscription_ =
        this->create_subscription<mpc_car_control::msg::ActuatorCommand>(
            "/actuator_command", 10,
            std::bind(&VehicleInterfaceNode::cmd_callback, this, _1));

    subscription_wheels_ =
        this->create_subscription<mpc_car_control::msg::WheelGroundHeights>(
            "/wheel_ground_heights", 10,
            std::bind(&VehicleInterfaceNode::wheels_callback, this, _1));

    timer_ = this->create_wall_timer(
        10ms, std::bind(&VehicleInterfaceNode::sim_loop, this));

    RCLCPP_INFO(this->get_logger(), "Vehicle Interface Node has been started.");

    // Init state
    state_.x = 0.0;
    state_.y = 0.0;
    state_.z = 0.0;
    state_.yaw = 0.0;
    state_.pitch = 0.0;
    state_.roll = 0.0;
    state_.vx = 0.0;
    state_.vy = 0.0;
    state_.vz = 0.0;
    state_.roll_rate = 0.0;
    state_.pitch_rate = 0.0;
    state_.yaw_rate = 0.0;

    sim_time_ = this->now();
  }

private:
  mpc_car_control::msg::VehicleState state_;
  mpc_car_control::msg::ActuatorCommand last_cmd_;
  mpc_car_control::msg::WheelGroundHeights last_wheels_;
  bool cmd_received_ = false;
  rclcpp::Time sim_time_;

  rclcpp::Publisher<mpc_car_control::msg::VehicleState>::SharedPtr publisher_;
  rclcpp::Subscription<mpc_car_control::msg::ActuatorCommand>::SharedPtr
      subscription_;
  rclcpp::Subscription<mpc_car_control::msg::WheelGroundHeights>::SharedPtr
      subscription_wheels_;
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

  void sim_loop() {
    // Simple Kinematic Bicycle Model
    double dt = 0.01;
    sim_time_ += rclcpp::Duration::from_seconds(dt);
    double L = 2.5; // Wheelbase

    if (cmd_received_) {
      double acc = (last_cmd_.throttle * 5.0) - (last_cmd_.brake * 8.0);
      double delta = last_cmd_.steering_angle;

      // Kinematics
      state_.x += state_.vx * std::cos(state_.yaw) * dt;
      state_.y += state_.vx * std::sin(state_.yaw) * dt;
      state_.yaw += (state_.vx / L) * std::tan(delta) * dt;
      state_.vx += acc * dt;

      // Mock 6DOF dynamics (Placeholder for Carsim)
      // Just integrate some dummy rates based on suspension forces if needed
      // For now, we keep them close to 0 or simple response
      state_.z = 0.0; // Assume flat ground + suspension logic
      state_.roll = 0.0;
      state_.pitch = 0.0;

      // Drag
      state_.vx -= 0.1 * state_.vx * dt;
    }

    state_.header.stamp = sim_time_;
    state_.header.frame_id = "map";
    publisher_->publish(state_);
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VehicleInterfaceNode>());
  rclcpp::shutdown();
  return 0;
}
