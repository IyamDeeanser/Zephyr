#include "Barometer.h"
#include <BMP388_DEV.h>

BMP388_DEV bmp388;

bool Barometer::begin() {
    if (!bmp388.begin()) {
        return false;
    }

    bmp388.setTimeStandby(TIME_STANDBY_20MS);
    bmp388.startNormalConversion();
    bmp388.setPresOversampling(OVERSAMPLING_X2);
    bmp388.setTempOversampling(OVERSAMPLING_SKIP);

    return true;
}

void Barometer::update() {
    bmp388.getMeasurements(temperature, pressure, rawAltitude);
}

float Barometer::getAltitude() {
    altitude = rawAltitude - bias;
    return altitude;
}


void Barometer::setAltitudeBias(){
    bias = rawAltitude;
}