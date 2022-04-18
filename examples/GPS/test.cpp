#include "GPS.h"

GPS_Stats ZephyrGPS;

void setup(){
    ZephyrGPS.begin();
}

void loop(){
    ZephyrGPS.update();

    SerialUSB.print(ZephyrGPS.latitude);
    SerialUSB.print('\n');
    SerialUSB.print(ZephyrGPS.longitude);
    SerialUSB.print('\n');
    SerialUSB.print(ZephyrGPS.altitude);
    SerialUSB.print('\n');
    SerialUSB.print(ZephyrGPS.speed);
    SerialUSB.print('\n');
    SerialUSB.print(ZephyrGPS.angle);
    SerialUSB.print('\n');
    SerialUSB.print(ZephyrGPS.numSatellites);
    delay(100);
}
