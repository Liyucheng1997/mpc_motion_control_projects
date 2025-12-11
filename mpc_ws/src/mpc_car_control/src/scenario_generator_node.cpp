#include <chrono>
#include <cmath>
#include <memory>
#include <vector>

#include "geometry_msgs/msg/point.hpp"
#include "mpc_car_control/msg/reference_trajectory.hpp"
#include "mpc_car_control/msg/vehicle_state.hpp"
#include "mpc_car_control/msg/wheel_ground_heights.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class ScenarioGeneratorNode : public rclcpp::Node {
public:
  ScenarioGeneratorNode() : Node("scenario_generator_node") {
    this->declare_parameter("scenario_id", 1);

    publisher_ =
        this->create_publisher<mpc_car_control::msg::ReferenceTrajectory>(
            "/reference_trajectory", 10);

    publisher_wheels_ =
        this->create_publisher<mpc_car_control::msg::WheelGroundHeights>(
            "/wheel_ground_heights", 10);

    publisher_markers_ =
        this->create_publisher<visualization_msgs::msg::MarkerArray>(
            "/visualization_marker_array", 10);

    subscription_state_ =
        this->create_subscription<mpc_car_control::msg::VehicleState>(
            "/vehicle_state", 10,
            std::bind(&ScenarioGeneratorNode::state_callback, this, _1));

    timer_ = this->create_wall_timer(
        100ms, std::bind(&ScenarioGeneratorNode::timer_callback, this));
    RCLCPP_INFO(this->get_logger(),
                "Scenario Generator Node has been started.");
  }

