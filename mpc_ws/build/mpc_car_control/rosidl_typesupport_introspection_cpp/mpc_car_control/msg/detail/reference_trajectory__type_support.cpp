// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from mpc_car_control:msg/ReferenceTrajectory.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "mpc_car_control/msg/detail/reference_trajectory__functions.h"
#include "mpc_car_control/msg/detail/reference_trajectory__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace mpc_car_control
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ReferenceTrajectory_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) mpc_car_control::msg::ReferenceTrajectory(_init);
}

void ReferenceTrajectory_fini_function(void * message_memory)
{
  auto typed_message = static_cast<mpc_car_control::msg::ReferenceTrajectory *>(message_memory);
  typed_message->~ReferenceTrajectory();
}

size_t size_function__ReferenceTrajectory__points(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ReferenceTrajectory__points(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  return &member[index];
}

void * get_function__ReferenceTrajectory__points(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  return &member[index];
}

void fetch_function__ReferenceTrajectory__points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const geometry_msgs::msg::Point *>(
    get_const_function__ReferenceTrajectory__points(untyped_member, index));
  auto & value = *reinterpret_cast<geometry_msgs::msg::Point *>(untyped_value);
  value = item;
}

void assign_function__ReferenceTrajectory__points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<geometry_msgs::msg::Point *>(
    get_function__ReferenceTrajectory__points(untyped_member, index));
  const auto & value = *reinterpret_cast<const geometry_msgs::msg::Point *>(untyped_value);
  item = value;
}

void resize_function__ReferenceTrajectory__points(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<geometry_msgs::msg::Point> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ReferenceTrajectory__velocity_profile(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ReferenceTrajectory__velocity_profile(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__ReferenceTrajectory__velocity_profile(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__ReferenceTrajectory__velocity_profile(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__ReferenceTrajectory__velocity_profile(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__ReferenceTrajectory__velocity_profile(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__ReferenceTrajectory__velocity_profile(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__ReferenceTrajectory__velocity_profile(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ReferenceTrajectory__yaw_profile(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ReferenceTrajectory__yaw_profile(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__ReferenceTrajectory__yaw_profile(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__ReferenceTrajectory__yaw_profile(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__ReferenceTrajectory__yaw_profile(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__ReferenceTrajectory__yaw_profile(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__ReferenceTrajectory__yaw_profile(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__ReferenceTrajectory__yaw_profile(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ReferenceTrajectory_message_member_array[4] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control::msg::ReferenceTrajectory, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "points",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Point>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control::msg::ReferenceTrajectory, points),  // bytes offset in struct
    nullptr,  // default value
    size_function__ReferenceTrajectory__points,  // size() function pointer
    get_const_function__ReferenceTrajectory__points,  // get_const(index) function pointer
    get_function__ReferenceTrajectory__points,  // get(index) function pointer
    fetch_function__ReferenceTrajectory__points,  // fetch(index, &value) function pointer
    assign_function__ReferenceTrajectory__points,  // assign(index, value) function pointer
    resize_function__ReferenceTrajectory__points  // resize(index) function pointer
  },
  {
    "velocity_profile",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control::msg::ReferenceTrajectory, velocity_profile),  // bytes offset in struct
    nullptr,  // default value
    size_function__ReferenceTrajectory__velocity_profile,  // size() function pointer
    get_const_function__ReferenceTrajectory__velocity_profile,  // get_const(index) function pointer
    get_function__ReferenceTrajectory__velocity_profile,  // get(index) function pointer
    fetch_function__ReferenceTrajectory__velocity_profile,  // fetch(index, &value) function pointer
    assign_function__ReferenceTrajectory__velocity_profile,  // assign(index, value) function pointer
    resize_function__ReferenceTrajectory__velocity_profile  // resize(index) function pointer
  },
  {
    "yaw_profile",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mpc_car_control::msg::ReferenceTrajectory, yaw_profile),  // bytes offset in struct
    nullptr,  // default value
    size_function__ReferenceTrajectory__yaw_profile,  // size() function pointer
    get_const_function__ReferenceTrajectory__yaw_profile,  // get_const(index) function pointer
    get_function__ReferenceTrajectory__yaw_profile,  // get(index) function pointer
    fetch_function__ReferenceTrajectory__yaw_profile,  // fetch(index, &value) function pointer
    assign_function__ReferenceTrajectory__yaw_profile,  // assign(index, value) function pointer
    resize_function__ReferenceTrajectory__yaw_profile  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ReferenceTrajectory_message_members = {
  "mpc_car_control::msg",  // message namespace
  "ReferenceTrajectory",  // message name
  4,  // number of fields
  sizeof(mpc_car_control::msg::ReferenceTrajectory),
  false,  // has_any_key_member_
  ReferenceTrajectory_message_member_array,  // message members
  ReferenceTrajectory_init_function,  // function to initialize message memory (memory has to be allocated)
  ReferenceTrajectory_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ReferenceTrajectory_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ReferenceTrajectory_message_members,
  get_message_typesupport_handle_function,
  &mpc_car_control__msg__ReferenceTrajectory__get_type_hash,
  &mpc_car_control__msg__ReferenceTrajectory__get_type_description,
  &mpc_car_control__msg__ReferenceTrajectory__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace mpc_car_control


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<mpc_car_control::msg::ReferenceTrajectory>()
{
  return &::mpc_car_control::msg::rosidl_typesupport_introspection_cpp::ReferenceTrajectory_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, mpc_car_control, msg, ReferenceTrajectory)() {
  return &::mpc_car_control::msg::rosidl_typesupport_introspection_cpp::ReferenceTrajectory_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
