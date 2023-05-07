
#ifndef _ILI9488_H_
#define _ILI9488_H_

#include "tft_font.h"

#define WIDTH 320
#define HEIGHT 480

#include <TouchScreen.h>
#include <SPI.h>
#include <SD.h>

// список функций
void begin(void);
void reset(void);
static void init_table(const void *table, int16_t size);
static inline void WriteCmdParam4(uint8_t cmd, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);
static void WriteCmdParamN(uint16_t cmd, int8_t N, uint8_t * block);
void WriteCmdData(uint16_t cmd, uint16_t dat);
void fillScreen(uint16_t color);
void drawPixel(int16_t x, int16_t y, uint16_t color);
void setRotation(uint8_t r);
void invertDisplay(boolean i);
void vertScroll(int16_t top, int16_t scrollines, int16_t offset);
void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void fill(uint16_t color);
//
void fillDelay(uint16_t color, uint16_t del);
void pushColors(uint16_t * block, int16_t n, bool first);
uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
// bmp
void bmpDraw(char *filename, int x, int y);
uint16_t read16(File f);
uint32_t read32(File f);
//
void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void writeHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void writeVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void drawRectWide(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
//
void drawCross(void);
//
void print(uint8_t ch);
void print(const char *ch);

void drawChar(int16_t x, int16_t y, unsigned char ch, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y);
void setCursor(int16_t x, int16_t y);

uint16_t _lcd_ID, _lcd_rev, _lcd_madctl, _lcd_drivOut, _MC, _MP, _MW, _SC, _EC, _SP, _EP;
uint16_t  _lcd_xor, _lcd_capable, _width, _height, rotation;

uint8_t wrap = 0, textsize_x = 3, textsize_y = 3;
int16_t cursor_x = 0, cursor_y = 0;
uint16_t textcolor = WHITE, textbgcolor = BLACK;

uint8_t spi_save;

#define SD_CS 5


static const uint8_t ILI9488_Init[] PROGMEM = {
    0x01, 0,            //Soft Reset
    TFTLCD_DELAY8, 50,
	0x11, 0,            //Sleep Out
    TFTLCD_DELAY8, 150,
    0x28, 0,            //Display Off
    0xC0, 2, 0x10, 0x10,        //Power Control 1 [0E 0E]
    0xC1, 1, 0x41,      //Power Control 2 [43]
    0xC5, 4, 0x00, 0x22, 0x80, 0x40,    //VCOM  Control 1 [00 40 00 40]
    0x36, 1, 0x68,      //Memory Access [00]
    0xB0, 1, 0x00,      //Interface     [00]
    0xB1, 2, 0xB0, 0x11,        //Frame Rate Control [B0 11]
    0xB4, 1, 0x02,      //Inversion Control [02]
    0xB6, 3, 0x02, 0x02, 0x3B,  // Display Function Control [02 02 3B] .kbv NL=480
    0xB7, 1, 0xC6,      //Entry Mode      [06]
    0x3A, 1, 0x55,      //Interlace Pixel Format [XX]
    0xF7, 4, 0xA9, 0x51, 0x2C, 0x82,    //Adjustment Control 3 [A9 51 2C 82]
    0x29, 0,            //Display On
};


//
void begin(void)
{
  _width = WIDTH;
  _height = HEIGHT;
  reset();  
  _lcd_capable = AUTO_READINC | MIPI_DCS_REV1 | MV_AXIS | READ_24BITS;
  init_table(ILI9488_Init, sizeof(ILI9488_Init));
  // _lcd_rev = ((_lcd_capable & REV_SCREEN) != 0);
  setRotation(0);             //PORTRAIT
  // invertDisplay(false);
// #ifdef __DEBUG
// #ifdef __SAMD21G18A__
//     SerialUSB.println(F("Begin TFT init"));
// #else
//     Serial.println(F("Begin TFT init"));
// #endif
}

//
void reset(void)
{
  setWriteDir();
  CTL_INIT();
  CS_IDLE;
  RD_IDLE;
  WR_IDLE;
  digitalWrite(5, LOW);
  delay(200);
  digitalWrite(5, HIGH);
}

//
static void init_table(const void *table, int16_t size)
{
    uint8_t *p = (uint8_t *) table, dat[16];
    while (size > 0) {
        uint8_t cmd = pgm_read_byte(p++);
        uint8_t len = pgm_read_byte(p++);
        if (cmd == TFTLCD_DELAY8) {
            delay(len);
            len = 0;
        } else {
            for (uint8_t i = 0; i < len; i++)
                dat[i] = pgm_read_byte(p++);
            WriteCmdParamN(cmd, len, dat);
        }
        size -= len + 2;
    }
}

//
static inline void WriteCmdParam4(uint8_t cmd, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4)
{
    uint8_t d[4];
    d[0] = d1, d[1] = d2, d[2] = d3, d[3] = d4;
    WriteCmdParamN(cmd, 4, d);
}

//
static void WriteCmdParamN(uint16_t cmd, int8_t N, uint8_t * block)
{
    CS_ACTIVE;
    WriteCmd(cmd);
    while (N-- > 0) {
        uint8_t u8 = *block++;
        CD_DATA;
        write8(u8);
    }
	
    CS_IDLE;
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
  
  if (_lcd_capable & MIPI_DCS_REV1) {
      WriteCmdParam4(_MC, x >> 8, x, x >> 8, x);
      WriteCmdParam4(_MP, y >> 8, y, y >> 8, y);
  }
	else {
    WriteCmdData(_MC, x);
    WriteCmdData(_MP, y);    
  }    
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
  if (_lcd_capable & MIPI_DCS_REV1) 
  {
    GS = (val & 0x80) ? (1 << 6) : 0;   //MY
    SS = (val & 0x40) ? (1 << 5) : 0;   //MX
    val &= 0x28;        //keep MV, BGR, MY=0, MX=0, ML=0
    d[0] = 0;
    d[1] = GS | SS | 0x02;      //MY, MX
    d[2] = 0x3B;
    WriteCmdParamN(0xB6, 3, d);
    _MC = 0x2A, _MP = 0x2B, _MW = 0x2C, _SC = 0x2A, _EC = 0x2A, _SP = 0x2B, _EP = 0x2B;
    WriteCmdParamN(0x36, 1, &val);
    _lcd_madctl = val;
  }
  else
  {
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
  }

  if ((rotation & 1) && ((_lcd_capable & MV_AXIS) == 0)) {
      uint16_t x;
      x = _MC, _MC = _MP, _MP = x;
      x = _SC, _SC = _SP, _SP = x;    //.kbv check 0139
      x = _EC, _EC = _EP, _EP = x;    //.kbv check 0139
  }
  setAddrWindow(0, 0, _width - 1, _height - 1);
  vertScroll(0, HEIGHT, 0);   //reset scrolling after a rotation
}

//
void invertDisplay(boolean i)
{
  _lcd_rev = ((_lcd_capable & REV_SCREEN) != 0) ^ i;   
  if (_lcd_capable & MIPI_DCS_REV1) {
    WriteCmdParamN(_lcd_rev ? 0x21 : 0x20, 0, NULL);
    return;
  }
  WriteCmdData(0x61, _lcd_rev);        
}

//
void vertScroll(int16_t top, int16_t scrollines, int16_t offset)
{
  int16_t bfa = HEIGHT - top - scrollines;  // bottom fixed area
  int16_t vsp;
  int16_t sea = top; 
  if (offset <= -scrollines || offset >= scrollines) offset = 0; //valid scroll
	vsp = top + offset; // vertical start position
  if (offset < 0) vsp += scrollines;          //keep in unsigned range
  sea = top + scrollines - 1;
  if (_lcd_capable & MIPI_DCS_REV1) {
    uint8_t d[6];           // for multi-byte parameters
    d[0] = top >> 8;        //TFA
    d[1] = top;
    d[2] = scrollines >> 8; //VSA
    d[3] = scrollines;
    d[4] = bfa >> 8;        //BFA
    d[5] = bfa;
    WriteCmdParamN(0x33, 6, d);
	  d[0] = vsp >> 8;        //VSP
    d[1] = vsp;
    WriteCmdParamN(0x37, 2, d);
    if (offset == 0 && (_lcd_capable & MIPI_DCS_REV1)) {
		  WriteCmdParamN(0x13, 0, NULL);    //NORMAL i.e. disable scroll
	  }
	  return;
  }

  WriteCmdData(0x61, (1 << 1) | _lcd_rev);        //!NDL, VLE, REV
  WriteCmdData(0x6A, vsp);        //VL#
}

//
void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1)
{
  if (_lcd_capable & MIPI_DCS_REV1) {
    WriteCmdParam4(_MC, x >> 8, x, x1 >> 8, x1);
    WriteCmdParam4(_MP, y >> 8, y, y1 >> 8, y1);
  }
  else {
    WriteCmdData(_MC, x);
    WriteCmdData(_MP, y);
    WriteCmdData(_SC, x);
    WriteCmdData(_SP, y);
    WriteCmdData(_EC, x1);
    WriteCmdData(_EP, y1);
  }
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
      
#if USING_16BIT_BUS
#define STROBE_16BIT {WR_ACTIVE; WR_IDLE;}
        write16(color);        //we could just do the strobe 
        uint8_t lo = end & 7;
        uint8_t hi = end >> 3;
        if (hi)
            do {
                STROBE_16BIT;
                STROBE_16BIT;
                STROBE_16BIT;
                STROBE_16BIT;
                STROBE_16BIT;
                STROBE_16BIT;
                STROBE_16BIT;
                STROBE_16BIT;
            } while (--hi > 0);
        while (lo-- > 0) {
            STROBE_16BIT;
        }
#else
      do {
          write8(hi);
          write8(lo);
      } while (--end != 0);
#endif
  }
  CS_IDLE;
  if (!(_lcd_capable & MIPI_DCS_REV1))
        setAddrWindow(0, 0, _width - 1, _height - 1);
}

