#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t button_count;// счетчик кнопки 1
volatile uint8_t button2_count;// счетчик кнопки 2
volatile uint8_t button_clk; // флаг клика

// обработчик прерывания по переполнению таймера 0
ISR(TIMER0_OVF_vect){
	// опрос первой кнопки
	if (PINC&(1<<PC0)) // если на ПИНе 1
	{
		if (button_count>=5 && button_count<60) button_clk=1; //если в рамках поднять флаг короткого клика 1
		button_count=0;// обнулить счетчик
	}
	else  // ИНАЧЕ на ПИНе 0
	{
		if (button_count<61) button_count++; // инкермент счетчика с ограничением 61
		if (button_count==60) button_clk=101;// если в счетчике 60 поднять флаг длинного клика 1
	}
	
	// опрос второй кнопки
	if (PINC&(1<<PC1)) // если на ПИНе 1
	{
		if (button2_count>=5 && button2_count<60) button_clk=2;// если в рамках поднять флаг короткого клика 2
		button2_count=0;// обнулить счетчик
	}
	else  // ИНАЧЕ на ПИНе 0
	{
		if (button2_count<61) button2_count++; // инкермент счетчика с ограничением 61
		if (button2_count==60) button_clk=102; //если в счетчике 60 поднять флаг длинного клика 2
	}
}

int main(void)
{
	TCCR0|=(1<<CS01) | (1<<CS00);// запуск таймера 0 с делителем 64
	TIMSK|=(1<<TOIE0); // разрешить прерывание по переполнению таймера 0
	
	DDRB|=(1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3);// пины светодиодов на выход
	
	sei();//глобально разрешить перерывания
	while (1)
	{
		if (button_clk) // проверка флажка клика
		{
			switch (button_clk)
			{
				case 1:// отработка короткого клика 1
				PORTB^=(1<<PB0);
				break;
				
				case 101:// отработка длинного клика 1
				PORTB^=(1<<PB1);
				break;
				
				case 2:// отработка короткого клика 2
				PORTB^=(1<<PB2);
				break;
				
				case 102:// отработка длинного клика 2
				PORTB^=(1<<PB3);
				break;
			}
			button_clk=0;// сбросить флаг клика в 0
		}
		
	}
}