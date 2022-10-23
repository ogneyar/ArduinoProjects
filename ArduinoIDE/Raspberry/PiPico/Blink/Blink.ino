
// Raspberry Pi Pico

#ifdef LED_BUILTIN 
#define LED LED_BUILTIN
#else
#define LED 25
#endif

void setup() {
  pinMode(LED, OUTPUT);
}


void loop() {
  digitalWrite(LED, HIGH);
  delay(100); 
  digitalWrite(LED, LOW);
  delay(100);
}
