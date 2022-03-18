//New and improved version by Timothy Cai
#include "BMI088.h"
#include <TimerOne.h> //hardware timing library
#include <Servo.h>
#include <SPI.h>
#include <SD.h>
#include <cstdio>

//classes
class vec3{
public:
  float x,y,z;

  vec3(float x,float y, float z)
  : x(x),y(y),z(z) {}

  vec3(float n)
  : vec3(n,n,n) {}

  vec3()
  : vec3(0) {}

  void set(float newX, float newY, float newZ) {
    x = newX;
    y = newY;
    z = newZ;
  }
};

class PID{
public:
  float error;
  float lastError;
  float totalError;
  float P, I, D;
  float Output;

  PID() {
    error = 0;
    lastError = 0;
    totalError = 0;
    P = 0;
    I = 0;
    D = 0;
    Output = 0;
  }
};

//state representation
enum State {
  GROUND_IDLE = 1,
  LAUNCH_READY,
  POWERED_ASCENT,
  UNPOWERED_ASCENT,
  SEPARATION,
  APOGEE,
  PARACHUTE_DESCENT,
  ROLL_CONTROL,
  MANUAL_ROLL_CONTROL,
  LANDING,
  MISSION_COMPLETE
};

//settings
#define timeInterval 0.01 //this is so you can easily change the loop time
int setpoint 0; //easier way of defining a word as a number
const float launchLimit = ~;   //in m/s/s
const float burnoutLimit = ~;  //in m/s/s
const float apogeeLimit = ~; //in m/s/s
const float burnoutTimeLimit = ~; //seconds after launch
const int BMI = 0x68;
  //PID settings
const float Kp = ~;
const float Ki = ~;
const float Kd = ~;
//needs a maximum rotation speed

//object initializers
State state;
vec3 accelData;
vec3 gyroData;
vec3 gyroBias;
PID rollData;
File dataFile, settingsFile;
Bmi088Accel accel(Wire, 0x18);
Bmi088Gyro gyro(Wire, 0x68);
Servo pitchServo; //todo: change to h bridge motor

//pins
const int LED_R = ~;
const int LED_G = ~;
const int LED_B = ~;
const int Buzzer = ~;
const int pitchPin = ~;
const int yawPin = ~;
const int chipSelect = ~;

//variable initializers
long timeAtLaunch = 0;
double totalTime = 0;
bool datalog = true;
bool accelBuffer, accelCheck;
bool checkBias = true;
  //orientation
bool gyroBuffer; //This allows the gyro data to be stored temporarily until the next cycle
float wS[4]; //this is to store angular velocities
float wI[4]; //this is to hold the initial desired orientation
float q_norm; //this is the norm of the last quaternion used in normalization
float q[4]; //this is the current derivative
float i_q[4]; //orientation of earth relative to sensor/the starting quaternion

//this section is for code outside the timer function which must be volatile
volatile float currentTime, previousTime, elapsedTime;
volatile float yaw, pitch, roll; //Tait-Bryan Angle variables
volatile float pre_q[4]; //this is the last estimate of orientation

//file writing variables
char datafilename[15], settingsfilename[20];
int filenum;
float dataSpacer = 1;
float counter = 0; 
bool logDelay = true;
bool SDCheck = false;
bool settingsWrite = true;


void setup() 
{
  Serial.begin(115200); // don't forget to set the baud rate to this too

  //initialize components
  accelInitialize();
  oriInitialize();
  miscInitialize();
  dataInitialize();
  gyroDebias();

  //create the time and interrupt function
  //this will cause the function chosen to repeat at any time interval determined here
  Timer1.initialize(timeInterval * 1000000); //this is in microseconds
  Timer1.attachInterrupt(TVC);
}

//the interrupt TVC function 
void TVC() //timer loop function
{
  //always runs
  states();
  timeCount();
  sensorRead();
  dataLogging();
  lights();
  
  switch(state) {
    case LAUNCH_READY:
      launchDetect();
      logDelay = true;
      break;

    case GROUND_IDLE:
      break;

    case POWERED_ASCENT:
      quaternions();
      PID();
      break;
    
    case SEPARATION:
      break;

    case APOGEE:
      break;

    case PARACHUTE_DESCENT:
      parachutes();
      logDelay = true;
      break;

    case MISSION_COMPLETE:
      shutDown();
      createSettings();
      break;

    default: 
      dataFile.println("State Error");
      shutDown();
  }
}

//-----setup----

//accelerometer initialization
void accelInitialize()
{
  //accelerometer
  int status;
  status = accel.begin();

  if (status < 0) {
    dataFile.println("Accel Initialization Error");
    Serial.println(status);
    //** add failure(); function
  }
}

