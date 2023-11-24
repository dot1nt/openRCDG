#include "Arduino.h"
#include "mixer.h"

#include "config.h"

#include "utils.h"

float gyro_curve(float x) {
  for (int i = 0; i < 10; i++) {
    float x0 = 0.1 * (float) i;
    float x1 = 0.1 * (float) (i+1);

    float y0 = GYRO_CURVE[i];
    float y1 = GYRO_CURVE[i+1];

    float absx = abs(x);

    if (x0 < absx && x1 >= absx) {
      float o = (y0*(x1-abs(x))+y1*(abs(x)-x0)) / (x1 - x0);
      return (x < 0) ? -o : o;
    }
  }

  return x;
}


void Mixer::update(float pid_output, float steering_input, float sens_input) {
  float inp_end[3] = {-1.0, 0.0, 1.0};
  steering_input = mapf3(steering_input, ENDPOINTS, inp_end);

  sens_input = abs(mapf(sens_input, 1500.0, 2000.0, 0.0, 1.0));

  pid_output = mapf(pid_output * sens_input, -1000.0, 1000.0, -1.0, 1.0);
  pid_output = REVERSE ? pid_output : -pid_output;
  pid_output = constrain(pid_output, -1.0, 1.0);
  pid_output = gyro_curve(pid_output);

  output = constrain(pid_output + steering_input, -1.0, 1.0);
  output = mapf3(output, inp_end, ENDPOINTS);
}
