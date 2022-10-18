#ifndef CONFIG_H_
#define CONFIG_H_
// ����� ��������� �.�. �� ���������. HB: FF, LB: 6A 
#define F_CPU 1200000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

//------------- ��������� UART ----------------------------
#define uart_DDR    DDRB
#define uart_PORT    PORTB
#define uart_PIN PB3 // PB3 � RXD
#define uart_delay  31 //  ��� ������� ������ 1.2 Mhz : 31 - 4800 ���, 62 - 2400 ���, 124 -1200 ���, 248 - 600 ���
//------------------------------------------------------------

//-------------- ��������� �� ------------------------
#define IR_DDR    DDRB
#define IR_PORT    PORTB
#define IR_PIN		PINB
#define IR PB4 // PB4 � ���������
//-----------------------------------------------------

#endif /* CONFIG_H_ */