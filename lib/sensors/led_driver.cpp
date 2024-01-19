#include "led_driver.hpp"

namespace hyped::sensors {

std::optional<LedDriver> LedDriver::create(core::ILogger &logger,
                                           std::shared_ptr<io::II2c> i2c,
                                           const std::uint8_t device_address)
{
    if (device_address != kDefaultLedDriverAddress) {
        logger.log(core::LogLevel::kFatal, "Invalid device address for LED driver");
        return std::nullopt;
    }

    auto ledDriver = LedDriver(logger, i2c, device_address);
    if (auto init_result = ledDriver.initialise(); !init_result) {
        logger.log(core::LogLevel::kFatal, "Failed to initialise LED driver");
        return std::nullopt;
    }

    logger.log(core::LogLevel::kDebug, "Successfully initialised LED driver");
    
    return LedDriver;
}


LedDriver::LedDriver(core::ILogger &logger, std::shared_ptr<io::II2c> i2c, const std::uint8_t device_address)
    : logger_(logger),
      i2c_(i2c),
      device_address_(device_address)
{
}

LedDriver::~LedDriver()
{
}

std::optional<core::Result> LedDriver::initialise()
{
    const auto write_led_control_result = i2c_->writeByteToRegister(device_address_, kLEDControlRegister, 0x00);

    if (write_led_control_result == core::Result::kFailure) {
        logger_.log(core::LogLevel::kFatal, "Failed to initialise LED driver");
        return std::nullopt;
    }

    return core::Result::kSuccess;
}

std::optional<core::Result> LedDriver::set_colour(std::uint8_t channel, std::uint8_t red, std::uint8_t green, std::uint8_t blue)
{
    const auto write_red_result = i2c_->writeByteToRegister(device_address_, kColorRegisterBase + channel, red);
    const auto write_green_result = i2c_->writeByteToRegister(device_address_, kColorRegisterBase + channel + 1, green);
    const auto write_blue_result = i2c_->writeByteToRegister(device_address_, kColorRegisterBase + channel + 2, blue);

    if (write_red_result == core::Result::kFailure || write_green_result == core::Result::kFailure || write_blue_result == core::Result::kFailure) {
        logger_.log(core::LogLevel::kFatal, "Failed to set color for LED channel %d", channel);
        return std::nullopt;
    }

    return core::Result::kSuccess;
}

std::optional<core::Result> LedDriver::set_intensity(std::uint8_t channel, std::uint8_t intensity)
{
    const auto write_intensity_result = i2c_->writeByteToRegister(device_address_, kBrightnessRegisterBase + channel, intensity);

    if (write_intensity_result == core::Result::kFailure) {
        logger_.log(core::LogLevel::kFatal, "Failed to set intensity for LED channel %d", channel);
        return std::nullopt;
    }

    return core::Result::kSuccess;
}

std::optional<core::Result> LedDriver::reset()
{
    const auto write_reset_result = i2c_->writeByteToRegister(device_address_, kResetRegister, 0x00);

    if (write_reset_result == core::Result::kFailure) {
        logger_.log(core::LogLevel::kFatal, "Failed to perform a reset for the LED driver");
        return std::nullopt;
    }

    return core::Result::kSuccess;
}

}  // namespace hyped::drivers