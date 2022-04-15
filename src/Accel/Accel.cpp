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
