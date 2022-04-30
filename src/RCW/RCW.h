#ifndef REACTIONWHEEL_H
#define REACTIONWHEEL_H

#include <Arduino.h>

class ReactionWheel {
private:
    const int outPin1 = 5;
    const int outPin2 = 11;
    float wheelOutput;
    bool state = true;
public:

    ReactionWheel();

    void writeWheelOutput(float pidXOut);

    void off();

    bool getState() const;
    void setState(bool val);
    bool getValue() const;

    float satTime;
};

#endif