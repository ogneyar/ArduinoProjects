#include <avr/io.h>
#include <avr/interrupt.h>

// преобразование АЦП в код нажатой кнопки
uint8_t button_code(uint8_t adc){
	if (adc>200) return 0;// кнопки не нажаты
	if (adc>160) return 4;// нажата 4-я кнопка 
	if (adc>110) return 3;// 3-я
	if (adc>30) return 2;// 2-я
	if (adc>=0) return 1;// 1-я
}

uint8_t button_old;// под хранение предыдущего состояния
uint8_t button_count;// счетчик
volatile uint8_t button_clk;// флажок клика

// обработчик прерывания по окончанию преобразования АЦП ~ 600Гц
ISR(ADC_vect){
	uint8_t button=button_code(ADCH);
	if (button!=button_old)// сравниваем текущее и предыдущее состояние
	{
		button_count=0;// сбросить счетчик в ноль
	} 
	else
	{
		if (button_count<255) button_count++; // инкремент счетчика
		if (button_count==30) button_clk=button;// если дотикали до 30 поднять флажок клика
	}
	
	button_old=button;// записать текущее значение для следующего прерывания
}

int main(void)
{
	// настройка АЦП
	ADMUX|=(1<<ADLAR); // результат преобразования - 8 старших бит в ADCH
	// разрешить работу АЦП, старт преобразования, free running mode, разрешить прерывание АЦП, максимальный делитель 128
	ADCSRA|=(1<<ADEN) | (1<<ADSC) | (1<<ADFR) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
	//-----------------------------------------------------------------------
	
	DDRD|=(1<<PD0) | (1<<PD1) | (1<<PD2) | (1<<PD3);// пины светодиодов на выход
	sei();// глобально разрешить прерывания
    while (1) 
    {
		if (button_clk)// если флажок не ноль
		{
			switch (button_clk)// отрабатываем клик
			{
				case 1:
				PORTD^=(1<<PD0);
				break;
				
				case 2:
				PORTD^=(1<<PD1);
				break;
				
				case 3:
				PORTD^=(1<<PD2);
				break;
				
				case 4:
				PORTD^=(1<<PD3);
				break;
			}
			button_clk=0;// сбросить флажок в ноль
		}
    }
}

