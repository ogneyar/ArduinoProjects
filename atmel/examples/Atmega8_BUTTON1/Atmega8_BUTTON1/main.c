#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t button_count;// ������� ������
volatile uint8_t button_clk; // ���� �����

// ���������� ���������� �� ������������ ������� 0
ISR(TIMER0_OVF_vect){
	if (PINC&(1<<PC0)) // ���� �� ���� 1
	{
		button_count=0;// �������� �������
	}
	else  // ����� �� ���� 0
	{
		if (button_count<6) button_count++; // ��������� �������� � ������������ 6
		if (button_count==5) button_clk=1; // ������� ���� ����� ��� �������� �������� = 5
	}
}

int main(void)
{
	TCCR0|=(1<<CS01) | (1<<CS00);// ������ ������� 0 � ��������� 64
	TIMSK|=(1<<TOIE0); // ��������� ���������� �� ������������ ������� 0
	
	DDRB|=(1<<PB0);// ��� ���������� �� �����
	
	sei();//��������� ��������� �����������
	while (1)
	{
		if (button_clk) // �������� ������ �����
		{
			PORTB^=(1<<PB0); // ��������� �����
			button_clk=0;// �������� ���� ����� � 0
		}
		
	}
}