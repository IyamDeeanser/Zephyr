#include "PID.h"
//NOTE: THIS IS SOLELY A ROLL PID
PID::PID()
{}

void PID::update(Timer time, IMU gyro)
{
    //PID
    lastError = error;
    error = gyro.bodyGyroDeg.x - setpoint;
    totalError = totalError + error * time.deltaTimeSec;
    P = Kp * error;   //Proportional part of PID
    I = Ki * totalError; //Integral part of PID
    D = Kd * (error - lastError) / time.deltaTimeSec; //Derivative part of PID    The 0.01 is the hardware loop time
    //Now for the whole PID equation
    Output = (P + I + D);
}

void PID::setSetpoint(float newPoint)
{
    setpoint = newPoint;
}