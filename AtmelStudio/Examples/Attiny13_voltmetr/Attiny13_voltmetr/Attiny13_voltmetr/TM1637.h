#ifndef TM1637_H_
#define TM1637_H_

//------------- настройка подключени€ индикатора, ножки  PB0 и PB1 (дл€ изменени€ порта мен€ть в коде функций)----------
#define _CLK PB0
#define _DIO PB1
//------------------------------------------------------------------


//------------- €ркость свечени€ индикатора ----------
#define Bright0 0x88
#define Bright1 0x89
#define Bright2 0x8A
#define Bright3 0x8B
#define Bright4 0x8C
#define Bright5 0x8D
#define Bright6 0x8E
#define Bright7 0x8F
#define SetBright Bright1 //сюда прописать €ркость от 0 до 7
//------------------------------------------------------------------




void indication(uint16_t n);

void start(void);
void stop(void);
void writeValue(uint8_t value);


#endif /* TM1637_H_ */