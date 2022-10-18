//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _SSD1306_H
#define _SSD1306_H

#include <types.h>


// ��������� ������������� ������� �� ����������� ssd1306
void SSD1306_Init(uint8_t Width, uint8_t Height);
// ��������� ��������� ������� � ����� ���
void SSD1306_Sleep(void);
// ��������� ������� ������� �� ������ ���
void SSD1306_Wake(void);
// ��������� �������� �������� �������
void SSD1306_SetInverseOn(void);
// ��������� ��������� �������� �������
void SSD1306_SetInverseOff(void);
// ��������� �������� ��� ������� ������� (���� ����������)
void SSD1306_AllPixOn(void);
// ��������� ��������� ���� ������� � ������� �� ���� �������� �� ������ ����� � ssd1306
void SSD1306_AllPixRAM(void);
// ��������� ������������� �������� ������������� (0-255)
void SSD1306_SetContrast(uint8_t Value);
// ��������� ������������� ��������� � �������� ������ ������� 
// ��� ������������ ��������� � ������ ����� ��� ������ ������.
void SSD1306_SetColumns(uint8_t Start, uint8_t End);
// ��������� ������������� ��������� � �������� ������ �������� 
// ��� ������������ ��������� � ������ ����� ��� ������ ������.
void SSD1306_SetPages(uint8_t Start, uint8_t End);
// ��������� ������� � ������� ����� ����� �� ������� pBuff
void SSD1306_DisplayFullUpdate(uint8_t *pBuff, uint16_t BuffLen);

#endif
