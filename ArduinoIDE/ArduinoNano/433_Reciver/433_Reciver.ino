
// Arduino Nano

#define RELE  7
#define LED   13
#define ON    LOW
#define OFF   HIGH

#include <Gyver433.h>
Gyver433_RX<2, 20> rx;  // указали пин и размер буфера

void setup() {
  Serial.begin(9600);  
  attachInterrupt(0, isr, CHANGE);  // прерывание пина радио по CHANGE
  Serial.println();
  Serial.println("Start!");

  pinMode(RELE, HIGH);
  digitalWrite(RELE, OFF);
}

// спец. тикер вызывается в прерывании
void isr() {
  rx.tickISR();
}

void loop() {
  if (rx.gotData()) {                   // если успешно принято больше 0
    Serial.write(rx.buffer, rx.size);   // выводим
    Serial.println();

    digitalWrite(RELE, ON);
    delay(1000);
    digitalWrite(RELE, OFF);
  }
}
