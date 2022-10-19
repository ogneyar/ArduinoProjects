//
// Created by panukov.a on 17.03.2021.
//

#ifndef USE_INIT_H
#define USE_INIT_H

#include <MLDR187.h>
#include <MLDR187_gpio.h>
#include <stdbool.h>

void init_clock();

void init_uart();

void init_bkp();

void init_interrupts();

void init_leds();
void toggle_led(int i);
void set_led(int i, BitStatus state);


#endif //USE_INIT_H

