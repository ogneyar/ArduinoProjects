
// 

#ifdef LED_BUILTIN
#undef LED_BUILTIN
#endif

#define LED_BUILTIN PB5

void setup() {
  DDRB |= (1 << LED_BUILTIN);
}


void loop() {
  PORTB |= (1 << LED_BUILTIN);
  delay(900);
  PORTB &= ~(1 << LED_BUILTIN);
  delay(100);
}

//