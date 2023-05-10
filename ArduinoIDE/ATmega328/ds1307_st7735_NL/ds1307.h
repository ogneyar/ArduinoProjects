
#ifndef _DS1307_H_
#define _DS1307_H_

#include "st7735.h"
#include "i2c.h"

#define DS1307_ADDRESS 0x86
#define DS1307_WRITE 0xD0
#define DS1307_READ 0xD1


void ds1307_ini(void);
void ds1307_writebyte(uint8_t reg, uint8_t byte);
uint8_t ds1307_readbyte(uint8_t reg);
void ds1307_settime(uint8_t hh, uint8_t mm, uint8_t ss);
void ds1307_gettime(uint8_t* hh, uint8_t* mm, uint8_t* ss);


//
void ds1307_ini(void) {
  uint8_t s = ds1307_readbyte(0);  // загружаем 0-й регистр  
  if (s >= 128)                    // если старший бит 1
  {
    ds1307_writebyte(0, 0);  // включаем микросхему
  }
// #if defined(__AVR_ATmega8__)
//   MCUCR |= (1 << ISC01);// прерывание по спаду инт0 ATmega8
//   GICR |= (1 << INT0);// разрешить прерывание инт0 ATmega8
// #elif defined(__AVR_ATmega328P__)
  EICRA |= (1 << ISC01);      // прерывание по спаду инт0 ATmega328p
  EIMSK |= (1 << INT0);       // разрешить прерывание инт0 ATmega328p
// #else
// #error "unknow MK"
// #endif
  ds1307_writebyte(7, 0x10);  // запуск частоты 1гц
}

//
void ds1307_writebyte(uint8_t reg, uint8_t byte) {
  i2c_start();              // старт
  i2c_write(DS1307_WRITE);  // адрес на запись
  i2c_write(reg);           // номер регистра
  i2c_write(byte);          // байт для записи
  i2c_stop();               // стоп
}

//
uint8_t ds1307_readbyte(uint8_t reg) {
  uint8_t byte;
  i2c_start();              // старт
  i2c_write(DS1307_WRITE);  //адрес на запись
  i2c_write(reg);           //номер регистра
  i2c_stop();               //стоп

  i2c_start();             //старт
  i2c_write(DS1307_READ);  //адрес на чтение
  byte = i2c_read(0);      //читаем байт без ответа
  i2c_stop();              //стоп

  return byte;  //вернем полученный байт
}

//
void ds1307_settime(uint8_t hh, uint8_t mm, uint8_t ss) {

  uint8_t h, m, s;
  // конвертим из 10-тичной в двоично десятичный
  s = ((ss / 10) << 4) | (ss % 10);
  m = ((mm / 10) << 4) | (mm % 10);
  h = ((hh / 10) << 4) | (hh % 10);

  i2c_start();              // старт
  i2c_write(DS1307_WRITE);  // адрес на запись
  i2c_write(0);             // номер начального регистра
  i2c_write(s);             // байт с секундами
  i2c_write(m);             // байт с минутами
  i2c_write(h);             // байт с часами
  i2c_stop();
}

//
void ds1307_gettime(uint8_t* hh, uint8_t* mm, uint8_t* ss) {
  uint8_t h, m, s;

  i2c_start();              // старт
  i2c_write(DS1307_WRITE);  //адрес на запись
  i2c_write(0);             //номер регистра
  i2c_stop();               //стоп

  i2c_start();             //старт
  i2c_write(DS1307_READ);  //адрес на чтение
  s = i2c_read(1);         //читаем байт с ответом
  m = i2c_read(1);
  h = i2c_read(0);  // без ответа т.к. последний байт
  i2c_stop();       //стоп

  // конвертим мз воично есятичного в десятичный
  *ss = (s >> 4) * 10 + (s & 0x0F);
  *mm = (m >> 4) * 10 + (m & 0x0F);
  *hh = (h >> 4) * 10 + (h & 0x0F);
}



#endif  /* _DS1307_H_ */
