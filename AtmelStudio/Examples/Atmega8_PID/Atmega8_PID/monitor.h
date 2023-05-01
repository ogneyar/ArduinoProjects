#ifndef MONITOR_H_
#define MONITOR_H_

#include "main.h"

// 8 ��� � ������, ��� �������� - ���, 1 ���� ���. ������� 9600
void uart_ini(void);

// �������� ������ � ����
void uart_send_str(char* str);


void uart_send_int(int16_t n);
void uart_send_float(float);

#endif 