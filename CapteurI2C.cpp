#include "CapteurI2C.h"

// Constructeur
CapteurI2C::CapteurI2C(I2C &i2c, int adresse) : _i2c(i2c), _adresse(adresse << 1) {}

// Fonction pour lire un registre d'un capteur en I2C
bool CapteurI2C::lireRegistre(char registre, char *data, int taille) {
    if (_i2c.write(_adresse, &registre, 1) != 0) // Ecrire le registre a lire
    {
        return false; // Erreur d'écriture
    }
    if (_i2c.read(_adresse, data, taille) != 0) // Lecture des donnees du registre
    {
        return false; // Erreur de lecture
    }
    return true;
}
