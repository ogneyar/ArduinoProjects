
// ATtiny13

// ДАТЧИК ДВИЖЕНИЯ

#define F_CPU 9600000UL

#include <Arduino.h>

#define photoresistor A1 // PB2
#define led_pin 1		 // PB1
#define motion_sensor 4  // PB4

word last_time;
int wait = 1000;
int pr;
boolean flagON = false;

void delay_millis(int del) {      
  if (millis() - last_time > del) {
      last_time = millis();
      sensor_polling();
  }
}

void sensor_polling() {
  // if ( ! flagON) pr = analogRead(photoresistor);
  // if(digitalRead(motion_sensor)==HIGH) {
    // if (pr > 430) {
    //   digitalWrite(led_pin, HIGH);
    //   flagON = true;
    // }else {
      // digitalWrite(led_pin, HIGH);
      // flagON = false;
    // }
    // wait = 3000;
  // }else {
    // digitalWrite(led_pin, LOW);
    // flagON = false;
    // wait = 500;
  // }
  
  digitalWrite(led_pin, digitalRead(motion_sensor));

}

void setup() {
  pinMode(motion_sensor, INPUT);
  pinMode(led_pin, OUTPUT);
  // pinMode(photoresistor, INPUT);
  
  digitalWrite(motion_sensor, LOW);
  digitalWrite(led_pin, LOW);
  
  last_time = millis();
}
void loop() {
  delay_millis(wait);
}
