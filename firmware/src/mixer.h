#pragma once

class Mixer {
  public:
    float output;

    void update(float pid_output, float steering_input, float sens_input);
};
