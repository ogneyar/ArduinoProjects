
#include <inttypes.h>
//#include "i2c.h"

// �����
void i2c_start(void){
	SDA_0;
	I2C_DELAY;
	SCL_0;
}

// ���� 
void i2c_stop(void){
	SDA_0;
	I2C_DELAY;
	SCL_1;
	I2C_DELAY;
	SDA_1;
}


// �������� �����
uint8_t i2c_send(uint8_t data){
	uint8_t i=8, ask;
	while (i--)
	{
		if(data&(1<<i)) SDA_1;// ���� ��� 1 ������ 1 �� �����
		else SDA_0;// ������ 0 �� �����
		I2C_DELAY;
		SCL_1;// �����
		I2C_DELAY;
		SCL_0;// ����
	}
	SDA_1;// ��������� ����
	I2C_DELAY;
	SCL_1;// ����� �����
	I2C_DELAY;
	ask=(SDA_PIN&(1<<SDA));// ������ ����� ���
	SCL_0;// ����
	return ask;//  0 - ask, �� 0 - nask
}


// ��������� �����
uint8_t i2c_read(uint8_t ask){
	uint8_t bytes=0, i=8;
	while(i--)
	{
		SCL_1;// ����� �����
		I2C_DELAY;
		if(SDA_PIN & (1 << SDA)) bytes|=(1<<i);// ���� SDA 1 � �-��� ��� ����� 1
		SCL_0;// ���� �����
		I2C_DELAY;
	}
	if(ask) SDA_0;// ask ��� nask
	else SDA_1;
	
	SCL_1;//
	I2C_DELAY;// ���� �� ��������� ������ ��� ��������
	SCL_0;//
	I2C_DELAY;
	SDA_1;// ��������� ��� ���� ��������
	return bytes;
}
