#include "Camera.h"

void Camera::initialize() {
    pinMode(CAMERA_PIN, OUTPUT);
}

void Camera::turnOn() {
    digitalWrite(CAMERA_PIN, HIGH);
    state = "ON";
}

void Camera::turnOff() {
    digitalWrite(CAMERA_PIN, LOW);
    state = "OFF";
}

String Camera::getState() const {
    return state;
}