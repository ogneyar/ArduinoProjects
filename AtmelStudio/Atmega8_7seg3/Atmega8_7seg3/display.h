#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "main.h"

// инициализация индикации
void display_ini(void);
// заполнения буфера символами
void display(uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3);

void display_bright(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3);

#endif 