//
void fill(uint16_t color)
{
  fillDelay(color, 0);
}


//
void fillDelay(uint16_t color, uint16_t del)
{
  uint16_t end;
  uint16_t h = _height, w = _width;
  setAddrWindow(0, 0, _width - 1, _height - 1);
  CS_ACTIVE;
  WriteCmd(_MW);
  CD_DATA;
  // uint8_t hi = (uint8_t)(color >> 8), lo = (uint8_t)color;
  while (h-- > 0) {
    end = w;
    do {
      if (del) for(uint16_t i = 0; i < del; i++) asm("NOP"); 
      write16(color);
      // write8(hi);
      // write8(lo);
    } while (--end != 0);
  }
  CS_IDLE;
}

//
void pushColors(uint16_t * block, int16_t n, bool first)
{
  uint16_t color;
  CS_ACTIVE;
  if (first) {
    WriteCmd(_MW);
  }  
  CD_DATA;
  while (n-- > 0) {
    color = *block++;
    write16(color);
  }
  CS_IDLE;
}

//
uint16_t color565(uint8_t r, uint8_t g, uint8_t b)
{ 
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3); 
}


#define BUFFPIXEL 20
//
void bmpDraw(char *filename, int x, int y)
{
  File 	bmpFile;
  int		bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t	bmpDepth;			   // Bit depth (currently must be 24)
  uint32_t bmpImageoffset; 	   // Start of image data in file
  uint32_t rowSize;			   // Not always = bmpWidth; may have padding
  uint8_t	sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  uint8_t	buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean	goodBmp = false;	   // Set to true on valid header parse
  boolean	flip	= true; 	   // BMP is stored bottom-to-top
  int		w, h, row, col;
  uint8_t	r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t	lcdidx = 0;
  boolean	first = true;
 
  if((x >= _width) || (y >= _height)) return;

#ifdef __DEBUG
#ifdef __SAMD21G18A__
  SerialUSB.println();
  SerialUSB.print("Loading image '");
  SerialUSB.print(filename);
  SerialUSB.println('\'');
#else
  Serial.println();
  Serial.print("Loading image '");
  Serial.print(filename);
  Serial.println('\'');
#endif
#endif
  // Open requested file on SD card
#ifndef __SAMD21G18A__
  SPCR = spi_save;
#endif
  if ((bmpFile = SD.open(filename)) == NULL) {
#ifdef __DEBUG
  #ifdef __SAMD21G18A__
    SerialUSB.print("File not found");
  #else
    Serial.print("File not found");
  #endif
#endif
	  return;
  }
 
  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature

#ifdef __DEBUG
  #ifdef __SAMD21G18A__
      SerialUSB.print(F("File size: ")); SerialUSB.println(read32(bmpFile));
  #else
      Serial.print(F("File size: ")); Serial.println(read32(bmpFile));
  #endif
#else
    (void)read32(bmpFile);
#endif
	  (void)read32(bmpFile); // Read & ignore creator bytes
	  bmpImageoffset = read32(bmpFile); // Start of image data
#ifdef __DEBUG
  #ifdef __SAMD21G18A__
      SerialUSB.print(F("Image Offset: ")); SerialUSB.println(bmpImageoffset, DEC);
      SerialUSB.print(F("Header size: ")); SerialUSB.println(read32(bmpFile));
  #else
      Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
      Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
  #endif
#else
    (void)read32(bmpFile);
#endif
	  bmpWidth  = read32(bmpFile);
	  bmpHeight = read32(bmpFile);
    
	  if(read16(bmpFile) == 1) { // # planes -- must be '1'
	    bmpDepth = read16(bmpFile); // bits per pixel
#ifdef __DEBUG
  #ifdef __SAMD21G18A__
        SerialUSB.print(F("Bit Depth: ")); SerialUSB.println(bmpDepth);
  #else
        Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
  #endif
#endif

	    if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed
		    goodBmp = true; // Supported BMP format -- proceed!
#ifdef __DEBUG
  #ifdef __SAMD21G18A__
		    SerialUSB.print(F("Image size: "));
        SerialUSB.print(bmpWidth);
		    SerialUSB.print('x');
		    SerialUSB.println(bmpHeight);
  #else
		    Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
		    Serial.print('x');
		    Serial.println(bmpHeight);
  #endif
#endif
 
        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;
 
        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip 	 = false;
        }
 
        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= _width)  w = _width  - x;
        if((y+h-1) >= _height) h = _height - y;
 
        // Set TFT address window to clipped image bounds
