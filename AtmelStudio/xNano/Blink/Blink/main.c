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
#define PA5 5
#endif

#define PORT_LED PORTA
#define LED (1<<PA5)

void delay(uint32_t  interval);


int main(void)
{
    DDRA |= LED;  // на выход
	PORT_LED |= LED; // pull up - (светодиод гаснет)
	
	uint32_t  interval = 100;
	
    while (1) 
    {
		PORT_LED ^= LED;
		delay(interval);		
    }
}

void delay(uint32_t  interval) {
	for (uint32_t i=0; i < interval<<4; i++) asm("nop"); // <<4 - вместо * на 16
}


