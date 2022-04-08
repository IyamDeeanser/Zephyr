#ifndef PID_H
#define PID_H

#include "../Timer/Timer.h"
#include "../IMU/IMU.h"

class PID{
private:
  float setpoint = 0;
  float error = 0;
  float lastError = 0;
  float totalError = 0;
  float Kp = 1, Ki = 0, Kd = 0;
  float P, I, D;
public:
  float Output = 0;
  void calculate(Timer time, IMU gyro);
  void setSetpoint(float newPoint);
};

#endif