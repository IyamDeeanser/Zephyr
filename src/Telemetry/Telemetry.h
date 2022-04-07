#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>

class Telemetry {
    public:
        void transmit(
            float ROTATLMoriX,
            float oriY,
            float oriZ,
            float accelX,
            float accelY,
            float accelZ,
            float gyroX,
            float gyroY,
            float gyroZ,
            float altitude,
            float rwValue,
            float velocityX,
            float velocityY,
            float velocityZ,
            float positionX,
            float positionY,
            float positionZ,
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

        void test();
        void sendStrln(const String & s);
        
        // Pre-conditions: Input must be <= 25 characters & be enclosed with <>
        String read();
};

#endif
