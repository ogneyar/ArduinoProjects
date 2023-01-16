
// LGT8F328

#define DDR_SPI DDRB
#define DD_SS 2
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5
 
char*    PtrToStrChar;           // Указатель на определенный символ в строке
char     ClearToSend   = 1;      // Флаг завершения отправки строки.
 
// Обработчик прерывания для режима Master (для управления потоком по прерываниям)
ISR(SPI_STC_vect) {
  ClearToSend = 1; //  отправку следующей строки.
}
  
// Подпрограмма инициализации режима Master с управлением потоком по прерываниям.
void SPI_Init_Master_IntContr(void) {
   volatile char IOReg;
  /* Настройка MOSI, SCK и SS как выход,
      все остальные сигналы как вход: */
   DDR_SPI  = (1 << DD_SS) | (1 << DD_MOSI) | (1 << DD_SCK);
   // Разрешить прерывание SPI и режим SPI Master 
   // с тактовой частотой SCK = fck/8: 4MHz (if F_CPU == 32MHz) and 2MHz (if F_CPU == 16MHz)
   // с тактовой частотой SCK = fck/16: 2MHz (if F_CPU == 32MHz) and 1MHz (if F_CPU == 16MHz)
   SPCR  = (1 << SPIE) | (1 << SPE) | (1 << MSTR) | (1 << SPR0); // SPI2X SPR1 SPR0 - 0 0 0 = fck/4; 0 0 1 = fck/16; 0 1 0 = fck/64; 0 1 1 = fck/128; 1 0 0 = fck/2; 1 0 1 = fck/8; 1 1 0 = fck/32; 1 1 1 = fck/64
   SPSR = (1 << SPI2X);
   IOReg   = SPSR;               // Очистить бит SPIF в регистре SPSR.
   IOReg   = SPDR;
   sei();         // Глобально разрешить прерывания.
 }
  
// Подпрограмма отправки режима Master (для работы по прерываниям)
void SPI_Master_Send_IntContr (char* TextString) {  
  PtrToStrChar = TextString;  // Установить указатель на начало строки.
  while (*PtrToStrChar != 0) {// Цикл "если не конец строки", то ..
    ClearToSend = 0; // заблокировать инициацию новых передач.
    /* Запуск передачи данных: */
    SPDR = *PtrToStrChar;
    /* Ожидание завершения передачи: */
    while (!ClearToSend) ;
    PtrToStrChar++;  // переход к следующему символу в строке.
  }  
}
 
void setup() {
  SPI_Init_Master_IntContr();      // инициализация SPI для работы по прерываниям
  
  SPI_Master_Send_IntContr("V");
}

void loop() {}

