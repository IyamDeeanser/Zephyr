#ifndef REACTIONWHEEL_H
#define REACTIONWHEEL_H

#include <Arduino.h>

class ReactionWheel {
private:
    const int outPin1 = 5;
    const int outPin2 = 11;
public:
    float wheelOutput;

    ReactionWheel();

    void writeWheelOutput(float pidXOut);

    void off();
};

#endif