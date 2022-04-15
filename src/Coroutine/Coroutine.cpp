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
    (*target)();
}

void Coroutine::begin(void (*foo)(), float frequency) {
    if(foo != nullptr) target = foo;
    setFrequency(frequency);
}

void Coroutine::update() {
    if(millis() >= lastCall + interval * 1000) {
        lastCall = millis();
        callTarget();
    }
}
