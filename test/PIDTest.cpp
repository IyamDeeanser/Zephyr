#include "PID.h"
#include "../Timer/Timer.h"
#include "../IMU/IMU.h"

PID rollcontrol;
IMU gyro;
Timer timer1;

void setup()
{
    SerialUSB.begin(9600);
}

void loop()
{
    rollcontrol.calculate(timer1, gyro)
    SerialUSB.println(rollcontrol.Output);
}
