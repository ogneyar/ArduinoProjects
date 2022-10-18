#include "IR.h"

void IR_init() {
		IR_DDR &= ~(1<<IR_PIN);
		IR_PORT &= ~(1<<IR_PIN);
}

unsigned int IR_read() {
	
	unsigned char time_IR; // ���������� �������� ������� ����
	bool IR_bit; // ���������� ��� ���������� ����
	unsigned int IR_block=0; // ���������� ��� �������� ����� ��������� �����.
	for ( char i=0; i<15; i++) {
		
		time_IR=0;            // �������� �������
		while(!(IR_PIN & 1<<IR)) { //���� ���� ���� ����������� � 1
			_delay_us(1);
			
		}
		while ((IR_PIN & 1<<IR)) { // ���� ���� 1 ����������� ������� �� 1, ������ 10 ���
			
			_delay_us(10);
			time_IR++;
			if (time_IR>250) break; // ���� ������� ����� 1680	��� ������ �������� ����� ��������
		}
		
		if (time_IR < 70) IR_bit=0; // ���� ������� ������ 70 ������ 0
		else IR_bit=1; // �����  1
		IR_block |=IR_bit<<i; // ����� ��� � ����������


	}
	return IR_block;
}