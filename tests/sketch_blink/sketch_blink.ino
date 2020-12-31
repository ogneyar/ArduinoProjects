boolean flag = true;

void setup() {
  pinMode(5,OUTPUT);  
  pinMode(7,OUTPUT);  
}

void loop() {
  
  digitalWrite(7, flag = !flag);
  digitalWrite(5, !flag);

  delay(200);

  return;
}
