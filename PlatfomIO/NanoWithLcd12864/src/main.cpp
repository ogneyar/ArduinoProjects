#include <Arduino.h>
#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);
#include <RussianText_u8g.h>


// вывод рамки на экран
void border(void) {
    u8g.drawLine(0, 0, 0, 63); // линия рамки слева 
    u8g.drawLine(0, 0, 127, 0); // линия рамки сверху
    u8g.drawLine(127, 0, 127, 63); // линия рамки справа
    u8g.drawLine(0, 63, 127, 63); // линия рамки снизу
}

// вывод русских букв на экран
void russian_text(void) {
  send("Йёмайё", 5, 10); 
  send("абвгдеёжзийклм", 5, 20);
  send("АБВГДЕЁЖЗИЙКЛМ", 5, 30);
}


void setup(void) {
    u8g.firstPage();
    do {
        u8g_prepare();
        
        russian_text();
        border();
    
    } while( u8g.nextPage() );
}

void loop(void) {
}
