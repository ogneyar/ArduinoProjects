//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _SPIM_H
#define _SPIM_H

#include "../types.h"


// Процедура инициализации spi (SPI1 или SPI2) в режиме master
void spim_init(SPI_TypeDef* SPIx, uint8_t WordLen);
// Процедура отправляет массив 16-битных слов
void SPI_send16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len);
// Процедура отправляет массив 8-битных слов
void SPI_send8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len);
// Процедура отправляет массив 16-битных слов
void SPI_recv16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len);
// Процедура отправляет массив 8-битных слов
void SPI_recv8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len);

#endif