boolean flag = 0;
int ch;

void setup() {
  Serial.begin(9600);
  Serial.println("Hell o world");
}

void loop() {      
  if (Serial.available()) {
//    char ch = Serial.read();    
    ch = Serial.parseInt();
    if (flag == 0) {
      Serial.print(ch);
      flag = 1; 
    }else {
      Serial.println("");
      flag = 0;
    }
  }
}
