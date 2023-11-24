The gyro can be configured in the config.cc file.

## Settings

Pin to which the servo is connected to. Can be any pwm pin.
```
int PWM_SERVO_PIN = 6;
```
---
Pins to which the the sensitivity and steering signals are connected to.
Must to be a PCINT pin. Currently PCINT1 and 2 are used. If you want to use a different pin, make sure to also change PCICR and PCMSK0 in the main.cpp file.

PCINT1 and 2 on an Arduino nano would be pin 9 and 10.
```
PWM_SENSITIVITY_PIN = 16;
PWM_STEERING_PIN = 15;
```
---
Pins to which button and LED are connected to. Can be any digital pin. If you don't have a button, comment the "eeprom_load_endpoints()" line in the main.cpp file and change the endpoints manually. Change LED\_PIN to LED_BUILTIN to use the LED on the Arduino.
```
int LED_PIN = 7;

int BUTTON_PIN = 4;
```
---
Microseconds every software loop should take.
```
int LOOP_TIME = 1000;
```
---
P I and D for the pid controller. [More info](https://en.wikipedia.org/wiki/Proportional%E2%80%93integral%E2%80%93derivative_controller)
```
float PIDS[3] = {10.0, 0.0, -5.0};
```
---
Gyro type and the axis the gyro should use.
Only MPU6050 supported right now.
```
int GYRO_TYPE = MPU6050;
int GYRO_AXIS = Z;
```
---
Curve how the servo should react to the gyro output.

The array contains the corresponding y-values for the x-values 0.0, 0.1, 0.2 ... 1.0.
```
float GYRO_CURVE[11] = {0.0 ,0.1 ,0.2 ,0.3 ,0.4 ,0.5 ,0.6 ,0.7 ,0.8 ,0.9 ,1.0};
```
Some other curves with the corresponding function would be:
```
float GYRO_CURVE[11] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };        // linear
float GYRO_CURVE[11] = {0.0 ,0.15 ,0.3 ,0.45 ,0.58 ,0.7 ,0.8 ,0.89 ,0.95 ,0.98 ,1.0};    // sin(x*pi/2)
float GYRO_CURVE[11] = {0.0 ,0.06 ,0.14 ,0.23 ,0.33 ,0.43 ,0.54 ,0.65 ,0.76 ,0.88 ,1.0}; // x^1.2
float GYRO_CURVE[11] = {0.0 ,0.14 ,0.26 ,0.36 ,0.46 ,0.56 ,0.65 ,0.74 ,0.83 ,0.91 ,1.0}; // x^(1/1.2)
float GYRO_CURVE[11] = {0.0 ,0.21 ,0.34 ,0.44 ,0.54 ,0.62 ,0.71 ,0.78 ,0.86 ,0.93 ,1.0}; // x^(1/1.5)
```
---
Filter cutoff in Hz for the gyro and d term for the pid controller.

Lower gyro filter cutoff = slower, smoother response

Higher gyro filter cutoff = faster, noisier response

D filter cutoff doesn't really matter.
```
float GYRO_LPF1_CUTOFF = 20.0;
float GYRO_D_FILTER_CUTOFF = 10.0;
```
---
Reverses the servo
```
bool REVERSE = true;
```
---
Servo endpoints. Should only be changed if you're not using a button to set the endpoints.
```
float ENDPOINTS[3] = { 1000.0, 1500.0, 2000.0 };
```

## Endpoint adjustment with button

1. Press the button while powering on \
LED should blink once
2. Steer completly to one side and press the button \
LED should blink twice
3. Steer to the other side \
LED should blink three times
4. Return to neutral and press the button a third time
