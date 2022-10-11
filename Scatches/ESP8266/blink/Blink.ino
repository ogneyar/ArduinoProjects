
// ESP8266 & D1 mini
// NodeMCU

byte LED1 = 2;
  
void setup() {
  pinMode(LED1, OUTPUT);
}

void loop() {
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  delay(1000);
}
