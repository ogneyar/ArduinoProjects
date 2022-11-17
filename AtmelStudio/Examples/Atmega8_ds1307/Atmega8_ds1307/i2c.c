#include "i2c.h"

// �������� ���������� �� ������������ 100 ���
void i2c_ini(void){
	TWSR=0;
	TWBR=32;
}

//�������� ���������� �������
void i2c_wait(void){
	while (!(TWCR & (1<<TWINT)));
}

// ������� �����
void i2c_start(void) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	i2c_wait();
}

// ������� ����
void i2c_stop(void) {
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

// ������ �����
void i2c_write(uint8_t byte) {
	TWDR = byte;
	TWCR = (1<<TWINT)|(1<<TWEN);
	i2c_wait();
}

// ������ �����, ack!=0 � �������, ack=0 ��� ������.
uint8_t i2c_read(uint8_t ack){
	if (ack) TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	else TWCR = (1<<TWINT)|(1<<TWEN);
	i2c_wait();
	return TWDR;
}