#ifndef __SAMD21G18A__
        SPCR = 0;
#endif
        setAddrWindow(x, y, x+w-1, y+h-1);
 
		    for (row=0; row<h; row++) { 
       
		      if(flip) pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
		      else pos = bmpImageoffset + row * rowSize;
          
#ifndef __SAMD21G18A__
		      SPCR = spi_save;
#endif
		      if(bmpFile.position() != pos) { // Need seek?
			      bmpFile.seek(pos);
			      buffidx = sizeof(sdbuffer); // Force buffer reload
		      }
 
		      for (col=0; col<w; col++) { // For each column...
			      // Time to read more pixel data?
			      if (buffidx >= sizeof(sdbuffer)) { // Indeed
			        // Push LCD buffer to the display first
			        if(lcdidx > 0) {
#ifndef __SAMD21G18A__
				        SPCR	= 0;
#endif
				        pushColors(lcdbuffer, lcdidx, first);
				        lcdidx = 0;
				        first	= false;
			        }
#ifndef __SAMD21G18A__
			        SPCR = spi_save;
#endif
			        bmpFile.read(sdbuffer, sizeof(sdbuffer));
			        buffidx = 0; // Set index to beginning
			      }
 
            // Convert pixel from BMP to TFT format
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            lcdbuffer[lcdidx++] = color565(r,g,b);
		      } // end pixel
		    } // end scanline
		    // Write any remaining data to LCD
		    if(lcdidx > 0) {
#ifndef __SAMD21G18A__
		      SPCR = 0;
#endif
		      pushColors(lcdbuffer, lcdidx, first);
		    }
