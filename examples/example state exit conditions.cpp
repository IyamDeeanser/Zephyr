    //Detecting engine burnout
    if(imu.bodyAccelX <= constants.burnoutAccelThreshold && (timer.currentTime - timer.launchTime) >= constants.burnoutDetectTime) {
        timer.burnoutTime = timer.currentTime;

        state = UNPOWERED_ASCENT;
    }

    //Apogee Detect
    if(baro.altitudeEstimate > baro.maximumAltitude){
        baro.maximumAltitude = baro.altitudeEstimate;
        timer.apogeeDetectStartTime = timer.currentTime; 
    }

    if((timer.currentTime - timer.apogeeDetectStartTime) >= constants.apogeeDetectTime) { 
        state = DESCENT; 
    }

    //Launch detect
    if(accelX >= constants.launchAccelThreshold) {
        timer.loggingFrequency = constants.logSpeedHigh; //Set logging speed to 100hz
        state = POWERED_ASCENT;
    }

    //descending altitude state change
    if(baro.altitudeEstimate <= constants.parachuteEjectAltitude){
        state = PARACHUTE_DESCENT;
    }

    //detecting touchdown
    if((abs(imu.bodyGyroX_Rad) < 0.05) && (abs(imu.bodyGyroY_Rad) < 0.05) && (abs(imu.bodyGyroZ_Rad) < 0.05)){
        state = LANDED_IDLE;
    }