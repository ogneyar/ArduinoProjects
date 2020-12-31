word last_time;



void setup() {
  Serial.begin(9600);
  Serial.println("Hell o world");
  last_time = millis();
}

void loop() {      
  if (millis() - last_time > 500) {
      last_time = millis();

      Serial.println("500");
  }
}
