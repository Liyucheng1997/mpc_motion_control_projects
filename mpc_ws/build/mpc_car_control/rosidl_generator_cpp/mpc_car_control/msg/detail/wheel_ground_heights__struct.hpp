// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from mpc_car_control:msg/WheelGroundHeights.idl
// generated code does not contain a copyright notice

#ifndef MPC_CAR_CONTROL__MSG__DETAIL__WHEEL_GROUND_HEIGHTS__STRUCT_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__WHEEL_GROUND_HEIGHTS__STRUCT_HPP_

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
# define DEPRECATED__mpc_car_control__msg__WheelGroundHeights __attribute__((deprecated))
#else
# define DEPRECATED__mpc_car_control__msg__WheelGroundHeights __declspec(deprecated)
#endif

namespace mpc_car_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WheelGroundHeights_
{
  using Type = WheelGroundHeights_<ContainerAllocator>;

  explicit WheelGroundHeights_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 4>::iterator, double>(this->wheel_ground_heights.begin(), this->wheel_ground_heights.end(), 0.0);
    }
  }

  explicit WheelGroundHeights_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    wheel_ground_heights(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 4>::iterator, double>(this->wheel_ground_heights.begin(), this->wheel_ground_heights.end(), 0.0);
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _wheel_ground_heights_type =
    std::array<double, 4>;
  _wheel_ground_heights_type wheel_ground_heights;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__wheel_ground_heights(
    const std::array<double, 4> & _arg)
  {
    this->wheel_ground_heights = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator> *;
  using ConstRawPtr =
    const mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__mpc_car_control__msg__WheelGroundHeights
    std::shared_ptr<mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__mpc_car_control__msg__WheelGroundHeights
    std::shared_ptr<mpc_car_control::msg::WheelGroundHeights_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WheelGroundHeights_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->wheel_ground_heights != other.wheel_ground_heights) {
      return false;
    }
    return true;
  }
  bool operator!=(const WheelGroundHeights_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WheelGroundHeights_

// alias to use template instance with default allocator
using WheelGroundHeights =
  mpc_car_control::msg::WheelGroundHeights_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace mpc_car_control

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__WHEEL_GROUND_HEIGHTS__STRUCT_HPP_
