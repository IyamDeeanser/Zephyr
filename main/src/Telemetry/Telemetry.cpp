#include "Telemetry.h"

Telemetry::Telemetry(/* args */)
{
    Serial.begin(9600);
}

void Telemetry::Send(const String & s) {
    Serial.print(s);
}

void Sendln(const String & s) {
    Send(s + '\n');
}

String Telemetry::Read() {
    static String result;
    while (Serial.available() > 0) {
        char c = Serial.read();
        if(c == '<') {
            result.clear();
        } else if (c == '>' || c == '\n') {
            return result;
        } else {
            result += c;
        }
    }
    return "";
}