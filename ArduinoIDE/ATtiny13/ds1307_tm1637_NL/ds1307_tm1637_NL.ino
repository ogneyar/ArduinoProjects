
// ATtiny13

// INT0 на PB1
// I2C_CLK на PB0
// I2C_DIO на PB2
// DISPLAY_CLK на PB3
// DISPLAY_DIO на PB4

#include "defines.h"

uint8_t update = 1;  // флажок для обновления
uint8_t digit[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6f };  // символы с 0 по 9
uint8_t Cmd_DispCtrl = 0;  //0x88;
uint8_t points = 1;


void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_read(uint8_t ack);
uint8_t i2c_write(uint8_t data);

void ds1307_ini(void);
void ds1307_writebyte(uint8_t reg, uint8_t byte);
uint8_t ds1307_readbyte(uint8_t reg);
void ds1307_settime(uint8_t hh, uint8_t mm, uint8_t ss);
void ds1307_showtime(void);

void tm1637_init(uint8_t bright);
void tm1637_start(void);
void tm1637_stop(void);
int tm1637_writeByte(int8_t wr_data);
void tm1637_brightness(uint8_t bri);
void tm1637_point(uint8_t pointFlag);
void tm1637_sendOne(uint8_t number, int8_t data);

// прерывание инт0
ISR(INT0_vect) {
  update = 1;
}


//
void setup(void)
{
  ds1307_ini();  // инициализация дс1307

  // EEPROM_read  
  while(EECR & (1<<EEPE)) ;
  EEARL = EEPROM_TIME_ADDRESS;
  EECR |= (1<<EERE);
  
  if (EEDR != EEPROM_TIME_KEY) {  // значение ключа    
    // EEPROM_write
    while(EECR & (1<<EEPE)) ;
    EECR = (0<<EEPM1)|(0>>EEPM0);
    EEARL = EEPROM_TIME_ADDRESS;
    EEDR = EEPROM_TIME_KEY;
    EECR |= (1<<EEMPE);
    EECR |= (1<<EEPE);
    // установить время == времени компиляции
    ds1307_settime(BUILD_HOUR, BUILD_MIN, BUILD_SEC);    
  }
  
  tm1637_init(3);  // 3 - яркость, 0 - 7 (минимум - максимум)
  tm1637_display(8, 8, 8, 8);

  sei(); // разрешить прерывания
}

void loop(void) {
  ds1307_showtime();// работает пока без прерываний с delay
}



//-------------------------------- I2C ------------------------------------------

// старт
void i2c_start(void){
	I2C_SDA_0;
	I2C_DELAY;
	I2C_SCL_0;
}

// стоп 
void i2c_stop(void){
	I2C_SDA_0;
	I2C_DELAY;
	I2C_SCL_1;
	I2C_DELAY;
	I2C_SDA_1;
}

// отправка байта
uint8_t i2c_write(uint8_t data){
	uint8_t i=8, ask;
	while (i--)
	{
		if(data & (1 << i)) I2C_SDA_1;// если бит 1 ставим 1 на линию
		else I2C_SDA_0;// ставим 0 на линию
		I2C_DELAY;
		I2C_SCL_1;// фронт
		I2C_DELAY;
		I2C_SCL_0;// спад
	}
	I2C_SDA_1;// отпустить дата
	I2C_DELAY;
	I2C_SCL_1;// фронт такта
	I2C_DELAY;
	ask=(I2C_SDA_PIN & (1 << I2C_SDA));// читаем линию сда
	I2C_SCL_0;// спад
	return ask;//  0 - ask, не 0 - nask
}

