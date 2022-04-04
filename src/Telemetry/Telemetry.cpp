#include "Telemetry.h"

Telemetry::Telemetry(/* args */)
{
    Serial.begin(115200);
}

void Telemetry::Send(const String & s) {
    Serial.print(s);
}

void Telemetry::Sendln(const String & s) {
    Send(s + '\n');
}

String Telemetry::Read() {
    static String result;
    while (Serial.available() > 0) {
        char c = Serial.read();
        if(c == '<') {
            result = "";
        } else if (c == '>' || c == '\n') {
            return result;
        } else {
            result += c;
        }
    }
    return "";
}