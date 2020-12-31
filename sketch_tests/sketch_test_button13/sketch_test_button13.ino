word last_time;
boolean flag;
boolean button;

void setup() {
  Serial.begin(9600);
  Serial.println("Hell o world");
  last_time = millis();
  flag = true;
  pinMode(13, OUTPUT);
  pinMode(A5, INPUT_PULLUP);
}

void loop() {      

  button = !digitalRead(A5);
  digitalWrite(13, button);
  
//  if (millis() - last_time > 300) {
//      last_time = millis();
//      Serial.println("300");      
//      flag = !flag;
//      digitalWrite(13, flag);
//  }

}
