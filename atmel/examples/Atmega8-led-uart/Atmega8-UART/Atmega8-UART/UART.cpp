#include "main.h"
#include "UART.h"

//настройка уарт 8 бит данных, проверка четности откл., 1 стоп бит.
void uart_init(uint16_t ubrr) {

// --------- настройка скорости ака BAUD RATE ---------------------
UBRRH = (uint8_t)(ubrr>>8);
UBRRL = (uint8_t)ubrr;
//-----------------------------------------------------------------

//UCSRA |= (1<<U2X); // двойная скорость 

UCSRB |= (1<<TXEN); // включение передатчика
UCSRB |= (1<<RXEN); // включение приемника

// нерабочая конструкция... по загадочным причинам.
// UCSRC |= (1<<URSEL);
// UCSRC|=(1<<UCSZ1)|(1<<UCSZ0);

// в бите URSEL должна быть 1, если хотим читать регистр UCSRC, а мы хотим :)
UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); // 8 бит данных в посылке.

//UCSRC = 0b10000110;
// остальное по умолчанию.

}





// отправка байта
void uart_send_byte(uint8_t data) {
	while (!(UCSRA & (1 << UDRE))); // Ожидание освобождения буфера отправки
	UDR = data; // записывает байт в буфер, отправка начинается автоматически.
}


// Отправка строки
void uart_send_str(uint8_t *s) {
	while (*s != 0) uart_send_byte(*s++);
}


// отправка строки из флэш памяти
void uart_send_flashstr(const char *string)
{
	while (pgm_read_byte(string)!='\0')
	{
		uart_send_byte(pgm_read_byte(string));
		string++;
	}
}


// Отправка числа от 0000 до 9999
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

// отправка числа int от 0 до 65535
void uart_send_numstr(uint16_t num) {
	char str[10];
	utoa(num, str, 10);
	uart_send_str((uint8_t*)str);
}


// перевод каретки на новую строку
void uart_send_entr() {
	uart_send_byte(0x0d);
}

//	Получение байта
uint8_t uart_read_byte(void) {
	while(!(UCSRA&(1<<RXC)))	//	Устанавливается, когда регистр свободен
	{}
	return UDR;
}

