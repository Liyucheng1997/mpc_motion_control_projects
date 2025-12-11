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

  // Linear Tire Parameters (Match Vehicle Model)
  const double C_af_ = 60000.0; // Front Cornering Stiffness

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
      cmd.brake = std::min(std::max(-msg->fx / 4000.0, 0.0), 1.0);
    }
    
    // 2. Lateral (Linear Inverse) for Steering
    // msg->fy is COMMANDED LATERAL FORCE (N)
    if (state_received_) {
      double vx = std::max(current_state_.vx, 0.1); // Avoid div by zero
      double vy = current_state_.vy;
      double r = current_state_.yaw_rate;
      double lf = 1.015;

      // Fy_total -> Fy_per_wheel
      double Fy_per_wheel = msg->fy / 2.0;

      // Linear Inverse: Force = C * alpha  =>  alpha = Force / C
      double alpha = Fy_per_wheel / C_af_;

      // Calculate Steering Angle
      // delta = alpha + atan2(vy + lf*r, vx)
      if (vx > 1.0) {
        double kin_term = std::atan2(vy + lf * r, vx);
        cmd.steering_angle = alpha + kin_term;
        
        RCLCPP_INFO_THROTTLE(
            this->get_logger(), *this->get_clock(), 200,
            "Fy: %.1f, Alpha: %.3f, Kin: %.3f, Delta: %.3f",
            msg->fy, alpha, kin_term, cmd.steering_angle);
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

    // 3. Torque Vectoring (DYC)
    // Convert Mz (Nm) to Differential Torque
    // Mz = (FL + RL) * Tf/2 - (FR + RR) * Tf/2
    // DiffForce_per_side = Mz / TrackWidth
    // DiffTorque_per_wheel = DiffForce_per_side * Radius / 2 (Assuming distributed to Front/Rear)
    // Simplified: Output Differential Torque to wheels.
    
    double trace_width = 1.675; // Average track width
    double wheel_radius = 0.3;
    
    // Total diff force required at contacts
    double F_diff_total = msg->mz / (trace_width / 2.0); 
    // Positive Mz -> Left Turn -> Left wheels slower/brake, Right wheels faster/drive
    // Wait, Mz is moment around Z-up. Positive Mz turns LEFT (CCW).
    // To turn LEFT, we need Force on Right > Force on Left.
    // So Right Forward (+), Left Backward (-).
    
    // F_right - F_left = F_diff_total
    // F_right = F_diff_total / 2.0
    // F_left = -F_diff_total / 2.0
    
    double T_diff_per_wheel = (F_diff_total / 2.0) * wheel_radius / 2.0; // Distribute to 2 wheels per side
    
    // 1. Longitudinal (Throttle/Brake base) + DYC
    // Original longitudinal force
    double Fx_total = msg->fx;
    double T_drive_base = 0.0;
    double T_brake_base = 0.0;
    
    if (Fx_total >= 0) {
      T_drive_base = (Fx_total / 4.0) * wheel_radius;
      T_brake_base = 0.0;
    } else {
      T_drive_base = 0.0;
      T_brake_base = (-Fx_total / 4.0) * wheel_radius; 
    }
    
    // Apply Diff Torque
    // Left Wheels (0, 2): T_base - T_diff
    // Right Wheels (1, 3): T_base + T_diff
    
    double T_left = T_drive_base - T_brake_base - T_diff_per_wheel;
    double T_right = T_drive_base - T_brake_base + T_diff_per_wheel;
    
    // Convert back to Throttle/Brake commands (Normalized)
    // Max Torque approx: 500Nm drive / 1000Nm brake per wheel (from VehicleModel)
    
    // Helper to set throt/brake for a wheel
    // (This requires changing ActuatorCommand to support per-wheel throttle/brake,
    // OR just averaging for now? NO, DYC needs differential.)
    // Standard ActuatorCommand message definition usually has single throttle/brake.
    // Let's check ActuatorCommand definition.
    // If it only has single float throttle, we CANNOT do DYC fully.
    // WE MUST ASSUME active_suspension_force is the only per-wheel output in standard msg?
    // OR we hijack suspension for comparison? 
    // Wait, the USER said "Bottom subsystem... includes DYC torque subsystem".
    // Does 14DOF model support per-wheel torque?
    // Let's check vehicle_model_node code again.
    // It reads: T_drive = (throttle * 500)/4.0. It uses SINGLE throttle.
    
    // CRITICAL: We need to update VehicleModel to support independent wheel torques 
    // or at least update ActuatorCommand to have 4 throttles.
    // BUT checking `ActuatorCommand`:
    // It likely only has `float64 throttle`, `float64 brake`.
    
    // FOR NOW: We will implement DYC by trickery or we must stop and modify message.
    // However, the user asked to "Connect these 3 systems... to 14DOF".
    // Checking Vehicle Model:
    // lines 280: if (throttle > 0) T_drive = (throttle * 500) / 4.0;
    
    // CONCLUSION: The current ActuatorCommand DOES NOT support DYC.
    // I need to modify ActuatorCommand.msg to support `float64[4] wheel_torque`?
    // Or just modify VehicleModel directly to take `control_command_body`? 
    // No, separation of concerns.
    
    // Plan B: Since I cannot modify .msg files easily without triggering full rebuild quirks (and user didn't ask),
    // AND I am in a specific task, I should check if I can modify ActuatorCommand.msg.
    // Actually, I can just publish `active_suspension_force` (4 floats) and maybe hijack that?
    // No, that's hacky.
    
    // Realization: I missed that I need to update the message definition to support DYC.
    // BUT time is short.
    // Maybe I can repurpose `active_suspension_force` for testing? No.
    // Let's look at `ActuatorCommand.msg` content if possible.
    // I'll assume for this step I calculate it, but if I can't send it, I can't verify control.
    
    // WAIT! usage of `diff_torque` with single throttle is impossible.
    // I should stop and add `wheel_torques` to `ActuatorCommand.msg`?
    // That involves CMakeLists re-run.
    
    // Alternative: Use `active_suspension_force` is ALREADY array[4].
    // Maybe I can add a new field to message?
    // Let's assume for this specific simulation I can add a field or use a separate topic.
    
    // Actually, looking at `vehicle_model_node.cpp`, it subscribes to `ActuatorCommand`.
    // I can change `ActuatorCommand.msg`!
    // But re-compiling interfaces takes time.
    
    // Let's modify `ActuatorCommand.msg` to include `float64[4] wheel_torque`.
    
    // So for this specific tool call, I will comment out the DYC application to throttle 
    // and note that I need to update the message.
    
    // Actually, the user asked to plan "Modify plan... then execute".
    // I missed updating the message in the plan.
    // I will update the logic here to calculat it, but if I can't send it, I can't verify control.
    // For now, I will write the logic but keep the output as single throttle (average) ensuring compile success,
    // and then immediately fix the message.
    
    // Wait, if I write invalid code (distributing to non-existent fields), it won't compile.
    // So I will implement the CALCULATION but apply it to the single throttle as a placeholder
    // (average which is zero sum) -> effectively no DYC yet.
    // Then I will do a proper MSG update.
    
    // Better: Update ActuatorCommand.msg FIRST?
    // I am already in the middle of editing `control_allocator`.
    // I will write the code assuming `wheel_torque` exists, 
    // AND then I will immediately update the msg file and vehicle_model.
    
    // To make this step valid CPP, I will comment out the assignment to `cmd.wheel_torque`.
    
    // Debug DYC
    if (std::abs(msg->mz) > 1.0) {
        RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 500,
            "DYC Active: Mz=%.1f, T_base=%.1f, T_diff=%.1f -> L:%.1f, R:%.1f",
            msg->mz, T_drive_base - T_brake_base, T_diff_per_wheel, T_left, T_right);
    }

    // Safety Saturation (Prevent physics instability)
    // Legacy model max drive was 125Nm, max brake 250Nm.
    double T_max = 200.0; 
    T_left = std::min(std::max(T_left, -T_max), T_max);
    T_right = std::min(std::max(T_right, -T_max), T_max);

    // Populate new field ALWAYS
    cmd.wheel_torque[0] = T_left;
    cmd.wheel_torque[1] = T_right;
    cmd.wheel_torque[2] = T_left;
    cmd.wheel_torque[3] = T_right;

    // 4. Suspension
    double fz_per_wheel = msg->fz / 4.0;
    double roll_force = msg->mx / 2.0;
    double pitch_force = msg->my / 2.0;

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
