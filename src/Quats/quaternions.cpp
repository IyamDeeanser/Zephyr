#include "quaternions.h"
#include <math.h>
void Quat::begin()
{
    //Set the initial quaternion's orientation
    pre_q[0] = 1;
    pre_q[1] = 0;
    pre_q[2] = 0;
    pre_q[3] = 0;
}

void Quat::calculateQuaternion(IMU& gyro, Timer& time)
{
    //Get the current angular rate
    wS[0] = 0;
    wS[1] = gyro.bodyGyroY_Rad;
    wS[2] = gyro.bodyGyroX_Rad;
    wS[3] = gyro.bodyGyroZ_Rad;

    //Now we have to normalize the previous orientation to be used
    //First we have to find the norm of the last one
    q_norm = (sqrt(pre_q[0] * pre_q[0] + pre_q[1] * pre_q[1] + pre_q[2] * pre_q[2] + pre_q[3] * pre_q[3]));
    pre_q[0] = pre_q[0] / q_norm;
    pre_q[1] = pre_q[1] / q_norm;
    pre_q[2] = pre_q[2] / q_norm;
    pre_q[3] = pre_q[3] / q_norm;
    //Obtain the derivative of the next quaternion
    q[0] = 0.5 * (pre_q[0] * wS[0] - pre_q[1] * wS[1] - pre_q[2] * wS[2] - pre_q[3] * wS[3]);
    q[1] = 0.5 * (pre_q[0] * wS[1] + pre_q[1] * wS[0] + pre_q[2] * wS[3] - pre_q[3] * wS[2]);
    q[2] = 0.5 * (pre_q[0] * wS[2] - pre_q[1] * wS[3] + pre_q[2] * wS[0] + pre_q[3] * wS[1]);
    q[3] = 0.5 * (pre_q[0] * wS[3] + pre_q[1] * wS[2] - pre_q[2] * wS[1] + pre_q[3] * wS[0]);
    //Calculate the "previous estimate" for the next cycle through integration, which is now the current quaternion ORIENTATION
    pre_q[0] = (pre_q[0] + q[0] * time.deltaTimeSec);
    pre_q[1] = (pre_q[1] + q[1] * time.deltaTimeSec);
    pre_q[2] = (pre_q[2] + q[2] * time.deltaTimeSec);
    pre_q[3] = (pre_q[3] + q[3] * time.deltaTimeSec);
    //Convert to Euler, add condition for PID loop later
    yaw = (atan2(2 * pre_q[1] * pre_q[2] - 2 * pre_q[0] * pre_q[3], 2 * pre_q[0] * pre_q[0] + 2 * pre_q[1] * pre_q[1] - 1));
    pitch = (-asin(2 * pre_q[1] * pre_q[3] + 2 * pre_q[0] * pre_q[2]));
    roll = (atan2(2 * pre_q[2] * pre_q[3] - 2 * pre_q[0] * pre_q[1], 2 * pre_q[0] * pre_q[0] + 2 * pre_q[3] * pre_q[3] - 1));
    //convert from radians to degrees
    yaw = yaw * (180 / pi);// - yawOffset;
    pitch = pitch * (180 / pi);// - pitchOffset;
    roll = roll * (180 / pi);
}