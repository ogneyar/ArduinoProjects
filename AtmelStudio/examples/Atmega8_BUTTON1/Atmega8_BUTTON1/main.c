#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t button_count;// счетчик кнопки
volatile uint8_t button_clk; // флаг клика

// обработчик прерывания по переполнению таймера 0
ISR(TIMER0_OVF_vect){
	if (PINC&(1<<PC0)) // если на ПИНе 1
	{
		button_count=0;// обнулить счетчик
	}
	else  // ИНАЧЕ на ПИНе 0
	{
		if (button_count<6) button_count++; // инкермент счетчика с ограничением 6
		if (button_count==5) button_clk=1; // поднять флаг клика при значении счетчика = 5
	}
}

int main(void)
{
	TCCR0|=(1<<CS01) | (1<<CS00);// запуск таймера 0 с делителем 64
	TIMSK|=(1<<TOIE0); // разрешить прерывание по переполнению таймера 0
	
	DDRB|=(1<<PB0);// пин светодиода на выход
	
	sei();//глобально разрешить перерывания
	while (1)
	{
		if (button_clk) // проверка флажка клика
		{
			PORTB^=(1<<PB0); // отработка клика
			button_clk=0;// сбросить флаг клика в 0
		}
		
	}
}