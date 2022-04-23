#ifndef BAROMETER_H
#define BAROMETER_H

// #include "../Timer/Timer.h"

class Barometer {
    public:
        float bias = 0;
        float altitudeAGL;
        float rawAltitude;
        float temperature;
        float pressure;
        float apogee = 0;
        unsigned long apogeeTime;

        bool begin();
        
        void update();
        
        void setAltitudeBias();
};

#endif