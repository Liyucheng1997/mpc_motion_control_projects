// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from mpc_car_control:msg/VehicleState.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__TRAITS_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__TRAITS_HPP_

#include "mpc_car_control/msg/detail/vehicle_state__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<mpc_car_control::msg::VehicleState>()
{
  return "mpc_car_control::msg::VehicleState";
}

template<>
inline const char * name<mpc_car_control::msg::VehicleState>()
{
  return "mpc_car_control/msg/VehicleState";
}

template<>
struct has_fixed_size<mpc_car_control::msg::VehicleState>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<mpc_car_control::msg::VehicleState>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<mpc_car_control::msg::VehicleState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__TRAITS_HPP_
