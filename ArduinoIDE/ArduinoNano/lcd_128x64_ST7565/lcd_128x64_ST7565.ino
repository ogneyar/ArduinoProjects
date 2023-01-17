
// Nano, Lgt8F328

#define BACKLIGHT_LED 3

#include <Arduino.h>
#include <U8g2lib.h>

uint32_t timeMillis = 0;
uint32_t current = 0;
uint16_t target = 1000;
uint8_t dots = 1;

// U8G2_ST7565_ERC12864_ALT_F_4W_SW_SPI u8g2(U8G2_R0, /* clock(SCL)=*/ 13, /* data(SI)=*/ 11, /* cs(CS)=*/ 10, /* dc(RS)=*/ 9, /* reset(RSE)=*/ 8);
U8G2_ST7565_ERC12864_ALT_F_4W_HW_SPI u8g2(U8G2_R0, /* cs(CS)=*/ 10, /* dc(RS)=*/ 9, /* reset(RSE)=*/ 8);


#include "test.h"


void clock(uint8_t _dots) {
  
    u8g2.clearBuffer();
    
    
    u8g2.setFont(u8g2_font_unifont_t_cyrillic);
    u8g2.setCursor(4, 12);
    u8g2.print("Часы Sвенирады!");  

    u8g2.setFont(u8g2_font_7Segments_26x42_mn);
    u8g2.setCursor(2, 63);
    u8g2.print(8888);  
    
    u8g2.setFont(u8g2_font_crox5tb_tn);
    u8g2.setCursor(59, 50);  
    if (_dots) u8g2.print(".");
    else u8g2.print(" ");  
    u8g2.setCursor(59, 38);
    if (_dots) u8g2.print(".");
    else u8g2.print(" ");    
       
    /*
    u8g2.drawLine(0, 0, 127, 0);
    u8g2.drawLine(0, 63, 127, 63);

    u8g2.drawTriangle(127,3, 127,60, 110,45);

    // x, y, radius
    u8g2.drawDisc(100,18,8);

    // x, y, length, width
    u8g2.drawBox(92,30,16,24);
    */
    
    u8g2.sendBuffer();
  
}


void setup(void) {
  pinMode(BACKLIGHT_LED, OUTPUT);
  digitalWrite(BACKLIGHT_LED, HIGH);
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setContrast(80);
}

void loop(void) {
  timeMillis = millis();
  if (timeMillis - current > target) {    
    current = timeMillis;    
    dots = !dots;
    clock(dots);
  }
//  test_screen();
}
