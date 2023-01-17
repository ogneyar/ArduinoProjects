
// LGT8F328

#define DDR_SPI DDRB
#define DD_SS 2
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5

char* PtrToStrChar;  // Указатель на определенный символ в строке

// Подпрограмма инициализации режима Master с управлением потоком по опросу.
void SPI_MasterInit(void) {
  /* Настройка MOSI и SCK как выход,
      все остальные сигналы как вход: */
  DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK);
  /* Разрешить работу SPI, режим Master,
      установить скорость (4MHz) тактов fck/4 для Nano и fck/8 для LGT8F328: */
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // SPI2X SPR1 SPR0 - 0 0 0 = fck/4; 0 0 1 = fck/16; 0 1 0 = fck/64; 0 1 1 = fck/128; 1 0 0 = fck/2; 1 0 1 = fck/8; 1 1 0 = fck/32; 1 1 1 = fck/64
  SPSR = (1 << SPI2X);
}

void SPI_MasterTransmit(char* TextString) {
  PtrToStrChar = TextString;  // Установить указатель на начало строки.
  while (*PtrToStrChar != 0) {// Цикл "если не конец строки", то ..
    /* Запуск передачи данных: */
    SPDR = *PtrToStrChar;
	asm volatile("nop");
    /* Ожидание завершения передачи: */
    while (!(SPSR & (1 << SPIF))) ;
    PtrToStrChar++;  // переход к следующему символу в строке.
  }  
}


int main() {
  // инициализация SPI для работы по опросу
  SPI_MasterInit(); 
  
  SPI_MasterTransmit("O");
  
  while (1) {}
}

