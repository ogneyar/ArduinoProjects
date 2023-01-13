
// Nano, LGT8F328

extern "C" {
  extern __FlashStringHelper *D13OnOff(byte);
}

void setup() {}

void loop() {
  D13OnOff(0b00000000);
  delay(450);
  D13OnOff(0b00100000);
  delay(50);
}