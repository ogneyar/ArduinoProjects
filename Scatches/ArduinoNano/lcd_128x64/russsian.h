
//#include <cstring>

void sendOne(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y, char* str);
void send(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y, char* str);
void a(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y);
void b(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y);
void v(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y);
void g(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y);
void d(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y);


void sendOne(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y, char* str) {
//  char *ach;
//  ach = strchr(str, 'а');
//if (ach != NULL) { // && ach-str == 0) { // если первый символ 'а'

  if (strcmp(str, "а") == 0) {
    a(u8g, x, y);
  }else if (strcmp(str, "б") == 0) {
    b(u8g, x, y);
  }else if (strcmp(str, "в") == 0) {
    v(u8g, x, y);
  }else if (strcmp(str, "г") == 0) {
    g(u8g, x, y);
  }else if (strcmp(str, "д") == 0) {
    d(u8g, x, y);
  }else {
    u8g.drawPixel(2,0);
    u8g.drawPixel(2,1);
    u8g.drawPixel(2,2);
    u8g.drawPixel(2,3);
    u8g.drawPixel(2,4);
  }
}

void send(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y, char* str) {
  char s = str[0];
	sendOne(u8g, x, y, s);
}


void a(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y) {
  
    //  .000.
    //  ....0
    //  .0000
    //  0...0
    //  .0000  
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(0+x,0+y);
    u8g.drawPixel(1+x,0+y);
    u8g.drawPixel(2+x,0+y);
    u8g.drawPixel(3+x,0+y);
//    u8g.drawPixel(4+x,0+y);

    // вторая строка
//    u8g.drawPixel(0+x,1+y);
//    u8g.drawPixel(1+x,1+y);
//    u8g.drawPixel(2+x,1+y);
//    u8g.drawPixel(3+x,1+y);
    u8g.drawPixel(4+x,1+y);

    // третья строка
//    u8g.drawPixel(0+x,2+y);
    u8g.drawPixel(1+x,2+y);
    u8g.drawPixel(2+x,2+y);
    u8g.drawPixel(3+x,2+y);
    u8g.drawPixel(4+x,2+y);

    // четвёртая строка
    u8g.drawPixel(0+x,3+y);
//    u8g.drawPixel(1+x,3+y);
//    u8g.drawPixel(2+x,3+y);
//    u8g.drawPixel(3+x,3+y);
    u8g.drawPixel(4+x,3+y);
    
    // пятая строка
//    u8g.drawPixel(0+x,4+y);
    u8g.drawPixel(1+x,4+y);
    u8g.drawPixel(2+x,4+y);
    u8g.drawPixel(3+x,4+y);
    u8g.drawPixel(4+x,4+y);
    
}


void b(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y) {
  
    //  .0000
    //  0....
    //  0000.
    //  0...0
    //  .0000  
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(0+x,0+y);
    u8g.drawPixel(1+x,0+y);
    u8g.drawPixel(2+x,0+y);
    u8g.drawPixel(3+x,0+y);
    u8g.drawPixel(4+x,0+y);

    // вторая строка
    u8g.drawPixel(0+x,1+y);
//    u8g.drawPixel(1+x,1+y);
//    u8g.drawPixel(2+x,1+y);
//    u8g.drawPixel(3+x,1+y);
//    u8g.drawPixel(4+x,1+y);

    // третья строка
    u8g.drawPixel(0+x,2+y);
    u8g.drawPixel(1+x,2+y);
    u8g.drawPixel(2+x,2+y);
    u8g.drawPixel(3+x,2+y);
//    u8g.drawPixel(4+x,2+y);

    // четвёртая строка
    u8g.drawPixel(0+x,3+y);
//    u8g.drawPixel(1+x,3+y);
//    u8g.drawPixel(2+x,3+y);
//    u8g.drawPixel(3+x,3+y);
    u8g.drawPixel(4+x,3+y);

    // пятая строка
//    u8g.drawPixel(0+x,4+y);
    u8g.drawPixel(1+x,4+y);
    u8g.drawPixel(2+x,4+y);
    u8g.drawPixel(3+x,4+y);
    u8g.drawPixel(4+x,4+y);
    
}


