#include "Accel.h"

void Accelerometer::begin(){
    if( !kxAccel.begin() ){
        // ! DO SOMETHING 
        // while(1);
    }
    if( !kxAccel.initialize(DEFAULT_SETTINGS)){ // ! is this default settings?
        Serial.println("Could not initialize the chip.");
        while(1);
    }

    kxAccel.setRange(KX134_RANGE32G);
}



void Accelerometer::update(){
    kxData = kxAccel.getAccelData();
    data.set(kxData.xData,kxData.yData,kxData.zData);
}
