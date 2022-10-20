// ATmega8

// ДАТЧИК ДВИЖЕНИЯ

#include "uart.h"

#define motion_sensor 6
#define led_pin 2
#define photoresistor A0

word last_time;
int wait = 100;
int pr;
boolean flagON = false;
boolean debug = true;

void delay_millis(int del) {      
  if (millis() - last_time > del) {
      last_time = millis();
      sensor_polling();
  }
}

void sensor_polling() {
  if ( ! flagON) pr = analogRead(photoresistor);
  if(digitalRead(motion_sensor)==HIGH) {
    if (pr > 600) {
      if (debug) uart_send("Somebody is here. Led ON.\n\r");
      digitalWrite(led_pin, HIGH);
      flagON = true;
    }else {
      if (debug) uart_send("Somebody is here. Led OFF.\n\r");
      digitalWrite(led_pin, LOW);
      flagON = false;
    }
    wait = 3000;
  }else {
    if (debug) uart_send("Nobody.\n\r");
    digitalWrite(led_pin, LOW);
    flagON = false;
    wait = 500;
  }
}

void setup() {
  if (debug) uart_ini();
  
  pinMode(motion_sensor, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(photoresistor, INPUT);
  
  digitalWrite(motion_sensor, LOW);
  digitalWrite(led_pin, LOW);
  
  last_time = millis();
}
void loop() {
  delay_millis(wait);
}
