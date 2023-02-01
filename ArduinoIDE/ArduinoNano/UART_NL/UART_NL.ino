
// Nano, LGT8F328


// #define F_CPU 16000000UL // для Nano
// #define F_CPU 32000000UL // для LGT8F328

// 8 бит в пакете, бит четности - нет, 1 стоп бит. битрейт 115200 - по умолчанию
void uart_ini(uint32_t baud = 115200)
{
	uint16_t ubrr = ( F_CPU / (8 * baud) ) - 1; // (8 * x) при U2X0 в 1, (16 * x) при U2X0 в 0
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	UCSR0A |= (1 << U2X0);// бит в 1
  
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // разрешить работу передатчика и приемника
  UCSR0C |= (1 << UPM01) | (1 << UCSZ01) | (1 << UCSZ00); // UPM01 - Enabled, Even Parity // UCSZ01 = 1 и UCSZ00 = 1 по умолчанию
}


// отправка строки в порт
void uart_send(char* str)
{
	uint8_t i = 0;
	while (str[i])
	{
		while ( ! (UCSR0A & (1 << UDRE0)) ); // ждем пока не освободится регистр передатчика
		UDR0 = str[i];// пишем данные в регистр передатчика для отправки 
		i++;
	}
}

// чтение и выполнение команд из порта
void uart_read_com(void)
{
	uint8_t val;
	if (UCSR0A & (1 << RXC0))
	{
		val = UDR0;
		if (val == 48)
		{
			PORTB &= ~(1 << PB5);
			uart_send("\n\r");
			uart_send("LED выкл");
			uart_send("\n\r");
		}
		
		if (val == 49)
		{
			PORTB |= (1 << PB5);
			uart_send("\n\r");
			uart_send("LED вкл");
			uart_send("\n\r");
		}
	}
}



int main(void)
// void setup()
{ 
#if defined(__LGT8F__) // для LGT8F328
		// prescaler settings
		CLKPR = 0x80;
		CLKPR = 0x00;	
#endif	

	DDRB |= (1 << PB5);// пин LED на выход 
	uart_ini(115200);	// инициализация UART

	uart_send("Hello Чел!!!\r\n\r\n");

	uart_send("Жми 1 для включения LED\r\n"); 
	uart_send("Жми 0 для выключения\r\n"); 

  while (1) uart_read_com();// ждем и выполняем команды

	return 0;
}

// void loop() 
// {
//   	uart_read_com();// ждем и выполняем команды
// }

//