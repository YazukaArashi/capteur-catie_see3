/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

DigitalOut led1(LED1);
DigitalOut led2(LED2);

InterruptIn button(BUTTON1);

using namespace std::chrono;
Timer t;
Ticker flipper;

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
    led2 = !led2;
}


int main()
{
    button.rise(&flip_on);
    button.fall(&flip_off);
    flipper.attach(&flip, 2.0);

    while (true) 
    {
        //printf("Test 1, 2. Test\n");
        //printf("Etat du bouton : %d \n", button.read());

        led1 = !led1;
        // if (button == 1)
        // {
        //     t.start();
        // }
        // else
        // {
        //     t.stop();
        //     printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
        //     t.reset();
        // }

        ThisThread::sleep_for(BLINKING_RATE);
    }
    
}
