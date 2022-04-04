#include "Timer.h"
#include "TimerOne.h"
#include "Arduino.h"

void Timer::update(){
    previousTime = currentTime;
    currentTime = micros();
    deltaTimeMicro = currentTime - previousTime;
    deltaTimeSec = deltaTimeMicro / 1000000.0;
}
