#include "vesc_uart_component.h"
#include "esphome/core/log.h"
#include <string>

namespace esphome {
namespace vesc_uart {

static const char *const TAG = "vesc_uart";

void VescUartComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up VESC UART...");
  this->check_uart_settings(9600); // VESC UART is typically 9600 baud
  // Use the correct method to get hardware serial from ESPHome UART component
#ifdef USE_ESP32
  this->vesc_uart_.setSerialPort(&Serial2); // or appropriate HardwareSerial instance
#elif defined(USE_ESP8266)
  this->vesc_uart_.setSerialPort(&Serial);
#else
  // For other platforms, you might need to use ESPHome's UART methods directly
  ESP_LOGE(TAG, "Platform not supported for direct hardware serial access");
#endif
}

void VescUartComponent::loop() {
  if (this->available()) {
    uint8_t payload[256];
    int payload_length = this->vesc_uart_.receiveUartMessage(payload);

    if (payload_length > 0) {
      this->vesc_uart_.processReadPacket(payload);
      
      // Check and publish sensor values
      if (this->voltage_sensor_) {
        this->voltage_sensor_->publish_state(this->vesc_uart_.data.inpVoltage);
      }
      if (this->motor_current_sensor_) {
        this->motor_current_sensor_->publish_state(this->vesc_uart_.data.avgMotorCurrent);
      }
      if (this->input_current_sensor_) {
        this->input_current_sensor_->publish_state(this->vesc_uart_.data.avgInputCurrent);
      }
      if (this->rpm_sensor_) {
        this->rpm_sensor_->publish_state(this->vesc_uart_.data.rpm);
      }
      if (this->motor_temperature_sensor_) {
        this->motor_temperature_sensor_->publish_state(this->vesc_uart_.data.tempMotor);
      }
      if (this->controller_temperature_sensor_) {
        this->controller_temperature_sensor_->publish_state(this->vesc_uart_.data.tempMosfet);
      }

      ESP_LOGD(TAG, "Received VESC data: avgMotorCurrent=%.2f, rpm=%.0f, inputVoltage=%.2f",
               this->vesc_uart_.data.avgMotorCurrent,
               this->vesc_uart_.data.rpm,
               this->vesc_uart_.data.inpVoltage);
    }
  }
}

void VescUartComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "VESC UART Component:");
  ESP_LOGCONFIG(TAG, "  Timeout: %dms", this->timeout_ms_);
  LOG_SENSOR("  ", "Voltage Sensor", this->voltage_sensor_);
  LOG_SENSOR("  ", "Motor Current Sensor", this->motor_current_sensor_);
  LOG_SENSOR("  ", "Input Current Sensor", this->input_current_sensor_);
  LOG_SENSOR("  ", "RPM Sensor", this->rpm_sensor_);
  LOG_SENSOR("  ", "Motor Temperature Sensor", this->motor_temperature_sensor_);
  LOG_SENSOR("  ", "Controller Temperature Sensor", this->controller_temperature_sensor_);
}

float VescUartComponent::get_setup_priority() const { 
  return setup_priority::LATE; 
}

}  // namespace vesc_uart
}  // namespace esphome