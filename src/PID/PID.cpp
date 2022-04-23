#include "PID.h"
//NOTE: THIS IS SOLELY A ROLL PID
PID::PID()
{}

void PID::update(Timer time, float rollOri)
{
    //PID
    lastError = error;
    error = setpoint - rollOri;
    totalError = totalError + error;
    P = Kp * error;   //Proportional part of PID
    I = Ki * totalError * time.deltaTimeSec; //Integral part of PID
    D = Kd * (error - lastError) / time.deltaTimeSec; //Derivative part of PID    The 0.01 is the hardware loop time
    //Now for the whole PID equation
    Output = (P + I + D);
}

void PID::setSetpoint(float newPoint)
{
    setpoint = newPoint;
}