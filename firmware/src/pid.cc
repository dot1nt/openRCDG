#include <Arduino.h>
#include "pid.h"

#include "config.h"

void PidController::init(float *pids) {
  d_filter.init(GYRO_D_FILTER_CUTOFF, LOOP_TIME * 1e-6);

  Kp = pids[0];
  Ki = pids[1];
  Kd = pids[2];
};

void PidController::update(float value) {
  error = value;

  proportional = error;
  integral += error * LOOP_TIME * 1e-6f;
  integral = constrain(integral, -50, 50);

  derivative = (error - last_error) / (LOOP_TIME * 1e-4f);
  d_filter.update(derivative);

  output = Kp * proportional + Ki * integral + Kd * d_filter.output;

  last_error = error;
}
