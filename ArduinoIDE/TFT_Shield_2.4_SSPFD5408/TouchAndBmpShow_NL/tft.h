
#ifndef _TFT_H_
#define _TFT_H_


#include <TouchScreen.h>
#include <SPI.h>
#include <SD.h>

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


//
void begin(void)
{  
  _width = WIDTH; // 240;
  _height = HEIGHT; // 320;
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
  digitalWrite(SD_CS, LOW);
  delay(200);
  digitalWrite(SD_CS, HIGH);
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
  CD_DATA;
  while (h-- > 0) {
    end = w;
#if USING_16BIT_BUS
#define STROBE_16BIT {WR_ACTIVE; WR_IDLE;}
        write16(color);        //we could just do the strobe 
        lo = end & 7;
        hi = end >> 3;
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
      write16(color);
    } while (--end != 0);
#endif
  }
  CS_IDLE;
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


#define BUFFPIXEL 80
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
  uint32_t pos = 0, startTime = 0;
  uint32_t startTimeRead = 0, endTimeRead = 0;
  uint8_t	lcdidx = 0;
  boolean	first = true;
 
  if((x >= _width) || (y >= _height)) return;

#ifdef __DEBUG
  Serial.println();
  Serial.print("Loading image '");
  Serial.print(filename);
  Serial.println('\'');
#endif
  // Open requested file on SD card
  SPCR = spi_save;
  if ((bmpFile = SD.open(filename)) == NULL) {
#ifdef __DEBUG
	  Serial.print("File not found");
#endif
	  return;
  }
 
  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature

#ifdef __DEBUG
	  Serial.print(F("File size: ")); Serial.println(read32(bmpFile));
#else
    (void)read32(bmpFile);
#endif
	  (void)read32(bmpFile); // Read & ignore creator bytes
	  bmpImageoffset = read32(bmpFile); // Start of image data
#ifdef __DEBUG
	  Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
	  // Read DIB header
	  Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
#else
    (void)read32(bmpFile);
#endif
	  bmpWidth  = read32(bmpFile);
	  bmpHeight = read32(bmpFile);
    
	  if(read16(bmpFile) == 1) { // # planes -- must be '1'
	    bmpDepth = read16(bmpFile); // bits per pixel
#ifdef __DEBUG
	    Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
#endif

	    if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed
		    goodBmp = true; // Supported BMP format -- proceed!
#ifdef __DEBUG
		    Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
		    Serial.print('x');
		    Serial.println(bmpHeight);
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
        SPCR = 0;
        setAddrWindow(x, y, x+w-1, y+h-1);

        // начало прорисовки изображения
        startTime = millis();

		    for (row=0; row<h; row++) { 
       
		      if(flip) pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
		      else pos = bmpImageoffset + row * rowSize;
          
		      SPCR = spi_save;
		      if(bmpFile.position() != pos) { // Need seek?
			      bmpFile.seek(pos);
			      buffidx = sizeof(sdbuffer); // Force buffer reload
		      }
 
		      for (col=0; col<w; col++) { // For each column...
			      // Time to read more pixel data?
			      if (buffidx >= sizeof(sdbuffer)) { // Indeed
			        // Push LCD buffer to the display first
			        if(lcdidx > 0) {
				        SPCR	= 0;
				        pushColors(lcdbuffer, lcdidx, first);
				        lcdidx = 0;
				        first	= false;
			        }
			        SPCR = spi_save;

              if ( ! startTimeRead ) startTimeRead =  millis();

			        bmpFile.read(sdbuffer, sizeof(sdbuffer));
              
              if ( ! endTimeRead ) endTimeRead =  millis();

			        buffidx = 0; // Set index to beginning
			      }
 
            // Convert pixel from BMP to TFT format
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            lcdbuffer[lcdidx++] = color565(r,g,b);

            // SPCR	= 0;
            // CS_ACTIVE;
            // if (first) {
            //   WriteCmd(_MW);
            // }  
            // CD_DATA;
            // write16(color565(r,g,b));
            // CS_IDLE;
				    // first	= false;


		      } // end pixel
		    } // end scanline
		    // вывод оставшихся данных на экран
		    if(lcdidx > 0) {
		      SPCR = 0;
		      pushColors(lcdbuffer, lcdidx, first);
		    }
#ifdef __DEBUG
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
        
        Serial.print(F("Buffer length: "));
        Serial.println(sizeof(sdbuffer));
        Serial.print(F("Read time buffer in "));
        Serial.print(endTimeRead - startTimeRead);
        Serial.println(" ms");
#endif
	    } // end goodBmp
	  }
  }
 
  bmpFile.close();
#ifdef __DEBUG
  if(!goodBmp) Serial.println("BMP format not recognized.");
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
void print(const char *ch)
{
  uint8_t * ptrCh = ch;
  while(*ptrCh != '\0') {
    print(*ptrCh);
    ptrCh++;
  }
}

//
void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y)
{
  GFXfont *gfxFont = &font;

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
          // drawPixel(x + xo + xx, y + yo + yy, color);
          drawPixel(_width - x + xo - xx, y + yo + yy, color);
        } else {
          // fillRect(x + (xo16 + xx) * size_x, y + (yo16 + yy) * size_y, size_x, size_y, color);
          fillRect(_width - x + (xo16 - xx) * size_x, y + (yo16 + yy) * size_y, size_x, size_y, color);
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


#endif /* _TFT_H_ */ 
