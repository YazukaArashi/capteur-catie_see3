/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <math.h>
#include <thread>
// Blinking rate in milliseconds
#define BLINKING_RATE 500ms
#define BLINKING_FUNC 700ms

DigitalOut led1(LED1);
Mutex stdio_mutex;
Thread t1(osPriorityNormal, 1024);
Thread t2(osPriorityNormal, 1024);

void ping()
{
    for (int i = 0; i < 100; i++)
    {
        stdio_mutex.lock();
        printf("Ping %d\n", i + 1);
        stdio_mutex.unlock();
    }
}

void pong()
{
    for (int j = 0; j < 100; j++)
    {
        stdio_mutex.lock();
        printf("Pong %d\n", j + 1);
        stdio_mutex.unlock();
    }
}

int main()
{

    t1.start(pong);
    t2.start(ping);

    while (1)
    {

        led1 = !led1;
        // printf("Alive!\n");
        ThisThread::sleep_for(BLINKING_RATE);
    }
}