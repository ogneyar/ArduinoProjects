
//#include <cstring>

void send(char* str, uint8_t x, uint8_t y);
void a(uint8_t x, uint8_t y);
void b(uint8_t x, uint8_t y);
void v(uint8_t x, uint8_t y);
void g(uint8_t x, uint8_t y);
void d(uint8_t x, uint8_t y);
void e(uint8_t x, uint8_t y);
void io(uint8_t x, uint8_t y);
void j(uint8_t x, uint8_t y);
void z(uint8_t x, uint8_t y);


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
        }else 
        if ( ( (str[i] & 0x00ff) == ('е'>>8 & 0x00ff) ) && ( (str[i+1] & 0x00ff) == ('е' & 0x00ff) ) ) {
            e(x, y);
        }else 
        if ( ( (str[i] & 0x00ff) == ('ё'>>8 & 0x00ff) ) && ( (str[i+1] & 0x00ff) == ('ё' & 0x00ff) ) ) {
            io(x, y);
        }else 
        if ( ( (str[i] & 0x00ff) == ('ж'>>8 & 0x00ff) ) && ( (str[i+1] & 0x00ff) == ('ж' & 0x00ff) ) ) {
            j(x, y);
        }else 
        if ( ( (str[i] & 0x00ff) == ('з'>>8 & 0x00ff) ) && ( (str[i+1] & 0x00ff) == ('з' & 0x00ff) ) ) {
            z(x, y);
        }
   
        i = i + 2;
        x = x + 8;
    }
}


void a(uint8_t x, uint8_t y) {
    //  а
    
    //  .....  1
    //  .000.  2
    //  ....0  3
    //  .0000  4
    //  0...0  5
    //  .0000  6
    //  .....  7
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(x+0,y);
//    u8g.drawPixel(x+1,y);
//    u8g.drawPixel(x+2,y);
//    u8g.drawPixel(x+3,y);
//    u8g.drawPixel(x+4,y);

    // вторая строка
//    u8g.drawPixel(x+0,y+1);
    u8g.drawPixel(x+1,y+1);
    u8g.drawPixel(x+2,y+1);
    u8g.drawPixel(x+3,y+1);
//    u8g.drawPixel(x+4,y+1);

    // третья строка
//    u8g.drawPixel(x+0,y+2);
//    u8g.drawPixel(x+1,y+2);
//    u8g.drawPixel(x+2,y+2);
//    u8g.drawPixel(x+3,y+2);
    u8g.drawPixel(x+4,y+2);

    // четвёртая строка
//    u8g.drawPixel(x+0,y+3);
    u8g.drawPixel(x+1,y+3);
    u8g.drawPixel(x+2,y+3);
    u8g.drawPixel(x+3,y+3);
    u8g.drawPixel(x+4,y+3);

    // пятая строка
    u8g.drawPixel(x+0,y+4);
//    u8g.drawPixel(x+1,y+4);
//    u8g.drawPixel(x+2,y+4);
//    u8g.drawPixel(x+3,y+4);
    u8g.drawPixel(x+4,y+4);
    
    // шестая строка
//    u8g.drawPixel(x+0,y+5);
    u8g.drawPixel(x+1,y+5);
    u8g.drawPixel(x+2,y+5);
    u8g.drawPixel(x+3,y+5);
    u8g.drawPixel(x+4,y+5);
    
    // седьмая строка
//    u8g.drawPixel(x+0,y+6);
//    u8g.drawPixel(x+1,y+6);
//    u8g.drawPixel(x+2,y+6);
//    u8g.drawPixel(x+3,y+6);
//    u8g.drawPixel(x+4,y+6);
    
}


