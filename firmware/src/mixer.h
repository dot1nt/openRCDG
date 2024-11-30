#pragma once

#include "curve.h"
#include "endpoints.h"

class Mixer {
public:
  Mixer(Curve &gyroCurve, Endpoints &endpoints, bool reverse);
  float update(float pidOutput, float steeringInput, float sensitivityInput);

private:
  Curve &gyroCurve;
  Endpoints &endpoints;
  bool reverse;
};
