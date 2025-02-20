//
// Created by pp on 7/24/22.
//

#include <main_board/device/sysfs_rgbled.hpp>
#include <device/logger.hpp>

namespace mgmt::device {
SysfsRGBLed::SysfsRGBLed(SysfsLed red, SysfsLed green, SysfsLed blue)
  : red_{ std::move(red) }
  , green_{ std::move(green) }
  , blue_{ std::move(blue) }
{}

RGBLedValue SysfsRGBLed::brightness() const
{
  common::logger::get(mgmt::device::Logger)->trace("SysfsRGBLed::{}", __FUNCTION__);

  return RGBLedValue{
    .red = red_.brightness(),
    .green = green_.brightness(),
    .blue = blue_.brightness()
  };
}

void SysfsRGBLed::set_brightness(const RGBLedValue& value)
{
  common::logger::get(mgmt::device::Logger)->trace("SysfsRGBLed::{}", __FUNCTION__);

  red_.set_brightness(value.red);
  green_.set_brightness(value.green);
  blue_.set_brightness(value.blue);
}
}// namespace mgmt::device
