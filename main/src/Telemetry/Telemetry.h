// Telemetry Functions 
// written by Brian
// Documentation: https://www.youtube.com/watch?v=qCjCRBLv_VM

// ! STRING LIB NEEDS TO BE INCLUDED!
#ifndef TELEMETRY_H
#define TELEMETRY_H


class Telemetry
{
private:
    /* data */
public:
    Telemetry();

    // @ sends string through serial port
    void Send(const String & s);
    void Sendln(const String & s);

    // @ pre-condition: commands must be received in this format: <command>
    // @ post-condition: returns command in string format. results empty string if no command
    String Read();
};

#endif