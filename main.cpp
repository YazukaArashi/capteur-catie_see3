/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     100ms

DigitalOut led1(LED1);
DigitalOut led2(LED2);

InterruptIn button(BUTTON1);

using namespace std::chrono;
Timer t;
Ticker flipper;
int cpt = 0, counter = 2;

void flip_on()
{
    led1 = 1;
}

void flip_off()
{
    led1 = 0;
}

void flip()
{
    cpt = cpt + 1;
    if (cpt == counter)
    {
        led2 = !led2; //toggle la led si le compteur et la fréquence sont les mêmes.
        cpt = 0; //remise à zéro du compteur. 
    }
}

void change_freq()
{
    counter = counter + 1; //diminution de la fréquence de clignottement.  
}

int main()
{
    button.rise(&change_freq);
    //button.fall(&flip_off);
    flipper.attach(&flip, 100ms);

    while (true) 
    {
        led1 = !led1;
        printf("Temps de fréquence de la led 2 : %d x plus que la led 1.\n", counter);


        ThisThread::sleep_for(BLINKING_RATE);
    }
    
}
