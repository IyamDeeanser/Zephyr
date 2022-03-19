// Telemetry Code Here
// ! STRING LIB NEEDED!
namespace TELE {
    void Send(const String & s) {
        Serial.print(s + '\n');
    }
}