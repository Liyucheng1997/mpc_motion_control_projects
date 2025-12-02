#include <chrono>
#include <cmath>
#include <memory>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "mpc_car_control/msg/reference_trajectory.hpp"
#include "geometry_msgs/msg/point.hpp"

using namespace std::chrono_literals;

class ScenarioGeneratorNode : public rclcpp::Node {
public:
  ScenarioGeneratorNode() : Node("scenario_generator_node") {
    publisher_ = this->create_publisher<mpc_car_control::msg::ReferenceTrajectory>(
        "/reference_trajectory", 10);
    timer_ = this->create_wall_timer(
        100ms, std::bind(&ScenarioGeneratorNode::timer_callback, this));
    RCLCPP_INFO(this->get_logger(), "Scenario Generator Node has been started.");
  }

private:
  void timer_callback() {
    auto message = mpc_car_control::msg::ReferenceTrajectory();
    message.header.stamp = this->now();
    message.header.frame_id = "map";

    // Generate a simple sinusoidal path
    // y = A * sin(k * x)
    double amplitude = 5.0;
    double frequency = 0.1;
    double length = 100.0;
    double step = 1.0;
    double target_velocity = 10.0; // m/s

    for (double x = 0.0; x < length; x += step) {
      geometry_msgs::msg::Point p;
      p.x = x;
      p.y = amplitude * std::sin(frequency * x);
      p.z = 0.0;
      message.points.push_back(p);

      message.velocity_profile.push_back(target_velocity);
      
      // Approximate yaw
      double dx = step;
      double dy = amplitude * std::sin(frequency * (x + step)) - p.y;
      double yaw = std::atan2(dy, dx);
      message.yaw_profile.push_back(yaw);
    }

    publisher_->publish(message);
  }

  rclcpp::Publisher<mpc_car_control::msg::ReferenceTrajectory>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ScenarioGeneratorNode>());
  rclcpp::shutdown();
  return 0;
}
