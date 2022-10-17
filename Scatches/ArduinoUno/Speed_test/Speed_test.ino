
// Arduino Uno

//#define F_CPU 16000000L

/* 
// 16 MHz - 1 000 000 nop
440 316 micros

// 16 MHz - 8 000 000 nop
3 521 076 micros

// 16 MHz - 16 000 000 nop
7 041 944 micros
*/


void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("\nStart!");
  
  //volatile long int mic = micros();
  Serial.println(micros());
  //Serial.println(mic);

  for (uint32_t i = 0; i < 8000000; i++) {
    asm("nop");
  }
  //Serial.println(mic);
  Serial.println(micros());
}

void loop() {}
