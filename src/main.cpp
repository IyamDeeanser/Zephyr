#include <Arduino.h>
#include "States/States.h"
#include "Telemetry/Telemetry.h"
#include "Vec3/Vec3.h"
#include "Settings/Settings.h"
#include "Time/Time.h"
// #include "SD_Card/SD_Card.h"

States State;
Telemetry Tele;
Timer Time;
// SD_Card SD;

void setup() {
  // initialize
  Tele.Sendln("BEEP BEEP BOOP BOOP! WAKING UP!");

  while(true) {
    Setup_Loop();
    delay(100); // ! BRUH
  }
}

void Setup_Loop() {
  Time.update();
  State_Machine();
}

void State_Machine() {
  switch (State)
  {
  case GROUND_IDLE:
    break;
  
  default:
    break;
  }
}


void loop() {}   