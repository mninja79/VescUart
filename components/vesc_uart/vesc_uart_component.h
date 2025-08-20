// VescUartComponent.h

#ifndef VESC_UART_COMPONENT_H
#define VESC_UART_COMPONENT_H

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "VescUart.h"

namespace esphome {
namespace vesc_uart {

static const char *TAG = "vesc_uart";

class VescUartComponent : public PollingComponent, public uart::UARTDevice {
 public:
  // Default constructor with a timeout of 1000ms.
  VescUartComponent();
  // Constructor with a configurable timeout.
  VescUartComponent(uint32_t timeout_ms);
  // Full constructor for all sensors and timeout.
  VescUartComponent(sensor::Sensor *voltage_sensor, sensor::Sensor *current_sensor, sensor::Sensor *power_sensor,
                    sensor::Sensor *rpm_sensor, sensor::Sensor *temp_sensor, sensor::Sensor *ah_consumed_sensor,
                    sensor::Sensor *ah_charged_sensor, sensor::Sensor *watt_hours_consumed_sensor,
                    sensor::Sensor *watt_hours_charged_sensor, sensor::Sensor *status_sensor, uint32_t timeout_ms = 1000);

  // ESPHome component lifecycle methods.
  void setup() override;
  void update() override;

 protected:
  VescUart vesc_uart_;
  uint32_t timeout_ms_;
  sensor::Sensor *voltage_sensor_{nullptr};
  sensor::Sensor *current_sensor_{nullptr};
  sensor::Sensor *power_sensor_{nullptr};
  sensor::Sensor *rpm_sensor_{nullptr};
  sensor::Sensor *temp_sensor_{nullptr};
  sensor::Sensor *ah_consumed_sensor_{nullptr};
  sensor::Sensor *ah_charged_sensor_{nullptr};
  sensor::Sensor *watt_hours_consumed_sensor_{nullptr};
  sensor::Sensor *watt_hours_charged_sensor_{nullptr};
  sensor::Sensor *status_sensor_{nullptr};
};

}  // namespace vesc_uart
}  // namespace esphome

#endif  // VESC_UART_COMPONENT_H