void b(uint8_t x, uint8_t y) {
    //  б
    
    //  ....0  1
    //  .0000  2
    //  0....  3
    //  0000.  4
    //  0...0  5
    //  .000.  6
    //  .....  7
  
    // вывод построчно    
    
    // первая строка
//    u8g.drawPixel(x+0,y);
//    u8g.drawPixel(x+1,y);
//    u8g.drawPixel(x+2,y);
//    u8g.drawPixel(x+3,y);
    u8g.drawPixel(x+4,y);

    // вторая строка
//    u8g.drawPixel(x+0,y+1);
    u8g.drawPixel(x+1,y+1);
    u8g.drawPixel(x+2,y+1);
    u8g.drawPixel(x+3,y+1);
    u8g.drawPixel(x+4,y+1);

    // третья строка
    u8g.drawPixel(x+0,y+2);
//    u8g.drawPixel(x+1,y+2);
//    u8g.drawPixel(x+2,y+2);
//    u8g.drawPixel(x+3,y+2);
//    u8g.drawPixel(x+4,y+2);

    // четвёртая строка
    u8g.drawPixel(x+0,y+3);
    u8g.drawPixel(x+1,y+3);
    u8g.drawPixel(x+2,y+3);
    u8g.drawPixel(x+3,y+3);
//    u8g.drawPixel(x+4,y+3);

    // пятая строка
    u8g.drawPixel(x+0,y+4);
//    u8g.drawPixel(x+1,y+4);
//    u8g.drawPixel(x+2,y+4);
//    u8g.drawPixel(x+3,y+4);
    u8g.drawPixel(x+4,y+4);
    
    // шестая строка
//    u8g.drawPixel(x+0,y+5);
    u8g.drawPixel(x+1,y+5);
    u8g.drawPixel(x+2,y+5);
    u8g.drawPixel(x+3,y+5);
//    u8g.drawPixel(x+4,y+5);
    
    // седьмая строка
//    u8g.drawPixel(x+0,y+6);
//    u8g.drawPixel(x+1,y+6);
//    u8g.drawPixel(x+2,y+6);
//    u8g.drawPixel(x+3,y+6);
//    u8g.drawPixel(x+4,y+6);
    
}


void v(uint8_t x, uint8_t y) {
    //  в

    //  .....  1
    //  000..  2
    //  0..0.  3
    //  0000.  4
    //  0...0  5
    //  0000.  6
    //  .....  7
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(x+0,y);
//    u8g.drawPixel(x+1,y);
//    u8g.drawPixel(x+2,y);
//    u8g.drawPixel(x+3,y);
//    u8g.drawPixel(x+4,y);

    // вторая строка
    u8g.drawPixel(x+0,y+1);
    u8g.drawPixel(x+1,y+1);
    u8g.drawPixel(x+2,y+1);
//    u8g.drawPixel(x+3,y+1);
//    u8g.drawPixel(x+4,y+1);

    // третья строка
    u8g.drawPixel(x+0,y+2);
//    u8g.drawPixel(x+1,y+2);
//    u8g.drawPixel(x+2,y+2);
    u8g.drawPixel(x+3,y+2);
//    u8g.drawPixel(x+4,y+2);

    // четвёртая строка
    u8g.drawPixel(x+0,y+3);
    u8g.drawPixel(x+1,y+3);
    u8g.drawPixel(x+2,y+3);
    u8g.drawPixel(x+3,y+3);
//    u8g.drawPixel(x+4,y+3);

    // пятая строка
    u8g.drawPixel(x+0,y+4);
//    u8g.drawPixel(x+1,y+4);
//    u8g.drawPixel(x+2,y+4);
//    u8g.drawPixel(x+3,y+4);
    u8g.drawPixel(x+4,y+4);
    
    // шестая строка
    u8g.drawPixel(x+0,y+5);
    u8g.drawPixel(x+1,y+5);
    u8g.drawPixel(x+2,y+5);
    u8g.drawPixel(x+3,y+5);
//    u8g.drawPixel(x+4,y+5);
    
    // седьмая строка
//    u8g.drawPixel(x+0,y+6);
//    u8g.drawPixel(x+1,y+6);
//    u8g.drawPixel(x+2,y+6);
//    u8g.drawPixel(x+3,y+6);
//    u8g.drawPixel(x+4,y+6);
    
}


