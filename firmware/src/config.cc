#include <Arduino.h>
#include "config.h"

int PWM_SERVO_PIN = 6;

int PWM_SENSITIVITY_PIN = 16;
int PWM_STEERING_PIN = 15;

int LED_PIN = 7;

int BUTTON_PIN = 4;

int LOOP_TIME = 1000; // hz

float PIDS[3] = { 15.0, 0.0, -5.0 }; // P, I, D

int GYRO_TYPE = MPU6050; 
int GYRO_AXIS = Z; // X, Y, Z

float GYRO_CURVE[11] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };          // linear

float GYRO_LPF1_CUTOFF = 20.0; // Hz
float GYRO_D_FILTER_CUTOFF = 10.0; // Hz

bool REVERSE = true;

float ENDPOINTS[3] = { 1000.0, 1500.0, 2000.0 };
