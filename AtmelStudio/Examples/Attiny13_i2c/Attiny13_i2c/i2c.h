#ifndef I2C_H_
#define I2C_H_

#include "main.h"

// пины
#define SDA			PB1
#define SDA_DDR		DDRB
#define SDA_PIN		PINB

#define SCL			PB0
#define SCL_DDR		DDRB
#define SCL_PIN		PINB

// пауза
#define I2C_DELAY	_delay_us(10)

// управление линиями
#define SDA_1		SDA_DDR&=~(1<<SDA)
#define SDA_0		SDA_DDR|=(1<<SDA)
#define SCL_1		SCL_DDR&=~(1<<SCL)
#define SCL_0		SCL_DDR|=(1<<SCL)



void i2c_start();
void i2c_stop();
uint8_t i2c_read(uint8_t ack);
uint8_t i2c_send(uint8_t data);


#endif 