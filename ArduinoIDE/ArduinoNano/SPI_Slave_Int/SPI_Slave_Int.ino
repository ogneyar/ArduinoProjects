
// Nano, LGT8F328

#define DDR_SPI DDRB
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5

 
#define  Error   0x01
#define  Success 0x02
 
char     flagReceive   = 1;      // Флаг приёма данных.
 
// Обработчик прерывания для режима Slave (для управления потоком по прерываниям)
ISR(SPI_STC_vect) {
  flagReceive = 0;
}
 
// Подпрограмма инициализации режима Slave с управлением потоком по прерываниям.
void SPI_Init_Slave_IntContr (void)
{
   volatile char IOReg;
   // Настройка MISO как выхода:
   DDR_SPI    = (1 << DD_MISO);
   // Разрешить прерывание SPI и разрешить SPI в режиме Slave
   SPCR     = (1 << SPIE) | (1 << SPE);
   IOReg    = SPSR;        // Очистить бит SPIF в регистре SPSR.
   IOReg    = SPDR;
   sei();   // Глобально разрешить прерывания.
}
 
// Подпрограмма приема в режиме Slave (с работой по прерываниям)
char SPI_Slave_Receive_IntContr (void)
{
  flagReceive = 1;
  return SPDR;
}
 
 
void setup() {
  SPI_Init_Slave_IntContr();
  Serial.begin(115200);
  Serial.println();
  Serial.println("SPI Slave Run");
}

void loop() {
  if ( ! flagReceive ) Serial.println(SPI_Slave_Receive_IntContr()); 
}




