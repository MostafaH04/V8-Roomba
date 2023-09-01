// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from more_interfaces:msg/Controls.idl
// generated code does not contain a copyright notice
#include "more_interfaces/msg/detail/controls__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
more_interfaces__msg__Controls__init(more_interfaces__msg__Controls * msg)
{
  if (!msg) {
    return false;
  }
  // speed
  // steering
  return true;
}

void
more_interfaces__msg__Controls__fini(more_interfaces__msg__Controls * msg)
{
  if (!msg) {
    return;
  }
  // speed
  // steering
}

bool
more_interfaces__msg__Controls__are_equal(const more_interfaces__msg__Controls * lhs, const more_interfaces__msg__Controls * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // speed
  if (lhs->speed != rhs->speed) {
    return false;
  }
  // steering
  if (lhs->steering != rhs->steering) {
    return false;
  }
  return true;
}

bool
more_interfaces__msg__Controls__copy(
  const more_interfaces__msg__Controls * input,
  more_interfaces__msg__Controls * output)
{
  if (!input || !output) {
    return false;
  }
  // speed
  output->speed = input->speed;
  // steering
  output->steering = input->steering;
  return true;
}

more_interfaces__msg__Controls *
more_interfaces__msg__Controls__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  more_interfaces__msg__Controls * msg = (more_interfaces__msg__Controls *)allocator.allocate(sizeof(more_interfaces__msg__Controls), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(more_interfaces__msg__Controls));
  bool success = more_interfaces__msg__Controls__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
more_interfaces__msg__Controls__destroy(more_interfaces__msg__Controls * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    more_interfaces__msg__Controls__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
more_interfaces__msg__Controls__Sequence__init(more_interfaces__msg__Controls__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  more_interfaces__msg__Controls * data = NULL;

  if (size) {
    data = (more_interfaces__msg__Controls *)allocator.zero_allocate(size, sizeof(more_interfaces__msg__Controls), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = more_interfaces__msg__Controls__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        more_interfaces__msg__Controls__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
more_interfaces__msg__Controls__Sequence__fini(more_interfaces__msg__Controls__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      more_interfaces__msg__Controls__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

more_interfaces__msg__Controls__Sequence *
more_interfaces__msg__Controls__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  more_interfaces__msg__Controls__Sequence * array = (more_interfaces__msg__Controls__Sequence *)allocator.allocate(sizeof(more_interfaces__msg__Controls__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = more_interfaces__msg__Controls__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
more_interfaces__msg__Controls__Sequence__destroy(more_interfaces__msg__Controls__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    more_interfaces__msg__Controls__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
more_interfaces__msg__Controls__Sequence__are_equal(const more_interfaces__msg__Controls__Sequence * lhs, const more_interfaces__msg__Controls__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!more_interfaces__msg__Controls__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
more_interfaces__msg__Controls__Sequence__copy(
  const more_interfaces__msg__Controls__Sequence * input,
  more_interfaces__msg__Controls__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(more_interfaces__msg__Controls);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    more_interfaces__msg__Controls * data =
      (more_interfaces__msg__Controls *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!more_interfaces__msg__Controls__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          more_interfaces__msg__Controls__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!more_interfaces__msg__Controls__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
