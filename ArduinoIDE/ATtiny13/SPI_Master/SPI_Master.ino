
#include <stdint.h>
#include <avr/io.h>

# define	SPI_MOSI	PB0	
# define	SPI_MISO	PB1	
# define	SPI_SCK		PB2	
# define	SPI_CS		PB3	

#define	SPI_PORT	PORTB
#define	SPI_DDR		DDRB
#define	SPI_PIN		PINB
#define	CS_PIN		(1<<SPI_CS)			// PB3 as default
#define	MOSI_PIN	(1<<SPI_MOSI)		// PB0 as default
#define	MISO_PIN 	(1<<SPI_MISO)		// PB1 as default
#define	SCK_PIN		(1<<SPI_SCK) 		// PB2 as default

#define	read_miso() 	(SPI_PIN & (MISO_PIN))
#define	select_chip() 	(SPI_PORT &= ~(CS_PIN))
#define	deselect_chip() (SPI_PORT |= (CS_PIN))
#define	SPI_SCK_HIGH() 	(SPI_PORT |= SCK_PIN)
#define	SPI_SCK_LOW() 	(SPI_PORT &= ~SCK_PIN)
#define	SPI_MOSI_HIGH() (SPI_PORT |= MOSI_PIN)
#define	SPI_MOSI_LOW() 	(SPI_PORT &= ~MOSI_PIN) 


void spi_init();
void spi_cs_enable(void);
void spi_cs_disable(void);
char spi_transfer(char c);


void setup() 
{
  spi_init();  
}

void loop() 
{
  spi_transfer(0x55);
  delay(1000);
}

char
spi_transfer(char c)
{
	uint8_t i;
	
	for (i = 0; i < 8; i++) {
		if (c & (1 << 7)) {
			SPI_MOSI_HIGH();
		} else {
			SPI_MOSI_LOW();
		}
		SPI_SCK_LOW();
		c <<= 1;
		if (read_miso()) {
			c |= 1;
		}
		SPI_SCK_HIGH();
	}
	
	return c;
}

void
spi_init(void)
{
	deselect_chip();
	SPI_DDR = MOSI_PIN|SCK_PIN|CS_PIN;
	SPI_SCK_HIGH();
}

void
spi_cs_enable(void)
{
	select_chip();
}

void
spi_cs_disable(void)
{
	deselect_chip();
}
