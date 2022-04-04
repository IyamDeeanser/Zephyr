#include "Telemetry.h"

Telemetry::Telemetry(/* args */)
{
    Serial1.begin(115200);
}

void Telemetry::Send(const String & s) {
    Serial1.print(s);
}

void Telemetry::Sendln(const String & s) {
    Send(s + '\n');
}

String Telemetry::Read() {
    static String result;
    while (Serial1.available() > 0) {
        char c = Serial1.read();
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