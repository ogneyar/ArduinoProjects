
// НЕ РАБОТАЕТ!!!
// LGT8F328

extern "C" {
  extern __FlashStringHelper *SPI_MasterInit();
  extern __FlashStringHelper *SPI_MasterTransmit(byte);
}

#define DDR_SPI DDRB
#define DD_SS 2
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5

char* PtrToStrChar;  // Указатель на определенный символ в строке

int main() {
  // инициализация SPI для работы по опросу
  SPI_MasterInit(); 
  
  SPI_MasterTransmit("Z");
  
  while (1) {}
}



