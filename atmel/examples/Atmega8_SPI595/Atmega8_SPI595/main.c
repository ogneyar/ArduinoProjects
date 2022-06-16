#include <avr/io.h>

#define SS		PB2
#define MOSI	PB3
#define SCK		PB5

void spi_ini(void) {
	DDRB|=(1<<SS) | (1<<MOSI) | (1<<SCK);
	PORTB|=(1<<SS);
	
	SPCR|=(1<<SPE);// разрешить работу SPI
	SPCR|=(1<<MSTR); // режим мастера
}

void spi_595(uint8_t data){
	PORTB&=~(1<<SS);// начало работы
	
	SPDR=data; // передача.
	while(!(SPSR&(1<<SPIF)));// ожидание конца передачи
	
	PORTB|=(1<<SS);// конец работы
}

int main(void)
{
	spi_ini();
	spi_595(0b00001111);
	spi_595(0b11110000);
    while (1) 
    {
		
    }
}

