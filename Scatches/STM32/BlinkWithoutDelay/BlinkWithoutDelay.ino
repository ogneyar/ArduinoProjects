
// STM32F103C8 - работает, уррааа

byte ledPin =  LED_BUILTIN; // PC13; 
bool ledState = LOW;
unsigned long previousMillis = 0;
unsigned long interval = 250;

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
