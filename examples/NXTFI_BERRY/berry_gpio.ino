/*
   This is from tasmota
   Template for creating modules
*/

#include <berry.h>
#include <be_mapping.h>
#include <Arduino.h>

const char kTypeError[] PROGMEM = "type_error";

extern "C" {

  const be_const_member_t lv_gpio_constants[] = {

    { "FALLING", (int32_t)FALLING },
    { "HIGH", (int32_t)HIGH },
    { "PULLDOWN", (int32_t)PULLDOWN }, // not working
    { "PULLUP", (int32_t)PULLUP }, // not working
    { "INPUT", (int32_t)INPUT},
    { "INPUT_PULLDOWN", (int32_t)INPUT_PULLDOWN },
    { "INPUT_PULLUP", (int32_t)INPUT_PULLUP },
    { "OUTPUT", (int32_t)OUTPUT },
    { "OUTPUT_OPEN_DRAIN", (int32_t)OUTPUT_OPEN_DRAIN },
    { "RISING", (int32_t)RISING },
    { "LOW", (int32_t)LOW}, // not working
    
  };

  const size_t lv_gpio_constants_size = sizeof(lv_gpio_constants) / sizeof(lv_gpio_constants[0]);

  int gp_member(bvm *vm);
  int gp_member(bvm *vm) {
    if (be_const_module_member(vm, lv_gpio_constants, lv_gpio_constants_size)) {
      be_return(vm);
    } else {
      be_return_nil(vm);
    }
  }
  int gp_pin_mode(bvm *vm);
  int gp_pin_mode(bvm *vm) {
    int32_t argc = be_top(vm);
    if (argc == 2 && be_isint(vm, 1) && be_isint(vm, 2)) {
      int32_t pin = be_toint(vm, 1);
      int32_t mode = be_toint(vm, 2);
      if (pin >= 0) {
        if (mode > 0) {
          // standard ESP mode
          pinMode(pin, mode);
        } else {
          if (-1 == mode) {
            // DAC
          }
        }
      }
      be_return_nil(vm);
    }
    be_raise(vm, kTypeError, nullptr);
  }
  int gp_digital_write(bvm *vm);
  int gp_digital_write(bvm *vm) {
    int32_t argc = be_top(vm);
    if (argc == 2 && be_isint(vm, 1) && be_isint(vm, 2)) {
      int32_t pin = be_toint(vm, 1);
      int32_t val = be_toint(vm, 2);
      if (pin >= 0) {
        digitalWrite(pin, val);
      }
      be_return_nil(vm);
    }
    be_raise(vm, kTypeError, nullptr);
  }
  int gp_digital_read(bvm *vm);
  int gp_digital_read(bvm *vm) {
    be_raise(vm, kTypeError, nullptr);
  }
  int gp_dac_voltage(bvm *vm);
  int gp_dac_voltage(bvm *vm) {
    be_raise(vm, kTypeError, nullptr);
  }
  int gp_pin_used(bvm *vm);
  int gp_pin_used(bvm *vm) {
    be_raise(vm, kTypeError, nullptr);
  }
  int gp_pin(bvm *vm);
  int gp_pin(bvm *vm) {
    be_raise(vm, kTypeError, nullptr);
  }
  void gp_set_duty(int32_t pin, int32_t duty, int32_t hpoint);
  void gp_set_duty(int32_t pin, int32_t duty, int32_t hpoint) {

  }
}
