#include "main.h"
#include "TM1637.h"


uint8_t digits[] =
{
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f
};




void indication(uint16_t n)
{
	uint8_t buf[4];
	for (uint8_t i = 0; i < 4; i++) 
	{ 
		buf[i] = digits[n % 10]; // записываем остаток в буфер
		n /= 10;         // "сдвигаем" число
	}
	start();
	writeValue(SetBright); // яркость, настраивается в main.h
	start();
	writeValue(0x40); // писать в регистры дисплея
	stop();
	start();
	writeValue(0xc0); // вывод с 1-го разряда.
	writeValue(buf[3]);
	writeValue(buf[2]+128); // +128 это точка, сташий бит врубаем
	writeValue(buf[1]);
	writeValue(buf[0]);
	stop();
}



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

void writeValue(uint8_t value)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		PORTB &=~ (1<<_CLK);
		_delay_us(5);
		bool not_null = ((value & (1 << i)) >> i);
		if(not_null)
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