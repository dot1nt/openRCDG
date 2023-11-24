#pragma once

#include "imu.h"

// https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

#define I2C_CLK_SPEED   300000

#define I2C_ADDRESS     0x69

#define PWR_REG         0x6B
#define GYRO_CONFIG_REG 0x1B

#define GYRO_X_REG      0x43
#define GYRO_Y_REG      0x45
#define GYRO_Z_REG      0x47

#define GYRO_FS_250     0x0
#define GYRO_FS_500     0x1
#define GYRO_FS_1000    0x2
#define GYRO_FS_2000    0x3

#define GYRO_FS_LSB_250     131.0f
#define GYRO_FS_LSB_500     66.5f // https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf#page=12
#define GYRO_FS_LSB_1000    32.8f
#define GYRO_FS_LSB_2000    16.4f

class Mpu6050 : public Imu {
  private:
    int gyro_range;
    void set_gyro_range(int range);

  public:
    void init(); 
    void get_gyro_axis(int axis);
};
