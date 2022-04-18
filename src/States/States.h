#ifndef STATES_H
#define STATES_H

#include <Arduino.h>

enum States {
  GROUND_IDLE,
  LAUNCH_READY,
  POWERED_ASCENT,
  UNPOWERED_ASCENT,
  SEPARATION,
  APOGEE,
  PARACHUTE_DESCENT,
  ROLL_CONTROL,
  MANUAL_ROLL_CONTROL,
  LANDING,
  MISSION_COMPLETE,
  ABORT
};

namespace states {
  String stateToStr(const States State);

}
 

#endif