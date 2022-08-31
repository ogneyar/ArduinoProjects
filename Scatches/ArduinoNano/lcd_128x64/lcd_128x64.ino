// Arduino Nano


#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 

#include "lib/russian.h"
#include "test.h"


void russian_text(void) {
  
  u8g.firstPage();
  do {
    u8g_prepare();
    
    // вывод русских букв на экран
    send("абвг", 0, 0);
    send("абвгдеё", 0, 10);
    send("абвгдеёжзи", 0, 20); 

    send("А", 0, 30);

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
