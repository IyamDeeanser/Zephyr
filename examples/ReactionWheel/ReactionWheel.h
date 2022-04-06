#ifndef REACTIONWHEEL_H
#define REACTIONWHEEL_H

#include <Arduino.h>

class ReactionWheel {
  public:
    float wheelOutput;

    ReactionWheel(int p1, int p2);

    void writeWheelOutput(float pidXOut);

    void off();

  private:
    float outPin1;
    float outPin2;
};

#endif
