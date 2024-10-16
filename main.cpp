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

void flip()
{
    led = !led;
}


int main()
{
button.rise(&flip);

    while (true) 
    {
        printf("Test 1, 2. Test\n");
        printf("Etat du bouton : %d \n", button.read());

        // led = button;
        
        t.start();
        printf("Hello World!\n");
        t.stop();
        printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());

        ThisThread::sleep_for(BLINKING_RATE);
    }


    
}
