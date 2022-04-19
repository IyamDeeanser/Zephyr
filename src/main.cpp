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
#include "GPS/GPS.h"
#include "Quats/quaternions.h"
// ! RCW not included
// ! PID not included
// ! Accel Orentation
// todo test & add libs above

// Global Objects
States State;
Timer Time;
Telemetry TLM;
SD_File logFile;
SD_File settingsFile; // ! we havent dont anything w/ this file yet
Camera Cam;
Accelerometer Accel;
Barometer Baro;
IMU Gyro;
Coroutine SDLogger;
Coroutine TLMSender;
GPS_Stats GPS; // ! NOT WORKING
Quat Quaternion;

// Global Constants
const float G = 9.80;

// Prototype Functions
void logData();
void sendData();
void checkForLanding();

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

  GPS.begin();

  TLM.printlnStr("INITALIZATION COMPLETE"); 
  // todo ADD BROWNOUT SAFEGUARD
}

void loop() 
{
  // updates objects
  Time.update();
  SDLogger.update();
  TLMSender.update();
  GPS.update();
  Baro.update();
  Accel.update();
  Gyro.update();
  if(State >= POWERED_ASCENT) Quaternion.calculateQuaternion(Gyro, Time);

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
      }
      // @ Maybe auto Switch to ascent IF mag. of velocity > 10 m/s
      break;

    case LAUNCH_READY: 
      Gyro.getGyroBias(); // ! NOT TESTED!
      if(abs(Accel.data.x) > 13 || TLM.read() == GOTO_POWERED_ASCENT) { // alternative, Accel.getAccelMag();
        State = POWERED_ASCENT;
        SDLogger.setFrequency(RATE_HIGH);
        TLMSender.setFrequency(RATE_HIGH);
        Quaternion.begin(); // ?? why does this need to be here
        Time.logLaunch();
        if (Gyro.biasComplete) {
          TLM.printlnStr("GYRO BIAS COMPLETE");
        } else {
          TLM.printlnStr("ERROR: GYRO BIAS INCOMPLETE!");
        }
        // ! LOG BOTH ACCELS, BUT ONLY TRANSMIT ONE (why not do both tho?) if > 15G use high g else use low g
      }
      break;

    case POWERED_ASCENT:
      if(Accel.getAccelMag() < 2 * G) { 
        State = UNPOWERED_ASCENT;
        // ! Switch to low G-Acc Readings
        SDLogger.setFrequency(RATE_MEDIUM);
      }
      break;

    case UNPOWERED_ASCENT:
      // ? Check for < 16g??
      // ? why check for x axis only?? 
      if(Accel.getAccelMag() < 4 * G) { // ? Is there a possiblity that it never reaches < 4?
        State = SEPARATION;
        TLM.printlnStr("SEPERATION!");
      }
      break;
    
    case SEPARATION:
      if(Baro.rawAltitude < Baro.apogee && millis() >= Baro.apogeeTime + 1000) { // @ raw Alt is used here in case alt isn't set.
        State = PARACHUTE_DESCENT;
        SDLogger.setFrequency(RATE_HIGH);
        TLM.printlnStr("APOGEE REACHED! Agopee: " + String(Baro.apogee - Baro.bias));
      }
      break;

    case PARACHUTE_DESCENT:
      static unsigned int parachuteDescentStartTime = millis();
      // todo add manual switcdh to roll control
      if (millis() > parachuteDescentStartTime + 2000)  { // ! delay is arbritrary
        State = ROLL_CONTROL;
      }

      break;

    case ROLL_CONTROL:
      // CONNECT DC MOTOR DIGITALLY
      // ! PID & RCW not done yet
      checkForLanding();
      break;

    case MANUAL_ROLL_CONTROL:
      // todo add manual
      checkForLanding(); 
      break;

    case LANDING: // ! untested
      static int loggedAlt = Baro.altitude;
      static long loggedAltTime = millis();
      
      if (abs(loggedAlt - Baro.altitude) > 1) { // ! 1 might be to small
        // todo auto stop logging when flight is > 1 min
        // todo manual mission complete
        loggedAlt = Baro.altitude;
        loggedAltTime = millis();
      } else if (millis() - loggedAltTime > 5000) {
        State = MISSION_COMPLETE;
        Cam.turnOff();
        logFile.eject();
        TLMSender.setFrequency(RATE_LOW);
      }

      break;

    case MISSION_COMPLETE:
      // ! This does nothing
      break;

    case ABORT:
      TLM.printlnStr("MISSION ABORTED!");
      break;

    default:
      TLM.printlnStr("STATE MACHINE ERROR: Sat is in an unrecognized state!");
  }
  // todo listen for commands from GCS
  // todo Manual State-Switcher based on GCS commands
  
}

// TEMP variable for varialbes I don't have
#define NA 0

void logData() { // ! doesnt match sendData
  logFile.logData(
    vec3(),
    Accel.data,
    Gyro.bodyGyroDeg,
    Baro.altitude,
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

void sendData() { // ! not all data is here
  TLM.transmit(
    vec3(Quaternion.pitch, Quaternion.yaw, Quaternion.roll), // orientation // ! i dont know if this is correct
    (Accel.getAccelMag() > 15 * G) ? Accel.data : Gyro.bodyAccel, // acceleration
    Gyro.bodyGyroDeg, // Gyro 
    Baro.altitude, // altitude
    NA, // RCW value
    Voltage::getVoltage(), // batt voltage
    State, // (int) state
    Cam.getState(), // (bool) cam state
    NA, // (bool) rwState // ! not sure
    Time.currentTimeSec, // on time in secs
    Time.launchTime  / 1000000.0, // Converting Micro -> Seconds
    Baro.pressure, // imu temp
    Gyro.temperature, // imu temp
    Baro.temperature,
    NA,
    NA,
    NA,
    0
  );
}

void checkForLanding() {
  if(Baro.altitude < 50) {
    State = LANDING;
    // todo disable motor
    SDLogger.setFrequency(RATE_MEDIUM);
  }
}