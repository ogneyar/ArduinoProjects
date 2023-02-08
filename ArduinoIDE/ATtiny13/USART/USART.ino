#define F_CPU 9600000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


#define uart_DDR    DDRB
#define uart_PORT   PORTB
#define uart_PIN    PB4 // PB4 к RXD
#define BAUD        9600 // 
#define uart_delay  ( ( F_CPU / 8 / BAUD ) - 1 ) // 124


//----------- функция отправки байта ------------------------
void bit_bang_tx(unsigned char data) {
	unsigned char i;
	uart_PORT &=~ (1<<uart_PIN);         // старт бит
	TCNT0 = 0;
	while (TCNT0 < uart_delay); // ожидаем 
	for (i = 0; i < 8; i++) { // отправка с младщего бита
		if (data & (0x01 << i)) uart_PORT |= (1<<uart_PIN);
		else uart_PORT &=~ (1<<uart_PIN);
		while (TCNT0 < uart_delay); // ожидаем
	}
	uart_PORT |= (1<<uart_PIN);        // стоп бит
	while (TCNT0 < uart_delay); // ожидаем 
}
//-----------------------------------------------------------

//------------- фунция отправки строки-----------------------
void bit_bang_tx_str(char *str) {
	while (*str) bit_bang_tx(*str++);
}
//------------------------------------------------------------


//-------------- просто инициализация------------------------
void uart_init() {
	uart_DDR |= (1<<uart_PIN);
	uart_PORT |= (1<<uart_PIN);
}
//-----------------------------------------------------------


int main(void) {
	
	TCCR0A = 0x02;  // таймер вкючаем в режим CTC
	TCCR0B = 0x02;  // делитель на 8
	OCR0A  = uart_delay; // регистр сравнения
	
	unsigned char number=0; // имитация данных
	char str[10]; // массив для строки.
	
	uart_init(); // инициализируем уарт
	
	while (1) {
		

		utoa(number, str, 10); // конвертируем данные в строку
		bit_bang_tx_str((char *)str); // отправляем данные в сериал 
		bit_bang_tx_str("\r\n"); // символы перехода на новую строку
		bit_bang_tx_str("я шлю всех в порт"); // отправка текстовой информации в порт
		bit_bang_tx_str("\r\n"); // снова переход на новую строку
		number++; // увеличиваем переменную на 1

		_delay_ms(1000); // задержка 1 секунда.
	}
}
