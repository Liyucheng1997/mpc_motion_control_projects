// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from mpc_car_control:msg/WheelGroundHeights.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "mpc_car_control/msg/detail/wheel_ground_heights__rosidl_typesupport_introspection_c.h"
#include "mpc_car_control/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "mpc_car_control/msg/detail/wheel_ground_heights__functions.h"
#include "mpc_car_control/msg/detail/wheel_ground_heights__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  mpc_car_control__msg__WheelGroundHeights__init(message_memory);
}

void mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_fini_function(void * message_memory)
{
  mpc_car_control__msg__WheelGroundHeights__fini(message_memory);
}

size_t mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__size_function__WheelGroundHeights__wheel_ground_heights(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__get_const_function__WheelGroundHeights__wheel_ground_heights(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__get_function__WheelGroundHeights__wheel_ground_heights(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__fetch_function__WheelGroundHeights__wheel_ground_heights(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__get_const_function__WheelGroundHeights__wheel_ground_heights(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__assign_function__WheelGroundHeights__wheel_ground_heights(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__get_function__WheelGroundHeights__wheel_ground_heights(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control__msg__WheelGroundHeights, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "wheel_ground_heights",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control__msg__WheelGroundHeights, wheel_ground_heights),  // bytes offset in struct
    NULL,  // default value
    mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__size_function__WheelGroundHeights__wheel_ground_heights,  // size() function pointer
    mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__get_const_function__WheelGroundHeights__wheel_ground_heights,  // get_const(index) function pointer
    mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__get_function__WheelGroundHeights__wheel_ground_heights,  // get(index) function pointer
    mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__fetch_function__WheelGroundHeights__wheel_ground_heights,  // fetch(index, &value) function pointer
    mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__assign_function__WheelGroundHeights__wheel_ground_heights,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_message_members = {
  "mpc_car_control__msg",  // message namespace
  "WheelGroundHeights",  // message name
  2,  // number of fields
  sizeof(mpc_car_control__msg__WheelGroundHeights),
  false,  // has_any_key_member_
  mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_message_member_array,  // message members
  mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_init_function,  // function to initialize message memory (memory has to be allocated)
  mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_message_type_support_handle = {
  0,
  &mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_message_members,
  get_message_typesupport_handle_function,
  &mpc_car_control__msg__WheelGroundHeights__get_type_hash,
  &mpc_car_control__msg__WheelGroundHeights__get_type_description,
  &mpc_car_control__msg__WheelGroundHeights__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_mpc_car_control
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mpc_car_control, msg, WheelGroundHeights)() {
  mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_message_type_support_handle.typesupport_identifier) {
    mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &mpc_car_control__msg__WheelGroundHeights__rosidl_typesupport_introspection_c__WheelGroundHeights_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
