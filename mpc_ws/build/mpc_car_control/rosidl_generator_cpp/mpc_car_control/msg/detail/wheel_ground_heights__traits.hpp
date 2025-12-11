// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from mpc_car_control:msg/WheelGroundHeights.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mpc_car_control/msg/wheel_ground_heights.hpp"


#ifndef MPC_CAR_CONTROL__MSG__DETAIL__WHEEL_GROUND_HEIGHTS__TRAITS_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__WHEEL_GROUND_HEIGHTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "mpc_car_control/msg/detail/wheel_ground_heights__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace mpc_car_control
{

namespace msg
{

inline void to_flow_style_yaml(
  const WheelGroundHeights & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: wheel_ground_heights
  {
    if (msg.wheel_ground_heights.size() == 0) {
      out << "wheel_ground_heights: []";
    } else {
      out << "wheel_ground_heights: [";
      size_t pending_items = msg.wheel_ground_heights.size();
      for (auto item : msg.wheel_ground_heights) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const WheelGroundHeights & msg,
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

  // member: wheel_ground_heights
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.wheel_ground_heights.size() == 0) {
      out << "wheel_ground_heights: []\n";
    } else {
      out << "wheel_ground_heights:\n";
      for (auto item : msg.wheel_ground_heights) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WheelGroundHeights & msg, bool use_flow_style = false)
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
  const mpc_car_control::msg::WheelGroundHeights & msg,
  std::ostream & out, size_t indentation = 0)
{
  mpc_car_control::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use mpc_car_control::msg::to_yaml() instead")]]
inline std::string to_yaml(const mpc_car_control::msg::WheelGroundHeights & msg)
{
  return mpc_car_control::msg::to_yaml(msg);
}

template<>
inline const char * data_type<mpc_car_control::msg::WheelGroundHeights>()
{
  return "mpc_car_control::msg::WheelGroundHeights";
}

template<>
inline const char * name<mpc_car_control::msg::WheelGroundHeights>()
{
  return "mpc_car_control/msg/WheelGroundHeights";
}

template<>
struct has_fixed_size<mpc_car_control::msg::WheelGroundHeights>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<mpc_car_control::msg::WheelGroundHeights>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<mpc_car_control::msg::WheelGroundHeights>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__WHEEL_GROUND_HEIGHTS__TRAITS_HPP_
