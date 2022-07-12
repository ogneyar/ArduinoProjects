#ifndef UART_H_
#define UART_H_

#define PRESCALL 16 // 16 (U2X = 0) или 8 если скорость двойная (U2X = 1).
#define BAUD 9600 // скорость
#define MYUBRR F_CPU/PRESCALL/BAUD-1 // расчет значения для регистра UBRR из даташита... ( у меня не пашет... причины загадочны)

void uart_init(uint16_t ubrr);
void uart_send_byte(uint8_t data);
void uart_send_str(uint8_t *s);
void uart_send_flashstr(const char *string);
void uart_send_int(uint16_t c);
void uart_send_numstr(uint16_t num);
void uart_send_entr();

uint8_t uart_read_byte(void);

#endif /* UART_H_ */