//orientation initialization
void oriInitialize()
{
  //start the sensors
  int status;
  status = gyro.begin();
  //set data rate
  bool status2;
  status2 = gyro.setOdr(Bmi088Gyro::ODR_200HZ_BW_64HZ);

  if (status < 0) {
    dataFile.println("Gyro Initialization Error");
    Serial.println(status);
    //** add failure(); function
  }

  //Set the initial quaternion's orientation
  pre_q[0] = 1;
  pre_q[1] = 0;
  pre_q[2] = 0;
  pre_q[3] = 0;
}

//misc. components eg. servos, lights
void miscInitialize()
{
  //Setup Servos
  pitchServo.attach(pitchPin); //the 3rd pin is the x axis servo
  yawServo.attach(yawPin); //the 4th pin is the y axis servo
 
  //setup lights and sound
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

//initialize datalogging
void dataInitialize()
{
  //SD Card Initialization
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    while(1)
    {
      analogWrite(Buzzer, HIGH);
    }
    return;
  }
  Serial.println("initialization done.");

  //-----data file writing-----
  //filewriting names
  filenum = 1;
  while(true) 
  {
    sprintf(datafilename, "Flight_%d.csv", filenum);
    if(!SD.exists(datafilename)) {
      break;
    }
    else {
      filenum++;
    }
  }

   dataFile = SD.open(datafilename, FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (dataFile) {
    Serial.print("Writing to data file...");
    dataFile.print("gyroData.x, ");
    dataFile.print("gyroData.y, ");
    dataFile.print("gyroData.z, ");
    dataFile.print("accelData.x, ");
    dataFile.print("accelData.y, ");
    dataFile.print("accelData.z, ");
    dataFile.print("yawData, ");
    dataFile.print("rollData, ");
    dataFile.print("rollData, ");
    dataFile.print("rollData.output, ");
    dataFile.print("yawData.output, ");
    dataFile.print("state, ");
    dataFile.println("time");

  // close the file:
    dataFile.close();
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening data file");
    while(1)
    {
      analogWrite(Buzzer, HIGH);
    }
  }
}

//create and log all of the flight settings
void createSettings()
{
  if(settingsWrite)
  {
    //-----settings file writing-----
    //filewriting names
    sprintf(settingsfilename, "Settin_%d.csv", filenum);

    settingsFile = SD.open(settingsfilename, FILE_WRITE);
    
    // if the file opened okay, write to it:
    if (settingsFile) {
      Serial.print("Writing to settings file...");
      settingsFile.print("Flight Number:,");                    settingsFile.println(filenum);
      settingsFile.print("Kp Pitch:,");                         settingsFile.println(Kp);
      settingsFile.print("Ki Pitch:,");                         settingsFile.println(Ki);
      settingsFile.print("Kd Pitch:,");                         settingsFile.println(Kd);
      settingsFile.print("Kp Yaw:,");                           settingsFile.println(Kp);
      settingsFile.print("Ki Yaw:,");                           settingsFile.println(Ki);
      settingsFile.print("Kd Yaw:,");                           settingsFile.println(Kd);
      settingsFile.print("TVC Max X Limit:,");                  settingsFile.println(maxAmount);
      settingsFile.print("TVC Max Y Limit:,");                  settingsFile.println(maxAmount);
      settingsFile.print("TVC Min X Limit:,");                  settingsFile.println(minAmount);
      settingsFile.print("TVC Min Y Limit:,");                  settingsFile.println(minAmount);
      settingsFile.print("TVC Gear Ratio X,");                  settingsFile.println(gearRatio);
      settingsFile.print("TVC Gear Ratio Y,");                  settingsFile.println(gearRatio);
      settingsFile.print("TVC Offset X:,");                     settingsFile.println(TVCOffset);
      settingsFile.print("TVC Offset Y:,");                     settingsFile.println(TVCOffset);
      settingsFile.print("Setpoint:,");                         settingsFile.println(setpoint);
      settingsFile.print("Gyroscope Bias X:,");                 settingsFile.println(gyroBias.x);
      settingsFile.print("Gyroscope Bias Y:,");                 settingsFile.println(gyroBias.y);
      settingsFile.print("Gyroscope Bias Z:,");                 settingsFile.println(gyroBias.z);
      settingsFile.print("Launch Threshold:, ");                settingsFile.println(launchLimit);
      settingsFile.print("Burnout Accelerometer Threshold:, "); settingsFile.println(burnoutLimit);
      settingsFile.print("Burnout Time Threshold:, ");          settingsFile.println(burnoutTimeLimit);
      settingsFile.print("Loop Speed:, ");                      settingsFile.println(timeInterval);
      settingsFile.print("Time of Launch:, ");                  settingsFile.println(timeAtLaunch);

    // close the file:
      settingsFile.close();
    }
    
    else {
      // if the file didn't open, print an error:
      Serial.println("error opening settings file");
    }
    settingsWrite = false;
  }
}

//find the constant angular velocity from 0
void gyroDebias()
{
  if(checkBias)
  {  
    //light signal
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);

    float debiasTime = millis(), specialTime;
    int loopcount = 0;
    while((specialTime - debiasTime) < 10000)
    {
      gyro.readSensor();
      gyroBias.x = gyroBias.x + gyro.getGyroX_rads();
      gyroBias.y = gyroBias.y + gyro.getGyroY_rads();
      gyroBias.z = gyroBias.z + gyro.getGyroZ_rads();
      //delay(10);
      loopcount++;
      specialTime = millis();
    }
    gyroBias.x = gyroBias.x/loopcount;
    gyroBias.y = gyroBias.y/loopcount;
    gyroBias.z = gyroBias.z/loopcount;
    checkBias = false;
  }
}

