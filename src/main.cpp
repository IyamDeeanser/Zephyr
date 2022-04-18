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
}

void loop() 
{
  Time.update();
  SDLogger.update();
  TLMSender.update();
  // todo SELECT STATE GIVEN CONDITION (in case device restarts mid flight)
  switch(State) {
    case GROUND_IDLE:
      if(TLM.read() == GOTO_LAUNCH_READY) {
        SDLogger.resume(); // starts logging data 
        TLMSender.setFrequency(RATE_HIGH);
        State = LAUNCH_READY;
        // todo MAYBE start GPS connection here (battery reasons)
        // ? Why is Camera Manually enabled??
        // todo MAYBE abort mission if communication with GCS isnt established by this point (Tim's idealol)
        // ? What's the point of signal tests? (also it should be done by ground station)
        // Gyro.getGyroBias();  // ! I Don't know if I'm doing this properly
      }
      // @ Maybe auto Switch to ascent IF mag. of velocity > 10 m/s
      break;

    case LAUNCH_READY: 
      if(Accel.getAccelMag() > 13 || TLM.read() == GOTO_POWERED_ASCENT) {
        State = POWERED_ASCENT;
        SDLogger.setFrequency(RATE_HIGH); // ! SINCE THE Acceleration must be > 13, the initial accleration won't be logged! (when the acc < 13)
        TLMSender.setFrequency(RATE_HIGH);
      }
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
    NA,
    NA,
    NA,
    vec3(),
    Voltage::getVoltage(),
    states::stateToStr(State),
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
    NA,
    NA,
    NA,
    vec3(),
    Voltage::getVoltage(),
    states::stateToStr(State),
    Cam.getState(),
    NA,
    Time.currentTimeSec,
    Time.launchTime  / 1000000.0, // Converting Micro -> Seconds
    Baro.pressure,
    Gyro.temperature,
    Baro.temperature,
    NA,
    NA,
    NA
  );
}
