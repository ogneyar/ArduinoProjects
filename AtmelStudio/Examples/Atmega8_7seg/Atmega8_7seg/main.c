#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

// символы цифр
uint8_t digit[]={63,6,91,79,102,109,125,7,127,111};

// вывод на индикацию
void display(uint8_t n, uint8_t dot){
	if (n<10)// если значение меньше 10 т.е. от 0 до 9
	{
		PORTD=digit[n]; // выводим значение n 
	} else {
		PORTD=121; // иначе ошибка
	}
	
	if(dot) PORTD|=(1<<7);// если dot не ноль зажигаем точку
}

int main(void)
{
	DDRD=255;// порт Д на выход
	
    while (1) 
    {
		// тикаем вперед без точки
		for (uint8_t i=0; i<10; i++)
		{
			display(i,0);
			_delay_ms(500);
		}
		
		// тикаем назад с точкой
		for (uint8_t i=9; i>0; i--)
		{
			display(i,1);
			_delay_ms(500);
		}
    }
}

