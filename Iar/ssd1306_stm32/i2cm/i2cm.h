//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _I2CM_H
#define _I2CM_H

#include "../types.h"


// Константы, обозначающие ошибки при чтении RAM из mlx9061x
#define I2C_ERR_Ok         0
#define I2C_ERR_NotConnect -1
#define I2C_ERR_BadChksum  -2
#define I2C_ERR_HWerr      -3


// Процедура инициализации i2c (I2C1 или I2C2) в режиме master с заданной частотой интерфейса
void i2cm_init(I2C_TypeDef* I2Cx, uint32_t i2c_clock);
// Функция стартует обмен. Выдаёт условие START, выдаёт адрес слейва с признаком R/W
int8_t i2cm_Start(I2C_TypeDef* I2Cx, uint8_t slave_addr, uint8_t IsRead, uint16_t TimeOut);
// Функция выдаёт условие STOP
int8_t i2cm_Stop(I2C_TypeDef* I2Cx, uint16_t TimeOut);
// Функция выдаёт на шину массив байт из буфера
int8_t i2cm_WriteBuff(I2C_TypeDef* I2Cx, uint8_t *pbuf, uint16_t len, uint16_t TimeOut);
// Функция читает массив байт с шины и выдаёт условие STOP
int8_t i2cm_ReadBuffAndStop(I2C_TypeDef* I2Cx, uint8_t *pbuf, uint16_t len, uint16_t TimeOut);

#endif