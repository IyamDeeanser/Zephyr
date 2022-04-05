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
    launchTime = 0, 
    timeSinceLaunch,
    burnoutTime, 
    apogeeDetectStartTime, 
    landingDetectStartTime;

    Timer();
    void update();
    void logLaunch();
    void logTransmit();
    void logBurnout();
    void logApogee();
};

#endif