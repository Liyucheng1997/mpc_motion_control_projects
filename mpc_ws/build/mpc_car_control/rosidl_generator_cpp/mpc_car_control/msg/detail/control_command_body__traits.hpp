// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from mpc_car_control:msg/ControlCommandBody.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mpc_car_control/msg/control_command_body.hpp"


#ifndef MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__TRAITS_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "mpc_car_control/msg/detail/control_command_body__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace mpc_car_control
{

namespace msg
{

inline void to_flow_style_yaml(
  const ControlCommandBody & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: fx
  {
    out << "fx: ";
    rosidl_generator_traits::value_to_yaml(msg.fx, out);
    out << ", ";
  }

  // member: fy
  {
    out << "fy: ";
    rosidl_generator_traits::value_to_yaml(msg.fy, out);
    out << ", ";
  }

  // member: mz
  {
    out << "mz: ";
    rosidl_generator_traits::value_to_yaml(msg.mz, out);
    out << ", ";
  }

  // member: fz
  {
    out << "fz: ";
    rosidl_generator_traits::value_to_yaml(msg.fz, out);
    out << ", ";
  }

  // member: mx
  {
    out << "mx: ";
    rosidl_generator_traits::value_to_yaml(msg.mx, out);
    out << ", ";
  }

  // member: my
  {
    out << "my: ";
    rosidl_generator_traits::value_to_yaml(msg.my, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ControlCommandBody & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: fx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fx: ";
    rosidl_generator_traits::value_to_yaml(msg.fx, out);
    out << "\n";
  }

  // member: fy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fy: ";
    rosidl_generator_traits::value_to_yaml(msg.fy, out);
    out << "\n";
  }

  // member: mz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mz: ";
    rosidl_generator_traits::value_to_yaml(msg.mz, out);
    out << "\n";
  }

  // member: fz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fz: ";
    rosidl_generator_traits::value_to_yaml(msg.fz, out);
    out << "\n";
  }

  // member: mx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mx: ";
    rosidl_generator_traits::value_to_yaml(msg.mx, out);
    out << "\n";
  }

  // member: my
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "my: ";
    rosidl_generator_traits::value_to_yaml(msg.my, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ControlCommandBody & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace mpc_car_control

namespace rosidl_generator_traits
{

[[deprecated("use mpc_car_control::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const mpc_car_control::msg::ControlCommandBody & msg,
  std::ostream & out, size_t indentation = 0)
{
  mpc_car_control::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use mpc_car_control::msg::to_yaml() instead")]]
inline std::string to_yaml(const mpc_car_control::msg::ControlCommandBody & msg)
{
  return mpc_car_control::msg::to_yaml(msg);
}

template<>
inline const char * data_type<mpc_car_control::msg::ControlCommandBody>()
{
  return "mpc_car_control::msg::ControlCommandBody";
}

template<>
inline const char * name<mpc_car_control::msg::ControlCommandBody>()
{
  return "mpc_car_control/msg/ControlCommandBody";
}

template<>
struct has_fixed_size<mpc_car_control::msg::ControlCommandBody>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<mpc_car_control::msg::ControlCommandBody>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<mpc_car_control::msg::ControlCommandBody>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__TRAITS_HPP_
