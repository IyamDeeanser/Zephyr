#ifndef COROUTINE_H
#define COROUTINE_H

#include <Arduino.h>

#define TLM_RATE_HIGH 15
#define TLM_RATE_MEDIUM 10
#define TLM_RATE_LOW 1

#define SD_RATE_HIGH 50
#define SD_RATE_MEDIUM 25
#define SD_RATE_LOW 1

class Coroutine {
private:
    void (*target)();
    float interval;
    unsigned long lastCall;
    bool running = true;

public:

    void setInterval(float target);
    void setFrequency(float target);
    void setTarget(void (*foo)());
    void callTarget();
    void pause();
    void resume();
    void begin(void (*foo)() = nullptr, float frequency = 1);
    
    void update();
};

#endif