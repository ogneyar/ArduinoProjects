#include <avr/io.h>
#include <avr/interrupt.h>

// �������������� ��� � ��� ������� ������
uint8_t button_code(uint8_t adc){
	if (adc>200) return 0;// ������ �� ������
	if (adc>160) return 4;// ������ 4-� ������ 
	if (adc>110) return 3;// 3-�
	if (adc>30) return 2;// 2-�
	if (adc>=0) return 1;// 1-�
}

uint8_t button_old;// ��� �������� ����������� ���������
uint8_t button_count;// �������
volatile uint8_t button_clk;// ������ �����

// ���������� ���������� �� ��������� �������������� ��� ~ 600��
ISR(ADC_vect){
	uint8_t button=button_code(ADCH);
	if (button!=button_old)// ���������� ������� � ���������� ���������
	{
		button_count=0;// �������� ������� � ����
	} 
	else
	{
		if (button_count<255) button_count++; // ��������� ��������
		if (button_count==30) button_clk=button;// ���� �������� �� 30 ������� ������ �����
	}
	
	button_old=button;// �������� ������� �������� ��� ���������� ����������
}

int main(void)
{
	// ��������� ���
	ADMUX|=(1<<ADLAR); // ��������� �������������� - 8 ������� ��� � ADCH
	// ��������� ������ ���, ����� ��������������, free running mode, ��������� ���������� ���, ������������ �������� 128
	ADCSRA|=(1<<ADEN) | (1<<ADSC) | (1<<ADFR) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
	//-----------------------------------------------------------------------
	
	DDRD|=(1<<PD0) | (1<<PD1) | (1<<PD2) | (1<<PD3);// ���� ����������� �� �����
	sei();// ��������� ��������� ����������
    while (1) 
    {
		if (button_clk)// ���� ������ �� ����
		{
			switch (button_clk)// ������������ ����
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
			button_clk=0;// �������� ������ � ����
		}
    }
}

