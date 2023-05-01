#include "monitor.h"

// 8 ��� � ������, ��� �������� - ���, 1 ���� ���. ������� 9600
void uart_ini(void){
	UBRRL = (F_CPU/BAUDRATE/16-1); // ��������� �������� ������ �������
	UBRRH = (F_CPU/BAUDRATE/16-1) >> 8;
	UCSRB|=(1<<RXEN) | (1<<TXEN);// ��������� ������ ����������� � ���������
}


// �������� ������ � ����
void uart_send_str(char* str){
	uint8_t i=0;
	while (str[i])
	{
		while (!(UCSRA&(1<<UDRE))); // ���� ���� �� ����������� ������� �����������
		UDR=str[i];// ����� ������ � ������� ����������� ��� ��������
		i++;
	}
}

void uart_send_int(int16_t n){
	char buf[5];
	itoa(n, buf, 10);
	uart_send_str(buf);
}

void uart_send_float(float n){
	char buf[5];
	if (n<0)
	{
		n*=-1;
		uart_send_str("-");
	}
	uint32_t PP=n*100;
	uint16_t PPc=PP/100;
	uint8_t PPd=PP%100;
	
	utoa(PPc, buf, 10);
	uart_send_str(buf);
	uart_send_str(".");
	utoa(PPd, buf, 10);
	uart_send_str(buf);
}