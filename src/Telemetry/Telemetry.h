#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>
#include "../Vec3/Vec3.h"

class Telemetry {
    public:
        void transmit(
            vec3 ori,
            vec3 accel,
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
        
        void begin();
        void printlnStr(const String & s);
        
        // Pre-conditions: Input must be <= 25 characters & be enclosed with <>
        String read();
};

#endif
