#ifndef DATALOGGING_H
#define DATALOGGING_H

#include <SD.h>

class DataLogging {
    public:
        bool begin(int cs);

        void createLogFiles();

        void logSettings(float propellantBurnTime,float propellantMass,float vehicleLoadedMass,float kP_x,float kI_x,float kD_x,float kP_y,float kI_y,float kD_y,float kP_z,float kI_z,float kD_z,float integralLimit,float launchAccelThreshold,float burnoutAccelThreshold,int landingDetectThreshold,int abortThreshold,int abortSafeTime,int burnoutDetectTime,int telemetryTransmitSpeed,int logSpeedLow,int logSpeedHigh,float gyroXBias,float gyroYBias,float gyroZBias,int tvcYDirection,int tvcZDirection,int maxActuationY,int maxActuationZ,float actuatorYRatio,float actuatorZRatio,float actuatorYCenter,float actuatorZCenter, int parachuteDeployAltitude, int apogeeDetectTime);

        void log(int state, bool abort, bool abortEnabled, float onTimeSec, float flightTimeSec, unsigned long dtMicro, float voltage, float massEstKg, float thrustEstN, float oriXIDeg, float oriYIDeg, float oriZIDeg, float gyroXBDps, float gyroYBDps, float gyroZBDps, float accelXBMS, float accelYBMS, float accelZBMS, float accelXIMS, float accelYIMS, float accelZIMS, float velXMS, float baroAltBias, float baroAltAGLM, float altEstimateM, float pressure_hPa, float tempBaroC, float tempIMUC, float rwX, float tvcY, float tvcZ, float pidYOutNm, float pidZOutNm, float pidYOutNmRot, float pidZOutNmRot, float pidXErrorDeg, float pidYErrorDeg, float pidZErrorDeg, float oriSetpointXDeg, float oriSetpointYDeg, float oriSetpointZDeg, int p1f, int p2f, int p3f, int p1c, int p2c, int p3c);

        void end();
    private:
        int flightNumber;

        File flightLogFile;
        File settingsLogFile;
        char fileName[16];
};

#endif
