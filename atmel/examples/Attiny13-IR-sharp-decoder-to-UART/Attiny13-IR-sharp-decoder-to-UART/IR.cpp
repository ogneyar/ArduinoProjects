#include "IR.h"

void IR_init() {
		IR_DDR &= ~(1<<IR_PIN);
		IR_PORT &= ~(1<<IR_PIN);
}

unsigned int IR_read() {
	
	unsigned char time_IR; // переменная хранения времени пауз
	bool IR_bit; // переменная для считанного бита
	unsigned int IR_block=0; // переменная для хранения всего принятого блока.
	for ( char i=0; i<15; i++) {
		
		time_IR=0;            // обнуляем тайминг
		while(!(IR_PIN & 1<<IR)) { //ждем пока шина поднимиться в 1
			_delay_us(1);
			
		}
		while ((IR_PIN & 1<<IR)) { // пока шина 1 увеличиваем тайминг на 1, каждые 10 мкс
			
			_delay_us(10);
			time_IR++;
			if (time_IR>250) break; // если тайминг более 1680	мкс значит случился конец передачи
		}
		
		if (time_IR < 70) IR_bit=0; // если тайминг меньше 70 значит 0
		else IR_bit=1; // иначе  1
		IR_block |=IR_bit<<i; // пишем бит в переменную


	}
	return IR_block;
}