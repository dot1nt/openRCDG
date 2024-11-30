#pragma once

class Endpoints {
public:
  Endpoints(float *endpoints);

  void setLeft(float left);
  void setRight(float right);
  void setCenter(float center);

  // Sets the endpoint based on the value. value < 1500 = left endpoint, value > 1500 = right endpoint
  void setEndpointFromValue(float endpoint);

  float mapToEndpoints(float x);  // -1 - 1 -> left endpoint - right endpoint
  float mapToNormalized(float x); // left endpoint - right endpoint -> -1 - 1

  void getFromEEPROM(int address);
  void saveToEEPROM(int address);

private:
  float *defaultEndpoints;
  float endpoints[3];

  bool endpointsValid(float *endpoints);
};