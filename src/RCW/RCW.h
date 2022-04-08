#ifndef REACTIONWHEEL_H
#define REACTIONWHEEL_H

#include <Arduino.h>

class ReactionWheel {
private:
    float outPin1;
    float outPin2;
public:
    float wheelOutput;

    ReactionWheel();

    void writeWheelOutput(float pidXOut);

    void off();
};

#endif