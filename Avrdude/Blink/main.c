#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRB |= (1<<PB5);
	
	while(1) {
		_delay_ms(200);
		PORTB ^= (1<<PB5);
	}
}