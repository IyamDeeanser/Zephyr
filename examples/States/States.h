#ifndef STATES_H
#define STATES_H

//Different states of flight
enum States {
  STARTUP = 0,
  GROUND_IDLE = 1,
  LAUNCH_DETECTION = 2,
  POWERED_ASCENT = 3,
  UNPOWERED_ASCENT = 4,
  DESCENT = 5,
  PARACHUTE_DESCENT = 6,
  LANDING_DETECTION = 7,
  LANDED_IDLE = 8,
  AVIONICS_ERROR = 42,
};

#endif
