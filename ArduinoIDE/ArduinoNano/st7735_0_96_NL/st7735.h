
#ifndef _ST7735_H_
#define _ST7735_H_


// значения по умолчанию
void st7735_fill(uint16_t color, uint8_t hl = 0, uint8_t hr = 0, uint8_t vt = 0, uint8_t vb = 0);
void st7735_set_column_and_page(uint8_t caset1 = ST7735_XSTART + ST7735_SHIFT, uint8_t caset2 = ST7735_XSTART + ST7735_SHIFT + ST7735_WIDTH, uint8_t raset1 = ST7735_YSTART, uint8_t raset2 = ST7735_YSTART + ST7735_HEIGHT);


//
void st7735_send(uint8_t dc, uint8_t data)
{
  if (dc == LCD_D) PORT_SPI |= (1 << DD_DC); // gpio_set(GPIOB,DC);
  else PORT_SPI &= ~(1 << DD_DC); // gpio_reset(GPIOB,DC);
  SPI_Master_SendByte(data);
  // _delay_us(20);
}

//
void st7735_display(uint16_t color)
{
  uint8_t c1=(uint8_t)((color & 0x00ff));
  uint8_t c2=color>>8;

  st7735_send(LCD_C, ST77XX_RAMWR); // 0x2C
  
  for (uint16_t i=0; i < (uint16_t)13040; i++)
  {
     st7735_send(LCD_D, c1);
     st7735_send(LCD_D, c2);
  }
}

//
void st7735_set_column_and_page(uint8_t caset1, uint8_t caset2, uint8_t raset1, uint8_t raset2)
{
  st7735_send(LCD_C, ST77XX_CASET); // 0x2A
  st7735_send(LCD_D, 0x00); // x1 high - начало
  st7735_send(LCD_D, caset1); // x1 low   // + 26 shift
  st7735_send(LCD_D, 0x00); // x2 high - конец
  st7735_send(LCD_D, caset2); // x2 low   // 80 horizontal + 26 shift

  st7735_send(LCD_C, ST77XX_RASET); // 0x2B
  st7735_send(LCD_D, 0x00); // y1 high - начало
  st7735_send(LCD_D, raset1); // y1 low
  st7735_send(LCD_D, 0x00); // y2 high - конец
  st7735_send(LCD_D, raset2); // y2 low  // 160 vertical
}

//
void st7735_fill(uint16_t color, uint8_t hl, uint8_t hr, uint8_t vt, uint8_t vb) // hl - horisontal left,  hr - horisontal right, vt - vertical top,  vb - vertical bottom
{
  PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
    
  st7735_set_column_and_page(ST7735_XSTART + ST7735_SHIFT + hl, ST7735_XSTART + ST7735_WIDTH + ST7735_SHIFT - hr, ST7735_YSTART + vt, ST7735_YSTART + ST7735_HEIGHT - vb);
  
  st7735_display(color);

  PORT_SPI |= (1 << DD_SS); // chip_select_disable();
}

//
void st7735_clear()
{
  st7735_fill(_BLACK);
}

