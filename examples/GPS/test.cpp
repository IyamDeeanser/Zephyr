#include "GPS.cpp"
#include "GPS Variables.cpp"
#include <Adafruit_GPS.h>

Adafruit_GPS ZephyrGPS;
GPSVariables GPSVar;

void setup(){
    GPSBegin(ZephyrGPS);
}

void loop(){
    GPSUpdate(ZephyrGPS, GPSVar);
    // SerialUSB.print("-----------------\n RotaSat GPS Testing: \n -----------------\n");
    // SerialUSB.print("Location: \n -----------------\n");
    // SerialUSB.print("Latitude: ");
    // SerialUSB.print(ZephyrGPS.generalLat);
    // SerialUSB.print('\n');
    // SerialUSB.print("Longitude: ");
    // SerialUSB.print(ZephyrGPS.generalLon);
    // SerialUSB.print('\n');
    // SerialUSB.print("-----------------\nAltitude: ");
    // SerialUSB.print(ZephyrGPS.altitude); SerialUSB.print(" m");
    // SerialUSB.print("\nSpeed: ");
    // SerialUSB.print(ZephyrGPS.speed); SerialUSB.print(" knots");
    // SerialUSB.print("\nAngle: ");
    // SerialUSB.print(ZephyrGPS.angle); SerialUSB.print(" degrees");
    // SerialUSB.print("\nNumber of Satellites Connected: ");
    // SerialUSB.print(ZephyrGPS.numSatellites);
    // SerialUSB.print('\n');
    // delay(2000);
}
