/*
 * Blink.c
 *
 * Created: 25.10.2022 14:09:48
 * Author : Огънеяръ
 */ 

//#define F_CPU 1000000UL

#include <avr/io.h>
#include <stdint.h>

#ifndef PA5
#define PA5  5
#define PB1  1
#endif

#define PORT_LED PORTA
#define PORT_BTN PORTB
#define LED		(1<<PA5)
#define BTN_USR (1<<PB1)

void delay(uint32_t  interval);


int main(void)
{
    DDRA |= LED;  // на выход
	DDRB &= ~BTN_USR; // на вход (по умолчанию)
	
	PORTB |= BTN_USR; // pull up -  подтяжка к плюсу питания
	
	uint32_t  interval = 10000;
	
    while (1) 
    {
		if ( ! (PORTB & BTN_USR) )
			interval = 100000;
		else 
			interval = 10000;
		
		PORT_LED ^= LED;
		delay(interval);
		
    }
}

void delay(uint32_t  interval) {
	for (uint32_t i=0; i < interval; i++) asm("nop");
}


