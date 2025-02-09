
#pragma once

#include <type_traits>
#include <concepts>

#include "device.hpp"

namespace mgmt::device {
template<class T>
concept TempSensor = Device<T> and requires(T obj)
{
  {
    obj.value()
    } -> std::same_as<float>;
};

}// namespace mgmt::device
