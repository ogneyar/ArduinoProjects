#include "main.h"


//------------- ��������� ����������� ����������, �����  PB0 � PB1 (��� ��������� ����� ������ 1637.h)----------
#define _CLK PB0
#define _DIO PB1
//------------------------------------------------------------------


//------------- ������� �������� ���������� ----------
#define Bright0 0x88
#define Bright1 0x89
#define Bright2 0x8A
#define Bright3 0x8B
#define Bright4 0x8C
#define Bright5 0x8D
#define Bright6 0x8E
#define Bright7 0x8F
#define SetBright Bright5 //���� ��������� ������� �� 0 �� 7
//------------------------------------------------------------------


void indication(uint16_t n, uint8_t znak);
void write(uint8_t n3, uint8_t n2, uint8_t n1, uint8_t n0);
void start(void);
void stop(void);
void writeValue(uint8_t value);
