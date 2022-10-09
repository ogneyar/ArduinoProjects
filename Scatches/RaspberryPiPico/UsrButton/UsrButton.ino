
// PiPico

const int buttonPin = 24;     // the number of the pushbutton pin
const int ledPin =  25;      // the number of the LED pin

int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  } else {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  }
}
