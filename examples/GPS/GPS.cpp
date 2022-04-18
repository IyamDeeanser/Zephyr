#include "GPS.h"

GPS_Stats::GPS_Stats(){

    //Initializes everything to 0
        //If GPS not responding then all variables will be equal to zero, and it will be obvious there is a problem
    latitude = 0.0;
    longitude = 0.0;
    altitude = 0.0;
    speed = 0.0;
    angle= 0.0;
    numSatellites = 0;
}

void GPS_Stats::begin(){
    ZephyrGPS.begin(0x10); //Change address if needed depending on where GPS is

    //turns on RMC (recommended minimum) and GGA (fix data) including altitude
    ZephyrGPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  
    ZephyrGPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate

    // Request updates on antenna status 
    ZephyrGPS.sendCommand(PGCMD_ANTENNA);

    delay(1000);
    
    // Ask for firmware version
    ZephyrGPS.println(PMTK_Q_RELEASE);
}

void GPS_Stats::update(){

    //Reads NMEA character by character 
    char c = ZephyrGPS.read();
    // if a sentence is received, we can check the checksum, parse it...
    if (ZephyrGPS.newNMEAreceived()) {
        // we can fail to parse a sentence in which case we should just wait for another
        if (!ZephyrGPS.parse(ZephyrGPS.lastNMEA())) {return;} 
    }

    //Updates each variable with new information
    latitude = ZephyrGPS.latitude;
    longitude = ZephyrGPS.longitude;
    altitude = ZephyrGPS.altitude;
    speed = ZephyrGPS.speed;
    angle= ZephyrGPS.angle;
    numSatellites = ZephyrGPS.satellites;
}
