
// ATmega328p

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
uint8_t key = 235;  // ключ для проверки первого запуска

#include <EEPROM.h>
#include "buildTime.h"
#include "ds1307.h"
#include "st7735.h"


void showtime(void);
void beep(void);


// прерывание инт0
ISR(INT0_vect) {
  update = 1;
}


void setup(void)
{
  // Serial.begin(9600);
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
    ds1307_settime(BUILD_HOUR, BUILD_MIN, BUILD_SEC);
  }

  sei(); // разрешить прерывания
}

void loop(void) {
  showtime();
}


//
void showtime(void)
{
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

    uint8_t height_segments = 57;

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
  analogWrite(5, 30);
  delay(500);
  analogWrite(5, 130);
  delay(500);
  analogWrite(5, 30);
  delay(500);
  analogWrite(5, 130);
  delay(500);
  analogWrite(5, 220);
  delay(250);
  analogWrite(5, 190);
  delay(250);
  analogWrite(5, 160);
  delay(250);
  analogWrite(5, 0);
}