void v(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y) {
  
    //  000..
    //  0..0.
    //  0000.
    //  0...0
    //  0000.  
  
    // вывод построчно
    
    // первая строка
    u8g.drawPixel(0+x,0+y);
    u8g.drawPixel(1+x,0+y);
    u8g.drawPixel(2+x,0+y);
//    u8g.drawPixel(3+x,0+y);
//    u8g.drawPixel(4+x,0+y);

    // вторая строка
    u8g.drawPixel(0+x,1+y);
//    u8g.drawPixel(1+x,1+y);
//    u8g.drawPixel(2+x,1+y);
    u8g.drawPixel(3+x,1+y);
//    u8g.drawPixel(4+x,1+y);

    // третья строка
    u8g.drawPixel(0+x,2+y);
    u8g.drawPixel(1+x,2+y);
    u8g.drawPixel(2+x,2+y);
    u8g.drawPixel(3+x,2+y);
//    u8g.drawPixel(4+x,2+y);

    // четвёртая строка
    u8g.drawPixel(0+x,3+y);
//    u8g.drawPixel(1+x,3+y);
//    u8g.drawPixel(2+x,3+y);
//    u8g.drawPixel(3+x,3+y);
    u8g.drawPixel(4+x,3+y);

    // пятая строка
    u8g.drawPixel(0+x,4+y);
    u8g.drawPixel(1+x,4+y);
    u8g.drawPixel(2+x,4+y);
    u8g.drawPixel(3+x,4+y);
//    u8g.drawPixel(4+x,4+y);
    
}


void g(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y) {
  
    //  00000
    //  0...0
    //  0....
    //  0....
    //  0....  
  
    // вывод построчно
    
    // первая строка
    u8g.drawPixel(0+x,0+y);
    u8g.drawPixel(1+x,0+y);
    u8g.drawPixel(2+x,0+y);
    u8g.drawPixel(3+x,0+y);
    u8g.drawPixel(4+x,0+y);

    // вторая строка
    u8g.drawPixel(0+x,1+y);
//    u8g.drawPixel(1+x,1+y);
//    u8g.drawPixel(2+x,1+y);
//    u8g.drawPixel(3+x,1+y);
    u8g.drawPixel(4+x,1+y);

    // третья строка
    u8g.drawPixel(0+x,2+y);
//    u8g.drawPixel(1+x,2+y);
//    u8g.drawPixel(2+x,2+y);
//    u8g.drawPixel(3+x,2+y);
//    u8g.drawPixel(4+x,2+y);

    // четвёртая строка
    u8g.drawPixel(0+x,3+y);
//    u8g.drawPixel(1+x,3+y);
//    u8g.drawPixel(2+x,3+y);
//    u8g.drawPixel(3+x,3+y);
//    u8g.drawPixel(4+x,3+y);

    // пятая строка
    u8g.drawPixel(0+x,4+y);    
//    u8g.drawPixel(1+x,4+y);
//    u8g.drawPixel(2+x,4+y);
//    u8g.drawPixel(3+x,4+y);
//    u8g.drawPixel(4+x,4+y);
    
}


void d(U8GLIB_SSD1306_128X64 u8g, uint8_t x, uint8_t y) {
  
    //  ..0..
    //  .000.
    //  .0.0.
    //  .0.0.
    //  00000
    //  0...0  
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(0+x,0+y);
//    u8g.drawPixel(1+x,0+y);
    u8g.drawPixel(2+x,0+y);
//    u8g.drawPixel(3+x,0+y);
//    u8g.drawPixel(4+x,0+y);

    // вторая строка
//    u8g.drawPixel(0+x,1+y);
    u8g.drawPixel(1+x,1+y);
    u8g.drawPixel(2+x,1+y);
    u8g.drawPixel(3+x,1+y);
//    u8g.drawPixel(4+x,1+y);

    // третья строка
//    u8g.drawPixel(0+x,2+y);
    u8g.drawPixel(1+x,2+y);
//    u8g.drawPixel(2+x,2+y);
    u8g.drawPixel(3+x,2+y);
//    u8g.drawPixel(4+x,2+y);

    // четвёртая строка
//    u8g.drawPixel(0+x,3+y);
    u8g.drawPixel(1+x,3+y);
//    u8g.drawPixel(2+x,3+y);
    u8g.drawPixel(3+x,3+y);
//    u8g.drawPixel(4+x,3+y);

    // пятая строка
    u8g.drawPixel(0+x,4+y);
    u8g.drawPixel(1+x,4+y);
    u8g.drawPixel(2+x,4+y);
    u8g.drawPixel(3+x,4+y);
    u8g.drawPixel(4+x,4+y);
    
    // шестая строка
    u8g.drawPixel(0+x,5+y);
//    u8g.drawPixel(1+x,5+y);
//    u8g.drawPixel(2+x,5+y);
//    u8g.drawPixel(3+x,5+y);
    u8g.drawPixel(4+x,5+y);
    
}
