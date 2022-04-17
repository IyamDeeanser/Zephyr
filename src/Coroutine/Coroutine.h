#ifndef COROUTINE_H
#define COROUTINE_H

#include <Arduino.h>

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