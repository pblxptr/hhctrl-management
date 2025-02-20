#pragma once

#include <spdlog/spdlog.h>

#include <device/temp_sensor.hpp>
#include <device/indicator_t.hpp>
#include <device/logger.hpp>
#include <main_board/device/main_board.hpp>
#include <main_board/platform/device_loader.hpp>

namespace mgmt::platform_device {
template<class GenericDeviceProcessor>
class PlatformBuilder
{
public:
  void add_device(mgmt::device::Indicator_t indicator)
  {
    common::logger::get(mgmt::device::Logger)->debug("PlatformBuilder::{}(Indicator_t)", __FUNCTION__);

    indicators_.push_back(std::move(indicator));
  }

  template<class D>
  void add_loader(DeviceLoader&& dev_loader)
  {
    common::logger::get(mgmt::device::Logger)->debug("PlatformBuilder::{}", __FUNCTION__);

    auto generic_loader = [dev_loader = std::move(dev_loader)](const GenericDeviceProcessor& processor) mutable -> bool {
      return processor.template handle<D>(std::move(dev_loader));
    };

    generic_loaders_.push_back(std::move(generic_loader));
  }

  auto build_board() &&
  {
    common::logger::get(mgmt::device::Logger)->debug("PlatformBuilder::{}", __FUNCTION__);

    return mgmt::device::MainBoard{ std::move(indicators_) };
  }

  auto build_generic_loaders() &&
  {
    common::logger::get(mgmt::device::Logger)->debug("PlatformBuilder::{}", __FUNCTION__);

    return std::move(generic_loaders_);
  }

private:
  std::vector<mgmt::device::Indicator_t> indicators_;
  std::vector<std::function<bool(const GenericDeviceProcessor&)>> generic_loaders_;
};
}// namespace mgmt::platform_device