void g(uint8_t x, uint8_t y) {
    //  г

    //  .....  1
    //  00000  2
    //  0...0  3
    //  0....  4
    //  0....  5
    //  0....  6
    //  .....  7
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(x+0,y);
//    u8g.drawPixel(x+1,y);
//    u8g.drawPixel(x+2,y);
//    u8g.drawPixel(x+3,y);
//    u8g.drawPixel(x+4,y);

    // вторая строка
    u8g.drawPixel(x+0,y+1);
    u8g.drawPixel(x+1,y+1);
    u8g.drawPixel(x+2,y+1);
    u8g.drawPixel(x+3,y+1);
    u8g.drawPixel(x+4,y+1);

    // третья строка
    u8g.drawPixel(x+0,y+2);
//    u8g.drawPixel(x+1,y+2);
//    u8g.drawPixel(x+2,y+2);
//    u8g.drawPixel(x+3,y+2);
    u8g.drawPixel(x+4,y+2);

    // четвёртая строка
    u8g.drawPixel(x+0,y+3);
//    u8g.drawPixel(x+1,y+3);
//    u8g.drawPixel(x+2,y+3);
//    u8g.drawPixel(x+3,y+3);
//    u8g.drawPixel(x+4,y+3);

    // пятая строка
    u8g.drawPixel(x+0,y+4);
//    u8g.drawPixel(x+1,y+4);
//    u8g.drawPixel(x+2,y+4);
//    u8g.drawPixel(x+3,y+4);
//    u8g.drawPixel(x+4,y+4);
    
    // шестая строка
    u8g.drawPixel(x+0,y+5);
//    u8g.drawPixel(x+1,y+5);
//    u8g.drawPixel(x+2,y+5);
//    u8g.drawPixel(x+3,y+5);
//    u8g.drawPixel(x+4,y+5);
    
    // седьмая строка
//    u8g.drawPixel(x+0,y+6);
//    u8g.drawPixel(x+1,y+6);
//    u8g.drawPixel(x+2,y+6);
//    u8g.drawPixel(x+3,y+6);
//    u8g.drawPixel(x+4,y+6);
    
}


void d(uint8_t x, uint8_t y) {
    //  д

    //  .....  1
    //  ..0..  2
    //  .000.  3
    //  .0.0.  4
    //  .0.0.  5
    //  00000  6
    //  0...0  7
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(x+0,y);
//    u8g.drawPixel(x+1,y);
//    u8g.drawPixel(x+2,y);
//    u8g.drawPixel(x+3,y);
//    u8g.drawPixel(x+4,y);

    // вторая строка
//    u8g.drawPixel(x+0,y+1);
//    u8g.drawPixel(x+1,y+1);
    u8g.drawPixel(x+2,y+1);
//    u8g.drawPixel(x+3,y+1);
//    u8g.drawPixel(x+4,y+1);

    // третья строка
//    u8g.drawPixel(x+0,y+2);
    u8g.drawPixel(x+1,y+2);
    u8g.drawPixel(x+2,y+2);
    u8g.drawPixel(x+3,y+2);
//    u8g.drawPixel(x+4,y+2);

    // четвёртая строка
//    u8g.drawPixel(x+0,y+3);
    u8g.drawPixel(x+1,y+3);
//    u8g.drawPixel(x+2,y+3);
    u8g.drawPixel(x+3,y+3);
//    u8g.drawPixel(x+4,y+3);

    // пятая строка
//    u8g.drawPixel(x+0,y+4);
    u8g.drawPixel(x+1,y+4);
//    u8g.drawPixel(x+2,y+4);
    u8g.drawPixel(x+3,y+4);
//    u8g.drawPixel(x+4,y+4);
    
    // шестая строка
    u8g.drawPixel(x+0,y+5);
    u8g.drawPixel(x+1,y+5);
    u8g.drawPixel(x+2,y+5);
    u8g.drawPixel(x+3,y+5);
    u8g.drawPixel(x+4,y+5);
    
    // седьмая строка
    u8g.drawPixel(x+0,y+6);
//    u8g.drawPixel(x+1,y+6);
//    u8g.drawPixel(x+2,y+6);
//    u8g.drawPixel(x+3,y+6);
    u8g.drawPixel(x+4,y+6);
    
}


