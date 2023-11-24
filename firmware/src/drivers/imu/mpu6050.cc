#include <inttypes.h>
#include <Wire.h>
#include "mpu6050.h"

#include "../../config.h"

void Mpu6050::init() {
    Wire.begin();
    Wire.setClock(I2C_CLK_SPEED);

    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(PWR_REG);
    Wire.write(0);
    Wire.endTransmission();

    set_gyro_range(2000);
}

void Mpu6050::set_gyro_range(int range) {
    gyro_range = range;

    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(GYRO_CONFIG_REG);

    switch(range) {
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

void Mpu6050::get_gyro_axis(int axis) {
  Wire.beginTransmission(I2C_ADDRESS);

  switch (axis) {
    case X:
      Wire.write(GYRO_X_REG);
      break;
    case Y:
      Wire.write(GYRO_Y_REG);
      break;
    case Z:  
      Wire.write(GYRO_Z_REG);
      break;
  }

  Wire.endTransmission(false);
  Wire.requestFrom(I2C_ADDRESS, 2);

  output = (int16_t)(Wire.read() << 8 | Wire.read());

  switch(gyro_range) {
    case 250:
      output /= GYRO_FS_LSB_250;
    case 500:
      output /= GYRO_FS_LSB_500;
    case 1000:
      output /= GYRO_FS_LSB_1000;
    case 2000:
      output /= GYRO_FS_LSB_2000;
  }
}
