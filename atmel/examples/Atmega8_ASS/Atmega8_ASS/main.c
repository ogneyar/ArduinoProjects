#define F_CPU	1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

ISR(TIMER2_OVF_vect){

}

int main(void)
{
	DDRB|=(1<<PB0); // ��� �� �����
	//------- ����������� ����� ������� 2----------------
	//TIMSK&=~((1<<OCIE2)|(1<<TOIE2));//1. ��������� ����������, � TIMSK �������� ���� OCIE2 and TOIE2
	ASSR|=(1<<AS2);//2. �������� ����������� �����, � ASSR ������� ��� AS2 
	
	//3. �������� �������� TCNT2, OCR2, and TCCR2, ��������� ������
	TCNT2=0;
	OCR2=0;
	//TCCR2=(1<<CS22) | (1<<CS20);// �������� 128
	//TCCR2=(1<<CS22);// �������� 64
	TCCR2= (1 << CS22)|(1 << CS21)|(1<<CS20);// ������������ �� 1024
	/*
	!!!!! ���� ���� ������ !!!!!
	TCCR2 ����� �������� � ����������� ����� ����� ��������� ��������� ��������.
	������ ����������� ���� "TCCR2|=(1<<���1) | (1<<���2);" ������� 
	����� ��������� ������� ������������ "TCCR2=(1<<���1) | (1<<���2);"
	*/
	
	while(ASSR!=8);//4. ����� ������ ������ TCN2UB, OCR2UB, and TCR2UB � �������� ASSR
	TIFR|=(1<<OCF2)|(1<<TOV2);//5. �������� ����� ���������� � TIFR ���� OCF2, TOV2
	TIMSK|=(1<<TOIE2); //6. ��������� ���������� ���� �����, � TIMSK
	//---------------------------------
	sei();// ��������� ��������� ����������
	set_sleep_mode(SLEEP_MODE_PWR_SAVE); // ����� ��� power save
    while (1) 
    {
		PORTB|=(1<<PB0);
		_delay_ms(300);
		PORTB&=~(1<<PB0);
		
		if (!(PINB&(1<<PB1)))
		{
			OCR2=1;//1. �������� ���-�� � �������� TCCR2, TCNT2, ��� OCR2
			while (ASSR != 8);//2.����� ������ ������ TCN2UB, OCR2UB, and TCR2UB � �������� ASSR
			sleep_enable();//3. ���� 
			sleep_cpu(); //	� ���
			} else {
			_delay_ms(300);
		}
    }
}

