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
GPS_Variables GPSVar; 
Quaternion Quat;
PID RollPID;
ReactionWheel RCW;
LED led(18, 17, 16);

// Global Constants
const float G = 9.80665;

// Prototype Functions
void logData();
void sendData();

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

  //GPS Variables
  GPSVar.GPSBegin();

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
  String Command;

  if(State != AVI_ERROR){
    SDLogger.update();
    TLMSender.update();
    //GPS.update();
    Baro.update();
    Accel.update();
    imu.update();
    GPSVar.GPSUpdate();

    Command = TLM.read();
    if(State >= POWERED_ASCENT && State != MISSION_COMPLETE) Quat.update(imu, Time); // what happens if quat updats before powered ascent?
  }

  // todo SELECT STATE GIVEN CONDITION (in case device restarts mid flight)
  switch(State) {
    case GROUND_IDLE:
      led.flash(led.yellow, led.green, 1000000, 50000, Time.currentTimeMicro, 13, 1100);

      // // !! Brownout (Ghetto?)
      // const static float startupAltitude = Baro.altitude;
      // if(Baro.altitude > startupAltitude + 50) gotoState(POWERED_ASCENT);
      // if(Baro.rawAltitude < Baro.altitude - 50) gotoState(PARACHUTE_DESCENT); // ! may have bugs since many stages are skipped
      // // @ Maybe auto Switch to ascent IF mag. of velocity > 10 m/s

      Baro.setAltitudeBias();

      if(Command == "EN"){ //Enable launch command
        Command = "";
        SDLogger.resume(); // starts logging data 
        TLMSender.setFrequency(RATE_HIGH);
        imu.getGyroBias(); // ! NOT TESTED!

        State = LAUNCH_READY;
        TLM.printlnStr("STATE: LAUNCH READY");
      }

      if(Command == "CL") {
        Command = "";
        Cam.turnOff();
      }

      if(Command == "CH") {
        Command = "";
        Cam.turnOn();
      }

      break;

    case LAUNCH_READY: 
      led.flash(led.yellow, led.green, 1000000, 50000, Time.currentTimeMicro, 13, 1100);

      Baro.setAltitudeBias();
      imu.getGyroBias();

      if(abs(Accel.data.x) >= 13 || Command == "AS") {
        Command = "";
        Cam.turnOn(); //For safety
        SDLogger.setFrequency(RATE_HIGH);
        Time.logLaunch();
        if (!imu.biasComplete) TLM.printlnStr("WARNING: GYRO BIAS INCOMPLETE!");
        State = POWERED_ASCENT;
        TLM.printlnStr("STATE: POWERED ASCENT");
      }

      if(Command == "CL") {
        Command = "";
        Cam.turnOff();
      }

      if(Command == "CH") {
        Command = "";
        Cam.turnOn();
      }

      if(Command == "CH") {
        Command = "";
        //imu.getGyroBias wont work more than once right now so we cant do this 
      }

      break;

    case POWERED_ASCENT:
      led.party(Time.currentTimeMicro, 13, 1000);

      if(abs(Accel.data.x) <= 2 || Command == "AS") {
        Command = "";
        SDLogger.setFrequency(RATE_MEDIUM);
        State = UNPOWERED_ASCENT;
        TLM.printlnStr("STATE: UNPOWERED ASCENT");
      }
      break;

    case UNPOWERED_ASCENT:
      led.flash(led.purple, led.white, 350000, 40000, Time.currentTimeMicro, 13, 1400);

      if(Accel.getAccelMag() >= 5 || Command == "AS") {
        Command = "";
        State = SEPARATION;
        TLM.printlnStr("STATE: SEPARATION");
      }
      break;
    
    case SEPARATION:
      led.flash(led.white, led.blue, 350000, 40000, Time.currentTimeMicro, 13, 1100);
      
      if(Baro.altitudeAGL > Baro.apogee) {
        Baro.apogee = Baro.altitudeAGL;
        Baro.apogeeTime = millis();
      }

      if((millis() - Baro.apogeeTime) >= 500 || Command == "AS") {
        Command = "";
        SDLogger.setFrequency(RATE_HIGH);
        State = PARACHUTE_DESCENT;
        TLM.printlnStr("APOGEE REACHED! Apogee: " + String(Baro.apogee));
        TLM.printlnStr("STATE: PARACHUTE DESCENT");
      }

      break;

    case PARACHUTE_DESCENT:
      led.flash(led.purple, led.white, 350000, 40000, Time.currentTimeMicro, 13, 1400);

      static unsigned int parachuteDescentStartTime = millis();

      if (millis() > parachuteDescentStartTime + 10000 || Command == "AS") {
        Command = "";
        State = ROLL_CONTROL;
        TLM.printlnStr("STATE: ROLL CONTROL");
      }

      break;

    case ROLL_CONTROL:
      led.flash(led.yellow, led.green, 600000, 45000, Time.currentTimeMicro, 13, 1100);

      RollPID.update(Time, Quat.roll);
      RCW.writeWheelOutput(RollPID.Output);

      if(Command == "SP") {
        Command = "";
        RollPID.setSetpoint(90);
      }

      if(Baro.altitudeAGL <= 50 || Command == "AS") {
        Command = "";
        SDLogger.setFrequency(RATE_MEDIUM);
        State = LANDING_DETECT;
        TLM.printlnStr("STATE: LANDING");
      }
      
      break;

    case LANDING_DETECT: // ! untested
      led.flash(led.blue, led.white, 350000, 40000, Time.currentTimeMicro, 13, 1380);

      static float loggedAlt = Baro.altitudeAGL;
      static long loggedAltTime = millis();
      
      if (abs(loggedAlt - Baro.altitudeAGL) > 1) { // ! 1 might be to small
        loggedAlt = Baro.altitudeAGL;
        loggedAltTime = millis();
      } else if (millis() - loggedAltTime > 5000) {
        TLMSender.setFrequency(RATE_LOW);
        logFile.eject();
        State = MISSION_COMPLETE;
        TLM.printlnStr("MISSION COMPLETE!");
      }

      //If gyros are all below 0.1 rad/s, we have landed
      if(((abs(imu.bodyGyroRad.x) < 0.1) && (abs(imu.bodyGyroRad.y) < 0.1) && (abs(imu.bodyGyroRad.z) < 0.1)) || Command == "AS") {
        Command = "";
        TLMSender.setFrequency(RATE_LOW);
        logFile.eject();
        State = MISSION_COMPLETE;
        TLM.printlnStr("MISSION COMPLETE!");
      }

      break;

    case MISSION_COMPLETE:
      led.flash(led.red, led.white, 500000, 50000, Time.currentTimeMicro, 13, 1200);
      
      static unsigned int landingTime = millis();
      if((millis() - landingTime) >= 15000){ //leave 15 second delay before shutting camera off
        Cam.turnOff();
      }

      break;

    case AVI_ERROR:
      led.flash(led.red, led.yellow, 500000, 100000, Time.currentTimeMicro, 13, 900);

      break;

    default:
      TLM.printlnStr("STATE MACHINE ERROR: Sat is in an unrecognized state!");
  }  
}

