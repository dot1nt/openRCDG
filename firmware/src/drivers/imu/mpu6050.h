#pragma once

#include "imu.h"

#include <Arduino.h>

class Mpu6050 : public Imu {
private:
  int gyroRange;
  void setGyroRange(int range);

  // https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
  static constexpr uint32_t I2C_CLK_SPEED = 300000;

  static constexpr uint8_t I2C_ADDRESS = 0x69;

  static constexpr uint8_t PWR_REG = 0x6B;
  static constexpr uint8_t GYRO_CONFIG_REG = 0x1B;

  static constexpr uint8_t GYRO_X_REG = 0x43;
  static constexpr uint8_t GYRO_Y_REG = 0x45;
  static constexpr uint8_t GYRO_Z_REG = 0x47;

  static constexpr uint8_t GYRO_FS_250 = 0x0;
  static constexpr uint8_t GYRO_FS_500 = 0x1;
  static constexpr uint8_t GYRO_FS_1000 = 0x2;
  static constexpr uint8_t GYRO_FS_2000 = 0x3;

  static constexpr float GYRO_FS_LSB_250 = 131.0f;
  static constexpr float GYRO_FS_LSB_500 = 66.5f; // https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf#page=12
  static constexpr float GYRO_FS_LSB_1000 = 32.8f;
  static constexpr float GYRO_FS_LSB_2000 = 16.4f;

public:
  Mpu6050();
  float getGyroAxis(int axis) override final;
};
