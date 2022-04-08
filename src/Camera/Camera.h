#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>

class Camera {
    const static int CAMERA_PIN = 2;
public:
    void turnOn();
    void turnOff();
    void initialize();
};

#endif