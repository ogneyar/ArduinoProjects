
// ATmega328pb

void setup() {
  DDRD |= (1 << PD3);
}

void loop() {
  PORTD ^= (1 << PD3);
  delay(1000);                 
}
