#include "ADC.h"


void adc_setup (void)
{
// 	ADMUX |= (1 << MUX1); // устанавливаем как вход АЦП ножку PB4 ака ADC2
// 	ADMUX |= (1 << ADLAR);//
	ADMUX=34;
	
	
// 	// Установка предделителя на 64 и разрешение АЦП
// 	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADEN);
	ADCSRA=134;
}

uint8_t adc_read (void)
{
	ADCSRA |= (1 << ADSC);// Запуск измерений
	while (ADCSRA & (1 << ADSC));// Ожидание окончания измерений т.е. пока ADCS не станет=0 ждем.
	return ADCH; // функция возвращает данные из ADCH
}

uint8_t adc_bt2(void){
	uint8_t dump;
	dump=adc_read();
	if (dump>206) { return 3;}
	if (dump>156) { return 1;}
	if (dump>100) {	return 0;}
	if (dump>50) { return 2;}
	if (dump>=0) { return 4;}
}

uint16_t change2(uint16_t n, uint8_t znak) {
	uint8_t m=1;
	uint8_t adc;
	while (m)
	{
		adc=adc_bt();
		if (adc==0)
		{
			_delay_ms(10);
			m++;
		}
		if (adc==1)
		{
			n++;
			_delay_ms(500);
		}
		
		if (adc==3)
		{
			n++;
			_delay_ms(100);
		}
		if (adc==2)
		{
			n--;
			_delay_ms(500);
		}
		if (adc==4)
		{
			n--;
			_delay_ms(100);
		}
		if (n>999 || n<1)
		{
			n=1;
		}
		indication(n, znak);
	}
	return n;
}


signed char adc_bt(void){
	uint8_t dump;
	dump=adc_read();
// 	if (dump>170) { return 1;}
// 	if (dump>85) { return 0;}
// 	if (dump>=0) { return -1;}
	if (dump>206) { return 10;}
	if (dump>156) { return 1;}
	if (dump>100) {	return 0;}
	if (dump>50) { return -1;}
	if (dump>=0) { return -10;}
}

uint16_t change(uint16_t n, uint8_t znak) {
	uint8_t m=1;
	signed char adc;
	while (m)
	{
		indication(n, znak);
		adc=adc_bt();
		if (adc==0)
		{
			_delay_ms(10);
			m++;
		} else {
			m=1;
			n+=adc;
			if (n>999 || n<1)
			{
				n=1;
			}
			indication(n, znak);
			_delay_ms(300);
		}

		
		
	}
	return n;
}