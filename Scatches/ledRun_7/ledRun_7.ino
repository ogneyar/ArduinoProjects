
boolean flagButton;
boolean button;
boolean flagLed;
unsigned long last_press;
unsigned long PORT_BUTTON = 3;
unsigned long PORT_LED = 5;

void setup() {
  pinMode(PORT_BUTTON, INPUT_PULLUP);
  pinMode(PORT_LED, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
    button = !digitalRead(PORT_BUTTON);
    if (button == true && flagButton == false && millis() - last_press > 50) {
      flagButton = true;
      Serial.println("Button pressed");
      flagLed =!flagLed;
      digitalWrite(PORT_LED, flagLed);
//      digitalWrite(13, flagLed);
      last_press = millis();
    }
    if (button == false && flagButton == true) {
      flagButton = false;
      Serial.println("Button released");
    }
}
