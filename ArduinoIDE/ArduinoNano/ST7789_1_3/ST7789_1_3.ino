
// Nano

/*
 ST7789 240x240 IPS without CS pin

 #01 GND -> GND
 #02 VCC -> VCC (3.3V only!)
 #03 SCL -> D13/SCK
 #04 SDA -> D11/MOSI
 #05 RES -> D8 or any digital
 #06 DC  -> D9 or any digital
 #07 BLK -> NC
*/

#define TFT_DC    9
#define TFT_RST   8 
// если есть CS
#define TFT_CS 10

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>

Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);


void setup(void) 
{
  pinMode(TFT_CS,HIGH);
  digitalWrite(TFT_CS,LOW);
  lcd.init(240, 240);
  lcd.fillScreen(BLACK);
  delay(1000);
  lcd.fillScreen(WHITE);
  delay(1000);
  lcd.fillScreen(YELLOW);
  delay(1000);
  lcd.fillScreen(GREEN);
}

void loop(){}
