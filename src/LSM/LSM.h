// LMS6DSL Gyroscope & Accelerometer Functions
// Documentation: https://github.com/stm32duino/LSM6DSL 
// Written by: Brian

// ! ACCEL & GYRO are in int32_t - may cause problems since most of our data is in float
#ifndef LMS_h
#define LMS_h

#include <Arduino.h>

#include <LSM6DSLSensor.h>

#include "../Vec3/Vec3.h"
// Initialization
// (I2C Initialization)

// todo add getters that return a vec3

class Acc_Gyr
{
private:
    TwoWire dev_i2c;
    LSM6DSLSensor AccGyr;
    float accelArr[3];
    float gyroArr[3];
public:
    Acc_Gyr();
    void UpdateAccelArr();
    void UpdateGyroArr();
    ~Acc_Gyr();
};

#endif