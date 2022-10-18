#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

// включить вачдог
void WDT_on(void){
	/* сборос вачдога */
	asm("wdr");
	/* разрешить изменение вачдога */
	WDTCR |= (1<<WDCE) | (1<<WDE);
	/* включить вачдог на резет через 2 секунды */
	WDTCR = (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
}

// отключить вачдог
void WDT_off(void){
	/* сборос вачдога */
	asm("wdr");
	/* разрешить изменение вачдога */
	WDTCR |= (1<<WDCE) | (1<<WDE);
	/* отключить вачдог */
	WDTCR = 0x00;
}
	
int main(void)
{
	DDRB|=(1<<PB0) | (1<<PB5);
	
	// желтая мигалка
	PORTB^=(1<<PB0);
	_delay_ms(500);
	PORTB^=(1<<PB0);
	WDT_on();
    while (1) 
    {
		// зеленая мигалка
		PORTB^=(1<<PB5);
		_delay_ms(1000);
		asm("wdr");// сброс вачдога
		_delay_ms(1500);
		asm("wdr");// сброс вачдога
	}
}

