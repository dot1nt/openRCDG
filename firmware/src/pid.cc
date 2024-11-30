#include "pid.h"

#include <Arduino.h>

PidController::PidController(float p, float i, float d, float dFilterCutoff, float loopTime)
    : Kp(p), Ki(i), Kd(d), loopTime(loopTime), dFilter(dFilterCutoff, loopTime) {};

float PidController::update(float data) {
  error = data;

  proportional = error;
  integral += error * loopTime;
  integral = constrain(integral, -50.0f, 50.0f);

  derivative = (error - lastError) / loopTime;
  float derivativeFiltered = dFilter.update(derivative);

  float output = Kp * proportional + Ki * integral + Kd * derivativeFiltered;

  lastError = error;

  return output;
}
