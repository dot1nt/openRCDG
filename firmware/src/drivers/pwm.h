#pragma once

#include <Arduino.h>

class PwmReader {
  private:
    bool high;
    unsigned long rising_start;

  public:
    int pin;
    float output;

    PwmReader(int pwm_pin);

    void update();
};