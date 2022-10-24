
// Arduino Nano 168p ST7735S 0,96 inch 80х160

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h> // Hardware-specific library

#define TFT_RST  9    // we use the seesaw for resetting to save a pin
#define TFT_CS   10
#define TFT_DC   8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

//uint16_t color = 0; // RGB-5-6-5

uint16_t white = 0b0000000000000000;
uint16_t green = 0b1111100000011111;
uint16_t red = 0b1111111111100000;
uint16_t blue = 0b0000011111111111;
uint16_t black = 0b1111111111111111;
  
void image(uint16_t color) {
  tft.fillRect(10, 10, 60, 50, color);
  tft.fillTriangle(10, 65, 70, 65, 40, 115, color);
  tft.fillCircle(40, 140, 15, color);
}

void setup() {
  tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display
//  tft.setRotation(1);
  tft.fillScreen(black);
    
//  delay(1000);  
//  tft.fillScreen(~ST77XX_RED); // blue
//  delay(1000);
//  tft.fillScreen(~ST77XX_GREEN); // green
//  delay(1000);
//  tft.fillScreen(~ST77XX_BLUE); // red
//  delay(1000);
//  tft.fillScreen(~ST77XX_BLACK); // black

}

void loop() {  
  image(red);
  delay(1000); 
  
  image(green);
  delay(1000); 
  
  image(blue);
  delay(1000); 
  
//  tft.fillScreen(0x0000);
//  color += 5;  
//  image(color);
//  delay(100);
    
}
