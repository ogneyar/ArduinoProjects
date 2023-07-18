
#ifndef _ST7735_H_
#define _ST7735_H_

#include "st_defines.h"
#include "spi.h"
#include "font.h"

uint8_t rotation = 1;
uint8_t _width = ST7735_WIDTH;
uint8_t _height = ST7735_HEIGHT;
uint8_t cursor_x = 0, cursor_y = 0;
uint8_t textsize_x = 1, textsize_y = 1;
uint8_t wrap = 0;
uint16_t textcolor = WHITE, textbgcolor = BLACK, dotcolor = WHITE;


// 
void st7735_send(uint8_t dc, uint8_t data);
void st7735_drawPixel(uint8_t x, uint8_t y, uint16_t color);
void st7735_drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color);
void st7735_display(uint16_t color, uint16_t length = 13040);
void st7735_set_column_and_page(uint8_t x = 0, uint8_t y = 0, uint8_t size_x = _width, uint8_t size_y = _height);
void st7735_fill(uint16_t color, uint8_t x = 0, uint8_t y = 0, uint8_t size_x = _width, uint8_t size_y = _height);
void st7735_clear();
void st7735_init();
void st7735_test_screen(uint16_t del = 0);
void st7735_print(uint8_t ch, uint16_t color);
void st7735_print(uint8_t ch);
void st7735_print(const char * ch, uint16_t color);
void st7735_print(const char *ch);
void st7735_printNum(uint32_t number, uint16_t color);
void st7735_printNum(uint32_t number);
void st7735_drawChar(uint8_t x, uint8_t y, unsigned char ch, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y);
void st7735_setCursor(uint8_t x, uint8_t y);
void st7735_setFontSize(uint8_t size);
void st7735_setFontSize(uint8_t sizeX, uint8_t sizeY);
void st7735_setFontColor(uint16_t color);
void st7735_setFontBgColor(uint16_t color);
void st7735_setFontDotColor(uint16_t color);
void st7735_setRotation(uint8_t r = 1);



//
void st7735_send(uint8_t dc, uint8_t data)
{
  if (dc == LCD_D) PORT_SPI |= (1 << DD_DC); // gpio_set(GPIOB,DC);
  else PORT_SPI &= ~(1 << DD_DC); // gpio_reset(GPIOB,DC);
  SPI_Master_SendByte(data);
  // _delay_us(20);
}

//
void st7735_drawPixel(uint8_t x, uint8_t y, uint16_t color)
{
  PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
  
  // if (rotation == 1) y = _height - y;

  st7735_set_column_and_page(x, y, 1, 1);
    
  uint8_t c1=(uint8_t)((color & 0x00ff));
  uint8_t c2=color>>8;

  st7735_send(LCD_C, ST77XX_RAMWR); // 0x2C
  
  st7735_send(LCD_D, c1);
  st7735_send(LCD_D, c2);

  PORT_SPI |= (1 << DD_SS); // chip_select_disable();  
}

void st7735_drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color)
{
  // PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
    
  // st7735_set_column_and_page(x1, y1, x2, y2);
    
  // uint8_t c1=(uint8_t)((color & 0x00ff));
  // uint8_t c2=color>>8;

  // st7735_send(LCD_C, ST77XX_RAMWR); // 0x2C
  
  // st7735_send(LCD_D, c1);
  // st7735_send(LCD_D, c2);

  // PORT_SPI |= (1 << DD_SS); // chip_select_disable();
}

//
void st7735_display(uint16_t color, uint16_t length)
{
  uint8_t c1=(uint8_t)((color & 0x00ff));
  uint8_t c2=color>>8;

  st7735_send(LCD_C, ST77XX_RAMWR); // 0x2C
  
  for (uint16_t i=0; i < length; i++)
  {
     st7735_send(LCD_D, c1);
     st7735_send(LCD_D, c2);
  }
}

//
void st7735_set_column_and_page(uint8_t x, uint8_t y, uint8_t size_x, uint8_t size_y)
{
  if (rotation == 1) {
    uint8_t temp;
    temp = ST7735_WIDTH - (size_y + y);
    y = x;
    x = temp;
    temp = size_y;
    size_y = size_x;
    size_x = temp;
  }
  st7735_send(LCD_C, ST77XX_CASET); // 0x2A
  st7735_send(LCD_D, 0x00); // x1 high - начало
  st7735_send(LCD_D, ST7735_SHIFT + x); // x1 low   // + 26 shift
  st7735_send(LCD_D, 0x00); // x2 high - конец
  st7735_send(LCD_D, ST7735_SHIFT + x + size_x); // x2 low   // 80 horizontal + 26 shift

  st7735_send(LCD_C, ST77XX_RASET); // 0x2B
  st7735_send(LCD_D, 0x00); // y1 high - начало
  st7735_send(LCD_D, y); // y1 low
  st7735_send(LCD_D, 0x00); // y2 high - конец
  st7735_send(LCD_D, y + size_y); // y2 low  // 160 vertical
}

