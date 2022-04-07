#ifndef TIMER_H
#define TIMER_H

class Timer {
  public:
    float deltaTimeSec, deltaTimeMicro, flightTimeSec, currentTimeSeconds;

    //Timer variables
    unsigned long currentTimeMicrons, 
    previousTime, 
    lastLogTime, 
    lastTlmTransmitTime, 
    launchTime = 0, 
    timeSinceLaunch,
    burnoutTime, 
    apogeeDetectStartTime, 
    landingDetectStartTime;

    void update();
    void logLaunch();
    void logTransmit();
    void logBurnout();
    void logApogee();
};

#endif