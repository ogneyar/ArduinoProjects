
// Wemos D1 mini
// SSD1306_128X32

/*
test1 61 Fps
test2 63 Fps
test3 40 Fps
test4 50.1 Fps
test5 65 Fps
*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED


typedef u8g2_uint_t u8g_uint_t;



#define SECONDS 2 // ESP wdt больше поставить не позволяет
uint8_t flip_color = 0;
uint8_t draw_color = 1;

void draw_set_screen(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g2.setColorIndex(flip_color);
  u8g2.drawBox( 0, 0, u8g2.getWidth(), u8g2.getHeight() );
}

void draw_clip_test(void) {
  u8g_uint_t i, j, k;
  char buf[3] = "AB";
  k = 0;
  u8g2.setColorIndex(draw_color);
  u8g2.setFont(u8g2_font_6x10_tf);
  
  for( i = 0; i  < 6; i++ ) {
    for( j = 1; j  < 8; j++ ) {
      u8g2.drawHLine(i-3, k, j);
      u8g2.drawHLine(i-3+10, k, j);
      
      u8g2.drawVLine(k+20, i-3, j);
      u8g2.drawVLine(k+20, i-3+10, j);
      
      k++;
    }
  }
  u8g2.setFontDirection(0);
  u8g2.drawStr(0-3, 50, buf);
  u8g2.setFontDirection(2);
  u8g2.drawStr(0+3, 50, buf);
  
  u8g2.setFontDirection(0);
  u8g2.drawStr(u8g2.getWidth()-3, 40, buf);
  u8g2.setFontDirection(2);
  u8g2.drawStr(u8g2.getWidth()+3, 40, buf);

  u8g2.setFontDirection(1);
  u8g2.drawStr(u8g2.getWidth()-10, 0-3, buf);
  u8g2.setFontDirection(3);
  u8g2.drawStr(u8g2.getWidth()-10, 3, buf);

  u8g2.setFontDirection(1);
  u8g2.drawStr(u8g2.getWidth()-20, u8g2.getHeight()-3, buf);
  u8g2.setFontDirection(3);
  u8g2.drawStr(u8g2.getWidth()-20, u8g2.getHeight()+3, buf);

  u8g2.setFontDirection(0);

}

void draw_char(void) {
  char buf[2] = "@";
  u8g_uint_t i, j;
  // graphic commands to redraw the complete screen should be placed here  
  u8g2.setColorIndex(draw_color);
  u8g2.setFont(u8g2_font_6x10_tf);
  j = 8;
  for(;;) {
    i = 0;
    for(;;) {
      u8g2.drawStr( i, j, buf);
      i += 8;
      if ( i > u8g2.getWidth() )
        break;
    }
    j += 8;
    if ( j > u8g2.getHeight() )
      break;
  }
  
}

void draw_pixel(void) {
  u8g_uint_t x, y, w2, h2;
  u8g2.setColorIndex(draw_color);
  w2 = u8g2.getWidth();
  h2 = u8g2.getHeight();
  w2 /= 2;
  h2 /= 2;
  for( y = 0; y < h2; y++ ) {
    for( x = 0; x < w2; x++ ) {
      if ( (x + y) & 1 ) {
        u8g2.drawPixel(x,y);
        u8g2.drawPixel(x,y+h2);
        u8g2.drawPixel(x+w2,y);
        u8g2.drawPixel(x+w2,y+h2);
      }
    }
  }
}

void draw_line(void) {
  u8g2.setColorIndex(draw_color);
  u8g2.drawLine(0,0, u8g2.getWidth()-1, u8g2.getHeight()-1);
}

// returns unadjusted FPS
uint16_t execute_with_fps(void (*draw_fn)(void), byte seconds) {
  uint16_t FPS10 = 0;
  uint32_t time;
  
  time = millis() + seconds*1000;
  
  // picture loop
  do {
    u8g2.clearBuffer();
    draw_fn();
    u8g2.sendBuffer();
    FPS10++;
    flip_color = flip_color ^ 1;
  } while( millis() < time );
  return FPS10;  
}

const char *convert_FPS(uint16_t fps, byte seconds) {
  static char buf[6];
  strcpy(buf, u8g2_u8toa( (uint8_t)(fps/seconds), 3));
  buf[3] =  '.';
  buf[4] = (fps % seconds) + '0';
  buf[5] = '\0';
  return buf;
}

void show_result(const char *s, uint16_t fps, byte seconds) {
  // assign default color value
  u8g2.setColorIndex(draw_color);
  u8g2.setFont(u8g2_font_8x13B_tf);
  u8g2.clearBuffer();
  u8g2.drawStr(0,12, s);
  u8g2.drawStr(0,24, convert_FPS(fps, seconds));
  u8g2.sendBuffer();
}

void setup(void) {
  u8g2.begin();
  draw_color = 1;         // pixel on
}

void loop(void) {
  uint16_t fps;
  fps = execute_with_fps(draw_clip_test, SECONDS);
  show_result("draw clip test", fps, SECONDS);
  delay(3000);
  fps = execute_with_fps(draw_set_screen, SECONDS);
  show_result("clear screen", fps, SECONDS);
  delay(3000);
  fps = execute_with_fps(draw_char, SECONDS);
  show_result("draw @", fps, SECONDS);
  delay(3000);  
  fps = execute_with_fps(draw_pixel, SECONDS);
  show_result("draw pixel", fps, SECONDS);
  delay(3000);
  fps = execute_with_fps(draw_line, 1);
  show_result("draw line", fps, 1);
  delay(3000);
}
