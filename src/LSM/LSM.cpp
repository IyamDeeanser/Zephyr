#include "LSM.h"

Acc_Gyr::Acc_Gyr() {
    // Not sure what the inputs of 'I2C_SDA' & 'I2C_SCL' is supposed to be
    dev_i2c = TwoWire(I2C_SDA, I2C_SCL);  // ! 
    dev_i2c.begin();

    AccGyr = LSM6DSLSensor(&dev_i2c);
    AccGyr.begin();
    AccGyr.Enable_X();  
    AccGyr.Enable_G();
}

//these two functions update accelerometer & gyro arrays
void Acc_Gyr::UpdateAccelArr() {
    AccGyr.Get_X_Axes(accelerometer);
} 

void Acc_Gyr::UpdateGyroArr() {
    AccGyr.Get_G_Axes(gyroscope);
}