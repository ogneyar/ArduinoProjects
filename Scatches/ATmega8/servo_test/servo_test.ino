// ATmega8
// Clock 8 MHz
// BOD disabled

#include <Servo.h>

Servo servo;
 
int del = 500;  

void delayAndBlink();
void test();
void testPotent();

void setup() {
  pinMode(13, 1);
  digitalWrite(13, 0);
  
  // подключение серво привода к 5 цифровому пину (PD5)
  servo.attach(5);  
}

void loop() {  
//  test();
  testPotent();
}


void delayAndBlink() {
  // мигаем светодиодом
  digitalWrite(13, 1);  
  // задержка
  delay(del);
  // мигаем светодиодом
  digitalWrite(13, 0);
  // задержка
  delay(del/2);
}

void test() { // от 0-170 - среднее значение - остановка
  // поворот по часовой стрелке
  servo.write(0);
  // задержка и мигаем светодиодом
  delayAndBlink();  
  // остановка вращения привода (85 - 90)
  servo.write(85);  
  // задержка и мигаем светодиодом
  delayAndBlink();  
  // поворот против часовой стрелки во всю скорость (127 - 170)
  servo.write(170);
  // задержка и мигаем светодиодом  
  delayAndBlink();
  // остановка вращения привода (85 - 90)
  servo.write(85);  
  // задержка и мигаем светодиодом
  delayAndBlink();  
  // отключение привода
  if (false) {
    servo.detach();
    delay(del*6);
  }
}

void testPotent() {  
  // считывем данные с потенциометра
  int potent = analogRead(5);
  // приводим диапазон значений из 0-1023 в 0-127 
  potent = map(potent, 0, 1023, 0, 127);
  // двигаем привод
  servo.write(potent);
}
