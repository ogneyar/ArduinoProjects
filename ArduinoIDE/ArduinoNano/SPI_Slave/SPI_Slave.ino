
// Nano

#define DDR_SPI DDRB
#define DD_SS 2
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5

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

void setup() {  
  SPI_SlaveInit();
  Serial.begin(115200);
  Serial.println();
  Serial.println("SPI Slave Run");
}

void loop() {
  Serial.println(SPI_SlaveReceive());
}


// Пример кода на ассемблере: (SPI_SlaveInit, SPI_SlaveReceive)
/*
SPI_SlaveInit:
; Настройка ножки порта MISO как выход,
; все остальные сигналы как вход:
   ldi r17,(1 << DD_MISO)
   out DDR_SPI,r17
; Разрешить работу SPI:
   ldi r17,(1 << SPE)
   out SPCR,r17
   ret
   
SPI_SlaveReceive:
; Ожидание завершения приема:
   in r16, SPSR
   sbrs r16, SPIF
   rjmp SPI_SlaveReceive
; Чтение принятых данных и возврат:
   in r16,SPDR
   ret
*/
