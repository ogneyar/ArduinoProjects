// Пример

//  Ё

//  .0.0.  1
//  00000  2
//  0....  3
//  0....  4
//  0000.  5
//  0....  6
//  0....  7
//  00000  8
//  .....  9


void A(uint8_t x, uint8_t y);



void A(uint8_t x, uint8_t y) { 
    // А

	//  .....  1
	//  ..0..  2
	//  .0.0.  3
	//  0...0  4
	//  0...0  5
	//  00000  6
	//  0...0  7
	//  0...0  8
	//  .....  9

    // вывод построчно
    
    // первая строка
    // u8g.drawPixel(x+0,y);
    // u8g.drawPixel(x+1,y);
    // u8g.drawPixel(x+2,y);
    // u8g.drawPixel(x+3,y);
    // u8g.drawPixel(x+4,y);

    // вторая строка
    // u8g.drawPixel(x+0,y+1);
    // u8g.drawPixel(x+1,y+1);
    u8g.drawPixel(x+2,y+1);
    // u8g.drawPixel(x+3,y+1);
    // u8g.drawPixel(x+4,y+1);

    // третья строка
    // u8g.drawPixel(x+0,y+2);
    u8g.drawPixel(x+1,y+2);
    // u8g.drawPixel(x+2,y+2);
    u8g.drawPixel(x+3,y+2);
    // u8g.drawPixel(x+4,y+2);

    // четвёртая строка
    u8g.drawPixel(x+0,y+3);
    // u8g.drawPixel(x+1,y+3);
    // u8g.drawPixel(x+2,y+3);
    // u8g.drawPixel(x+3,y+3);
    u8g.drawPixel(x+4,y+3);

    // пятая строка
    u8g.drawPixel(x+0,y+4);
    // u8g.drawPixel(x+1,y+4);
    // u8g.drawPixel(x+2,y+4);
    // u8g.drawPixel(x+3,y+4);
    u8g.drawPixel(x+4,y+4);
    
    // шестая строка
    u8g.drawPixel(x+0,y+5);
    u8g.drawPixel(x+1,y+5);
    u8g.drawPixel(x+2,y+5);
    u8g.drawPixel(x+3,y+5);
    u8g.drawPixel(x+4,y+5);
    
    // седьмая строка
    u8g.drawPixel(x+0,y+6);
    // u8g.drawPixel(x+1,y+6);
    // u8g.drawPixel(x+2,y+6);
    // u8g.drawPixel(x+3,y+6);
    u8g.drawPixel(x+4,y+6);
    
    // восьмая строка
    u8g.drawPixel(x+0,y+7);
    // u8g.drawPixel(x+1,y+7);
    // u8g.drawPixel(x+2,y+7);
    // u8g.drawPixel(x+3,y+7);
    u8g.drawPixel(x+4,y+7);
   
    // девятая строка
    // u8g.drawPixel(x+0,y+8);
    // u8g.drawPixel(x+1,y+8);
    // u8g.drawPixel(x+2,y+8);
    // u8g.drawPixel(x+3,y+8);
    // u8g.drawPixel(x+4,y+8);

}
