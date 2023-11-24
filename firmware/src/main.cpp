#include <Arduino.h>
#include <Servo.h>

#include "config.h"

#include "drivers/led.h"
#include "drivers/pwm.h"
#include "drivers/eeprom.h"

#include "drivers/imu/imu.h"
#include "drivers/imu/mpu6050.h"

#include "mixer.h"
#include "pid.h"
#include "utils.h"

///////////////////////////////////////////////////////

Led led(LED_PIN);

Imu *imu;

PidController pid_controller;

Mixer mixer;

Lpf1 lpf1;

PwmReader pwm_steering(PWM_STEERING_PIN);
PwmReader pwm_sensitivity(PWM_SENSITIVITY_PIN);

Servo servo;

///////////////////////////////////////////////////////

ISR(PCINT0_vect) {
  pwm_steering.update();
  pwm_sensitivity.update();
}

///////////////////////////////////////////////////////

void wait_for_button_press() {
  int debounce_delay = 50;

  bool is_pressed = false;

  while (true) {
    int state = digitalRead(BUTTON_PIN);

    if (!is_pressed) {
      if (!state) {
        delay(debounce_delay);
        is_pressed = true;
      }
    } else {
      if (state) {
        delay(debounce_delay);
        return;
      }
    }

    servo.writeMicroseconds(pwm_steering.output);
  }
}

void set_endpoint(float value) {
  if (value < 1500) {
    ENDPOINTS[0] = value;
  } else {
    ENDPOINTS[2] = value;
  }
}

void configure_endpoints() {
  while (!digitalRead(BUTTON_PIN)) {}

  led.blink(1);
  wait_for_button_press();
  set_endpoint(pwm_steering.output);

  led.blink(2);
  wait_for_button_press();
  set_endpoint(pwm_steering.output);

  led.blink(3);
  wait_for_button_press();
  ENDPOINTS[1] = pwm_steering.output;

  eeprom_save_endpoints(ENDPOINTS);

  delay(500);
}

///////////////////////////////////////////////////////

void setup() {
  Serial.begin(38400);
  
  delay(500);

  PCICR  |= B00000001; // interrupts group 0
  PCMSK0 |= B00000110; // interrupts pcint 1, 2

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  eeprom_get_endpoints(ENDPOINTS); 

  servo.attach(PWM_SERVO_PIN);

  if (!digitalRead(BUTTON_PIN)) {
    configure_endpoints();
  }

  switch (GYRO_TYPE) {
    case MPU6050:
      imu = new Mpu6050();
      break;
  }

  imu->init();

  pid_controller.init(PIDS);

  lpf1.init(GYRO_LPF1_CUTOFF, LOOP_TIME * 1e-6);

  led.setup_finished();
}

///////////////////////////////////////////////////////

void loop() {
  unsigned long start_time = micros();

  /////////////

  imu->get_gyro_axis(GYRO_AXIS);

  lpf1.update(imu->output);
  
  pid_controller.update(lpf1.output);

  mixer.update(pid_controller.output, pwm_steering.output, pwm_sensitivity.output);

  servo.writeMicroseconds(mixer.output);

  /////////////

  int delay = LOOP_TIME - micros() - start_time;
  if (delay < 0) { return; }

  delayMicroseconds(delay);
}
