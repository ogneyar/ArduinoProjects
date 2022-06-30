// Arduino Nano

byte LED1 = 13;
  
void setup() {
  pinMode(LED1, OUTPUT);
}

void loop() {
  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED1, LOW);
  delay(500);
}
