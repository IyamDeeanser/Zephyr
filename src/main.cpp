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
#include "PID/PID.h"
#include "RCW/RCW.h"
#include "LED/LED.h"

#define Serial SerialUSB

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
IMU imu;
Coroutine SDLogger;
Coroutine TLMSender;
GPS_Stats GPS; // ! NOT WORKING
Quaternion Quat;
PID Roll;
ReactionWheel RCW;
LED led(18, 17, 16);

// Global Constants
const float G = 9.80665;

// Prototype Functions
void logData();
void sendData();
void checkForCommands();
void gotoState(States target);

// setup loop
void setup() {
  led.colour(led.purple);

  delay(1000);
  
  // Telemetry
  TLM.begin();

  Serial.begin(9600);
  
  // SD card
  if(!SD_Card::begin(15)) {
    TLM.printlnStr("SD CARD FAILED TO INITIALIZE!");
    Serial.println("SD CARD FAILED TO INITIALIZE!");
    State = AVI_ERROR;
  }
  
  // Accelerometer
  if(!Accel.begin()) {
    TLM.printlnStr("HIGH-G ACCELEROMETER FAILED TO INITIALIZE!");
    Serial.println("HIGH-G ACCELEROMETER FAILED TO INITIALIZE!");
    State = AVI_ERROR;
  }

  // Barometer 
  if(!Baro.begin()) {
    TLM.printlnStr("BAROMETER FAILED TO INITIALIZE!");
    Serial.println("BAROMETER FAILED TO INITIALIZE!");
    State = AVI_ERROR;
  }

  // Inertial Measurement Unit
  if(!imu.begin()) {
    TLM.printlnStr("IMU FAILED TO INITIALIZE!");
    Serial.println("IMU FAILED TO INITIALIZE!");
    State = AVI_ERROR;
  }

  // GPS
  //GPS.begin();

  if(State != AVI_ERROR){
    // camera
    Cam.initialize();

    // Quaternions
    Quat.begin();

    // // Files
    String flightFolderPath = SD_Card::createNewDir();
    logFile.begin("data.csv", flightFolderPath);
    logFile.println("Ori x (deg),Ori y (deg),Ori z (deg),Accel x (m/s^2),Accel y (m/s^2),Accel z (m/s^2),AccelHiG x (m/s^2),AccelHiG y (m/s^2),AccelHiG z (m/s^2),Gyro x (deg/s),Gyro y (deg/s),Gyro z (deg/s),Baro Alt AGL (m),GPS Altitude (m),RW Value,Voltage,State,Cam State,RW State,On Time (sec),Flight Time (sec),Pressure (hPa),IMU Temp (C),Baro Temp (C),GPS Sats,Latitude,Longitude");
    // ^ printing header log file
    settingsFile.begin("settings.txt", flightFolderPath);

    // Coroutines
    SDLogger.begin(logData);
    TLMSender.begin(sendData);
    SDLogger.pause(); // SD Card starts logging at Launch Ready

    TLM.printlnStr("SETUP COMPLETE"); 
    Serial.println("SETUP COMPLETE");
  }
}

