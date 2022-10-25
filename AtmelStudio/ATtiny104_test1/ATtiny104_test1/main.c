/*
 * ATtiny104_test1.c
 *
 * Created: 25.10.2022 12:47:32
 * Author : Огънеяръ
 */ 

#define F_CPU 1000000UL

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
	//DDRB &= ~BTN_USR; // на вход (по умолчанию)
	DDRB |= BTN_USR;
	
	//PORTB |= BTN_USR; // pull up -  подтяжка к плюсу питания
	//PORTB &= ~BTN_USR; // pull down -  подтяжка к минусу питания
	
	PORTB = 0b00000010;
	
	uint32_t  interval = 10000;
	
	while(PORTB == 0b00000010) ;// BTN_USR) ) ;
	
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


