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
// @ maybe DONT start GPS connection here (battery reasons)
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
  // todo ADD BROWNOUT SAFEGUARD
}

void loop() 
{
  Time.update();
  SDLogger.update();
  TLMSender.update();
  // BARO NEEDS TO BE UPDATED! EVERY LOOP
  // todo SELECT STATE GIVEN CONDITION (in case device restarts mid flight)
  switch(State) {
    case GROUND_IDLE:
      if(TLM.read() == GOTO_LAUNCH_READY) {
        SDLogger.resume(); // starts logging data 
        TLMSender.setFrequency(RATE_HIGH);
        State = LAUNCH_READY;
        Baro.setAltitudeBias();
        // todo MAYBE start GPS connection here (battery reasons)
        // ? Why is Camera Manually enabled??
        // todo MAYBE abort mission if communication with GCS isnt established by this point (Tim's idealol)
        // ? What's the point of signal tests? (also it should be done by ground station)
      }
      // @ Maybe auto Switch to ascent IF mag. of velocity > 10 m/s
      break;

    case LAUNCH_READY: 
      Gyro.getGyroBias(); // ! IF COMPUTER REBOOTS IN THE AIR, GYRO BIAS WILL NOT BE SET PROPERLY
      if(abs(Accel.data.x) > 13 || TLM.read() == GOTO_POWERED_ASCENT) { // alternative, Accel.getAccelMag();
        State = POWERED_ASCENT;
        SDLogger.setFrequency(RATE_HIGH);
        TLMSender.setFrequency(RATE_HIGH);
        if (Gyro.biasComplete) {
          TLM.printlnStr("GYRO BIAS COMPLETE");
        } else {
          TLM.printlnStr("ERROR: GYRO BIAS INCOMPLETEL!");
        }
        // ! LOG BOTH ACCELS, BUT ONLY TRANSMIT ONE (why not do both tho?)
      }
      break;

    case POWERED_ASCENT:
      if(Accel.getAccelMag() < 2) { // ? Is 2 the right term to use?
        State = UNPOWERED_ASCENT;
        // ! Switch to low G-Acc Readings
        SDLogger.setFrequency(RATE_MEDIUM);
      }
      break;

    case UNPOWERED_ASCENT:
      // ? Check for < 16g??
      // ? why check for x axis only?? 
      if(Accel.getAccelMag() < 4) { // ! WHY IS IT 2 for POWERED & 4 for SEP? WHY ONLY GET X AXIS??
        State = SEPARATION;
        TLM.printlnStr("SEPERATION!");
      }
      break;
    
    case SEPARATION:
      // ?? nothing happens here
      
      break;

    case APOGEE:
      // ?? nothing happens here
      break;

    case PARACHUTE_DESCENT: // !! Currently no way to get to this part of code

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
      TLM.printlnStr("MISSION ABORTED!");
      break;

    default:
      TLM.printlnStr("STATE MACHINE ERROR: Sat is in an unrecognized state!");
  }
  // todo listen for commands from GCS
  // ! SIGNALS ARE OFTEN DISTORTED, DEPLOY COUNTER-MEASURES!
  // todo Manual State-Switcher based on GCS commands
}

// TEMP variable for varialbes I don't have
#define NA 0

void logData() {
  logFile.logData(
    vec3(),
    Accel.data,
    Gyro.bodyGyroDeg,
    Baro.getAltitude(),
    NA,
    NA,
    vec3(),
    Voltage::getVoltage(),
    State,
    Cam.getState(),
    NA,
    Time.currentTimeSec, // ? Maybe use Micro for SD for more precision
    Time.launchTime, // ? Micro too?
    Baro.pressure,
    Gyro.temperature,
    Baro.temperature,
    NA,
    NA,
    NA
  );
}

void sendData() {
  TLM.transmit(
    vec3(),
    Accel.data,
    Gyro.bodyGyroDeg,
    Baro.getAltitude(),
    NA,
    NA,
    vec3(),
    Voltage::getVoltage(),
    State,
    Cam.getState(), // ! Bool
    NA,
    Time.currentTimeSec,
    Time.launchTime  / 1000000.0, // Converting Micro -> Seconds
    Baro.pressure,
    Gyro.temperature,
    Baro.temperature,
    NA,
    NA,
    NA,
    0
  );
}
