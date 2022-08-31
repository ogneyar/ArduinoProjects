#include <SoftwareSerial.h>

SoftwareSerial SIM800(4,5); // rx sim in - GPIO4 // tx sim in - GPIO5

uint32_t bod = 9600; // 115200; //  

void setup() {
  Serial.begin(bod);
  Serial.println("Start");
  delay(1000);
  SIM800.begin(bod);
  SIM800.println("AT");
  delay(1000);
}

void loop() {
  if (SIM800.available()) Serial.write(SIM800.read());
  
  if (Serial.available()) SIM800.write(Serial.read());
  
//  delay(10);
}
