
// ATmega8

// INT0 на PD2
// I2C_CLK на PC5 (A5)
// I2C_DIO на PC4 (A4)

// DISPLAY_CLK на PB5
// DISPLAY_DIO на PB3
// DISPLAY_CS на PB2
// DISPLAY_BLK на PB1
// DISPLAY_DC на PB0
// DISPLAY_RES на PD7

uint8_t update;  // флажок для обновления
uint8_t segment1 = 10;
uint8_t segment2 = 10;
uint8_t segment3 = 10;
uint8_t segment4 = 10;
uint8_t points = 0;

int address = 0;    // адрес ключа
uint8_t key = 236;  // ключ для проверки первого запуска

bool settingPressed = false;
bool flagButton1 = false;
bool flagButton2 = false;
bool flagButton3 = false;
uint8_t h, m, s;
uint8_t hour1, hour2;
uint8_t min1, min2;
uint8_t height_segments = 57;

/***************
for beep atmega8
****************/
//---------------------
#if defined(__AVR_ATmega8__)
byte pin = 5;
byte value = 255;
int pause1 = 0x000001c0;
int pause2 = 0x00000180;
#endif
//---------------------

#define button1Pin A0 // кнопка настроек
#define button2Pin A1 // кнопка часов
#define button3Pin A2 // кнопка минут

#include <EEPROM.h>
#include "buildTime.h"
#include "ds1307.h"
#include "st7735.h"


bool setTime(void);
void showTime(void);
void beep(void);

/***************
for beep atmega8
****************/
//---------------------
#if defined(__AVR_ATmega8__)
void beep7(int pause = pause1);
void beep6(int pause = pause1);
void beep5(int pause = pause1);
void beep4(int pause = pause1);
void beep3(int pause = pause2);
void beep2(int pause = pause2);
void beep1(int pause = pause2);
#endif
//---------------------


// прерывание инт0
ISR(INT0_vect) {
  update = 1;
}


void setup(void)
{
  // Serial.begin(115200);
  pinMode(button1Pin, INPUT_PULLUP); // кнопка настроек
  pinMode(button2Pin, INPUT_PULLUP); // кнопка часов
  pinMode(button3Pin, INPUT_PULLUP); // кнопка минут

  analogWrite(9, 30); // back light
  
  SPI_Master_Init();
  st7735_init();
  st7735_clear();

  st7735_test_screen(100);

  st7735_setFontBgColor(BLACK); 
  st7735_setFontColor(OLIVE); 
  st7735_setFontDotColor(DARKGREY); 
  st7735_fill(textbgcolor);
  st7735_setFontSize(10, 8);

  i2c_ini();     // инициализация i2c
  ds1307_ini();  // инициализация дс1307

  if (EEPROM.read(address) != key) {  // значение ключа
    EEPROM.write(address, key);
    // установить время == времени компиляции
    ds1307_settime(BUILD_HOUR, BUILD_MIN+1, 0);
  }

  sei(); // разрешить прерывания
}

void loop(void) {
  if ( ! settingPressed ) showTime();
  settingPressed = setTime();
}

//
bool setTime(void)
{  

  boolean button1 = !digitalRead(button1Pin);
  if (button1 == true && flagButton1 == false) {
    flagButton1 = true;
    // Serial.println("Button1 pressed");

    /*
      читаем время
    */
    
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

    delay(10);
  }
  if (button1 == false && flagButton1 == true) {
    flagButton1 = false;
    // Serial.println("Button1 released");

    /*
      записываем время
    */

    ds1307_settime(( (h >> 4) * 10 + (h & 0x0F) ), ( (m >> 4) * 10 + (m & 0x0F) ), 0x00);

    delay(10);
  }

  boolean button2 = !digitalRead(button2Pin);
  if (button2 == true && flagButton2 == false) {
    flagButton2 = true;
    // Serial.println("Button2 pressed");
    delay(10);
  }
  if (button2 == false && flagButton2 == true) {
    flagButton2 = false;
    // Serial.println("Button2 released");
    
    /*
      меняем часы
    */
    if (flagButton1) // если нажата кнопка настроек
    {
      // if (update) Serial.println(h);
      hour1 = (h >> 4);
      hour2 = (h & 0x0f);

      if (hour2 == 9)
      {
        hour2 = 0;
        if (hour1 == 1) hour1 = 2;
        else hour1 = 1;
      }
      else 
      {
        if (hour1 == 2 && hour2 == 3) 
        {
          hour1 = 0;
          hour2 = 0;
        }
        else hour2 += 1;
      }
      
      h = (hour1 << 4) | (hour2);

      if (segment1 != (h >> 4))
      {
        st7735_setCursor(10, height_segments);
        st7735_printNum(segment1, textbgcolor);
        segment1 = (h >> 4);
        st7735_setCursor(10, height_segments);
        st7735_printNum(segment1);
      }
      
      if (segment2 != (h & 0x0F))
      {
        st7735_setCursor(45, height_segments);
        st7735_printNum(segment2, textbgcolor);
        segment2 = (h & 0x0F);
        st7735_setCursor(45, height_segments);
        st7735_printNum(segment2);
      }

    }

    delay(10);
  }
  
  boolean button3 = !digitalRead(button3Pin);
  if (button3 == true && flagButton3 == false) {
    flagButton3 = true;
    // Serial.println("Button3 pressed");
    delay(10);
  }
  if (button3 == false && flagButton3 == true) {
    flagButton3 = false;
    // Serial.println("Button3 released");

    /*
      меняем минуты
    */
    if (flagButton1) // если нажата кнопка настроек
    {
      // if (update) Serial.println(m);
      min1 = (m >> 4);
      min2 = (m & 0x0f);
      
      if (min2 == 9)
      {
        min2 = 0;
        if (min1 == 5) min1 = 0;
        else min1 += 1;
      }
      else 
      {
        min2 += 1;
      }
      
      m = (min1 << 4) | (min2);
      
      if (segment3 != (m >> 4))
      {
        st7735_setCursor(95, height_segments);
        st7735_printNum(segment3, textbgcolor);
        segment3 = (m >> 4);
        st7735_setCursor(95, height_segments);
        st7735_printNum(segment3);
      }
      
      if (segment4 != (m & 0x0F))
      {
        st7735_setCursor(130, height_segments);
        st7735_printNum(segment4, textbgcolor);
        segment4 = (m & 0x0F);
        st7735_setCursor(130, height_segments);
        st7735_printNum(segment4);
      }
    }

    delay(10);
  }

  return flagButton1;
}

