// Arduino Nano


#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 

#include "lib/russsian.h"
#include "test.h"


void russsian_text(void) {
  
  u8g.firstPage();
  do {
    u8g_prepare();
    
    // вывод русских букв на экран
    send("абв", 10, 0);
    send("абвгде", 10, 10);
    send("абвгдеёжз", 10, 20);

    send("А", 10, 30);

    u8g.drawStr( 0, 0, "a");
    u8g.drawStr( 0, 10, "A");
    u8g.drawStr( 0, 20, "?");
    
  } while( u8g.nextPage() );
  
}

void setup(void) {
  
  // flip screen, if required
  // u8g.setRot180();
  
  russsian_text();
}

void loop(void) {
  
//  test_screen();
  
}
