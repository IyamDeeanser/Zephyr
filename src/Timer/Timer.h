#ifndef TIMER_H
#define TIMER_H

class Timer {
  public:
    float deltaTimeSec, deltaTimeMicro;

    int loggingFrequency;
    int transmitFrequency;

    //Timer variables
    unsigned long 
    currentTimeMicro, 
    previousTimeMicro, 
    currentTimeSec, 
    previousTimeSec,
    lastLogTime,
    lastTlmTransmitTime, 
    launchTime, 
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
