#ifndef REG595_H_
#define REG595_H_

#include "main.h"
// ���������� ��������� � �����
#define REG_NUM			3

// SH_CP ����� ������������
#define TAKT			PB0
#define TAKT_PORT		PORTB
#define TAKT_DDR		DDRB

// DS ����� ������
#define DATA			PB1
#define DATA_PORT		PORTB
#define DATA_DDR		DDRB

// ST_CP ����� �������
#define ENTER			PB2
#define ENTER_PORT		PORTB
#define ENTER_DDR		DDRB


void reg595_ini(void);// ������������� �����
void reg595_send_byte(uint8_t byte); // ���������� ������ ��������
void reg595_send(uint8_t* array);// �������� ������ � ������ ��������� ���������

#endif