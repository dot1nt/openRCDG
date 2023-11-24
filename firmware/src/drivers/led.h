#pragma once

#include <Arduino.h>

class Led {
  private:
    int pin;

  public:
    Led(int led_pin);

    void high();
    void low();

    void setup_finished();
    void blink(int times);
};
