// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from more_interfaces:msg/Readings.idl
// generated code does not contain a copyright notice

#ifndef MORE_INTERFACES__MSG__DETAIL__READINGS__STRUCT_HPP_
#define MORE_INTERFACES__MSG__DETAIL__READINGS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__more_interfaces__msg__Readings __attribute__((deprecated))
#else
# define DEPRECATED__more_interfaces__msg__Readings __declspec(deprecated)
#endif

namespace more_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Readings_
{
  using Type = Readings_<ContainerAllocator>;

  explicit Readings_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->acc_x = 0.0f;
      this->acc_y = 0.0f;
      this->acc_z = 0.0f;
      this->gyr_x = 0.0f;
      this->gyr_y = 0.0f;
      this->gyr_z = 0.0f;
    }
  }

  explicit Readings_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->acc_x = 0.0f;
      this->acc_y = 0.0f;
      this->acc_z = 0.0f;
      this->gyr_x = 0.0f;
      this->gyr_y = 0.0f;
      this->gyr_z = 0.0f;
    }
  }

  // field types and members
  using _acc_x_type =
    float;
  _acc_x_type acc_x;
  using _acc_y_type =
    float;
  _acc_y_type acc_y;
  using _acc_z_type =
    float;
  _acc_z_type acc_z;
  using _gyr_x_type =
    float;
  _gyr_x_type gyr_x;
  using _gyr_y_type =
    float;
  _gyr_y_type gyr_y;
  using _gyr_z_type =
    float;
  _gyr_z_type gyr_z;

  // setters for named parameter idiom
  Type & set__acc_x(
    const float & _arg)
  {
    this->acc_x = _arg;
    return *this;
  }
  Type & set__acc_y(
    const float & _arg)
  {
    this->acc_y = _arg;
    return *this;
  }
  Type & set__acc_z(
    const float & _arg)
  {
    this->acc_z = _arg;
    return *this;
  }
  Type & set__gyr_x(
    const float & _arg)
  {
    this->gyr_x = _arg;
    return *this;
  }
  Type & set__gyr_y(
    const float & _arg)
  {
    this->gyr_y = _arg;
    return *this;
  }
  Type & set__gyr_z(
    const float & _arg)
  {
    this->gyr_z = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    more_interfaces::msg::Readings_<ContainerAllocator> *;
  using ConstRawPtr =
    const more_interfaces::msg::Readings_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<more_interfaces::msg::Readings_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<more_interfaces::msg::Readings_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      more_interfaces::msg::Readings_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<more_interfaces::msg::Readings_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      more_interfaces::msg::Readings_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<more_interfaces::msg::Readings_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<more_interfaces::msg::Readings_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<more_interfaces::msg::Readings_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__more_interfaces__msg__Readings
    std::shared_ptr<more_interfaces::msg::Readings_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__more_interfaces__msg__Readings
    std::shared_ptr<more_interfaces::msg::Readings_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Readings_ & other) const
  {
    if (this->acc_x != other.acc_x) {
      return false;
    }
    if (this->acc_y != other.acc_y) {
      return false;
    }
    if (this->acc_z != other.acc_z) {
      return false;
    }
    if (this->gyr_x != other.gyr_x) {
      return false;
    }
    if (this->gyr_y != other.gyr_y) {
      return false;
    }
    if (this->gyr_z != other.gyr_z) {
      return false;
    }
    return true;
  }
  bool operator!=(const Readings_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Readings_

// alias to use template instance with default allocator
using Readings =
  more_interfaces::msg::Readings_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace more_interfaces

#endif  // MORE_INTERFACES__MSG__DETAIL__READINGS__STRUCT_HPP_