//
void st7735_fill(uint16_t color, uint8_t x, uint8_t y, uint8_t size_x, uint8_t size_y)
{
  PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
    
  st7735_set_column_and_page(x, y, size_x, size_y);
  
  st7735_display(color, ((size_x+1)*(size_y+1)));

  PORT_SPI |= (1 << DD_SS); // chip_select_disable();
}

//
void st7735_clear()
{
  // st7735_fill(_BLACK, 0, 0, _width, _height);
  st7735_fill(_BLACK);
}

//
void st7735_init()
{  
  st7735_setRotation();
  
  PORTD &= ~(1 << DD_RES);
  delay(10);
  
  PORTD |= (1 << DD_RES);
  delay(10);

  PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
  
  st7735_send(LCD_C, ST77XX_SWRESET); // 0x01 //  1: Software reset, 0 args, w/delay
  delay(150);
  st7735_send(LCD_C, ST77XX_SLPOUT); // 0x11 //  2: Out of sleep mode, 0 args, w/delay
  delay(255);

  st7735_send(LCD_C, ST77XX_INVON); // 0x21 // 13: Invert display, no args

  st7735_send(LCD_C, ST77XX_COLMOD); // 0x3A // 15: set color mode, 1 arg
  st7735_send(LCD_D, 0x05); // 16-bit/pixel 
      
  st7735_send(LCD_C, ST7735_GMCTRP1); // 0xE0 //  1: Gamma Adjustments (pos. polarity), 16 args
  st7735_send(LCD_D, 0x02);
  st7735_send(LCD_D, 0x1C);
  st7735_send(LCD_D, 0x07);
  st7735_send(LCD_D, 0x12);
  st7735_send(LCD_D, 0x37);
  st7735_send(LCD_D, 0x32);
  st7735_send(LCD_D, 0x29);
  st7735_send(LCD_D, 0x2D);
  st7735_send(LCD_D, 0x29);
  st7735_send(LCD_D, 0x25);
  st7735_send(LCD_D, 0x2B);
  st7735_send(LCD_D, 0x39);
  st7735_send(LCD_D, 0x00);
  st7735_send(LCD_D, 0x01);
  st7735_send(LCD_D, 0x03);
  st7735_send(LCD_D, 0x10);

  st7735_send(LCD_C, ST7735_GMCTRN1); // 0xE1 //  2: Gamma Adjustments (neg. polarity), 16 args
  st7735_send(LCD_D, 0x03);
  st7735_send(LCD_D, 0x1D);
  st7735_send(LCD_D, 0x07);
  st7735_send(LCD_D, 0x06);
  st7735_send(LCD_D, 0x2E);
  st7735_send(LCD_D, 0x2C);
  st7735_send(LCD_D, 0x29);
  st7735_send(LCD_D, 0x2D);
  st7735_send(LCD_D, 0x2E);
  st7735_send(LCD_D, 0x2E);
  st7735_send(LCD_D, 0x37);
  st7735_send(LCD_D, 0x3F);
  st7735_send(LCD_D, 0x00);
  st7735_send(LCD_D, 0x00);
  st7735_send(LCD_D, 0x02);
  st7735_send(LCD_D, 0x10);

  st7735_send(LCD_C, ST77XX_DISPON); // 0x29 //  4: Main screen turn on, no args w/delay
  delay(100);

  PORT_SPI |= (1 << DD_SS); // chip_select_disable();
}

void st7735_test_screen(uint16_t del)
{
  delay(del);
  st7735_fill(_WHITE, 5, 5, 10, 10);  
  delay(del);
  st7735_fill(_RED, 10, 10, 20, 20);  
  delay(del);
  st7735_fill(_GREEN, 15, 15, 30, 30);  
  delay(del);
  st7735_fill(_BLUE, 20, 20, 40, 40);  
  delay(del);
  st7735_fill(_RED_BLUE, 25, 25, 50, 50);  
  delay(del);
  st7735_fill(_BLUE_GREEN, 30, 30, 60, 60);  
  delay(del);
  st7735_fill(_RED_GREEN, 35, 35, 70, 70);  
  delay(500);
  st7735_fill(_BLACK);
  // st7735_setFontBGcolor(_WHITE);
  st7735_drawPixel(40,10,_BLUE_GREEN);
  st7735_fill(_WHITE, 10, 10, 10, 10);  
  st7735_setCursor(25, 25);
  st7735_print("a");  
  st7735_setCursor(35, 25);
  st7735_print("Hello");
  st7735_setFontSize(2);
  st7735_setFontColor(_GREEN);   
  st7735_setCursor(10, 40);
  st7735_print("Hello");
  st7735_setFontColor(_BLUE);
  st7735_setCursor(80, 40);
  st7735_print("World");  
  st7735_setFontColor(_RED); 
  st7735_setFontSize(3);
  st7735_setCursor(5, 65);
  st7735_print("13:09");
  st7735_setFontColor(_RED_GREEN); 
  st7735_setCursor(90, 65);
  st7735_printNum(2023);
  delay(1000);
  // st7735_clear();
}

