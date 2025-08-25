import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import (
    CONF_ID,
    CONF_TIMEOUT,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_EMPTY,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_VOLTAGE,
    STATE_CLASS_MEASUREMENT,
    UNIT_AMPERE,
    UNIT_CELSIUS,
    UNIT_EMPTY,
    UNIT_VOLT,
)

DEPENDENCIES = ["uart"]

vesc_uart_ns = cg.esphome_ns.namespace("vesc_uart")
VescUartComponent = vesc_uart_ns.class_("VescUartComponent", cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(VescUartComponent),
            cv.Optional(CONF_TIMEOUT, default="100ms"): cv.positive_time_period_milliseconds,
            cv.Optional("voltage_sensor"): sensor.sensor_schema(
                unit_of_measurement=UNIT_VOLT,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_VOLTAGE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional("motor_current_sensor"): sensor.sensor_schema(
                unit_of_measurement=UNIT_AMPERE,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_CURRENT,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional("input_current_sensor"): sensor.sensor_schema(
                unit_of_measurement=UNIT_AMPERE,
                accuracy_decimals=2,
                device_class=DEVICE_CLASS_CURRENT,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional("rpm_sensor"): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional("motor_temperature_sensor"): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional("controller_temperature_sensor"): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
        }
    ).extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
    
    cg.add(var.set_timeout(config[CONF_TIMEOUT]))
    
    if voltage_config := config.get("voltage_sensor"):
        sens = await sensor.new_sensor(voltage_config)
        cg.add(var.set_voltage_sensor(sens))
    
    if motor_current_config := config.get("motor_current_sensor"):
        sens = await sensor.new_sensor(motor_current_config)
        cg.add(var.set_motor_current_sensor(sens))
    
    if input_current_config := config.get("input_current_sensor"):
        sens = await sensor.new_sensor(input_current_config)
        cg.add(var.set_input_current_sensor(sens))
    
    if rpm_config := config.get("rpm_sensor"):
        sens = await sensor.new_sensor(rpm_config)
        cg.add(var.set_rpm_sensor(sens))
    
    if motor_temp_config := config.get("motor_temperature_sensor"):
        sens = await sensor.new_sensor(motor_temp_config)
        cg.add(var.set_motor_temperature_sensor(sens))
    
    if controller_temp_config := config.get("controller_temperature_sensor"):
        sens = await sensor.new_sensor(controller_temp_config)
        cg.add(var.set_controller_temperature_sensor(sens))