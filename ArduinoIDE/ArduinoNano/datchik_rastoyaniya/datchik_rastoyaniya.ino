
// Nano

// out - подключил на D2
#define OUT_PIN 2
#define LED_PIN 13

void setup() {
  pinMode(LED_PIN,1);
  pinMode(OUT_PIN,0);

  Serial.begin(9600);
  Serial.println("Run\r\n");
}

void loop() {
  if (digitalRead(OUT_PIN)) 
  {
    digitalWrite(LED_PIN,1);
    Serial.println("LED ON\r\n");
  }
  else
  {
    digitalWrite(LED_PIN,0);    
    Serial.println("LED OFF\r\n");
  }
}
