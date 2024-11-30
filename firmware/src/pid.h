#pragma once

#include "filter.h"

class PidController {
public:
  PidController(float p, float i, float d, float dFilterCutoff, float loopTime);
  float update(float data);

private:
  float Kp, Ki, Kd;
  float loopTime;

  float error;
  float lastError;

  float proportional;
  float integral;
  float derivative;

  PT1Filter dFilter;
};
