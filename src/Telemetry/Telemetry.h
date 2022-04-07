#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>

class Telemetry {
    public:
        void transmit(
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

        void test();

        String read();
};

#endif
