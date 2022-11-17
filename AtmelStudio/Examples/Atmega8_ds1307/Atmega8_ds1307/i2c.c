#include "i2c.h"

// натройка интерфейса на тактирование 100  гц
void i2c_ini(void){
	TWSR=0;
	TWBR=32;
}

//ожидание завершени€ задани€
void i2c_wait(void){
	while (!(TWCR & (1<<TWINT)));
}

// условие старт
void i2c_start(void) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	i2c_wait();
}

// условие стоп
void i2c_stop(void) {
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

// запись байта
void i2c_write(uint8_t byte) {
	TWDR = byte;
	TWCR = (1<<TWINT)|(1<<TWEN);
	i2c_wait();
}

// чтение байта, ack!=0 с ответом, ack=0 без ответа.
uint8_t i2c_read(uint8_t ack){
	if (ack) TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	else TWCR = (1<<TWINT)|(1<<TWEN);
	i2c_wait();
	return TWDR;
}