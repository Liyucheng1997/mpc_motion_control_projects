#include <chrono>
#include <cmath>
#include <memory>

#include "mpc_car_control/msg/actuator_command.hpp"
#include "mpc_car_control/msg/vehicle_state.hpp"
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

    timer_ = this->create_wall_timer(
        10ms, std::bind(&VehicleInterfaceNode::sim_loop, this));

    RCLCPP_INFO(this->get_logger(), "Vehicle Interface Node has been started.");

    // Init state
    state_.x = 0.0;
    state_.y = 0.0;
    state_.yaw = 0.0;
    state_.vx = 0.0;
  }

private:
  void
  cmd_callback(const mpc_car_control::msg::ActuatorCommand::SharedPtr msg) {
    last_cmd_ = *msg;
    cmd_received_ = true;
  }

  void sim_loop() {
    // Simple Kinematic Bicycle Model
    double dt = 0.01;
    double L = 2.5; // Wheelbase

    if (cmd_received_) {
      double acc = (last_cmd_.throttle * 5.0) - (last_cmd_.brake * 8.0);
      double delta = last_cmd_.steering_angle;

      state_.x += state_.vx * std::cos(state_.yaw) * dt;
      state_.y += state_.vx * std::sin(state_.yaw) * dt;
      state_.yaw += (state_.vx / L) * std::tan(delta) * dt;
      state_.vx += acc * dt;

      // Drag
      state_.vx -= 0.1 * state_.vx * dt;
    }

    publisher_->publish(state_);
  }

  rclcpp::Publisher<mpc_car_control::msg::VehicleState>::SharedPtr publisher_;
  rclcpp::Subscription<mpc_car_control::msg::ActuatorCommand>::SharedPtr
      subscription_;
  rclcpp::TimerBase::SharedPtr timer_;

  mpc_car_control::msg::VehicleState state_;
  mpc_car_control::msg::ActuatorCommand last_cmd_;
  bool cmd_received_ = false;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VehicleInterfaceNode>());
  rclcpp::shutdown();
  return 0;
}
