// Arduino Nano

#include <U8glib.h>
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);	// I2C / TWI 

#include "lib/russian.h"
#include "test.h"


void russian_text(void) {
  
  u8g.firstPage();
  do {
    u8g_prepare();
    
    // вывод русских букв на экран
    send("абвгдеёжзи", 0, 0); 

    send("А", 0, 20);

    u8g.drawLine(0, 31, 127, 31);
    u8g.drawLine(0, 0, 127, 0);

    u8g.drawTriangle(127,3, 127,28, 110,20);

    // x, y, radius
    u8g.drawDisc(100,18,8);

    // x, y, length, width
    u8g.drawBox(80,10,10,16);
    
//     u8g.drawStr( 0, 0, "a");
//     u8g.drawStr( 0, 10, "A");
//     u8g.drawStr( 0, 20, "?");
    
  } while( u8g.nextPage() );
  
}

void setup(void) {
  
  // flip screen, if required
  // u8g.setRot180();
  
  russian_text();
}

void loop(void) {
  
//  test_screen();
  
}
