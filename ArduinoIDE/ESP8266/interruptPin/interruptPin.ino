const byte interruptPin = D3;
volatile byte state = HIGH;
volatile uint32_t i = 0;
volatile byte wait = false;

void ICACHE_RAM_ATTR interruptHandler();

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (interruptPin, INPUT_PULLUP);

  digitalWrite (LED_BUILTIN, state);

  //—Задаем  функцию blink , которая будет вызвана по внешнему прерыванию.
  attachInterrupt ( digitalPinToInterrupt (interruptPin), interruptHandler, HIGH);
  //sei();
}

void loop() {
  
}

void interruptHandler () {
  if (!wait) {
    wait = true;
    state = !state;
    digitalWrite (LED_BUILTIN, state);
    Serial.println("attachInterrupt");
    for(i = 0; i < 200000; i++) asm("nop");
    wait = false;
  }
}
