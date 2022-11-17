#include "main.h"

uint8_t hh,mm,ss;


int main(void)
{
	i2c_ini();// инициализация i2c
	ds1307_ini(); // инициализация дс1307
	
	display_ini();
	display(1,2,3,4);
	display_bright(255,255,255,255);
	sei();
	
	
    while (1) 
    {
		ds1307_showtime();
    }
}