//-----main flight-----

//state changer
void states()
{
  if (accelCheck == false)
  {
    state = LAUNCH_READY;
  }

  if (accelCheck && state == LAUNCH_READY)
  {
    datalog = true;
    logDelay = false;
    state = GROUND_IDLE;
  }

  else if (state == GROUND_IDLE)
  {
    state = POWERED_ASCENT;
  }

  if ((totalTime - timeAtLaunch) >= burnoutTimeLimit && accelData.z <= burnoutLimit && state == POWERED_ASCENT)
  {
    state = SEPARATION;
  }

  if (state == SEPARATION && accelData.z <= apogeeLimit)
  {
    state = APOGEE;
  }
  
  else if (state == APOGEE)
  {
    state = PARACHUTE_DESCENT;
  }

  if (state == PARACHUTE_DESCENT) 
  {
    if(accelData.x > 5 || accelData.y > 5 || accelData.z > 5) //looking for impact spike
    {
      state = POWERED_ASCENT;
    }
  }
}

//orienation 
void quaternions()
{
  gyro.readSensor();
  //Get the current angular rate
  wS[0] = 0;
  wS[1] = gyro.getGyroY_rads() - gyroBias.y;
  wS[2] = gyro.getGyroX_rads() - gyroBias.x;
  wS[3] = gyro.getGyroZ_rads() - gyroBias.z;
  //Now we have to normalize the previous orientation to be used
  //First we have to find the norm of the last one
  q_norm = (sqrt(pre_q[0] * pre_q[0] + pre_q[1] * pre_q[1] + pre_q[2] * pre_q[2] + pre_q[3] * pre_q[3]));
  pre_q[0] = pre_q[0] / q_norm;
  pre_q[1] = pre_q[1] / q_norm;
  pre_q[2] = pre_q[2] / q_norm;
  pre_q[3] = pre_q[3] / q_norm;
  //Obtain the derivative of the next quaternion
  q[0] = 0.5 * (pre_q[0] * wS[0] - pre_q[1] * wS[1] - pre_q[2] * wS[2] - pre_q[3] * wS[3]);
  q[1] = 0.5 * (pre_q[0] * wS[1] + pre_q[1] * wS[0] + pre_q[2] * wS[3] - pre_q[3] * wS[2]);
  q[2] = 0.5 * (pre_q[0] * wS[2] - pre_q[1] * wS[3] + pre_q[2] * wS[0] + pre_q[3] * wS[1]);
  q[3] = 0.5 * (pre_q[0] * wS[3] + pre_q[1] * wS[2] - pre_q[2] * wS[1] + pre_q[3] * wS[0]);
  //Calculate the "previous estimate" for the next cycle through integration, which is now the current quaternion ORIENTATION
  pre_q[0] = (pre_q[0] + q[0] * timeInterval);
  pre_q[1] = (pre_q[1] + q[1] * timeInterval);
  pre_q[2] = (pre_q[2] + q[2] * timeInterval);
  pre_q[3] = (pre_q[3] + q[3] * timeInterval);
  //Convert to Euler, add condition for PID loop later
  yaw = (atan2(2 * pre_q[1] * pre_q[2] - 2 * pre_q[0] * pre_q[3], 2 * pre_q[0] * pre_q[0] + 2 * pre_q[1] * pre_q[1] - 1));
  pitch = (-asin(2 * pre_q[1] * pre_q[3] + 2 * pre_q[0] * pre_q[2]));
  roll = (atan2(2 * pre_q[2] * pre_q[3] - 2 * pre_q[0] * pre_q[1], 2 * pre_q[0] * pre_q[0] + 2 * pre_q[3] * pre_q[3] - 1));
  //convert from radians to degrees
  yaw = yaw * (180 / M_PI);
  pitch = pitch * (180 / M_PI);
  roll = roll * (180 / M_PI);
}

