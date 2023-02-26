
// Nano

// b1 - подключил на D2
#define B1_PIN 2
// b2 - подключил на D3
#define B2_PIN 3
#define LED_PIN 13

void setup() {
  pinMode(LED_PIN,1);
  pinMode(B1_PIN,1);
  pinMode(B2_PIN,1);

  digitalWrite(B1_PIN,1);
  digitalWrite(B2_PIN,0);

  Serial.begin(9600);
  Serial.println("Run\r\n");
}

void loop() {
  digitalWrite(LED_PIN,1);
  Serial.println("LED ON\r\n");

  digitalWrite(B1_PIN,0);
  digitalWrite(B2_PIN,1);
  
  delay(2000);

  digitalWrite(LED_PIN,0);    
  Serial.println("LED OFF\r\n");

  digitalWrite(B1_PIN,1);
  digitalWrite(B2_PIN,0);

  delay(2000);
  
}
