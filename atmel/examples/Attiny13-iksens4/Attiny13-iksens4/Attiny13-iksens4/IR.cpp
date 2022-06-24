#include "main.h"
#include "IR.h"



void IR_ini(void) {
	// ����� ���  38 ��� ��� 9.6���
	//������� �������=F_CPU / 2*��������*(1+OCR0A)

	
	GIMSK|=(1<<PCIE); // ��������� ���.
	PCMSK|=(1<<PCINT1); // PCINT0 ��� PB1 ���.
	
	TCCR0A |=(1<<WGM01); // ����� CTC, ����� ��� ����������
	//TCCR0A |= (1<<COM0A0); // ��������� ������ OC0A �������� �� ��������������� ��� ��������� ��������� TCNT0 � OCR0A.
	TCCR0B |= (1<<CS00);  // ��� ��������
	OCR0A = 126; // ������� ���������
	
	TIMSK0 |= (1<< OCIE0A);// ���������� �� ���������� ����
	
	DDRB|=(1<<TX); // ��� �����������
	DDRB&=~(1<<RX); // ��� ���������

}

//--------- �������� �� ----------------------
void IRR_0 (void) {
	TCCR0A |= (1<<COM0A0);
	_delay_us(100);
	TCCR0A &=~(1<<COM0A0);
	_delay_us(500);
}

void IRR_1(void) {
	TCCR0A |= (1<<COM0A0);
	_delay_us(500);
	TCCR0A &=~(1<<COM0A0);
	_delay_us(500);
}


void IRR_code(uint8_t code) {
	uint8_t a,i;
	a=1; // 0b0000001
	for (i=0; i<8; i++)
	{
		if ((code&a)==0) {
			IRR_0();	//����
			}  else {
			IRR_1(); //�������
		}
		a=a<<1;
	}
}
//-------------------------------------------


// ������ �������
uint8_t status(uint8_t cod, uint8_t null)
{
	static uint8_t COUNT_ok; // ������� ���������
	static uint8_t COUNT_er; // ������� �� ���������
	if (null) // ��������� ��������
	{
		COUNT_er=0;
		COUNT_ok=0;
		return 0;
	}
	
	if (cod!=IR_CODE)
	{
		if (COUNT_er<OTR_OFF) { COUNT_er++;}
		} else {
		if (COUNT_ok<OTR_ON) {COUNT_ok++; COUNT_er=0;}
	}
	
	if (COUNT_er==OTR_OFF)
	{
		COUNT_ok=0;
		COUNT_er=0;
	}
	
	if (COUNT_ok==OTR_ON)
	{
		return 1;
	}
	
	return 0;
}
//-----------------------------------------------------------------------------------------------------------

//--------------�������� �������� �� ����----------------------
void IR_0 (void) {
	PORTB|=(1<<TX);
	_delay_us(100);
	PORTB&=~(1<<TX);
	_delay_us(500);
}

void IR_1(void) {
	PORTB|=(1<<TX);
	_delay_us(500);
	PORTB&=~(1<<TX);
	_delay_us(500);
}


void IR_code(uint8_t code) {
	uint8_t a,i;
	a=1; // 0b0000001
	for (i=0; i<8; i++)
	{
		if ((code&a)==0) {
			IR_0();	//����
			}  else {
			IR_1(); //�������
		}
		a=a<<1;
	}
}
//----------------------------------------------------