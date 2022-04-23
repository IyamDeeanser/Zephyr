#ifndef PID_H
#define PID_H

#include <Arduino.h>
#include "../Timer/Timer.h"

class PID{
private:
  float setpoint = 0;
  float error = 0;
  float lastError = 0;
  float totalError = 0;
  float Kp = 1, Ki = 0, Kd = 0;
  float P, I, D;
public:
  PID();
  float Output = 0;
  void update(Timer time, float rollOri);
  void setSetpoint(float newPoint);
};

#endif