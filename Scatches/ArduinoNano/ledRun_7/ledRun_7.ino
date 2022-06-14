
boolean flagButton;
boolean button;
boolean flagLed;
short last_press;
short BUTTON = 3;
short LED = 5;

void setup() {
//  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUTTON, INPUT);
//  digitalWrite(BUTTON, 0);
  pinMode(LED, OUTPUT);
//  digitalWrite(LED, 0);
  Serial.begin(9600); 
}

void loop() {
    button = digitalRead(BUTTON);
    delay(3);
    //if (button == true && flagButton == false && millis() - last_press > 50) {
    //  flagButton = true;
    //  Serial.println("Button pressed");
    //  flagLed =!flagLed;
    //  digitalWrite(PORT_LED, flagLed);
//      digitalWrite(13, flagLed);
    //  last_press = millis();
    //}
    //if (button == false && flagButton == true) {
    //  flagButton = false;
    //  Serial.println("Button released");
    //}
    if (button == true) {
      digitalWrite(LED, 0);
//      delay(30);
    }else if (button == false) {
      digitalWrite(LED, 0);
      delay(30);
      digitalWrite(LED, 1);
      delay(30);
    }
    //digitalWrite(LED, 0);
}
