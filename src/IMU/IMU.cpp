#include "IMU.h"
#include <Adafruit_LSM6DS3TRC.h>

Adafruit_LSM6DS3TRC lsm;

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
    const static unsigned long startTime = millis();
    static int loopNum = 0;
    const int delayTime = 6; // in milliseconds
    const int totalLoops = 2000;

    if (biasComplete) return;

    if (millis() > startTime + delayTime * loopNum && loopNum < totalLoops){
        loopNum++;
        sensors_event_t accel, gyro, temp;
        lsm.getEvent(&accel, &gyro, &temp);

        gyroBias.x = gyroBias.x + gyro.gyro.x;
        gyroBias.y = gyroBias.y + gyro.gyro.y;
        gyroBias.z = gyroBias.z + gyro.gyro.z;
    }

    if (loopNum > totalLoops) biasComplete = true;

    gyroBias.x = gyroBias.x / 2000;
    gyroBias.y = gyroBias.y / 2000;
    gyroBias.z = gyroBias.z / 2000;
}
