#ifndef BAROMETER_H
#define BAROMETER_H

// #include "../Timer/Timer.h"

class Barometer {
    public:
        float bias;
        float altitude;
        float rawAltitude;
        float temperature;
        float pressure;

        bool begin();
        
        void update();

        float getAltitude();
        
        void setAltitudeBias();
};

#endif