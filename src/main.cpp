// ! We should write a bit of info abt this project & abt team zephyr

//⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝
//⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇
//⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀
//⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀
//⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀
//⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀
//⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀
//⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀
//⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
//⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
//⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
//⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
//⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// 
//      no descriptions?

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
#include "Quaternions/Quaternions.h"
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
Quaternion Quat;

// Global Constants
const float G = 9.80;

// Prototype Functions
void logData();
void sendData();
void checkForCommands();
void gotoState(States target);

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
  logFile.println("ori.x,ori.y,ori.z,accel.x,accel.y,accel.z,accelHighG.x,accelHighG.y,accelHighG.z,gyro.x,gyro.y,gyro.z,altitude,rwValue,batteryVoltage,systemState,cameraState,RWState,onTimeSec,flightTimeSec,pressure,imuTemp,baroTemp,GPSSats,latitude,longitude");
  // ^ printing header log file
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

  // Quaternions
  Quat.begin();

  // Coroutines
  SDLogger.begin(logData);
  TLMSender.begin(sendData);
  SDLogger.pause(); // SD Card starts logging at Launch Ready

  // GPS
  GPS.begin();

  TLM.printlnStr("SETUP COMPLETE"); 
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
  checkForCommands();
  if(State >= POWERED_ASCENT) Quat.update(Gyro, Time); // what happens if quat updats before powered ascent?

  // todo SELECT STATE GIVEN CONDITION (in case device restarts mid flight)
  switch(State) {
    case GROUND_IDLE:
      // !! Brownout (Ghetto?)
      const static float startupAltitude = Baro.altitude;
      if(Baro.altitude > startupAltitude + 50) gotoState(POWERED_ASCENT);
      if(Baro.rawAltitude < Baro.altitude - 50) gotoState(PARACHUTE_DESCENT); // ! may have bugs since many stages are skipped
      // @ Maybe auto Switch to ascent IF mag. of velocity > 10 m/s
      break;

    case LAUNCH_READY: 
      Gyro.getGyroBias(); // ! NOT TESTED!
      if(abs(Accel.data.x) > 13) { // alternative, Accel.getAccelMag();
        gotoState(POWERED_ASCENT);
      }
      break;

    case POWERED_ASCENT:
      if(Accel.getAccelMag() < 2 * G) { 
        gotoState(UNPOWERED_ASCENT);
      }
      break;

    case UNPOWERED_ASCENT:
      // ? Check for < 16g??
      if(Accel.getAccelMag() < 4 * G) { // ? Is there a possiblity that it never reaches < 4?
        gotoState(SEPARATION);
      }
      break;
    
    case SEPARATION:
      if(Baro.rawAltitude < Baro.apogee && millis() >= Baro.apogeeTime + 1000) { // @ raw Alt is used here in case alt isn't set.
        gotoState(PARACHUTE_DESCENT);
      }
      break;

    case PARACHUTE_DESCENT:
      static unsigned int parachuteDescentStartTime = millis();
      // todo add manual switcdh to roll control
      if (millis() > parachuteDescentStartTime + 2000)  { // ! delay is arbritrary
        gotoState(ROLL_CONTROL);
      }

      break;

    case ROLL_CONTROL:
      // ! PID & RCW not done yet
      // ! we need a bool that tells us if we are controlling roll manually 
      // todo add manual roll
      if(Baro.altitude < 50) gotoState(LANDING); // ! maybe call Baro.alt -> Baro.RELATIVEALT
      break;

    case LANDING: // ! untested
      static int loggedAlt = Baro.altitude;
      static long loggedAltTime = millis();
      
      if (abs(loggedAlt - Baro.altitude) > 1) { // ! 1 might be to small
        loggedAlt = Baro.altitude;
        loggedAltTime = millis();
      } else if (millis() - loggedAltTime > 5000) {
        gotoState(MISSION_COMPLETE);
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
    
    if(State > LAUNCH_READY && Time.launchTime != 0 && Time.currentTimeMicro - Time.launchTime > 100000 * 60 * 5) { // ! potentially dangerious code
      State = ABORT; // equibilent of mission complete, but if this every happens we know that something is wrong.
      logFile.eject();
      // settingsFile.eject();
      TLMSender.setFrequency(LOW);
    }
  }  
}

