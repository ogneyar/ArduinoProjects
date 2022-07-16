// Arduino Nano

void setup() {
  Serial.begin(9600);
  pinMode(6,INPUT);
  digitalWrite(6,LOW);
}
void loop() {
  if(digitalRead(6)==HIGH) {
    Serial.println("Somebody is here.");
  }
  else {
    Serial.println("Nobody.");
  }
  delay(1000);
}
