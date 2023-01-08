
// NodeMCU

#include <Arduino.h>
#include <U8g2lib.h>
#include <uRTCLib.h>
#include <EEPROM.h>
#include "buildTime.h"

U8G2_SH1106_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 5, /* data=*/ 4, /* reset=*/ U8X8_PIN_NONE); // D1 and D2 on ESP8266
uRTCLib rtc(0x68);

int address = 0;   // адрес ключа
uint8_t key = 238; // ключ для проверки первого запуска  
uint32_t timeMillis = 0;
uint32_t current = 0;
uint16_t target = 1000;
uint8_t dots = 1;


// настройки
void setup(void)
{
  URTCLIB_WIRE.begin(0, 2); // D3 and D4 on ESP8266  
  
  EEPROM.begin(512);  
  if (EEPROM.read(address) != key) { // значение ключа
    EEPROM.write(address, key);
    EEPROM.commit();
    // установить время == времени компиляции
    rtc.set(BUILD_SEC, BUILD_MIN, BUILD_HOUR, 6, BUILD_DAY, BUILD_MONTH, BUILD_YEAR);  // 6 - dayOfWeek
  }
  
  u8g2.begin();
  u8g2.enableUTF8Print();
}

// беЗконечный цикл
void loop(void) {  
  timeMillis = millis();
  if (timeMillis - current > target) {    
    current = timeMillis;    
    dots = !dots;
    printTime(dots);
  }
}

// вывод времени на дисплей
void printTime(uint8_t _dots) {
  rtc.refresh();
  
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_unifont_t_cyrillic);
  u8g2.setCursor(4, 12);
  u8g2.print("Часы Sвенирады!");  

  u8g2.setFont(u8g2_font_7Segments_26x42_mn);
  u8g2.setCursor(2, 63);
  uint8_t hour = rtc.hour();
  if (hour < 10) u8g2.print(0);
  u8g2.print(hour);    
  uint8_t minute = rtc.minute();
  if (minute < 10) u8g2.print(0);
  u8g2.print(minute);  
  
  u8g2.setFont(u8g2_font_crox5tb_tn);
  u8g2.setCursor(59, 50);  
  if (_dots) u8g2.print(".");
  else u8g2.print(" ");  
  u8g2.setCursor(59, 38);
  if (_dots) u8g2.print(".");
  else u8g2.print(" ");    
  
  u8g2.sendBuffer();
}
