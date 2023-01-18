
// Nano, LGT8F328

extern "C" {
  extern __FlashStringHelper *D13OnOff(byte);
}
  
void setup() {
}

void loop() {
  D13OnOff(0b00000000);
  delay(900);  
  D13OnOff(1<<5);
  delay(100);
}

//