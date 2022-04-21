#include "RCW.h"

ReactionWheel::ReactionWheel()
{}

void ReactionWheel::writeWheelOutput(float pidXOut){
  wheelOutput = constrain(
    pidXOut, 
    -255, 
    255
  );

  if(wheelOutput > 0){
    analogWrite(outPin1, wheelOutput);
    analogWrite(outPin2, 0);
  }

  if(wheelOutput < 0){
    analogWrite(outPin1, 0);
    analogWrite(outPin2, wheelOutput);
  }

  if(wheelOutput == 0){
    analogWrite(outPin1, 0);
    analogWrite(outPin2, 0);
  }
}

void ReactionWheel::off(){
  analogWrite(outPin1, 0);
  analogWrite(outPin2, 0);
}

bool ReactionWheel::getState() const {
    return state;
}

bool ReactionWheel::getValue() const {
    return wheelOutput;
}