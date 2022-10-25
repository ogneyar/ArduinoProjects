/*
 * attiny13-IR-send.cpp
 *
 * Created: 12.11.2017 22:05:52
 * Author : andrey
 */ 
#define F_CPU 1200000UL
#include <avr/io.h>
#include <util/delay.h>

// ������ �������� ����
void IR_sendbit(char bit)
{

	PORTB &= ~(1<<PB0); // ������ �� ���� 0
	_delay_us(320); // ���� 320 ���
	PORTB |=(1<<PB0); // ������ �� ���� 1
	if(bit) { _delay_us(1680); } // ���� ���=1 �� ���� 1680 ���
		else { _delay_us(680); } // ���� 0 �� ���� 680 ���

}

// ������� �������� ������� ������.
void IR_send(char adress, char command) {

// �������� ������
	for(char i=0; i<5; i++)//�������� �������� ������ ��� 
	{
		if((adress & (1<<i)) == 1<<i)//�������� 1
		IR_sendbit(1);
		else //�������� 0
		IR_sendbit(0);
	}
	
// �������� �������
	
		for(char i=0; i<8; i++)//�������� �������� ������ ��� 
		{
			if((command & (1<<i)) == 1<<i)//�������� 1
			IR_sendbit(1);
			else //�������� 0
			IR_sendbit(0);
		}
		
// �������� ��� ���������� =1
		IR_sendbit(1);
//�������� ��� �������� =0
		IR_sendbit(0);
			PORTB &= ~(1<<PB0); // ������ �� ���� 0
			_delay_us(320); // ���� 320 ���
		PORTB |= (1<<PB0);
		
_delay_ms(40);

	// �������� ������
	for(char i=0; i<5; i++)//�������� �������� ������ ���
	{
		if((adress & (1<<i)) == 1<<i)//�������� 1
		IR_sendbit(1);
		else //�������� 0
		IR_sendbit(0);
	}
	// �������� �������
	
	for(char i=0; i<8; i++)//�������� �������� ������ ���
	{
		if((command & (1<<i)) == 1<<i)//�������� 0
		IR_sendbit(0);
		else //�������� 1
		IR_sendbit(1);
	}
		
		// �������� ��� ���������� =0
		IR_sendbit(0);
		//�������� ��� �������� =1
		IR_sendbit(1);
		PORTB &= ~(1<<PB0); // ������ �� ���� 0
		_delay_us(320); // ���� 320 ���
		PORTB |= (1<<PB0);

}



int main(void)
{
	
			DDRB|= (1<<PB0);
			PORTB |= (1<<PB0);
			
			char adress=0x03;
			char command=0x11;
_delay_ms(2000);
    /* Replace with your application code */
    while (1) 
    {
		IR_send( adress,  command);
		_delay_ms(5000);
    }
}

