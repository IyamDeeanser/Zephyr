// Libraries
#include <Arduino.h>
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
SD_File dataFile; // ! we havent dont anything w/ this file yet
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
void ForceState(States target);

// setup loop
void setup() {
  led.colour(led.purple);

  delay(10000); // !! CHANGE THIS BACK
  
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

  //GPS
  if(!GPSVar.GPSBegin()) {
    TLM.printlnStr("GPS FAILED TO INITIALIZE!");
    Serial.println("GPS FAILED TO INITIALIZE!");
    State = AVI_ERROR;
  }

  if(State != AVI_ERROR){
    // camera
    Cam.initialize();

    // Quaternions
    Quat.begin();

    // // Files
    String flightFolderPath = SD_Card::createNewDir();
    logFile.begin("log.csv", flightFolderPath);
    logFile.println("Ori x (deg),Ori y (deg),Ori z (deg),Accel x (m/s^2),Accel y (m/s^2),Accel z (m/s^2),AccelHiG x (m/s^2),AccelHiG y (m/s^2),AccelHiG z (m/s^2),Gyro x (deg/s),Gyro y (deg/s),Gyro z (deg/s),Baro Alt AGL (m),GPS Altitude (m),RW Value,Voltage,State,Cam State,RW State,On Time (sec),Flight Time (sec),Pressure (hPa),IMU Temp (C),Baro Temp (C),GPS Sats,Latitude,Longitude");
    // ^ printing header log file
    dataFile.begin("data.txt", flightFolderPath);

    // Coroutines
    SDLogger.begin(logData);
    TLMSender.begin(sendData);
    SDLogger.pause(); // SD Card starts logging at Launch Ready

    TLM.printlnStr("SETUP COMPLETE"); 
    Serial.println("SETUP COMPLETE");

    State = GROUND_IDLE;
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
    Baro.update();
    Accel.update();
    imu.update();
    GPSVar.GPSUpdate();
    Command = TLM.read();
    if(State == GROUND_IDLE || State == LAUNCH_READY) Quat.accelOri(imu.bodyAccel.x,imu.bodyAccel.y,imu.bodyAccel.z);
    if(State >= POWERED_ASCENT && State != MISSION_COMPLETE) Quat.update(imu, Time);
  }

  switch(State) {
    case GROUND_IDLE:
      led.flash(led.yellow, led.green, 1000000, 50000, Time.currentTimeMicro, 13, 1100);
      
      if(Command == "EN"){ //Enable launch command
        Command = "";
        SDLogger.resume(); // starts logging data 
        TLMSender.setFrequency(TLM_RATE_HIGH);
        Baro.setAltitudeBias();
        State = LAUNCH_READY;
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
      led.flash(led.blue, led.white, 1000000, 50000, Time.currentTimeMicro, 13, 1380);

      imu.getGyroBias();

      static unsigned int ascentStartTime;

      // ! doesnt account for done or heli 

      // if(Accel.getAccelMag() < 12) {
      //   ascentStartTime = millis();
      // }

      if(Baro.rawAltitude - Baro.bias < 25) {
        ascentStartTime = millis();
      } else if((millis() - ascentStartTime) >= 700 || Command == "AS") {
        // Command = ""; // ? Pretty sure this isn't needed
        Cam.turnOn(); //For safety
        SDLogger.setFrequency(TLM_RATE_HIGH);
        Time.logLaunch();
        if (!imu.biasComplete) return;
        dataFile.println("Launch Time: " + ascentStartTime);
        State = POWERED_ASCENT;
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

    case POWERED_ASCENT:
      led.party(Time.currentTimeMicro, 13, 1000);

      if(Baro.altitudeAGL > Baro.apogee) {
        Baro.apogee = Baro.altitudeAGL;
        Baro.apogeeTime = millis();
      }
      // ! maybe we don't need the apogee - altitudeAGL cuz first condition means alt < apogee
      if(((millis() - Baro.apogeeTime) >= 1500 && Baro.apogee - Baro.altitudeAGL > 9)|| Command == "AS") {
        // Command = "";
        SDLogger.setFrequency(SD_RATE_HIGH);
        dataFile.println("Apogee Time: " + Baro.apogeeTime);
        dataFile.println("Apogee Height: " + String(Baro.apogee));
        State = PARACHUTE_DESCENT;
      }

      break;

    case PARACHUTE_DESCENT:
      led.flash(led.purple, led.white, 350000, 40000, Time.currentTimeMicro, 13, 1400);

      static unsigned int parachuteDescentStartTime = millis();

      if (millis() >= (parachuteDescentStartTime + 10000)|| Command == "AS") {
        Command = "";
        RCW.setState(true); //safety
        State = ROLL_CONTROL;
      }

      break;

    case ROLL_CONTROL:
      led.flash(led.yellow, led.green, 600000, 45000, Time.currentTimeMicro, 13, 1100);

      RollPID.update(Time, Quat.roll);
      RCW.writeWheelOutput(RollPID.Output);

      if(abs(RollPID.Output) < 255) {
        RCW.satTime = millis();
      }

      if(((millis() - RCW.satTime) >= 10000)) {
        RCW.setState(false);
      }

      if(Command == "SP") {
        Command = "";
        RollPID.setSetpoint(90);
      }

      if(Baro.altitudeAGL <= 30 || Command == "AS") {
        Command = "";
        SDLogger.setFrequency(SD_RATE_MEDIUM);
        State = LANDING_DETECT;
      }
      
      break;

    case LANDING_DETECT:
      led.flash(led.blue, led.white, 350000, 40000, Time.currentTimeMicro, 13, 1380);

      static float loggedAlt = Baro.altitudeAGL;
      static long loggedAltTime = millis();
      
      if (abs(loggedAlt - Baro.altitudeAGL) > 2) {
        loggedAlt = Baro.altitudeAGL;
        loggedAltTime = millis();
      } else if (millis() - loggedAltTime > 5000) {
        TLMSender.setFrequency(TLM_RATE_LOW);
        State = MISSION_COMPLETE;
      }

      //If gyros are all below 0.1 rad/s, we have landed
      if(((abs(imu.bodyGyroRad.x) < 0.1) && (abs(imu.bodyGyroRad.y) < 0.1) && (abs(imu.bodyGyroRad.z) < 0.1)) || Command == "AS") {
        Command = "";
        TLMSender.setFrequency(TLM_RATE_LOW);
        State = MISSION_COMPLETE;
      }

      break;

    case MISSION_COMPLETE:
      led.flash(led.red, led.white, 500000, 50000, Time.currentTimeMicro, 13, 4000);
      
      static unsigned int landingTime = millis();
      if((millis() - landingTime) >= 15000){ //leave 15 second delay before shutting camera off
        Cam.turnOff();
        dataFile.println("Landing Time: " + landingTime);
      }

      break;

    case AVI_ERROR:
      led.flash(led.red, led.yellow, 500000, 100000, Time.currentTimeMicro, 13, 900);

      break;

    default:
      break;
  }  

  // SMART STATE SWITCH
  static float lastAltLog = Baro.altitudeAGL;
  static float lastLogTime = millis();

  if(millis() > lastLogTime + 2500) {
    float deltaAlt = Baro.altitudeAGL - lastAltLog;

    if(abs(deltaAlt) > 13) {
      // forgot to mantually set state to Launch Ready
      if(deltaAlt < 0) {
        ForceState(POWERED_ASCENT);
      } else if(State < PARACHUTE_DESCENT || State == MISSION_COMPLETE) {
        ForceState(PARACHUTE_DESCENT);
      }
    }

    lastAltLog = Baro.altitudeAGL;
    lastLogTime = millis();
  }

}

void logData() {
  logFile.logData(
    (State == GROUND_IDLE || State == LAUNCH_READY) ? vec3(Quat.roll, Quat.accelPitch, Quat.accelYaw) : vec3(Quat.roll, Quat.pitch, Quat.yaw), // orientation
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
    (State == GROUND_IDLE || State == LAUNCH_READY) ? 0 : (Time.currentTimeSec - Time.launchTime), // Flight time is 0 until flight has started
    Baro.pressure, // imu temp
    imu.temperature, // imu temp
    Baro.temperature,
    GPSVar.numSatellites, //GPS sats
    GPSVar.latitude, //Lat 
    GPSVar.longitude //lon
  );
}

void sendData() {
  TLM.transmit(
    (State == GROUND_IDLE || State == LAUNCH_READY) ? vec3(Quat.roll, Quat.accelPitch, Quat.accelYaw) : vec3(Quat.roll, Quat.pitch, Quat.yaw), // orientation 
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
    (State == GROUND_IDLE || State == LAUNCH_READY) ? 0 : (Time.currentTimeSec - Time.launchTime), // Flight time is 0 until flight has started
    Baro.pressure, // imu temp
    imu.temperature, // imu temp
    Baro.temperature,
    GPSVar.numSatellites, //GPS sats
    GPSVar.latitude, //Lat 
    GPSVar.longitude //lon
  );
}

void ForceState(States target) {
  dataFile.println("Force State Switch to '" + String(target) + "' at time: " + millis());

  if(target != MISSION_COMPLETE) {
    Cam.turnOn();
  } else {
    Cam.turnOff();
  }

  // set altitude bias

  switch (State)
  {
  case LAUNCH_READY:
    TLMSender.setFrequency(TLM_RATE_HIGH);
    SDLogger.setFrequency(SD_RATE_LOW);
    
    break;

  case POWERED_ASCENT:
    Time.logLaunch();
    TLMSender.setFrequency(TLM_RATE_HIGH);
    SDLogger.setFrequency(SD_RATE_HIGH);
    break;

  case PARACHUTE_DESCENT:
    Baro.apogee = Baro.altitudeAGL;
    TLMSender.setFrequency(TLM_RATE_HIGH);
    SDLogger.setFrequency(SD_RATE_HIGH);
    break;

  default:
    dataFile.println("Force State Switch ERROR");

    break;
  }
  
  // must be last line
  State = target;
}