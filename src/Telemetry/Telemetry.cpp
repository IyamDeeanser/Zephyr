#include "Telemetry.h"

void Telemetry::transmit(float oriXIDeg, float oriYIDeg, float oriZIDeg, float gyroXBDps, float gyroYBDps, float gyroZBDps, float accelXBMS, float accelYBMS, float accelZBMS, float altEstimateM, float tvcY, float tvcZ, float rwX, float baroAltBias, float velXMS, float pressure_hPa, float tempIMUC, float tempBaroC, float voltage, int state, bool abort, bool abortEnabled, float massEstKg, int p1f, int p2f, int p3f, int p1c, int p2c, int p3c, float onTimeSec, float flightTimeSec){
    Serial1.print("TLM"); //Required prefix
    Serial1.print(oriXIDeg, 3);           Serial1.print(",");
    Serial1.print(oriYIDeg, 3);           Serial1.print(",");
    Serial1.print(oriZIDeg, 3);           Serial1.print(",");
    Serial1.print(gyroXBDps, 3);          Serial1.print(",");
    Serial1.print(gyroYBDps, 3);          Serial1.print(",");
    Serial1.print(gyroZBDps, 3);          Serial1.print(",");
    Serial1.print(accelXBMS, 3);          Serial1.print(",");
    Serial1.print(accelYBMS, 3);          Serial1.print(",");
    Serial1.print(accelZBMS, 3);          Serial1.print(",");
    Serial1.print(altEstimateM, 3);       Serial1.print(",");
    Serial1.print(tvcY, 3);               Serial1.print(",");
    Serial1.print(tvcZ, 3);               Serial1.print(",");
    Serial1.print(rwX, 3);                Serial1.print(",");
    Serial1.print(baroAltBias, 3);        Serial1.print(",");
    Serial1.print(velXMS, 3);             Serial1.print(",");
    Serial1.print(pressure_hPa, 3);       Serial1.print(",");
    Serial1.print(tempIMUC, 3);           Serial1.print(",");
    Serial1.print(tempBaroC, 3);          Serial1.print(",");
    Serial1.print(voltage, 2);            Serial1.print(",");
    Serial1.print(state);                 Serial1.print(","); 
    Serial1.print(abort);                 Serial1.print(",");
    Serial1.print(abortEnabled);          Serial1.print(",");
    Serial1.print(massEstKg, 3);          Serial1.print(","); 
    Serial1.print(p1f);                   Serial1.print(",");
    Serial1.print(p2f);                   Serial1.print(",");
    Serial1.print(p3f);                   Serial1.print(",");
    Serial1.print(p1c);                   Serial1.print(",");
    Serial1.print(p2c);                   Serial1.print(",");
    Serial1.print(p3c);                   Serial1.print(",");
    Serial1.print(onTimeSec, 3);          Serial1.print(",");
    Serial1.println(flightTimeSec, 3);
}

void Telemetry::test() {
    Serial1.println("<TEST TRANSMIT BEEP BEEP BOOP BOOP>");
}

void Telemetry::sendStrln(const String & s) {
    Serial1.println(s);
}

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