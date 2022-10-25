#include "1637.h"


uint8_t digits[] =
{
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f
};



//
void indication(uint16_t n, uint8_t znak)
{
	uint8_t n1, n2, n3;
	n1 =  n % 10;
	n2 = ((n % 100)-n1)/10;
	n3 = ((n % 1000) - n2 - n1) / 100;
	write(digits[n3], digits[n2]+128, digits[n1], znak);
}


//
void write(uint8_t n3, uint8_t n2, uint8_t n1, uint8_t n0)
{
	start();
	writeValue(SetBright); // яркость
	start();
	writeValue(0x40); // писать в регистры дисплея
	stop();
	start();
	writeValue(0xc0); // вывод с 1-го разряда.
	writeValue(n3);
	writeValue(n2);
	writeValue(n1);
	writeValue(n0);
	stop();
}



// 
void start(void)
{
	DDRB|=(1<<_CLK);
	DDRB|=(1<<_DIO);
	PORTB |= (1<<_CLK);
	PORTB |= (1<<_DIO);
	_delay_us(5);
	PORTB &=~ (1<<_DIO);
	PORTB &=~ (1<<_CLK);
	_delay_us(5);
}

//
void stop(void)
{
	DDRB|=(1<<_CLK);
	DDRB|=(1<<_DIO);
	PORTB &=~ (1<<_CLK);
	PORTB &=~ (1<<_DIO);
	_delay_us(5);
	PORTB |= (1<<_CLK);
	PORTB |= (1<<_DIO);
	_delay_us(5);
}

//
void writeValue(uint8_t value)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		PORTB &=~ (1<<_CLK);
		_delay_us(5);
		if((value & (1 << i)))
		PORTB |= (1<<_DIO);
		else
		PORTB &=~ (1<<_DIO);
		_delay_us(5);
		PORTB |= (1<<_CLK);
		_delay_us(5);
	}
	PORTB &=~ (1<<_CLK);
	_delay_us(5);
	PORTB |= (1<<_CLK);
	_delay_us(5);
}