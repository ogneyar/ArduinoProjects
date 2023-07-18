
#ifndef _ST_DEFINES_H_
#define _ST_DEFINES_H_


  // НЕ RGB А RBG
// Some ready-made 16-bit ('565') color settings:
#define _BLACK 0x0000
#define _WHITE 0xFFFF
#define _RED 0xF800
#define _GREEN 0x001F
#define _BLUE 0x07E0
#define _RED_BLUE 0xFFE0    // розовый
#define _BLUE_GREEN 0x07FF  // голубой
#define _RED_GREEN 0xF81F   // жёлтый

#define RGB565RBG(r, g, b) ((((r)&0xF8) << 8) | (((b)&0xFC) << 3) | ((g) >> 3))

#define BLACK RGB565RBG(0, 0, 0)
#define NAVY RGB565RBG(0, 0, 123)
#define DARKGREEN RGB565RBG(0, 125, 0)
#define DARKCYAN RGB565RBG(0, 125, 123)
#define MAROON RGB565RBG(123, 0, 0)
#define PURPLE RGB565RBG(123, 0, 123)
#define OLIVE RGB565RBG(123, 125, 0)
#define LIGHTGREY RGB565RBG(198, 195, 198)
#define DARKGREY RGB565RBG(123, 125, 123)
#define BLUE RGB565RBG(0, 0, 255)
#define GREEN RGB565RBG(0, 255, 0)
#define CYAN RGB565RBG(0, 255, 255)
#define RED RGB565RBG(255, 0, 0)
#define MAGENTA RGB565RBG(255, 0, 255)
#define YELLOW RGB565RBG(255, 255, 0)
#define WHITE RGB565RBG(255, 255, 255)
#define ORANGE RGB565RBG(255, 127, 0)
#define GREENYELLOW RGB565RBG(173, 255, 41)
#define PINK RGB565RBG(255, 130, 198)
#define VIOLET RGB565RBG(255, 0, 127)


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


#define LCD_D        1 // data
#define LCD_C        0 // command

#define ST7735_SHIFT  26
#define ST7735_XSTART 0
#define ST7735_YSTART 0
#define ST7735_WIDTH  80
#define ST7735_HEIGHT 160


#endif  /* _ST_DEFINES_H_ */