private:
  void state_callback(const mpc_car_control::msg::VehicleState::SharedPtr msg) {
    current_state_ = *msg;
  }

  double get_bump_height(double x, double /*y*/) {
    // Simple bump at x = 20 to 22
    if (x > 20.0 && x < 22.0) {
      return 0.1 * std::sin((x - 20.0) * M_PI / 2.0); // 10cm bump
    }
    return 0.0;
  }

  void timer_callback() {
    int scenario_id = this->get_parameter("scenario_id").as_int();

    auto traj_msg = mpc_car_control::msg::ReferenceTrajectory();
    traj_msg.header.stamp = this->now();
    traj_msg.header.frame_id = "map";

    auto wheels_msg = mpc_car_control::msg::WheelGroundHeights();
    wheels_msg.header.stamp = this->now();
    wheels_msg.wheel_ground_heights = {0.0, 0.0, 0.0, 0.0}; // Default flat

    visualization_msgs::msg::MarkerArray marker_array;

    double step = 0.5;
    double target_velocity = 5.0; // Reduced from 8.0 for stability testing

    // --- Scenario Logic ---
    if (scenario_id == 1) {
      // 1. Straight 100m
      double total_length = 100.0;
      for (double s = 0.0; s <= total_length; s += step) {
        geometry_msgs::msg::Point p;
        p.x = s;
        p.y = 0.0;
        p.z = 0.0;
        traj_msg.points.push_back(p);
        traj_msg.yaw_profile.push_back(0.0);

        double v = target_velocity;
        if (s > total_length - 20.0)
          v = target_velocity * (total_length - s) / 20.0;
        traj_msg.velocity_profile.push_back(std::max(0.0, v));
      }
    } else if (scenario_id == 2) {
      // 2. Straight + Speed Bump at 50m
      double total_length = 100.0;
      double bump_x = 50.0;

      for (double s = 0.0; s <= total_length; s += step) {
        geometry_msgs::msg::Point p;
        p.x = s;
        p.y = 0.0;
        p.z = 0.0;
        traj_msg.points.push_back(p);
        traj_msg.yaw_profile.push_back(0.0);

        double v = target_velocity;
        if (s > total_length - 20.0)
          v = target_velocity * (total_length - s) / 20.0;
        traj_msg.velocity_profile.push_back(std::max(0.0, v));
      }

      // Bump Logic
      double car_x = current_state_.x;
      if (car_x > bump_x - 1.0 && car_x < bump_x + 1.0) {
        double h =
            0.3 * std::cos((car_x - bump_x) * M_PI / 2.0); // Massive 0.5m Bump
        wheels_msg.wheel_ground_heights = {h, h, h, h};
      }

      // Visualize Bump
      visualization_msgs::msg::Marker bump_marker;
      bump_marker.header.frame_id = "map";
      bump_marker.header.stamp = this->now();
      bump_marker.ns = "bumps";
      bump_marker.id = 0;
      bump_marker.type = visualization_msgs::msg::Marker::CUBE;
      bump_marker.action = visualization_msgs::msg::Marker::ADD;
      bump_marker.pose.position.x = bump_x;
      bump_marker.pose.position.y = 0.0;
      bump_marker.pose.position.z = 0.25; // Center at half height
      bump_marker.scale.x = 2.0;
      bump_marker.scale.y = 4.0;
      bump_marker.scale.z = 0.5; // Height
      bump_marker.color.r = 1.0;
      bump_marker.color.a = 0.8;
      marker_array.markers.push_back(bump_marker);
    } else if (scenario_id == 3) {
      // 3. Complex Turn WITHOUT Bump (Straight -> Turn -> Straight)
      double straight_1 = 50.0;
      double turn_radius = 20.0;
      double turn_angle = M_PI / 2.0;
      double turn_len = turn_radius * turn_angle;
      double straight_2 = 50.0;
      double total_len = straight_1 + turn_len + straight_2;

      for (double s = 0.0; s <= total_len; s += step) {
        geometry_msgs::msg::Point p;
        double yaw = 0.0;

        if (s < straight_1) {
          p.x = s;
          p.y = 0.0;
          yaw = 0.0;
        } else if (s < straight_1 + turn_len) {
          double s_turn = s - straight_1;
          double theta = s_turn / turn_radius;
          // Right Turn
          p.x = straight_1 + turn_radius * std::sin(theta);
          p.y = -turn_radius * (1.0 - std::cos(theta));
          yaw = -theta;
        } else {
          double s2 = s - (straight_1 + turn_len);
          p.x = straight_1 + turn_radius;
          p.y = -turn_radius - s2;
          yaw = -M_PI_2;
        }
        p.z = 0.0;
        traj_msg.points.push_back(p);
        traj_msg.yaw_profile.push_back(yaw);

        double v = target_velocity;
        if (s > total_len - 20.0)
          v = target_velocity * (total_len - s) / 20.0;
        traj_msg.velocity_profile.push_back(std::max(0.0, v));
      }
    } else if (scenario_id == 4) {
      // 4. Straight -> Turn (w/ Bump) -> Straight
      double straight_1 = 50.0;
      double turn_radius = 20.0;
      double turn_angle = M_PI / 2.0;
      double turn_len = turn_radius * turn_angle;
      double straight_2 = 50.0;
      double total_len = straight_1 + turn_len + straight_2;

      for (double s = 0.0; s <= total_len; s += step) {
        geometry_msgs::msg::Point p;
        double yaw = 0.0;

        if (s < straight_1) {
          p.x = s;
          p.y = 0.0;
          yaw = 0.0;
        } else if (s < straight_1 + turn_len) {
          double s_turn = s - straight_1;
          double theta = s_turn / turn_radius;
          // Turn Left: x = s1 + R*sin(theta), y = R*(1-cos(theta))
          // Turn Right (as requested before): x = s1 + R*sin(theta), y =
          // -R*(1-cos(theta)) Let's do Right Turn to match previous
          p.x = straight_1 + turn_radius * std::sin(theta);
          p.y = -turn_radius * (1.0 - std::cos(theta));
          yaw = -theta;
        } else {
          double s2 = s - (straight_1 + turn_len);
          p.x = straight_1 + turn_radius + s2 * 0.0; // Heading South (-Y)
          // End of turn: x = s1 + R, y = -R. Heading -PI/2.
          // Actually: x = s1 + R*sin(PI/2) = s1+R. y = -R*(1-cos(PI/2)) = -R.
          // Heading is -PI/2.
          // So delta x = 0, delta y = -s2.
          p.x = straight_1 + turn_radius;
          p.y = -turn_radius - s2;
          yaw = -M_PI_2;
        }
        p.z = 0.0;
        traj_msg.points.push_back(p);
        traj_msg.yaw_profile.push_back(yaw);

        double v = target_velocity;
        if (s > total_len - 20.0)
          v = target_velocity * (total_len - s) / 20.0;
        traj_msg.velocity_profile.push_back(std::max(0.0, v));
      }

      // Bump Logic (Inside Turn)
      // Bump at 45 degrees into the turn
      double bump_angle = M_PI / 4.0;
      // Check if car is near bump
      // Calculate car 's' (approximate)
      // Simple check: distance to bump center
      double bump_center_x = straight_1 + turn_radius * std::sin(bump_angle);
      double bump_center_y = -turn_radius * (1.0 - std::cos(bump_angle));

      double dx = current_state_.x - bump_center_x;
      double dy = current_state_.y - bump_center_y;
      double dist_to_bump = std::sqrt(dx * dx + dy * dy);

      if (dist_to_bump < 1.0) {
        double h = 0.1 * std::cos(dist_to_bump * M_PI / 2.0);
        wheels_msg.wheel_ground_heights = {h, h, h, h};
      }

      // Visualize Bump
      visualization_msgs::msg::Marker bump_marker;
      bump_marker.header.frame_id = "map";
      bump_marker.header.stamp = this->now();
      bump_marker.ns = "bumps";
      bump_marker.id = 1;
      bump_marker.type = visualization_msgs::msg::Marker::CUBE;
      bump_marker.action = visualization_msgs::msg::Marker::ADD;
      bump_marker.pose.position.x = bump_center_x;
      bump_marker.pose.position.y = bump_center_y;
      bump_marker.pose.position.z = 0.05;
      // Rotate to match turn tangent (-45 deg)
      tf2::Quaternion q;
      q.setRPY(0, 0, -bump_angle);
      bump_marker.pose.orientation.x = q.x();
      bump_marker.pose.orientation.y = q.y();
      bump_marker.pose.orientation.z = q.z();
      bump_marker.pose.orientation.w = q.w();

      bump_marker.scale.x = 2.0;
      bump_marker.scale.y = 4.0;
      bump_marker.scale.z = 0.1;
      bump_marker.color.r = 1.0;
      bump_marker.color.a = 0.8;
      marker_array.markers.push_back(bump_marker);
    }

    publisher_->publish(traj_msg);
    publisher_wheels_->publish(wheels_msg);
    publisher_markers_->publish(marker_array);
  }

  rclcpp::Publisher<mpc_car_control::msg::ReferenceTrajectory>::SharedPtr
      publisher_;
  rclcpp::Publisher<mpc_car_control::msg::WheelGroundHeights>::SharedPtr
      publisher_wheels_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr
      publisher_markers_;
  rclcpp::Subscription<mpc_car_control::msg::VehicleState>::SharedPtr
      subscription_state_;
  rclcpp::TimerBase::SharedPtr timer_;
  mpc_car_control::msg::VehicleState current_state_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ScenarioGeneratorNode>());
  rclcpp::shutdown();
  return 0;
}
