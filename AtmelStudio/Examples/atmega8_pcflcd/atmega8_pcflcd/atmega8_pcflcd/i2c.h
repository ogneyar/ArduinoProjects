#ifndef I2C_H_
#define I2C_H_

#include "main.h"

void i2c_ini(void);// инициализация
void i2c_start(void);// условие старт
void i2c_stop(void);// условие стоп
void i2c_write(uint8_t byte);// запись байта
uint8_t i2c_read(uint8_t ack);// чтение байта, ack!=0 с ответом, ack=0 без ответа.


#endif 