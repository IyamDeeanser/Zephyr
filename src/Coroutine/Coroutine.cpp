#include "Coroutine.h"

void Coroutine::setInterval(float target) {
    interval = target;
}

void Coroutine::setFrequency(float target) {
    interval = 1 / target;
}

void Coroutine::setTarget(void (*foo)()) {
    target = foo;
}

void Coroutine::callTarget() {
    if(target != nullptr) (*target)();
}

void Coroutine::initialize(float frequency = 1.0f, void (*foo)() = nullptr) {
    if(foo != nullptr) target = foo;
    lastCall = millis();
    setFrequency(frequency);
    callTarget();
}

void Coroutine::update() {
    if(millis() > lastCall + interval * 1000) {
        lastCall = millis();
        callTarget();
    }
}