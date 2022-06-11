//int sensorPin = 0;
int ledPin = 1;
//unsigned int sensor = 0;
byte del = 50;


void setup() {
//  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
//  sensor = analogRead(sensorPin);
//  if (sensor < 350) digitalWrite(ledPin, HIGH);
//  else digitalWrite(ledPin, LOW);
//  delay(del);
  
  digitalWrite(ledPin, HIGH);
  delay(del);
  digitalWrite(ledPin, LOW);
  delay(del);
  digitalWrite(ledPin, HIGH);
  delay(del);
}
