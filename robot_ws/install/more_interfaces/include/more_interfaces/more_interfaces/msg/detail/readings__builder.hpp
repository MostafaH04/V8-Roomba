// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from more_interfaces:msg/Readings.idl
// generated code does not contain a copyright notice

#ifndef MORE_INTERFACES__MSG__DETAIL__READINGS__BUILDER_HPP_
#define MORE_INTERFACES__MSG__DETAIL__READINGS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "more_interfaces/msg/detail/readings__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace more_interfaces
{

namespace msg
{

namespace builder
{

class Init_Readings_gyr_z
{
public:
  explicit Init_Readings_gyr_z(::more_interfaces::msg::Readings & msg)
  : msg_(msg)
  {}
  ::more_interfaces::msg::Readings gyr_z(::more_interfaces::msg::Readings::_gyr_z_type arg)
  {
    msg_.gyr_z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::more_interfaces::msg::Readings msg_;
};

class Init_Readings_gyr_y
{
public:
  explicit Init_Readings_gyr_y(::more_interfaces::msg::Readings & msg)
  : msg_(msg)
  {}
  Init_Readings_gyr_z gyr_y(::more_interfaces::msg::Readings::_gyr_y_type arg)
  {
    msg_.gyr_y = std::move(arg);
    return Init_Readings_gyr_z(msg_);
  }

private:
  ::more_interfaces::msg::Readings msg_;
};

class Init_Readings_gyr_x
{
public:
  explicit Init_Readings_gyr_x(::more_interfaces::msg::Readings & msg)
  : msg_(msg)
  {}
  Init_Readings_gyr_y gyr_x(::more_interfaces::msg::Readings::_gyr_x_type arg)
  {
    msg_.gyr_x = std::move(arg);
    return Init_Readings_gyr_y(msg_);
  }

private:
  ::more_interfaces::msg::Readings msg_;
};

class Init_Readings_acc_z
{
public:
  explicit Init_Readings_acc_z(::more_interfaces::msg::Readings & msg)
  : msg_(msg)
  {}
  Init_Readings_gyr_x acc_z(::more_interfaces::msg::Readings::_acc_z_type arg)
  {
    msg_.acc_z = std::move(arg);
    return Init_Readings_gyr_x(msg_);
  }

private:
  ::more_interfaces::msg::Readings msg_;
};

class Init_Readings_acc_y
{
public:
  explicit Init_Readings_acc_y(::more_interfaces::msg::Readings & msg)
  : msg_(msg)
  {}
  Init_Readings_acc_z acc_y(::more_interfaces::msg::Readings::_acc_y_type arg)
  {
    msg_.acc_y = std::move(arg);
    return Init_Readings_acc_z(msg_);
  }

private:
  ::more_interfaces::msg::Readings msg_;
};

class Init_Readings_acc_x
{
public:
  Init_Readings_acc_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Readings_acc_y acc_x(::more_interfaces::msg::Readings::_acc_x_type arg)
  {
    msg_.acc_x = std::move(arg);
    return Init_Readings_acc_y(msg_);
  }

private:
  ::more_interfaces::msg::Readings msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::more_interfaces::msg::Readings>()
{
  return more_interfaces::msg::builder::Init_Readings_acc_x();
}

}  // namespace more_interfaces

#endif  // MORE_INTERFACES__MSG__DETAIL__READINGS__BUILDER_HPP_
