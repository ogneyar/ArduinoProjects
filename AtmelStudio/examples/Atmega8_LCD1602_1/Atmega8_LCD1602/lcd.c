#include "lcd.h"

void write(uint8_t n){
	n<<=4;// �������� �� 5 ������ ����� �������� ������ � ������� 4 ����
	E1;// ����� � � 1
	LCD_PORT&=~DATA;// ������� ���������� ��������
	LCD_PORT|=n;// ��������� �������� �� ���� ���������� ���� ������
	asm("nop");// ������� �����
	E0;// ����� � � 0
}

void send_byte(uint8_t byte, uint8_t tip){
	if(tip) RS1; // ���� ��� ������ - �� ����� RS 1
	else RS0;// ����� ��� ������� � ������� RS 0
	write(byte>>4);// �������� �������� ���������
	write(byte);// �������� �������� ���������
}

void lcd_ini(void){
	LCD_DDR|=DATA | (1<<RS) | (1<<E);
	_delay_ms(40);// ���� 40 �� ������������ �������
	RS0;// ����� RS � 0
	write(3);
	_delay_ms(5);
	write(3);
	_delay_us(150);
	write(3);
	_delay_us(50);// ����������� ����� ���������� �������
	write(2);
	_delay_us(50);// ����������� ����� ���������� �������
	
	send_byte(40,0);// ������� Function Set 001_DL_N_F_X_X
	_delay_us(50);

	send_byte(15,0);// ������� DISPLAY SWITCH 00001_D_C_B
	_delay_us(50);
	
	send_byte(1,0);// ������� ������� ������� (��� ����������)
	_delay_ms(2);
	
	send_byte(6,0);// ������� INPUT SET 000001_ID_S
	_delay_us(50);
}


