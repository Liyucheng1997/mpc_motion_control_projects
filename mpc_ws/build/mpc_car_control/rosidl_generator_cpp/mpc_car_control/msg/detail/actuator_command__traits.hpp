// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from mpc_car_control:msg/ActuatorCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mpc_car_control/msg/actuator_command.hpp"


#ifndef MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__TRAITS_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "mpc_car_control/msg/detail/actuator_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace mpc_car_control
{

namespace msg
{

inline void to_flow_style_yaml(
  const ActuatorCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: steering_angle
  {
    out << "steering_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_angle, out);
    out << ", ";
  }

  // member: throttle
  {
    out << "throttle: ";
    rosidl_generator_traits::value_to_yaml(msg.throttle, out);
    out << ", ";
  }

  // member: brake
  {
    out << "brake: ";
    rosidl_generator_traits::value_to_yaml(msg.brake, out);
    out << ", ";
  }

  // member: active_suspension_force
  {
    if (msg.active_suspension_force.size() == 0) {
      out << "active_suspension_force: []";
    } else {
      out << "active_suspension_force: [";
      size_t pending_items = msg.active_suspension_force.size();
      for (auto item : msg.active_suspension_force) {
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
  const ActuatorCommand & msg,
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

  // member: steering_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steering_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_angle, out);
    out << "\n";
  }

  // member: throttle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "throttle: ";
    rosidl_generator_traits::value_to_yaml(msg.throttle, out);
    out << "\n";
  }

  // member: brake
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "brake: ";
    rosidl_generator_traits::value_to_yaml(msg.brake, out);
    out << "\n";
  }

  // member: active_suspension_force
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.active_suspension_force.size() == 0) {
      out << "active_suspension_force: []\n";
    } else {
      out << "active_suspension_force:\n";
      for (auto item : msg.active_suspension_force) {
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

inline std::string to_yaml(const ActuatorCommand & msg, bool use_flow_style = false)
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
  const mpc_car_control::msg::ActuatorCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  mpc_car_control::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use mpc_car_control::msg::to_yaml() instead")]]
inline std::string to_yaml(const mpc_car_control::msg::ActuatorCommand & msg)
{
  return mpc_car_control::msg::to_yaml(msg);
}

template<>
inline const char * data_type<mpc_car_control::msg::ActuatorCommand>()
{
  return "mpc_car_control::msg::ActuatorCommand";
}

template<>
inline const char * name<mpc_car_control::msg::ActuatorCommand>()
{
  return "mpc_car_control/msg/ActuatorCommand";
}

template<>
struct has_fixed_size<mpc_car_control::msg::ActuatorCommand>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<mpc_car_control::msg::ActuatorCommand>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<mpc_car_control::msg::ActuatorCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__TRAITS_HPP_
