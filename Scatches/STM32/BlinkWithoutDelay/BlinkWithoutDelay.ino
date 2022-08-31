
// STM32F103C8 - работает, уррааа

byte ledPin = PC13; // LED_BUILTIN; //
bool ledState = LOW;
unsigned long previousMillis = 0;
unsigned long interval = 25;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}
