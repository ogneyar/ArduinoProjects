#include "adc.h"
volatile uint8_t adc_col;// счетчик преобразований
volatile uint32_t adc_summ;// переменная для суммы преобразований 

// обработчик прерывания АЦП
ISR(ADC_vect) {
	if (adc_col)// если счетчик не ноль
	{
		adc_col--;// декремент
		adc_summ+=ADC;// добавить в сумму очередное значение
		ADCSRA|=(1<<ADSC);// запуск преобразования
	}
}

// настройки АЦП
void adc_ini(void){
	ADMUX|=(1<<REFS0);// выбор источником опорного напряжения - AVCC
	ADMUX|=2; // выбор канала 2
	//ADMUX|=(1<<ADLAR);// формирование 8 старших бит результата в ADCH
	ADCSRA|=(1<<ADPS2);// делитель 16
	ADCSRA|=(1<<ADEN); // включение АЦП
	ADCSRA|=(1<<ADIE);// разрешить прерывание АЦП
}

// старт блока преобразований
void adc_start(void){
	adc_col=200;
	ADCSRA|=(1<<ADSC);// запуск преобразования
}

// проверка окончания блока преобразований, 1 - если конец, 0 - если еще нет
uint8_t adc_chek(void){
	if(adc_col) return 0;
	return 1;
}

// забрать и обнулить сумму преобразований
uint32_t adc_get_summ(void){
	uint32_t val=adc_summ;
	adc_summ=0;
	return val;
}