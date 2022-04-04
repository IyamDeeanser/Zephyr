// SD Card functions here
// by Timothy Cai
#ifndef SD_CARD_h
#define SD_CARD_h

#include <SD.h> 
#include <Arduino.h>
#include "Timer.cpp"

class SDCard
{
private:
    File dataFile, settingsFile;
    char datafilename[15], settingsfilename[20];
    int filenum;
    float counter = 0, dataSpacer = 0; 
    bool logDelay = true, SDCheck = false, settingsWrite = true, datalog = true;
    void logcheck();
    void dataInitialize();
    void settingsInitialize();
public:
    SDCard();

    // @ logs FORMATTED strings to the SD card
    void Log(const String & s);
    void Logln(const String & s);
    // @ changes the datalog rate in terms of time
    void SetRate(const float & n);

};

#endif
