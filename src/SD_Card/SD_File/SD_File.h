#ifndef SD_FILE_H
#define SD_FILE_H

#include <Arduino.h>
#include "SD.h"
#include "../../Vec3/Vec3.h"

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
        vec3 ori,
        vec3 accel,
        vec3 gyro,
        float altitude,
        float rwValue,
        vec3 velocity,
        vec3 position,
        float batteryVoltage,
        float systemState,
        float cameraState,
        float reactionWheelState,
        float onTimeSec,
        float flightTimeSec,
        float pressure,
        float imuTemp,
        float baroTemp,
        float GPSSats,
        float latitude,
        float longitude
    );
};


#endif