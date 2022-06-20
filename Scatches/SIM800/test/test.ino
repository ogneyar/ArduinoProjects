#include <SoftwareSerial.h>

SoftwareSerial SIM800(6,3); // rx sim in 6 pin // tx sim in 3 pin

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  SIM800.begin(115200);
  SIM800.println("AT");
}

void loop() {
  if (SIM800.available())
    Serial.write(SIM800.read());
   if (Serial.available())
    SIM800.write(Serial.read());
}
