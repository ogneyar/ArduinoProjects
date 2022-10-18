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
