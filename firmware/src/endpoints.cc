#include "endpoints.h"

#include <Arduino.h>
#include <EEPROM.h>

#include "utils.h"

Endpoints::Endpoints(float *endpoints) {
  memcpy(this->endpoints, endpoints, 3 * sizeof(float));
  defaultEndpoints = endpoints;
}

void Endpoints::setLeft(float value) { endpoints[0] = value; }
void Endpoints::setRight(float value) { endpoints[2] = value; }
void Endpoints::setCenter(float value) { endpoints[1] = value; }
void Endpoints::setEndpointFromValue(float endpoint) {
  if (endpoint < 1500) {
    setLeft(endpoint);
  } else {
    setRight(endpoint);
  }
}

bool Endpoints::endpointsValid(float *endpoints) {
  for (int i = 0; i < 3; i++) {
    if (endpoints[i] < 500.0f || endpoints[i] > 2500.0f || isnan(endpoints[i])) {
      return false;
    }
  }

  return true;
}

float Endpoints::mapToEndpoints(float x) {
  float out;

  if (0 > x) {
    out = mapf(x, -1.0f, 0.0f, endpoints[0], endpoints[1]);
  } else {
    out = mapf(x, 0.0f, 1.0f, endpoints[1], endpoints[2]);
  }

  return out;
}

float Endpoints::mapToNormalized(float x) {
  float out;

  if (endpoints[1] > x) {
    out = mapf(x, endpoints[0], endpoints[1], -1.0f, 0.0f);
  } else {
    out = mapf(x, endpoints[1], endpoints[2], 0.0f, 1.0f);
  }

  return out;
}

void Endpoints::saveToEEPROM(int address) {
  EEPROM.put(address, endpoints);
}

void Endpoints::getFromEEPROM(int address) {
  float eepromEndpoints[3];
  EEPROM.get(address, eepromEndpoints);

  if (!endpointsValid(eepromEndpoints)) {
    EEPROM.put(address, defaultEndpoints);
  } else {
    memcpy(endpoints, eepromEndpoints, 3 * sizeof(float));
  }
}