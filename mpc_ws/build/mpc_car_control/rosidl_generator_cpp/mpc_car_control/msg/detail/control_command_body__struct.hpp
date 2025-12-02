// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from mpc_car_control:msg/ControlCommandBody.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__STRUCT_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__STRUCT_HPP_

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
# define DEPRECATED__mpc_car_control__msg__ControlCommandBody __attribute__((deprecated))
#else
# define DEPRECATED__mpc_car_control__msg__ControlCommandBody __declspec(deprecated)
#endif

namespace mpc_car_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ControlCommandBody_
{
  using Type = ControlCommandBody_<ContainerAllocator>;

  explicit ControlCommandBody_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->fx = 0.0;
      this->fy = 0.0;
      this->mz = 0.0;
    }
  }

  explicit ControlCommandBody_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->fx = 0.0;
      this->fy = 0.0;
      this->mz = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _fx_type =
    double;
  _fx_type fx;
  using _fy_type =
    double;
  _fy_type fy;
  using _mz_type =
    double;
  _mz_type mz;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__fx(
    const double & _arg)
  {
    this->fx = _arg;
    return *this;
  }
  Type & set__fy(
    const double & _arg)
  {
    this->fy = _arg;
    return *this;
  }
  Type & set__mz(
    const double & _arg)
  {
    this->mz = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    mpc_car_control::msg::ControlCommandBody_<ContainerAllocator> *;
  using ConstRawPtr =
    const mpc_car_control::msg::ControlCommandBody_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<mpc_car_control::msg::ControlCommandBody_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<mpc_car_control::msg::ControlCommandBody_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      mpc_car_control::msg::ControlCommandBody_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<mpc_car_control::msg::ControlCommandBody_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      mpc_car_control::msg::ControlCommandBody_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<mpc_car_control::msg::ControlCommandBody_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<mpc_car_control::msg::ControlCommandBody_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<mpc_car_control::msg::ControlCommandBody_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__mpc_car_control__msg__ControlCommandBody
    std::shared_ptr<mpc_car_control::msg::ControlCommandBody_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__mpc_car_control__msg__ControlCommandBody
    std::shared_ptr<mpc_car_control::msg::ControlCommandBody_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ControlCommandBody_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->fx != other.fx) {
      return false;
    }
    if (this->fy != other.fy) {
      return false;
    }
    if (this->mz != other.mz) {
      return false;
    }
    return true;
  }
  bool operator!=(const ControlCommandBody_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ControlCommandBody_

// alias to use template instance with default allocator
using ControlCommandBody =
  mpc_car_control::msg::ControlCommandBody_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace mpc_car_control

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__CONTROL_COMMAND_BODY__STRUCT_HPP_
