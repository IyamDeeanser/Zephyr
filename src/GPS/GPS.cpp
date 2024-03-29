#include "GPS.h"

//Global variables :((
// Connect to the ZephyrGPS on the hardware I2C port
Adafruit_GPS GPS(&Wire);
#define Serial SerialUSB

//A timer to make sure data isn't jamming and updating properly
uint32_t timer = millis();

GPS_Variables::GPS_Variables(){
    //Latitude and Longitude Numbers 
    latitude = 0.0;
    longitude = 0.0;

    //Cardinal directions in N,E,S,W for latitude and longitude
    latDir = 'N';
    lonDir = 'W';

    //Other variables
    altitude = 0.0;
    speed = 0.0;
    angle = 0.0;
    numSatellites = 0;

    //Fix info
    fix = 0;
    fixQuality = 0;
}

//Converts lat/long in degree decimal minutes form to decimal degrees 
double GPS_Variables::convertToDecimalDegrees(double degMins){
    double result = 0.0;

    int degrees = (int) (degMins/100.0);
    double minutes = degMins - degrees*100;

    double leftOverDeg = minutes/60.0;

    result = degrees + leftOverDeg;

    return result;
}

bool GPS_Variables::GPSBegin(){

    if (!GPS.begin(0x10)){
        return false;
    } 

    //turns on RMC (recommended minimum) and GGA (fix data) including altitude
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate

    // Request updates on antenna status 
    GPS.sendCommand(PGCMD_ANTENNA);

    delay(1000);

    return true;
}

void GPS_Variables::GPSUpdate(){

    //Reads NMEA character by character 
    char c = GPS.read();

    // if a sentence is received, we can check the checksum, parse it...
    if (GPS.newNMEAreceived()) {
        // we can fail to parse a sentence in which case we should just wait for another
        if (!GPS.parse(GPS.lastNMEA())) {return;} 
    }

// approximately every 2 seconds or so, update the current stats
  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    fix = (int)GPS.fix;
    fixQuality = (int)GPS.fixquality;
    if (GPS.fix) {
        latitude = convertToDecimalDegrees(GPS.latitude);
        latDir = GPS.lat;

        if (latDir == 'S'){latitude *= -1;}

        longitude = convertToDecimalDegrees(GPS.longitude);
        lonDir = GPS.lon;

        if (lonDir == 'W'){longitude *= -1;}

        speed = GPS.speed;

        angle = GPS.angle;

        altitude = (GPS.altitude)/100.0;

        numSatellites = (int)GPS.satellites;
    }
    else{
        // SerialUSB.print("Ew no fix again. :(");
    }
  }
}