// @ TEMP variable for unkonwn inputs
#define NA 0

void logData() { // ! doesnt match sendData
  logFile.logData(
    vec3(Quat.pitch, Quat.yaw, Quat.roll), // orientation // ! i dont know if this is correct
    Gyro.bodyAccel, // acceleration
    Accel.data,
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

void sendData() { // ! not all data is here
  TLM.transmit(
    vec3(Quat.pitch, Quat.yaw, Quat.roll), // orientation // ! i dont know if this is correct
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

// ! NOT TESTED!
void checkForCommands() { // ! i might be paranoid but having unencrypted data means anyone w/ a yagi can intercept & send malicicous commands
  // Safeguards in code might peg us
  String Command = TLM.read();
  if(Command == "GOTO LAUNCH READY") {
    gotoState(LAUNCH_READY);
  }
  if(Command == "GOTO POWERED ASCENT") {
    gotoState(POWERED_ASCENT);
    return;
  }
  if(Command == "GOTO ROLL CONTROL") {
    State = ROLL_CONTROL;
    return;
  }
  if(Command == "") {
    return;
  }
  if(Command == "") {
    return;
  }
  if(Command == "SHUTDOWN") { // ! DANGEROUS to add
    return;
  }
}

void gotoState(States target) { // ! we can add a FORCE parameter to bypass safeguards
  switch (target)
  {
  case GROUND_IDLE:
    // ! this probably means theres an error in our program.
    return;

  case LAUNCH_READY:
    if(State != GROUND_IDLE) return;
    SDLogger.resume(); // starts logging data 
    TLMSender.setFrequency(RATE_HIGH);
    Baro.setAltitudeBias();
    // todo MAYBE start GPS connection here (battery reasons)
    State = LAUNCH_READY;
    TLM.printlnStr("STATE: LAUNCH READY");
    return;

  case POWERED_ASCENT:
    if(State >= POWERED_ASCENT) return; // !! should these safeguards be here?, will peg us if we go try to go back a state
    if(State == GROUND_IDLE) {
      Baro.setAltitudeBias();
      TLMSender.setFrequency(RATE_HIGH);
      SDLogger.resume();
    }
    Cam.turnOn(); // ! WARNING: putting this here means the first few seconds of lauch isn't recorded!
    SDLogger.setFrequency(RATE_HIGH);
    Time.logLaunch();
    if (!Gyro.biasComplete) TLM.printlnStr("WARNING: GYRO BIAS INCOMPLETE!");
    State = POWERED_ASCENT;
    TLM.printlnStr("STATE: POWER ASCENT");
    return;

  case UNPOWERED_ASCENT:
    SDLogger.setFrequency(RATE_MEDIUM);
    // if(State != POWERED_ASCENT) // @ do something
    State = UNPOWERED_ASCENT;
    TLM.printlnStr("STATE: UNPOWERED ASCENT");
    return;

  case SEPARATION:
    TLM.printlnStr("SEPERATION!");
    State = SEPARATION;
    TLM.printlnStr("STATE: SEPARATION");
    return;

  case PARACHUTE_DESCENT:
    SDLogger.setFrequency(RATE_HIGH);
    TLM.printlnStr("APOGEE REACHED! Agopee: " + String(Baro.apogee - Baro.bias));
    State = PARACHUTE_DESCENT;
    TLM.printlnStr("STATE: PARACHUTE DESCENT");
    return;

  case ROLL_CONTROL:
    // todo CONNECT DC MOTOR DIGITALLY
    State = ROLL_CONTROL;
    TLM.printlnStr("STATE: ROLL CONTROL");
    return;

  case LANDING:
    // todo disable motor
    SDLogger.setFrequency(RATE_MEDIUM);
    State = LANDING;
    TLM.printlnStr("STATE: LANDING");
    return;

  case MISSION_COMPLETE:
      Cam.turnOff();
      logFile.eject();
      // ! maybe log some settings data, & eject that too!
      TLMSender.setFrequency(RATE_LOW);
      State = MISSION_COMPLETE;
      TLM.printlnStr("MISSION COMPLETE!");
    return;

  case ABORT:
    // ! this means something bad happened do we need this?
    return;

  default:
    break;
  }
}