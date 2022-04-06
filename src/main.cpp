#include <Arduino.h>
#include "States/States.h"
#include "Telemetry/Telemetry.h"
#include "Vec3/Vec3.h"
#include "Settings/Settings.h"
#include "Timer/Timer.h"
#include "Baro/Baro.h"
#include "SD_Card/SD_Card.h"

States State;
Telemetry Tele;
Timer Time;
Barometer Baro;
SD_Card SD;


// SD_Card SD;

void setup() {
  // initialize
  Serial1.begin(115200);
  Serial1.println("BEEP BEEP BOOP BOOP! WAKING UP!");

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