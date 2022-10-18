#define F_CPU	1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

ISR(TIMER2_OVF_vect){

}

int main(void)
{
	DDRB|=(1<<PB0); // пин на выход
	//------- асинхронный режим таймера 2----------------
	//TIMSK&=~((1<<OCIE2)|(1<<TOIE2));//1. Запретить прерывания, в TIMSK сбросить биты OCIE2 and TOIE2
	ASSR|=(1<<AS2);//2. включить асинхронный режим, в ASSR поднять бит AS2 
	
	//3. изменить регистры TCNT2, OCR2, and TCCR2, настроить таймер
	TCNT2=0;
	OCR2=0;
	//TCCR2=(1<<CS22) | (1<<CS20);// делитель 128
	//TCCR2=(1<<CS22);// делитель 64
	TCCR2= (1 << CS22)|(1 << CS21)|(1<<CS20);// Предделитель на 1024
	/*
	!!!!! выше была ошибка !!!!!
	TCCR2 после перехода в асинхронный режим может содержать рандомное значение.
	посему конструкция типа "TCCR2|=(1<<бит1) | (1<<бит2);" неверна 
	нужно применить простое присваивание "TCCR2=(1<<бит1) | (1<<бит2);"
	*/
	
	while(ASSR!=8);//4. ждать сброса флагов TCN2UB, OCR2UB, and TCR2UB в регистре ASSR
	TIFR|=(1<<OCF2)|(1<<TOV2);//5. сбросить флаги прерываний в TIFR биты OCF2, TOV2
	TIMSK|=(1<<TOIE2); //6. разрешить прерывания если нужно, в TIMSK
	//---------------------------------
	sei();// глобально разрешить прерывания
	set_sleep_mode(SLEEP_MODE_PWR_SAVE); // режим сна power save
    while (1) 
    {
		PORTB|=(1<<PB0);
		_delay_ms(300);
		PORTB&=~(1<<PB0);
		
		if (!(PINB&(1<<PB1)))
		{
			OCR2=1;//1. записать что-то в регистры TCCR2, TCNT2, или OCR2
			while (ASSR != 8);//2.ждать сброса флагов TCN2UB, OCR2UB, and TCR2UB в регистре ASSR
			sleep_enable();//3. уход 
			sleep_cpu(); //	в сон
			} else {
			_delay_ms(300);
		}
    }
}

