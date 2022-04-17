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

    bodyGyroRad.x = gyro.gyro.x - gyroBias.x;
    bodyGyroRad.y = gyro.gyro.y - gyroBias.y;
    bodyGyroRad.z = gyro.gyro.z - gyroBias.z;

    bodyGyroDeg.x = bodyGyroRad.x * (180/PI);
    bodyGyroDeg.y = bodyGyroRad.y * (180/PI);
    bodyGyroDeg.z = bodyGyroRad.z * (180/PI);

    bodyAccel.x = accel.acceleration.x;
    bodyAccel.y = accel.acceleration.y;
    bodyAccel.z = accel.acceleration.z;
}

void IMU::getGyroBias() {
    for (int i = 0; i < 1000; i++){
        sensors_event_t accel, gyro, temp;
        lsm.getEvent(&accel, &gyro, &temp);

        gyroBias.x = gyroBias.x + gyro.gyro.x;
        gyroBias.y = gyroBias.y + gyro.gyro.y;
        gyroBias.z = gyroBias.z + gyro.gyro.z;

        delay(6); // Delay to make sure imu does not give repeats
    }

    gyroBias.x = gyroBias.x / 1000;
    gyroBias.y = gyroBias.y / 1000;
    gyroBias.z = gyroBias.z / 1000;
}