void loop() 
{
  // updates objects
  Time.update();

  if(State != AVI_ERROR){
    SDLogger.update();
    TLMSender.update();
    //GPS.update();
    Baro.update();
    Accel.update();
    imu.update();
    checkForCommands();
    if(State >= POWERED_ASCENT && State != MISSION_COMPLETE) Quat.update(imu, Time); // what happens if quat updats before powered ascent?
  }

  // todo SELECT STATE GIVEN CONDITION (in case device restarts mid flight)
  switch(State) {
    case GROUND_IDLE:
      led.flash(led.yellow, led.green, 1000000, 50000, Time.currentTimeMicro, 13, 1100);

      // !! Brownout (Ghetto?)
      const static float startupAltitude = Baro.altitude;
      if(Baro.altitude > startupAltitude + 50) gotoState(POWERED_ASCENT);
      if(Baro.rawAltitude < Baro.altitude - 50) gotoState(PARACHUTE_DESCENT); // ! may have bugs since many stages are skipped
      // @ Maybe auto Switch to ascent IF mag. of velocity > 10 m/s
      break;

    case LAUNCH_READY: 
      led.flash(led.yellow, led.green, 1000000, 50000, Time.currentTimeMicro, 13, 1100);

      imu.getGyroBias(); // ! NOT TESTED!
      if(abs(Accel.data.x) > 13) { // alternative, Accel.getAccelMag();
        gotoState(POWERED_ASCENT);
      }
      break;

    case POWERED_ASCENT:
      led.party(Time.currentTimeMicro, 13, 1000);

      if(Accel.getAccelMag() < 2 * G) { 
        gotoState(UNPOWERED_ASCENT);
      }
      break;

    case UNPOWERED_ASCENT:
      led.flash(led.purple, led.white, 350000, 40000, Time.currentTimeMicro, 13, 1400);

      // ? Check for < 16g??
      if(Accel.getAccelMag() < 4 * G) { // ? Is there a possiblity that it never reaches < 4?
        gotoState(SEPARATION);
      }
      break;
    
    case SEPARATION:
      led.flash(led.white, led.blue, 350000, 40000, Time.currentTimeMicro, 13, 1100);

      if(Baro.rawAltitude < Baro.apogee && millis() >= Baro.apogeeTime + 1000) { // @ raw Alt is used here in case alt isn't set.
        gotoState(PARACHUTE_DESCENT);
      }
      break;

    case PARACHUTE_DESCENT:
      led.flash(led.purple, led.white, 350000, 40000, Time.currentTimeMicro, 13, 1400);

      static unsigned int parachuteDescentStartTime = millis();
      // todo add manual switcdh to roll control
      if (millis() > parachuteDescentStartTime + 5000)  { // ! delay is arbritrary
        gotoState(ROLL_CONTROL);
      }

      break;

    case ROLL_CONTROL:
      led.flash(led.yellow, led.green, 600000, 45000, Time.currentTimeMicro, 13, 1100);

      // ! PID & RCW not done yet
      // ! we need a bool that tells us if we are controlling roll manually 
      // todo add manual roll
      if(Baro.altitude <= 50) {
        gotoState(LANDING_DETECT); // ! maybe call Baro.alt -> Baro.RELATIVEALT
      }

      Roll.update(Time,imu);
      RCW.writeWheelOutput(Roll.Output);
      
      break;

    case LANDING_DETECT: // ! untested
      led.flash(led.blue, led.white, 350000, 40000, Time.currentTimeMicro, 13, 1380);

      static float loggedAlt = Baro.altitude;
      static long loggedAltTime = millis();
      
      if (abs(loggedAlt - Baro.altitude) > 1) { // ! 1 might be to small
        loggedAlt = Baro.altitude;
        loggedAltTime = millis();
      } else if (millis() - loggedAltTime > 5000) {
        gotoState(MISSION_COMPLETE);
      }

      //If gyros are all below 0.1 rad/s, we have landed
      if((abs(imu.bodyGyroRad.x) < 0.1) && (abs(imu.bodyGyroRad.y) < 0.1) && (abs(imu.bodyGyroRad.z) < 0.1)){ 
        gotoState(MISSION_COMPLETE);
      }

      break;

    case MISSION_COMPLETE:
      led.flash(led.red, led.white, 500000, 50000, Time.currentTimeMicro, 13, 1200);

      // ! This does nothing
      break;

    case AVI_ERROR:
      led.flash(led.red, led.yellow, 500000, 100000, Time.currentTimeMicro, 13, 900);
      // ! This does nothing
      break;

    default:
      TLM.printlnStr("STATE MACHINE ERROR: Sat is in an unrecognized state!");
    
    // if(State > LAUNCH_READY && Time.launchTime != 0 && Time.currentTimeMicro - Time.launchTime > 100000 * 60 * 5) { // ! potentially dangerious code
    //   State = ABORT; // equibilent of mission complete, but if this every happens we know that something is wrong.
    //   logFile.eject();
    //   // settingsFile.eject();
    //   TLMSender.setFrequency(LOW);
    // }
  }  
}

// @ TEMP variable for unkonwn inputs
#define NA 0

void logData() { // ! doesnt match sendData
  logFile.logData(
    vec3(Quat.pitch, Quat.yaw, Quat.roll), // orientation // ! i dont know if this is correct
    imu.bodyAccel, // acceleration
    Accel.data,
    imu.bodyGyroDeg, // Gyro 
    Baro.altitude, // altitude
    NA, //Position from GPS
    RCW.getValue(), // RCW value
    Voltage::getVoltage(), // batt voltage
    State, // (int) state
    Cam.getState(), // (bool) cam state
    RCW.getState(),
    Time.currentTimeSec, // on time in secs
    Time.currentTimeSec - (Time.launchTime  / 1000000.0), // Converting Micro -> Seconds
    Baro.pressure, // imu temp
    imu.temperature, // imu temp
    Baro.temperature,
    NA, //GPS sats
    NA, //Lat 
    NA //lon
  );
}

void sendData() { // ! not all data is here
  TLM.transmit(
    vec3(Quat.roll, Quat.pitch, Quat.yaw), // orientation // ! i dont know if this is correct
    (Accel.getAccelMag() > 15 * G) ? Accel.data : imu.bodyAccel, // acceleration
    imu.bodyGyroDeg, // Gyro 
    Baro.altitude, // altitude
    NA, //GPS altitude
    RCW.getValue(), // RCW value
    Voltage::getVoltage(), // batt voltage
    State, // (int) state
    Cam.getState(), // (bool) cam state
    RCW.getState(), // (bool) rwState // ! not sure
    Time.currentTimeSec, // on time in secs
    Time.currentTimeSec - (Time.launchTime  / 1000000.0), // Converting Micro -> Seconds
    Baro.pressure, // imu temp
    imu.temperature, // imu temp
    Baro.temperature,
    NA, //GPS sats
    NA, //Lat 
    NA //lon
  );
}

// ! NOT TESTED!
void checkForCommands() { // ! i might be paranoid but having unencrypted data means anyone w/ a yagi can intercept & send malicicous commands
  // Safeguards in code might peg us
  String Command = TLM.read();
  if(Command == "") return;

  if(Command == "GTLR") {
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
  // ! <AS> Advacned state, <CL> Camera off, <CH> Camera on <SP> State machine setpoint <GY> gyro debias
}

void gotoState(States target) { // ! we can add a FORCE parameter to bypass safeguards
  switch (target)
  {
  if(target != ROLL_CONTROL) RCW.writeWheelOutput(0); // ! ghetto code here, can fix later
  
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
    if (!imu.biasComplete) TLM.printlnStr("WARNING: GYRO BIAS INCOMPLETE!");
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
    State = ROLL_CONTROL;
    TLM.printlnStr("STATE: ROLL CONTROL");
    return;

  case LANDING_DETECT:
    SDLogger.setFrequency(RATE_MEDIUM);
    State = LANDING_DETECT;
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

  case AVI_ERROR:
    
    return;

  default:
    // ! if this happens we made an oopsies
    break;
  }
}