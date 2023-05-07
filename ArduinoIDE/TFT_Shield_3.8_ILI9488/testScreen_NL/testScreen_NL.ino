
// Mega

#include "tft_defines.h"
#include "ili9488.h"

// список функций
void testScreen(void);


//
void setup(void) 
{
#ifdef __SAMD21G18A__
  SerialUSB.begin(9600);
  while(!SerialUSB) ;
  SerialUSB.println("Hello!");
#else
  Serial.begin(9600);
  while(!Serial) ;
  Serial.println("Hello!");
#endif
  begin();
  testScreen();
  // fillScreen(0xf800);
}

//
void loop(void) 
{
#ifdef __SAMD21G18A__
  SerialUSB.println("Loop!");
#else
  Serial.println("Loop!");
#endif
  fillScreen(0x0ff0);
  delay(3000);
  fillScreen(0xf00f);
  delay(3000);
}

//
void testScreen(void) 
{
  uint16_t x, y;
  uint16_t del = 1000;
  fillScreen(0xf800);
  delay(del);
  drawCross();
  delay(del);
  fillScreen(0x008f);
  delay(del);
  drawCross();
  delay(del);
  fillScreen(0x0ff0);
}
