#include "Voltage.h"

float Voltage::getVoltage() {
    return analogRead(VOLTAGE_DIV_PIN) * ((3.3 / 1023.0) * (86600.0 + 30100.0) / 30100.0);
}