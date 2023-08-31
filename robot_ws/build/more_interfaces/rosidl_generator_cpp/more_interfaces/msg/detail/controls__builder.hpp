// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from more_interfaces:msg/Controls.idl
// generated code does not contain a copyright notice

#ifndef MORE_INTERFACES__MSG__DETAIL__CONTROLS__BUILDER_HPP_
#define MORE_INTERFACES__MSG__DETAIL__CONTROLS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "more_interfaces/msg/detail/controls__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace more_interfaces
{

namespace msg
{

namespace builder
{

class Init_Controls_steering
{
public:
  explicit Init_Controls_steering(::more_interfaces::msg::Controls & msg)
  : msg_(msg)
  {}
  ::more_interfaces::msg::Controls steering(::more_interfaces::msg::Controls::_steering_type arg)
  {
    msg_.steering = std::move(arg);
    return std::move(msg_);
  }

private:
  ::more_interfaces::msg::Controls msg_;
};

class Init_Controls_speed
{
public:
  Init_Controls_speed()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Controls_steering speed(::more_interfaces::msg::Controls::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_Controls_steering(msg_);
  }

private:
  ::more_interfaces::msg::Controls msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::more_interfaces::msg::Controls>()
{
  return more_interfaces::msg::builder::Init_Controls_speed();
}

}  // namespace more_interfaces

#endif  // MORE_INTERFACES__MSG__DETAIL__CONTROLS__BUILDER_HPP_
