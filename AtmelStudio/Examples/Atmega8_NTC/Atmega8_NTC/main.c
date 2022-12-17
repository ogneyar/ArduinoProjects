#include "main.h"

#define R1				10000.0// ������������� ��������� (r1)
#define Rt				10000.0// ����������� ������������� ���������� ��� 25�
#define B				4050.0 // ��� � ���������� (������ �������)
#define Tk				298.15 // 25+273.15 = 25� � ���������
#define MAXADC			1023.0// ������������ �������� ���
uint16_t adc;// ��� ���
float Rntc;// ��� ������� ������������� ����������
float temp;// ��� ������� �����������

// ������ ���
uint16_t adc_read(void){
	ADCSRA|=(1<<ADSC);
	while(ADCSRA&(1<<ADSC));
	return ADC;
}

int main(void)
{
	ADMUX|=(1<<MUX2) | (1<<MUX1);// ����� 6
	ADCSRA|=(1<<ADEN)| (1<<ADPS1);
	
    while (1) 
    {
		adc=adc_read();// ������ ���
		Rntc=R1/(MAXADC/adc-1);// ��������� ������������� ����������
		temp=(1 / ((log(Rntc/Rt) / B) + (1 / Tk)))- 273.15;// ��������� ����������� � �������� �������.
		_delay_ms(300);
    }
}

