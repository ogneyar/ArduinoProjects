
// Esp32s2_lolin_mini (LED_BUILTIN 15)
// Esp32с3_WeAct (LED_BUILTIN 8)

#define LED_BUILTIN 8


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

//