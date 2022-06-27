#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

// ������� ����
uint8_t digit[]={63,6,91,79,102,109,125,7,127,111};

// ����� �� ���������
void display(uint8_t n, uint8_t dot){
	if (n<10)// ���� �������� ������ 10 �.�. �� 0 �� 9
	{
		PORTD=digit[n]; // ������� �������� n 
	} else {
		PORTD=121; // ����� ������
	}
	
	if(dot) PORTD|=(1<<7);// ���� dot �� ���� �������� �����
}

int main(void)
{
	DDRD=255;// ���� � �� �����
	
    while (1) 
    {
		// ������ ������ ��� �����
		for (uint8_t i=0; i<10; i++)
		{
			display(i,0);
			_delay_ms(500);
		}
		
		// ������ ����� � ������
		for (uint8_t i=9; i>0; i--)
		{
			display(i,1);
			_delay_ms(500);
		}
    }
}

