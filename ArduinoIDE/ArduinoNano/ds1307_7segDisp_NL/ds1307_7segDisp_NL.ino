
// LGT8F328, Nano, ATmega8

#define DISPLAY_CLK 5
#define DISPLAY_DIO 6

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define DS1307_ADDRESS 0x86
#define DS1307_WRITE 0xD0
#define DS1307_READ 0xD1

#define ADDR_AUTO 0x40
#define ADDR_FIXED 0x44
#define STARTADDR 0xc0


#include <Arduino.h>
#include <EEPROM.h>
#include "buildTime.h"

uint8_t update;  // флажок для обновления
uint8_t hh, mm, ss;

uint8_t digit[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6f };  // символы с 0 по 9

uint8_t Cmd_DispCtrl = 0;  //0x88;

uint8_t _DispCLKpin = 3;
uint8_t _DispDIOpin = 4;

uint8_t points = 0;

int address = 0;    // адрес ключа
uint8_t key = 235;  // ключ для проверки первого запуска

void i2c_ini(void);             // инициализация
void i2c_start(void);           // условие старт
void i2c_stop(void);            // условие стоп
void i2c_write(uint8_t byte);   /// запись байта
uint8_t i2c_read(uint8_t ack);  // чтение байта, ack!=0 с ответом, ack=0 без ответа.

void ds1307_ini(void);
void ds1307_writebyte(uint8_t reg, uint8_t byte);
uint8_t ds1307_readbyte(uint8_t reg);
void ds1307_settime(uint8_t hh, uint8_t mm, uint8_t ss);
void ds1307_gettime(uint8_t* hh, uint8_t* mm, uint8_t* ss);
void ds1307_showtime(void);

void tm1637_run(uint8_t clk_pin, uint8_t dio_pin);
void tm1637_start(void);
void tm1637_stop(void);
int tm1637_writeByte(int8_t wr_data);
void tm1637_brightness(uint8_t bri);

void tm1637_sendOne(uint8_t number, int8_t data);
void tm1637_sendAll(uint8_t data[]);
void tm1637_clear(void);

// прерывание инт0
ISR(INT0_vect) {
  update = 1;
}


// int main(void)
void setup(void)
{
  // Serial.begin(9600);
  // Serial.println("run");

  i2c_ini();     // инициализация i2c
  ds1307_ini();  // инициализация дс1307

  if (EEPROM.read(address) != key) {  // значение ключа
    EEPROM.write(address, key);
    // установить время == времени компиляции
    ds1307_settime(BUILD_HOUR, BUILD_MIN, BUILD_SEC);    
  }
  
  tm1637_run(DISPLAY_CLK, DISPLAY_DIO);  // по умолчанию CLK = 3, а DIO = 4
  tm1637_clear();
  tm1637_brightness(7);  // яркость, 0 - 7 (минимум - максимум)
  // tm1637_display(1, 2, 3, 4);

  sei(); // разрешить прерывания

  // while(1) {
  //   ds1307_showtime();
  // }
}

void loop(void) {
  ds1307_showtime();
  // if (update) Serial.println("update");
}





// натройка интерфейса на тактирование 100  гц
void i2c_ini(void) {
  TWSR = 0;
  // TWBR = F_CPU/(2*400000)-8; // 12 --> 400KHz
  TWBR = F_CPU / (2 * 100000) - 8;  // 72 --> 100KHz
  // TWBR = F_CPU/(2*50000)-8; // 152 --> 50KHz
}

//ожидание завершени¤ задани¤
void i2c_wait(void) {
  while (!(TWCR & (1 << TWINT)))
    ;
}

// условие старт
void i2c_start(void) {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  i2c_wait();
}

