
// Wemos D1 mini
// NodeMCU
// Generic ESP8266 Module (модуль ESP12-F или ESP01)

byte LED1 = 2; // у ESP01 LED на Tx (1)
  
void setup() {
  Serial.begin(115200);
  while(!Serial);
  pinMode(LED1, OUTPUT);
}

void loop() {
  // Serial.println("go");
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  delay(1000);
}
