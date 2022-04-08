#include "Camera.h"

void Camera::initialize() {
    pinMode(CAMERA_PIN, OUTPUT);
}

void Camera::turnOn() {
    digitalWrite(CAMERA_PIN, HIGH);
}

void Camera::turnOff() {
    digitalWrite(CAMERA_PIN, LOW);
}