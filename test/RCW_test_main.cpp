#include <Arduino.h>
#include "RCW/RCW.h"

ReactionWheel roll;

void setup()
{
}

void loop()
{
    roll.writeWheelOutput(100);
}