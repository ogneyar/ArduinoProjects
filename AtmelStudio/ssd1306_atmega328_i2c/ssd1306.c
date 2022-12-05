#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#include "ssd1306.h"
#include "font.h"
#include "twi_driver.h"

uint8_t scr_buffer[0]; // Буфер дисплея

// Массив команд инициализации
const uint8_t init[] PROGMEM =
{
0xAE, // Выключить дисплей

0xD5, // Настройка частоты обновления дисплея
0x80, 
///+----- делитель 0-F/ 0 - деление на 1
//+------ частота генератора. по умочанию 0x80
0xA8, // Установить multiplex ratio
0x1F, // 1/64 duty (значение по умолчанию), 0x1F - 128x32, 0x3F - 128x64

0xD3, // Смещение дисплея (offset)
0x00, // Нет смещения

0x40, // Начала строки начала разверки 0x40 с начала RAM

0x8D, // Управление внутреним преобразователем
0x14, // 0x10 - отключить (VCC подается извне) 0x14 - запустить внутрений DC/DC

0x20, // Режим автоматической адресации
0x00, // 0-по горизонтали с переходом на новую страницу (строку)
      // 1 - по вертикали с переходом на новую строку
      // 2 - только по выбранной странице без перехода 

0xA1, // Режим разверки по странице (по X)
      // A1 - нормальный режим (слева/направо) A0 - обратный (справа/налево)

0xC8, // Режим сканирования озу дисплея
      // для изменения системы координат
      // С0 - снизу/верх (начало нижний левый угол)
      // С8 - сверху/вниз (начало верний левый угол)
0xDA, // Аппаратная конфигурация COM
0x02, // 0x02 - 128x32, 0x12 - 128x64

0x81, // Установка яркости дисплея
0x8F, // 0x8F..0xCF

0xD9, // Настройка фаз DC/DC преоразователя
0xF1, // 0x22 - VCC подается извне / 0xF1 для внутренего

0xDB, // Установка уровня VcomH
0x40, // Влияет на яркость дисплея 0x00..0x70

0xA4, // Режим нормальный

0xA6, // 0xA6 - нет инверсии, 0xA7 - инверсия дисплея

0xAF  // Дисплей включен
};

// Функция инициализации дисплея
void display_init(void)
{
// Посылаем команды в дисплей из массива инициализации
for(uint8_t i = 0; i < sizeof init; i++) disp_write(0, pgm_read_byte(&init[i]));

}

// Функция записи данных/команды в дисплей
void disp_write(uint8_t mode, uint8_t data) // Режим: 1-данные, 0-команда
{
uint8_t m;
if(mode) m = 0x40; // Режим данных
else m = 0x00; // Режим команды

Send_start();			//send start strings
Send_byte(OWN_ADR);		//Slave address
Send_byte(m);		//Control Byte - Command
Send_byte(data);		//payload
Send_stop();
}

// Функция очистки буфера дисплея
void screen_clear(void)
{
for(uint16_t i = 0; i < 512; i++) scr_buffer[i] = 0;
}

// Функция обновления дисплея
void screen_update(void)
{
disp_write(0,0x21); // Установка столбца
disp_write(0,0);    // Начальный адрес
disp_write(0,127);  // Конечный адрес

disp_write(0,0x22); // Установка строки
disp_write(0,0);    // Начальный адрес
disp_write(0,3);    // Конечный адрес
// Запись данных из буфера в дисплей
for(uint16_t i = 0; i < 512; i++) disp_write(1, scr_buffer[i]);
}

// Функция вывода символа 5x8
void print_char_5x8(uint8_t column, uint8_t string, uint8_t sign) // 0..120 / 0..7 / Символ
{
if(column <= 120 && string < 3)
  {
  if((sign >= 0x20) && (sign <= 0x7F))
  sign -= 32;// Смещение в таблице для символов ASCII[0x20-0x7F]
  else if (sign >= 0xC0)
  sign -= 96; // Смещение в таблице для символов CP1251[0xC0-0xFF]
  else  sign = 85; // Остальные игнорируем (их просто нет в таблице для экономии памяти)
  
  for(uint8_t i = 0; i < 5; i++)
	{
	scr_buffer[128*string + column + i] = pgm_read_byte(&font_5x8[5*sign + i]);
	}
  }
}

// Функция вывода строки 5x8
void print_string_5x8(uint8_t column, uint8_t string, char *str) // 0..120 / 0..7 / Строка
{
while(*str)
	{
	print_char_5x8(column, string, *str++);
	column+=6;
	}
}


