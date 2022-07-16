#define F_CPU 1200000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_CONTROL		PB4// определ€ем пин управл€ющий счетчиком

//установка значени€
void set(uint8_t num){
	static uint8_t position;// переменна€ дл€ хранени€текущей позиции
	uint8_t clk=(num-position)&127;// расчет количетва импульсов дл€ установки новой позиции
	position=num;//запоминаем новую позицию
	// отправка импульсов в счетчик
	while (clk--)
	{
		DDRB|=(1<<LED_CONTROL);
		DDRB&=~(1<<LED_CONTROL);
	}
}

int main(void)
{
	_delay_ms(1000);
	uint8_t leds=1;
    while (1) 
    {
		while (leds<64)
		{
			set(leds);
			leds<<=1;
			_delay_ms(500);
		}
		
		while (leds>1)
		{
			set(leds);
			leds>>=1;
			_delay_ms(500);
		}
		
		for (uint8_t i=0; i<4; i++)
		{
			set(0b01110111);
			_delay_ms(500);
			set(0b00001000);
			_delay_ms(500);
		}
		
		for (uint8_t i=0; i<4; i++)
		{
			set(0b01010101);
			_delay_ms(500);
			set(0b00101010);
			_delay_ms(500);
		}
		
		while (leds<64)
		{
			set(leds);
			leds=(leds*2)+1;
			_delay_ms(500);
		}
		
		while (leds>1)
		{
			set(leds);
			leds=(leds-1)/2;
			_delay_ms(500);
		}
    }
}

