//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _DISP1COLOR_H
#define _DISP1COLOR_H

#include <types.h>

// ������ �������������� �������� (������������ ��������)
#define DISPTYPE_ssd1306        0       // OLED-������� � ������������ ssd1306


// � ����� ����� ������� ����� �������� ������ disp1color 
#define DISP1COLOR_type         DISPTYPE_ssd1306

// ������� ������� � ��������
#define DISP1COLOR_Width        128
#define DISP1COLOR_Height       64


// ��������� �������������� 1-������ �������
void disp1color_Init(void);
// ��������� ��������� ������� Test �������
void disp1color_TestMode(uint8_t TestOn);
// ��������� ������������� ������� �������
void disp1color_SetBrightness(uint8_t Value);
// ��������� ��������� ����� ����� ��������� FillValue
void disp1color_FillScreenbuff(uint8_t FillValue);
// ��������� ��������� ��������� ����������� � ������������ � ������� �����
void disp1color_UpdateFromBuff(void);

// ��������� ������ ������ ����� � ������ ����� �������
void disp1color_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
// ��������� ������ ������������� � ������ ����� �������
void disp1color_DrawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
// ��������� ������ ���������� � ������ ����� �������. x0 � y0 - ���������� ������ ����������
void disp1color_DrawCircle(int16_t x0, int16_t y0, int16_t radius);

// ������� ������ ������� Char �� �������. ���������� ������ ����������� �������
uint8_t disp1color_DrawChar(uint8_t X, uint8_t Y, uint8_t FontID, uint8_t Char);
// ������� ������ ������ �� ������ Str �� �������
void disp1color_DrawString(uint8_t X, uint8_t Y, uint8_t FontID, uint8_t *Str);
// ��������� ������� �� ������� ��������������� ������
void disp1color_printf(uint8_t X, uint8_t Y, uint8_t FontID, const char *args, ...);

#endif