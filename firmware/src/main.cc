#include <Arduino.h>
#include <Servo.h>

#include "config.h"

#include "drivers/button.h"
#include "drivers/led.h"
#include "drivers/pwm.h"

#include "drivers/imu/imu.h"
#include "drivers/imu/mpu6050.h"

#include "endpoints.h"
#include "mixer.h"
#include "pid.h"

///////////////////////////////////////////////////////

constexpr float loopTime = 1 / static_cast<float>(Config::LOOP_TIME_HZ);

Endpoints endpoints(Config::DEFAULT_ENDPOINTS);

Button button(Config::BUTTON_PIN);

Led led(Config::LED_PIN);

Imu *imu;

PidController pidController(
    Config::PID_P,
    Config::PID_I,
    Config::PID_D,
    Config::PID_D_FILTER_CUTOFF,
    loopTime);

Curve gyroCurve;

Mixer mixer(gyroCurve, endpoints, Config::REVERSE);

PT1Filter gyroFilter(Config::GYRO_LPF_CUTOFF, loopTime);

PwmReader pwmSteering(Config::PWM_STEERING_PIN);
PwmReader pwmSensitivity(Config::PWM_SENSITIVITY_PIN);

Servo steeringServo;

///////////////////////////////////////////////////////

ISR(PCINT0_vect) {
  pwmSteering.update();
  pwmSensitivity.update();
}

///////////////////////////////////////////////////////

void waitForButtonPress() {
  while (true) {
    if (button.update()) {
      return;
    }

    steeringServo.writeMicroseconds(pwmSteering.getValue());
  }
}

void configureEndpoints() {
  led.low();
  delay(500);

  led.blink(1);
  waitForButtonPress();
  endpoints.setEndpointFromValue(pwmSteering.getValue());

  led.blink(2);
  waitForButtonPress();
  endpoints.setEndpointFromValue(pwmSteering.getValue());

  led.blink(3);
  waitForButtonPress();
  endpoints.setCenter(pwmSteering.getValue());

  endpoints.saveToEEPROM(0);

  led.setupFinished();
}

// delayMicroseconds() has a 16383 limit
void _delayMicroseconds(unsigned long us) {
  unsigned long delay = us;

  while (delay > 16383) {
    delay -= 16383;
    delayMicroseconds(16383);
  }

  delayMicroseconds(delay);
}

///////////////////////////////////////////////////////

void setup() {
  Serial.begin(Config::SERIAL_BAUDRATE);

  delay(1000);

  PCICR |= B00000001;  // interrupts group 0
  PCMSK0 |= B00000110; // interrupts pcint 1, 2

  steeringServo.attach(Config::PWM_SERVO_PIN);

  endpoints.getFromEEPROM(0);

  switch (Config::GYRO_CURVE_TYPE) {
  case Curve::CurveType::CUSTOM:
    gyroCurve.setCustomCurve(Config::CUSTOM_GYRO_CURVE);
    break;

  default:
    gyroCurve.setCurveType(Config::GYRO_CURVE_TYPE);
    break;
  }

  switch (Config::IMU_TYPE) {
  case Config::ImuType::MPU6050:
    imu = new Mpu6050();
    break;
  }

  led.setupFinished();
}

///////////////////////////////////////////////////////

unsigned long loopTimeUs = loopTime * 1e6;

void loop() {
  unsigned long startTime = micros();

  /////////////

  if (Config::USE_BUTTON) {
    if (button.update()) {
      configureEndpoints();
    }
  }

  float gyroOutput = imu->getGyroAxis(Config::GYRO_AXIS);

  float filteredGyroOutput = gyroFilter.update(gyroOutput);

  float pidOutput = pidController.update(filteredGyroOutput);

  unsigned long sensitivity;
  if (Config::USE_SENSITIVITY_INPUT) {
    sensitivity = pwmSensitivity.getValue();
  } else {
    sensitivity = Config::DEFAULT_SENSITIVITY;
  }

  float mixerOutput = mixer.update(
      pidOutput,
      pwmSteering.getValue(),
      sensitivity);

  steeringServo.writeMicroseconds(mixerOutput);

  /////////////

  if (micros() - startTime > loopTimeUs) {
    return;
  }

  unsigned long delay = loopTimeUs - micros() + startTime;

  _delayMicroseconds(delay);
}
