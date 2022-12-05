#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#include "ssd1306.h"
#include "font.h"
#include "twi_driver.h"

uint8_t scr_buffer[0]; // ����� �������

// ������ ������ �������������
const uint8_t init[] PROGMEM =
{
0xAE, // ��������� �������

0xD5, // ��������� ������� ���������� �������
0x80, 
///+----- �������� 0-F/ 0 - ������� �� 1
//+------ ������� ����������. �� �������� 0x80
0xA8, // ���������� multiplex ratio
0x1F, // 1/64 duty (�������� �� ���������), 0x1F - 128x32, 0x3F - 128x64

0xD3, // �������� ������� (offset)
0x00, // ��� ��������

0x40, // ������ ������ ������ �������� 0x40 � ������ RAM

0x8D, // ���������� ��������� ����������������
0x14, // 0x10 - ��������� (VCC �������� �����) 0x14 - ��������� ��������� DC/DC

0x20, // ����� �������������� ���������
0x00, // 0-�� ����������� � ��������� �� ����� �������� (������)
      // 1 - �� ��������� � ��������� �� ����� ������
      // 2 - ������ �� ��������� �������� ��� �������� 

0xA1, // ����� �������� �� �������� (�� X)
      // A1 - ���������� ����� (�����/�������) A0 - �������� (������/������)

0xC8, // ����� ������������ ��� �������
      // ��� ��������� ������� ���������
      // �0 - �����/���� (������ ������ ����� ����)
      // �8 - ������/���� (������ ������ ����� ����)
0xDA, // ���������� ������������ COM
0x02, // 0x02 - 128x32, 0x12 - 128x64

0x81, // ��������� ������� �������
0x8F, // 0x8F..0xCF

0xD9, // ��������� ��� DC/DC ��������������
0xF1, // 0x22 - VCC �������� ����� / 0xF1 ��� ����������

0xDB, // ��������� ������ VcomH
0x40, // ������ �� ������� ������� 0x00..0x70

0xA4, // ����� ����������

0xA6, // 0xA6 - ��� ��������, 0xA7 - �������� �������

0xAF  // ������� �������
};

// ������� ������������� �������
void display_init(void)
{
// �������� ������� � ������� �� ������� �������������
for(uint8_t i = 0; i < sizeof init; i++) disp_write(0, pgm_read_byte(&init[i]));

}

// ������� ������ ������/������� � �������
void disp_write(uint8_t mode, uint8_t data) // �����: 1-������, 0-�������
{
uint8_t m;
if(mode) m = 0x40; // ����� ������
else m = 0x00; // ����� �������

Send_start();			//send start strings
Send_byte(OWN_ADR);		//Slave address
Send_byte(m);		//Control Byte - Command
Send_byte(data);		//payload
Send_stop();
}

// ������� ������� ������ �������
void screen_clear(void)
{
for(uint16_t i = 0; i < 512; i++) scr_buffer[i] = 0;
}

// ������� ���������� �������
void screen_update(void)
{
disp_write(0,0x21); // ��������� �������
disp_write(0,0);    // ��������� �����
disp_write(0,127);  // �������� �����

disp_write(0,0x22); // ��������� ������
disp_write(0,0);    // ��������� �����
disp_write(0,3);    // �������� �����
// ������ ������ �� ������ � �������
for(uint16_t i = 0; i < 512; i++) disp_write(1, scr_buffer[i]);
}

// ������� ������ ������� 5x8
void print_char_5x8(uint8_t column, uint8_t string, uint8_t sign) // 0..120 / 0..7 / ������
{
if(column <= 120 && string < 3)
  {
  if((sign >= 0x20) && (sign <= 0x7F))
  sign -= 32;// �������� � ������� ��� �������� ASCII[0x20-0x7F]
  else if (sign >= 0xC0)
  sign -= 96; // �������� � ������� ��� �������� CP1251[0xC0-0xFF]
  else  sign = 85; // ��������� ���������� (�� ������ ��� � ������� ��� �������� ������)
  
  for(uint8_t i = 0; i < 5; i++)
	{
	scr_buffer[128*string + column + i] = pgm_read_byte(&font_5x8[5*sign + i]);
	}
  }
}

// ������� ������ ������ 5x8
void print_string_5x8(uint8_t column, uint8_t string, char *str) // 0..120 / 0..7 / ������
{
while(*str)
	{
	print_char_5x8(column, string, *str++);
	column+=6;
	}
}


