/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

DigitalOut led(LED1);

InterruptIn button(BUTTON1);

using namespace std::chrono;
Timer t;

void flip_on()
{
    led = 1;
}

void flip_off()
{
    led = 0;
}


int main()
{
    button.rise(&flip_on);
    button.fall(&flip_off);

    while (true) 
    {
        printf("Test 1, 2. Test\n");
        printf("Etat du bouton : %d \n", button.read());

        //led = button;
        if (button == 1)
        {
            t.start();
        }
        else
        {
            t.stop();
            printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
            t.reset();
        }

        ThisThread::sleep_for(BLINKING_RATE);
    }
    
}
