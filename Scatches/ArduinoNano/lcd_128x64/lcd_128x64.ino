// Arduino Nano


#include <U8glib.h>
#include "russsian.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 

#include "test.h"


void russsian_text(void) {
  
  u8g.firstPage();
  do {
    u8g_prepare();

    sendOne(u8g, 0, 0, "а");
    sendOne(u8g, 6, 0, "б");
    sendOne(u8g, 12, 0, "в");
    sendOne(u8g, 18, 0, "г");
    sendOne(u8g, 24, 0, "д");
    
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
