// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mpc_car_control:msg/ReferenceTrajectory.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mpc_car_control/msg/reference_trajectory.hpp"


#ifndef MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__BUILDER_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "mpc_car_control/msg/detail/reference_trajectory__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace mpc_car_control
{

namespace msg
{

namespace builder
{

class Init_ReferenceTrajectory_yaw_profile
{
public:
  explicit Init_ReferenceTrajectory_yaw_profile(::mpc_car_control::msg::ReferenceTrajectory & msg)
  : msg_(msg)
  {}
  ::mpc_car_control::msg::ReferenceTrajectory yaw_profile(::mpc_car_control::msg::ReferenceTrajectory::_yaw_profile_type arg)
  {
    msg_.yaw_profile = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mpc_car_control::msg::ReferenceTrajectory msg_;
};

class Init_ReferenceTrajectory_velocity_profile
{
public:
  explicit Init_ReferenceTrajectory_velocity_profile(::mpc_car_control::msg::ReferenceTrajectory & msg)
  : msg_(msg)
  {}
  Init_ReferenceTrajectory_yaw_profile velocity_profile(::mpc_car_control::msg::ReferenceTrajectory::_velocity_profile_type arg)
  {
    msg_.velocity_profile = std::move(arg);
    return Init_ReferenceTrajectory_yaw_profile(msg_);
  }

private:
  ::mpc_car_control::msg::ReferenceTrajectory msg_;
};

class Init_ReferenceTrajectory_points
{
public:
  explicit Init_ReferenceTrajectory_points(::mpc_car_control::msg::ReferenceTrajectory & msg)
  : msg_(msg)
  {}
  Init_ReferenceTrajectory_velocity_profile points(::mpc_car_control::msg::ReferenceTrajectory::_points_type arg)
  {
    msg_.points = std::move(arg);
    return Init_ReferenceTrajectory_velocity_profile(msg_);
  }

private:
  ::mpc_car_control::msg::ReferenceTrajectory msg_;
};

class Init_ReferenceTrajectory_header
{
public:
  Init_ReferenceTrajectory_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ReferenceTrajectory_points header(::mpc_car_control::msg::ReferenceTrajectory::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ReferenceTrajectory_points(msg_);
  }

private:
  ::mpc_car_control::msg::ReferenceTrajectory msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mpc_car_control::msg::ReferenceTrajectory>()
{
  return mpc_car_control::msg::builder::Init_ReferenceTrajectory_header();
}

}  // namespace mpc_car_control

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__BUILDER_HPP_
