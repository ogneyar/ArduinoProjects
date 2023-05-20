
// Mega, Uno

#define __DEBUG 1

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include <SD.h>
#include <Adafruit_GFX.h> // Hardware-specific library

#include <MCUFRIEND_kbv.h>

//----------------------------------------|
// TFT Breakout  -- Arduino UNO / Mega2560 / OPEN-SMART UNO Black
// GND              -- GND
// 3V3               -- 3.3V
// CS                 -- A3
// RS                 -- A2
// WR                -- A1
// RD                 -- A0
// RST                -- RESET
// LED                -- GND
// DB0                -- 8
// DB1                -- 9
// DB2                -- 10
// DB3                -- 11
// DB4                -- 4
// DB5                -- 13
// DB6                -- 6
// DB7                -- 7
MCUFRIEND_kbv tft;
#define SD_CS 5

File root;
char namebuf[32] = "girl.bmp";
int pathlen;
uint8_t         spi_save;

void setup()
{
#ifdef __DEBUG
    Serial.begin(9600);
    Serial.print("Show BMP files on TFT with ID:0x");
#endif      
        
    tft.begin(0x9320); // SPFD5408 can use ILI9320 driver
    tft.fillScreen(0xf0f0);
    
    bool good = SD.begin(SD_CS);
    if (!good) {
#ifdef __DEBUG
        Serial.print(F("cannot start SD"));
#endif      
        return;
    }
 }
 
 void loop()
 {
   // 320 на 240
   tft.setRotation(4); // 1 - горизонт, 2 - обзор слева, 3 - кверх ногами, 4 - обзор справа

   bmpDraw("01.bmp", 0, 0);//
   delay(3000);
  //  tft.fillScreen(0);
  
   bmpDraw("02.bmp", 0, 0);
   delay(3000);
  //  tft.fillScreen(0);
   
   bmpDraw("03.bmp", 0, 0);
   delay(3000);
  //  tft.fillScreen(0);
 }
 
 
#define BUFFPIXEL 20
 
void bmpDraw(char *filename, int x, int y) {
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
 
   if((x >= tft.width()) || (y >= tft.height())) return;

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
		 if((x+w-1) >= tft.width())  w = tft.width()  - x;
		 if((y+h-1) >= tft.height()) h = tft.height() - y;
 
		 // Set TFT address window to clipped image bounds
		 SPCR = 0;
		 tft.setAddrWindow(x, y, x+w-1, y+h-1);
 
		 for (row=0; row<h; row++) { // For each scanline...
		   // Seek to start of scan line.  It might seem labor-
		   // intensive to be doing this on every line, but this
		   // method covers a lot of gritty details like cropping
		   // and scanline padding.  Also, the seek only takes
		   // place if the file position actually needs to change
		   // (avoids a lot of cluster math in SD library).
		   if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
			 pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
		   else 	// Bitmap is stored top-to-bottom
			 pos = bmpImageoffset + row * rowSize;
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
				 tft.pushColors(lcdbuffer, lcdidx, first);
				 lcdidx = 0;
				 first	= false;
			   }
			   SPCR = spi_save;
			   bmpFile.read(sdbuffer, sizeof(sdbuffer));
			   buffidx = 0; // Set index to beginning
			 }
 
			 // Convert pixel from BMP to TFT format
			 b = sdbuffer[buffidx++];
			 g = sdbuffer[buffidx++];
			 r = sdbuffer[buffidx++];
			 lcdbuffer[lcdidx++] = tft.color565(r,g,b);
		   } // end pixel
		 } // end scanline
		 // Write any remaining data to LCD
		 if(lcdidx > 0) {
		   SPCR = 0;
		   tft.pushColors(lcdbuffer, lcdidx, first);
		 }
#ifdef __DEBUG
		 Serial.print(F("Loaded in "));
		 Serial.print(millis() - startTime);
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
 
 // These read 16- and 32-bit types from the SD card file.
 // BMP data is stored little-endian, Arduino is little-endian too.
 // May need to reverse subscript order if porting elsewhere.
 
 uint16_t read16(File f) {
   uint16_t result;
   ((uint8_t *)&result)[0] = f.read(); // LSB
   ((uint8_t *)&result)[1] = f.read(); // MSB
   return result;
 }
 
 uint32_t read32(File f) {
   uint32_t result;
   ((uint8_t *)&result)[0] = f.read(); // LSB
   ((uint8_t *)&result)[1] = f.read();
   ((uint8_t *)&result)[2] = f.read();
   ((uint8_t *)&result)[3] = f.read(); // MSB
   return result;
 }
 