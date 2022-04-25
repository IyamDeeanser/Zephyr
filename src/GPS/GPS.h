#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SPI.h>
#include <Wire.h>

// Set ZephyrGPSECHO to 'false' to turn off echoing the ZephyrGPS data to the Serial console
#define ZephyrGPSECHO false

struct GPS_Variables{

    //Latitude and Longitude Numbers 
        float latitude;
        float longitude;

        //Cardingal directions in N,E,S,W for latitude and longitude
        char latDir;
        char lonDir;

        //Other variables
        float altitude;
        float speed;
        float angle;
        int numSatellites;

        //Fix info
        int fix;
        int fixQuality;

    GPS_Variables();
    void GPSBegin();
    void GPSUpdate();
};

#endif
