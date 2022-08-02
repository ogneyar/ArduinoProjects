// Arduino Nano


#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 

#include "russsian.h"
#include "test.h"


void russsian_text(void) {
  
  u8g.firstPage();
  do {
    u8g_prepare();
    
    // вывод русских букв на экран
    send("абвгд", 0, 0);
    send("абвгд", 0, 7);
    send("абвгд", 0,14);
    
  } while( u8g.nextPage() );
  
}

void setup(void) {
  
  // flip screen, if required
  // u8g.setRot180();
  
}

void loop(void) {
  
//  test_screen();
  russsian_text();
  
}
