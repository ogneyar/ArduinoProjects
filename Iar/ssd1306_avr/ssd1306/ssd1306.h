//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _SSD1306_H
#define _SSD1306_H

#include <types.h>

#define SSD1306_IfMode_Par8080                  0       // Параллельный интерфейс 8080 8-бит
#define SSD1306_IfMode_Par6800                  1       // Параллельный интерфейс 6800 8-бит
#define SSD1306_IfMode_SPI_3w                   2       // SPI по 3 линиям (CS, SCLK, MOSI)
#define SSD1306_IfMode_SPI_4w                   3       // SPI по 4 линиям (CS, SCLK, MOSI, D/C)
#define SSD1306_IfMode_I2C                      4       // I2C

// Интерфейс подключения дисплея      
#define SSD1306_IfMode          SSD1306_IfMode_SPI_4w //SSD1306_IfMode_I2C 


// Режимы автоматического сдвига указателя в памяти кадра ssd1306
#define SSD1306_Adressing_Horizontal            0       // Сначала инкремент по горизонтали, затем инкремент по вертикали
#define SSD1306_Adressing_Vertical              1       // Сначала инкремент по вертикали, затем инкремент по горизонтали
#define SSD1306_Adressing_Page                  2       // Инкремент только по горизонтали

// Команды из раздела Fundamental
#define SSD1306_CMD_SetContrast                 0x81
#define SSD1306_CMD_AllPixRAM                   0xA4
#define SSD1306_CMD_AllPixOn                    0xA5
#define SSD1306_CMD_SetInverseOff               0xA6
#define SSD1306_CMD_SetInverseOn                0xA7
#define SSD1306_CMD_Sleep                       0xAE
#define SSD1306_CMD_Wake                        0xAF

//==============================================================================
// Коды команд дисплея
//==============================================================================
// Команды из раздела Fundamental
#define SSD1306_CMD_SetContrast                 0x81
#define SSD1306_CMD_AllPixRAM                   0xA4
#define SSD1306_CMD_AllPixOn                    0xA5
#define SSD1306_CMD_SetInverseOff               0xA6
#define SSD1306_CMD_SetInverseOn                0xA7
#define SSD1306_CMD_Sleep                       0xAE
#define SSD1306_CMD_Wake                        0xAF

// Команды из раздела Scrolling
#define SSD1306_CMD_DeactivateScroll            0x2E

// Команды из раздела Addressing Setting
// Команда выбора режима автосдвига указателя в памяти кадра
#define SSD1306_CMD_SetMemAdressingMode         0x20    
// Команды выбора диапазона изменения страницы и колонки при автосдвиге указателя в памяти кадра
// Применяется для режимов автосдвига SSD1306_Adressing_Horizontal и SSD1306_Adressing_Vertical
#define SSD1306_CMD_SetColumnAddr               0x21
#define SSD1306_CMD_SetPageAddr                 0x22
// Команды выбора страницы и диапазона изменения колонки при автосдвиге указателя в памяти кадра
// Применяется для режима автосдвига SSD1306_Adressing_Page
#define SSD1306_CMD_PageAddrMode_SetPage        0xB0
#define SSD1306_CMD_PageAddrMode_StartColumnLo  0x00
#define SSD1306_CMD_PageAddrMode_StartColumnHi  0x10

// Команды из раздела Hardware Configuration
#define SSD1306_CMD_SetDisplayStartLine         0x40
#define SSD1306_CMD_SetSegmentRemap             0xA0
#define SSD1306_CMD_SetMultiplexRatio           0xA8
#define SSD1306_CMD_SetCOMoutScanDirection      0xC0 
#define SSD1306_CMD_SetDisplayOffset            0xD3
#define SSD1306_CMD_SetCOMPinsConfig            0xDA
  
// Команды из раздела Timing & Driving Scheme Setting
#define SSD1306_CMD_SetDisplayClockDivider      0xD5
#define SSD1306_CMD_SetPrechargePeriod          0xD9
#define SSD1306_CMD_SetVCOMHDeselectLevel       0xDB

// Команды из раздела Charge Pump
#define SSD1306_CMD_ChargePumpSetting           0x8D
//==============================================================================


//==============================================================================
// Настройки подключения к дисплею
//==============================================================================
#define SSD1306_ResetPinUsed            1       // Используется управление пином Reset ssd1306      
#define SSD1306_Reset_Port              PORTB
#define SSD1306_Reset_DDR               DDRB
#define SSD1306_Reset_Mask              (1 << 0)

#if (SSD1306_IfMode == SSD1306_IfMode_I2C)       // Параметры работы по I2C
  // i2c-адрес контроллера дисплея. Зависит от состояния ножки SA0 (она же D/C). 0x3C или 0x3D
  #define SSD1306_I2C_addr              0x3C //0x3D;   // 7-битный i2c-адрес контроллера дисплея ssd1306      
  #define SSD1306_I2C_clock             100000  // Частота работы I2C        
#elif (SSD1306_IfMode == SSD1306_IfMode_SPI_4w)       // Параметры работы по SPI-4w
  #define SSD1306_CSPinUsed             0       // Используется управление пином CS ssd1306      
  #define SSD1306_CS_Port               PORTD
  #define SSD1306_CS_DDR                DDRD
  #define SSD1306_CS_Mask               (1 << 7)
  #define SSD1306_DC_Port               PORTB
  #define SSD1306_DC_DDR                DDRB
  #define SSD1306_DC_Mask               (1 << 1)
#else
  #error Работа по выбранному интерфейсу ещё не реализована (см. константу SSD1306_IfMode)
#endif
//==============================================================================


// Процедура инициализации дисплея на контроллере ssd1306
void SSD1306_Init(uint8_t Width, uint8_t Height);
// Процедура переводит дисплей в режим сна
void SSD1306_Sleep(void);
// Процедура выводит дисплей из режима сна
void SSD1306_Wake(void);
// Процедура включает инверсию дисплея
void SSD1306_SetInverseOn(void);
// Процедура отключает инверсию дисплея
void SSD1306_SetInverseOff(void);
// Процедура включает все пиксели дисплея (Тест индикатора)
void SSD1306_AllPixOn(void);
// Процедура отключает тест дисплея и выводит на него картинку из буфера кадра в ssd1306
void SSD1306_AllPixRAM(void);
// Процедура устанавливает параметр контрастности (0-255)
void SSD1306_SetContrast(uint8_t Value);
// Процедура устанавливает начальный и конечный индекс колонки 
// для автосмещения указателя в памяти кадра при чтении записи.
void SSD1306_SetColumns(uint8_t Start, uint8_t End);
// Процедура устанавливает начальный и конечный индекс страницы 
// для автосмещения указателя в памяти кадра при чтении записи.
void SSD1306_SetPages(uint8_t Start, uint8_t End);
// Процедура передаёт в дисплей буфер кадра из массива pBuff
void SSD1306_DisplayFullUpdate(uint8_t *pBuff, uint16_t BuffLen);

#endif
