#include <Arduino.h>
#include "States/States.h"
#include "Telemetry/Telemetry.h"
#include "Vec3/Vec3.h"
#include "Settings/Settings.h"
#include <TimerOne.h>

void TVC(const States & State) {

  switch (State)
  {
  case GROUND_IDLE:
    break;
  
  default:
    break;
  }
}

void setup() {
  // initialize
  States State;
  Telemetry Tele;
  // @ SD Card Init

  Tele.Sendln("INITALIZED!");
  Timer1.initialize(500000);
}

void loop() {}   