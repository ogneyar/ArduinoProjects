#include "main.h"

int main(void)
{
	display_ini();
	display(1,2,3,4);
	display_bright(150,150,150,150);
	sei();
    while (1) 
    {
		while(PIND&(1<<PD2));
		display_bright(50,50,250,250);
		_delay_ms(1000);
		
		while(PIND&(1<<PD2));
		display_bright(250,250,50,50);
		_delay_ms(1000);
		
		
		while(PIND&(1<<PD2));
		display_bright(250,50,250,50);
		_delay_ms(1000);
		
		
		while(PIND&(1<<PD2));
		display_bright(50,250,50,250);
		_delay_ms(1000);
    }
}

