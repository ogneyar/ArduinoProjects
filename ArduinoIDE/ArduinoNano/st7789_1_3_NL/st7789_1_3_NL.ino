
// Nano

#include "spi.h"
#include "defines.h"


void st7735_fill(uint16_t color, uint8_t hl = 0, uint8_t hr = 0, uint8_t vt = 0, uint8_t vb = 0);
void st7735_set_column_and_page(uint8_t caset1 = ST7789_XSTART, uint8_t caset2 = ST7789_XSTART + ST7789_WIDTH, uint8_t raset1 = ST7789_YSTART, uint8_t raset2 = ST7789_YSTART + ST7789_HEIGHT);


void setup(void) {
  SPI_Master_Init();
  st7735_init();
  
  st7735_clear();
    
  delay(1000);
  st7735_fill(_WHITE, 5, 5, 10, 10);
  
  delay(1000);
  st7735_fill(_RED, 10, 10, 20, 20);
  
  delay(1000);
  st7735_fill(_GREEN, 15, 15, 30, 30);
  
  delay(1000);
  st7735_fill(_BLUE, 20, 20, 40, 40);
  
  delay(1000);
  st7735_fill(_RED_BLUE, 25, 25, 50, 50);
  
  delay(1000);
  st7735_fill(_BLUE_GREEN, 30, 30, 60, 60);
  
  delay(1000);
  st7735_fill(_RED_GREEN, 35, 35, 70, 70);    
}

void loop() {}


void st7735_display(uint16_t color)
{
  st7735_send(LCD_C, ST77XX_RAMWR); // 0x2C
  
  uint8_t c1=(uint8_t)((color & 0x00ff));
  uint8_t c2=color>>8;

  for (uint32_t i=0; i < 57600; i++)
  {
     st7735_send(LCD_D, c1);
     st7735_send(LCD_D, c2);
  }
}


void st7735_fill(uint16_t color, uint8_t hl, uint8_t hr, uint8_t vt, uint8_t vb) // hl - horisontal left,  hr - horisontal right, vt - vertical top,  vb - vertical bottom
{
  PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
  st7735_set_column_and_page(ST7789_XSTART + hl, ST7789_XSTART + ST7789_WIDTH - hr, ST7789_YSTART + vt, ST7789_YSTART + ST7789_HEIGHT - vb);

  st7735_display(color);
  PORT_SPI |= (1 << DD_SS); // chip_select_disable();
}



void st7735_set_column_and_page(uint8_t caset1, uint8_t caset2, uint8_t raset1, uint8_t raset2)
{
  st7735_send(LCD_C, ST77XX_CASET); // 0x2A
  st7735_send(LCD_D, 0x00);   // x1 low byte - начало
  st7735_send(LCD_D, caset1); // x1 high byte 
  st7735_send(LCD_D, 0x00);   // x2 low byte - конец
  st7735_send(LCD_D, caset2); // x1 high byte    // 240 horizontal

  st7735_send(LCD_C, ST77XX_RASET); // 0x2B
  st7735_send(LCD_D, 0x00);   // y1 low byte - начало
  st7735_send(LCD_D, raset1); // y1 high byte 
  st7735_send(LCD_D, 0x00);   // y2 low byte - конец
  st7735_send(LCD_D, raset2); // y1 high byte    // 240 hvertical
}


void st7735_clear()
{
  st7735_fill(_BLACK);
}



void st7735_send(uint8_t dc, uint8_t data)
{
  if (dc == LCD_D) PORT_SPI |= (1 << DD_DC); // gpio_set(GPIOB,DC);
  else PORT_SPI &= ~(1 << DD_DC); // gpio_reset(GPIOB,DC);
  SPI_Master_SendByte(data);
}


void st7735_init() 
{  
    PORT_SPI &= ~(1 << DD_RES);
    delay(50);
    PORT_SPI |= (1 << DD_RES);
    delay(50);

    PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
    
    st7735_send(LCD_C, ST77XX_SWRESET); // 0x01 //  1: Software reset, 0 args, w/delay
    delay(150);
    st7735_send(LCD_C, ST77XX_SLPOUT); // 0x11 //  2: Out of sleep mode, 0 args, w/delay
    delay(500);

    st7735_send(LCD_C, ST77XX_COLMOD); // 0x3A // 15: set color mode, 1 arg
    st7735_send(LCD_D, 0x05); 
    delay(10);
    
    st7735_send(LCD_C, ST77XX_INVON); // 0x21 // 13: Invert display, no args
    delay(10);
        
    st7735_send(LCD_C, ST77XX_DISPON); // 0x29 //  4: Main screen turn on, no args w/delay
    delay(20);

    PORT_SPI |= (1 << DD_SS); // chip_select_disable();
}


