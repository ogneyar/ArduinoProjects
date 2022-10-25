#ifndef TM1637_H_
#define TM1637_H_

#include "main.h"

//------------- ��������� ����������� ����������--------------------
#define CLK				PB3
#define DDR_CLK			DDRB
#define PORT_CLK		PORTB

#define DIO				PB4
#define DDR_DIO			DDRB
#define PORT_DIO		PORTB
//------------------------------------------------------------------

//------------- ������� ���������� ----------
#define Bright0 0x88
#define Bright1 0x89
#define Bright2 0x8A
#define Bright3 0x8B
#define Bright4 0x8C
#define Bright5 0x8D
#define Bright6 0x8E
#define Bright7 0x8F
#define SetBright Bright7 //���� ��������� ������� �� 0 �� 7
//------------------------------------------------------------------

//��������� 16 ������� ��������
void tm1637_indication(uint16_t n);
//��������� 16 ������� �������� � ������
void tm1637_indication_dot(uint16_t n, uint8_t dot);

#endif