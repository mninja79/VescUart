#include "vesc_uart_component.h"
#include "esphome/core/log.h"
#include "VescUart.h"

namespace esphome {
namespace vesc_uart {

static const char *TAG = "vesc_uart";

void VescUART::setup() {
  this->set_uart_device(this);
  ESP_LOGCONFIG(TAG, "VESC UART Component is being set up.");
}

void VescUART::update() {
    if (this->available()) {
        int success = vesc_uart_.getVescValues();
        if (success == 1) {
            this->data.avgMotorCurrent = vesc_uart_.data.avgMotorCurrent;
            this->data.avgInputVoltage = vesc_uart_.data.avgInputVoltage;
            this->data.rpm = vesc_uart_.data.rpm;
            ESP_LOGD(TAG, "VESC Data: Current=%.2fA, Voltage=%.2fV, RPM=%.0f", this->data.avgMotorCurrent, this->data.avgInputVoltage, this->data.rpm);
        } else {
            ESP_LOGW(TAG, "Failed to read VESC values. Error code: %d", success);
        }
    }
}

void VescUART::dump_config() {
  ESP_LOGCONFIG(TAG, "VESC UART:");
  LOG_UART_DEVICE(this);
  ESP_LOGCONFIG(TAG, "  Update Interval: %dms", this->get_update_interval());
}

} // namespace vesc_uart
} // namespace esphome