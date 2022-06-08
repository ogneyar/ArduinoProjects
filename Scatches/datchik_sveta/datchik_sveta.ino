int sensorPin = A0;
int ledPin = 2;
unsigned int sensor = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() {
  sensor = analogRead(sensorPin);
  if (sensor < 350) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
  Serial.println(sensor, DEC);
  delay(500);
  
  //digitalWrite(ledPin, HIGH);
  //delay(500);
  //digitalWrite(ledPin, LOW);
  //delay(500);
  //digitalWrite(ledPin, HIGH);
  //delay(500);
}
