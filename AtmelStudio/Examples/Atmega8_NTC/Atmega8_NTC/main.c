#include "main.h"

#define R1				10000.0// сопротивление резистора (r1)
#define Rt				10000.0// номинальное сопротивление термистора при 25С
#define B				4050.0 // коф В термистора (смотри дадашит)
#define Tk				298.15 // 25+273.15 = 25С в кельвинах
#define MAXADC			1023.0// максимальное значение ацп
uint16_t adc;// под ацп
float Rntc;// под текущее сопротивление термистора
float temp;// под текущую температуру

// чтение ацп
uint16_t adc_read(void){
	ADCSRA|=(1<<ADSC);
	while(ADCSRA&(1<<ADSC));
	return ADC;
}

int main(void)
{
	ADMUX|=(1<<MUX2) | (1<<MUX1);// канал 6
	ADCSRA|=(1<<ADEN)| (1<<ADPS1);
	
    while (1) 
    {
		adc=adc_read();// читаем ацп
		Rntc=R1/(MAXADC/adc-1);// вычисляем сопротивление термистора
		temp=(1 / ((log(Rntc/Rt) / B) + (1 / Tk)))- 273.15;// вычисляем температуру в градусах цельсия.
		_delay_ms(300);
    }
}

