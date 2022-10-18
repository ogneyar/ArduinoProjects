#include "main.h"
#include "UART.h"

const char err[] PROGMEM = "errorko";

int main(void)
{
	DDRC |= (1<<0);
	uint16_t n=0;
	uint8_t error[]="error";
	uint8_t press[]="press number - ";
	uart_init(MYUBRR);

	_delay_ms(1000);
	uart_send_str((uint8_t*)"UART led control. ");
	
	uart_send_entr();
    while (1) 
    {
		if(UCSRA&(1<<RXC))			//	если пришёл байт по UART
		{
			if ('y'==uart_read_byte()) 
			{
				PORTC^=(1<<0);
				uart_send_str(press);
				uart_send_numstr(n++);
				uart_send_entr();
			}
			else {
				uart_send_str(error);
				//uart_send_flashstr(err);
				uart_send_entr();
			}

		}


    }
}

