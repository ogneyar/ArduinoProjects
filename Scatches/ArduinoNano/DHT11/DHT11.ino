// Arduino Nano

#include <util/delay.h>
#include "dht.h"

uint8_t _hum, _temp;// переменные для влажности и температуры


void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  _delay_ms(1000);
}


void loop() {  
  uint8_t response = dht_read(&_hum, &_temp);// опроса датчика
//  Serial.println(response); // вывод номера ошибки в консоль
  
  Serial.print("hum: ");
  Serial.print(_hum);
  Serial.print("   ");
  Serial.print("temp: ");
  Serial.println(_temp);
  _delay_ms(1000);
}
