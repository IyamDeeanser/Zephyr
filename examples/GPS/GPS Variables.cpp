#include <Adafruit_GPS.h>

class GPSVariables{
public:
    //A timer to make sure data isn't jamming and updating properly
    uint32_t timer;

    //Latitude and Longitude Numbers 
    float latitude;
    float longitude;

    //Cardingal directions in N,E,S,W for latitude and longitude
    char latDir;
    char lonDir;

    //Other variables
    float altitude;
    float speed;
    float angle;
    int numSatellites;

    //Fix info
    int fix;
    int fixQuality;

    GPSVariables(){
        //A timer to make sure data isn't jamming and updating properly
        timer = millis();

        //Latitude and Longitude Numbers 
        float latitude = 0.0;
        float longitude 0.0;

        //Cardingal directions in N,E,S,W for latitude and longitude
        char latDir = 'N';
        char lonDir = 'W';

        //Other variables
        float altitude = 0.0;
        float speed = 0.0;
        float angle = 0.0;
        int numSatellites = 0;

        //Fix info
        int fix = 0;
        int fixQuality = 0;
    }
};
