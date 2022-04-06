#ifndef LED_H
#define LED_H

#include <Arduino.h>

//RGB structure
struct RGB {
  int r;
  int g;
  int b;
};

class LED {
  private:
    int rPin;
    int gPin;
    int bPin;

    unsigned long lastBlinkTime;
    unsigned long lastFlashTime;

    int partyState;

    bool flashState;

  public:
    //Create new LED
    LED(int red, int green, int blue);

    //Set LED colour
    void colour(RGB rgb);

    //Party LED
    void party(float time);

    void flash(RGB colour1, RGB colour2, int duration1, int duration2, int time);
        
    //LED colours
    RGB red = {LOW, HIGH, HIGH};
    RGB yellow = {LOW, LOW, HIGH};
    RGB green = {HIGH, LOW, HIGH};
    RGB blue = {HIGH, HIGH, LOW};
    RGB purple = {LOW, HIGH, LOW};
    RGB white = {LOW, LOW, LOW};
    RGB off = {HIGH, HIGH, HIGH};
};

#endif
