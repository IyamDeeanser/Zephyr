#ifndef ACCEL_H
#define ACCEL_H

#include "SparkFun_Qwiic_KX13X.h"
#include "../Vec3/Vec3.h"

class Accelerometer {
private:
    QwiicKX134 kxAccel;
    outputData kxData;
public:
    vec3 data;
    void begin();
    void update();
};

#endif