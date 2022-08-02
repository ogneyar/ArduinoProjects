
//#include <cstring>

void send(char* str, uint8_t x, uint8_t y);
void a(uint8_t x, uint8_t y);
void b(uint8_t x, uint8_t y);
void v(uint8_t x, uint8_t y);
void g(uint8_t x, uint8_t y);
void d(uint8_t x, uint8_t y);


void send(char * str, uint8_t x, uint8_t y) {

    uint8_t i = 0;
    while (str[i]) {
        if ( ( (str[i] & 0x00ff) == ('а'>>8 & 0x00ff) ) && ( (str[i+1] & 0x00ff) == ('а' & 0x00ff) ) ) {
            a(x, y);
        }else 
        if ( ( (str[i] & 0x00ff) == ('б'>>8 & 0x00ff) ) && ( (str[i+1] & 0x00ff) == ('б' & 0x00ff) ) ) {
            b(x, y);
        }else 
        if ( ( (str[i] & 0x00ff) == ('в'>>8 & 0x00ff) ) && ( (str[i+1] & 0x00ff) == ('в' & 0x00ff) ) ) {
            v(x, y);
        }else 
        if ( ( (str[i] & 0x00ff) == ('г'>>8 & 0x00ff) ) && ( (str[i+1] & 0x00ff) == ('г' & 0x00ff) ) ) {
            g(x, y);
        }else 
        if ( ( (str[i] & 0x00ff) == ('д'>>8 & 0x00ff) ) && ( (str[i+1] & 0x00ff) == ('д' & 0x00ff) ) ) {
            d(x, y);
        }
   
        i = i + 2;
        x = x + 6;
    }
}


void a(uint8_t x, uint8_t y) {
  
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


void b(uint8_t x, uint8_t y) {
  
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


void v(uint8_t x, uint8_t y) {
  
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


void g(uint8_t x, uint8_t y) {
  
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


void d(uint8_t x, uint8_t y) {
  
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
