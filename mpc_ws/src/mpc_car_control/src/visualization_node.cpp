#include <chrono>
#include <cmath>
#include <iomanip> // Added for std::setprecision
#include <memory>
#include <string>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "mpc_car_control/msg/reference_trajectory.hpp"
#include "mpc_car_control/msg/vehicle_state.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class VisualizationNode : public rclcpp::Node {
public:
  VisualizationNode() : Node("visualization_node") {
    subscription_ =
        this->create_subscription<mpc_car_control::msg::VehicleState>(
            "/vehicle_state", 10,
            std::bind(&VisualizationNode::state_callback, this, _1));

    subscription_traj_ =
        this->create_subscription<mpc_car_control::msg::ReferenceTrajectory>(
            "/reference_trajectory", 10,
            std::bind(&VisualizationNode::traj_callback, this, _1));

    // ... (existing includes)

    marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>(
        "/visualization_marker_array", 10);

    pub_error_ =
        this->create_publisher<std_msgs::msg::Float64>("/control_error", 10);

    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

    // Initialize actual path marker
    actual_path_marker_.header.frame_id = "map";
    actual_path_marker_.ns = "actual_path";
    actual_path_marker_.id = 3;
    actual_path_marker_.type = visualization_msgs::msg::Marker::LINE_STRIP;
    actual_path_marker_.action = visualization_msgs::msg::Marker::ADD;
    actual_path_marker_.scale.x = 0.2;
    actual_path_marker_.color.r = 1.0f; // Red for actual path
    actual_path_marker_.color.g = 0.0f;
    actual_path_marker_.color.b = 0.0f;
    actual_path_marker_.color.a = 1.0f;
    actual_path_marker_.pose.orientation.w = 1.0;

    RCLCPP_INFO(this->get_logger(), "Visualization Node started.");
  }

