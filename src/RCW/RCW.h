#ifndef REACTIONWHEEL_H
#define REACTIONWHEEL_H

#include <Arduino.h>

class ReactionWheel {
private:
    int outPin1 = 5;
    int outPin2 = 11;
public:
    float wheelOutput;

    ReactionWheel();

    void writeWheelOutput(float pidXOut);

    void off();
};

#endif