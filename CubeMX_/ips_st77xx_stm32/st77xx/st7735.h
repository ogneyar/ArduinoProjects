//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _ST7735_H
#define _ST7735_H

#include <types.h>

// ������� ����� ��������� ��������� ST7789
#define ST7735_ColorMode_12bit  0x03
#define ST7735_ColorMode_16bit  0x05
#define ST7735_ColorMode_18bit  0x06

// �������� ������� ������������ �����/�������� �����������
#define ST7735_X_Start          26
#define ST7735_Y_Start          1


// ��������� ������������� �������
void ST7735_Init(uint8_t Width, uint8_t Height);


#endif
