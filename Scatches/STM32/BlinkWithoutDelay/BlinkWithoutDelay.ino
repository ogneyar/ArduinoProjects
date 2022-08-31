
// STM32F103C8T6 
//#define LED_BUILTIN PC13
// STM32F030F4P6 
#define LED_BUILTIN PA4

byte ledPin = LED_BUILTIN; 
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
