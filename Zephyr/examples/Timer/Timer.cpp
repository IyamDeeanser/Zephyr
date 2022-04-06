#include "Timer.h"
#include "Arduino.h"

void Time::update(){
    previousTime = currentTime;
    currentTime = micros();
    deltaTimeMicro = currentTime - previousTime;
    deltaTimeSec = deltaTimeMicro / 1000000.0;
}
