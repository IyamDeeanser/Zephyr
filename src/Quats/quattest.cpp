#include "quaternions.h"
#include "../Timer/Timer.h"
#include "../IMU/IMU.h"


Quat quaternion;
IMU gyro;
Timer timer1;

void setup()
{
    SerialUSB.begin(9600);
}

void loop()
{
    quaternion.calculateQuaternion(gyro, timer1);
    SerialUSB.print(quaternion.pitch);  SerialUSB.print(" ");
    SerialUSB.print(quaternion.yaw);  SerialUSB.print(" ");
    SerialUSB.println(quaternion.roll); 
}