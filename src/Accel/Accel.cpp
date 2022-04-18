#include "Accel.h"

bool Accelerometer::begin(){ 
    Wire.begin();
    
    if(!kxAccel.begin(0x1E)) return false;
    if(!kxAccel.initialize(DEFAULT_SETTINGS)) return false;

    kxAccel.setRange(KX134_RANGE64G);

    return true;
}


void Accelerometer::update(){
    kxData = kxAccel.getAccelData();
    data.set(kxData.xData,kxData.yData,kxData.zData);
}

float Accelerometer::getAccelMag() const {
    return sqrt(pow(data.x,2) + pow(data.y,2) + pow(data.z,2));
}
