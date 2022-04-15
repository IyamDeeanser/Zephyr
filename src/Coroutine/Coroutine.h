#ifndef COROUTINE_H
#define COROUTINE_H

#include <Arduino.h>

class Coroutine {
private:
    void (*target)();
    float interval = 1.0f;
    unsigned long lastCall;

public:
    void setInterval(float target);
    void setFrequency(float target);
    void setTarget(void (*foo)());
    void callTarget();
    void initialize(float frequency = 1.0f, void (*foo)() = nullptr);
    void update();
};


#endif