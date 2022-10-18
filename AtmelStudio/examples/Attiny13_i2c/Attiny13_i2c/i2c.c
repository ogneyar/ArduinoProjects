#include "i2c.h"

// старт
void i2c_start(void){
	SDA_0;
	I2C_DELAY;
	SCL_0;
}

// стоп 
void i2c_stop(void){
	SDA_0;
	I2C_DELAY;
	SCL_1;
	I2C_DELAY;
	SDA_1;
}


// отправка байта
uint8_t i2c_send(uint8_t data){
	uint8_t i=8, ask;
	while (i--)
	{
		if(data&(1<<i)) SDA_1;// если бит 1 ставим 1 на линию
		else SDA_0;// ставим 0 на линию
		I2C_DELAY;
		SCL_1;// фронт
		I2C_DELAY;
		SCL_0;// спад
	}
	SDA_1;// отпустить дата
	I2C_DELAY;
	SCL_1;// фронт такта
	I2C_DELAY;
	ask=(SDA_PIN&(1<<SDA));// читаем линию сда
	SCL_0;// спад
	return ask;//  0 - ask, не 0 - nask
}


// получение байта
uint8_t i2c_read(uint8_t ack){
	uint8_t byte=0, i=8;
	while(i--)
	{
		SCL_1;// фронт такта
		I2C_DELAY;
		if(SDA_PIN & (1 << SDA)) byte|=(1<<i);// если SDA 1 в и-тый бит пишем 1
		SCL_0;// спад такта
		I2C_DELAY;
	}
	if(ack) SDA_0;// ask или nask
	else SDA_1;
	
	SCL_1;//
	I2C_DELAY;// такт на получения ответа или неответа
	SCL_0;//
	I2C_DELAY;
	SDA_1;// отпустить сда если притянут
	return byte;
}
