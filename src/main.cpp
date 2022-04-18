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
// todo test & add libs above

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
// @json MAYBE start GPS connection here (battery reasons)
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
  // todo SELECT STATE GIVEN CONDITION (in case device restarts mid flight)
  switch(State) {
    case GROUND_IDLE:
      // setup
      if(GROUND_IDLE_SETUP) { // ! replace w/ state transition
        GROUND_IDLE_SETUP = false;
      }
      // loop
      // todo manual Trigger to go into launch ready
      
      break;

    case LAUNCH_READY:
      // setup
      if(LAUNCH_READY_SETUP) {
        LAUNCH_READY_SETUP = false;
        SDLogger.resume(); // starts logging data 
        TLMSender.setFrequency(RATE_HIGH);
        // todo MAYBE abort mission if communication with GCS isnt established by this point (Tim's idea lol)
        // todo MAYBE start GPS connection here (battery reasons)
      }
      // loop

      break;

    case POWERED_ASCENT:
      // setup
      if(POWERED_ASCENT_SETUP) {
        POWERED_ASCENT_SETUP = false;
      }
      // loop

      break;

    case UNPOWERED_ASCENT:
      // setup
      if(UNPOWERED_ASCENT_SETUP) {
        UNPOWERED_ASCENT_SETUP = false;
      }
      // loop

      break;
    
    case SEPARATION:
      // setup
      if(SEPARATION_SETUP) {
        SEPARATION_SETUP = false;
      }
      // loop

      break;

    case APOGEE:
      // setup 
      if(APOGEE_SETUP) {
        APOGEE_SETUP = false;
      }
      // loop

      break;

    case PARACHUTE_DESCENT:
      // setup
      if(PARACHUTE_DESCENT_SETUP) {
        PARACHUTE_DESCENT_SETUP = false;
      }
      // loop

      break;

    case ROLL_CONTROL:
      // setup
      if(ROLL_CONTROL_SETUP) {
        ROLL_CONTROL_SETUP = false;
      }
      // loop

      break;

    case MANUAL_ROLL_CONTROL:
      // setup
      if(MANUAL_ROLL_CONTROL_SETUP) {
        MANUAL_ROLL_CONTROL_SETUP = false;
      }
      // loop

      break;

    case LANDING:
      // setup
      if(LANDING_SETUP) {
        LANDING_SETUP = false;
      }
      // loop

      break;

    case MISSION_COMPLETE:
      // setup 
      if(MISSION_COMPLETE_SETUP) {
        MISSION_COMPLETE_SETUP = false;
      }
      // loop

      break;

    case ABORT:
      TLM.printlnStr("MISSION ABORTED!");
      break;

    default:
      TLM.printlnStr("STATE MACHINE ERROR: Sat is in an unrecognized state!");
  }
  // todo listen for commands from GCS
  // ! SIGNALS ARE OFTEN DISTORTED, DEPLOY COUNTER-MEASURES!
  // todo Manual State-Switcher based on GCS commands
}

void logData() {

}

void sendData() {

}
