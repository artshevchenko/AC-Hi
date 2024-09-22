import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, binary_sensor, text_sensor, uart
from esphome.const import *
ac_hi_ns = cg.esphome_ns.namespace('ac_hi')
ACHiComponent = ac_hi_ns.class_('ACHiComponent', cg.PollingComponent)

DEPENDENCIES = ['uart']
AUTO_LOAD = ['uart', 'sensor', 'text_sensor', 'binary_sensor']