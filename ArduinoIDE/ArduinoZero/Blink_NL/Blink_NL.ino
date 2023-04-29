
// Zero(Samd21)

#define LED 17 // PA17 = D13
#define LED_PIN (1 << LED)

void setup() {
  PORT->Group[0].DIRSET.reg = LED_PIN; 
}


void loop() {
  PORT->Group[0].OUTSET.reg = LED_PIN;
  delay(200);
  PORT->Group[0].OUTCLR.reg = LED_PIN;
  delay(800);
}
