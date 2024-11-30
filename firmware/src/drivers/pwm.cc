#include "pwm.h"

#include <Arduino.h>

PwmReader::PwmReader(int pin) : pin(pin) {}

void PwmReader::update() {
  int trigger = digitalRead(pin);

  if (trigger) {
    if (!high) {
      risingStart = micros();
    }

    high = true;
  } else {
    if (high) {
      value = micros() - risingStart;
    }

    high = false;
  }
}

unsigned long PwmReader::getValue() {
  return value;
}
