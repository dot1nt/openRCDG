#pragma once

#include "curve.h"

namespace Config {

enum class ImuType {
  MPU6050,
};

// Baudrate for the serial port. Used only for debugging.
constexpr int SERIAL_BAUDRATE = 9600;

// Time in Hz every software loop should take.
constexpr int LOOP_TIME_HZ = 1000;

// Change to false if no sensitivity input is used.
constexpr bool USE_SENSITIVITY_INPUT = true;

// Sensitivity if USE_SENSITIVITY_INPUT is false. From 1000 - 2000.
constexpr unsigned long DEFAULT_SENSITIVITY = 2000;

// Pins to which the the sensitivity and steering signals are connected to.
// Must to be a PCINT pin. Currently PCINT1 and 2 are used.
// If you want to use a different pin, make sure to also change PCICR and PCMSK0 in the main.cc file.
// PCINT1 and 2 on an Arduino nano would be pin 9 and 10.
constexpr int PWM_SENSITIVITY_PIN = 16;
constexpr int PWM_STEERING_PIN = 15;

// Pin where the servo is connected.
constexpr int PWM_SERVO_PIN = 6;

// Pin where the LED is connected.
// Change this to LED_BUILDIN if you want to use the Arduino's onbaord LED.
constexpr int LED_PIN = 7;

// Pin where the button is connected.
// Change USE_BUTTON to false if no button is connected.
constexpr bool USE_BUTTON = true;
constexpr int BUTTON_PIN = 4;

// Default endpoints if USE_BUTTON is false.
float DEFAULT_ENDPOINTS[3] = {1000.0f, 1500.0f, 2000.0f};

// P, I and D for the pid controller.
// More info here: https://en.wikipedia.org/wiki/Proportional%E2%80%93integral%E2%80%93derivative_controller
constexpr float PID_P = 10.0f;
constexpr float PID_I = 0.0f;
constexpr float PID_D = -0.5f;

// Reverses the servo output.
constexpr bool REVERSE = true;

constexpr ImuType IMU_TYPE = ImuType::MPU6050;

// Gyro axis that should be used.
// 0 = X, 1 = Y, 2 = Z
constexpr int GYRO_AXIS = 2;

// LINEAR, SIN, LOG, CUSTOM
constexpr Curve::CurveType GYRO_CURVE_TYPE = Curve::LINEAR;

// Only active if GYRO_CURVE_TYPE = Curve::CUSTOM.
// This holds the corresponding y values for the x values 0.0, 0.1, 0.2 .. 0.9, 1.0.
float CUSTOM_GYRO_CURVE[11] = {0.0f, 0.25f, 0.35f, 0.53f, 0.6f, 0.66f, 0.73f, 0.8f, 0.86f, 0.93f, 1.0f};

// Gyro low pass filter cutoff in Hz.
// higher = faster, noisier response
// lower = slower, smoother response
constexpr float GYRO_LPF_CUTOFF = 10.0f;

// Pid d filter cutoff in Hz
constexpr float PID_D_FILTER_CUTOFF = 10.0f;

} // namespace Config