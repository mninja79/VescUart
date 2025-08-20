#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "VescUart.h"

namespace esphome {
namespace vesc_uart {

struct VescData {
    float avgMotorCurrent;
    float avgInputVoltage;
    float rpm;
};

class VescUART : public PollingComponent, public uart::UARTDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;

  VescData data;

 protected:
  VescUart vesc_uart_;
};

} // namespace vesc_uart
} // namespace esphome