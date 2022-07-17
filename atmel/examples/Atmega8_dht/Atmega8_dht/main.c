#include "main.h"

int main(void)
{
	DDRB|=(1<<PB0);
	sei();
	dht_ini();
    while (1) 
    {
		PORTB^=(1<<PB0);
		_delay_ms(300);
    }
}

