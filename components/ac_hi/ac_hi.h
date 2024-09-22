#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/number/number.h"
#include "esphome/components/select/select.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/climate/climate.h"

namespace esphome {
namespace ac_hi {

class ACHi : public PollingComponent, public UARTDevice {
 public:
  ACHi(UARTComponent *parent);

  void setup() override;
  void loop() override;
  void update() override;

  // Control methods
  void set_power(bool power);
  void set_temperature(float temperature);
  void set_mode(const std::string &mode);
  void set_fan_speed(const std::string &speed);
  void set_sleep_mode(const std::string &sleep_mode);
  void set_quiet_mode(bool quiet);
  void set_turbo_mode(bool turbo);
  void set_eco_mode(bool eco);
  void set_led(bool led);
  void set_swing_up_down(bool swing);
  void set_swing_left_right(bool swing);

  // Sensors
  Sensor *sensor_wind;
  Sensor *sensor_sleep;
  Sensor *sensor_mode;
  Sensor *temp_set;
  Sensor *temp_current;
  Sensor *compr_freq_set;
  Sensor *compr_freq;
  Sensor *temp_outdoor;
  Sensor *temp_outdoor_condenser;
  Sensor *sensor_quiet;
  Sensor *sensor_turbo;
  Sensor *sensor_led;
  Sensor *sensor_eco;
  Sensor *temp_pipe_current;
  Sensor *sensor_left_right;
  Sensor *sensor_up_down;

  // Text Sensors
  TextSensor *power_status;

  // Number (Temperature Control)
  Number *my_temperature;

  // Selects
  Select *ac_mode_select;
  Select *ac_wind_select;
  Select *ac_sleep_select;

  // Switches
  Switch *power_switch;
  Switch *quiet_switch;
  Switch *turbo_switch;
  Switch *eco_switch;
  Switch *led_switch;
  Switch *swing_up_down_switch;
  Switch *swing_left_right_switch;

  // Climate
  //climate::Climate *climate_device;
  public:
    climate::Climate *climate_device = new climate::Climate();

  // Callback methods for component events
  void on_my_temperature_value(float value);
  void on_ac_mode_select_value(const std::string &value);
  void on_ac_wind_select_value(const std::string &value);
  void on_ac_sleep_select_value(const std::string &value);
  void on_power_switch_state(bool state);
  void on_quiet_switch_state(bool state);
  void on_turbo_switch_state(bool state);
  void on_eco_switch_state(bool state);
  void on_led_switch_state(bool state);
  void on_swing_up_down_switch_state(bool state);
  void on_swing_left_right_switch_state(bool state);

  // Climate control methods
  void on_climate_call(climate::ClimateCall &call);

 private:
  // Variables previously defined as globals
  bool current_power_;
  uint8_t current_set_temp_;
  std::string current_ac_mode_;
  std::string current_wind_;
  std::string current_sleep_;

  bool lock_update_;
  bool write_changes_;

  uint8_t power_bin_;
  uint8_t mode_bin_;
  uint8_t updown_bin_;
  uint8_t leftright_bin_;
  uint8_t turbo_bin_;
  uint8_t eco_bin_;
  uint8_t quiet_bin_;
  uint8_t led_bin_;

  std::vector<uint8_t> bytearray_;

  // Helper methods
  void send_read_command();
  void process_incoming_data(const std::vector<uint8_t> &data);
  void write_changes();
  void schedule_write_changes();

  // Timer for periodic actions
  uint32_t last_read_time_;
  uint32_t last_write_time_;

  // Other necessary variables
  int status_crc_;

  // Decoding arrays
  const std::string decode_acmode_codes_[8] = {"fan_only", "heat", "cool", "dry", "auto", "auto", "auto", "auto"};
  const std::string decode_wind_codes_[19] = {"off", "auto", "auto", "", "", "", "", "", "", "", "lowest", "", "low", "", "medium", "", "high", "", "highest"};
  const std::string decode_sleep_codes_[5] = {"off", "sleep_1", "sleep_2", "sleep_3", "sleep_4"};

  // Encoding arrays
  const uint8_t mode_codes_[5] = {0, 1, 2, 3, 4};
  const uint8_t wind_codes_[7] = {0, 1, 10, 12, 14, 16, 18};
  const uint8_t sleep_codes_[5] = {0, 1, 2, 4, 8};

  // Helper variables
  bool pending_write_;
};

}  // namespace ac_hi
}  // namespace esphome