#ifndef CD4024_H_
#define CD4024_H_

#include "main.h"

#define PIN_CONTROL		PB4// пин управления счетчиком

void cd4024_ini(void);

void cd4024_clear(void);
void cd4024_set(uint8_t n);

#endif 