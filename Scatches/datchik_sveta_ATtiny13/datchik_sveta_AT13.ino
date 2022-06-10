//int sensorPin = 0;//A0;//
int ledPin = 1;//D2;//
//unsigned int sensor = 0;
byte del = 50;


void setup() {
//  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
//  Serial.begin(9600);
}

void loop() {
//  sensor = analogRead(sensorPin);
//  if (sensor < 350) digitalWrite(ledPin, HIGH);
//  else digitalWrite(ledPin, LOW);
//  Serial.println(sensor, DEC);
//  delay(del);
  
  digitalWrite(ledPin, HIGH);
  delay(del);
  digitalWrite(ledPin, LOW);
  delay(del);
  digitalWrite(ledPin, HIGH);
  delay(del);
}
