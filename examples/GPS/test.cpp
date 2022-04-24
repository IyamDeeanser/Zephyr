//        ⣠⣴⣶⣿⠿⢿⣶⣶⣦⣄⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⣼⡿⠋⠁⠀⠀⠀⢀⣈⠙⢿⣷⡄⠀⠀
// ⠀⠀⠀⠀⢸⣿⠁⠀⢀⣴⣿⠿⠿⠿⠿⠿⢿⣷⣄⠀
// ⠀⢀⣀⣠⣾⣿⡇⠀⣾⣿⡄⠀⠀⠀⠀⠀⠀⠀⠹⣧
// ⣾⡿⠉⠉⣿⠀⡇⠀⠸⣿⡌⠓⠶⠤⣤⡤⠶⢚⣻⡟
// ⣿⣧⠖⠒⣿⡄⡇⠀⠀⠙⢿⣷⣶⣶⣶⣶⣶⢿⣿⠀
// ⣿⡇⠀⠀⣿⡇⢰⠀⠀⠀⠀⠈⠉⠉⠉⠁⠀⠀⣿⠀
// ⣿⡇⠀⠀⣿⡇⠈⡄⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⠀
// ⣿⣷⠀⠀⣿⡇⠀⠘⠦⣄⣀⣀⣀⣀⣀⡤⠊⠀⣿⠀
// ⢿⣿⣤⣀⣿⡇⠀⠀⠀⢀⣀⣉⡉⠁⣀⡀⠀⣾⡟⠀
// ⠀⠉⠛⠛⣿⡇⠀⠀⠀⠀⣿⡟⣿⡟⠋⠀⢰⣿⠃⠀
// ⠀⠀⠀⠀⣿⣧⠀⠀⠀⢀⣿⠃⣿⣇⠀⢀⣸⡯⠀⠀
// ⠀⠀⠀  ⠹⢿⣶⣶⣶⠿⠃⠀⠈⠛⠛⠛⠛
//HELP MEEE HELP

//Test File Version 2
    //With Global Variables 

#include "GPS.h"

//Variable storage object
GPS_Variables GPSVar;

void setup()
{
    SerialUSB.begin(115200);
    GPSVar.GPSBegin();
}

void loop(){
    GPSVar.GPSUpdate();
    SerialUSB.println(GPSVar.latitude);
    SerialUSB.println(GPSVar.longitude);
}
