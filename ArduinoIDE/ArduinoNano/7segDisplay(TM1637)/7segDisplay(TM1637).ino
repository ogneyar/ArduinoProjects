
// Nano, LGT8F328

//ПОДКЛЮЧЕНИЕ ДИСПЛЕЯ НА TM1637

#define CLK 2
#define DIO 3

#include <GyverTM1637.h>
GyverTM1637 disp(CLK, DIO);

void setup() {
 disp.clear();
 disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
//  disp.clear();
//  disp.displayByte(_H, _O, _L, _L);
//  disp.displayByte(_1, _2, _3, _4);
 disp.displayByte(_8, _8, _8, _8);
}

void loop(){
  disp.point(1); // показать точки
  delay(1000);
  disp.point(0); // выключить точки
  delay(1000);
}