//
void st7735_init_minimal() {
  
    PORT_SPI &= ~(1 << DD_RES);
    // PORTD &= ~(1 << DD_RES);
    delay(10);
    PORT_SPI |= (1 << DD_RES);
    // PORTD |= (1 << DD_RES);
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



void st7735_init() {
  
    PORT_SPI &= ~(1 << DD_RES);
    delay(10);
    PORT_SPI |= (1 << DD_RES);
    delay(10);

    PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
    
    st7735_send(LCD_C, ST77XX_SWRESET); // 0x01 //  1: Software reset, 0 args, w/delay
    delay(150);
    st7735_send(LCD_C, ST77XX_SLPOUT); // 0x11 //  2: Out of sleep mode, 0 args, w/delay
    delay(255);

    st7735_send(LCD_C, ST7735_FRMCTR1); // 0xB1 //  3: Framerate ctrl - normal mode, 3 arg
    st7735_send(LCD_D, 0x01);
    st7735_send(LCD_D, 0x2C);
    st7735_send(LCD_D, 0x2D);

    st7735_send(LCD_C, ST7735_FRMCTR2); // 0xB2 //  4: Framerate ctrl - idle mode, 3 args
    st7735_send(LCD_D, 0x01);
    st7735_send(LCD_D, 0x2C);
    st7735_send(LCD_D, 0x2D);

    st7735_send(LCD_C, ST7735_FRMCTR3); // 0xB3 //  5: Framerate - partial mode, 6 args
    st7735_send(LCD_D, 0x01);
    st7735_send(LCD_D, 0x2C);
    st7735_send(LCD_D, 0x2D);
    st7735_send(LCD_D, 0x01);
    st7735_send(LCD_D, 0x2C);
    st7735_send(LCD_D, 0x2D);

    st7735_send(LCD_C, ST7735_INVCTR); // 0xB4 //  6: Display inversion ctrl, 1 arg
    st7735_send(LCD_D, 0x07); //     No inversion

    st7735_send(LCD_C, ST7735_PWCTR1); // 0xC0 //  7: Power control, 3 args
    st7735_send(LCD_D, 0xA2);
    st7735_send(LCD_D, 0x02);
    st7735_send(LCD_D, 0x84);

    st7735_send(LCD_C, ST7735_PWCTR2); // 0xC1 //  8: Power control, 1 arg
    st7735_send(LCD_D, 0xC5);

    st7735_send(LCD_C, ST7735_PWCTR3); // 0xC2 //  9: Power control, 2 args
    st7735_send(LCD_D, 0x0A);
    st7735_send(LCD_D, 0x00);

    st7735_send(LCD_C, ST7735_PWCTR4); // 0xC3 // 10: Power control, 2 args
    st7735_send(LCD_D, 0x8A);
    st7735_send(LCD_D, 0x2A);

    st7735_send(LCD_C, ST7735_PWCTR5); // 0xC4 // 11: Power control, 2 args
    st7735_send(LCD_D, 0x8A);
    st7735_send(LCD_D, 0xEE);

    st7735_send(LCD_C, ST7735_VMCTR1); // 0xC5 // 12: Power control, 1 arg
    st7735_send(LCD_D, 0x0E);

    // st7735_send(LCD_C, ST77XX_INVOFF); // 0x20 // 13: Don't invert display, no args
    st7735_send(LCD_C, ST77XX_INVON); // 0x21 // 13: Invert display, no args

    st7735_send(LCD_C, ST77XX_MADCTL); // 0x36 // 14: Mem access ctl (directions), 1 arg 
    st7735_send(LCD_D, 0xC0); // направление  (0b11111100 - mask)

    st7735_send(LCD_C, ST77XX_COLMOD); // 0x3A // 15: set color mode, 1 arg
    st7735_send(LCD_D, 0x05); // 16-bit/pixel 
    // st7735_send(LCD_D, 0x03); // 12-bit/pixel 

    st7735_send(LCD_C, ST77XX_CASET); // 0x2A //  2: Column addr set, 4 args
    st7735_send(LCD_D, 0);
    st7735_send(LCD_D, 0);
    st7735_send(LCD_D, 0);
    st7735_send(LCD_D, 0x4f);         // 79 horizontal

    st7735_send(LCD_C, ST77XX_RASET); // 0x2B //  3: Row addr set, 4 args
    st7735_send(LCD_D, 0);
    st7735_send(LCD_D, 0);
    st7735_send(LCD_D, 0);
    st7735_send(LCD_D, 0x9f);         // 159  vertical

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

    st7735_send(LCD_C, ST77XX_NORON); // 0x13 //  3: Normal display on, no args, w/delay
    delay(10);

    st7735_send(LCD_C, ST77XX_DISPON); // 0x29 //  4: Main screen turn on, no args w/delay
    delay(100);

    PORT_SPI |= (1 << DD_SS); // chip_select_disable();
}


#endif  /* _ST7735_H_ */


