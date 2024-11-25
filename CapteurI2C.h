#ifndef CAPTEURI2C_H
#define CAPTEURI2C_H

//#include "I2C.h"
#include <stdint.h>
#include "mbed.h"

class CapteurI2C {
    protected:
    I2C &_i2c; // Ref a une instance d I2C
    int _adresse; // adresse du capteur

    public:
    CapteurI2C(I2C &i2c, int adresse); // Constructeur
    bool lireRegistre(char registre, char *data, int taille); // Fonction pour lire un registre d'un capteur en I2C
};

#endif // CapteurI2C_H