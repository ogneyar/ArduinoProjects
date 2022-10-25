#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t button_count;// ������� ������ 1
volatile uint8_t button2_count;// ������� ������ 2
volatile uint8_t button_clk; // ���� �����

// ���������� ���������� �� ������������ ������� 0
ISR(TIMER0_OVF_vect){
	// ����� ������ ������
	if (PINC&(1<<PC0)) // ���� �� ���� 1
	{
		if (button_count>=5 && button_count<60) button_clk=1; //���� � ������ ������� ���� ��������� ����� 1
		button_count=0;// �������� �������
	}
	else  // ����� �� ���� 0
	{
		if (button_count<61) button_count++; // ��������� �������� � ������������ 61
		if (button_count==60) button_clk=101;// ���� � �������� 60 ������� ���� �������� ����� 1
	}
	
	// ����� ������ ������
	if (PINC&(1<<PC1)) // ���� �� ���� 1
	{
		if (button2_count>=5 && button2_count<60) button_clk=2;// ���� � ������ ������� ���� ��������� ����� 2
		button2_count=0;// �������� �������
	}
	else  // ����� �� ���� 0
	{
		if (button2_count<61) button2_count++; // ��������� �������� � ������������ 61
		if (button2_count==60) button_clk=102; //���� � �������� 60 ������� ���� �������� ����� 2
	}
}

int main(void)
{
	TCCR0|=(1<<CS01) | (1<<CS00);// ������ ������� 0 � ��������� 64
	TIMSK|=(1<<TOIE0); // ��������� ���������� �� ������������ ������� 0
	
	DDRB|=(1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3);// ���� ����������� �� �����
	
	sei();//��������� ��������� �����������
	while (1)
	{
		if (button_clk) // �������� ������ �����
		{
			switch (button_clk)
			{
				case 1:// ��������� ��������� ����� 1
				PORTB^=(1<<PB0);
				break;
				
				case 101:// ��������� �������� ����� 1
				PORTB^=(1<<PB1);
				break;
				
				case 2:// ��������� ��������� ����� 2
				PORTB^=(1<<PB2);
				break;
				
				case 102:// ��������� �������� ����� 2
				PORTB^=(1<<PB3);
				break;
			}
			button_clk=0;// �������� ���� ����� � 0
		}
		
	}
}