//
void showTime(void)
{
  if (update)
  {
    points = !points;
    // uint8_t h, m, s;
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

    if (segment1 != (h >> 4))
    {
      st7735_setCursor(10, height_segments);
      st7735_printNum(segment1, textbgcolor);
      segment1 = (h >> 4);
      st7735_setCursor(10, height_segments);
      st7735_printNum(segment1);
    }
    
    if (segment2 != (h & 0x0F))
    {
      st7735_setCursor(45, height_segments);
      st7735_printNum(segment2, textbgcolor);
      segment2 = (h & 0x0F);
      st7735_setCursor(45, height_segments);
      st7735_printNum(segment2);
    }

    st7735_setCursor(78, height_segments);
    if (points) st7735_print(":", dotcolor);
    else st7735_print(":", textbgcolor);
    
    if (segment3 != (m >> 4))
    {
      st7735_setCursor(95, height_segments);
      st7735_printNum(segment3, textbgcolor);
      segment3 = (m >> 4);
      st7735_setCursor(95, height_segments);
      st7735_printNum(segment3);
    }
    
    if (segment4 != (m & 0x0F))
    {
      st7735_setCursor(130, height_segments);
      st7735_printNum(segment4, textbgcolor);
      segment4 = (m & 0x0F);
      st7735_setCursor(130, height_segments);
      st7735_printNum(segment4);
    }
    
    // st7735_print(":");
    // st7735_printNum(s >> 4);
    // st7735_printNum(s & 0x0F);

    // Serial.print("h: ");
    // Serial.println(h);
    // Serial.print("m: ");
    // Serial.println(m);
    // Serial.print("s: ");
    // Serial.println(s);
    
    if ((segment1 == 1 && segment2 == 1 && segment3 == 0 && segment4 == 0 && (s >> 4) == 0) 
      || (segment1 == 1 && segment2 == 7 && segment3 == 0 && segment4 == 0 && (s >> 4) == 0)) 
    {
      beep();
    }

    update = 0;
  }
}

void beep(void)
{
#if defined(__AVR_ATmega8__)
  beep4();
  beep7();
  beep4();
  beep6();
  beep3();
  beep2();
  beep1();
#elif defined(__AVR_ATmega328P__)
  analogWrite(5, 30);
  delay(400);
  analogWrite(5, 130);
  delay(400);
  analogWrite(5, 30);
  delay(400);
  analogWrite(5, 130);
  delay(400);
  analogWrite(5, 220);
  delay(200);
  analogWrite(5, 190);
  delay(200);
  analogWrite(5, 160);
  delay(200);
  analogWrite(5, 0);
  delay(1000);
#else
#error "beep(): unknow MK"
#endif
}


/**********************************************
****************
beep for atmega8 (цыганский стиль)
****************
**********************************************/

#if defined(__AVR_ATmega8__)
//
void beep7(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(700);
  }
}
//
void beep6(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(600);
  }
}
//
void beep5(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(500);
  }
}
//
void beep4(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(400);
  }
}
//
void beep3(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(300);
  }
}
//
void beep2(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(200);
  }
}
//
void beep1(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(100);
  }
}
#endif

/**********************************************
****************
*******
****************
**********************************************/
