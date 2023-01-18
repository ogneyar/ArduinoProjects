
// LGT8F328

#define CLK 2
#define DIO 3

#include "tm1637.h" // переделал библиотеку GyverTM1637, так, для изучения

uint8_t digit[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6f};// символы с 0 по 9

void display(uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3);


int main(void) {
  run(CLK, DIO); // по умолчанию CLK = 2, а DIO = 3, так что эту строку можно за комментировать
  clear();
  brightness(7);  // яркость, 0 - 7 (минимум - максимум)

  uint8_t arrayData[] = {_E, _H, _L, _O};  

  while (1) {
    display(8, 7, 6, 5);
    _delay_ms(1500);

    sendAll(arrayData);
    _delay_ms(1500);
    
    sendOne(1, _H);
    sendOne(2, _E);
    _delay_ms(1000);
    
    sendOne(3, _L);
    _delay_ms(500);
    sendOne(4, _P);
    _delay_ms(1000);
    clear();
    _delay_ms(500);
  }
}


void display(uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3) {
  sendOne(1, digit[n0]);
  sendOne(2, digit[n1]);
  sendOne(3, digit[n2]);
  sendOne(4, digit[n3]);
}
