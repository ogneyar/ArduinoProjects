#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRB |= (1<<PB1);
	
	while(1) {
		_delay_ms(50);
		PORTB ^= (1<<PB1);
	}
}