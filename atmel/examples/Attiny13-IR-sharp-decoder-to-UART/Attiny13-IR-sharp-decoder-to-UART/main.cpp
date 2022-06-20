#include "config.h"
#include "UART.h"
#include "IR.h"


int main(void)
{



unsigned int IR_block=0;// переменная пакета переданного по ИК

uart_init(); // инициализируем уарт
IR_init(); // инит ИК

    while (1) 
    {
		
			
		if (!(IR_PIN & 1<<IR)) // если сигнал 0 начинаем читать посылку
		 { 
			IR_block = IR_read(); // читаем посылку
			uart_print (IR_block); // отправляем в уарт


		}

    }
}

