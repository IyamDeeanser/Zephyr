#include "Telemetry.h"

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