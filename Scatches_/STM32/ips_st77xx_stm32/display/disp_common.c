//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#include <dispcolor.h>
#include <font.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#if (DISPCOLOR_type == DISPTYPE_st7789)
  #include <st77xx.h>
  #include <st7789.h>
#elif (DISPCOLOR_type == DISPTYPE_st7735)
  #include <st77xx.h>
  #include <st7735.h>
#else
  #error ������ c ��������� ����� ������� �� ��������������, ���������� �������� ������ disp1color
#endif


//==============================================================================
// ��������� �������������� ������� �������
//==============================================================================
void disp_Init(uint8_t Width, uint8_t Height)
{
#if (DISPCOLOR_type == DISPTYPE_st7789)
  // ������������� �������
  ST7789_Init(Width, Height);
#elif (DISPCOLOR_type == DISPTYPE_st7735)
  // ������������� �������
  ST7735_Init(Width, Height);
#endif
}
//==============================================================================


//==============================================================================
// ��������� ������������� ������� �������
//==============================================================================
void disp_SetBrightness(uint8_t Value)
{
#if (DISPCOLOR_type == DISPTYPE_st7789)
  st77xx_SetBL(Value);
#elif (DISPCOLOR_type == DISPTYPE_st7735)
  st77xx_SetBL(Value);
#endif
}
//==============================================================================


//==============================================================================
// ��������� ����������� ����� ������ color
//==============================================================================
void disp_FillScreen(uint16_t color)
{
#if (DISPCOLOR_type == DISPTYPE_st7789)
  ST77xx_FillScreen(color);
#elif (DISPCOLOR_type == DISPTYPE_st7735)
  ST77xx_FillScreen(color);
#endif
}
//==============================================================================


//==============================================================================
// ��������� ���������� 1 ������� �������
//==============================================================================
void disp_DrawPixel(int16_t x, int16_t y, uint16_t color)
{
#if (DISPCOLOR_type == DISPTYPE_st7789)
  ST77xx_DrawPixel(x, y, color);
#elif (DISPCOLOR_type == DISPTYPE_st7735)
  ST77xx_DrawPixel(x, y, color);
#endif
}
//==============================================================================


//==============================================================================
// ��������� ���������� �������������� ������ color
//==============================================================================
void disp_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
#if (DISPCOLOR_type == DISPTYPE_st7789)
  ST77xx_FillRect(x, y, w, h, color);
#elif (DISPCOLOR_type == DISPTYPE_st7735)
  ST77xx_FillRect(x, y, w, h, color);
#endif
}
//==============================================================================


//==============================================================================
// ��������� ���������� ������������� ������� �� ������ (������� ���������� ������� Y, X
//==============================================================================
void disp_DrawPartYX(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pBuff)
{
#if (DISPCOLOR_type == DISPTYPE_st7789)
  ST77xx_DrawPartYX(x, y, w, h, pBuff);
#elif (DISPCOLOR_type == DISPTYPE_st7735)
  ST77xx_DrawPartYX(x, y, w, h, pBuff);
#endif
}
//==============================================================================


//==============================================================================
// ��������� ���������� ������������� ������� �� ������ (������� ���������� ������� X, Y
//==============================================================================
void disp_DrawPartXY(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pBuff)
{
#if (DISPCOLOR_type == DISPTYPE_st7789)
  ST77xx_DrawPartXY(x, y, w, h, pBuff);
#elif (DISPCOLOR_type == DISPTYPE_st7735)
  ST77xx_DrawPartXY(x, y, w, h, pBuff);
#endif
}
//==============================================================================
