
// spi avr

#ifndef __SPI_H
#define __SPI_H

#define DDR_SPI DDRB
#define DD_SS 2
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5

char* PtrToStrChar;  // Указатель на определенный символ в строке

void SPI_MasterInit(void);
void SPI_MasterTransmit(char* data);
void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);

#endif