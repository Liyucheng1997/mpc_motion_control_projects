#include <cmath>
#include <memory>

#include "mpc_car_control/msg/actuator_command.hpp"
#include "mpc_car_control/msg/control_command_body.hpp"
#include "rclcpp/rclcpp.hpp"

using std::placeholders::_1;

class ControlAllocatorNode : public rclcpp::Node {
public:
  ControlAllocatorNode() : Node("control_allocator_node") {
    publisher_ = this->create_publisher<mpc_car_control::msg::ActuatorCommand>(
        "/actuator_command", 10);

    subscription_ =
        this->create_subscription<mpc_car_control::msg::ControlCommandBody>(
            "/control_command_body", 10,
            std::bind(&ControlAllocatorNode::topic_callback, this, _1));

    RCLCPP_INFO(this->get_logger(), "Control Allocator Node has been started.");
  }

private:
  void topic_callback(
      const mpc_car_control::msg::ControlCommandBody::SharedPtr msg) {
    auto cmd = mpc_car_control::msg::ActuatorCommand();
    cmd.header.stamp = this->now();

    // Simple Allocation Map
    // Fx -> Throttle/Brake
    // Fy + Mz -> Steering

    // Longitudinal
    if (msg->fx >= 0) {
      cmd.throttle =
          std::min(std::max(msg->fx / 1000.0, 0.0), 1.0); // Normalize
      cmd.brake = 0.0;
    } else {
      cmd.throttle = 0.0;
      cmd.brake = std::min(std::max(-msg->fx / 2000.0, 0.0), 1.0);
    }

    // Lateral / Yaw
    // Assuming linear tire model for small angles: Fy = C_alpha * alpha
    // Steering ~ Fy / CorneringStiffness
    // Also add yaw moment contribution

    double steering_from_fy = msg->fy / 1000.0; // Dummy stiffness
    double steering_from_mz = msg->mz / 2000.0;

    cmd.steering_angle = steering_from_fy + steering_from_mz;

    // Saturation
    cmd.steering_angle =
        std::min(std::max(cmd.steering_angle, -0.5), 0.5); // +/- 0.5 rad

    // Suspension Force Allocation
    // Simple logic:
    // Fz -> Evenly distributed
    // Mx (Roll) -> Left +, Right - (To roll right/lift left)
    // My (Pitch) -> Front +, Rear - (To pitch up/lift front)

    double fz_per_wheel = msg->fz / 4.0;
    // Assuming generic track width and wheelbase scaling for moments
    // For real car, divide by track_width and wheelbase
    double roll_force = msg->mx / 2.0;
    double pitch_force = msg->my / 2.0;

    // Indices: 0:FL, 1:FR, 2:RL, 3:RR
    cmd.active_suspension_force[0] =
        fz_per_wheel + roll_force + pitch_force; // FL
    cmd.active_suspension_force[1] =
        fz_per_wheel - roll_force + pitch_force; // FR
    cmd.active_suspension_force[2] =
        fz_per_wheel + roll_force - pitch_force; // RL
    cmd.active_suspension_force[3] =
        fz_per_wheel - roll_force - pitch_force; // RR

    publisher_->publish(cmd);
  }

  rclcpp::Publisher<mpc_car_control::msg::ActuatorCommand>::SharedPtr
      publisher_;
  rclcpp::Subscription<mpc_car_control::msg::ControlCommandBody>::SharedPtr
      subscription_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ControlAllocatorNode>());
  rclcpp::shutdown();
  return 0;
}
