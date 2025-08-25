# ESPHome VESC UART Component

This is an external component for ESPHome to interface with a VESC motor controller over UART. It allows you to monitor various parameters of your VESC directly in Home Assistant.

This component is based on the [VescUart](https://github.com/SolidGeek/VescUart) library and wraps it for easy use within the ESPHome framework.

## Features

This component exposes the following sensors from the VESC:

*   **Voltage:** The input voltage of the VESC.
*   **Motor Current:** The current flowing through the motor.
*   **Input Current:** The current being drawn by the VESC from the power supply.
*   **RPM:** The speed of the motor in revolutions per minute.
*   **Motor Temperature:** The temperature of the motor.
*   **Controller Temperature:** The temperature of the VESC controller.

## Hardware Dependencies

*   An ESP32 or ESP8266 board.
*   A VESC-based motor controller with firmware FW5 or newer.
*   A UART connection between the ESP board and the VESC.

## Installation

You can install this component using the `external_components` feature of ESPHome. Add the following to your ESPHome YAML configuration:

```yaml
external_components:
  - source:
      type: local
      path: /path/to/your/components/VescUart
```

Replace `/path/to/your/components/VescUart` with the actual path to this component on your system.

## Configuration

Here is an example of how to configure the `vesc_uart` component in your ESPHome YAML file:

```yaml
uart:
  id: uart_bus
  tx_pin: GPIO1
  rx_pin: GPIO3
  baud_rate: 115200

vesc_uart:
  id: my_vesc
  uart_id: uart_bus
  timeout: 100ms
  voltage_sensor:
    name: "VESC Voltage"
  motor_current_sensor:
    name: "VESC Motor Current"
  input_current_sensor:
    name: "VESC Input Current"
  rpm_sensor:
    name: "VESC RPM"
  motor_temperature_sensor:
    name: "VESC Motor Temperature"
  controller_temperature_sensor:
    name: "VESC Controller Temperature"
```

### Configuration Variables

*   **id** (Optional, ID): The ID of the component.
*   **uart_id** (Required, ID): The ID of the UART bus to use for communication.
*   **timeout** (Optional, Time): The timeout for waiting for data from the VESC. Defaults to `100ms`.
*   **voltage_sensor** (Optional): The voltage sensor configuration.
*   **motor_current_sensor** (Optional): The motor current sensor configuration.
*   **input_current_sensor** (Optional): The input current sensor configuration.
*   **rpm_sensor** (Optional): The RPM sensor configuration.
*   **motor_temperature_sensor** (Optional): The motor temperature sensor configuration.
*   **controller_temperature_sensor** (Optional): The controller temperature sensor configuration.

All sensor configurations are optional. If you don't configure a sensor, it will not be created.

## Credits

This component is made possible by the underlying `VescUart` library.