// получение байта
uint8_t i2c_read(uint8_t ack){
	uint8_t byte=0, i=8;
	while(i--)
	{
		I2C_SCL_1;// фронт такта
		I2C_DELAY;
		if(I2C_SDA_PIN & (1 << I2C_SDA)) byte |= (1 << i);// если SDA 1 в и-тый бит пишем 1
		I2C_SCL_0;// спад такта
		I2C_DELAY;
	}
	if(ack) I2C_SDA_0;// ask или nask
	else I2C_SDA_1;
	
	I2C_SCL_1;//
	I2C_DELAY;// такт на получения ответа или неответа
	I2C_SCL_0;//
	I2C_DELAY;
	I2C_SDA_1;// отпустить сда если притянут
	return byte;
}

//-------------------------------------------------------------------------------


//-------------------------------- DS1307 ---------------------------------------

//
void ds1307_ini(void) 
{
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
#elif defined(__AVR_ATtiny13__)
  MCUCR |= (1 << ISC01); // прерывание по спаду инт0 ATtiny13
  GIMSK |= (1 << INT0); // разрешить прерывание инт0 ATtiny13
#else
#error "unknow MK"
#endif
  ds1307_writebyte(7, 0x10);  // запуск частоты 1гц
}

//
void ds1307_writebyte(uint8_t reg, uint8_t byte) 
{
  i2c_start();              // старт
  i2c_write(DS1307_WRITE);  // адрес на запись
  i2c_write(reg);           // номер регистра
  i2c_write(byte);          // байт для записи
  i2c_stop();               // стоп
}

//
uint8_t ds1307_readbyte(uint8_t reg) 
{
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
void ds1307_settime(uint8_t hh, uint8_t mm, uint8_t ss)
{
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
    // update = 0;
    delay(1000);
  }
}

//-------------------------------------------------------------------------------


//-------------------------------- TM1637 ---------------------------------------

// tm1637 initialization
void tm1637_init(uint8_t bright) {
  DDRB |= (1 << DISPLAY_CLK) |  (1 << DISPLAY_DIO);  // CLK OUTPUT, DIO OUTPUT
  tm1637_brightness(bright);
}

//send start signal
void tm1637_start(void) {
  PORTB |= (1 << DISPLAY_CLK); // CLK HIGH
  PORTB |= (1 << DISPLAY_DIO); // DIO HIGH
  PORTB &= ~(1 << DISPLAY_DIO); // DIO LOW
  PORTB &= ~(1 << DISPLAY_CLK); // CLK LOW
}

//End of transmission
void tm1637_stop(void) {
  PORTB &= ~(1 << DISPLAY_CLK); // CLK LOW
  PORTB &= ~(1 << DISPLAY_DIO); // DIO LOW
  PORTB |= (1 << DISPLAY_CLK); // CLK HIGH
  PORTB |= (1 << DISPLAY_DIO); // DIO HIGH
}

//
int tm1637_writeByte(int8_t wr_data) {
  uint8_t i, count1;
  for (i = 0; i < 8; i++)  //sent 8bit data
  {
    PORTB &= ~(1 << DISPLAY_CLK); // CLK LOW
    if (wr_data & 0x01) PORTB |= (1 << DISPLAY_DIO); // DIO HIGH
    else PORTB &= ~(1 << DISPLAY_DIO); // DIO LOW
    wr_data >>= 1;
    PORTB |= (1 << DISPLAY_CLK); // CLK HIGH
  }
  PORTB &= ~(1 << DISPLAY_CLK); // CLK LOW
  PORTB |= (1 << DISPLAY_DIO); // DIO HIGH
  PORTB |= (1 << DISPLAY_CLK); // CLK HIGH
  DDRB &= ~(1 << DISPLAY_DIO); // DIO INPUT

  delayMicroseconds(50);
  uint8_t ack = PINB & (1 << DISPLAY_DIO);
  if (ack == 0) {
    DDRB |= (1 << DISPLAY_DIO); // DIO OUTPUT
    PORTB &= ~(1 << DISPLAY_DIO); // DIO LOW
  }
  delayMicroseconds(50);
  DDRB |= (1 << DISPLAY_DIO); // DIO OUTPUT
  delayMicroseconds(50);

  return ack;
}

//
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

//-------------------------------------------------------------------------------

//