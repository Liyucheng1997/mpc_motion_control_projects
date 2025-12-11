// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from mpc_car_control:msg/VehicleState.idl
// generated code does not contain a copyright notice
#ifndef MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "mpc_car_control/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "mpc_car_control/msg/detail/vehicle_state__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
bool cdr_serialize_mpc_car_control__msg__VehicleState(
  const mpc_car_control__msg__VehicleState * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
bool cdr_deserialize_mpc_car_control__msg__VehicleState(
  eprosima::fastcdr::Cdr &,
  mpc_car_control__msg__VehicleState * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
size_t get_serialized_size_mpc_car_control__msg__VehicleState(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
size_t max_serialized_size_mpc_car_control__msg__VehicleState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
bool cdr_serialize_key_mpc_car_control__msg__VehicleState(
  const mpc_car_control__msg__VehicleState * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
size_t get_serialized_size_key_mpc_car_control__msg__VehicleState(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
size_t max_serialized_size_key_mpc_car_control__msg__VehicleState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mpc_car_control
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, mpc_car_control, msg, VehicleState)();

#ifdef __cplusplus
}
#endif

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__VEHICLE_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
