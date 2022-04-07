//quaternion orientation libs
//by Timothy Cai

#ifndef QUAT_h
#define QUAT_h

#include "../IMU/IMU.h"
#include "../Timer/Timer.h"

const float M_PI = 3.1415926535;

class Quat
{
private:
    float wS[4]; //this is to store angular velocities
    float wI[4]; //this is to hold the initial desired orientation
    float q_norm; //this is the norm of the last quaternion used in normalization
    float q[4]; //this is the current derivative
    float i_q[4]; //orientation of earth relative to sensor/the starting quaternion
    float pre_q[4]; //this is the previous quaternion derivative
    
public:
    float yaw, pitch, roll;
    
    Quat();

    void calculateQuaternion(IMU gyro, Timer time);
};

#endif