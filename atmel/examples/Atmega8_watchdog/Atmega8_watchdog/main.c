#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

// �������� ������
void WDT_on(void){
	/* ������ ������� */
	asm("wdr");
	/* ��������� ��������� ������� */
	WDTCR |= (1<<WDCE) | (1<<WDE);
	/* �������� ������ �� ����� ����� 2 ������� */
	WDTCR = (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
}

// ��������� ������
void WDT_off(void){
	/* ������ ������� */
	asm("wdr");
	/* ��������� ��������� ������� */
	WDTCR |= (1<<WDCE) | (1<<WDE);
	/* ��������� ������ */
	WDTCR = 0x00;
}
	
int main(void)
{
	DDRB|=(1<<PB0) | (1<<PB5);
	
	// ������ �������
	PORTB^=(1<<PB0);
	_delay_ms(500);
	PORTB^=(1<<PB0);
	WDT_on();
    while (1) 
    {
		// ������� �������
		PORTB^=(1<<PB5);
		_delay_ms(1000);
		asm("wdr");// ����� �������
		_delay_ms(1500);
		asm("wdr");// ����� �������
	}
}

