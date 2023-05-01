#ifndef MONITOR_H_
#define MONITOR_H_

#include "main.h"

// 8 бит в пакете, бит четности - нет, 1 стоп бит. битрейт 9600
void uart_ini(void);

// отправка строки в порт
void uart_send_str(char* str);


void uart_send_int(int16_t n);
void uart_send_float(float);

#endif 