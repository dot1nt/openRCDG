#pragma once

class Imu {
  public:
    float output;

    virtual void init();
    virtual void get_gyro_axis(int axis);
};
