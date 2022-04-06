#ifndef PID_H
#define PID_H

#include "Timer.h"
#include <Arduino.h>

class PID {
  public:
    //PID error variables
    float err, oldErr;

    //PID output
    float out;

    //Setpoint
    float setpoint;

    //PID
    float p;
    float i;
    float d;

    //Limit for integral clamping
    float integralLimit;

    //PID gains
    float Kp;
    float Ki;
    float Kd;

    void setGains(float KP, float KI, float KD, float iLimit);

    void compute(float pv, Timer timer);
};

#endif
