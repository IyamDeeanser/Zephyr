#include <Arduino.h>
#include "Quaternions/Quaternions.h"
#include "Timer/Timer.h"
#include "IMU/IMU.h"


Quaternion quaternion;
IMU gyro;
Timer timer1;

void setup()
{
    gyro.begin();
    gyro.getGyroBias();
    
    SerialUSB.begin(9600);
}

void loop()
{
    gyro.update();
    timer1.update();
    quaternion.calculateQuaternion(gyro, timer1);
    SerialUSB.print(quaternion.pitch);      SerialUSB.print(", ");
    SerialUSB.print(quaternion.yaw);        SerialUSB.print(", ");
    SerialUSB.println(quaternion.roll); 
}