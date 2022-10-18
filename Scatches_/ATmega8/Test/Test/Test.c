
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= (1<<PD0);
	
    while(1)
    {
        PORTD |= (1<<PD0);
		_delay_ms(100);
		PORTD &= ~(1<<PD0);
		_delay_ms(100);
    }
}