//control algorithm
void PID()
{
  //rollData.PID
  rollData.lastError = rollData.error;
  rollData.error = setpoint - pitch;
  rollData.totalError = rollData.totalError + rollData.error * timeInterval;
  rollData.P = Kp * rollData.error;   //Proportional part of rollData.PID
  rollData.I = Ki * rollData.totalError; //Integral part of rollData.PID
  rollData.D = Kd * (rollData.error - rollData.lastError) / timeInterval; //Derivative part of rollData.PID    The 0.01 is the hardware loop time
  //Now for the whole rollData.PID equation
  rollData.Output = (rollData.P + rollData.I + rollData.D) * gearRatio + TVCOffset;
  pitchServo.write(rollData.Output);
}

//launch detection
void launchDetect()
{  
  //Acceleration check
  if (accelData.z > launchLimit) {
    delay(50);
    if (accelData.z > launchLimit) {
      accelCheck = true;
      timeAtLaunch = totalTime;
    }
  }
  
  else {
    accelCheck = false;
  }
}

//sensor data
void sensorRead()
{
  //data reading; start sensor
  accel.readSensor();
  accelData.z = -accel.getAccelY_mss();
  accelData.x = accel.getAccelX_mss();
  accelData.y = accel.getAccelX_mss();

  gyro.readSensor();
  gyroData.x = gyro.getGyroX_rads() - gyroBias.z;
  gyroData.y = gyro.getGyroY_rads() - gyroBias.y;
  gyroData.z = gyro.getGyroZ_rads() - gyroBias.z;
}

//datalogging **still needs filewriting code**
void dataLogging()
{
  if(logDelay)
  {
    if((totalTime-counter) > dataSpacer)
    {
      datalog = true;
      counter = totalTime;
    }
    else
    {
      datalog = false;
    }
  }
 
  //write data to the SD card
  dataFile = SD.open(datafilename, FILE_WRITE);

  if (dataFile && datalog) {
    dataFile.print(gyroData.x);            dataFile.print(", ");
    dataFile.print(gyroData.y);            dataFile.print(", ");
    dataFile.print(gyroData.z);            dataFile.print(", ");
    dataFile.print(accelData.x);           dataFile.print(", ");
    dataFile.print(accelData.y);           dataFile.print(", ");
    dataFile.print(accelData.z);           dataFile.print(", ");
    dataFile.print(yaw);              dataFile.print(", ");
    dataFile.print(pitch);            dataFile.print(", ");
    dataFile.print(roll);             dataFile.print(", ");
    dataFile.print(rollData.Output-90);   dataFile.print(", ");
    dataFile.print(yawData.Output-90);     dataFile.print(", ");
    dataFile.print(state);            dataFile.print(", ");
    dataFile.println(totalTime);
    dataFile.close(); // close the file

    //do all of the printing again in serial
    Serial.print(gyroBias.x);        Serial.print(", ");
    Serial.print(gyroBias.y);        Serial.print(", ");
    Serial.print(gyroBias.z);        Serial.print(", ");
    Serial.print(gyroData.x);            Serial.print(", ");
    Serial.print(gyroData.y);            Serial.print(", ");
    Serial.print(gyroData.z);            Serial.print(", ");
    Serial.print(accelData.x);           Serial.print(", ");
    Serial.print(accelData.y);           Serial.print(", ");
    Serial.print(accelData.z);           Serial.print(", ");
    Serial.print(yaw);              Serial.print(", ");
    Serial.print(pitch);            Serial.print(", ");
    Serial.print(roll);             Serial.print(", ");
    Serial.print(rollData.Output-90);   Serial.print(", ");
    Serial.print(yawData.Output-90);     Serial.print(", ");
    Serial.print(state);            Serial.print(", ");
    Serial.println(totalTime);
  }
  
  else if(!datalog)
  {
    dataFile.close();
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening data file");
  }
}

//lights
void lights()
{
  //LED Signal
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, HIGH);
}

//time recording
void timeCount()
{
  //note: time at launch is recorded in launchDetect function
  //continually record the time
  totalTime = totalTime + timeInterval;
}

//shutting down the system
void shutDown()
{ 

}

//nothing
void loop() {
}
