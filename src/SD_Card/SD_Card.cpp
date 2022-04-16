#include "SD_Card.h"

SD_Card::SD_Card() {

}

bool SD_Card::begin(int chipSelect){
    return SD.begin(chipSelect);
}

String SD_Card::createNewDir() {
    int num = 1;
    char name[] = "Launch";
    char buffer[20];

    sprintf(buffer,"%s_%d", name, num);
    while(SD.exists(buffer)) {
        sprintf(buffer,"%s_%d", name, ++num);
    }

    SD.mkdir(buffer);
    
    Serial.println(buffer);

    return '/' + String(buffer) + '/';
}