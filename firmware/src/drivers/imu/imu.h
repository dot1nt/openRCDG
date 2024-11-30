#pragma once

class Imu {
public:
  virtual float getGyroAxis(int axis) = 0;
};
