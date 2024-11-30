#pragma once

class Curve {
public:
  typedef enum {
    LINEAR,
    SIN,
    LOG,
    CUSTOM,
  } CurveType;

  void setCurveType(CurveType curveType);
  void setCustomCurve(float *curve);
  float getValue(float x);

private:
  CurveType curveType = LINEAR;
  float *customCurve = nullptr;
};