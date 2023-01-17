
// LGT8F328

#define DDR_SPI DDRB
#define DD_SS 2
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5

char* PtrToStrChar;  // Указатель на байт в массиве

// Подпрограмма инициализации режима Master с управлением потоком по опросу.
void SPI_Master_Init(void) {
  /* Настройка MOSI и SCK как выход,
      все остальные сигналы как вход: */
  DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK);
  /* Разрешить работу SPI, режим Master,
      установить скорость тактов */
  // SPI2X SPR1 SPR0 - 0 0 0 = fck/4; 0 0 1 = fck/16; 0 1 0 = fck/64; 0 1 1 = fck/128; 1 0 0 = fck/2; 1 0 1 = fck/8; 1 1 0 = fck/32; 1 1 1 = fck/64
  SPCR = (1 << SPE) | (1 << MSTR);// | (1 << SPR1) | (1 << SPR0);
  SPSR = (1 << SPI2X);
  // LGT8F328: fck/2 анализатор показывает 4MHz
}

void SPI_Master_SendByte(uint8_t data) {
    /* Запуск передачи данных: */
    SPDR = data;
	  asm volatile("nop");
    /* Ожидание завершения передачи: */
    while (!(SPSR & (1 << SPIF))) ;
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
  // _delay_us(500);
  
  while (1) {
    SPI_Master_SendByte(0x55);
    // _delay_us(500);
  }
}