void e(uint8_t x, uint8_t y) {
    // е

    //  .....  1
    //  .000.  2
    //  0...0  3
    //  00000  4
    //  0....  5
    //  .0000  6
    //  .....  7
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(x+0,y);
//    u8g.drawPixel(x+1,y);
//    u8g.drawPixel(x+2,y);
//    u8g.drawPixel(x+3,y);
//    u8g.drawPixel(x+4,y);

    // вторая строка
//    u8g.drawPixel(x+0,y+1);
    u8g.drawPixel(x+1,y+1);
    u8g.drawPixel(x+2,y+1);
    u8g.drawPixel(x+3,y+1);
//    u8g.drawPixel(x+4,y+1);

    // третья строка
    u8g.drawPixel(x+0,y+2);
//    u8g.drawPixel(x+1,y+2);
//    u8g.drawPixel(x+2,y+2);
//    u8g.drawPixel(x+3,y+2);
    u8g.drawPixel(x+4,y+2);

    // четвёртая строка
    u8g.drawPixel(x+0,y+3);
    u8g.drawPixel(x+1,y+3);
    u8g.drawPixel(x+2,y+3);
    u8g.drawPixel(x+3,y+3);
    u8g.drawPixel(x+4,y+3);

    // пятая строка
    u8g.drawPixel(x+0,y+4);
//    u8g.drawPixel(x+1,y+4);
//    u8g.drawPixel(x+2,y+4);
//    u8g.drawPixel(x+3,y+4);
//    u8g.drawPixel(x+4,y+4);
    
    // шестая строка
//    u8g.drawPixel(x+0,y+5);
    u8g.drawPixel(x+1,y+5);
    u8g.drawPixel(x+2,y+5);
    u8g.drawPixel(x+3,y+5);
    u8g.drawPixel(x+4,y+5);
    
    // седьмая строка
//    u8g.drawPixel(x+0,y+6);
//    u8g.drawPixel(x+1,y+6);
//    u8g.drawPixel(x+2,y+6);
//    u8g.drawPixel(x+3,y+6);
//    u8g.drawPixel(x+4,y+6);
    
}


void io(uint8_t x, uint8_t y) {
    // ё

    //  .0.0.  1
    //  .000.  2
    //  0...0  3
    //  00000  4
    //  0....  5
    //  .0000  6
    //  .....  7
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(x+0,y);
    u8g.drawPixel(x+1,y);
//    u8g.drawPixel(x+2,y);
    u8g.drawPixel(x+3,y);
//    u8g.drawPixel(x+4,y);

    // вторая строка
//    u8g.drawPixel(x+0,y+1);
    u8g.drawPixel(x+1,y+1);
    u8g.drawPixel(x+2,y+1);
    u8g.drawPixel(x+3,y+1);
//    u8g.drawPixel(x+4,y+1);

    // третья строка
    u8g.drawPixel(x+0,y+2);
//    u8g.drawPixel(x+1,y+2);
//    u8g.drawPixel(x+2,y+2);
//    u8g.drawPixel(x+3,y+2);
    u8g.drawPixel(x+4,y+2);

    // четвёртая строка
    u8g.drawPixel(x+0,y+3);
    u8g.drawPixel(x+1,y+3);
    u8g.drawPixel(x+2,y+3);
    u8g.drawPixel(x+3,y+3);
    u8g.drawPixel(x+4,y+3);

    // пятая строка
    u8g.drawPixel(x+0,y+4);
//    u8g.drawPixel(x+1,y+4);
//    u8g.drawPixel(x+2,y+4);
//    u8g.drawPixel(x+3,y+4);
//    u8g.drawPixel(x+4,y+4);
    
    // шестая строка
//    u8g.drawPixel(x+0,y+5);
    u8g.drawPixel(x+1,y+5);
    u8g.drawPixel(x+2,y+5);
    u8g.drawPixel(x+3,y+5);
    u8g.drawPixel(x+4,y+5);
    
    // седьмая строка
//    u8g.drawPixel(x+0,y+6);
//    u8g.drawPixel(x+1,y+6);
//    u8g.drawPixel(x+2,y+6);
//    u8g.drawPixel(x+3,y+6);
//    u8g.drawPixel(x+4,y+6);
    
}


