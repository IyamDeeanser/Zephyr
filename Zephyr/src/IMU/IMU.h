#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

class IMU {
  public:
    //Raw gyro readings   Tims note: this is not raw. theres debiasing processing
    float bodyGyroX_Rad, bodyGyroY_Rad, bodyGyroZ_Rad;
    float bodyGyroX_Deg, bodyGyroY_Deg, bodyGyroZ_Deg;

    //Temperature frm IMU
    float temperature;

    //Raw acc readings in m/s^2
    float bodyAccelX, bodyAccelY, bodyAccelZ;

    float gyroXBias, gyroYBias, gyroZBias;

    bool begin();

    void update();

    void getGyroBias();
};

#endif
