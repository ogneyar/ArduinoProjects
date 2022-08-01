// Arduino Nano


#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 

#include "russsian.h"
#include "test.h"


void russsian_text(void) {
  
  u8g.firstPage();
  do {
    u8g_prepare();

    sendOne(0, 0, "а");
    sendOne(6, 0, "б");
    sendOne(12, 0, "в");
    sendOne(18, 0, "г");
    sendOne(24, 0, "д");

    send("абвгд", 0, 7);
    
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