// условие стоп
void i2c_stop(void) {
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

// запись байта
void i2c_write(uint8_t byte) {
  TWDR = byte;
  TWCR = (1 << TWINT) | (1 << TWEN);
  i2c_wait();
}

// чтение байта, ack!=0 с ответом, ack=0 без ответа.
uint8_t i2c_read(uint8_t ack) {
  if (ack) TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  else TWCR = (1 << TWINT) | (1 << TWEN);
  i2c_wait();
  return TWDR;
}




void ds1307_ini(void) {
  uint8_t s = ds1307_readbyte(0);  // загружаем 0-й регистр
  if (s >= 128)                    // если старший бит 1
  {
    ds1307_writebyte(0, 0);  // включаем микросхему
  }
#if defined(__AVR_ATmega8__)
  MCUCR |= (1 << ISC01);// прерывание по спаду инт0 ATmega8
  GICR |= (1 << INT0);// разрешить прерывание инт0 ATmega8
#elif defined(__AVR_ATmega328P__)
  EICRA |= (1 << ISC01);      // прерывание по спаду инт0 ATmega328p
  EIMSK |= (1 << INT0);       // разрешить прерывание инт0 ATmega328p
#else
#error "unknow MK"
#endif
  ds1307_writebyte(7, 0x10);  // запуск частоты 1гц
}

void ds1307_writebyte(uint8_t reg, uint8_t byte) {
  i2c_start();              // старт
  i2c_write(DS1307_WRITE);  // адрес на запись
  i2c_write(reg);           // номер регистра
  i2c_write(byte);          // байт для записи
  i2c_stop();               // стоп
}

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


void ds1307_showtime(void) {
  if (update) {
    points = !points;
    uint8_t h, m, s;
    i2c_start();              // старт
    i2c_write(DS1307_WRITE);  //адрес на запись
    i2c_write(0);             //номер регистра
    i2c_stop();               //стоп

    i2c_start();             //старт
    i2c_write(DS1307_READ);  //адрес на чтение
    s = i2c_read(1);         // читаем байт с ответом
    m = i2c_read(1);         // читаем байт с ответом
    h = i2c_read(0);         // без ответа т.к. последний байт
    i2c_stop();              //стоп

    tm1637_display(h >> 4, h & 0x0F, m >> 4, m & 0x0F);
    update = 0;
  }
}


// tm1637
void tm1637_run(uint8_t clk_pin, uint8_t dio_pin) {
  _DispCLKpin = clk_pin;
  _DispDIOpin = dio_pin;
  pinMode(_DispCLKpin, OUTPUT);
  pinMode(_DispDIOpin, OUTPUT);
}

//send start signal
void tm1637_start(void) {
  digitalWrite(_DispCLKpin, HIGH);
  digitalWrite(_DispDIOpin, HIGH);
  digitalWrite(_DispDIOpin, LOW);
  digitalWrite(_DispCLKpin, LOW);
}
//End of transmission
void tm1637_stop(void) {
  digitalWrite(_DispCLKpin, LOW);
  digitalWrite(_DispDIOpin, LOW);
  digitalWrite(_DispCLKpin, HIGH);
  digitalWrite(_DispDIOpin, HIGH);
}

int tm1637_writeByte(int8_t wr_data) {
  uint8_t i, count1;
  for (i = 0; i < 8; i++)  //sent 8bit data
  {
    digitalWrite(_DispCLKpin, LOW);
    if (wr_data & 0x01) digitalWrite(_DispDIOpin, HIGH);  //LSB first
    else digitalWrite(_DispDIOpin, LOW);
    wr_data >>= 1;
    digitalWrite(_DispCLKpin, HIGH);
  }
  digitalWrite(_DispCLKpin, LOW);  //wait for the ACK
  digitalWrite(_DispDIOpin, HIGH);
  digitalWrite(_DispCLKpin, HIGH);
  pinMode(_DispDIOpin, INPUT);

  delayMicroseconds(50);
  uint8_t ack = digitalRead(_DispDIOpin);
  if (ack == 0) {
    pinMode(_DispDIOpin, OUTPUT);
    digitalWrite(_DispDIOpin, LOW);
  }
  delayMicroseconds(50);
  pinMode(_DispDIOpin, OUTPUT);
  delayMicroseconds(50);

  return ack;
}


void tm1637_display(uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3) {
  tm1637_sendOne(1, digit[n0]);
  tm1637_sendOne(2, digit[n1]);
  tm1637_sendOne(3, digit[n2]);
  tm1637_sendOne(4, digit[n3]);
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
  points = 0;
  tm1637_sendOne(1, 0x00);
  tm1637_sendOne(2, 0x00);
  tm1637_sendOne(3, 0x00);
  tm1637_sendOne(4, 0x00);
}
