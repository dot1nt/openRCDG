#include <Arduino.h>
#include <utils.h>

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float mapf3(float x, float *inp_end, float *out_end) {
  float out;

  if (inp_end[1] > x) {
    out = mapf(x, inp_end[0], inp_end[1], out_end[0], out_end[1]);
  } else {
    out = mapf(x, inp_end[1], inp_end[2], out_end[1], out_end[2]);
  }

  return out;
}
