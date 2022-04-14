#include "Accel.h"

bool Accelerometer::begin(){ 
    if( !kxAccel.begin()){
        return false;
    }
    if( !kxAccel.initialize(DEFAULT_SETTINGS)){ // ! is this default settings?
        return false;
    }
    kxAccel.setRange(KX134_RANGE64G);
    return true;
}



void Accelerometer::update(){
    kxData = kxAccel.getAccelData();
    data.set(kxData.xData,kxData.yData,kxData.zData);
}
