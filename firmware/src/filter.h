#pragma once

class Lpf1 {
  private:
    float k;

  public:
    float output;

    void init(float cutoff, float lt);
    void update(float data);
};