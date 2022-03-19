// Telemetry Code Here
// written by Brian
// ! STRING LIB NEEDED!
// Documentation: https://www.youtube.com/watch?v=qCjCRBLv_VM

// @ pre-condition: serial port is set up properly
namespace TELE {

    // @ sends string through serial port
    void Send(const String & s) {
        Serial.print(s);
    }
    
    void Sendln(const String & s) {
        Send(s + '\n');
    }
    
    // @ pre-condition: commands must be received in this format: <command>
    // @ post-condition: returns command in string format. results empty string if no command
    String Read() {
        static String result;
        while (Serial.available() > 0) {
            char c = Serial.read();
            if(c == '<') {
                result.clear();
            } else if (c == '>' || c == '\n') {
                return result;
            } else {
                result += c;
            }
        }
        return "";
    }
}