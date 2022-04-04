// LMS6DSL Gyroscope & Accelerometer Functions
// Documentation: https://github.com/stm32duino/LSM6DSL 
// https://os.mbed.com/teams/ST/code/LSM6DSL/docs/tip/LSM6DSLSensor_8cpp_source.html 

#ifndef LMS_h
#define LMS_h

#include <Arduino.h>
#include <Servo.h>
#include <LSM6DSL_ACC_GYRO_Driver.h>

#include "../Vec3/Vec3.h"
// Initialization
// (I2C Initialization)

// todo add getters that return a vec3

class Acc_Gyr
{
private:
    TwoWire dev_i2c;
    LSM6DSLSensor AccGyr;
    int32_t accelerometer[3];
    int32_t gyroscope[3];
public:
    Acc_Gyr();
    void UpdateAccelArr();
    void UpdateGyroArr();
};

#endif