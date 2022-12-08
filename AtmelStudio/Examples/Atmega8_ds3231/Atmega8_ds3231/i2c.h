#ifndef I2C_H_
#define I2C_H_

#include "main.h"

void i2c_ini(void);// �������������
void i2c_start(void);// ������� �����
void i2c_stop(void);// ������� ����
void i2c_write(uint8_t byte);// ������ �����
uint8_t i2c_read(uint8_t ack);// ������ �����, ack!=0 � �������, ack=0 ��� ������.


#endif 