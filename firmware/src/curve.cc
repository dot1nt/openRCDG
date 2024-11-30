#include "curve.h"

#include <Arduino.h>

void Curve::setCurveType(CurveType curveType) {
  this->curveType = curveType;
}

void Curve::setCustomCurve(float *curve) {
  customCurve = curve;
  curveType = CurveType::CUSTOM;
}

float Curve::getValue(float x) {
  switch (curveType) {
  case LINEAR:
    return x;

  case SIN:
    return sin(0.5f * x * PI);

  case LOG: {
    float y = log10(9 * abs(x) + 1);
    return x < 0.0f ? -y : y;
  }

  case CUSTOM: {
    float absx = abs(x);

    for (int i = 0; i < 10; i++) {
      float x0 = 0.1f * i;
      float x1 = 0.1f * (i + 1);

      float y0 = customCurve[i];
      float y1 = customCurve[i + 1];

      if (x0 < absx && x1 >= absx) {
        float o = (y0 * (x1 - abs(x)) + y1 * (abs(x) - x0)) / (x1 - x0);
        return (x < 0.0f) ? -o : o;
      }
    }

    return x;
  }

  default:
    return x;
  }
}