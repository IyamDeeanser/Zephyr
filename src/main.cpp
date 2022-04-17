// ! We should write a bit of info abt this project & abt team zephyr

// Libraries
#include <Arduino.h>
#include "Settings/Settings.h" // ! We don't need this file
#include "States/States.h"
#include "Timer/Timer.h"
#include "Telemetry/Telemetry.h"
#include "SD_Card/SD_Card.h"
#include "Camera/Camera.h"
#include "Accel/Accel.h"
#include "Barometer/Barometer.h"
#include "IMU/IMU.h"
#include "Coroutine/Coroutine.h"
#include "Voltage/Voltage.h"
// ! GPS NOT INCLUDED
// ! Quaterions not included
// ! RCW not included
// ! PID not included
// ! Accel Orentation

// Global Objects
States State;
Timer Time;
Telemetry TLM;
SD_File logFile;
SD_File settingsFile;
Camera Cam;
Accelerometer Accel;
Barometer Baro;
IMU Gyro;
Coroutine SDLogger;
Coroutine TLMSender;

// Prototype Functions
void logData();
void sendData();

// setup loop
void setup() {
  // Telemetry
  TLM.begin();
  
  // SD card
  if(!SD_Card::begin(15))
    TLM.printlnStr("SD CARD FAILED TO INITIALIZE!");

  // Files
  String flightFolderPath = SD_Card::createNewDir();
  logFile.begin("file.txt", flightFolderPath);
  settingsFile.begin("settings.txt", flightFolderPath);

  // camera
  Cam.initialize();
  
  // Accelerometer
  if(!Accel.begin())
    TLM.printlnStr("HIGH-G ACCEROMETER FAILED TO INITIALIZE!");

  // Barometer 
  if(!Baro.begin())
    TLM.printlnStr("BAROMETER FAILED TO INITIALIZE!");

  // Inertial Measurement Unit
  if(!Gyro.begin())
    TLM.printlnStr("IMU FAILED TO INITIALIZE!");

  // Coroutines
  SDLogger.begin(logData);
  TLMSender.begin(sendData);
  SDLogger.pause(); // SD Card starts logging at Launch Ready

  TLM.printlnStr("INITALIZATION COMPLETE");
}

void loop() 
{
  Time.update();
  SDLogger.update();
  TLMSender.update();
  
  switch(State) {
    case GROUND_IDLE:

      break;

    case LAUNCH_READY:

      break;

    case POWERED_ASCENT:

      break;

    case UNPOWERED_ASCENT:

      break;
    
    case SEPARATION:

      break;

    case APOGEE:

      break;

    case PARACHUTE_DESCENT:

      break;

    case ROLL_CONTROL:

      break;

    case MANUAL_ROLL_CONTROL:

      break;

    case LANDING:

      break;

    case MISSION_COMPLETE:

      break;

    case ABORT:

      break;
  }
}

void logData() {

}

void sendData() {

}
