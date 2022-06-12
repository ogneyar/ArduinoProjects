#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

// 8 ��� � ������, ��� �������� - ���, 1 ���� ���. ������� 9600
void uart_ini(void){
	UBRRL=12;
	UCSRA|=(1<<U2X);// ��� � 1
	UCSRB|=(1<<RXEN) | (1<<TXEN);// ��������� ������ ����������� � ���������
}


// �������� ������ � ����
void uart_send(char* str){
	uint8_t i=0;
	while (str[i])
	{
		while (!(UCSRA&(1<<UDRE))); // ���� ���� �� ����������� ������� �����������
		UDR=str[i];// ����� ������ � ������� ����������� ��� �������� 
		i++;
	}
}

// ������ � ���������� ������ �� �����
void uart_read_com(void){
	uint8_t val;
	if (UCSRA&(1<<RXC))
	{
		val=UDR;
		if (val==48)
		{
			PORTB&=~(1<<PB0);
			uart_send("\n\r");
			uart_send("LED OFF");
			uart_send("\n\r");
		}
		
		if (val==49)
		{
			PORTB|=(1<<PB0);
			uart_send("\n\r");
			uart_send("LED ON");
			uart_send("\n\r");
		}
	}
}

int main(void)
{
	DDRB|=(1<<PB0);// ��� �� �����
	uart_ini();	// ������������� ����

    while (1) 
    {
		uart_read_com();// ���� � ��������� �������
    }
}

