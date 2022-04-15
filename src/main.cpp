#include <Arduino.h>
#include "States/States.h"
#include "Telemetry/Telemetry.h"
#include "Vec3/Vec3.h"
#include "Settings/Settings.h"
#include "Timer/Timer.h"
#include "Baro/Baro.h"
#include "SD_Card/SD_Card.h"
#include "GPS/GPS.h"
#include "Camera/Camera.h"

States State;
Telemetry Tele;
Timer Time;
Barometer Baro;
SD_Card SD;
Camera Cam;

void setup() {
  // initialize
  Serial1.begin(115200);
  Serial1.println("BEEP BEEP BOOP BOOP! WAKING UP!" + String(2.34));
  Cam.initialize(); // initializes camera
}

void loop() 
{
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

void states()
{
  if (/*acceleration check*/)
  {
    State = LAUNCH_READY;
  }
}