#include "States.h"

String states::stateToStr(const States State) {
    switch(State) {
        case GROUND_IDLE:
            return "GROUND IDLE";
        case LAUNCH_READY:
            return "LAUNCH READY";
        case POWERED_ASCENT:
            return "POWERED ASCENT";
        case UNPOWERED_ASCENT:
            return "UNPOWERED ASCENT";
        case SEPARATION:
            return "SEPARATION";
        case APOGEE:
            return "APOGEE";
        case PARACHUTE_DESCENT:
            return "PARACHUTE DESCENT";
        case ROLL_CONTROL:
            return "ROLL CONTROL";
        case MANUAL_ROLL_CONTROL:
            return "MANUAL ROLL CONTROL";
        case LANDING:
            return "LANDING";
        case MISSION_COMPLETE:
            return "MISSION COMPLETE";
        case ABORT:
            return "ABORT";
        default:
            return "ERROR";
    }
}