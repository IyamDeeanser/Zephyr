#ifndef PID_H
#define PID_H

#include "../Timer/Timer.h"
#include "../IMU/IMU.h"

class PID{
private:
  float error = 0;
  float lastError = 0;
  float totalError = 0;
  float Kp = 0, Ki = 0, Kd = 0;
public:
  float Output = 0;
  PID PID();
  void calculate(Timer time);
};

#endif