
// Uno, Mega

#define __DEBUG 1

#include "defines.h"
#include "tft.h"


// установки / настройки
void setup(void) 
{
#ifdef __DEBUG
  Serial.begin(9600);
  Serial.print("Show BMP files on TFT");
#endif   
    
  begin();
  testScreen();
    
  bool good = SD.begin(SD_CS);
  if (!good) {
#ifdef __DEBUG
    Serial.print(F("cannot start SD"));
#endif      
    return;
  }
  spi_save = SPCR;
}

// основной цикл программы
void loop(void) 
{
  uint16_t del = 80;
  
  fillDelay(0xf800, del);
  bmpDraw("01.bmp", 0, 0); //
  delay(3000);
   
  fillDelay(0x0ff0, del);
  bmpDraw("02.bmp", 0, 0);
  delay(3000);
   
  fillDelay(0x008f, del);
  bmpDraw("03.bmp", 0, 0);
  delay(3000);
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
}


 
 
