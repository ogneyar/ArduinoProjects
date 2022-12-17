
// Esp32s2_lolin_mini (LED_BUILTIN 15)

#define LED_BUILTIN 15


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}
