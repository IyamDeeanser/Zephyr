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

void SD_File::logData(vec3 ori, vec3 accel, vec3 accelHG, vec3 gyro, float positionX, float altitude, float rwValue, float batteryVoltage, const int & systemState, const bool & cameraState, bool reactionWheelState, float onTimeSec, float flightTimeSec, float pressure, float imuTemp, float baroTemp, float GPSSats, float latitude, float longitude) {
    File file = SD.open(filePath, O_CREAT | O_WRITE);
    file.print(ori.x, 3);                 file.print(",");
    file.print(ori.y, 3);                 file.print(",");
    file.print(ori.z, 3);                 file.print(",");
    file.print(accel.x, 3);               file.print(",");
    file.print(accel.y, 3);               file.print(",");
    file.print(accel.z, 3);               file.print(",");
    file.print(accelHG.x, 3);             file.print(",");
    file.print(accelHG.y, 3);             file.print(",");
    file.print(accelHG.z, 3);             file.print(",");
    file.print(gyro.x, 3);                file.print(",");
    file.print(gyro.y, 3);                file.print(",");
    file.print(gyro.z, 3);                file.print(",");
    file.print(altitude, 3);              file.print(",");
    file.print(positionX, 3);             file.print(",");
    file.print(rwValue, 3);               file.print(",");
    file.print(batteryVoltage, 3);        file.print(",");
    file.print(systemState);              file.print(",");
    file.print(cameraState);              file.print(",");
    file.print(reactionWheelState);       file.print(",");
    file.print(onTimeSec, 3);             file.print(",");
    file.print(flightTimeSec, 3);         file.print(",");
    file.print(pressure, 3);              file.print(",");
    file.print(imuTemp, 3);               file.print(",");
    file.print(baroTemp, 3);              file.print(",");
    file.print(GPSSats);                  file.print(",");
    file.print(latitude, 4);              file.print(",");
    file.println(longitude, 4);

    file.close();
    // ! IF NOT LOGGING FAST ENOUGH use Serial1.flush() to push all chars out before moving on! (blocking function)
}