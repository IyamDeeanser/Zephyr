#ifndef REACTIONWHEEL_H
#define REACTIONWHEEL_H

#include <Arduino.h>

class ReactionWheel {
private:
    const int outPin1 = 5;
    const int outPin2 = 11;
    bool state = 0;
    float wheelOutput;
public:

    ReactionWheel();

    void writeWheelOutput(float pidXOut);

    void off();

    bool getState() const;
    bool getValue() const;
};

#endif