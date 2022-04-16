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

void SD_File::logData(float oriXIDeg, float oriYIDeg, float oriZIDeg, float gyroXBDps, float gyroYBDps, float gyroZBDps, float accelXBMS, float accelYBMS, float accelZBMS, float altEstimateM, float tvcY, float tvcZ, float rwX, float baroAltBias, float velXMS, float pressure_hPa, float tempIMUC, float tempBaroC, float voltage, int state, bool abort, bool abortEnabled, float massEstKg, int p1f, int p2f, int p3f, int p1c, int p2c, int p3c, float onTimeSec, float flightTimeSec){
    File file = SD.open(filePath, FILE_WRITE);
    file.print(oriXIDeg, 3);           file.print(",");
    file.print(oriYIDeg, 3);           file.print(",");
    file.print(oriZIDeg, 3);           file.print(",");
    file.print(gyroXBDps, 3);          file.print(",");
    file.print(gyroYBDps, 3);          file.print(",");
    file.print(gyroZBDps, 3);          file.print(",");
    file.print(accelXBMS, 3);          file.print(",");
    file.print(accelYBMS, 3);          file.print(",");
    file.print(accelZBMS, 3);          file.print(",");
    file.print(altEstimateM, 3);       file.print(",");
    file.print(tvcY, 3);               file.print(",");
    file.print(tvcZ, 3);               file.print(",");
    file.print(rwX, 3);                file.print(",");
    file.print(baroAltBias, 3);        file.print(",");
    file.print(velXMS, 3);             file.print(",");
    file.print(pressure_hPa, 3);       file.print(",");
    file.print(tempIMUC, 3);           file.print(",");
    file.print(tempBaroC, 3);          file.print(",");
    file.print(voltage, 2);            file.print(",");
    file.print(state);                 file.print(","); 
    file.print(abort);                 file.print(",");
    file.print(abortEnabled);          file.print(",");
    file.print(massEstKg, 3);          file.print(","); 
    file.print(p1f);                   file.print(",");
    file.print(p2f);                   file.print(",");
    file.print(p3f);                   file.print(",");
    file.print(p1c);                   file.print(",");
    file.print(p2c);                   file.print(",");
    file.print(p3c);                   file.print(",");
    file.print(onTimeSec, 3);          file.print(",");
    file.println(flightTimeSec, 3);
    file.close();
}
