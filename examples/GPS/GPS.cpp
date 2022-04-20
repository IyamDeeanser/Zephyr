#define GPSECHO false
#include <Adafruit_GPS.h>
#include "GPS Variables.cpp"

void GPSBegin(Adafruit_GPS GPS){
    SerialUSB.begin(115200);
    SerialUSB.println("Please work omg :'(");
    GPS.begin(0x10); //Change address if needed depending on where GPS is

    //turns on RMC (recommended minimum) and GGA (fix data) including altitude
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate

    // Request updates on antenna status 
    GPS.sendCommand(PGCMD_ANTENNA);

    delay(1000);
    
    // Ask for firmware version
    GPS.println(PMTK_Q_RELEASE);
}

void GPSUpdate(Adafruit_GPS GPS, GPSVariables &GVar){
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
        if (c) Serial.print(c);
    // if a sentence is received, we can check the checksum, parse it...
    if (GPS.newNMEAreceived()) {
        Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
        if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
        return; // we can fail to parse a sentence in which case we should just wait for another
    }

// approximately every 2 seconds or so, update the current stats
  if (millis() - GVar.timer > 2000) {
    GVar.timer = millis(); // reset the timer
    GVar.fix = (int)GPS.fix;
    GVar.fixQuality = (int)GPS.fixquality;
    if (GPS.fix) {
        GVar.latitude = GPS.latitude;
        SerialUSB.print("Latitude: ");
        SerialUSB.print(GVar.latitude);

        GVar.longitude = GPS.longitude;
        SerialUSB.print("Longitude: ");
        SerialUSB.print(GVar.longitude);

        GVar.speed = GPS.speed;
        SerialUSB.print("Speed: ");
        SerialUSB.print(GVar.speed);

        GVar.angle = GPS.angle;
        SerialUSB.print("Angle: ");
        SerialUSB.print(GVar.angle);

        GVar.altitude = (GPS.altitude)/100.0;

        GVar.numSatellites = (int)GPS.satellites;
    }
    else{
        SerialUSB.print("Ew no fix again. :(");
    }
  }
}
