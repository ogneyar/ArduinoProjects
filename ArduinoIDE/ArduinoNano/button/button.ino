// Arduino Nano

boolean flagButton;
boolean flagLed;
unsigned long last_press;

void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(13, 1);
  Serial.begin(9600); 
}

void loop() {
	
    boolean button = !digitalRead(7);
    // if (button == true && flagButton == false && millis() - last_press > 50) {
    if (button == true && flagButton == false) {
      flagButton = true;
      Serial.println("Button pressed");
      flagLed =!flagLed;
      digitalWrite(13, flagLed);
      // last_press = millis();
      delay(10);
    }
    if (button == false && flagButton == true) {
      flagButton = false;
      Serial.println("Button released");
      delay(10);
    }
	
}
