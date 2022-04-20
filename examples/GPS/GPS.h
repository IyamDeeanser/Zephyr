#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SPI.h>
#include <Wire.h>

// Set ZephyrGPSECHO to 'false' to turn off echoing the ZephyrGPS data to the Serial console
#define ZephyrGPSECHO false

class GPS_Stats{

public:
    //The GPS object
    Adafruit_GPS GPS;

    //A timer to make sure data isn't jamming and updating properly
    uint32_t timer = millis();

    //Value variables, public for simplicity 
    String generalLat;
    String generalLon;
    float altitude;
    float speed;
    float angle;
    int numSatellites;
    int fix;
    int fixQuality;

    //Constructor and update function declaration
    GPS_Stats();
    void begin();
    void update();
};

#endif
