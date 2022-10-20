// ATtiny13

//ПОДКЛЮЧЕНИЕ ДИСПЛЕЯ НА TM1637

#define CLK 3
#define DIO 4

#include <tm1637.h> // переделал библиотеку GyverTM1637, так, для изучения, для общего развития

int main(void) {
  run(CLK, DIO);
  clear();
  brightness(7);  // яркость, 0 - 7 (минимум - максимум)

  uint8_t arrayData[] = {_E, _H, _L, _O};  
  
  while (1) {
    sendAll(arrayData);
    _delay_ms(1500);
    
    sendOne(1, _H);
    sendOne(2, _E);
    _delay_ms(1000);
    
    sendOne(4, _L);
    _delay_ms(1000);
    sendOne(4, _P);
    _delay_ms(1000);
    clear();
    _delay_ms(1000);
  }
}



//#define CLK 3
//#define DIO 4
//
//#include <GyverTM1637.h>
//GyverTM1637 disp(CLK, DIO);
//
//void setup() {
//  disp.clear();
//  disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
//  disp.displayByte(_H, _O, _L, _L);
//}
//
//void loop(){}
