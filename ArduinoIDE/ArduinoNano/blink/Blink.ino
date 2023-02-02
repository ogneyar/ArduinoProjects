
// Nano, LGT8F328, ProMini

//byte LED1 = 13; // PB5
  
void setup() {
//  pinMode(LED1, OUTPUT);
  DDRB |= (1 << 5);
}

void loop() {
//  digitalWrite(LED1, HIGH);
//  delay(500);  
//  digitalWrite(LED1, LOW);
//  delay(500);
  PORTB ^= (1 << 5);
  _delay_us(200000);
}
