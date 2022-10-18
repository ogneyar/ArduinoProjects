#include "main.h"
#include "ADC.h"
#include "TM1637.h"

		
// медианный фильтр из 3-х значений
uint16_t median_3(uint16_t a, uint16_t b, uint16_t c) {
	uint16_t value;
	if ((a <= b) && (a <= c)) {
		value = (b <= c) ? b : c;
	}
	else {
		if ((b <= a) && (b <= c)) {
			value = (a <= c) ? a : c;
		}
		else {
			value = (a <= b) ? a : b;
		}
	}
	return value;
}
//------------------------------------------------------

// Uизм = ((Uref/1023)*adc)*k
// k=(47k+(pot10k+3.3k))/(pot10k+3.3k)
int main(void)
{
	adc_setup_VCC();
	uint32_t adc_sum=0;// сумма всех измерений
	uint16_t adc_buf[3];// под три замера АЦП
	uint16_t adc_val=0; // итоговое значение АЦП (среднее от суммы средне медианных)
	uint16_t Volt=0; // итоговое в вольтах
    while (1) 
    {
		// версия 1
		for (uint8_t i=0; i<200; i++)
		{

			adc_buf[0]=adc_read16();
			adc_buf[1]=adc_read16();
			adc_buf[2]=adc_read16();

			adc_sum=adc_sum + median_3(adc_buf[0], adc_buf[1], adc_buf[2]);// складываем все значения
		}
		adc_val= adc_sum/200; // вычислям среднее
		adc_sum=0;
		Volt=(3*adc_val);// считаем сколько это в вольтах x100
		indication(Volt);

    }
}

