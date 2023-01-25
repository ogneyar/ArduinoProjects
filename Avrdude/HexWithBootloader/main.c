#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRB |= (1<<PB3);
	
	while(1) {
		_delay_ms(2);
		PORTB ^= (1<<PB3);
	}
}