
// Nano

#include <SoftwareSerial.h>

static const int RXPin = 3, TXPin = 4;

SoftwareSerial Serial2(TXPin, RXPin);

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial.println("Start");
}

void loop() {
  if (Serial2.available()) {
    Serial.println("-------------------");
    String data = Serial2.readStringUntil('\n');
    Serial.println("-------------------");
    Serial.println(data);
  }
}