//
void st7735_print(uint8_t ch, uint16_t color)
{
  if (ch == '\n') {              // Newline?
    cursor_x = 0;               // Reset x to zero,
    cursor_y += textsize_y * 8; // advance y one line
  } else if (ch != '\r') {       // Ignore carriage returns
    if (wrap && ((cursor_x + textsize_x * 6) > _width)) { // Off right?
      cursor_x = 0;                                       // Reset x to zero,
      cursor_y += textsize_y * 8; // advance y one line
    }
    st7735_drawChar(cursor_x, cursor_y, ch, color, textbgcolor, textsize_x, textsize_y);
    cursor_x += textsize_x * 6; // Advance x one char
  }
}

//
void st7735_print(uint8_t ch)
{
  st7735_print(ch, textcolor);
}

//
void st7735_print(const char * ch, uint16_t color)
{
  const char * ptrCh = ch;
  while(*ptrCh != '\0') {
    st7735_print(*ptrCh, color);
    ptrCh++;
  }
}

//
void st7735_print(const char * ch)
{
  st7735_print(ch, textcolor);
}

//
void st7735_printNum(uint32_t number, uint16_t color)
{
  if (number <= 9) { 
    st7735_print(number + 0x30, color);
  }else if (number > 9 && number < 100) {
    st7735_print(number/10 + 0x30, color);
    st7735_print( number - ((number/10) * 10) + 0x30, color);
  }else if (number > 99 && number < 1000) {
    uint8_t temp = number / 100;
    st7735_print(temp + 0x30, color);
    uint8_t temp2 = ( number - temp*100 )  / 10;
    st7735_print(temp2 + 0x30, color);
    uint8_t temp3 = number - temp*100 - temp2*10;
    st7735_print(temp3 + 0x30, color);
  }else if (number > 999 && number < 10000) {
    uint8_t temp = number / 1000;
    st7735_print(temp + 0x30, color);
    uint8_t temp2 = ( number - temp*1000 )  / 100;
    st7735_print(temp2 + 0x30, color);
    uint8_t temp3 = (number - temp*1000 - temp2*100) / 10;
    st7735_print(temp3 + 0x30, color);
    uint8_t temp4 = number - temp*1000 - temp2*100 - temp3*10;
    st7735_print(temp4 + 0x30, color);
  }
}

//
void st7735_printNum(uint32_t number)
{  
  st7735_printNum(number, textcolor);
}

//
void st7735_drawChar(uint8_t x, uint8_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y)
{
  const GFXfont *gfxFont = &font;

  c -= (uint8_t)pgm_read_byte(&gfxFont->first);
  GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c);
  uint8_t *bitmap = pgm_read_bitmap_ptr(gfxFont);

  uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
  uint8_t w = pgm_read_byte(&glyph->width), h = pgm_read_byte(&glyph->height);
  uint8_t xo = pgm_read_byte(&glyph->xOffset),
         yo = pgm_read_byte(&glyph->yOffset);
  uint8_t xx, yy, bits = 0, bit = 0;
  uint16_t xo16 = 0, yo16 = 0;

  if (size_x > 1 || size_y > 1) {
    xo16 = xo;
    yo16 = yo;
  }

  for (yy = 0; yy < h; yy++) {
    for (xx = 0; xx < w; xx++) {
      if (!(bit++ & 7)) {
        bits = pgm_read_byte(&bitmap[bo++]);
      }
      if (bits & 0x80) {
        if (size_x == 1 && size_y == 1) {
          st7735_drawPixel(x + xo + xx, y + yo + yy, color);
        } else {
          st7735_fill(color, x + (xo16 + xx) * size_x, y + (yo16 + yy) * size_y, size_x, size_y);
        }
      }
      bits <<= 1;
    }
  }
}

//
void st7735_setCursor(uint8_t x, uint8_t y)
{
  cursor_x = x;
  cursor_y = y;
}

//
void st7735_setFontSize(uint8_t size)
{  
  textsize_x = size;
  textsize_y = size;
}

//
void st7735_setFontSize(uint8_t sizeX, uint8_t sizeY)
{  
  if (rotation == 1) {
    textsize_x = sizeY;
    textsize_y = sizeX;
  }else {    
    textsize_x = sizeX;
    textsize_y = sizeY;
  }
}

//
void st7735_setFontColor(uint16_t color)
{
  textcolor = color;
}

//
void st7735_setFontBgColor(uint16_t color)
{
  textbgcolor = color;
}

//
void st7735_setFontDotColor(uint16_t color)
{
  dotcolor = color;
}

void st7735_setRotation(uint8_t r)
{
  rotation = r;  
  if (r) {
    _width = ST7735_HEIGHT;
    _height = ST7735_WIDTH;
  }else {    
    _width = ST7735_WIDTH;
    _height = ST7735_HEIGHT;
  }
}




#endif  /* _ST7735_H_ */