void j(uint8_t x, uint8_t y) {
    // ж

    //  .....  1
    //  0.0.0  2
    //  0.0.0  3
    //  .000.  4
    //  0.0.0  5
    //  0.0.0  6
    //  .....  7
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(x+0,y);
//    u8g.drawPixel(x+1,y);
//    u8g.drawPixel(x+2,y);
//    u8g.drawPixel(x+3,y);
//    u8g.drawPixel(x+4,y);

    // вторая строка
    u8g.drawPixel(x+0,y+1);
//    u8g.drawPixel(x+1,y+1);
    u8g.drawPixel(x+2,y+1);
//    u8g.drawPixel(x+3,y+1);
    u8g.drawPixel(x+4,y+1);

    // третья строка
    u8g.drawPixel(x+0,y+2);
//    u8g.drawPixel(x+1,y+2);
    u8g.drawPixel(x+2,y+2);
//    u8g.drawPixel(x+3,y+2);
    u8g.drawPixel(x+4,y+2);

    // четвёртая строка
//    u8g.drawPixel(x+0,y+3);
    u8g.drawPixel(x+1,y+3);
    u8g.drawPixel(x+2,y+3);
    u8g.drawPixel(x+3,y+3);
//    u8g.drawPixel(x+4,y+3);

    // пятая строка
    u8g.drawPixel(x+0,y+4);
//    u8g.drawPixel(x+1,y+4);
    u8g.drawPixel(x+2,y+4);
//    u8g.drawPixel(x+3,y+4);
    u8g.drawPixel(x+4,y+4);
    
    // шестая строка
    u8g.drawPixel(x+0,y+5);
//    u8g.drawPixel(x+1,y+5);
    u8g.drawPixel(x+2,y+5);
//    u8g.drawPixel(x+3,y+5);
    u8g.drawPixel(x+4,y+5);
    
    // седьмая строка
//    u8g.drawPixel(x+0,y+6);
//    u8g.drawPixel(x+1,y+6);
//    u8g.drawPixel(x+2,y+6);
//    u8g.drawPixel(x+3,y+6);
//    u8g.drawPixel(x+4,y+6);
    
}



void z(uint8_t x, uint8_t y) {
    // з

    //  .....  1
    //  00000  2
    //  ....0  3
    //  .000.  4
    //  ....0  5
    //  00000  6
    //  .....  7
  
    // вывод построчно
    
    // первая строка
//    u8g.drawPixel(x+0,y);
//    u8g.drawPixel(x+1,y);
//    u8g.drawPixel(x+2,y);
//    u8g.drawPixel(x+3,y);
//    u8g.drawPixel(x+4,y);

    // вторая строка
    u8g.drawPixel(x+0,y+1);
    u8g.drawPixel(x+1,y+1);
    u8g.drawPixel(x+2,y+1);
    u8g.drawPixel(x+3,y+1);
    u8g.drawPixel(x+4,y+1);

    // третья строка
//    u8g.drawPixel(x+0,y+2);
//    u8g.drawPixel(x+1,y+2);
//    u8g.drawPixel(x+2,y+2);
//    u8g.drawPixel(x+3,y+2);
    u8g.drawPixel(x+4,y+2);

    // четвёртая строка
//    u8g.drawPixel(x+0,y+3);
    u8g.drawPixel(x+1,y+3);
    u8g.drawPixel(x+2,y+3);
    u8g.drawPixel(x+3,y+3);
//    u8g.drawPixel(x+4,y+3);

    // пятая строка
//    u8g.drawPixel(x+0,y+4);
//    u8g.drawPixel(x+1,y+4);
//    u8g.drawPixel(x+2,y+4);
//    u8g.drawPixel(x+3,y+4);
    u8g.drawPixel(x+4,y+4);
    
    // шестая строка
    u8g.drawPixel(x+0,y+5);
    u8g.drawPixel(x+1,y+5);
    u8g.drawPixel(x+2,y+5);
    u8g.drawPixel(x+3,y+5);
    u8g.drawPixel(x+4,y+5);
    
    // седьмая строка
//    u8g.drawPixel(x+0,y+6);
//    u8g.drawPixel(x+1,y+6);
//    u8g.drawPixel(x+2,y+6);
//    u8g.drawPixel(x+3,y+6);
//    u8g.drawPixel(x+4,y+6);
    
}
