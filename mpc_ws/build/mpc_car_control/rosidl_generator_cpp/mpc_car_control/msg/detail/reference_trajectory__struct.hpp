// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from mpc_car_control:msg/ReferenceTrajectory.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mpc_car_control/msg/reference_trajectory.hpp"


#ifndef MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__STRUCT_HPP_
#define MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'points'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__mpc_car_control__msg__ReferenceTrajectory __attribute__((deprecated))
#else
# define DEPRECATED__mpc_car_control__msg__ReferenceTrajectory __declspec(deprecated)
#endif

namespace mpc_car_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ReferenceTrajectory_
{
  using Type = ReferenceTrajectory_<ContainerAllocator>;

  explicit ReferenceTrajectory_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit ReferenceTrajectory_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _points_type =
    std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>>;
  _points_type points;
  using _velocity_profile_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _velocity_profile_type velocity_profile;
  using _yaw_profile_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _yaw_profile_type yaw_profile;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__points(
    const std::vector<geometry_msgs::msg::Point_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Point_<ContainerAllocator>>> & _arg)
  {
    this->points = _arg;
    return *this;
  }
  Type & set__velocity_profile(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->velocity_profile = _arg;
    return *this;
  }
  Type & set__yaw_profile(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->yaw_profile = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator> *;
  using ConstRawPtr =
    const mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__mpc_car_control__msg__ReferenceTrajectory
    std::shared_ptr<mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__mpc_car_control__msg__ReferenceTrajectory
    std::shared_ptr<mpc_car_control::msg::ReferenceTrajectory_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ReferenceTrajectory_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->points != other.points) {
      return false;
    }
    if (this->velocity_profile != other.velocity_profile) {
      return false;
    }
    if (this->yaw_profile != other.yaw_profile) {
      return false;
    }
    return true;
  }
  bool operator!=(const ReferenceTrajectory_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ReferenceTrajectory_

// alias to use template instance with default allocator
using ReferenceTrajectory =
  mpc_car_control::msg::ReferenceTrajectory_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace mpc_car_control

#endif  // MPC_CAR_CONTROL__MSG__DETAIL__REFERENCE_TRAJECTORY__STRUCT_HPP_
