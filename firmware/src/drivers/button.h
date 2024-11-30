#pragma once

class Button {
public:
  Button(int pin);
  ~Button();
  
  bool update();
  bool getState();

private:
  static constexpr unsigned long DEBOUNCE_TIME = 100; // ms

  int pin;

  int currentState;
  int lastState;
  unsigned long lastTime;
};