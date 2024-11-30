#include "filter.h"

#include <Arduino.h>

PT1Filter::PT1Filter(float cutoffFrequency, float loopTime) {
  float o = 2.0f * PI * cutoffFrequency * loopTime;
  k = o / (o + 1.0f);
}

float PT1Filter::update(float data) {
  lastOutput = lastOutput + k * (data - lastOutput);
  return lastOutput;
}