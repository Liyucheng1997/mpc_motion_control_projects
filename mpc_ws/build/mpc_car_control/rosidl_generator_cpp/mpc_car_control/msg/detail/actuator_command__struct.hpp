// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from mpc_car_control:msg/ActuatorCommand.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__STRUCT_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__mpc_car_control__msg__ActuatorCommand __attribute__((deprecated))
#else
# define DEPRECATED__mpc_car_control__msg__ActuatorCommand __declspec(deprecated)
#endif

namespace mpc_car_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ActuatorCommand_
{
  using Type = ActuatorCommand_<ContainerAllocator>;

  explicit ActuatorCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->steering_angle = 0.0;
      this->throttle = 0.0;
      this->brake = 0.0;
    }
  }

  explicit ActuatorCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->steering_angle = 0.0;
      this->throttle = 0.0;
      this->brake = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _steering_angle_type =
    double;
  _steering_angle_type steering_angle;
  using _throttle_type =
    double;
  _throttle_type throttle;
  using _brake_type =
    double;
  _brake_type brake;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__steering_angle(
    const double & _arg)
  {
    this->steering_angle = _arg;
    return *this;
  }
  Type & set__throttle(
    const double & _arg)
  {
    this->throttle = _arg;
    return *this;
  }
  Type & set__brake(
    const double & _arg)
  {
    this->brake = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    mpc_car_control::msg::ActuatorCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const mpc_car_control::msg::ActuatorCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<mpc_car_control::msg::ActuatorCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<mpc_car_control::msg::ActuatorCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      mpc_car_control::msg::ActuatorCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<mpc_car_control::msg::ActuatorCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      mpc_car_control::msg::ActuatorCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<mpc_car_control::msg::ActuatorCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<mpc_car_control::msg::ActuatorCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<mpc_car_control::msg::ActuatorCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__mpc_car_control__msg__ActuatorCommand
    std::shared_ptr<mpc_car_control::msg::ActuatorCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__mpc_car_control__msg__ActuatorCommand
    std::shared_ptr<mpc_car_control::msg::ActuatorCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ActuatorCommand_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->steering_angle != other.steering_angle) {
      return false;
    }
    if (this->throttle != other.throttle) {
      return false;
    }
    if (this->brake != other.brake) {
      return false;
    }
    return true;
  }
  bool operator!=(const ActuatorCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ActuatorCommand_

// alias to use template instance with default allocator
using ActuatorCommand =
  mpc_car_control::msg::ActuatorCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace mpc_car_control

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__ACTUATOR_COMMAND__STRUCT_HPP_
