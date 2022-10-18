/*
 * attiny13-PWM.cpp
 *
 * Created: 17.11.2017 19:54:23
 * Author : andrey
 */ 

// ‘ьюзы HB: FF, LB: 7A

#define F_CPU 9600000UL
#include <avr/io.h>
#include <util/delay.h>

#define IR_LED PB0 

// частота 38 гц, скважность 1\4
void IR38_signal(void) {
	PORTB |=(1<<IR_LED);
	_delay_us(5);
	PORTB &=~(1<<IR_LED);
	_delay_us(20);
}

// сигнал длительностью примерно 320 мкс
void sharp_signal(void) {
	for (char i=0; i<13; i++) {
		PORTB |=(1<<IR_LED);
		_delay_us(5);
		PORTB &=~(1<<IR_LED);
		_delay_us(20);
	}
	
}

// 1
void sharp_1 (void) {
	sharp_signal();
	_delay_us(1680);
}

// 0
void sharp_0 (void) {
	sharp_signal();
	_delay_us(680);	
}

void IR_sharp (char adress, char command) {
	for(char i=0; i<5; i++)//посылаем отдельно каждый бит
		{
	if((adress & (1<<i)) == 1<<i)//посылаем 1
	sharp_1();
	else //посылаем 0
	sharp_0();
		}	

	for(char i=0; i<8; i++)//посылаем отдельно каждый бит
	{
		if((command & (1<<i)) == 1<<i)//посылаем 1
		sharp_1();
		else //посылаем 0
		sharp_0();
	}
	sharp_1();
	sharp_0();
	sharp_signal();

}

void IR_sharp_INVERS (char adress, char command) {
	for(char i=0; i<5; i++)//посылаем отдельно каждый бит
	{
		if((adress & (1<<i)) == 1<<i)//посылаем 1
		sharp_1();
		else //посылаем 0
		sharp_0();
	}

	for(char i=0; i<8; i++)//посылаем отдельно каждый бит
	{
		if((command & (1<<i)) == 1<<i)//посылаем 1
		sharp_1();
		else //посылаем 0
		sharp_0();
	}
	sharp_0();
	sharp_1();
	sharp_signal();

}

void IR_test (void) {
	for (char i=0; i<13; i++) {
	 IR38_signal();		
	}
	_delay_us(1680);
	
}
int main(void)
{
	// —ветидиод:
	DDRB |= (1 << IR_LED);
	PORTB &= ~(1 << IR_LED);

_delay_ms(100);

	IR_sharp(0x01,0x16);
	_delay_ms(40);
	IR_sharp_INVERS(0x01,0xE9);
	
	while(1)
	{
		




	}
}