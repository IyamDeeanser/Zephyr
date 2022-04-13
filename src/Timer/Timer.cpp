#include "Timer.h"
#include "Arduino.h"

void Timer::update(){
    previousTime = currentTimeMicrons;
    //currentTime += loopTime;

    //none of this is needed when you can just add looptime in a hardware timer
    currentTimeMicrons = micros();
    currentTimeSeconds = currentTimeMicrons / 1000.0;
    timeSinceLaunch = currentTimeMicrons - launchTime;
    deltaTimeMicro = currentTimeMicrons - previousTime;
    deltaTimeSec = deltaTimeMicro / 1000.0;
}

void Timer::logLaunch()
{
    launchTime = currentTimeMicrons;
}

void Timer::logTransmit()
{
    lastTlmTransmitTime = currentTimeMicrons;
}

void Timer::logBurnout()
{
    burnoutTime = currentTimeMicrons;
}

void Timer::logApogee()
{
    apogeeDetectStartTime = currentTimeMicrons;
}