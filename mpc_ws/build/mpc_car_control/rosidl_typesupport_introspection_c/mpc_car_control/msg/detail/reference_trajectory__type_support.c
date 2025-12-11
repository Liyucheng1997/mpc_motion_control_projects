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

void mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  mpc_car_control__msg__ReferenceTrajectory__init(message_memory);
}

void mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_fini_function(void * message_memory)
{
  mpc_car_control__msg__ReferenceTrajectory__fini(message_memory);
}

size_t mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__size_function__ReferenceTrajectory__points(
  const void * untyped_member)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return member->size;
}

const void * mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__ReferenceTrajectory__points(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void * mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__ReferenceTrajectory__points(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__fetch_function__ReferenceTrajectory__points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Point * item =
    ((const geometry_msgs__msg__Point *)
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__ReferenceTrajectory__points(untyped_member, index));
  geometry_msgs__msg__Point * value =
    (geometry_msgs__msg__Point *)(untyped_value);
  *value = *item;
}

void mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__assign_function__ReferenceTrajectory__points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Point * item =
    ((geometry_msgs__msg__Point *)
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__ReferenceTrajectory__points(untyped_member, index));
  const geometry_msgs__msg__Point * value =
    (const geometry_msgs__msg__Point *)(untyped_value);
  *item = *value;
}

bool mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__resize_function__ReferenceTrajectory__points(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  geometry_msgs__msg__Point__Sequence__fini(member);
  return geometry_msgs__msg__Point__Sequence__init(member, size);
}

size_t mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__size_function__ReferenceTrajectory__velocity_profile(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__ReferenceTrajectory__velocity_profile(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__ReferenceTrajectory__velocity_profile(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__fetch_function__ReferenceTrajectory__velocity_profile(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__ReferenceTrajectory__velocity_profile(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__assign_function__ReferenceTrajectory__velocity_profile(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__ReferenceTrajectory__velocity_profile(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__resize_function__ReferenceTrajectory__velocity_profile(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__size_function__ReferenceTrajectory__yaw_profile(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__ReferenceTrajectory__yaw_profile(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__ReferenceTrajectory__yaw_profile(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__fetch_function__ReferenceTrajectory__yaw_profile(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__ReferenceTrajectory__yaw_profile(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__assign_function__ReferenceTrajectory__yaw_profile(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__ReferenceTrajectory__yaw_profile(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__resize_function__ReferenceTrajectory__yaw_profile(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control__msg__ReferenceTrajectory, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "points",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control__msg__ReferenceTrajectory, points),  // bytes offset in struct
    NULL,  // default value
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__size_function__ReferenceTrajectory__points,  // size() function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__ReferenceTrajectory__points,  // get_const(index) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__ReferenceTrajectory__points,  // get(index) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__fetch_function__ReferenceTrajectory__points,  // fetch(index, &value) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__assign_function__ReferenceTrajectory__points,  // assign(index, value) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__resize_function__ReferenceTrajectory__points  // resize(index) function pointer
  },
  {
    "velocity_profile",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control__msg__ReferenceTrajectory, velocity_profile),  // bytes offset in struct
    NULL,  // default value
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__size_function__ReferenceTrajectory__velocity_profile,  // size() function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__ReferenceTrajectory__velocity_profile,  // get_const(index) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__ReferenceTrajectory__velocity_profile,  // get(index) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__fetch_function__ReferenceTrajectory__velocity_profile,  // fetch(index, &value) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__assign_function__ReferenceTrajectory__velocity_profile,  // assign(index, value) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__resize_function__ReferenceTrajectory__velocity_profile  // resize(index) function pointer
  },
  {
    "yaw_profile",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control__msg__ReferenceTrajectory, yaw_profile),  // bytes offset in struct
    NULL,  // default value
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__size_function__ReferenceTrajectory__yaw_profile,  // size() function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_const_function__ReferenceTrajectory__yaw_profile,  // get_const(index) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__get_function__ReferenceTrajectory__yaw_profile,  // get(index) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__fetch_function__ReferenceTrajectory__yaw_profile,  // fetch(index, &value) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__assign_function__ReferenceTrajectory__yaw_profile,  // assign(index, value) function pointer
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__resize_function__ReferenceTrajectory__yaw_profile  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_members = {
  "mpc_car_control__msg",  // message namespace
  "ReferenceTrajectory",  // message name
  4,  // number of fields
  sizeof(mpc_car_control__msg__ReferenceTrajectory),
  false,  // has_any_key_member_
  mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_member_array,  // message members
  mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_init_function,  // function to initialize message memory (memory has to be allocated)
  mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_type_support_handle = {
  0,
  &mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_members,
  get_message_typesupport_handle_function,
  &mpc_car_control__msg__ReferenceTrajectory__get_type_hash,
  &mpc_car_control__msg__ReferenceTrajectory__get_type_description,
  &mpc_car_control__msg__ReferenceTrajectory__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_mpc_car_control
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mpc_car_control, msg, ReferenceTrajectory)() {
  mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_type_support_handle.typesupport_identifier) {
    mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &mpc_car_control__msg__ReferenceTrajectory__rosidl_typesupport_introspection_c__ReferenceTrajectory_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
