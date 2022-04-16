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
Telemetry TLM;
Timer Time;
Barometer Baro;
SD_Card SD; // ! bad name
Camera Cam;

void setup() {
  // initialize
  TLM.begin();
  Cam.initialize(); // initializes camera
  Serial1.println("ROTA SAT Initialized!");
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

