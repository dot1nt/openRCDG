#include "led.h"

#include <Arduino.h>

Led::Led(int pin) : pin(pin) {
  pinMode(pin, OUTPUT);
}

Led::~Led() {
  pinMode(pin, INPUT);
}

void Led::high() {
  digitalWrite(pin, HIGH);
}

void Led::low() {
  digitalWrite(pin, LOW);
}

void Led::setupFinished() {
  blink(2);
  high();
}

void Led::blink(int times) {
  for (int i = 0; i < times; i++) {
    high();
    delay(BLINK_DELAY);
    low();
    delay(BLINK_DELAY);
  }
}