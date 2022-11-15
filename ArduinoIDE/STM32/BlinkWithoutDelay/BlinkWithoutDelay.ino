
// STM32F103C8T6 or STM32F401CCU6 or STM32F411CEU6
// #define LED PC13
// STM32F030F4P6 
// #define LED PA4
// (STM32G070RBT6 and STM32G030C8T6 and STM32G030F6P6 not working)
#define LED D2

byte ledPin = LED; 
bool ledState = LOW;
unsigned long previousMillis = 0;
unsigned long interval = 100;

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
