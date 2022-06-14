void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(13, 1);
  Serial.begin(9600); 
}

boolean flagButton;
boolean flagLed;
unsigned long last_press;

void loop() {
    boolean button = !digitalRead(7);
    if (button == true && flagButton == false && millis() - last_press > 50) {
      flagButton = true;
      Serial.println("Button pressed");
      flagLed =!flagLed;
      digitalWrite(13, flagLed);
      last_press = millis();
    }
    if (button == false && flagButton == true) {
      flagButton = false;
      Serial.println("Button released");
    }
       
//    if (flag == true) {
//      digitalWrite(13, 0);
//      flag = false;
//    }else {
//      digitalWrite(13, 1);
//      flag = true;
//    }
  
//  Serial.print("Button: ");
//  Serial.println(button);

//  delay(500);
  
}
