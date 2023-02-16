
// ATtiny88 (MH-Tiny)

#include "spi.h"
#include <util/delay.h>


// Some register settings
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH 0x04

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5

#define ST7735_PWCTR6 0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1


#define ST77XX_NOP 0x00
#define ST77XX_SWRESET 0x01
#define ST77XX_RDDID 0x04
#define ST77XX_RDDST 0x09

#define ST77XX_SLPIN 0x10
#define ST77XX_SLPOUT 0x11
#define ST77XX_PTLON 0x12
#define ST77XX_NORON 0x13

#define ST77XX_INVOFF 0x20
#define ST77XX_INVON 0x21
#define ST77XX_DISPOFF 0x28
#define ST77XX_DISPON 0x29
#define ST77XX_CASET 0x2A
#define ST77XX_RASET 0x2B
#define ST77XX_RAMWR 0x2C
#define ST77XX_RAMRD 0x2E

#define ST77XX_PTLAR 0x30
#define ST77XX_TEOFF 0x34
#define ST77XX_TEON 0x35
#define ST77XX_MADCTL 0x36
#define ST77XX_COLMOD 0x3A

#define ST77XX_MADCTL_MY 0x80
#define ST77XX_MADCTL_MX 0x40
#define ST77XX_MADCTL_MV 0x20
#define ST77XX_MADCTL_ML 0x10
#define ST77XX_MADCTL_RGB 0x00


// Some ready-made 16-bit ('565') color settings:
#define _BLACK 0x0000
#define _WHITE 0xFFFF
#define _RED 0xF800
#define _GREEN 0x001F
#define _BLUE 0x07E0
#define _RED_BLUE 0xFFE0    // розовый
#define _BLUE_GREEN 0x07FF  // голубой
#define _RED_GREEN 0xF81F   // жёлтый

#define LCD_D        1 // data
#define LCD_C        0 // command

void st7735_fill(uint16_t color, uint8_t hl = 0, uint8_t hr = 0, uint8_t vt = 0, uint8_t vb = 0);
void st7735_set_column_and_page(uint8_t caset1 = 0x1a, uint8_t caset2 = 0x6a, uint8_t raset1 = 0x00, uint8_t raset2 = 0xa0);


void setup(void) {
  SPI_Master_Init();
  // st7735_init();
  st7735_init_minimal();
  st7735_clear();
  
  // НЕ RGB А RBG
  
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
  uint8_t c1=(uint8_t)((color & 0x00ff));
  uint8_t c2=color>>8;

  //PORT_SPI |= (1 << DD_DC); // gpio_set(GPIOB,DC);
  for (uint16_t i=0; i < (uint16_t)13040; i++)
  {
     st7735_send(LCD_D, c1);
     st7735_send(LCD_D, c2);
  }
}

void st7735_fill(uint16_t color, uint8_t hl, uint8_t hr, uint8_t vt, uint8_t vb) // hl - horisontal left,  hr - horisontal right, vt - vertical top,  vb - vertical bottom
{
  PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();

  st7735_set_column_and_page(0x1a+hl, 0x6a-hr, 0x00+vt, 0xa0-vb);

  st7735_send(LCD_C, ST77XX_RAMWR); // 0x2C
  
  st7735_display(color);

  PORT_SPI |= (1 << DD_SS); // chip_select_disable();
}



void st7735_set_column_and_page(uint8_t caset1, uint8_t caset2, uint8_t raset1, uint8_t raset2)
{
  st7735_send(LCD_C, ST77XX_CASET); // 0x2A
  st7735_send(LCD_D, 0x00); // x1 - начало
  st7735_send(LCD_D, caset1); // y1
  st7735_send(LCD_D, 0x00); // x2 - конец
  st7735_send(LCD_D, caset2); // y1   // 128 horizontal

  st7735_send(LCD_C, ST77XX_RASET); // 0x2B
  st7735_send(LCD_D, 0x00); // x1 - начало
  st7735_send(LCD_D, raset1); // y1
  st7735_send(LCD_D, 0x00); // x2 - конец
  st7735_send(LCD_D, raset2); // y1   // 160 vertical
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
  _delay_us(2);
}


void st7735_init_minimal() {
  
    PORT_SPI &= ~(1 << DD_RES);
    delay(10);
    PORT_SPI |= (1 << DD_RES);
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



