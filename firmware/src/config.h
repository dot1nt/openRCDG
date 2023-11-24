#pragma once

typedef enum {
  MPU6050,
} Gyro_type_e;

typedef enum {
  X,
  Y,
  Z,
} Gyro_axis_e;

extern int PWM_SERVO_PIN;

extern int PWM_SENSITIVITY_PIN;
extern int PWM_STEERING_PIN;

extern int LED_PIN;

extern int BUTTON_PIN;

extern int LOOP_TIME;

extern float PIDS[3];

extern bool REVERSE;

extern int GYRO_TYPE;
extern int GYRO_AXIS;

extern float GYRO_CURVE[11];

extern float GYRO_LPF1_CUTOFF;
extern float GYRO_D_FILTER_CUTOFF;

extern float ENDPOINTS[3];
