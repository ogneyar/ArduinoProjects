
// НЕ РАБОТАЕТ!!!
// Nano

extern "C" {
  extern __FlashStringHelper *SPI_SlaveInit();
  extern __FlashStringHelper *SPI_SlaveReceive();
}

#define DDR_SPI DDRB
#define DD_SS 2
#define DD_MOSI 3
#define DD_MISO 4
#define DD_SCK 5

void setup() {  
  SPI_SlaveInit();
  Serial.begin(115200);
  Serial.println();
  Serial.println("SPI Slave Run");
}

void loop() {
  Serial.println(SPI_SlaveReceive());
}

