// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mpc_car_control:msg/WheelGroundHeights.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__WHEEL_GROUND_HEIGHTS__BUILDER_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__WHEEL_GROUND_HEIGHTS__BUILDER_HPP_

#include "mpc_car_control/msg/detail/wheel_ground_heights__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace mpc_car_control
{

namespace msg
{

namespace builder
{

class Init_WheelGroundHeights_wheel_ground_heights
{
public:
  explicit Init_WheelGroundHeights_wheel_ground_heights(::mpc_car_control::msg::WheelGroundHeights & msg)
  : msg_(msg)
  {}
  ::mpc_car_control::msg::WheelGroundHeights wheel_ground_heights(::mpc_car_control::msg::WheelGroundHeights::_wheel_ground_heights_type arg)
  {
    msg_.wheel_ground_heights = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mpc_car_control::msg::WheelGroundHeights msg_;
};

class Init_WheelGroundHeights_header
{
public:
  Init_WheelGroundHeights_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WheelGroundHeights_wheel_ground_heights header(::mpc_car_control::msg::WheelGroundHeights::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_WheelGroundHeights_wheel_ground_heights(msg_);
  }

private:
  ::mpc_car_control::msg::WheelGroundHeights msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mpc_car_control::msg::WheelGroundHeights>()
{
  return mpc_car_control::msg::builder::Init_WheelGroundHeights_header();
}

}  // namespace mpc_car_control

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__WHEEL_GROUND_HEIGHTS__BUILDER_HPP_
