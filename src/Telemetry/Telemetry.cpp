#include "Telemetry.h"

void Telemetry::begin() {
    Serial1.begin(115200);
}

void Telemetry::transmit(float oriX, float oriY, float oriZ, float accelX, float accelY, float accelZ, float gyroX, float gyroY, float gyroZ, float altitude, float rwValue, float velocityX, float velocityY, float velocityZ, float positionX, float positionY, float positionZ, float batteryVoltage, float systemState, float cameraState, float reactionWheelState, float onTimeSec, float flightTimeSec, float pressure, float imuTemp, float baroTemp, float GPSSats, float latitude, float longitude){
    Serial1.print("ROTATLM"); // prefix
    Serial1.print(oriX, 3);           Serial1.print(",");
    Serial1.print(oriY, 3);           Serial1.print(",");
    Serial1.print(oriZ, 3);           Serial1.print(",");
    Serial1.print(accelX, 3);           Serial1.print(",");
    Serial1.print(accelY, 3);           Serial1.print(",");
    Serial1.print(accelZ, 3);           Serial1.print(",");
    Serial1.print(gyroX, 3);           Serial1.print(",");
    Serial1.print(gyroY, 3);           Serial1.print(",");
    Serial1.print(gyroZ, 3);           Serial1.print(",");
    Serial1.print(altitude, 3);           Serial1.print(",");
    Serial1.print(rwValue, 3);           Serial1.print(",");
    Serial1.print(velocityX, 3);           Serial1.print(",");
    Serial1.print(velocityY, 3);           Serial1.print(",");
    Serial1.print(velocityZ, 3);           Serial1.print(",");
    Serial1.print(positionX, 3);           Serial1.print(",");
    Serial1.print(positionY, 3);           Serial1.print(",");
    Serial1.print(positionZ, 3);           Serial1.print(",");
    Serial1.print(batteryVoltage, 3);           Serial1.print(",");
    Serial1.print(systemState, 3);           Serial1.print(",");
    Serial1.print(cameraState, 3);           Serial1.print(",");
    Serial1.print(reactionWheelState, 3);           Serial1.print(",");
    Serial1.print(onTimeSec, 3);           Serial1.print(",");
    Serial1.print(flightTimeSec, 3);           Serial1.print(",");
    Serial1.print(pressure, 3);           Serial1.print(",");
    Serial1.print(imuTemp, 3);           Serial1.print(",");
    Serial1.print(baroTemp, 3);           Serial1.print(",");
    Serial1.print(GPSSats, 3);           Serial1.print(",");
    Serial1.print(latitude, 3);           Serial1.print(",");
    Serial1.print(longitude, 3);
}

void Telemetry::test() {
    Serial1.println("<TEST TRANSMIT BEEP BEEP BOOP BOOP>");
}


void Telemetry::sendStrln(const String & s) {
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