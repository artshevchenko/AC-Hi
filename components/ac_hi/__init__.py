import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

DEPENDENCIES = ['uart']
AUTO_LOAD = ['sensor', 'text_sensor', 'number', 'select', 'switch', 'climate']

ac_hi_ns = cg.esphome_ns.namespace('ac_hi')
ACHi = ac_hi_ns.class_('ACHi', cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ACHi),
}).extend(uart.UART_DEVICE_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], cg.get_variable(config[uart.CONF_UART_ID]))
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)