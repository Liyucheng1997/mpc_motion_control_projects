// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from mpc_car_control:msg/ReferenceTrajectory.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mpc_car_control/msg/reference_trajectory.hpp"


#ifndef MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__TRAITS_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "mpc_car_control/msg/detail/reference_trajectory__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'points'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace mpc_car_control
{

namespace msg
{

inline void to_flow_style_yaml(
  const ReferenceTrajectory & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: points
  {
    if (msg.points.size() == 0) {
      out << "points: []";
    } else {
      out << "points: [";
      size_t pending_items = msg.points.size();
      for (auto item : msg.points) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: velocity_profile
  {
    if (msg.velocity_profile.size() == 0) {
      out << "velocity_profile: []";
    } else {
      out << "velocity_profile: [";
      size_t pending_items = msg.velocity_profile.size();
      for (auto item : msg.velocity_profile) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: yaw_profile
  {
    if (msg.yaw_profile.size() == 0) {
      out << "yaw_profile: []";
    } else {
      out << "yaw_profile: [";
      size_t pending_items = msg.yaw_profile.size();
      for (auto item : msg.yaw_profile) {
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
  const ReferenceTrajectory & msg,
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

  // member: points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.points.size() == 0) {
      out << "points: []\n";
    } else {
      out << "points:\n";
      for (auto item : msg.points) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: velocity_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.velocity_profile.size() == 0) {
      out << "velocity_profile: []\n";
    } else {
      out << "velocity_profile:\n";
      for (auto item : msg.velocity_profile) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: yaw_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.yaw_profile.size() == 0) {
      out << "yaw_profile: []\n";
    } else {
      out << "yaw_profile:\n";
      for (auto item : msg.yaw_profile) {
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

inline std::string to_yaml(const ReferenceTrajectory & msg, bool use_flow_style = false)
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
  const mpc_car_control::msg::ReferenceTrajectory & msg,
  std::ostream & out, size_t indentation = 0)
{
  mpc_car_control::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use mpc_car_control::msg::to_yaml() instead")]]
inline std::string to_yaml(const mpc_car_control::msg::ReferenceTrajectory & msg)
{
  return mpc_car_control::msg::to_yaml(msg);
}

template<>
inline const char * data_type<mpc_car_control::msg::ReferenceTrajectory>()
{
  return "mpc_car_control::msg::ReferenceTrajectory";
}

template<>
inline const char * name<mpc_car_control::msg::ReferenceTrajectory>()
{
  return "mpc_car_control/msg/ReferenceTrajectory";
}

template<>
struct has_fixed_size<mpc_car_control::msg::ReferenceTrajectory>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<mpc_car_control::msg::ReferenceTrajectory>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<mpc_car_control::msg::ReferenceTrajectory>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__TRAITS_HPP_
