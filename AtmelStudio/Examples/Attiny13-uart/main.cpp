#define F_CPU 1200000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


#define uart_DDR    DDRB
#define uart_PORT    PORTB
#define uart_PIN PB1 // PB1 � RXD
#define uart_delay  31 //  ��� ������� ������ 1.2 Mhz : 31 - 4800 ���, 62 - 2400 ���, 124 -1200 ���, 248 - 600 ���


//----------- ������� �������� ����� ------------------------
void bit_bang_tx(unsigned char data) {
	unsigned char i;
	uart_PORT &=~ (1<<uart_PIN);         // ����� ���
	TCNT0 = 0;
	while (TCNT0 < uart_delay); // ������� 
	for (i = 0; i < 8; i++) { // �������� � �������� ����
		if (data & (0x01 << i)) uart_PORT |= (1<<uart_PIN);
		else uart_PORT &=~ (1<<uart_PIN);
		while (TCNT0 < uart_delay); // �������
	}
	uart_PORT |= (1<<uart_PIN);        // ���� ���
	while (TCNT0 < uart_delay); // ������� 
}
//-----------------------------------------------------------

//------------- ������ �������� ������-----------------------
void bit_bang_tx_str(char *str) {
	while (*str) bit_bang_tx(*str++);
}
//------------------------------------------------------------


//-------------- ������ �������������------------------------
void uart_init() {
	uart_DDR |= (1<<uart_PIN);
	uart_PORT |= (1<<uart_PIN);
}
//-----------------------------------------------------------


int main(void) {
	
	TCCR0A = 0x02;  // ������ ������� � ����� CTC
	TCCR0B = 0x02;  // �������� �� 8
	OCR0A  = uart_delay; // ������� ���������
	
	unsigned char number=0; // �������� ������
	char str[10]; // ������ ��� ������.
	
	uart_init(); // �������������� ����
	
	while (1) {
		

		utoa(number, str, 10); // ������������ ������ � ������
		bit_bang_tx_str((char *)str); // ���������� ������ � ������ 
		bit_bang_tx_str("\r\n"); // ������� �������� �� ����� ������
		bit_bang_tx_str("� ��� ���� � ����"); // �������� ��������� ���������� � ����
		bit_bang_tx_str("\r\n"); // ����� ������� �� ����� ������
		number++; // ����������� ���������� �� 1

		_delay_ms(1000); // �������� 1 �������.
	}
}
