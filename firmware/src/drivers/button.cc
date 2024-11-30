#include "button.h"

#include <Arduino.h>

Button::Button(int pin) : pin(pin) {
  pinMode(pin, INPUT_PULLUP);
}

Button::~Button() {
  pinMode(pin, INPUT);
}

bool Button::update() {
  bool stateChanged = false;
  int state = !digitalRead(pin);

  if (state != lastState) {
    lastTime = millis();
  }

  if ((millis() - lastTime) > DEBOUNCE_TIME) {
    if (state != currentState) {
      currentState = state;

      if (state == 1) {
        stateChanged = true;
      }
    }
  }

  lastState = state;
  return stateChanged;
}

bool Button::getState() {
  return !digitalRead(pin);
}