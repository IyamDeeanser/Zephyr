#ifndef ACCEL_H
#define ACCEL_H

#include "SparkFun_Qwiic_KX13X.h"
#include "../Vec3/Vec3.h"

class Accelerometer { // instance of class needs to be made as global object
private:
    QwiicKX134 kxAccel;
    outputData kxData;
public:
    vec3 data; // access data
    void begin(); // run ONCE in setup
    void update(); // run periodically in loop to updata 'data'
};

#endif