
// Nano

#define SLIDER_POT_PIN A0

void setup() {
  Serial.begin(9600);
  pinMode(SLIDER_POT_PIN, INPUT);
}

void loop() {
  Serial.println(analogRead(SLIDER_POT_PIN));
  delay(5);
}