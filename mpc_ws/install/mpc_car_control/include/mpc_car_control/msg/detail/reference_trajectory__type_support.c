// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from mpc_car_control:msg/ReferenceTrajectory.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "mpc_car_control/msg/detail/reference_trajectory__rosidl_typesupport_introspection_c.h"
#include "mpc_car_control/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "mpc_car_control/msg/detail/reference_trajectory__functions.h"
#include "mpc_car_control/msg/detail/reference_trajectory__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `points`
#include "geometry_msgs/msg/point.h"
// Member `points`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"
// Member `velocity_profile`
// Member `yaw_profile`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  mpc_car_control__msg__ReferenceTrajectory__init(message_memory);
}

void ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_fini_function(void * message_memory)
{
  mpc_car_control__msg__ReferenceTrajectory__fini(message_memory);
}

size_t ReferenceTrajectory__rosidl_typesupport_introspection_c__size_function__Point__points(
  const void * untyped_member)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return member->size;
}

const void * ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__Point__points(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void * ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__Point__points(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

bool ReferenceTrajectory__rosidl_typesupport_introspection_c__resize_function__Point__points(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  geometry_msgs__msg__Point__Sequence__fini(member);
  return geometry_msgs__msg__Point__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control__msg__ReferenceTrajectory, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "points",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control__msg__ReferenceTrajectory, points),  // bytes offset in struct
    NULL,  // default value
    ReferenceTrajectory__rosidl_typesupport_introspection_c__size_function__Point__points,  // size() function pointer
    ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__Point__points,  // get_const(index) function pointer
    ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__Point__points,  // get(index) function pointer
    ReferenceTrajectory__rosidl_typesupport_introspection_c__resize_function__Point__points  // resize(index) function pointer
  },
  {
    "velocity_profile",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control__msg__ReferenceTrajectory, velocity_profile),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yaw_profile",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control__msg__ReferenceTrajectory, yaw_profile),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_members = {
  "mpc_car_control__msg",  // message namespace
  "ReferenceTrajectory",  // message name
  4,  // number of fields
  sizeof(mpc_car_control__msg__ReferenceTrajectory),
  ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_member_array,  // message members
  ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_init_function,  // function to initialize message memory (memory has to be allocated)
  ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_type_support_handle = {
  0,
  &ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_mpc_car_control
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mpc_car_control, msg, ReferenceTrajectory)() {
  ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_type_support_handle.typesupport_identifier) {
    ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
