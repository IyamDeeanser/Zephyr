// SD Card functions here
// by Timothy Cai
#ifndef SD_CARD_h
#define SD_CARD_h

#include <SD.h> 
#include <Arduino.h>
#include "SD_File/SD_File.h"

class SD_Card {
public:
    SD_Card();
    static String createNewDir();
    static bool begin(int chipSelect = 15);
    
};

#endif
