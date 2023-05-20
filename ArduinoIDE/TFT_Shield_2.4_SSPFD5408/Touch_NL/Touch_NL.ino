
// 

#include "defines.h"
#include "tft.h"

#include <TouchScreen.h>

uint8_t YP = A1;  // must be an analog pin, use "An" notation! (WR)
uint8_t XM = A2;  // must be an analog pin, use "An" notation! (RS)
uint8_t YM = 7;   // can be a digital pin (D7)
uint8_t XP = 6;   // can be a digital pin (D6)
uint8_t SwapXY = 0;

uint16_t TS_LEFT = 940;
uint16_t TS_RT  = 185;
uint16_t TS_TOP = 950;
uint16_t TS_BOT = 170;
char *name = "Unknown controller";

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 500);
TSPoint tp;

#define MINPRESSURE 20
#define MAXPRESSURE 1000

#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}

int16_t BOXSIZE;
int16_t PENRADIUS = 5;
uint16_t identifier, oldcolor, currentcolor;
uint8_t Orientation = 0;    //PORTRAIT

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void show_tft(void);
void buttonClearScreen(void);


//
void setup(void)
{
  Serial.begin(9600);
  begin(); // SPFD5408 can use ILI9320 driver (0x9320)
  //
  show_tft();
}

void loop()
{
  uint16_t xpos, ypos;  //screen coordinates
  tp = ts.getPoint();   //tp.x, tp.y are ADC values

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(XP, OUTPUT);
  pinMode(YM, OUTPUT);

  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
    
    xpos = map(tp.x, TS_LEFT, TS_RT, 0, _width);  // 240
    ypos = map(tp.y, TS_TOP, TS_BOT, 0, _height);

    if (ypos < BOXSIZE) {               //draw white border on selected color box
      oldcolor = currentcolor;

      if (xpos < BOXSIZE) 
      {
        currentcolor = MAGENTA;
        drawRectWide(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, WHITE);
      } 
      else if (xpos < BOXSIZE * 2) 
      {
        currentcolor = BLUE;
        drawRectWide(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, WHITE);
      } 
      else if (xpos < BOXSIZE * 3) 
      {
        currentcolor = CYAN;
        drawRectWide(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, WHITE);          
      } 
      else if (xpos < BOXSIZE * 4) 
      {
        currentcolor = GREEN;
        drawRectWide(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, WHITE);
      } 
      else if (xpos < BOXSIZE * 5) 
      {
        currentcolor = YELLOW;
        drawRectWide(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
      } 
      else if (xpos < BOXSIZE * 6) 
      {
        currentcolor = RED;
        drawRectWide(0, 0, BOXSIZE, BOXSIZE, WHITE);
      }

      if (oldcolor != currentcolor) { //rub out the previous white border
        if (oldcolor == RED) fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
        if (oldcolor == YELLOW) fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
        if (oldcolor == GREEN) fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
        if (oldcolor == CYAN) fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
        if (oldcolor == BLUE) fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
        if (oldcolor == MAGENTA) fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
      }
    }
    // рисование на холсте
    if (((ypos - PENRADIUS) > BOXSIZE) && ((ypos + PENRADIUS) < _height)) {
      if (ypos < (_height - 40)) {
        fillCircle(_width - xpos, ypos, PENRADIUS, currentcolor);
      }           
    }
    // очистка части экрана
    if ((ypos > _height - 30) && ((_width - xpos) > 60) && (xpos > 60)) {
      fillRect(0, BOXSIZE, _width, _height - BOXSIZE, BLACK);
      buttons(); // прорисовка копок
    }
    // 
    if ((ypos > _height - 40) && ((_width - xpos) < 60)) {
      show_tft();
    }
  }
}

//
void show_tft(void)
{
  fillScreen(BLACK);
  drawRectWide(90, 160, 40, 60, WHITE);
  while (1) {
    tp = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
    if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
    if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) break;
  }
  
  BOXSIZE = _width / 6;
  fillScreen(BLACK);  
  // блок кнопок (выход, очистка экрана, ...)
  buttons();
  
  fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
  fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
  fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
  fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);

  drawRectWide(0, 0, BOXSIZE, BOXSIZE, WHITE);
  currentcolor = RED;
  // delay(1000);
}

//
void buttons(void)
{  
  drawRectWide(0, 280, 40, 60, WHITE);
  drawRectWide(60, 290, 30, 120, WHITE);
  drawRectWide(180, 280, 40, 60, WHITE);
}

