
// NodeMCU

#include <Arduino.h>
#include <U8g2lib.h>


#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#include "buildTime.h" // библиотека BuildTime от AlexGyver

uint8_t time[] = __TIME__;
uint8_t hour = __TIME__; //BUILD_HOUR;
uint8_t min = BUILD_MIN;

void printTime(uint8_t _hour, uint8_t _min, bool dotted);

// настройки
void setup(void)
{
  u8g2.begin();
  u8g2.enableUTF8Print();
}

// беЗконечный цикл
void loop(void) {
  printTime(hour, min, true);

  delay(1000);
  
  printTime(hour, min, false);

  delay(1000);
}

// вывод времени на дисплей
void printTime(uint8_t _hour, uint8_t _min, uint8_t dotted) {
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_cyrillic);
  u8g2.setCursor(6, 12);
  u8g2.print("Часы Sвенирады!");
  
  u8g2.setFont(u8g2_font_7Segments_26x42_mn);
  u8g2.setCursor(2, 63);
  //u8g2.print("8888");
  u8g2.print(_hour);
  u8g2.print(_min);
  
  u8g2.setFont(u8g2_font_crox5tb_tn);
  u8g2.setCursor(59, 50);
  if (dotted) u8g2.print(".");
  else u8g2.print(" ");  
  u8g2.setCursor(59, 38);
  if (dotted) u8g2.print(".");
  else u8g2.print(" ");  
  
  u8g2.sendBuffer();
}

