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

  while(true) {
    Setup_Loop();
    delay(100); // ! BRUH this is not acceptable; it'll kill the entire sat for 0.1 seconds
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