// @ TEMP variable for unkonwn inputs
#define NA 0

void logData() {
  logFile.logData(
    vec3(Quat.roll, Quat.pitch, Quat.yaw), // orientation
    imu.bodyAccel, // acceleration
    Accel.data,
    imu.bodyGyroDeg, // Gyro 
    Baro.altitudeAGL, // altitude
    GPSVar.altitude, //Position from GPS
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
    GPSVar.numSatellites, //GPS sats
    GPSVar.latitude, //Lat 
    GPSVar.longitude //lon
  );
}

void sendData() { // ! not all data is here
  TLM.transmit(
    vec3(Quat.roll, Quat.pitch, Quat.yaw), // orientation 
    (Accel.getAccelMag() > 15 * G) ? Accel.data : imu.bodyAccel, // acceleration
    imu.bodyGyroDeg, // Gyro 
    Baro.altitudeAGL, // altitude
    GPSVar.altitude, //GPS altitude
    RCW.getValue(), // RCW value
    Voltage::getVoltage(), // batt voltage
    State, // (int) state
    Cam.getState(), // (bool) cam state
    RCW.getState(), // (bool) rwState 
    Time.currentTimeSec, // on time in secs
    Time.currentTimeSec - (Time.launchTime  / 1000000.0), // Converting Micro -> Seconds
    Baro.pressure, // imu temp
    imu.temperature, // imu temp
    Baro.temperature,
    GPSVar.numSatellites, //GPS sats
    GPSVar.latitude, //Lat 
    GPSVar.longitude //lon
  );
}
