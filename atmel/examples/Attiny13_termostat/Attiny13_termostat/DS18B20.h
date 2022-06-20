#ifndef DS18B20_H_
#define DS18B20_H_

#include "main.h"

//------------- ��������� ����������� ������� ds18b20 ----------
#define PORTTEMP PORTB
#define DDRTEMP DDRB
#define PINTEMP PINB
#define BITTEMP PB3 // ����� PB3
//------------------------------------------------------------------

#define NOID 0xCC //���������� �������������
#define T_CONVERT 0x44 //��� ��������� �����������
#define READ_DATA 0xBE //�������� ������ ��������
#define SEND_DATA 0x4e

unsigned int dt_check(void); //������ ������ ������� � ����������
char converttemp (unsigned int tt); //�������������� ����������� � �������
unsigned char dt_convert(unsigned int tt);
void DT_init12(void);

#endif /* DS18B20_H_ */