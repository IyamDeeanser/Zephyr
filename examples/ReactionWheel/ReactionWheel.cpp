#include "ReactionWheel.h"

ReactionWheel::ReactionWheel(int p1, int p2){
  outPin1 = p1;
  outPin2 = p2;
}

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
