
// библиотека 4х разрядного семисегментного индикатрора (циферблата)

//*****definitions for TM1637*****
#define ADDR_AUTO 0x40
#define ADDR_FIXED 0x44
#define STARTADDR 0xc0

#include <inttypes.h>
#include <Arduino.h>
#include <util/delay.h>


uint8_t digit[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6f };  // символы с 0 по 9

uint8_t Cmd_DispCtrl = 0;  //0x88;
uint8_t points = 0;

uint8_t CLKpin = 3;
uint8_t DIOpin = 4;


void tm1637_run(uint8_t clk_pin, uint8_t dio_pin) {
  CLKpin = clk_pin;
  DIOpin = dio_pin;
  pinMode(CLKpin, OUTPUT);
  pinMode(DIOpin, OUTPUT);
}

//send start signal
void tm1637_start(void) {
  digitalWrite(CLKpin, HIGH);
  digitalWrite(DIOpin, HIGH);
  digitalWrite(DIOpin, LOW);
  digitalWrite(CLKpin, LOW);
}
//End of transmission
void tm1637_stop(void) {
  digitalWrite(CLKpin, LOW);
  digitalWrite(DIOpin, LOW);
  digitalWrite(CLKpin, HIGH);
  digitalWrite(DIOpin, HIGH);
}

int tm1637_writeByte(int8_t wr_data) {
  uint8_t i, count1;
  for (i = 0; i < 8; i++)  //sent 8bit data
  {
    digitalWrite(CLKpin, LOW);
    if (wr_data & 0x01) digitalWrite(DIOpin, HIGH);  //LSB first
    else digitalWrite(DIOpin, LOW);
    wr_data >>= 1;
    digitalWrite(CLKpin, HIGH);
  }
  digitalWrite(CLKpin, LOW);  //wait for the ACK
  digitalWrite(DIOpin, HIGH);
  digitalWrite(CLKpin, HIGH);
  pinMode(DIOpin, INPUT);

  delayMicroseconds(50);
  uint8_t ack = digitalRead(DIOpin);
  if (ack == 0) {
    pinMode(DIOpin, OUTPUT);
    digitalWrite(DIOpin, LOW);
  }
  delayMicroseconds(50);
  pinMode(DIOpin, OUTPUT);
  delayMicroseconds(50);

  return ack;
}

// установка яркости экрана
void tm1637_brightness(uint8_t bri) {
  Cmd_DispCtrl = 0x88 + bri;
}

// показывать ли точки
void tm1637_point(uint8_t pointFlag) {
  points = pointFlag;
}

// функция отправки данных на дисплей
void tm1637_sendOne(uint8_t number, int8_t data) {
  tm1637_start();
  tm1637_writeByte(ADDR_FIXED);              //
  tm1637_stop();                             //
  tm1637_start();                            //
  tm1637_writeByte(number - 1 | STARTADDR);  //
  if (points) tm1637_writeByte(data | 0x80);
  else tm1637_writeByte(data);     //
  tm1637_stop();                   //
  tm1637_start();                  //
  tm1637_writeByte(Cmd_DispCtrl);  //
  tm1637_stop();                   //
}

// отображение массива данных
void tm1637_sendAll(uint8_t data[]) {
  tm1637_start();
  tm1637_writeByte(ADDR_AUTO);  //
  tm1637_stop();                //
  tm1637_start();               //
  tm1637_writeByte(STARTADDR);  //
  for (byte i = 0; i < 4; i++) {
    if (points) tm1637_writeByte(data[i] | 0x80);
    else tm1637_writeByte(data[i]);  //
  }
  tm1637_stop();                   //
  tm1637_start();                  //
  tm1637_writeByte(Cmd_DispCtrl);  //
  tm1637_stop();                   //
}

// очистка экрана
void tm1637_clear(void) {
  tm1637_sendOne(1, 0x00);
  tm1637_sendOne(2, 0x00);
  tm1637_sendOne(3, 0x00);
  tm1637_sendOne(4, 0x00);
}


void tm1637_display(uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3) {
  tm1637_sendOne(1, digit[n0]);
  tm1637_sendOne(2, digit[n1]);
  tm1637_sendOne(3, digit[n2]);
  tm1637_sendOne(4, digit[n3]);
}

#define _A 0x77
#define _B 0x7f
#define _C 0x39
#define _D 0x3f
#define _E 0x79
#define _F 0x71
#define _G 0x3d
#define _H 0x76
#define _I 0x06
#define _J 0x1e
#define _L 0x38
#define _N 0x37
#define _O 0x3f
#define _P 0x73
#define _S 0x6d
#define _U 0x3e
#define _Y 0x6e
#define _a 0x5f
#define _b 0x7c
#define _c 0x58
#define _d 0x5e
#define _e 0x7b
#define _f 0x71
#define _h 0x74
#define _i 0x10
#define _j 0x0e
#define _l 0x06
#define _n 0x54
#define _o 0x5c
#define _q 0x67
#define _r 0x50
#define _t 0x78
#define _u 0x1c
#define _y 0x6e
#define _dash 0x40
#define _under 0x08
#define _equal 0x48
#define _empty 0x00
#define _degree 0x63

#define _0 0x3f
#define _1 0x06
#define _2 0x5b
#define _3 0x4f
#define _4 0x66
#define _5 0x6d
#define _6 0x7d
#define _7 0x07
#define _8 0x7f
#define _9 0x6f
