// Test code for Adafruit ZephyrGPS That Support Using I2C
//
// This code shows how to parse data from the I2C ZephyrGPS
//
// Pick one up today at the Adafruit electronics shop
// and help support open source hardware & software! -ada

#include <Arduino.h>
#include <Adafruit_GPS.h>

// Connect to the ZephyrGPS on the hardware I2C port
Adafruit_GPS ZephyrGPS(&Wire);

// Set ZephyrGPSECHO to 'false' to turn off echoing the ZephyrGPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw ZephyrGPS sentences
#define ZephyrGPSECHO false

uint32_t timer = millis();


void setup()
{
  //while (!Serial);  // uncomment to have the sketch wait until Serial is ready

  // connect at 115200 so we can read the ZephyrGPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("Adafruit I2C ZephyrGPS library basic test!");

<<<<<<< HEAD
  while(true) {
    Setup_Loop();
    delay(100); // ! BRUH this is not acceptable; it'll kill the entire sat for 0.1 seconds
=======
  // 9600 NMEA is the default baud rate for Adafruit MTK ZephyrGPS's- some use 4800
  ZephyrGPS.begin(0x10);  // The I2C address to use is 0x10
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  ZephyrGPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //ZephyrGPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  ZephyrGPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  ZephyrGPS.sendCommand(PGCMD_ANTENNA);

  delay(1000);

  // Ask for firmware version
  ZephyrGPS.println(PMTK_Q_RELEASE);
}

void loop() // run over and over again
{
  // read data from the ZephyrGPS in the 'main loop'
  char c = ZephyrGPS.read();
  // if you want to debug, this is a good time to do it!
  if (ZephyrGPSECHO)
    if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (ZephyrGPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    Serial.println(ZephyrGPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!ZephyrGPS.parse(ZephyrGPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
>>>>>>> e4e760414b35a0469aff46b25b3c628f5eacbc42
  }

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    Serial.print("\nTime: ");
    if (ZephyrGPS.hour < 10) { Serial.print('0'); }
    Serial.print(ZephyrGPS.hour, DEC); Serial.print(':');
    if (ZephyrGPS.minute < 10) { Serial.print('0'); }
    Serial.print(ZephyrGPS.minute, DEC); Serial.print(':');
    if (ZephyrGPS.seconds < 10) { Serial.print('0'); }
    Serial.print(ZephyrGPS.seconds, DEC); Serial.print('.');
    if (ZephyrGPS.milliseconds < 10) {
      Serial.print("00");
    } else if (ZephyrGPS.milliseconds > 9 && ZephyrGPS.milliseconds < 100) {
      Serial.print("0");
    }
    Serial.println(ZephyrGPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(ZephyrGPS.day, DEC); Serial.print('/');
    Serial.print(ZephyrGPS.month, DEC); Serial.print("/20");
    Serial.println(ZephyrGPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)ZephyrGPS.fix);
    Serial.print(" quality: "); Serial.println((int)ZephyrGPS.fixquality);
    if (ZephyrGPS.fix) {
      Serial.print("Location: ");
      Serial.print(ZephyrGPS.latitude, 4); Serial.print(ZephyrGPS.lat);
      Serial.print(", ");
      Serial.print(ZephyrGPS.longitude, 4); Serial.println(ZephyrGPS.lon);
      Serial.print("Speed (knots): "); Serial.println(ZephyrGPS.speed);
      Serial.print("Angle: "); Serial.println(ZephyrGPS.angle);
      Serial.print("Altitude: "); Serial.println(ZephyrGPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)ZephyrGPS.satellites);
    }
  }
}