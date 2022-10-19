#ifndef USE_INIT_H
#define USE_INIT_H

#include <MLDR187_lib.h>

void init_clock();

void init_interrupts();

void init_leds();
void toggle_led(int i);
void set_led(int i, BitStatus state);

#endif //USE_INIT_H

