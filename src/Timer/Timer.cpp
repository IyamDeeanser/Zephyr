#include "Timer.h"
// #include "TimerOne.h"
#include "Arduino.h"

void Timer::update(){
    previousTime = currentTime;
    //currentTime += loopTime;

    //none of this is needed when you can just add looptime in a hardware timer
    currentTime = micros();
    timeSinceLaunch = currentTime - launchTime;
    deltaTimeMicro = currentTime - previousTime;
    deltaTimeSec = deltaTimeMicro / 1000000.0;
}

void Timer::logLaunch()
{
    launchTime = currentTime;
}

void Timer::logTransmit()
{
    lastTlmTransmitTime = currentTime;
}

void Timer::logBurnout()
{
    burnoutTime = currentTime;
}

void Timer::logApogee()
{
    apogeeDetectStartTime = currentTime;
}