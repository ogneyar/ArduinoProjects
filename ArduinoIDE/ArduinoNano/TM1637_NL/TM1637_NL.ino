
// LGT8F328

#define CLK 3
#define DIO 4

#include "tm1637.h" // переделал библиотеку GyverTM1637, так, для изучения


int main(void) {
  tm1637_run(CLK, DIO); // по умолчанию CLK = 3, а DIO = 4
  tm1637_clear();
  tm1637_brightness(7);  // яркость, 0 - 7 (минимум - максимум)

  uint8_t arrayData[] = {_E, _H, _L, _O};  

  uint8_t pointFlag = 0;

  while (1) {
    tm1637_display(8, 7, 6, 5);
    _delay_ms(500);

    tm1637_sendAll(arrayData);
    _delay_ms(500);
    
    tm1637_sendOne(1, _H);
    tm1637_sendOne(2, _E);
    _delay_ms(100);
    
    pointFlag = ! pointFlag;
    tm1637_point(pointFlag);

    tm1637_sendOne(4, _L);
    _delay_ms(50);
    tm1637_sendOne(4, _P);
    _delay_ms(100);
    tm1637_clear();
    _delay_ms(50);
  }
}


