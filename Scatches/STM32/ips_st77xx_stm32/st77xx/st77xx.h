//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _ST77XX_H
#define _ST77XX_H

#include <types.h>


// ������������ SPI (SPI1, SPI2)
#define ST77xx_SPI_periph       SPI1
#define ST77xx_RESET_Used       1       // ������������ ����� RESET �������
#define ST77xx_CS_Used          0       // ������������ ����� CS �������. ����� ���������� � 0 ���� ������� ���� � �� CS ���. 1
#define ST77xx_DC_Used          1       // ������������ ����� DC (Data/Command) �������. 0 ���� ������������ 3-��������� ����� ����������� �� SPI
#define ST77xx_BLK_PWM_Used     1       // ������������ ������� ���������� �������� ��������� ��������� ��� (����� ���������� ���������� - ���/����)

//==============================================================================
// ��������� ����������� � ���������� �������
//==============================================================================
// ������ RESET
#if (ST77xx_RESET_Used)
  #define ST77xx_RESET_Port     GPIOA
  #define ST77xx_RESET_Pin      GPIO_Pin_3
#endif
// ������ CS
#if (ST77xx_CS_Used)
  #define ST77xx_CS_Port        GPIOB
  #define ST77xx_CS_Pin         GPIO_Pin_10
#endif
// ������ DC
#if (ST77xx_DC_Used)
  #define ST77xx_DC_Port        GPIOA
  #define ST77xx_DC_Pin         GPIO_Pin_2
#endif

#if (ST77xx_BLK_PWM_Used)
// ������������ 1 ����� ������� 2 ��� ���������� � ������� ���
  #define ST77xx_PWM_TMR2_Chan  1       // ����� ������ (1-4) ������� 2, ������������ ��� ���
#else
  // ������ BLK (��� ���������� ����������)
  #define ST77xx_BLK_Port       GPIOA
  #define ST77xx_BLK_Pin        GPIO_Pin_1
#endif
//==============================================================================


// ����� ������
//#define ST7735_Cmd_NOP          0x00
#define ST77xx_Cmd_SWRESET      0x01
//#define ST7735_Cmd_RDDID        0x04
//#define ST7735_Cmd_RDDST        0x09
#define ST77xx_Cmd_SLPIN        0x10
#define ST77xx_Cmd_SLPOUT       0x11
#define ST77xx_Cmd_PTLON        0x12
#define ST77xx_Cmd_NORON        0x13
#define ST77xx_Cmd_INVOFF       0x20
#define ST77xx_Cmd_INVON        0x21
#define ST77xx_Cmd_GAMSET       0x26
#define ST77xx_Cmd_DISPOFF      0x28
#define ST77xx_Cmd_DISPON       0x29
#define ST77xx_Cmd_CASET        0x2A
#define ST77xx_Cmd_RASET        0x2B
#define ST77xx_Cmd_RAMWR        0x2C
//#define ST7735_Cmd_RAMRD        0x2E
#define ST77xx_Cmd_PTLAR        0x30
#define ST77xx_Cmd_COLMOD       0x3A
#define ST77xx_Cmd_MADCTL       0x36    // Memory data access control 

#define ST7735_Cmd_FRMCTR1      0xB1    // Frame Rate Control in normal mode
#define ST7735_Cmd_FRMCTR2      0xB2    // Frame Rate Control in idle mode
#define ST7735_Cmd_FRMCTR3      0xB3    // Frame Rate Control in partial mode
#define ST7735_Cmd_INVCTR       0xB4
#define ST7735_Cmd_DISSET5      0xB6    // Display Function set 5 
#define ST7735_Cmd_PWCTR1       0xC0    // Power control 1 
#define ST7735_Cmd_PWCTR2       0xC1    // Power control 2 
#define ST7735_Cmd_PWCTR3       0xC2    // Power control 3 
#define ST7735_Cmd_PWCTR4       0xC3    // Power control 4 
#define ST7735_Cmd_PWCTR5       0xC4    // Power control 5 
#define ST7735_Cmd_VMCTR1       0xC5    // VCOM Control 1

#define ST7789_Cmd_MADCTL_MY    0x80
#define ST7789_Cmd_MADCTL_MX    0x40
#define ST7789_Cmd_MADCTL_MV    0x20
#define ST7789_Cmd_MADCTL_ML    0x10
#define ST7789_Cmd_MADCTL_RGB   0x00

#define ST7789_Cmd_RDID1        0xDA
#define ST7789_Cmd_RDID2        0xDB
#define ST7789_Cmd_RDID3        0xDC
#define ST7789_Cmd_RDID4        0xDD
//==============================================================================
#define ST7735_ColorMode_12bit  0x03
#define ST7735_ColorMode_16bit  0x05
#define ST7735_ColorMode_18bit  0x06

#define ST77xx_MADCTL_MY        0x80
#define ST77xx_MADCTL_MX        0x40
#define ST77xx_MADCTL_MV        0x20
#define ST77xx_MADCTL_ML        0x10
#define ST77xx_MADCTL_BGR       0x08
#define ST77xx_MADCTL_MH        0x04



extern uint8_t ST77xx_Width, ST77xx_Height;
extern uint8_t ST77xx_X_Start, ST77xx_Y_Start;

// ��������� ��������� ����� ���������������� ��� ������ � ST77xx
void ST77xx_GPIO_init(void);
// ��������� �������� ������� � �������
void ST77xx_SendCmd(uint8_t Cmd);
// ��������� �������� ������ (����������) � �������
void ST77xx_SendData(uint8_t Data);
// ��������� ����������� ������ ������� (������ RESET)
void ST77xx_HardReset(void);
// ��������� ������������ ������ �������
void ST77xx_SoftReset(void);
// ��������� ���������/���������� ������ ���
void ST77xx_SleepMode(uint8_t Mode);
// ��������� ���������/���������� ������ ���������� ���������� ������
void ST77xx_InversionMode(uint8_t Mode);
// ��������� ���������/���������� ������� �������
void ST77xx_DisplayPower(uint8_t On);
// ��������� ������ ������ �����-���������
void ST77xx_GammaSet(uint8_t CurveNum);
// ��������� ��������� ������� �����
void ST77xx_ColorModeSet(uint8_t ColorMode);
// ��������� ��������� �����������  
void ST77xx_MemAccessModeSet(uint8_t Rotation, uint8_t VertMirror, uint8_t HorizMirror, uint8_t IsBGR);
// ��������� ���������� ���������� (��� ��������� ���)
void st77xx_SetBL(uint8_t Value);
// ��������� ��������� ������ ������ ��� ����������
void ST77xx_SetWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
// ��������� ����������� ����� ������ color
void ST77xx_FillScreen(uint16_t color);
// ��������� ���������� 1 ������� �������
void ST77xx_DrawPixel(int16_t x, int16_t y, uint16_t color);
// ��������� ���������� �������������� ������ color
void ST77xx_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
// ��������� ���������� ������������� ������� �� ������. ������� ���������� ������ Y - X
void ST77xx_DrawPartYX(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pBuff);
// ��������� ���������� ������������� ������� �� ������. ������� ���������� ������ X - Y
void ST77xx_DrawPartXY(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pBuff);


#endif