private:
  void state_callback(const mpc_car_control::msg::VehicleState::SharedPtr msg) {
    // 1. Broadcast TF (map -> base_link)
    geometry_msgs::msg::TransformStamped t;
    t.header.stamp = msg->header.stamp;
    t.header.frame_id = "map";
    t.child_frame_id = "base_link";

    t.transform.translation.x = msg->x;
    t.transform.translation.y = msg->y;
    t.transform.translation.z = msg->z;

    tf2::Quaternion q;
    q.setRPY(msg->roll, msg->pitch, msg->yaw);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    tf_broadcaster_->sendTransform(t);

    // 2. Update Actual Path (with Deadband)
    geometry_msgs::msg::Point p;
    p.x = msg->x;
    p.y = msg->y;
    p.z = msg->z;

    bool add_point = false;
    if (actual_path_marker_.points.empty()) {
      add_point = true;
    } else {
      const auto &last_p = actual_path_marker_.points.back();
      double dist =
          std::sqrt(std::pow(p.x - last_p.x, 2) + std::pow(p.y - last_p.y, 2));
      if (dist > 0.1) { // 10cm deadband
        add_point = true;
      }
    }

    if (add_point) {
      actual_path_marker_.points.push_back(p);
      if (actual_path_marker_.points.size() > 10000) {
        actual_path_marker_.points.erase(actual_path_marker_.points.begin());
      }
    }

    // 3. Markers
    visualization_msgs::msg::MarkerArray marker_array;

    // Actual Path Marker
    actual_path_marker_.header.stamp = msg->header.stamp;
    marker_array.markers.push_back(actual_path_marker_);

    // --- Composite Car Model ---
    // Common Header
    std_msgs::msg::Header car_header;
    car_header.frame_id = "base_link";
    car_header.stamp = msg->header.stamp;

    // 1. Chassis (Lower Body)
    visualization_msgs::msg::Marker chassis;
    chassis.header = car_header;
    chassis.ns = "vehicle_body";
    chassis.id = 0;
    chassis.type = visualization_msgs::msg::Marker::CUBE;
    chassis.action = visualization_msgs::msg::Marker::ADD;
    chassis.pose.position.x = 0.0;
    chassis.pose.position.y = 0.0;
    chassis.pose.position.z = -0.58; // Lowered by 0.88m
    chassis.pose.orientation.w = 1.0;
    chassis.scale.x = 4.5;
    chassis.scale.y = 1.8;
    chassis.scale.z = 0.6;
    chassis.color.r = 0.0;
    chassis.color.g = 0.3;
    chassis.color.b = 0.8;
    chassis.color.a = 1.0; // Dark Blue
    chassis.lifetime = rclcpp::Duration(0, 0);
    marker_array.markers.push_back(chassis);

    // 2. Cabin (Upper Body)
    visualization_msgs::msg::Marker cabin;
    cabin.header = car_header;
    cabin.ns = "vehicle_body";
    cabin.id = 10;
    cabin.type = visualization_msgs::msg::Marker::CUBE;
    cabin.action = visualization_msgs::msg::Marker::ADD;
    cabin.pose.position.x = -0.2;
    cabin.pose.position.y = 0.0;
    cabin.pose.position.z = -0.08; // Lowered by 0.88m
    cabin.pose.orientation.w = 1.0;
    cabin.scale.x = 2.5;
    cabin.scale.y = 1.6;
    cabin.scale.z = 0.6;
    cabin.color.r = 0.2;
    cabin.color.g = 0.2;
    cabin.color.b = 0.2;
    cabin.color.a = 0.8; // Dark Grey/Glass
    cabin.lifetime = rclcpp::Duration(0, 0);
    marker_array.markers.push_back(cabin);

    // 3. Wheels
    double wheel_x = 1.4;
    double wheel_y = 0.9;
    double wheel_z = -0.58;    // Lowered by 0.88m
    double wheel_radius = 0.3; // Corrected radius
    double wheel_width = 0.3;

    for (int i = 0; i < 4; ++i) {
      visualization_msgs::msg::Marker wheel;
      wheel.header = car_header;
      wheel.ns = "vehicle_wheels";
      wheel.id = 20 + i;
      wheel.type = visualization_msgs::msg::Marker::CYLINDER;
      wheel.action = visualization_msgs::msg::Marker::ADD;

      // FL, FR, RL, RR
      double wx = (i < 2) ? wheel_x : -wheel_x;
      double wy = (i % 2 == 0) ? wheel_y : -wheel_y;

      wheel.pose.position.x = wx;
      wheel.pose.position.y = wy;
      wheel.pose.position.z = wheel_z;

      // Rotate cylinder to be horizontal (along Y axis)
      tf2::Quaternion q;
      q.setRPY(M_PI_2, 0, 0);
      wheel.pose.orientation.x = q.x();
      wheel.pose.orientation.y = q.y();
      wheel.pose.orientation.z = q.z();
      wheel.pose.orientation.w = q.w();

      wheel.scale.x = wheel_radius * 2.0;
      wheel.scale.y = wheel_radius * 2.0;
      wheel.scale.z = wheel_width;

      wheel.color.r = 0.1;
      wheel.color.g = 0.1;
      wheel.color.b = 0.1;
      wheel.color.a = 1.0; // Black
      wheel.lifetime = rclcpp::Duration(0, 0);
      marker_array.markers.push_back(wheel);
    }

    // 4. Calculate Error
    double min_dist_sq = std::numeric_limits<double>::max();
    size_t closest_point_idx = 0;
    bool has_ref = !ref_traj_.points.empty();

    if (has_ref) {
      for (size_t i = 0; i < ref_traj_.points.size(); ++i) {
        double dx = msg->x - ref_traj_.points[i].x;
        double dy = msg->y - ref_traj_.points[i].y;
        double dist_sq = dx * dx + dy * dy;
        if (dist_sq < min_dist_sq) {
          min_dist_sq = dist_sq;
          closest_point_idx = i;
        }
      }
    } else {
      min_dist_sq = 0.0;
    }

    double error = std::sqrt(min_dist_sq);

    // 5. Publish Error
    std_msgs::msg::Float64 error_msg;
    error_msg.data = error;
    pub_error_->publish(error_msg);

    // 6. Error Graph Marker
    if (true) {
      if (error_graph_marker_.points.empty()) {
        error_graph_marker_.header.frame_id = "map";
        error_graph_marker_.ns = "error_graph";
        error_graph_marker_.id = 7;
        error_graph_marker_.type = visualization_msgs::msg::Marker::LINE_STRIP;
        error_graph_marker_.action = visualization_msgs::msg::Marker::ADD;
        error_graph_marker_.scale.x = 0.1;
        error_graph_marker_.color.r = 1.0f; // Red
        error_graph_marker_.color.g = 0.0f;
        error_graph_marker_.color.b = 1.0f; // Purple/Magenta
        error_graph_marker_.color.a = 1.0f;
        error_graph_marker_.pose.orientation.w = 1.0;
      }

      if (has_ref) {
        geometry_msgs::msg::Point p_err;
        p_err.x = msg->x;
        p_err.y = msg->y;
        // Visualize error magnitude as height above the car
        // Scale factor 5.0 makes 10cm error look like 0.5m height
        p_err.z = msg->z + error * 5.0;

        error_graph_marker_.points.push_back(p_err);
        if (error_graph_marker_.points.size() > 5000)
          error_graph_marker_.points.erase(error_graph_marker_.points.begin());

        error_graph_marker_.header.stamp = msg->header.stamp;
        marker_array.markers.push_back(error_graph_marker_);
      }
    }

    // 7. Text Overlay
    visualization_msgs::msg::Marker text_marker;
    text_marker.header.frame_id = "base_link";
    text_marker.header.stamp = msg->header.stamp;
    text_marker.ns = "info_text";
    text_marker.id = 1;
    text_marker.type = visualization_msgs::msg::Marker::TEXT_VIEW_FACING;
    text_marker.action = visualization_msgs::msg::Marker::ADD;
    text_marker.pose.position.z = 0.62; // Lowered by 0.88m
    text_marker.scale.z = 0.5;
    text_marker.color.r = 1.0f;
    text_marker.color.g = 1.0f;
    text_marker.color.b = 1.0f;
    text_marker.color.a = 1.0f;
    text_marker.lifetime = rclcpp::Duration(0, 0);

    double speed = std::sqrt(msg->vx * msg->vx + msg->vy * msg->vy);
    std::stringstream ss;
    ss << "Speed: " << std::fixed << std::setprecision(1) << speed << " m/s\n"
       << "Error: " << std::setprecision(3) << error << " m\n"
       << "Z: " << std::setprecision(2) << msg->z << " m";
    text_marker.text = ss.str();
    marker_array.markers.push_back(text_marker);

    // 8. Error Vector
    if (false) {
      visualization_msgs::msg::Marker error_vector;
      error_vector.header.frame_id = "map";
      error_vector.header.stamp = msg->header.stamp;
      error_vector.ns = "error_vector";
      error_vector.id = 8;
      error_vector.type = visualization_msgs::msg::Marker::LINE_LIST;
      error_vector.action = visualization_msgs::msg::Marker::ADD;
      error_vector.scale.x = 0.05;
      error_vector.color.r = 1.0f;
      error_vector.color.g = 0.0f;
      error_vector.color.b = 1.0f;
      error_vector.color.a = 1.0f;

      geometry_msgs::msg::Point p_car;
      p_car.x = msg->x;
      p_car.y = msg->y;
      p_car.z = msg->z;

      geometry_msgs::msg::Point p_ref = ref_traj_.points[closest_point_idx];
      p_ref.z = msg->z;

      error_vector.points.push_back(p_car);
      error_vector.points.push_back(p_ref);
      marker_array.markers.push_back(error_vector);
    }

    marker_pub_->publish(marker_array);
  }

  void traj_callback(
      const mpc_car_control::msg::ReferenceTrajectory::SharedPtr msg) {
    ref_traj_ = *msg; // Store for error calculation
    error_graph_marker_.points
        .clear(); // Clear error graph when new trajectory is received

    visualization_msgs::msg::MarkerArray marker_array;

    // 1. Reference Trajectory (Green Line)
    visualization_msgs::msg::Marker line_marker;
    line_marker.header.frame_id = "map";
    line_marker.header.stamp = this->now();
    line_marker.ns = "reference_trajectory";
    line_marker.id = 2;
    line_marker.type = visualization_msgs::msg::Marker::LINE_STRIP;
    line_marker.action = visualization_msgs::msg::Marker::ADD;
    line_marker.scale.x = 0.2;
    line_marker.color.r = 0.0f;
    line_marker.color.g = 1.0f;
    line_marker.color.b = 0.0f;
    line_marker.color.a = 1.0f;
    line_marker.pose.orientation.w = 1.0;

    for (const auto &p : msg->points) {
      line_marker.points.push_back(p);
    }
    marker_array.markers.push_back(line_marker);

    // 2. Road Boundaries
    // 2. Road Boundaries
    double lane_width = 3.5; // Reduced from 4.0m to 3.5m

    visualization_msgs::msg::Marker right_edge, left_edge, center_line;
    right_edge.header = line_marker.header;
    right_edge.ns = "road_boundaries";
    right_edge.id = 4;
    right_edge.type = visualization_msgs::msg::Marker::LINE_STRIP;
    right_edge.action = visualization_msgs::msg::Marker::ADD;
    right_edge.scale.x = 0.2;
    right_edge.color.r = 1.0f;
    right_edge.color.g = 1.0f;
    right_edge.color.b = 1.0f;
    right_edge.color.a = 1.0f;
    right_edge.pose.orientation.w = 1.0;
    right_edge.lifetime = rclcpp::Duration(0, 0);

    left_edge = right_edge;
    left_edge.id = 5;
    left_edge.lifetime = rclcpp::Duration(0, 0);

    center_line = right_edge;
    center_line.id = 6;
    center_line.type = visualization_msgs::msg::Marker::LINE_LIST; // Dashed
    center_line.scale.x = 0.15;
    center_line.lifetime = rclcpp::Duration(0, 0);

    for (size_t i = 0; i < msg->points.size() - 1; ++i) {
      const auto &p1 = msg->points[i];
      const auto &p2 = msg->points[i + 1];

      double dx = p2.x - p1.x;
      double dy = p2.y - p1.y;
      double len = std::sqrt(dx * dx + dy * dy);
      if (len < 0.001)
        continue;

      // Normal vector (-dy, dx) points LEFT
      double nx = -dy / len;
      double ny = dx / len;

      // Right Edge (Ref - Normal * W/2)
      geometry_msgs::msg::Point pr;
      pr.x = p1.x - nx * (lane_width / 2.0);
      pr.y = p1.y - ny * (lane_width / 2.0);
      pr.z = p1.z;
      right_edge.points.push_back(pr);

      // Center Line (Ref + Normal * W/2)
      geometry_msgs::msg::Point pc;
      pc.x = p1.x + nx * (lane_width / 2.0);
      pc.y = p1.y + ny * (lane_width / 2.0);
      pc.z = p1.z;

      if (i % 4 < 2) {
        center_line.points.push_back(pc);
        geometry_msgs::msg::Point pc2;
        pc2.x = p2.x + nx * (lane_width / 2.0);
        pc2.y = p2.y + ny * (lane_width / 2.0);
        pc2.z = p2.z;
        center_line.points.push_back(pc2);
      }

      // Left Edge (Ref + Normal * 1.5W)
      geometry_msgs::msg::Point pl;
      pl.x = p1.x + nx * (lane_width * 1.5);
      pl.y = p1.y + ny * (lane_width * 1.5);
      pl.z = p1.z;
      left_edge.points.push_back(pl);
    }

    marker_array.markers.push_back(right_edge);
    marker_array.markers.push_back(center_line);
    marker_array.markers.push_back(left_edge);

    marker_pub_->publish(marker_array);
  }

  rclcpp::Subscription<mpc_car_control::msg::VehicleState>::SharedPtr
      subscription_;
  rclcpp::Subscription<mpc_car_control::msg::ReferenceTrajectory>::SharedPtr
      subscription_traj_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr
      marker_pub_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr pub_error_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  visualization_msgs::msg::Marker actual_path_marker_;
  mpc_car_control::msg::ReferenceTrajectory ref_traj_;
  visualization_msgs::msg::Marker
      error_graph_marker_; // Visualizes error as Z-height
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VisualizationNode>());
  rclcpp::shutdown();
  return 0;
}
