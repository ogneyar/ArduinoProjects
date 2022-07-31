#include "cd4024.h"

void cd4024_ini(void){
	DDRB|=(1<<PIN_CONTROL);
}

void cd4024_clear(void){
	PORTB|=(1<<PIN_CONTROL);
	_delay_ms(2);// ждем заряда
	PORTB&=~(1<<PIN_CONTROL);
	_delay_ms(4);// ждем разряда, подольше чтобы наверняка
}

void cd4024_set(uint8_t n){
	cd4024_clear();
	while (n--)
	{
		PORTB|=(1<<PIN_CONTROL);
		PORTB&=~(1<<PIN_CONTROL);
	}
}