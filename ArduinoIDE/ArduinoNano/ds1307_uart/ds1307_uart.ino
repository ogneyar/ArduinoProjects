
// LGT8F328

// INT0 на PD2
// I2C_CLK на PC5 (A5)
// I2C_DIO на PC4 (A4)


#define DS1307_ADDRESS 0x86
#define DS1307_WRITE 0xD0
#define DS1307_READ 0xD1

#include <EEPROM.h>
#include "buildTime.h"

// uint8_t update;  // флажок для обновления

int address = 0;    // адрес ключа
uint8_t key = 138;  // ключ для проверки первого запуска

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


// прерывание инт0
// ISR(INT0_vect) {
//   update = 1;
// }


void setup(void)
{
  Serial.begin(9600);    
  i2c_ini();     // инициализация i2c
  ds1307_ini();  // инициализация дс1307

  if (EEPROM.read(address) != key) {  // значение ключа
    EEPROM.write(address, key);
    // установить время == времени компиляции
    ds1307_settime(BUILD_HOUR, BUILD_MIN, BUILD_SEC);    
  }
  
  // sei(); // разрешить прерывания
}

void loop(void) {
  ds1307_showtime();
  delay(1000);
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
// #if defined(__AVR_ATmega8__)
//   MCUCR |= (1 << ISC01);// прерывание по спаду инт0 ATmega8
//   GICR |= (1 << INT0);// разрешить прерывание инт0 ATmega8
// #elif defined(__AVR_ATmega328P__)
//   EICRA |= (1 << ISC01);      // прерывание по спаду инт0 ATmega328p
//   EIMSK |= (1 << INT0);       // разрешить прерывание инт0 ATmega328p
// #else
// #error "unknow MK"
// #endif
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
  // if (update) {
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
    
    Serial.print(h >> 4);    
    Serial.print(h & 0x0F);    
    Serial.print(":");    
    Serial.print(m >> 4);    
    Serial.print(m & 0x0F);   
    Serial.print(":");    
    Serial.print(s >> 4);    
    Serial.println(s & 0x0F); 
      
    // update = 0;
  // }
}

