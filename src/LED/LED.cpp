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

void LED::party(float time, int buzzer, int buzzerFreq){
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
        tone(buzzer, buzzerFreq, 90000/1000);
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

void LED::flash(RGB colour1, RGB colour2, int duration1, int duration2, int time, int buzzer, int buzzerFreq){
  if(flashState && ((time - lastFlashTime) >= (unsigned)duration1)){
    colour(colour2);
    tone(buzzer, buzzerFreq, duration2 / 1000);
    lastFlashTime = time;
    flashState = false;
  }

  if(!flashState && ((time - lastFlashTime) >= (unsigned)duration2)){
    colour(colour1);
    lastFlashTime = time;
    flashState = true;
  }
}
