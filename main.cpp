/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <math.h>
// Blinking rate in milliseconds
#define BLINKING_RATE 500ms

I2C i2c(P1_I2C_SDA, P1_I2C_SCL);

const int addr8bit_hum = 0x40 << 1; // 8bit I2C address, 0x90
const int addr8bit_pres = 0x70 << 1;

int recup_humidity()
{
    char cmd[2] = {0};
    char reg_hum = 0xE5;
    i2c.write(addr8bit_hum, &reg_hum, 1);               // Commencer par une écriture. Valeur du registre que l'on veut lire.
    i2c.read(addr8bit_hum, cmd, 2);                     // Lecture des valeur à l'adresse du registre 0xE5
    int16_t tmp = (cmd[0] << 8) | (cmd[1] & 0xFC);      // Concaténation des 2 cases du tableau pour récupérer la pression
    int humidity_final = -6 + (125 * tmp / pow(2, 16)); // Calcul de l'humidité avec la formule de la datasheet
    return humidity_final;
}

int recup_temperature()
{
    char cmd[2] = {0};
    char reg_temp = 0xE3;
    i2c.write(addr8bit_hum, &reg_temp, 1);                 // Commencer par une écriture. Valeur du registre que l'on veut lire.
    i2c.read(addr8bit_hum, cmd, 2);                        // Lecture des valeur à l'adresse du registre 0xE3
    int16_t tmp = (cmd[0] << 8) | (cmd[1] & 0xFC);         // Concaténation des 2 cases du tableau pour récupérer la température
    int temp_final = -46.85 + (175.72 * tmp / pow(2, 16)); // Calcul de la température avec la formule de la datasheet
    return temp_final;
}

int main()
{

    /*char cmd[2] = {0};
    char reg_pres = 0xF7;
    char reg_temp_wpres = 0xFA;*/

    while (1)
    {


        int humidity = recup_humidity();
        int temperature = recup_temperature();

        printf("Humidite = %d %\n", humidity);
        printf("Temperature = %d degre C\n", temperature);
        
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
        printf("cmd[0] = 0x%02X, cmd[1] = 0x%02X\n", cmd[0], cmd[1]);*/


        /*i2c.write(addr8bit_pres, &reg_pres, 1); // Commencer par une écriture. Valeur du registre que l'on veut lire.
        i2c.read(addr8bit_pres, cmd, 2);
        //int16_t tmp2 = (cmd[0] << 8) | (cmd[1] & 0xFC);
        int16_t tmp2 = (cmd[0] << 8) | cmd[1] ;
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

        printf("cmd[0] = 0x%02X, cmd[1] = 0x%02X\n", cmd[0], cmd[1]);*/
        //  printf("cmd[0] = 0x%02X\n", cmd[0]);
