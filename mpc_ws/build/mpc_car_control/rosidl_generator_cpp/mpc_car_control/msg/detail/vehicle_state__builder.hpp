// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mpc_car_control:msg/VehicleState.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_

#include "mpc_car_control/msg/detail/vehicle_state__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace mpc_car_control
{

namespace msg
{

namespace builder
{

class Init_VehicleState_az
{
public:
  explicit Init_VehicleState_az(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  ::mpc_car_control::msg::VehicleState az(::mpc_car_control::msg::VehicleState::_az_type arg)
  {
    msg_.az = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_yaw_rate
{
public:
  explicit Init_VehicleState_yaw_rate(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_az yaw_rate(::mpc_car_control::msg::VehicleState::_yaw_rate_type arg)
  {
    msg_.yaw_rate = std::move(arg);
    return Init_VehicleState_az(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_pitch_rate
{
public:
  explicit Init_VehicleState_pitch_rate(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_yaw_rate pitch_rate(::mpc_car_control::msg::VehicleState::_pitch_rate_type arg)
  {
    msg_.pitch_rate = std::move(arg);
    return Init_VehicleState_yaw_rate(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_roll_rate
{
public:
  explicit Init_VehicleState_roll_rate(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_pitch_rate roll_rate(::mpc_car_control::msg::VehicleState::_roll_rate_type arg)
  {
    msg_.roll_rate = std::move(arg);
    return Init_VehicleState_pitch_rate(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_vz
{
public:
  explicit Init_VehicleState_vz(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_roll_rate vz(::mpc_car_control::msg::VehicleState::_vz_type arg)
  {
    msg_.vz = std::move(arg);
    return Init_VehicleState_roll_rate(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_vy
{
public:
  explicit Init_VehicleState_vy(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_vz vy(::mpc_car_control::msg::VehicleState::_vy_type arg)
  {
    msg_.vy = std::move(arg);
    return Init_VehicleState_vz(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_vx
{
public:
  explicit Init_VehicleState_vx(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_vy vx(::mpc_car_control::msg::VehicleState::_vx_type arg)
  {
    msg_.vx = std::move(arg);
    return Init_VehicleState_vy(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_yaw
{
public:
  explicit Init_VehicleState_yaw(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_vx yaw(::mpc_car_control::msg::VehicleState::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_VehicleState_vx(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_pitch
{
public:
  explicit Init_VehicleState_pitch(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_yaw pitch(::mpc_car_control::msg::VehicleState::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_VehicleState_yaw(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_roll
{
public:
  explicit Init_VehicleState_roll(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_pitch roll(::mpc_car_control::msg::VehicleState::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_VehicleState_pitch(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_z
{
public:
  explicit Init_VehicleState_z(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_roll z(::mpc_car_control::msg::VehicleState::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_VehicleState_roll(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_y
{
public:
  explicit Init_VehicleState_y(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_z y(::mpc_car_control::msg::VehicleState::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_VehicleState_z(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_x
{
public:
  explicit Init_VehicleState_x(::mpc_car_control::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_y x(::mpc_car_control::msg::VehicleState::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_VehicleState_y(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

class Init_VehicleState_header
{
public:
  Init_VehicleState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleState_x header(::mpc_car_control::msg::VehicleState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_VehicleState_x(msg_);
  }

private:
  ::mpc_car_control::msg::VehicleState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mpc_car_control::msg::VehicleState>()
{
  return mpc_car_control::msg::builder::Init_VehicleState_header();
}

}  // namespace mpc_car_control

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_
