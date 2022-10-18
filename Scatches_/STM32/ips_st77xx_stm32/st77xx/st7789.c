//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <delay.h>
#include <dispcolor.h>
#include <st77xx.h>
#include <st7789.h>
#include <gpio.h>
#include <spim.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>



//==============================================================================
// ��������� ������������� �������
//==============================================================================
void ST7789_Init(uint8_t Width, uint8_t Height)
{
  ST77xx_Width = Width;
  ST77xx_Height = Height;
  ST77xx_X_Start = ST7789_X_Start;
  ST77xx_Y_Start = ST7789_Y_Start;

  // ������������� ����� ���������� ���������� ��������
  ST77xx_GPIO_init();
  // ������������� ���������� SPI
  spim_init(ST77xx_SPI_periph, 1, 8);
  
  // �������� ����� ������ �������
  delay_ms(40);
  
  // ����� �������
  ST77xx_HardReset();
  // ���������� ������������������ ���������������� ������
  ST77xx_SoftReset();

  ST77xx_SleepMode(0);

  ST77xx_ColorModeSet(ST7789_ColorMode_65K | ST7789_ColorMode_16bit);
  delay_ms(10);
  ST77xx_MemAccessModeSet(4, 1, 1, 0);
  delay_ms(10);
  ST77xx_InversionMode(1);
  delay_ms(10);

  ST77xx_FillScreen(0);
  
  // �������� ���������
  st77xx_SetBL(100);

  ST77xx_DisplayPower(1);
  delay_ms(100);
}
//==============================================================================