#ifdef __DEBUG
  #ifdef __SAMD21G18A__
        SerialUSB.print(F("Loaded in "));
        SerialUSB.print(millis() - startTime);
        SerialUSB.println(" ms");
  #else
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
  #endif
#endif
	    } // end goodBmp
	  }
  }
 
  bmpFile.close();
#ifdef __DEBUG
  #ifdef __SAMD21G18A__
  if(!goodBmp) SerialUSB.println("BMP format not recognized.");
  #else
  if(!goodBmp) Serial.println("BMP format not recognized.");
  #endif
#endif
}
 
//
uint16_t read16(File f)
{
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}
 
uint32_t read32(File f)
{
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

//
void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  writeHLine(x, y, w, color);
  writeHLine(x + h - 1, y, w, color);
  writeVLine(x, y, h, color);
  writeVLine(x, y + w - 1, h, color);
}

//
void writeHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
  
  setAddrWindow(0, 0, _width - 1, _height - 1);
  for(int16_t i = 0; i < w; i++)
  {
    if ((y + i) < _height) drawPixel(x, y + i, color);
  }
}

//
void writeVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  setAddrWindow(0, 0, _width - 1, _height - 1);
  for(int16_t i = 0; i < h; i++)
  {
    if ((x + i) < _width) drawPixel(x + i, y, color);
  }
}

