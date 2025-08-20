import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID, CONF_UPDATE_INTERVAL

DEPENDENCIES = ["uart"]

vesc_uart_ns = cg.esphome_ns.namespace("vesc_uart")
VescUART = vesc_uart_ns.class_("VescUART", cg.PollingComponent, uart.UARTDevice)
VescData = vesc_uart_ns.struct("VescData")

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(VescUART),
        }
    )
    .extend(cv.PollingComponent.polling_schema(CONF_UPDATE_INTERVAL))
    .extend(uart.UART_DEVICE_SCHEMA)
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)