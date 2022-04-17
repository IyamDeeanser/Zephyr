#ifndef VOLTAGE_H
#define VOLTAGE_H

#include <Arduino.h>

#define VOLTAGE_DIV_PIN 14

class Voltage {
public:
    static float getVoltage();
};

#endif