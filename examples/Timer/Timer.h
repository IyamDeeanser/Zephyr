#ifndef TIMER_H
#define TIMER_H

class Time {
  public:
    float deltaTimeSec, deltaTimeMicro, flightTimeSec;

    int loggingFrequency;
    int transmitFrequency;

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
