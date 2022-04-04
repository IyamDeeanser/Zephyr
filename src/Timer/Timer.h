#ifndef TIMER_H
#define TIMER_H

class Timer {
  public:
    float deltaTimeSec, deltaTimeMicro, flightTimeSec;

    //Timer variables
    unsigned long currentTime, 
    previousTime, 
    lastLogTime, 
    lastTlmTransmitTime, 
    launchTime, 
    burnoutTime, 
    apogeeDetectStartTime, 
    landingDetectStartTime;

    void update();
};

#endif
