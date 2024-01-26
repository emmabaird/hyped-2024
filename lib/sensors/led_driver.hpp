#pragma once

#include "i2c_sensors.hpp"

#include <cstdint>
#include <memory>
#include <optional>

#include <core/logger.hpp>
#include <io/i2c.hpp>

static constexpr std::uint8_t kDefaultLedDriverAddress = 0x30;

namespace hyped::sensors {
class LedDriver {
 public:
  static std::optional<LedDriver> create(core::ILogger &logger, std::shared_ptr<io::II2c> i2c);
  ~LedDriver();

  core::Result initialise();
  core::Result setColour(std::uint8_t channel,
                         std::uint8_t red,
                         std::uint8_t green,
                         std::uint8_t blue);
  core::Result setIntensity(std::uint8_t channel, std::uint8_t intensity);
  core::Result reset();

 private:
  LedDriver(core::ILogger &logger, std::shared_ptr<io::II2c> i2c);

 private:
  core::ILogger &logger_;
  std::shared_ptr<io::II2c> i2c_;
  const std::uint8_t device_address_ = kDefaultLedDriverAddress;

 private:
  static constexpr std::uint8_t kLEDControlRegister     = 0x02;
  static constexpr std::uint8_t kBrightnessRegisterBase = 0x08;
  static constexpr std::uint8_t kColorRegisterBase      = 0x14;
  static constexpr std::uint8_t kResetRegister          = 0x38;
};
}  // namespace hyped::sensors