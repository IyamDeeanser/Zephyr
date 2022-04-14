#include "Timer.h"
#include "Arduino.h"

void Timer::update(){
    previousTimeMicro = currentTimeMicro;
    previousTimeSec = previousTimeMicro / 1000000.0;
    currentTimeMicro = micros();
    currentTimeSec = currentTimeMicro / 1000000.0;
    deltaTimeMicro = currentTimeMicro - previousTimeMicro;
    deltaTimeSec = deltaTimeMicro / 1000000.0;
}

void Timer::logLaunch()
{
    launchTime = currentTimeSec;
}

void Timer::logTransmit()
{
    lastTlmTransmitTime = currentTimeSec;
}

void Timer::logBurnout()
{
    burnoutTime = currentTimeSec;
}

void Timer::logApogee()
{
    apogeeDetectStartTime = currentTimeSec;
}