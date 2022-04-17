#ifndef BAROMETER_H
#define BAROMETER_H

// #include "../Timer/Timer.h"

class Barometer {
    public:
        float altitudeBias;
        float altitudeBaroAGL;
        float altitudeBaroMSL;
        float temperature;
        float pressure;

        bool begin();

        void update();

        void getAltitude();

        void setAltitudeBias();
};

#endif