/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <math.h>
// Blinking rate in milliseconds
#define BLINKING_RATE 500ms

// Classe de base pour un capteur I2C
class CapteurI2C
{
protected:
    I2C &_i2c;
    int _adresse;

public:
    CapteurI2C(I2C &i2c, int adresse) : _i2c(i2c), _adresse(adresse << 1) {}

    bool lireRegistre(char registre, char *data, int taille)
    {
        if (_i2c.write(_adresse, &registre, 1) != 0)
        {
            return false; // Erreur d'écriture
        }
        if (_i2c.read(_adresse, data, taille) != 0)
        {
            return false; // Erreur de lecture
        }
        return true;
    }
};

// Classe pour le capteur d'humidité et de température
class CapteurHumiditeTemperature : public CapteurI2C
{
public:
    CapteurHumiditeTemperature(I2C &i2c, int adresse)
        : CapteurI2C(i2c, adresse) {}

    int lireHumidite()
    {
        char data[2] = {0};
        if (!lireRegistre(0xE5, data, 2))
        {
            printf("Erreur lecture humidite\n");
            return -1;
        }
        int16_t valeur = (data[0] << 8) | (data[1] & 0xFC);
        return -6 + (125 * valeur / pow(2, 16));
    }

    int lireTemperature()
    {
        char data[2] = {0};
        if (!lireRegistre(0xE3, data, 2))
        {
            printf("Erreur lecture temperature\n");
            return -1;
        }
        int16_t valeur = (data[0] << 8) | (data[1] & 0xFC);
        return -46.85 + (175.72 * valeur / pow(2, 16));
    }
};

class CapteurPression : public CapteurI2C
{
public:
    CapteurPression(I2C &i2c, int adresse)
        : CapteurI2C(i2c, adresse) {}

    int lirePression()
    {
        char data[2] = {0};
        char temp[3] = {0};

        if (!lireRegistre(0xB6, data, 2))
        {
            printf("Erreur lecture temperature\n");
            return -1;
        }
        long int a2 = (data[0] << 8) | data[1];
        printf("a2 = %x\n", a2);

        if (!lireRegistre(0xB4, data, 2))
        {
            printf("Erreur lecture temperature\n");
            return -1;
        }
        long int a1 = (data[0] << 8) | data[1];
        printf("a1 = %x\n", a1);

        if (!lireRegistre(0xB2, data, 2))
        {
            printf("Erreur lecture temperature\n");
            return -1;
        }
        long int a0_temp = (data[0] << 8) | data[1];

        if (!lireRegistre(0xB8, data, 2))
        {
            printf("Erreur lecture temperature\n");
            return -1;
        }
        long int a0 = (a0_temp << 4) | data[1];
        printf("a0 = %x\n", a0);
        


        
        if (!lireRegistre(0xFA, temp, 3))
        {
            printf("Erreur lecture temperature\n");
            return -1;
        }
        //printf("cmd[0] = 0x%02X, cmd[1] = 0x%02X\n", data[0], data[1]);

        long int Dt = (temp[0]<< 16) | (temp[1]<< 8) | temp[2]; 
        Dt = Dt - pow(2,23);
        printf("temp = %d\n", Dt);


        long int Tr = a0 + a1*Dt + a2*pow(Dt, 2);
        printf("Tr = %d\n", Tr);

        return 0;
    }
};

int main()
{
    I2C i2c(P1_I2C_SDA, P1_I2C_SCL);

    CapteurHumiditeTemperature capteurHT(i2c, 0x40); // 8bit I2C address, 0x90
    CapteurPression capteurPression(i2c, 0x70);


    while (true)
    {
        //int humidite = capteurHT.lireHumidite();
        //int temperature = capteurHT.lireTemperature();
        int pression = capteurPression.lirePression();

        /*if (humidite != -1 && temperature != -1)
        {
            printf("Humidité : %d %\n", humidite);
            printf("Température : %d degre C\n", temperature);
        }*/
        if (pression != -1)
        {
            printf("Pression : %d kPa\n", pression);
        }

        

        ThisThread::sleep_for(BLINKING_RATE);
    }
}

/*int humidity = recup_humidity();
        int temperature = recup_temperature();

        printf("Humidite = %d %\n", humidity);
        printf("Temperature = %d degre C\n", temperature);

        i2c.write(addr8bit_pres, &reg_temp_wpres, 1); // Commencer par une écriture. Valeur du registre que l'on veut lire.
        i2c.read(addr8bit_pres, cmd, 2);
        //int16_t tmp2 = (cmd[0] << 8) | (cmd[1] & 0xFC);
        int16_t temperature2 = (cmd[0] << 8) | cmd[1] ;
        printf("cmd[0] = 0x%02X, cmd[1] = 0x%02X\n", cmd[0], cmd[1]);

        i2c.write(addr8bit_pres, &reg_pres, 1); // Commencer par une écriture. Valeur du registre que l'on veut lire.
        i2c.read(addr8bit_pres, cmd, 2);
        // int16_t tmp2 = (cmd[0] << 8) | (cmd[1] & 0xFC);
        int16_t tmp2 = (cmd[0] << 8) | cmd[1];
        printf("cmd[0] = 0x%02X, cmd[1] = 0x%02X\n", cmd[0], cmd[1]);

        reg_pres = 0xF8;
        i2c.write(addr8bit_pres, &reg_pres, 1); // Commencer par une écriture. Valeur du registre que l'on veut lire.
        i2c.read(addr8bit_pres, cmd, 2);
        int16_t tmp1 = (cmd[0] << 8) | (cmd[1] & 0xFC);
        printf("cmd[0] = 0x%02X, cmd[1] = 0x%02X\n", cmd[0], cmd[1]);

        reg_pres = 0xF9;
        i2c.write(addr8bit_pres, &reg_pres, 1); // Commencer par une écriture. Valeur du registre que l'on veut lire.
        i2c.read(addr8bit_pres, cmd, 2);
        int16_t tmp0 = (cmd[0] << 8) | (cmd[1] & 0xFC);

        int pression_final = (tmp2 << 16) + (tmp1 << 8) + tmp0 - pow(2, 23);

        printf("Pression = %d kPa\n", pression_final);

        printf("cmd[0] = 0x%02X, cmd[1] = 0x%02X\n", cmd[0], cmd[1]);
        //  printf("cmd[0] = 0x%02X\n", cmd[0]);*/