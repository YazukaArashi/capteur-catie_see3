/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


int main()
{
    // Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif

    printf("Test 1, 2. Test\n");

    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
         printf("Test 1, 2. Test\n");
    }
    
}