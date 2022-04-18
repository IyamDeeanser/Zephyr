#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>

class Camera {
    const static int CAMERA_PIN = 2;
    String state = "OFF";
public:
    void turnOn();
    void turnOff();
    void initialize();
    String getState() const;
};

#endif