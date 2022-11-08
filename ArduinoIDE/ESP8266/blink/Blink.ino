
// Wemos D1 mini
// NodeMCU
// Generic ESP8266 Module (модуль ESP12-F)

byte LED1 = 2;
  
void setup() {
  Serial.begin(9600);
  while(!Serial);
  pinMode(LED1, OUTPUT);
}

void loop() {
  Serial.println("go");
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  delay(1000);
}
