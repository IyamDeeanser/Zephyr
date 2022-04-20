#include <GPS.h>

GPS_Stats::GPS_Stats(){

    //Initializes everything to 0
        //If GPS not responding then all variables will be equal to zero, and it will be obvious there is a problem
    generalLat = "Nothing";
    generalLon = "Also Nothing";
    altitude = 0.0;
    speed = 0.0;
    angle= 0.0;
    numSatellites = 0;
}

void GPS_Stats::begin(){
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

void GPS_Stats::update(){

    //Reads NMEA character by character 
    char c = GPS.read();

    if (ZephyrGPSECHO){
        if (c) Serial.print(c);
    }
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
        generalLat = GPS.latitude;
        SerialUSB.print("Latitude: ");
        SerialUSB.print(generalLat);

        generalLon = GPS.longitude;
        SerialUSB.print("Longitude: ");
        SerialUSB.print(generalLon);

        speed = GPS.speed;
        SerialUSB.print("Speed: ");
        SerialUSB.print(speed);

        angle = GPS.angle;
        SerialUSB.print("Angle: ");
        SerialUSB.print(angle);

        altitude = (GPS.altitude)/100.0;

        numSatellites = (int)GPS.satellites;
    }
    else{
        SerialUSB.print("Ew no fix again. :(");
    }
  }
}
