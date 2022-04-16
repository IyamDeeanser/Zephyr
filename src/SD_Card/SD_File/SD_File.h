#ifndef SD_FILE_H
#define SD_FILE_H

#include <Arduino.h>
#include "SD.h"

class SD_File {
    char filePath[50];
    bool canWrite = true;
public:
    void begin(String name = "file.txt", String folderPath = "");
    void print(String s);
    void println(String s);
    
    void eject();

    //cansat specific
    void logData(
            float oriXIDeg, 
            float oriYIDeg, 
            float oriZIDeg, 
            float gyroXBDps, 
            float gyroYBDps, 
            float gyroZBDps, 
            float accelXBMS, 
            float accelYBMS, 
            float accelZBMS, 
            float altEstimateM, 
            float tvcY, 
            float tvcZ, 
            float rwX, 
            float baroAltBias, 
            float velXMS, 
            float pressure_hPa, 
            float tempIMUC, 
            float tempBaroC, 
            float voltage, 
            int state, 
            bool abort, 
            bool abortEnabled, 
            float massEstKg, 
            int p1f, 
            int p2f, 
            int p3f, 
            int p1c, 
            int p2c, 
            int p3c, 
            float onTimeSec, 
            float flightTimeSec
        );
};


#endif