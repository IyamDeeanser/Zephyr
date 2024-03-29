#ifndef ACCEL_H
#define ACCEL_H

#include <Wire.h>
#include "SparkFun_Qwiic_KX13X.h"
#include "../Vec3/Vec3.h"

class Accelerometer { // instance of class needs to be made as global object
private:
    QwiicKX134 kxAccel;
    outputData kxData;
    const float G = 9.80665;
public:
    vec3 data; // access data
    bool begin(); // run ONCE in setup, returns false if failed to initalize
    void update(); // run periodically in loop to updata 'data'
    float getAccelMag() const;
};

#endif