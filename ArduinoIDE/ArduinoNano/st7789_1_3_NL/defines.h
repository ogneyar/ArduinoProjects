
#ifndef _DEFINES_H_
#define _DEFINES_H_


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


#define RGBto565(r,g,b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3)) 

// Some ready-made 16-bit ('565') color settings:
// НЕ RGB А RBG
#define _BLACK 0x0000
#define _WHITE 0xFFFF
#define _RED 0x07E0
#define _GREEN 0x001F
#define _BLUE 0xF800
#define _RED_BLUE 0xFFE0    // фиолетовый
#define _RED_GREEN 0x07FF  // голубой
#define _BLUE_GREEN 0xF81F   // оранджевый

#define LCD_D        1 // data
#define LCD_C        0 // command

#define ST7789_SHIFT  80
#define ST7789_XSTART 0
#define ST7789_YSTART 0
#define ST7789_WIDTH  240
#define ST7789_HEIGHT 240


#endif  /* _DEFINES_H_ */

