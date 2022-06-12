#include "main.h"

uint8_t test1, test11, test2;

//адреса для чтения
#define LM75_1_R	0x91
#define LM75_2_R	0x9f
// адреса для записи
#define LM75_1_W	0x90
#define LM75_2_W	0x9E
int main(void)
{
	while (1)
	{
		
		i2c_start();
		i2c_send(LM75_1_R);
		test1=i2c_read(1);
		test11=i2c_read(0);
		i2c_stop();
		
		
		i2c_start();
		i2c_send(LM75_2_R);
		test2=i2c_read(0);
		i2c_stop();
		
		_delay_ms(500);
	}
}

