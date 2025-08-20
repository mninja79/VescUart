import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.components import sensor
from esphome.components import binary_sensor
# Correct import path for the PollingComponent base class
from esphome.components.component import PollingComponent
from esphome.const import CONF_ID, CONF_UPDATE_INTERVAL

# The UART dependency is still correct
DEPENDENCIES = ["uart"]

# Define the namespace and classes for the C++ code
vesc_uart_ns = cg.esphome_ns.namespace("vesc_uart")
# Use the correct base class from the imported module
VescUartComponent = vesc_uart_ns.class_("VescUartComponent", PollingComponent, uart.UARTDevice)

# VESC-specific configuration options.
CONF_VESC_UART_ID = "vesc_uart_id"
CONF_VOLTAGE = "voltage"
CONF_CURRENT = "current"
CONF_POWER = "power"
CONF_RPM = "rpm"
CONF_TEMPERATURE = "temperature"
CONF_AMPHOURS_CONSUMED = "amphours_consumed"
CONF_AMPHOURS_CHARGED = "amphours_charged"
CONF_WATTHOURS_CONSUMED = "watthours_consumed"
CONF_WATTHOURS_CHARGED = "watthours_charged"
CONF_STATUS = "status"

# Configuration schema for the component.
CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(VescUartComponent),
            cv.Optional(CONF_VOLTAGE): sensor.sensor_schema(
                unit_of_measurement="V", accuracy_decimals=2,
                device_class="voltage", state_class="measurement"
            ),
            cv.Optional(CONF_CURRENT): sensor.sensor_schema(
                unit_of_measurement="A", accuracy_decimals=2,
                device_class="current", state_class="measurement"
            ),
            cv.Optional(CONF_POWER): sensor.sensor_schema(
                unit_of_measurement="W", accuracy_decimals=2,
                device_class="power", state_class="measurement"
            ),
            cv.Optional(CONF_RPM): sensor.sensor_schema(
                unit_of_measurement="RPM", accuracy_decimals=0,
                icon="mdi:rotate-3d"
            ),
            cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement="°C", accuracy_decimals=1,
                device_class="temperature", state_class="measurement"
            ),
            cv.Optional(CONF_AMPHOURS_CONSUMED): sensor.sensor_schema(
                unit_of_measurement="Ah", accuracy_decimals=2,
                icon="mdi:current-ac"
            ),
            cv.Optional(CONF_AMPHOURS_CHARGED): sensor.sensor_schema(
                unit_of_measurement="Ah", accuracy_decimals=2,
                icon="mdi:current-ac"
            ),
            cv.Optional(CONF_WATTHOURS_CONSUMED): sensor.sensor_schema(
                unit_of_measurement="Wh", accuracy_decimals=2,
                icon="mdi:flash"
            ),
            cv.Optional(CONF_WATTHOURS_CHARGED): sensor.sensor_schema(
                unit_of_measurement="Wh", accuracy_decimals=2,
                icon="mdi:flash"
            ),
            cv.Optional(CONF_STATUS): binary_sensor.binary_sensor_schema(
                icon="mdi:link"
            ),
        }
    )
    .extend(cv.polling_component_schema(2000))
    .extend(uart.UART_DEVICE_SCHEMA)
)

def to_code(config):
    """
    Generates the C++ code for the ESPHome component.
    """
    # Create a new C++ variable for the VescUartComponent
    var = cg.new_Pvariable(config[CONF_ID])
    # Register the component with the ESPHome framework
    yield cg.register_component(var, config)
    # Register the UART device
    yield uart.register_uart_device(var, config)

    # If the user has configured sensors in the YAML, create the C++ objects and set them on the component.
    if CONF_VOLTAGE in config:
        cg.add(var.set_voltage_sensor(config[CONF_VOLTAGE]))
    if CONF_CURRENT in config:
        cg.add(var.set_current_sensor(config[CONF_CURRENT]))
    if CONF_POWER in config:
        cg.add(var.set_power_sensor(config[CONF_POWER]))
    if CONF_RPM in config:
        cg.add(var.set_rpm_sensor(config[CONF_RPM]))
    if CONF_TEMPERATURE in config:
        cg.add(var.set_temp_sensor(config[CONF_TEMPERATURE]))
    if CONF_AMPHOURS_CONSUMED in config:
        cg.add(var.set_amphours_consumed_sensor(config[CONF_AMPHOURS_CONSUMED]))
    if CONF_AMPHOURS_CHARGED in config:
        cg.add(var.set_amphours_charged_sensor(config[CONF_AMPHOURS_CHARGED]))
    if CONF_WATTHOURS_CONSUMED in config:
        cg.add(var.set_watthours_consumed_sensor(config[CONF_WATTHOURS_CONSUMED]))
    if CONF_WATTHOURS_CHARGED in config:
        cg.add(var.set_watthours_charged_sensor(config[CONF_WATTHOURS_CHARGED]))
    if CONF_STATUS in config:
        cg.add(var.set_status_sensor(config[CONF_STATUS]))
