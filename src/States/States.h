#ifndef STATES_H
#define STATES_H

#include <Arduino.h>

enum States {
  GROUND_IDLE = 1,
  LAUNCH_READY = 2,
  POWERED_ASCENT = 3,
  SEPARATION = 4,
  PARACHUTE_DESCENT = 5,
  ROLL_CONTROL = 6,
  LANDING_DETECT = 7,
  MISSION_COMPLETE = 8,
  AVI_ERROR = 42
};

#endif