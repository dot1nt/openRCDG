#pragma once

#include <Arduino.h>

class PwmReader {
public:
  PwmReader(int pin);

  void update();
  unsigned long getValue();

private:
  int pin;
  unsigned long value = 1500;

  bool high;
  unsigned long risingStart;
};