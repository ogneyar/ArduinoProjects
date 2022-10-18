#include "main.h"
#include "UART.h"

//��������� ���� 8 ��� ������, �������� �������� ����., 1 ���� ���.
void uart_init(uint16_t ubrr) {

// --------- ��������� �������� ��� BAUD RATE ---------------------
UBRRH = (uint8_t)(ubrr>>8);
UBRRL = (uint8_t)ubrr;
//-----------------------------------------------------------------

//UCSRA |= (1<<U2X); // ������� �������� 

UCSRB |= (1<<TXEN); // ��������� �����������
UCSRB |= (1<<RXEN); // ��������� ���������

// ��������� �����������... �� ���������� ��������.
// UCSRC |= (1<<URSEL);
// UCSRC|=(1<<UCSZ1)|(1<<UCSZ0);

// � ���� URSEL ������ ���� 1, ���� ����� ������ ������� UCSRC, � �� ����� :)
UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); // 8 ��� ������ � �������.

//UCSRC = 0b10000110;
// ��������� �� ���������.

}





// �������� �����
void uart_send_byte(uint8_t data) {
	while (!(UCSRA & (1 << UDRE))); // �������� ������������ ������ ��������
	UDR = data; // ���������� ���� � �����, �������� ���������� �������������.
}


// �������� ������
void uart_send_str(uint8_t *s) {
	while (*s != 0) uart_send_byte(*s++);
}


// �������� ������ �� ���� ������
void uart_send_flashstr(const char *string)
{
	while (pgm_read_byte(string)!='\0')
	{
		uart_send_byte(pgm_read_byte(string));
		string++;
	}
}


// �������� ����� �� 0000 �� 9999
void uart_send_int(uint16_t c)
{
	uint8_t temp;
	c=c%10000;
	temp=c/100;
	uart_send_byte(temp/10+'0');
	uart_send_byte(temp%10+'0');
	temp=c%100;
	uart_send_byte(temp/10+'0');
	uart_send_byte(temp%10+'0');
}

// �������� ����� int �� 0 �� 65535
void uart_send_numstr(uint16_t num) {
	char str[10];
	utoa(num, str, 10);
	uart_send_str((uint8_t*)str);
}


// ������� ������� �� ����� ������
void uart_send_entr() {
	uart_send_byte(0x0d);
}

//	��������� �����
uint8_t uart_read_byte(void) {
	while(!(UCSRA&(1<<RXC)))	//	���������������, ����� ������� ��������
	{}
	return UDR;
}

