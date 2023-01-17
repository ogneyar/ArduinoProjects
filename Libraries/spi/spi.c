

#include "spi.h"


// Подпрограмма инициализации режима Master с управлением потоком по опросу.
void SPI_MasterInit(void) {
  /* Настройка MOSI и SCK как выход,
      все остальные сигналы как вход: */
  DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK);
  /* Разрешить работу SPI, режим Master,
      установить скорость тактов */
// SPI2X SPR1 SPR0 - 0 0 0 = fck/4; 0 0 1 = fck/16; 0 1 0 = fck/64; 0 1 1 = fck/128; 1 0 0 = fck/2; 1 0 1 = fck/8; 1 1 0 = fck/32; 1 1 1 = fck/64
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0); 
  SPSR = (1 << SPI2X);
}

void SPI_MasterTransmit(char* data) {
  PtrToStrChar = data;  // Установить указатель на начало строки.
  while (*PtrToStrChar != 0) {// Цикл "если не конец строки", то ..
    /* Запуск передачи данных: */
    SPDR = *PtrToStrChar;
	asm volatile("nop");
    /* Ожидание завершения передачи: */
    while (!(SPSR & (1 << SPIF))) ;
    PtrToStrChar++;  // переход к следующему байту
  }  
}

// Подпрограмма инициализации режима Slave с управлением потоком по опросу.
void SPI_SlaveInit(void) {
  volatile char IOReg;
  /* Настройка ножки порта MISO как выход,
      все остальные сигналы как вход: */
  DDR_SPI = (1 << DD_MISO);
  /* Разрешить работу SPI: */
  SPCR = (1 << SPE);
  IOReg = SPSR;  // Очистить бит SPIF в регистре SPSR.
  IOReg = SPDR;
}

// Прием данных в режиме Slave (с работой по опросу)
char SPI_SlaveReceive(void) {
  /* Ожидание завершения приема: */
  while (!(SPSR & (1 << SPIF)))
    ;
  /* Чтение принятых данных и возврат: */
  return SPDR;
}