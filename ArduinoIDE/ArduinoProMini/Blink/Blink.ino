
// Arduino Pro Mini

// Перед загрузкой через UART необходимо жать RESET
// у меня плата 3.3v 328p

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(20);
  digitalWrite(LED_BUILTIN, LOW);
  delay(20);
}
