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
#define I2C_ERR_Ok              0
#define I2C_ERR_NotConnect      -1
#define I2C_ERR_BadChksum       -2
#define I2C_ERR_HWerr           -3


// Константы для определения состояния периферии TWI
#define TW_STATUS_MASK                  0xF8
#define TW_STATUS                       (TWSR & TW_STATUS_MASK)
#define TW_START                        0x08    // Состояние - Условие START выдано
#define TW_REP_START                    0x10    // Состояние - Повторный START выдано
#define TW_MT_SLA_ACK                   0x18
#define TW_MT_SLA_NACK                  0x20
#define TW_MT_DATA_ACK                  0x28    // Состояние - Байт передан и ACK получен
#define TW_MT_DATA_NACK                 0x30    // Состояние - Байт передан и NACK получен
#define TW_MT_ARB_LOST                  0x38
#define TW_MR_ARB_LOST                  0x38
#define TW_MR_SLA_ACK                   0x40
#define TW_MR_SLA_NACK                  0x48
#define TW_MR_DATA_ACK                  0x50
#define TW_MR_DATA_NACK                 0x58
#define TW_ST_SLA_ACK                   0xA8
#define TW_ST_ARB_LOST_SLA_ACK          0xB0
#define TW_ST_DATA_ACK                  0xB8
#define TW_ST_DATA_NACK                 0xC0
#define TW_ST_LAST_DATA                 0xC8
#define TW_SR_SLA_ACK                   0x60
#define TW_SR_ARB_LOST_SLA_ACK          0x68
#define TW_SR_GCALL_ACK                 0x70
#define TW_SR_ARB_LOST_GCALL_ACK        0x78
#define TW_SR_DATA_ACK                  0x80
#define TW_SR_DATA_NACK                 0x88
#define TW_SR_GCALL_DATA_ACK            0x90
#define TW_SR_GCALL_DATA_NACK           0x98
#define TW_SR_STOP                      0xA0
#define TW_NO_INFO                      0xF8
#define TW_BUS_ERROR                    0x00
 


// Процедура инициализации i2c (I2C1 или I2C2) в режиме master с заданной частотой интерфейса
void i2cm_init(uint32_t i2c_clock);
// Функция стартует обмен. Выдаёт условие START, выдаёт адрес слейва с признаком R/W
int8_t i2cm_Start(uint8_t slave_addr, uint8_t IsRead, uint16_t TimeOut);
// Функция выдаёт условие STOP
int8_t i2cm_Stop(uint16_t TimeOut);
// Функция выдаёт на шину массив байт из буфера
int8_t i2cm_WriteBuff(uint8_t *pbuf, uint16_t len, uint16_t TimeOut);
// Функция читает массив байт с шины и выдаёт условие STOP
int8_t i2cm_ReadBuffAndStop(uint8_t *pbuf, uint16_t len, uint16_t TimeOut);

#endif