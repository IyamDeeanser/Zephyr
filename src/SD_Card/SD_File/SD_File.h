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
        vec3 accelHG,
        vec3 gyro,
        float altitude,
        float rwValue,
        float batteryVoltage,
        const int & systemState,
        const bool & cameraState,
        bool reactionWheelState,
        float onTimeSec,
        float flightTimeSec,
        float pressure,
        float imuTemp,
        float baroTemp,
        float GPSSats,
        float latitude,
        float longitude,
        bool RWState
    );
};


#endif