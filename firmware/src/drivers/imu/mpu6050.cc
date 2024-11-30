#include "mpu6050.h"

#include <Wire.h>

Mpu6050::Mpu6050() {
  Wire.begin();
  Wire.setClock(I2C_CLK_SPEED);
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(PWR_REG);
  Wire.write(0);
  Wire.endTransmission();

  delayMicroseconds(200);

  setGyroRange(2000);
}

void Mpu6050::setGyroRange(int range) {
  gyroRange = range;

  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(GYRO_CONFIG_REG);

  switch (range) {
  case 250:
    Wire.write(GYRO_FS_250 << 3);
  case 500:
    Wire.write(GYRO_FS_500 << 3);
  case 1000:
    Wire.write(GYRO_FS_1000 << 3);
  case 2000:
    Wire.write(GYRO_FS_2000 << 3);
  }

  Wire.endTransmission();
}

float Mpu6050::getGyroAxis(int axis) {
  Wire.beginTransmission(I2C_ADDRESS);

  switch (axis) {
  case 0:
    Wire.write(GYRO_X_REG);
    break;
  case 1:
    Wire.write(GYRO_Y_REG);
    break;
  case 2:
    Wire.write(GYRO_Z_REG);
    break;
  }

  Wire.endTransmission(false);
  Wire.requestFrom(I2C_ADDRESS, static_cast<uint8_t>(2));

  float output = static_cast<int16_t>(Wire.read() << 8 | Wire.read());

  switch (gyroRange) {
  case 250:
    output /= GYRO_FS_LSB_250;
  case 500:
    output /= GYRO_FS_LSB_500;
  case 1000:
    output /= GYRO_FS_LSB_1000;
  case 2000:
    output /= GYRO_FS_LSB_2000;
  }

  return output;
}
