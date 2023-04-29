
// Zero(Samd21)

// #undef LED_BUILTIN
#ifndef LED_BUILTIN
#define LED_BUILTIN 13u
#endif


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(800);
}
