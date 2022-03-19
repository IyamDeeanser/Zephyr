// LMS6DSL Gyroscope & Accelerometer Functions
// Documentation: https://github.com/stm32duino/LSM6DSL 
// Written by: Brian

// ! ACCEL & GYRO are in int32_t - may cause problems since most of our data is in float
#ifndef SD_CARD_h
#define SD_CARD_h

#include <Arduino.h>
#include <Arduino_LSM6DS3.h>

// Initialization
// (I2C Initialization)

// todo add getters that return a vec3

class Acc_Gyr
{
private:
    TwoWire dev_i2c;
    LSM6DSLSensor AccGyr;
    int32_t accelArr[3];
    int32_t gyroArr[3];
public:
    Acc_Gyr();
    void UpdateAccelArr();
    void UpdateGyroArr();
    ~Acc_Gyr();
};

#endif