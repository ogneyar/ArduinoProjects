
// ATtiny84

void setup() {
  DDRA |= (1 << PA3);
}

void loop() {
  PORTA ^= (1 << PA3);
  delay(1000);                 
}
