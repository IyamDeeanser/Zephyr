#include "Baro.h"

Barometer::Barometer() {

    if (!bmp.begin_I2C()) {   
        while(true);
        // ! ERROR
    }
  // Set up oversampling and filter initialization
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}


void Barometer::update() {
    if (! bmp.performReading()) {
        // Serial.println("Failed to perform reading :(");
        return;
    }

    temperature =  bmp.temperature;

    pressure = bmp.pressure / 100.0;

    altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
}