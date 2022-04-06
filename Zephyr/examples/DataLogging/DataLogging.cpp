#include "DataLogging.h"

bool DataLogging::begin(int cs){
    return SD.begin(cs);
}

void DataLogging::createLogFiles(){
    for(int i = 1; i < 999; i++){
        sprintf(fileName, "FL%.3u.csv", i);
        if(!SD.exists(fileName)){
            flightNumber = i;
            
            flightLogFile = SD.open(fileName, FILE_WRITE);
            flightLogFile.println("State,Abort,Abort Enabled,On Time (sec),Flight Time (sec),Delta Time (us),Avi Batt (volts),Vehicle Mass (kg),Thrust (N),Ori xi (Deg),Ori yi (Deg),Ori zi (Deg),Ori Setpoint x(Deg),Ori Setpoint y(Deg),Ori Setpoint z(Deg),Gyro xb (Deg/s),Gyro yb (Deg/s),Gyro zb (Deg/s),Accel xb (m/s^2),Accel yb (m/s^2),Accel zb (m/s^2),Accel xi (m/s^2),Accel yi (m/s^2),Accel zi (m/s^2),Vel x (m/s), Alt Bias (m),Baro Alt AGL (m),Alt Estimate (m),Pressure (hPa),Baro Temp (C),IMU Temp (C),Reaction Wheel Value,TVC y,TVC z,PID y(Nm),PID z(Nm),PID y rot(Nm),PID z rot(Nm),PID Error x(Deg),PID Error y(Deg),PID Error z(Deg),P1 Fire,P2 Fire,P3 Fire,P1 Cont,P2 Cont,P3 Cont");
            
            for(int i = 1; i < 999; i++){
                sprintf(fileName, "SL%.3u.csv", i);
                if(!SD.exists(fileName)){
                    settingsLogFile = SD.open(fileName, FILE_WRITE);
                    settingsLogFile.println("PARAMETER,VALUE");
                    settingsLogFile.println();
                    return;
                }
            }
        }
    }
}

