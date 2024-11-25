/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "CapteurHumiditeTemperature.h"
#include "CapteurI2C.h"

// Blinking rate in milliseconds
#define BLINKING_RATE 500ms

int main()
{
    I2C i2c(P1_I2C_SDA, P1_I2C_SCL); // Crée une instance d'I2C
    CapteurHumiditeTemperature capteurHT(i2c, 0x40); // Passe l'objet I2C et l'adresse

    while (true)
    {
        int humidite = capteurHT.lireHumidite();
        int temperature = capteurHT.lireTemperature();
    // CapteurPression capteurPression(i2c, 0x70); // Adresse capteur de pression

        if (humidite != -1 && temperature != -1)
        {
            printf("Humidité : %d %%\n", humidite);
            printf("Température : %d degre C\n", temperature);
        }

        // if (pression != -1)
        // {
        //     printf("Pression : %d kPa\n", pression);
        // }

        ThisThread::sleep_for(BLINKING_RATE);
    }
}

// // Classe pour le capteur de pression
// class CapteurPression : public CapteurI2C
// {
// public:
//     CapteurPression(I2C &i2c, int adresse)
//         : CapteurI2C(i2c, adresse) {}

//     int lirePression()
//     {
//         char data[2] = {0};
//         char temp[3] = {0};

//         if (!lireRegistre(0xB6, data, 2))
//         {
//             printf("Erreur lecture temperature\n");
//             return -1;
//         }
//         long int a2 = (data[0] << 8) | data[1];
//         printf("a2 = %x\n", a2);

//         if (!lireRegistre(0xB4, data, 2))
//         {
//             printf("Erreur lecture temperature\n");
//             return -1;
//         }
//         long int a1 = (data[0] << 8) | data[1];
//         printf("a1 = %x\n", a1);

//         if (!lireRegistre(0xB2, data, 2))
//         {
//             printf("Erreur lecture temperature\n");
//             return -1;
//         }
//         long int a0_temp = (data[0] << 8) | data[1];

//         if (!lireRegistre(0xB8, data, 2))
//         {
//             printf("Erreur lecture temperature\n");
//             return -1;
//         }
//         long int a0 = (a0_temp << 4) | data[1];
//         printf("a0 = %x\n", a0);
        
        
//         if (!lireRegistre(0xFA, temp, 3))
//         {
//             printf("Erreur lecture temperature\n");
//             return -1;
//         }
//         //printf("cmd[0] = 0x%02X, cmd[1] = 0x%02X\n", data[0], data[1]);

//         long int Dt = (temp[0]<< 16) | (temp[1]<< 8) | temp[2]; 
//         Dt = Dt - pow(2,23);
//         printf("temp = %d\n", Dt);


//         long int Tr = a0 + a1*Dt + a2*pow(Dt, 2);
//         printf("Tr = %d\n", Tr);

//         return 0;
//     }