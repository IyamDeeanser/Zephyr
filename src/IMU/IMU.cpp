#include "IMU.h"
#include <Adafruit_LSM6DSL.h>

Adafruit_LSM6DSL lsm;

bool IMU::begin() {
    if (!lsm.begin_I2C()) {
        return false;
    }

    lsm.setAccelRange(LSM6DS_ACCEL_RANGE_16_G);
    lsm.setGyroRange(LSM6DS_GYRO_RANGE_500_DPS);
    lsm.setAccelDataRate(LSM6DS_RATE_208_HZ);
    lsm.setGyroDataRate(LSM6DS_RATE_208_HZ);

    return true;
}

void IMU::update() {
    sensors_event_t accel, gyro, temp;
    lsm.getEvent(&accel, &gyro, &temp);

    temperature = temp.temperature;

    bodyGyroX_Rad = gyro.gyro.x - gyroXBias;
    bodyGyroY_Rad = gyro.gyro.y - gyroYBias;
    bodyGyroZ_Rad = gyro.gyro.z - gyroZBias;

    bodyGyroX_Deg = bodyGyroX_Rad * (180/PI);
    bodyGyroY_Deg = bodyGyroY_Rad * (180/PI);
    bodyGyroZ_Deg = bodyGyroZ_Rad * (180/PI);

    bodyAccelX = accel.acceleration.x;
    bodyAccelY = accel.acceleration.y;
    bodyAccelZ = accel.acceleration.z;
}

void IMU::getGyroBias() {
    for (int i = 0; i < 1000; i++){
        sensors_event_t accel, gyro, temp;
        lsm.getEvent(&accel, &gyro, &temp);

        gyroXBias = gyroXBias + gyro.gyro.x;
        gyroYBias = gyroYBias + gyro.gyro.y;
        gyroZBias = gyroZBias + gyro.gyro.z;

        delay(6); // Delay to make sure imu does not give repeats
    }

    gyroXBias = gyroXBias / 1000;
    gyroYBias = gyroYBias / 1000;
    gyroZBias = gyroZBias / 1000;
}
