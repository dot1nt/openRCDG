#pragma once

#include "filter.h"

class PidController {
  private:
    float Kp, Ki, Kd;
    float error;
    float last_error;

    float proportional;
    float integral;
    float derivative;
    
    Lpf1 d_filter;

  public:
    float output;

    void init(float *pids);
    void update(float value);
};
