#include "PID.h"

void PID::setGains(float KP, float KI, float KD, float iLimit) {
    Kp = KP;
    Ki = KI;
    Kd = KD;
    
    integralLimit = iLimit;
}

void PID::compute(float pv, Timer timer) {
    //Set previous error values
    oldErr = err;

    //Set current error values
    err = pv - setpoint;

    //Calculate PID
    p = Kp * err;

    i = Ki * (constrain(i + (err * timer.deltaTimeSec), -integralLimit, integralLimit));

    d = Kd * ((err - oldErr) / timer.deltaTimeSec);

    out = p + i + d;
}
