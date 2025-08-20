import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.components import polling_component
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

vesc_uart_ns = cg.esphome_ns.namespace("vesc_uart")
VescUART = vesc_uart_ns.class_("VescUART", polling_component.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(VescUART),
        }
    )
    .extend(polling_component.polling_component_schema(2000))
    .extend(uart.UART_DEVICE_SCHEMA)
)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)