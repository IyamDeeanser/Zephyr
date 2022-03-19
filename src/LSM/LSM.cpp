#include "LSM.h"

Acc_Gyr::Acc_Gyr()
: dev_i2c(I2C_SDA, I2C_SCL)
{
    dev_i2c.begin();
    LSM6DSLSensor AG(&dev_i2c); // GHETTO AS FUCK fix
    AccGyr= AG;
    AccGyr.begin();
    AccGyr.Enable_X();  
    AccGyr.Enable_G();
}

//these two functions update accelerometer & gyro arrays
void Acc_Gyr::UpdateAccelArr() {
    AccGyr.Get_X_Axes(accelArr);
} 

void Acc_Gyr::UpdateGyroArr() {
    AccGyr.Get_G_Axes(gyroArr);
}