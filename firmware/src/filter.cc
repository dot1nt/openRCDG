#include <Arduino.h>
#include "filter.h"

void Lpf1::init(float cutoff, float lt) {
  float o = 2.0f * 3.14f * cutoff * lt;
  k = o / (o + 1.0f);
}

void Lpf1::update(float data) {
  output = output + k * (data - output);  
}