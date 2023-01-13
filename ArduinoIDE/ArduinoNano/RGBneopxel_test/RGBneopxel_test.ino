
// Nano

#include <Adafruit_NeoPixel.h>

#define LED_PIXEL_PIN    3 // PD3
#define LED_COUNT        1 // 30


Adafruit_NeoPixel strip(LED_COUNT, LED_PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int           stripInterval = 1000;
unsigned long stripPrevious = 0;

uint8_t color = 1;


void setup() {
  strip.begin(); 
  //strip.show();
  strip.setBrightness(50); // яркость общая
}


// loop() function -- runs repeatedly as long as board is on ---------------
void loop() {
  unsigned long currentMillis = millis(); 


  if((currentMillis - stripPrevious) >= stripInterval) {  
      stripPrevious = currentMillis;
      
      switch (color) {      
        case 3:
          strip.setPixelColor(0, strip.Color(0, 0, 127)); // Blue  (127 - яркость диода)
          break;
        case 2:
          strip.setPixelColor(0, strip.Color(0, 127, 0)); // Green
          break;
        case 1:
          strip.setPixelColor(0, strip.Color(127, 0, 0)); // Red
          break;        
        default:
          strip.setPixelColor(0, strip.Color(127, 127, 127)); // White
          break;
      }
      
      strip.show();
      
      color++;
      if (color > 4) color = 1;
  }
}

