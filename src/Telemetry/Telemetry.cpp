#include "Telemetry.h"

void Telemetry::begin() {
    Serial1.begin(115200);
}

void Telemetry::transmit(vec3 ori, vec3 accel, vec3 gyro, float altitude, float rwValue, vec3 velocity, vec3 position, float batteryVoltage, const int & systemState, const bool & cameraState, float reactionWheelState, float onTimeSec, float flightTimeSec, float pressure, float imuTemp, float baroTemp, float GPSSats, float latitude, float longitude, bool RWState) {
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
    Serial1.print(rwValue, 3);               Serial1.print(",");
    Serial1.print(batteryVoltage, 3);        Serial1.print(",");
    Serial1.print(systemState);              Serial1.print(",");
    Serial1.print(cameraState);              Serial1.print(",");
    Serial1.print(RWState);                  Serial1.print(",");
    Serial1.print(onTimeSec, 3);             Serial1.print(",");
    Serial1.print(flightTimeSec, 3);         Serial1.print(",");
    Serial1.print(velocity.x, 3);            Serial1.print(",");
    Serial1.print(velocity.y, 3);            Serial1.print(",");
    Serial1.print(velocity.z, 3);            Serial1.print(",");
    Serial1.print(position.x, 3);            Serial1.print(",");
    Serial1.print(position.y, 3);            Serial1.print(",");
    Serial1.print(position.z, 3);            Serial1.print(",");
    Serial1.print(reactionWheelState, 3);    Serial1.print(",");
    Serial1.print(pressure, 3);              Serial1.print(",");
    Serial1.print(imuTemp, 3);               Serial1.print(",");
    Serial1.print(baroTemp, 3);              Serial1.print(",");
    Serial1.print(GPSSats, 3);               Serial1.print(",");
    Serial1.print(latitude, 3);              Serial1.print(",");
    Serial1.println(longitude, 3);
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
            if(result.length() > 27) result = "";
        }
    }
    return "";
}