/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <math.h>
// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

I2C i2c(P1_I2C_SDA, P1_I2C_SCL);

const int addr7bit = 0x40;      // 7 bit I2C address
const int addr8bit = 0x40 << 1; // 8bit I2C address, 0x90

int main()
{
    char cmd[2] = {0};
    char reg_add = 0xE5;
    // char reg_add = 0x00;

    while (1) 
    {

        i2c.write(addr8bit, &reg_add, 1); //Commencer par une écriture. Valeur du registre que l'on veut lire. 
        //ThisThread::sleep_for(50ms); //Tempo pour séparer les 2 requêtes. Nécessaire pour le start and stop.
        i2c.read(addr8bit, cmd, 2); 
        
        int16_t tmp = (cmd[0] << 8) | (cmd[1] & 0xFC);
        //int tmp_final = tmp /128;
        int humidity_final = -6 + (125 * tmp / pow(2, 16));
        printf("Humidite = %d %\n", humidity_final);
        //printf("cmd[0] = 0x%02X, cmd[1] = 0x%02X\n", cmd[0], cmd[1]);
        //printf("cmd[0] = 0x%02X\n", cmd[0]);
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
