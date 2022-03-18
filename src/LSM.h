// LMS6DSL Gyroscope & Accelerometer 
// Documentation: https://github.com/stm32duino/LSM6DSL 
// Written by: Brian Zhou

#include <Arduino_LSM6DS3.h>

// Initialization

// (I2C Initialization)
TwoWire dev_i2c(I2C_SDA, I2C_SCL);
dev_i2c.begin();

LSM6DSLSensor AccGyr(&dev_i2c);
AccGyr.begin();
AccGyr.Enable_X();  
AccGyr.Enable_G();

int32_t accelArr[3];
int32_t gyroArr[3];

//these two functions update accelerometer & gyro arrays
void UpdateAccelArr() {
    AccGyr.Get_X_Axes(accelArr);
}

void UpdateGyroArr() {
    AccGyr.Get_G_Axes(gyroArr);
}

//brian is a weirdo