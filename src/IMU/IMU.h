#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include "../Vec3/Vec3.h"

class IMU_Sensor {
  public:
    //Raw gyro readings   Tims note: this is not raw. theres debiasing processing
    vec3 bodyGyroRad;
    vec3 bodyGyroDeg;

    //Temperature from IMU
    float temperature;
    bool biasComplete = false;
    //Raw acc readings in m/s^2
    vec3 bodyAccel;
    vec3 gyroBias;
    
    bool begin();

    void update();

    void getGyroBias();
};

#endif
