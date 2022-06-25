#include <SoftwareSerial.h>

SoftwareSerial SIM800(6,7); // rx sim in 6 pin // tx sim in 7 pin

uint32_t bod = 115200; // 9600; // 

void setup() {
  Serial.begin(bod);
  Serial.println("Start");
  SIM800.begin(bod);
  SIM800.println("AT");
}

void loop() {
  if (SIM800.available()) Serial.write(SIM800.read());
  
  if (Serial.available()) SIM800.write(Serial.read());
  
  _delay_ms(100);
}
