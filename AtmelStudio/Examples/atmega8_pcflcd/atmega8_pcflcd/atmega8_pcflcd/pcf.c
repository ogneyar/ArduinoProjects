#include "pcf.h"


void pcf_write(uint8_t byte){
	i2c_start();
	i2c_write(0x40);// ����� �� ������
	i2c_write(byte);
	i2c_stop();
}