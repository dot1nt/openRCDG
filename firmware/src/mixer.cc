#include "mixer.h"

#include <Arduino.h>

#include "utils.h"

Mixer::Mixer(Curve &gyroCurve, Endpoints &endpoints, bool reverse)
    : gyroCurve(gyroCurve), endpoints(endpoints), reverse(reverse) {};

float Mixer::update(float pidOutput, float steeringInput, float sensitivityInput) {
  float steeringInputNormalized = endpoints.mapToNormalized(steeringInput);
  float sensitivityInputNormalized = abs(mapf(sensitivityInput, 1500.0f, 2000.0f, 0.0f, 1.0f));

  float output = mapf(pidOutput * sensitivityInputNormalized, -1000.0f, 1000.0f, -1.0f, 1.0f);
  output = reverse ? output : -output;
  output = constrain(output, -1.0f, 1.0f);
  output = gyroCurve.getValue(output);
  output = constrain(output + steeringInputNormalized, -1.0f, 1.0f);
  output = endpoints.mapToEndpoints(output);

  return output;
}
