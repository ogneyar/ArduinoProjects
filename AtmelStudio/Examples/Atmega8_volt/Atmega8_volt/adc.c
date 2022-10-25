#include "adc.h"
volatile uint8_t adc_col;// ������� ��������������
volatile uint32_t adc_summ;// ���������� ��� ����� �������������� 

// ���������� ���������� ���
ISR(ADC_vect) {
	if (adc_col)// ���� ������� �� ����
	{
		adc_col--;// ���������
		adc_summ+=ADC;// �������� � ����� ��������� ��������
		ADCSRA|=(1<<ADSC);// ������ ��������������
	}
}

// ��������� ���
void adc_ini(void){
	ADMUX|=(1<<REFS0);// ����� ���������� �������� ���������� - AVCC
	ADMUX|=2; // ����� ������ 2
	//ADMUX|=(1<<ADLAR);// ������������ 8 ������� ��� ���������� � ADCH
	ADCSRA|=(1<<ADPS2);// �������� 16
	ADCSRA|=(1<<ADEN); // ��������� ���
	ADCSRA|=(1<<ADIE);// ��������� ���������� ���
}

// ����� ����� ��������������
void adc_start(void){
	adc_col=200;
	ADCSRA|=(1<<ADSC);// ������ ��������������
}

// �������� ��������� ����� ��������������, 1 - ���� �����, 0 - ���� ��� ���
uint8_t adc_chek(void){
	if(adc_col) return 0;
	return 1;
}

// ������� � �������� ����� ��������������
uint32_t adc_get_summ(void){
	uint32_t val=adc_summ;
	adc_summ=0;
	return val;
}