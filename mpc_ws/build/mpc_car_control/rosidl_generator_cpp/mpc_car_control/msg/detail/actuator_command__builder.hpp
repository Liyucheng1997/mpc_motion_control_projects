// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mpc_car_control:msg/ActuatorCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mpc_car_control/msg/actuator_command.hpp"


#ifndef MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__BUILDER_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "mpc_car_control/msg/detail/actuator_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace mpc_car_control
{

namespace msg
{

namespace builder
{

class Init_ActuatorCommand_wheel_torque
{
public:
  explicit Init_ActuatorCommand_wheel_torque(::mpc_car_control::msg::ActuatorCommand & msg)
  : msg_(msg)
  {}
  ::mpc_car_control::msg::ActuatorCommand wheel_torque(::mpc_car_control::msg::ActuatorCommand::_wheel_torque_type arg)
  {
    msg_.wheel_torque = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mpc_car_control::msg::ActuatorCommand msg_;
};

class Init_ActuatorCommand_active_suspension_force
{
public:
  explicit Init_ActuatorCommand_active_suspension_force(::mpc_car_control::msg::ActuatorCommand & msg)
  : msg_(msg)
  {}
  Init_ActuatorCommand_wheel_torque active_suspension_force(::mpc_car_control::msg::ActuatorCommand::_active_suspension_force_type arg)
  {
    msg_.active_suspension_force = std::move(arg);
    return Init_ActuatorCommand_wheel_torque(msg_);
  }

private:
  ::mpc_car_control::msg::ActuatorCommand msg_;
};

class Init_ActuatorCommand_brake
{
public:
  explicit Init_ActuatorCommand_brake(::mpc_car_control::msg::ActuatorCommand & msg)
  : msg_(msg)
  {}
  Init_ActuatorCommand_active_suspension_force brake(::mpc_car_control::msg::ActuatorCommand::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return Init_ActuatorCommand_active_suspension_force(msg_);
  }

private:
  ::mpc_car_control::msg::ActuatorCommand msg_;
};

class Init_ActuatorCommand_throttle
{
public:
  explicit Init_ActuatorCommand_throttle(::mpc_car_control::msg::ActuatorCommand & msg)
  : msg_(msg)
  {}
  Init_ActuatorCommand_brake throttle(::mpc_car_control::msg::ActuatorCommand::_throttle_type arg)
  {
    msg_.throttle = std::move(arg);
    return Init_ActuatorCommand_brake(msg_);
  }

private:
  ::mpc_car_control::msg::ActuatorCommand msg_;
};

class Init_ActuatorCommand_steering_angle
{
public:
  explicit Init_ActuatorCommand_steering_angle(::mpc_car_control::msg::ActuatorCommand & msg)
  : msg_(msg)
  {}
  Init_ActuatorCommand_throttle steering_angle(::mpc_car_control::msg::ActuatorCommand::_steering_angle_type arg)
  {
    msg_.steering_angle = std::move(arg);
    return Init_ActuatorCommand_throttle(msg_);
  }

private:
  ::mpc_car_control::msg::ActuatorCommand msg_;
};

class Init_ActuatorCommand_header
{
public:
  Init_ActuatorCommand_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ActuatorCommand_steering_angle header(::mpc_car_control::msg::ActuatorCommand::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ActuatorCommand_steering_angle(msg_);
  }

private:
  ::mpc_car_control::msg::ActuatorCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mpc_car_control::msg::ActuatorCommand>()
{
  return mpc_car_control::msg::builder::Init_ActuatorCommand_header();
}

}  // namespace mpc_car_control

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__BUILDER_HPP_
