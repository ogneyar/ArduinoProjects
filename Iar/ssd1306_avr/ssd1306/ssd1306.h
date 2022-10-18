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

#define SSD1306_IfMode_Par8080                  0       // ������������ ��������� 8080 8-���
#define SSD1306_IfMode_Par6800                  1       // ������������ ��������� 6800 8-���
#define SSD1306_IfMode_SPI_3w                   2       // SPI �� 3 ������ (CS, SCLK, MOSI)
#define SSD1306_IfMode_SPI_4w                   3       // SPI �� 4 ������ (CS, SCLK, MOSI, D/C)
#define SSD1306_IfMode_I2C                      4       // I2C

// ��������� ����������� �������      
#define SSD1306_IfMode          SSD1306_IfMode_SPI_4w //SSD1306_IfMode_I2C 


// ������ ��������������� ������ ��������� � ������ ����� ssd1306
#define SSD1306_Adressing_Horizontal            0       // ������� ��������� �� �����������, ����� ��������� �� ���������
#define SSD1306_Adressing_Vertical              1       // ������� ��������� �� ���������, ����� ��������� �� �����������
#define SSD1306_Adressing_Page                  2       // ��������� ������ �� �����������

// ������� �� ������� Fundamental
#define SSD1306_CMD_SetContrast                 0x81
#define SSD1306_CMD_AllPixRAM                   0xA4
#define SSD1306_CMD_AllPixOn                    0xA5
#define SSD1306_CMD_SetInverseOff               0xA6
#define SSD1306_CMD_SetInverseOn                0xA7
#define SSD1306_CMD_Sleep                       0xAE
#define SSD1306_CMD_Wake                        0xAF

//==============================================================================
// ���� ������ �������
//==============================================================================
// ������� �� ������� Fundamental
#define SSD1306_CMD_SetContrast                 0x81
#define SSD1306_CMD_AllPixRAM                   0xA4
#define SSD1306_CMD_AllPixOn                    0xA5
#define SSD1306_CMD_SetInverseOff               0xA6
#define SSD1306_CMD_SetInverseOn                0xA7
#define SSD1306_CMD_Sleep                       0xAE
#define SSD1306_CMD_Wake                        0xAF

// ������� �� ������� Scrolling
#define SSD1306_CMD_DeactivateScroll            0x2E

// ������� �� ������� Addressing Setting
// ������� ������ ������ ���������� ��������� � ������ �����
#define SSD1306_CMD_SetMemAdressingMode         0x20    
// ������� ������ ��������� ��������� �������� � ������� ��� ���������� ��������� � ������ �����
// ����������� ��� ������� ���������� SSD1306_Adressing_Horizontal � SSD1306_Adressing_Vertical
#define SSD1306_CMD_SetColumnAddr               0x21
#define SSD1306_CMD_SetPageAddr                 0x22
// ������� ������ �������� � ��������� ��������� ������� ��� ���������� ��������� � ������ �����
// ����������� ��� ������ ���������� SSD1306_Adressing_Page
#define SSD1306_CMD_PageAddrMode_SetPage        0xB0
#define SSD1306_CMD_PageAddrMode_StartColumnLo  0x00
#define SSD1306_CMD_PageAddrMode_StartColumnHi  0x10

// ������� �� ������� Hardware Configuration
#define SSD1306_CMD_SetDisplayStartLine         0x40
#define SSD1306_CMD_SetSegmentRemap             0xA0
#define SSD1306_CMD_SetMultiplexRatio           0xA8
#define SSD1306_CMD_SetCOMoutScanDirection      0xC0 
#define SSD1306_CMD_SetDisplayOffset            0xD3
#define SSD1306_CMD_SetCOMPinsConfig            0xDA
  
// ������� �� ������� Timing & Driving Scheme Setting
#define SSD1306_CMD_SetDisplayClockDivider      0xD5
#define SSD1306_CMD_SetPrechargePeriod          0xD9
#define SSD1306_CMD_SetVCOMHDeselectLevel       0xDB

// ������� �� ������� Charge Pump
#define SSD1306_CMD_ChargePumpSetting           0x8D
//==============================================================================


//==============================================================================
// ��������� ����������� � �������
//==============================================================================
#define SSD1306_ResetPinUsed            1       // ������������ ���������� ����� Reset ssd1306      
#define SSD1306_Reset_Port              PORTB
#define SSD1306_Reset_DDR               DDRB
#define SSD1306_Reset_Mask              (1 << 0)

#if (SSD1306_IfMode == SSD1306_IfMode_I2C)       // ��������� ������ �� I2C
  // i2c-����� ����������� �������. ������� �� ��������� ����� SA0 (��� �� D/C). 0x3C ��� 0x3D
  #define SSD1306_I2C_addr              0x3C //0x3D;   // 7-������ i2c-����� ����������� ������� ssd1306      
  #define SSD1306_I2C_clock             100000  // ������� ������ I2C        
#elif (SSD1306_IfMode == SSD1306_IfMode_SPI_4w)       // ��������� ������ �� SPI-4w
  #define SSD1306_CSPinUsed             0       // ������������ ���������� ����� CS ssd1306      
  #define SSD1306_CS_Port               PORTD
  #define SSD1306_CS_DDR                DDRD
  #define SSD1306_CS_Mask               (1 << 7)
  #define SSD1306_DC_Port               PORTB
  #define SSD1306_DC_DDR                DDRB
  #define SSD1306_DC_Mask               (1 << 1)
#else
  #error ������ �� ���������� ���������� ��� �� ����������� (��. ��������� SSD1306_IfMode)
#endif
//==============================================================================


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
