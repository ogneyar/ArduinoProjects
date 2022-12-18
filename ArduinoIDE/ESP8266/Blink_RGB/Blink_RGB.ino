
// NodeMCU_mini

byte LED = 2;
byte RGB_LED1 = 15; // Red
byte RGB_LED2 = 12; // Green
byte RGB_LED3 = 13; // Blue
  
void setup() {
  Serial.begin(115200);
  while(!Serial);
  pinMode(LED, OUTPUT);
  pinMode(RGB_LED1, OUTPUT);
  pinMode(RGB_LED2, OUTPUT);
  pinMode(RGB_LED3, OUTPUT);
}

void loop() {
  Serial.println("go");
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(RGB_LED1, HIGH);
  delay(100);
  digitalWrite(RGB_LED2, HIGH);
  delay(100);
  digitalWrite(RGB_LED3, HIGH);
  delay(100);

  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(RGB_LED1, LOW);
  delay(100);
  digitalWrite(RGB_LED2, LOW);
  delay(100);
  digitalWrite(RGB_LED3, LOW);
  delay(100);
}
