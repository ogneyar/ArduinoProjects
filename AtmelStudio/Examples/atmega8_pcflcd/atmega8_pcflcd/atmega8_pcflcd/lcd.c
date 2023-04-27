#include "lcd.h"

#define E		2
#define RS		0

void write(uint8_t n){
	n|=(1<<E);
	pcf_write(n);
	n&=~(1<<E);
	pcf_write(n);
}


void send_byte(uint8_t byte, uint8_t tip){
	uint8_t data=0;
	if(tip) data|=(1<<RS); // ���� ��� ������ - �� ����� RS 1
	
	write(data|(byte&0xF0));// �������� �������� ���������
	write(data|(byte<<4));// �������� �������� ���������
}

// �������� ����� ��������
void mychar(void){
	
	// ������ � ����� ���������
	uint8_t simvol[16]={
		//  ������ 1
		0x04,
		0x0E,
		0x04,
		0x1F,
		0x04,
		0x0A,
		0x11,
		0x00,
		// ������ 2
		0x04,
		0x0E,
		0x15,
		0x0E,
		0x04,
		0x0A,
		0x0A,
		0x00
	};
	send_byte(64,0); // ������� � ������ 0 CGRAM ������
	
	// ��������� ������ � ��������� � ������ CGRAM
	for (uint8_t i=0; i<16; i++)
	{
		send_byte(simvol[i], 1);
	}
	
	// ������� ������� � ����� ������
	lcd_pos(0,0);
}


void lcd_ini(void){
	
	//----------- ���������� �������� ������������----------------
	
	_delay_ms(40);// ���� 40 �� ������������ �������

	write(3<<4);
	_delay_ms(5);
	write(3<<4);
	_delay_us(150);
	write(3<<4);
	_delay_us(50);// ����������� ����� ���������� �������
	write(2<<4);
	_delay_us(50);// ����������� ����� ���������� �������
	
	// ---------------------- ����� ��------------------------------
	
	// -----------������� �������������--------------------
	
	send_byte(40,0);// ������� Function Set 001_DL_N_F_X_X
	// DL 0/1 -4bit/8bit
	// N 0/1 -1/2 ������
	// F 0/1 -5x7/5x11 �����
	_delay_us(50);

	send_byte(12,0);// ������� DISPLAY SWITCH 00001_D_C_B
	// D 0/1 - off/on display
	// C 0/1 - off/on cursor
	// B 0/1 - off/on blink
	
	_delay_us(50);
	
	send_byte(1,0);// ������� ������� ������� (��� ����������)
	_delay_ms(2);
	
	send_byte(6,0);// ������� INPUT SET 000001_ID_S
	// ID 0/1 ����� �����/������
	// S 0/1 shift
	_delay_us(50);
	
	//--------------- ������� �� ------------------------------------
	
	
	mychar();// �������� ����� ��������

	//---------------����� ��������� ----------------------------------
	lcd_str("count=");
	lcd_pos(1,2);
	lcd_str("HOLa Amigos!");
	// -----------����� ��----------------------------------------------
}


// ����� ������ �� ���������
void lcd_str(char* str){
	uint8_t n=0;// ������� 
	while(str[n])// ���� �-��� ������ �� 0 �������� ����
	{
		send_byte(str[n],1);// ������� �-��� �������� ���������
		n++;// ������ ����� ������� 
	}
}

// ����� �������� ������ ����� ������ (������� �������)
void lcd_pos(uint8_t line, uint8_t pos){
	uint8_t adress=(line*0x40+pos)|0x80;// ��������� ����� � �������� �������� � ��� �������
	send_byte(adress,0);// �������� �������
	_delay_us(50);
}

// ����� 8 ������� �������� �� ���������
void lcd_num(uint8_t num, uint8_t line, uint8_t pos) {
	char buf[4];// ����� �� 4 �������
	
	utoa(num, buf, 10);// ����������� �������� num � ������ � ������� buf
	lcd_pos(line, pos);// ����� ������� ������� 
	lcd_str("   ");// �������� ��� ���������� ���������
	lcd_pos(line, pos);//  ����� ������� ������� 
	lcd_str(buf);// ������� ������
}

// ��������
void lcd_animation(void){
	static uint8_t status;
	lcd_pos(1,15);
	
	if (status)
	{
		send_byte(0,1);//  ������ � ����� 0
		status=0;
	} 
	else
	{
		send_byte(1,1);// ������ � ����� 1
		status=1;
	}
}