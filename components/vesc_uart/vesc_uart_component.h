#ifndef ESPHOME_VESC_UART_COMPONENT_H
#define ESPHOME_VESC_UART_COMPONENT_H

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "VescUart.h"

namespace esphome {
namespace vesc_uart {

class VescUartComponent : public Component, public uart::UARTDevice {
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
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override;

  void set_timeout(uint32_t timeout_ms) { this->timeout_ms_ = timeout_ms; }

  void set_voltage_sensor(sensor::Sensor *voltage_sensor) { this->voltage_sensor_ = voltage_sensor; }
  void set_motor_current_sensor(sensor::Sensor *motor_current_sensor) { this->motor_current_sensor_ = motor_current_sensor; }
  void set_input_current_sensor(sensor::Sensor *input_current_sensor) { this->input_current_sensor_ = input_current_sensor; }
  void set_rpm_sensor(sensor::Sensor *rpm_sensor) { this->rpm_sensor_ = rpm_sensor; }
  void set_motor_temperature_sensor(sensor::Sensor *motor_temperature_sensor) { this->motor_temperature_sensor_ = motor_temperature_sensor; }
  void set_controller_temperature_sensor(sensor::Sensor *controller_temperature_sensor) { this->controller_temperature_sensor_ = controller_temperature_sensor; }

 protected:
  VescUart vesc_uart_{};
  uint32_t timeout_ms_{100};

  sensor::Sensor *voltage_sensor_{nullptr};
  sensor::Sensor *motor_current_sensor_{nullptr};
  sensor::Sensor *input_current_sensor_{nullptr};
  sensor::Sensor *rpm_sensor_{nullptr};
  sensor::Sensor *motor_temperature_sensor_{nullptr};
  sensor::Sensor *controller_temperature_sensor_{nullptr};
};

}  // namespace vesc_uart
}  // namespace esphome

#endif  // ESPHOME_VESC_UART_COMPONENT_H