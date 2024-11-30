#pragma once

#include <Arduino.h>

class Led {
public:
  Led(int pin);
  ~Led();

  void high();
  void low();

  void setupFinished();
  void blink(int times);

private:
  static constexpr int BLINK_DELAY = 200; // ms

  int pin;
};
