#include <Arduino.h>
#include "pwm.h"

PwmReader::PwmReader(int pwm_pin) { pin = pwm_pin; }

void PwmReader::update() {
  int trigger = digitalRead(pin);

  if (trigger) {
    if (!high) {
      rising_start = micros();      
    }

    high = true;
  } else {
    if (high) {
      output = micros()-rising_start;
    }

    high = false;
  }
}
