#ifndef BARO_H
#define BARO_H

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"


#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

class Barometer {
public:
    Adafruit_BMP3XX bmp;
    Barometer();
    void update();
    float altitude; // meters
    double temperature; // Celsius 
    double pressure; // hPa
};


#endif