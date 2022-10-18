#include "main.h"
#include "ADC.h"
#include "TM1637.h"

		
// ��������� ������ �� 3-� ��������
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

// U��� = ((Uref/1023)*adc)*k
// k=(47k+(pot10k+3.3k))/(pot10k+3.3k)
int main(void)
{
	adc_setup_VCC();
	uint32_t adc_sum=0;// ����� ���� ���������
	uint16_t adc_buf[3];// ��� ��� ������ ���
	uint16_t adc_val=0; // �������� �������� ��� (������� �� ����� ������ ���������)
	uint16_t Volt=0; // �������� � �������
    while (1) 
    {
		// ������ 1
		for (uint8_t i=0; i<200; i++)
		{

			adc_buf[0]=adc_read16();
			adc_buf[1]=adc_read16();
			adc_buf[2]=adc_read16();

			adc_sum=adc_sum + median_3(adc_buf[0], adc_buf[1], adc_buf[2]);// ���������� ��� ��������
		}
		adc_val= adc_sum/200; // �������� �������
		adc_sum=0;
		Volt=(3*adc_val);// ������� ������� ��� � ������� x100
		indication(Volt);

    }
}