void DataLogging::logSettings(float propellantBurnTime,float propellantMass,float vehicleLoadedMass,float kP_x,float kI_x,float kD_x,float kP_y,float kI_y,float kD_y,float kP_z,float kI_z,float kD_z,float integralLimit,float launchAccelThreshold,float burnoutAccelThreshold,int landingDetectThreshold,int abortThreshold,int abortSafeTime,int burnoutDetectTime,int telemetryTransmitSpeed,int logSpeedLow,int logSpeedHigh,float gyroXBias,float gyroYBias,float gyroZBias,int tvcYDirection,int tvcZDirection,int maxActuationY,int maxActuationZ,float actuatorYRatio,float actuatorZRatio,float actuatorYCenter,float actuatorZCenter, int parachuteDeployAltitude, int apogeeDetectTime){
    settingsLogFile.print("Flight Number:,");                   settingsLogFile.println(flightNumber);
    settingsLogFile.print("Propellant Burn Time (s):,");        settingsLogFile.println(propellantBurnTime);
    settingsLogFile.print("Propellant Mass (kg):,");            settingsLogFile.println(propellantMass, 3);
    settingsLogFile.print("Vehicle Loaded Mass (kg):,");        settingsLogFile.println(vehicleLoadedMass, 3);
    settingsLogFile.print("Kp X:,");                            settingsLogFile.println(kP_x);
    settingsLogFile.print("Ki X:,");                            settingsLogFile.println(kI_x);
    settingsLogFile.print("Kd X:,");                            settingsLogFile.println(kD_x);
    settingsLogFile.print("Kp Y:,");                            settingsLogFile.println(kP_y);
    settingsLogFile.print("Ki Y:,");                            settingsLogFile.println(kI_y);
    settingsLogFile.print("Kd Y:,");                            settingsLogFile.println(kD_y);
    settingsLogFile.print("Kp Z:,");                            settingsLogFile.println(kP_z);
    settingsLogFile.print("Ki Z:,");                            settingsLogFile.println(kI_z);
    settingsLogFile.print("Kd Z:,");                            settingsLogFile.println(kD_z);
    settingsLogFile.print("TVC Integral Limit:,");              settingsLogFile.println(integralLimit);
    settingsLogFile.print("Launch Accel Threshold (m/s^2):,");  settingsLogFile.println(launchAccelThreshold);
    settingsLogFile.print("Burnout Accel Threshold (m/s^2):,"); settingsLogFile.println(burnoutAccelThreshold);
    settingsLogFile.print("Landing Detect Threshold (m):,");    settingsLogFile.println(landingDetectThreshold);
    settingsLogFile.print("Parachute Deploy Altitude (m):,");   settingsLogFile.println(parachuteDeployAltitude);
    settingsLogFile.print("Abort Threshold (deg):,");           settingsLogFile.println(abortThreshold);
    settingsLogFile.print("Abort Safe Time (s):,");             settingsLogFile.println(abortSafeTime / 1000000.0f);
    settingsLogFile.print("Burnout Detect Time (s):,");         settingsLogFile.println(burnoutDetectTime / 1000000.0f);
    settingsLogFile.print("Apogee Detect Time (s):,");          settingsLogFile.println(apogeeDetectTime / 1000000.0f);
    settingsLogFile.print("Telemetry Transmit Rate (Hz):,");    settingsLogFile.println(1 / (telemetryTransmitSpeed / 1000000.0f));
    settingsLogFile.print("Ground Log Rate (Hz):,");            settingsLogFile.println(1 / (logSpeedLow / 1000000.0f));
    settingsLogFile.print("In Flight Log Rate (Hz):,");         settingsLogFile.println(1 / (logSpeedHigh / 1000000.0f));
    settingsLogFile.print("Gyro Bias X:,");                     settingsLogFile.println(gyroXBias, 3);
    settingsLogFile.print("Gyro Bias Y:,");                     settingsLogFile.println(gyroYBias, 3);
    settingsLogFile.print("Gyro Bias Z:,");                     settingsLogFile.println(gyroZBias, 3);
    settingsLogFile.print("TVC Direction Y:,");                 settingsLogFile.println(tvcYDirection);
    settingsLogFile.print("TVC Direction Z:,");                 settingsLogFile.println(tvcZDirection);
    settingsLogFile.print("TVC Max Y (deg):,");                 settingsLogFile.println(maxActuationY);
    settingsLogFile.print("TVC Max Z (deg):,");                 settingsLogFile.println(maxActuationZ);
    settingsLogFile.print("TVC Gear Ratio Y:,");                settingsLogFile.println(actuatorYRatio);
    settingsLogFile.print("TVC Gear Ratio Z:,");                settingsLogFile.println(actuatorZRatio);
    settingsLogFile.print("TVC Center Y:,");                    settingsLogFile.println(actuatorYCenter);
    settingsLogFile.print("TVC Center Z:,");                    settingsLogFile.println(actuatorZCenter);

    settingsLogFile.close();
}

