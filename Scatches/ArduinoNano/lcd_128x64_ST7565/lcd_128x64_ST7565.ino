
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


U8G2_ST7565_ERC12864_ALT_F_4W_SW_SPI u8g2(U8G2_R0, /* clock(SCL)=*/ 8, /* data(SI)=*/ 9, /* cs(CS)=*/ 5, /* dc(RS)=*/ 7, /* reset(RSE)=*/ 6); // contrast improved version for ERC12864
// для русских символов создаём класс u8g
U8G2_ST7565_ERC12864_ALT_F_4W_SW_SPI u8g(U8G2_R0, /* clock(SCL)=*/ 8, /* data(SI)=*/ 9, /* cs(CS)=*/ 5, /* dc(RS)=*/ 7, /* reset(RSE)=*/ 6); // contrast improved version for ERC12864


#include "lib/russian.h"
#include "test.h"


void russian_text(void) {
  
    u8g2.clearBuffer();
    
    u8g2_prepare();
    
    // вывод русских букв на экран
    send("абвг", 0, 0);
    send("абвгдеё", 0, 10);
    send("абвгдеёжзи", 0, 20); 

    send("А", 0, 30);

    
    u8g.drawLine(0, 0, 127, 0);
    u8g.drawLine(0, 63, 127, 63);

    u8g.drawTriangle(127,3, 127,60, 110,45);

    // x, y, radius
    u8g.drawDisc(100,18,8);

    // x, y, length, width
    u8g.drawBox(92,30,16,24);
    

//     u8g.drawStr( 0, 0, "a");
//     u8g.drawStr( 0, 10, "A");
//     u8g.drawStr( 0, 20, "?");

    
    u8g2.sendBuffer();
  
}


void setup(void) {
  u8g2.begin();
  
  russian_text();
}

void loop(void) {
  
//  test_screen();

}
