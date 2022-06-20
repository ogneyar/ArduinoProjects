/*
 * attiny13-IR-send.cpp
 *
 * Created: 12.11.2017 22:05:52
 * Author : andrey
 */ 
#define F_CPU 1200000UL
#include <avr/io.h>
#include <util/delay.h>

// фунция отправки бита
void IR_sendbit(char bit)
{

	PORTB &= ~(1<<PB0); // ставим на шине 0
	_delay_us(320); // ждем 320 мкс
	PORTB |=(1<<PB0); // ставим на шине 1
	if(bit) { _delay_us(1680); } // если бит=1 то ждем 1680 мкс
		else { _delay_us(680); } // если 0 то ждем 680 мкс

}

// функция отправки полного пакета.
void IR_send(char adress, char command) {

// отправка адреса
	for(char i=0; i<5; i++)//посылаем отдельно каждый бит 
	{
		if((adress & (1<<i)) == 1<<i)//посылаем 1
		IR_sendbit(1);
		else //посылаем 0
		IR_sendbit(0);
	}
	
// отправка команды
	
		for(char i=0; i<8; i++)//посылаем отдельно каждый бит 
		{
			if((command & (1<<i)) == 1<<i)//посылаем 1
			IR_sendbit(1);
			else //посылаем 0
			IR_sendbit(0);
		}
		
// отправка бит расширения =1
		IR_sendbit(1);
//отправка бит контроля =0
		IR_sendbit(0);
			PORTB &= ~(1<<PB0); // ставим на шине 0
			_delay_us(320); // ждем 320 мкс
		PORTB |= (1<<PB0);
		
_delay_ms(40);

	// отправка адреса
	for(char i=0; i<5; i++)//посылаем отдельно каждый бит
	{
		if((adress & (1<<i)) == 1<<i)//посылаем 1
		IR_sendbit(1);
		else //посылаем 0
		IR_sendbit(0);
	}
	// отправка команды
	
	for(char i=0; i<8; i++)//посылаем отдельно каждый бит
	{
		if((command & (1<<i)) == 1<<i)//посылаем 0
		IR_sendbit(0);
		else //посылаем 1
		IR_sendbit(1);
	}
		
		// отправка бит расширения =0
		IR_sendbit(0);
		//отправка бит контроля =1
		IR_sendbit(1);
		PORTB &= ~(1<<PB0); // ставим на шине 0
		_delay_us(320); // ждем 320 мкс
		PORTB |= (1<<PB0);

}



int main(void)
{
	
			DDRB|= (1<<PB0);
			PORTB |= (1<<PB0);
			
			char adress=0x03;
			char command=0x11;
_delay_ms(2000);
    /* Replace with your application code */
    while (1) 
    {
		IR_send( adress,  command);
		_delay_ms(5000);
    }
}

