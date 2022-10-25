#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// обработчик прерывания INT1
ISR(INT1_vect){
	// выход из сна
}


// имитация работы мк
void work(void){
	for (uint8_t i=0; i<100;i++)
	{
		PORTB^=(1<<PB0);
		_delay_ms(100);
	}
}

int main(void)
{
	MCUCR|=(1<<SE);// разрешить сон
	MCUCR|=(1<<SM1); // выбор режима сна Power-down 
	
	GICR|=(1<<INT1); // разрешить прерывание INT1
	// биты ISC11, ISC10 должны быть в нуле для пробуждения мк.
	
    DDRB|=(1<<PB0);// пин на выход
	
	sei(); // глобально разрешить прерывания
    while (1) 
    {
		work();// работаем
		asm("sleep");// уход в сон
    }
}

