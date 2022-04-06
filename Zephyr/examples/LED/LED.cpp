#include "LED.h"
#include <Arduino.h>

LED::LED(int red, int green, int blue) {
  rPin = red;
  gPin = green;
  bPin = blue;

  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);
}

void LED::colour(RGB rgb){
  digitalWrite(rPin, rgb.r);
  digitalWrite(gPin, rgb.g);
  digitalWrite(bPin, rgb.b);
}

void LED::party(float time){
  if((time - lastBlinkTime) > 90000){
    lastBlinkTime = time;
    switch(partyState) {
      case 0:
        
        colour(blue);
        partyState++;
        break;

      case 1:
        
        colour(red);
        partyState++;
        break;

      case 2:
        
        colour(purple);
        partyState = 0;
        break;
        
      default:
        break;
    }
  }
}

void LED::flash(RGB colour1, RGB colour2, int duration1, int duration2, int time){
  if(flashState && ((time - lastFlashTime) >= (unsigned)duration1)){
    colour(colour2);
    lastFlashTime = time;
    flashState = false;
  }

  if(!flashState && ((time - lastFlashTime) >= (unsigned)duration2)){
    colour(colour1);
    lastFlashTime = time;
    flashState = true;
  }
}
