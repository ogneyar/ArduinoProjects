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
#define PB0  0
#define PB1  1
#endif

#define PORT_LED PORTA
#define PORT_BTN PORTB
#define LED		(1<<PA5)
#define BTN_USR (1<<PB1)

void delay(uint32_t  interval);


int main(void)
{
    DDRA |= LED; // на выход
	//DDRA &= ~LED; // на вход (по умолчанию)
    DDRB |= BTN_USR; // на выход
	//DDRB &= ~BTN_USR; // на вход (по умолчанию)
		
	PORT_BTN |= BTN_USR; // pull up -  подтяжка к плюсу питания
	//PORT_BTN &= ~BTN_USR; // pull down -  подтяжка к минусу питания
	PORT_LED |= LED; // pull up - (светодиод гаснет)
	//PORT_LED &= ~LED; // pull down - (светодиод горит)
		
	uint32_t  interval = 1000; // примерно секунда
	
	int8_t flag = 0;
	
    while (1) 
    {
		if (!(PINB & BTN_USR)) //  если кнопка нажата
			interval = 50;
		else if (flag < 4)
			interval = 500;
		else 
			interval = 100;
		
		delay(interval);
		PORT_LED ^= LED;
		
		flag++;
		
		if (flag > 10) flag = 0;
    }
}

void delay(uint32_t  interval) {
	for (uint32_t i=0; i < (interval<<4); i++) asm("nop"); // <<4 - вместо * на 16
}


