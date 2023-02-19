
// LGT8F328, Nano

#define DDR_SPI 	DDRB
#define PORT_SPI 	PORTB
#define DD_RES 		PB0		// pin 8
#define DD_DC 		PB1		// pin 9
#define DD_SS 		PB2		// pin 10 // Slave Select
#define DD_MOSI 	PB3		// pin 11
#define DD_MISO 	PB4		// pin 12
#define DD_SCK 		PB5		// pin 13

char* PtrToStrChar;  // Указатель на байт в массиве

// Подпрограмма инициализации режима Master с управлением потоком по опросу.
void SPI_Master_Init(void) 
{
  DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_DC) | (1 << DD_RES) | (1 << DD_SS);
  
	// Разрешить работу SPI, режим Master
  SPCR |= (1 << SPE) | (1 << MSTR);

  // установить скорость тактов
  // SPI2X SPR1 SPR0 - 0 0 0 = fck/4; 0 0 1 = fck/16; 0 1 0 = fck/64; 0 1 1 = fck/128; 1 0 0 = fck/2; 1 0 1 = fck/8; 1 1 0 = fck/32; 1 1 1 = fck/64
  // SPCR |= (1 << SPR0) | (1 << SPR1);	
	SPSR |= (1 << SPI2X);
  
  // SPCR &= ~(1 << CPOL); SPCR &= ~(1 << CPHA);   // Mode 0 (CPOL = 0, CPHA = 0)
  // SPCR &= ~(1 << CPOL); SPCR |= (1 << CPHA);    // Mode 1 (CPOL = 0, CPHA = 1)
  // SPCR |= (1 << CPOL);  SPCR &= ~(1 << CPHA);   // Mode 2 (CPOL = 1, CPHA = 0)
  SPCR |= (1 << CPOL);  SPCR |= (1 << CPHA);    // Mode 3 (CPOL = 1, CPHA = 1)
  
  // LGT8F328: fck/2 анализатор показывает 4MHz
  // Nano: fck/2 анализатор показывает 8MHz
}

void SPI_Master_SendByte(uint8_t data) {
  /* Запуск передачи данных: */
  SPDR = data;
  /* Ожидание завершения передачи: */
  while (!(SPSR & (1 << SPIF))) ;
	asm volatile("nop");
	asm volatile("nop"); // для Nano при максимальной скорости
}

void SPI_Master_SendStr(char * data) {
  PtrToStrChar = data;  // Установить указатель на начало строки.
  while (*PtrToStrChar != 0) {// Цикл "если не конец строки", то ..
    SPI_Master_SendByte(*PtrToStrChar);
    PtrToStrChar++;  // переход к следующему символу в строке.
  }  
}


int main() {
  // инициализация SPI для работы по опросу
  SPI_Master_Init(); 
  
  SPI_Master_SendByte(0x55);
  SPI_Master_SendByte(0xaa);
  SPI_Master_SendStr("O");
  // delay(1);
  
  while (1) {
    SPI_Master_SendByte(0x55);
    // delay(1);
  }
}

