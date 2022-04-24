#include "SD_File.h"

void SD_File::begin(String name, String folderPath) {
    String filePathStr = folderPath + name;
    char buffer[filePathStr.length() + 1];
    filePathStr.toCharArray(buffer, filePathStr.length() + 1);
    
    if(!SD.exists(buffer)) {
        File file = SD.open(buffer, FILE_WRITE);
        file.close();
    } else {
        int num = 2, periodIndex = name.indexOf('.');
        String newName;
        while(true) {
            if(periodIndex == -1) {
                newName = name + num++;
            } else {
                String a = name.substring(0, periodIndex);
                String b = name.substring(periodIndex, name.length());
                newName = a + num++ + b;
            }

            String filePathStr = folderPath + newName;
            filePathStr.toCharArray(buffer, filePathStr.length() + 1);
            if(!SD.exists(buffer)) {
                File file = SD.open(buffer, FILE_WRITE);
                file.close();
                break;
            }
        }
    }
    
    // sets filePath to result
    filePathStr.toCharArray(filePath, filePathStr.length() + 1);
}

void SD_File::print(String s) {
    if(canWrite) {
        File file = SD.open(filePath, FILE_WRITE);
        file.print(s);
        file.close();
    }
}

void SD_File::println(String s) {
    if(canWrite) {
        File file = SD.open(filePath, FILE_WRITE);
        file.println(s);
        file.close();
    }
}

void SD_File::eject() {
    canWrite = false;
}

void SD_File::logData(vec3 ori, vec3 accel, vec3 accelHG, vec3 gyro, float altitude, float rwValue, float batteryVoltage, const int & systemState, const bool & cameraState, bool reactionWheelState, float onTimeSec, float flightTimeSec, float pressure, float imuTemp, float baroTemp, float GPSSats, float latitude, float longitude, float positionX) {
    Serial1.print(ori.x, 3);                 Serial1.print(",");
    Serial1.print(ori.y, 3);                 Serial1.print(",");
    Serial1.print(ori.z, 3);                 Serial1.print(",");
    Serial1.print(accel.x, 3);               Serial1.print(",");
    Serial1.print(accel.y, 3);               Serial1.print(",");
    Serial1.print(accel.z, 3);               Serial1.print(",");
    Serial1.print(accelHG.x, 3);             Serial1.print(",");
    Serial1.print(accelHG.y, 3);             Serial1.print(",");
    Serial1.print(accelHG.z, 3);             Serial1.print(",");
    Serial1.print(gyro.x, 3);                Serial1.print(",");
    Serial1.print(gyro.y, 3);                Serial1.print(",");
    Serial1.print(gyro.z, 3);                Serial1.print(",");
    Serial1.print(altitude, 3);              Serial1.print(",");
    Serial1.print(positionX, 3);             Serial1.print(",");
    Serial1.print(rwValue, 3);               Serial1.print(",");
    Serial1.print(batteryVoltage, 3);        Serial1.print(",");
    Serial1.print(systemState);              Serial1.print(",");
    Serial1.print(cameraState);              Serial1.print(",");
    Serial1.print(reactionWheelState);       Serial1.print(",");
    Serial1.print(onTimeSec, 3);             Serial1.print(",");
    Serial1.print(flightTimeSec, 3);         Serial1.print(",");
    Serial1.print(pressure, 3);              Serial1.print(",");
    Serial1.print(imuTemp, 3);               Serial1.print(",");
    Serial1.print(baroTemp, 3);              Serial1.print(",");
    Serial1.print(GPSSats);                  Serial1.print(",");
    Serial1.print(latitude, 4);              Serial1.print(",");
    Serial1.println(longitude, 4);
    // ! IF NOT LOGGING FAST ENOUGH use Serial1.flush() to push all chars out before moving on! (blocking function)
}