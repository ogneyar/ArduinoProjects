
// Wemos D1 mini
/* 
// 80 MHz - 1 000 000 nop
62559 micros
62560 micros

// 160 MHz - 1 000 000 nop
31294 micros
31295 micros

// 80 MHz - 16 000 000 nop
999 868 micros
1 000 064 micros

// 160 MHz - 16 000 000 nop
500 052 micros
500 052 micros

// 80 MHz - 80 000 000 nop
5 000 056 micros
5 000 057 micros
 
// 160 MHz - 80 000 000 nop
2 500 061 micros
2 500 061 micros
*/


void setup() {
  //ESP.wdtDisable(); // для 80 MHz - 80 000 000 nop
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("\nStart!");
  
  //volatile long int mic = micros();
  Serial.println(micros());
  //Serial.println(mic);

  for (uint32_t i = 0; i < 80000000; i++) {
    asm("nop");
  }
  //Serial.println(mic);
  Serial.println(micros());
}

void loop() {}
