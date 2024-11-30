#pragma once

class PT1Filter {
public:
  PT1Filter(float cutoffFrequency, float loopTime);
  float update(float data);

private:
  float k;
  float lastOutput;
};