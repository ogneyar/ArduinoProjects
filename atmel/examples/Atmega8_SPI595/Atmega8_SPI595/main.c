#include <avr/io.h>

#define SS		PB2
#define MOSI	PB3
#define SCK		PB5

void spi_ini(void) {
	DDRB|=(1<<SS) | (1<<MOSI) | (1<<SCK);
	PORTB|=(1<<SS);
	
	SPCR|=(1<<SPE);// ��������� ������ SPI
	SPCR|=(1<<MSTR); // ����� �������
}

void spi_595(uint8_t data){
	PORTB&=~(1<<SS);// ������ ������
	
	SPDR=data; // ��������.
	while(!(SPSR&(1<<SPIF)));// �������� ����� ��������
	
	PORTB|=(1<<SS);// ����� ������
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

