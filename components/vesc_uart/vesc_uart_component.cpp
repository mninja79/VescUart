// VescUartComponent.cpp

#include "VescUartComponent.h"
#include "esphome/core/log.h"

namespace esphome {
namespace vesc_uart {

VescUartComponent::VescUartComponent() : VescUartComponent(1000) {}

VescUartComponent::VescUartComponent(uint32_t timeout_ms)
    : PollingComponent(1000) {
    this->timeout_ms_ = timeout_ms;
}

VescUartComponent::VescUartComponent(sensor::Sensor *voltage_sensor, sensor::Sensor *current_sensor, sensor::Sensor *power_sensor,
                                     sensor::Sensor *rpm_sensor, sensor::Sensor *temp_sensor, sensor::Sensor *ah_consumed_sensor,
                                     sensor::Sensor *ah_charged_sensor, sensor::Sensor *watt_hours_consumed_sensor,
                                     sensor::Sensor *watt_hours_charged_sensor, sensor::Sensor *status_sensor, uint32_t timeout_ms)
    : PollingComponent(1000) {
    this->voltage_sensor_ = voltage_sensor;
    this->current_sensor_ = current_sensor;
    this->power_sensor_ = power_sensor;
    this->rpm_sensor_ = rpm_sensor;
    this->temp_sensor_ = temp_sensor;
    this->ah_consumed_sensor_ = ah_consumed_sensor;
    this->ah_charged_sensor_ = ah_charged_sensor;
    this->watt_hours_consumed_sensor_ = watt_hours_consumed_sensor;
    this->watt_hours_charged_sensor_ = watt_hours_charged_sensor;
    this->status_sensor_ = status_sensor;
    this->timeout_ms_ = timeout_ms;
}
  
void VescUartComponent::setup() {
  // This function runs once on startup.
  // Initialize the VESC UART library and set up the serial port.
  vesc_uart_.setSerialPort(this);
  vesc_uart_.set_timeout(this->timeout_ms_);
  ESP_LOGCONFIG(TAG, "VESC UART Component initialized with timeout: %u ms", this->timeout_ms_);
  
  // Set an initial value for the status sensor
  if (this->status_sensor_ != nullptr) {
      this->status_sensor_->publish_state(0); // 0 = Not connected
  }
}

void VescUartComponent::update() {
  // This function is called at a regular interval defined by update_interval.
  // It is a more robust way to poll for data than using a non-blocking loop().
  
  ESP_LOGD(TAG, "Requesting VESC telemetry data...");
  
  // Attempt to get VESC values. The VescUart library handles the request/response.
  if (vesc_uart_.getVescValues()) {
    // Data was successfully received from the VESC.
    ESP_LOGD(TAG, "VESC telemetry received!");

    // Publish sensor values. Check if each sensor is configured before publishing.
    if (this->voltage_sensor_ != nullptr) {
      this->voltage_sensor_->publish_state(vesc_uart_.data.inpVoltage);
    }
    if (this->current_sensor_ != nullptr) {
      this->current_sensor_->publish_state(vesc_uart_.data.avgInputCurrent);
    }
    if (this->power_sensor_ != nullptr) {
      this->power_sensor_->publish_state(vesc_uart_.data.inpVoltage * vesc_uart_.data.avgInputCurrent);
    }
    if (this->rpm_sensor_ != nullptr) {
      this->rpm_sensor_->publish_state(vesc_uart_.data.rpm);
    }
    if (this->temp_sensor_ != nullptr) {
      this->temp_sensor_->publish_state(vesc_uart_.data.tempFET + vesc_uart_.data.tempMotor / 2); // Simple average
    }
    if (this->ah_consumed_sensor_ != nullptr) {
      this->ah_consumed_sensor_->publish_state(vesc_uart_.data.ampHours);
    }
    if (this->ah_charged_sensor_ != nullptr) {
      this->ah_charged_sensor_->publish_state(vesc_uart_.data.ampHoursCharged);
    }
    if (this->watt_hours_consumed_sensor_ != nullptr) {
      this->watt_hours_consumed_sensor_->publish_state(vesc_uart_.data.wattHours);
    }
    if (this->watt_hours_charged_sensor_ != nullptr) {
      this->watt_hours_charged_sensor_->publish_state(vesc_uart_.data.wattHoursCharged);
    }
    // Update status sensor to show successful connection.
    if (this->status_sensor_ != nullptr) {
      this->status_sensor_->publish_state(1); // 1 = Connected
    }
  } else {
    // Failed to get data. This could be due to a timeout or other serial error.
    ESP_LOGW(TAG, "Failed to read VESC telemetry. Check connection and power.");
    if (this->status_sensor_ != nullptr) {
      this->status_sensor_->publish_state(0); // 0 = Not connected
    }
  }
}

}  // namespace vesc_uart
}  // namespace esphome