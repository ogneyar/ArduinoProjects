
// Uno, Mega

#include "defines.h"
#include "tft.h"

bool good = false;

// установки / настройки
void setup(void) 
{
#ifdef __DEBUG
#ifdef __SAMD21G18A__
  SerialUSB.begin(9600);
  while(!SerialUSB) 
    ;
  SerialUSB.println("Show BMP files on TFT");
  SerialUSB.print("F_CPU: ");
  SerialUSB.println(F_CPU);
#else
  Serial.begin(9600);
  Serial.println("Show BMP files on TFT");
  Serial.print("F_CPU: ");
  Serial.println(F_CPU);
#endif
  delay(2000);
#endif   
    
  begin();
  testScreen();
    
  good = SD.begin(F_CPU/2,SD_CS);
  if (!good) {
#ifdef __DEBUG
#ifdef __SAMD21G18A__
    SerialUSB.println(F("cannot start SD"));
#else
    Serial.println(F("cannot start SD"));
#endif
#endif      
    // return;
    // while(1) ;
  }
  
#ifndef __SAMD21G18A__
  spi_save = SPCR;
#endif
  
}

// основной цикл программы
void loop(void) 
{
  uint16_t del = 80;
  
  fillDelay(0xf800, del);
  if (good) bmpDraw("01.bmp", 0, 0); //  
#ifdef __DEBUG
#ifdef __SAMD21G18A__
  SerialUSB.println();
  SerialUSB.println(F("bmpDraw '01.bmp'"));
#else
  Serial.println();
  Serial.println(F("bmpDraw '01.bmp'"));
#endif
#endif      
  delay(3000);
   
  fillDelay(0x0ff0, del);
  if (good) bmpDraw("02.bmp", 0, 0);
#ifdef __DEBUG
#ifdef __SAMD21G18A__
  SerialUSB.println();
  SerialUSB.println(F("bmpDraw '02.bmp'"));
#else
  Serial.println();
  Serial.println(F("bmpDraw '02.bmp'"));
#endif
#endif      
  delay(3000);
   
  fillDelay(0x008f, del);
  if (good) bmpDraw("03.bmp", 0, 0);
#ifdef __DEBUG
#ifdef __SAMD21G18A__
  SerialUSB.println();
  SerialUSB.println(F("bmpDraw '03.bmp'"));
#else
  Serial.println();
  Serial.println(F("bmpDraw '03.bmp'"));
#endif
#endif      
  delay(3000);
#ifdef __DEBUG
#ifdef __SAMD21G18A__
  SerialUSB.println();
  SerialUSB.println("loop...");
#else
  Serial.println();
  Serial.println("loop...");
#endif
#endif
}


// тестирование дисплея
void testScreen(void) 
{
  uint8_t x, y;
  uint16_t del = 500;
  fill(0xf800);
  delay(del);
  x = 60, y = 160;
  while(x++ < 180) drawPixel(x, y, 0xffff);
  x = 120, y = 80;
  while(y++ < 240) drawPixel(x, y, 0xffff);
  delay(del);
  fillScreen(0x0ff0);
  delay(del);
  x = 60, y = 160;
  while(x++ < 180) drawPixel(x, y, 0xffff);
  x = 120, y = 80;
  while(y++ < 240) drawPixel(x, y, 0xffff);
  delay(del);
  fill(0x008f);
  delay(del);
  x = 60, y = 160;
  while(x++ < 180) drawPixel(x, y, 0xffff);
  x = 120, y = 80;
  while(y++ < 240) drawPixel(x, y, 0xffff);
  delay(del);
#ifdef __DEBUG
#ifdef __SAMD21G18A__
    SerialUSB.println("test screen...");
#else
    Serial.println("test screen...");
#endif
#endif
}


 
 
