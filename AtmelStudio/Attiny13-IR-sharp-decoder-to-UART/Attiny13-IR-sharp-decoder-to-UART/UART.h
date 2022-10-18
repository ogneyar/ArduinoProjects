#ifndef UART_H_
#define UART_H_

#include "config.h"


void bit_bang_tx(unsigned char data);
void bit_bang_tx_str(char *str);
void uart_init();
void uart_print (unsigned int IR_block);




#endif /* UART_H_ */