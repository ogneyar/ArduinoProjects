
// Uno

#include "defines.h"

void testScreen(void);
void begin(void);
void reset(void);
void init_table16(const void *table, int16_t size);
void WriteCmdData(uint16_t cmd, uint16_t dat);
void fillScreen(uint16_t color);
void drawPixel(int16_t x, int16_t y, uint16_t color);
void setRotation(uint8_t r);
void invertDisplay(boolean i);
void vertScroll(int16_t top, int16_t scrollines, int16_t offset);
void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void fill(uint16_t color);

uint16_t _lcd_ID, _lcd_rev, _lcd_madctl, _lcd_drivOut, _MC, _MP, _MW, _SC, _EC, _SP, _EP;
uint16_t  _lcd_xor, _lcd_capable, _width, _height, rotation;

//
void setup(void) 
{
  begin();
  testScreen();
}

//
void loop(void) 
{

}

//
void testScreen(void) 
{
  uint8_t x, y;
  uint16_t del = 1000;
  fillScreen(0xf800);
  delay(del);
  x = 60, y = 160;
  while(x++ < 180) drawPixel(x, y, 0xffff);
  x = 120, y = 80;
  while(y++ < 240) drawPixel(x, y, 0xffff);
  delay(del);
  fillScreen(0x008f);
  delay(del);
  x = 60, y = 160;
  while(x++ < 180) drawPixel(x, y, 0xffff);
  x = 120, y = 80;
  while(y++ < 240) drawPixel(x, y, 0xffff);
  delay(del);
  fillScreen(0x0ff0);
}

//
void begin(void)
{
  _width = 240;
  _height = 320;
  reset();
  _lcd_capable = 0 | REV_SCREEN | READ_BGR;
  init_table16(ILI9320_regValues, sizeof(ILI9320_regValues));  
  _lcd_rev = ((_lcd_capable & REV_SCREEN) != 0);
  setRotation(0);             //PORTRAIT
  invertDisplay(false);
}

//
void reset(void)
{
  setWriteDir();
  CTL_INIT();
  CS_IDLE;
  RD_IDLE;
  WR_IDLE;
}

//
void init_table16(const void *table, int16_t size)
{
    uint16_t *p = (uint16_t *) table;
    while (size > 0) {
        uint16_t cmd = pgm_read_word(p++);
        uint16_t d = pgm_read_word(p++);
        if (cmd == TFTLCD_DELAY)
            delay(d);
        else {
            CS_ACTIVE;
            WriteCmd(cmd);
            WriteData(d);
            CS_IDLE;
        }
        size -= 2 * sizeof(int16_t);
    }
}

//
void WriteCmdData(uint16_t cmd, uint16_t dat)
{
    CS_ACTIVE;
    WriteCmd(cmd);
    WriteData(dat);
    CS_IDLE;
}

//
void fillScreen(uint16_t color)
{ 
  fillRect(0, 0, _width, _height, color); 
}

//
void drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if (x < 0 || y < 0 || x >= _width || y >= _height) return;        
  WriteCmdData(_MC, x);
  WriteCmdData(_MP, y);        
  WriteCmdData(_MW, color);
}

//
void setRotation(uint8_t r)
{
  uint16_t GS, SS, ORG, REV = _lcd_rev;
  uint8_t val, d[3];
  rotation = r & 3;           // just perform the operation ourselves on the protected variables
  _width = (rotation & 1) ? HEIGHT : WIDTH;
  _height = (rotation & 1) ? WIDTH : HEIGHT;
  switch (rotation) {
    case 0:                    //PORTRAIT:
      val = 0x48;             //MY=0, MX=1, MV=0, ML=0, BGR=1
      break;
  case 1:                    //LANDSCAPE: 90 degrees
      val = 0x28;             //MY=0, MX=0, MV=1, ML=0, BGR=1
      break;
  case 2:                    //PORTRAIT_REV: 180 degrees
      val = 0x88;             //MY=1, MX=0, MV=0, ML=1, BGR=1
      break;
  case 3:                    //LANDSCAPE_REV: 270 degrees
      val = 0xf8;             //MY=1, MX=1, MV=1, ML=1, BGR=1
      break;
  }
    
  _MC = 0x20, _MP = 0x21, _MW = 0x22, _SC = 0x50, _EC = 0x51, _SP = 0x52, _EP = 0x53;
  GS = (val & 0x80) ? (1 << 15) : 0;
  WriteCmdData(0x60, GS | 0x2700);    // Gate Scan Line (0xA700)
  
  SS = (val & 0x40) ? (1 << 8) : 0;
  SS = (val&0x05)<<8;
  WriteCmdData(0x01, SS);     // set Driver Output Control
  
  ORG = (val & 0x20) ? (1 << 3) : 0;
  if (val & 0x08)
      ORG |= 0x1000;  //BGR
  _lcd_madctl = ORG | 0x0030;
  WriteCmdData(0x03, _lcd_madctl);    // set GRAM write direction and BGR=1.
  
  setAddrWindow(0, 0, _width - 1, _height - 1);
  vertScroll(0, HEIGHT, 0);   //reset scrolling after a rotation
}

//
void invertDisplay(boolean i)
{
  _lcd_rev = ((_lcd_capable & REV_SCREEN) != 0) ^ i;    
  WriteCmdData(0x61, _lcd_rev);        
}

//
void vertScroll(int16_t top, int16_t scrollines, int16_t offset)
{
  int16_t vsp;  
  if (offset <= -scrollines || offset >= scrollines) offset = 0; //valid scroll
	vsp = top + offset; // vertical start position
  if (offset < 0) vsp += scrollines;          //keep in unsigned range
  WriteCmdData(0x61, (1 << 1) | _lcd_rev);        //!NDL, VLE, REV
  WriteCmdData(0x6A, vsp);        //VL#
}

//
void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1)
{
  WriteCmdData(_MC, x);
  WriteCmdData(_MP, y);
  WriteCmdData(_SC, x);
  WriteCmdData(_SP, y);
  WriteCmdData(_EC, x1);
  WriteCmdData(_EP, y1);
}

//
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  int16_t end;
  if (w < 0) {
      w = -w;
      x -= w;
  }                           //+ve w
  end = x + w;
  if (x < 0)
      x = 0;
  if (end > _width)
      end = _width;
  w = end - x;
  if (h < 0) {
      h = -h;
      y -= h;
  }                           //+ve h
  end = y + h;
  if (y < 0)
      y = 0;
  if (end > _height)
      end = _height;
  h = end - y;

  setAddrWindow(x, y, x + w - 1, y + h - 1);
  CS_ACTIVE;
  WriteCmd(_MW);
  if (h > w) {
      end = h;
      h = w;
      w = end;
  }
  uint8_t hi = color >> 8, lo = color & 0xFF;
  CD_DATA;
  while (h-- > 0) {
      end = w;
      
      do {
          write8(hi);
          write8(lo);
      } while (--end != 0);
  }
  CS_IDLE;
}

//
void fill(uint16_t color)
{
  uint16_t h = _height, w = _width;
  setAddrWindow(0, 0, _width, _height);
  CS_ACTIVE;
  WriteCmd(_MW);
  uint8_t hi = color >> 8, lo = color & 0xFF;
  CD_DATA;
  while (h-- > 0) {
      do {
          write8(hi);
          write8(lo);
      } while (--w != 0);
  }
  CS_IDLE;
}


