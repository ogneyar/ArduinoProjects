#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// ���������� ���������� INT1
ISR(INT1_vect){
	// ����� �� ���
}


// �������� ������ ��
void work(void){
	for (uint8_t i=0; i<100;i++)
	{
		PORTB^=(1<<PB0);
		_delay_ms(100);
	}
}

int main(void)
{
	MCUCR|=(1<<SE);// ��������� ���
	MCUCR|=(1<<SM1); // ����� ������ ��� Power-down 
	
	GICR|=(1<<INT1); // ��������� ���������� INT1
	// ���� ISC11, ISC10 ������ ���� � ���� ��� ����������� ��.
	
    DDRB|=(1<<PB0);// ��� �� �����
	
	sei(); // ��������� ��������� ����������
    while (1) 
    {
		work();// ��������
		asm("sleep");// ���� � ���
    }
}

