#include "main.h"

int8_t temp=99;

int main(void)
{
	sei();
	i2c_ini();// ������������� i2c
	ds_ini(); // ������������� ��1307
	
	display_ini();
	display_bright(255,255,255,255);
	
	
	ds_settime(11,11,11);
	
    while (1) 
    {
		ds_showtime();
		ds_temp(&temp);
    }
}

