
//#include <cstring>

void send(char* str, uint8_t x, uint8_t y);
void a(uint8_t x, uint8_t y);
void b(uint8_t x, uint8_t y);
void v(uint8_t x, uint8_t y);
void g(uint8_t x, uint8_t y);
void d(uint8_t x, uint8_t y);


void send(char * str, uint8_t x, uint8_t y) {

    uint8_t i = 0;
    while (i < strlen(str)) {
        switch(str[i]<<8 | str[i+1]) {
            case 'а': 
                a(x, y);
            break;
            case 'б': 
                b(x, y);
            break;
            case 'в': 
                v(x, y);
            break;
            case 'г': 
                g(x, y);
            break;
            case 'д': 
                d(x, y);
            break;
        }
        i = i + 2;
    };

//   if (strcmp(str, "а") == 0) {
//     a(x, y);
//   }else if (strcmp(str, "б") == 0) {
//     b(x, y);
//   }else if (strcmp(str, "в") == 0) {
//     v(x, y);
//   }else if (strcmp(str, "г") == 0) {
//     g(x, y);
//   }else if (strcmp(str, "д") == 0) {
//     d(x, y);
//   }
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
