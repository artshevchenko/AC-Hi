import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, binary_sensor, text_sensor, uart
from esphome.const import *

DEPENDENCIES = ['uart']
AUTO_LOAD = ['sensor', 'text_sensor', 'number', 'select', 'switch', 'climate']

CONF_TEMP_CURRENT = "temp_current"
CONF_TEMP_OUTDOOR = "temp_outdoor"

ac_hi_ns = cg.esphome_ns.namespace('ac_hi')
ACHi = ac_hi_ns.class_('ACHi', cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ACHi),

    cv.Optional(CONF_TEMP_CURRENT):
        sensor.sensor_schema(device_class=DEVICE_CLASS_TEMPERATURE,unit_of_measurement=UNIT_CELSIUS,accuracy_decimals=1,state_class=STATE_CLASS_MEASUREMENT).extend(),

    cv.Optional(CONF_TEMP_OUTDOOR):
        sensor.sensor_schema(device_class=DEVICE_CLASS_TEMPERATURE,unit_of_measurement=UNIT_CELSIUS,accuracy_decimals=1,state_class=STATE_CLASS_MEASUREMENT).extend(),
}).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    uart_component = await cg.get_variable(config[uart.CONF_UART_ID])
    var = cg.new_Pvariable(config[CONF_ID], uart_component)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_TEMP_CURRENT in config:
        conf = config[CONF_TEMP_CURRENT]
        sens = await sensor.new_sensor(conf)
        cg.add(var.set_temp_current_sensor(sens))
    
    if CONF_TEMP_OUTDOOR in config:
        conf = config[CONF_TEMP_OUTDOOR]
        sens = await sensor.new_sensor(conf)
        cg.add(var.set_temp_outdoor_sensor(sens))