void DataLogging::log(int state, bool abort, bool abortEnabled, float onTimeSec, float flightTimeSec, unsigned long dtMicro, float voltage, float massEstKg, float thrustEstN, float oriXIDeg, float oriYIDeg, float oriZIDeg, float gyroXBDps, float gyroYBDps, float gyroZBDps, float accelXBMS, float accelYBMS, float accelZBMS, float accelXIMS, float accelYIMS, float accelZIMS, float velXMS, float baroAltBias, float baroAltAGLM, float altEstimateM, float pressure_hPa, float tempBaroC, float tempIMUC, float rwX, float tvcY, float tvcZ, float pidYOutNm, float pidZOutNm, float pidYOutNmRot, float pidZOutNmRot, float pidXErrorDeg, float pidYErrorDeg, float pidZErrorDeg, float oriSetpointXDeg, float oriSetpointYDeg, float oriSetpointZDeg, int p1f, int p2f, int p3f, int p1c, int p2c, int p3c){
    flightLogFile.print(state);                 flightLogFile.print(","); 
    flightLogFile.print(abort);                 flightLogFile.print(",");
    flightLogFile.print(abortEnabled);          flightLogFile.print(",");
    flightLogFile.print(onTimeSec, 3);          flightLogFile.print(",");
    flightLogFile.print(flightTimeSec, 3);      flightLogFile.print(",");
    flightLogFile.print(dtMicro);               flightLogFile.print(",");
    flightLogFile.print(voltage, 2);            flightLogFile.print(",");
    flightLogFile.print(massEstKg, 3);          flightLogFile.print(","); 
    flightLogFile.print(thrustEstN, 3);         flightLogFile.print(",");
    flightLogFile.print(oriXIDeg, 3);           flightLogFile.print(",");
    flightLogFile.print(oriYIDeg, 3);           flightLogFile.print(",");
    flightLogFile.print(oriZIDeg, 3);           flightLogFile.print(",");
    flightLogFile.print(oriSetpointXDeg, 3);    flightLogFile.print(",");
    flightLogFile.print(oriSetpointYDeg, 3);    flightLogFile.print(",");
    flightLogFile.print(oriSetpointZDeg, 3);    flightLogFile.print(",");
    flightLogFile.print(gyroXBDps, 3);          flightLogFile.print(",");
    flightLogFile.print(gyroYBDps, 3);          flightLogFile.print(",");
    flightLogFile.print(gyroZBDps, 3);          flightLogFile.print(",");
    flightLogFile.print(accelXBMS, 3);          flightLogFile.print(",");
    flightLogFile.print(accelYBMS, 3);          flightLogFile.print(",");
    flightLogFile.print(accelZBMS, 3);          flightLogFile.print(",");
    flightLogFile.print(accelXIMS, 3);          flightLogFile.print(",");
    flightLogFile.print(accelYIMS, 3);          flightLogFile.print(",");
    flightLogFile.print(accelZIMS, 3);          flightLogFile.print(",");
    flightLogFile.print(velXMS, 3);             flightLogFile.print(",");
    flightLogFile.print(baroAltBias, 3);        flightLogFile.print(",");
    flightLogFile.print(baroAltAGLM, 3);        flightLogFile.print(",");
    flightLogFile.print(altEstimateM, 3);       flightLogFile.print(",");
    flightLogFile.print(pressure_hPa, 3);       flightLogFile.print(",");
    flightLogFile.print(tempBaroC, 3);          flightLogFile.print(",");
    flightLogFile.print(tempIMUC, 3);           flightLogFile.print(",");
    flightLogFile.print(rwX, 3);                flightLogFile.print(",");
    flightLogFile.print(tvcY, 3);               flightLogFile.print(",");
    flightLogFile.print(tvcZ, 3);               flightLogFile.print(",");
    flightLogFile.print(pidYOutNm, 3);          flightLogFile.print(",");
    flightLogFile.print(pidZOutNm, 3);          flightLogFile.print(",");
    flightLogFile.print(pidYOutNmRot, 3);       flightLogFile.print(",");
    flightLogFile.print(pidZOutNmRot, 3);       flightLogFile.print(",");
    flightLogFile.print(pidXErrorDeg, 3);       flightLogFile.print(",");
    flightLogFile.print(pidYErrorDeg, 3);       flightLogFile.print(",");
    flightLogFile.print(pidZErrorDeg, 3);       flightLogFile.print(",");
    flightLogFile.print(p1f);                   flightLogFile.print(",");
    flightLogFile.print(p2f);                   flightLogFile.print(",");
    flightLogFile.print(p3f);                   flightLogFile.print(",");
    flightLogFile.print(p1c);                   flightLogFile.print(",");
    flightLogFile.print(p2c);                   flightLogFile.print(",");
    flightLogFile.println(p3c);
}

void DataLogging::end(){
    flightLogFile.close();
}
