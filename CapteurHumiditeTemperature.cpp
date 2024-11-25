#include "CapteurHumiditeTemperature.h"
#include <stdio.h>

// Classe pour le capteur d'humidité et de température
//Constructeur
CapteurHumiditeTemperature::CapteurHumiditeTemperature(I2C &i2c, int adresse) : CapteurI2C(i2c, adresse) {}

// Methode pour lire donnees (humidite et temperature)
int CapteurHumiditeTemperature::lireHumidite() {
    char data[2] = {0};
    if (!lireRegistre(0xE5, data, 2)) // Lecture de l'humidité via le registre
    {
        printf("Erreur lecture humidite\n");
        return -1;
    }
    int16_t valeur = (data[0] << 8) | (data[1] & 0xFC);
    return -6 + (125 * valeur / pow(2, 16)); // Calcul de la valeur de l'humidité via la datasheet
}

int CapteurHumiditeTemperature::lireTemperature() {
    char data[2] = {0};
    if (!lireRegistre(0xE3, data, 2)) // Lecture de la température via le registre
    {
        printf("Erreur lecture temperature\n");
        return -1;
    }
    int16_t valeur = (data[0] << 8) | (data[1] & 0xFC);
    return -46.85 + (175.72 * valeur / pow(2, 16)); // Calcul de la valeur de la température via la datasheet
}

