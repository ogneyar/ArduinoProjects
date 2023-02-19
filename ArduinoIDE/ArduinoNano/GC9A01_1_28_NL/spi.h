
#ifndef _SPI_H_
#define _SPI_H_


#define DDR_SPI 	DDRB
#define PORT_SPI 	PORTB
#define DD_RES 		PB0		// pin 8
#define DD_DC 		PB1		// pin 9
#define DD_SS 		PB2		// pin 10 // Slave Select
#define DD_MOSI 	PB3		// pin 11
#define DD_MISO 	PB4		// pin 12
#define DD_SCK 		PB5		// pin 13



void SPI_Master_Init() 
{
	DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_DC) | (1 << DD_RES) | (1 << DD_SS);
	
  SPCR |= (1 << SPE) | (1 << MSTR);
	// Разрешить работу SPI, режим Master, установить скорость тактов
	// SPI2X SPR1 SPR0 - 0 0 0 = fck/4; 0 0 1 = fck/16; 0 1 0 = fck/64; 0 1 1 = fck/128;      1 0 0 = fck/2; 1 0 1 = fck/8; 1 1 0 = fck/32; 1 1 1 = fck/64
	// SPCR |= (1 << SPR0) | (1 << SPR1);	
	SPSR |= (1 << SPI2X);

  // SPCR &= ~(1 << CPOL); SPCR &= ~(1 << CPHA);   // Mode 0 (CPOL = 0, CPHA = 0)
  // SPCR &= ~(1 << CPOL); SPCR |= (1 << CPHA);    // Mode 1 (CPOL = 0, CPHA = 1)
  // SPCR |= (1 << CPOL);  SPCR &= ~(1 << CPHA);   // Mode 2 (CPOL = 1, CPHA = 0)
  SPCR |= (1 << CPOL);  SPCR |= (1 << CPHA);    // Mode 3 (CPOL = 1, CPHA = 1)
}


void SPI_Master_SendByte(uint8_t data)
{	
    // Запуск передачи данных
	SPDR = data;  
	while(!(SPSR & (1 << SPIF))) ;
  asm volatile("nop");
  asm volatile("nop");	
}


#endif  /* _SPI_H_ */
