// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mpc_car_control:msg/ControlCommandBody.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__BUILDER_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__BUILDER_HPP_

#include "mpc_car_control/msg/detail/control_command_body__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace mpc_car_control
{

namespace msg
{

namespace builder
{

class Init_ControlCommandBody_my
{
public:
  explicit Init_ControlCommandBody_my(::mpc_car_control::msg::ControlCommandBody & msg)
  : msg_(msg)
  {}
  ::mpc_car_control::msg::ControlCommandBody my(::mpc_car_control::msg::ControlCommandBody::_my_type arg)
  {
    msg_.my = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mpc_car_control::msg::ControlCommandBody msg_;
};

class Init_ControlCommandBody_mx
{
public:
  explicit Init_ControlCommandBody_mx(::mpc_car_control::msg::ControlCommandBody & msg)
  : msg_(msg)
  {}
  Init_ControlCommandBody_my mx(::mpc_car_control::msg::ControlCommandBody::_mx_type arg)
  {
    msg_.mx = std::move(arg);
    return Init_ControlCommandBody_my(msg_);
  }

private:
  ::mpc_car_control::msg::ControlCommandBody msg_;
};

class Init_ControlCommandBody_fz
{
public:
  explicit Init_ControlCommandBody_fz(::mpc_car_control::msg::ControlCommandBody & msg)
  : msg_(msg)
  {}
  Init_ControlCommandBody_mx fz(::mpc_car_control::msg::ControlCommandBody::_fz_type arg)
  {
    msg_.fz = std::move(arg);
    return Init_ControlCommandBody_mx(msg_);
  }

private:
  ::mpc_car_control::msg::ControlCommandBody msg_;
};

class Init_ControlCommandBody_mz
{
public:
  explicit Init_ControlCommandBody_mz(::mpc_car_control::msg::ControlCommandBody & msg)
  : msg_(msg)
  {}
  Init_ControlCommandBody_fz mz(::mpc_car_control::msg::ControlCommandBody::_mz_type arg)
  {
    msg_.mz = std::move(arg);
    return Init_ControlCommandBody_fz(msg_);
  }

private:
  ::mpc_car_control::msg::ControlCommandBody msg_;
};

class Init_ControlCommandBody_fy
{
public:
  explicit Init_ControlCommandBody_fy(::mpc_car_control::msg::ControlCommandBody & msg)
  : msg_(msg)
  {}
  Init_ControlCommandBody_mz fy(::mpc_car_control::msg::ControlCommandBody::_fy_type arg)
  {
    msg_.fy = std::move(arg);
    return Init_ControlCommandBody_mz(msg_);
  }

private:
  ::mpc_car_control::msg::ControlCommandBody msg_;
};

class Init_ControlCommandBody_fx
{
public:
  explicit Init_ControlCommandBody_fx(::mpc_car_control::msg::ControlCommandBody & msg)
  : msg_(msg)
  {}
  Init_ControlCommandBody_fy fx(::mpc_car_control::msg::ControlCommandBody::_fx_type arg)
  {
    msg_.fx = std::move(arg);
    return Init_ControlCommandBody_fy(msg_);
  }

private:
  ::mpc_car_control::msg::ControlCommandBody msg_;
};

class Init_ControlCommandBody_header
{
public:
  Init_ControlCommandBody_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ControlCommandBody_fx header(::mpc_car_control::msg::ControlCommandBody::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ControlCommandBody_fx(msg_);
  }

private:
  ::mpc_car_control::msg::ControlCommandBody msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mpc_car_control::msg::ControlCommandBody>()
{
  return mpc_car_control::msg::builder::Init_ControlCommandBody_header();
}

}  // namespace mpc_car_control

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__BUILDER_HPP_
