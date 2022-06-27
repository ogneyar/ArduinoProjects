#include "main.h"
#include "IR.h"
#define OUT PB2 // ��� ������ ����������



volatile uint16_t count=0; // ������� ���������� �� �������
volatile uint8_t signal=0; // ��������� ��� ��������� �������
volatile uint16_t start; // ��������� �������� count
volatile uint16_t dlinna; // ������ ������� � ����� count
volatile uint8_t code; // ���


// ����������� �� �������
ISR (TIM0_COMPA_vect) {
	count++; // ��� ���
	if (count>=10000) // �������� ��� ���������, ��� 5000 �������� �� ������������ ������
	{
		count=0;
	}
}


// ���������� �� ������� �� ���������
ISR (PCINT0_vect) {
	if (!(PINB&(1<<RX)))
	{
		start=count; // ������ �������
	} else {
		dlinna=count-start; // ����� �������
		if (dlinna>=50) // ���� ������ � ���������
		{
			code|=(1<<signal);
		}
		signal++;
	}
}


	
int main(void)
{
	DDRB|=(1<<OUT); // ����� 
	
	uint8_t stat=0; // ������ �������
	uint8_t trigger=0; // ������� ����
	uint8_t mode=0; // ����� ������
	IR_ini(); // ��������� ������ � ������� ������������� �������, ��� � ����
	sei();// ��������� ����������
	
//-----------������ �����----------
	if (!(PINB&(1<<PB3)))
	{
		mode|=(1<<0);
	}
	if (!(PINB&(1<<PB4)))
	{
		mode|=(1<<1);
	}
//----------------------------------

    while (1) 
    {
		if (!count) // ����� ���� - ���� � ��������� ������
		{
			signal=0; // 
			code=0;	//
			//IR_code(IR_CODE);// ��� ��������
			IRR_code(IR_CODE); // ��� ��������
			stat=status(code, 0);
		}

//-------- ��������� �����������--------------
		if (mode==0)
		{
			if (stat)
			{
				PORTB|=(1<<OUT); // �������
			} else
			{
				PORTB&=~(1<<OUT); // ��������
			}
		}
//------------------------------		
		
		
// -------------�������	-------------
		if (mode==1)
		{
			if (stat)
			{
				if (trigger!=stat) 
				{
					PORTB^=(1<<OUT);// �������������
				}
			}
		trigger=stat;
		}
//--------------------------------

// ---------������������ 10 ���------------------
		if (mode==2)
		{
			if (stat)
			{
				cli();// ���������� ����.
				PORTB|=(1<<OUT); // ��������� 
				_delay_ms(10000); // �����
				PORTB&=~(1<<OUT); // ����������
				status(1, 1); // ����� �������� ������ �������
				code=0; // ��������� 
				stat=0; // ����� �������
				count=0; // ����� ��������
				sei(); // ���������� ���.
			}
		}
//---------------------------------
		
// ---------������������ 60 ���------------------
		if (mode==3)
		{
			if (stat)
			{
				cli();// ���������� ����.
				PORTB|=(1<<OUT); // ���������
				_delay_ms(60000); // �����
				PORTB&=~(1<<OUT); // ����������
				status(1, 1); // ����� �������� ������ �������
				code=0; // ���������
				stat=0; // ����� �������
				count=0; // ����� ��������
				sei(); // ���������� ���.
			}
		}
//---------------------------------

				
    }//w
}//m
