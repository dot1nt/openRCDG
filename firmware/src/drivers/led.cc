#include <Arduino.h>
#include "led.h"

Led::Led(int led_pin) {
  pin = led_pin;
  pinMode(pin, OUTPUT);
}

void Led::high() {
  digitalWrite(pin, HIGH);
}

void Led::low() {
  digitalWrite(pin, LOW);
}

void Led::setup_finished() {
  blink(2);
  high();
}

void Led::blink(int times) {
  int t = 200;

  for (int i = 0; i < times; i++) {
    high();
    delay(t);
    low();
    delay(t);
  }
}