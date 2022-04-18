#include "Camera.h"

void Camera::initialize() {
    pinMode(CAMERA_PIN, OUTPUT);
}

void Camera::turnOn() {
    digitalWrite(CAMERA_PIN, HIGH);
    state = 1;
}

void Camera::turnOff() {
    digitalWrite(CAMERA_PIN, LOW);
    state = 0;
}

bool Camera::getState() const {
    return state;
}