#include "Telemetry.h"

void Telemetry::begin() {
    Serial1.begin(115200);
}

void Telemetry::transmit(vec3 ori, vec3 accel, vec3 gyro, float altitude, float positionX, float rwValue, float batteryVoltage, const int & systemState, const bool & cameraState, bool reactionWheelState, float onTimeSec, float flightTimeSec, float pressure, float imuTemp, float baroTemp, float GPSSats, float latitude, float longitude) {
    Serial1.print("ROTATLM"); // prefix
    Serial1.print(ori.x, 3);                 Serial1.print(",");
    Serial1.print(ori.y, 3);                 Serial1.print(",");
    Serial1.print(ori.z, 3);                 Serial1.print(",");
    Serial1.print(accel.x, 3);               Serial1.print(",");
    Serial1.print(accel.y, 3);               Serial1.print(",");
    Serial1.print(accel.z, 3);               Serial1.print(",");
    Serial1.print(gyro.x, 3);                Serial1.print(",");
    Serial1.print(gyro.y, 3);                Serial1.print(",");
    Serial1.print(gyro.z, 3);                Serial1.print(",");
    Serial1.print(altitude, 3);              Serial1.print(",");
    Serial1.print(positionX, 3);             Serial1.print(",");
    Serial1.print(rwValue, 3);               Serial1.print(",");
    Serial1.print(batteryVoltage, 3);        Serial1.print(",");
    Serial1.print(systemState);              Serial1.print(",");
    Serial1.print(cameraState);              Serial1.print(",");
    Serial1.print(reactionWheelState);                  Serial1.print(",");
    Serial1.print(onTimeSec, 3);             Serial1.print(",");
    Serial1.print(flightTimeSec, 3);         Serial1.print(",");
    Serial1.print(pressure, 3);              Serial1.print(",");
    Serial1.print(imuTemp, 3);               Serial1.print(",");
    Serial1.print(baroTemp, 3);              Serial1.print(",");
    Serial1.print(GPSSats, 3);               Serial1.print(",");
    Serial1.print(latitude, 3);              Serial1.print(",");
    Serial1.println(longitude, 3);
    // ! IF NOT LOGGING FAST ENOUGH use Serial1.flush() to push all chars out before moving on! (blocking function)
}

void Telemetry::printlnStr(const String & s) {
    Serial1.println(s);
}

// Theres a 'Seria.readString() function that does this better LOL
String Telemetry::read() {
    static String result;
    while (Serial1.available() > 0) {
        char c = Serial1.read();
        if(c == '<') {
            result = "";
        } else if (c == '>' || c == '\n') {
            return result;
        } else {
            result += c;
            if(result.length() > 30) result = "";
        }
    }
    return "";
}