//
void drawRectWide(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  writeHLine(x, y, w, color);
  writeHLine(x + 1, y, w, color);
  writeHLine(x + h - 1, y, w, color);
  writeHLine(x + h - 2, y, w, color);
  writeVLine(x, y, h, color);
  writeVLine(x, y + 1, h, color);
  writeVLine(x, y + w - 1, h, color);
  writeVLine(x, y + w - 2, h, color);
}


void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{    
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  setAddrWindow(0, 0, _width - 1, _height - 1);
  
  drawPixel(x0, y0 + r, color);
  drawPixel(x0, y0 - r, color);
  drawPixel(x0 + r, y0, color);
  drawPixel(x0 - r, y0, color);

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

//
void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
  uint8_t corners = 3;
  int16_t delta = 0;
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;
  int16_t px = x;
  int16_t py = y;
  
  setAddrWindow(0, 0, _width - 1, _height - 1);
  writeHLine(x0, y0 - r, 2 * r + 1, color);
  
  delta++; // Avoid some +1's in the loop

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    if (x < (y + 1)) {
      if (corners & 1)
        writeHLine(x0 + x, y0 - y, 2 * y + delta, color);
      if (corners & 2)
        writeHLine(x0 - x, y0 - y, 2 * y + delta, color);
    }
    if (y != py) {
      if (corners & 1)
        writeHLine(x0 + py, y0 - px, 2 * px + delta, color);
      if (corners & 2)
        writeHLine(x0 - py, y0 - px, 2 * px + delta, color);
      py = y;
    }
    px = x;
  }
}


void drawCross(void) 
{
  uint16_t x, y;
  x = 60, y = _height / 2;
  while(x++ < (_width - 60)) drawPixel(x, y, 0xffff);
  x = _width / 2, y = 80;
  while(y++ < (_height - 80)) drawPixel(x, y, 0xffff);
}


//
void print(uint8_t ch)
{
  if (ch == '\n') {              // Newline?
    cursor_x = 0;               // Reset x to zero,
    cursor_y += textsize_y * 8; // advance y one line
  } else if (ch != '\r') {       // Ignore carriage returns
    if (wrap && ((cursor_x + textsize_x * 6) > _width)) { // Off right?
      cursor_x = 0;                                       // Reset x to zero,
      cursor_y += textsize_y * 8; // advance y one line
    }
    drawChar(cursor_x, cursor_y, ch, textcolor, textbgcolor, textsize_x, textsize_y);
    cursor_x += textsize_x * 6; // Advance x one char
  }
}

//
void print(const char * ch)
{
  const char * ptrCh = ch;
  while(*ptrCh != '\0') {
    print(*ptrCh);
    ptrCh++;
  }
}

//
void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y)
{
  const GFXfont *gfxFont = &font;

  c -= (uint8_t)pgm_read_byte(&gfxFont->first);
  GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c);
  uint8_t *bitmap = pgm_read_bitmap_ptr(gfxFont);

  uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
  uint8_t w = pgm_read_byte(&glyph->width), h = pgm_read_byte(&glyph->height);
  int8_t xo = pgm_read_byte(&glyph->xOffset),
         yo = pgm_read_byte(&glyph->yOffset);
  uint8_t xx, yy, bits = 0, bit = 0;
  int16_t xo16 = 0, yo16 = 0;

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
          drawPixel(x + xo + xx, y + yo + yy, color);
          // drawPixel(_width - x + xo - xx, y + yo + yy, color);
        } else {
          fillRect(x + (xo16 + xx) * size_x, y + (yo16 + yy) * size_y, size_x, size_y, color);
          // fillRect(_width - x + (xo16 - xx) * size_x, y + (yo16 + yy) * size_y, size_x, size_y, color);
        }
      }
      bits <<= 1;
    }
  }
}

//
void setCursor(int16_t x, int16_t y)
{
  cursor_x = x;
  cursor_y = y;
}


#endif /* _ILI9488_H_ */
