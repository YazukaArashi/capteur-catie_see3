#ifndef CAPTEURHUMIDITETEMPERATURE_H
#define CAPTEURHUMIDITETEMPERATURE_H

#include "CapteurI2C.h" // classe mere
#include <math.h> 
#include <stdint.h> 
#include "mbed.h"

class CapteurHumiditeTemperature : public CapteurI2C {
    // classe fille de I2C
    public: 
    CapteurHumiditeTemperature(I2C &i2C, int adresse); // Constructeur
    // Methode pour lire les valeurs (humidite et temperature)
    int lireHumidite();
    int lireTemperature();
};

#endif // CAPTEURHUMIDITETEMPERATURE_H

