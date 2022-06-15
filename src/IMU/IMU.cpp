#include "IMU.h"
#include <Arduino_LSM6DS3.h>

bool IMU_Sensor::begin() {
    return IMU.begin();
}

void IMU_Sensor::update() {
    vec3 rawGyroData;

    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(bodyAccel.x, bodyAccel.y, bodyAccel.z);
    }

    if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(rawGyroData.x, rawGyroData.y, rawGyroData.z);
    }

    bodyGyroRad.x = rawGyroData.x - gyroBias.x;
    bodyGyroRad.y = rawGyroData.y - gyroBias.y;
    bodyGyroRad.z = rawGyroData.z - gyroBias.z;

    bodyGyroDeg.x = bodyGyroRad.x * (180/PI);
    bodyGyroDeg.y = bodyGyroRad.y * (180/PI);
    bodyGyroDeg.z = bodyGyroRad.z * (180/PI);

    // temperature = temp.temperature;
}

void IMU_Sensor::getGyroBias() {
    const static unsigned long startTime = millis();
    static int loopNum = 0;
    const int delayTime = 6; // in milliseconds
    const int totalLoops = 1000;

    if (biasComplete) return;

    if (millis() > startTime + delayTime * loopNum && loopNum < totalLoops){
        loopNum++;
        vec3 rawGyroData;
        IMU.readGyroscope(rawGyroData.x, rawGyroData.y, rawGyroData.z);

        gyroBias.x = gyroBias.x + rawGyroData.x;
        gyroBias.y = gyroBias.y + rawGyroData.y;
        gyroBias.z = gyroBias.z + rawGyroData.z;
    }

    if (loopNum > totalLoops) biasComplete = true;

    gyroBias.x = gyroBias.x / 1000;
    gyroBias.y = gyroBias.y / 1000;
    gyroBias.z = gyroBias.z / 1000;
}
