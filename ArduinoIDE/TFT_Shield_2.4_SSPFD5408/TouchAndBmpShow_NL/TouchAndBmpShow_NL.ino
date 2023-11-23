
// Uno

// #define __DEBUG 1
// #define __SAMD21G18A__


#include "defines.h"
#include "tft.h"


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
int16_t PENRADIUS = 3;
uint16_t identifier, oldcolor, currentcolor;
uint8_t Orientation = 0;    //PORTRAIT

// char bmp[20][7] = {
//   "01.bmp", "02.bmp", "03.bmp", "04.bmp", "05.bmp", "06.bmp", "07.bmp", "08.bmp", "09.bmp", "10.bmp", 
//   "11.bmp", "12.bmp", "13.bmp", "14.bmp", "15.bmp", "16.bmp", "17.bmp", "18.bmp", "19.bmp", "20.bmp"
// };


void show_tft(void);
void buttonClearScreen(void);

//
#define scan() { \
  uint8_t exit = 0; \
  uint16_t pause = 1500; \
  while(pause-- > 0) { \
    tp = ts.getPoint(); \
    pinMode(XM, OUTPUT); \
    pinMode(YP, OUTPUT); \
    pinMode(XP, OUTPUT); \
    pinMode(YM, OUTPUT); \
    if (tp.x > 450 && tp.x < 690  && tp.y > 450 && tp.y < 570) { \
      exit = 1; \
      break; \
    } \
    delay(1); \
  } \
  if (exit) break; \  
} 



//
void setup(void)
{
#ifdef __DEBUG
  Serial.begin(9600);
  Serial.println("Touch Screen And Show BMP files on TFT");
#endif   
  //
  begin(); // SPFD5408 can use ILI9320 driver (0x9320)
  
  // начальное меню
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
        drawRectWide(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, WHITE);
      } 
      else if (xpos < BOXSIZE * 2) 
      {
        currentcolor = BLUE;
        drawRectWide(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, WHITE);
      } 
      else if (xpos < BOXSIZE * 3) 
      {
        currentcolor = CYAN;
        drawRectWide(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, WHITE);        
      } 
      else if (xpos < BOXSIZE * 4) 
      {
        currentcolor = GREEN;
        drawRectWide(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, WHITE);
      } 
      else if (xpos < BOXSIZE * 5) 
      {
        currentcolor = YELLOW;
        drawRectWide(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, WHITE);   
      } 
      else if (xpos < BOXSIZE * 6) 
      {
        currentcolor = ORANGE;
        drawRectWide(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, WHITE);
      }
      else if (xpos < BOXSIZE * 7) 
      {
        currentcolor = RED;
        drawRectWide(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
      }
      else if (xpos < BOXSIZE * 8) 
      {
        currentcolor = WHITE;
        drawRectWide(0, 0, BOXSIZE, BOXSIZE, BLACK);
      }
      
      if (oldcolor != currentcolor) { //rub out the previous white border
        if (oldcolor == WHITE) fillRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
        if (oldcolor == RED) fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, RED);
        if (oldcolor == ORANGE) fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ORANGE);
        if (oldcolor == YELLOW) fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, YELLOW);
        if (oldcolor == GREEN) fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, GREEN);
        if (oldcolor == CYAN) fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, CYAN);
        if (oldcolor == BLUE) fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, BLUE);
        if (oldcolor == MAGENTA) fillRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, MAGENTA);
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
      // начальное меню
      show_tft();
    }
    // 
    if ((ypos > _height - 40) && (xpos) < 60) { 
//------------------------------------------------------------------------- begin SD card      
      bool good = SD.begin(8000000, SD_CS);
//-------------------------------------------------------------------------
      if (!good) {
#ifdef __DEBUG
        Serial.print(F("cannot start SD"));
#endif      
        return;
      }
      spi_save = SPCR;

      uint8_t del = 0;
      SPCR = 0;
      // fill(0xf800);
      
      while (1) { 
      
        for (byte i = 1; i <= 40; i++) {
          String bmpStr = "";
          if (i < 10) bmpStr = "0";
          bmpStr += String(i) + ".bmp";

          char bmpChar[13]; // 8 символов имя, 1 точка, 3 символа разширения и 1 символ конца строки
          byte j = 0;
          do {
            bmpChar[j] = bmpStr[j];
            j++;
          }while(bmpStr[j-1] != '\0');

          if (SD.exists(bmpChar)) { bmpDraw(bmpChar, 0, 0); scan(); }
        }

        // for (byte i = 0; i < sizeof(bmp); i++) {
        //   if (SD.exists(bmp[i])) { bmpDraw(bmp[i], 0, 0); scan(); }
        // }

        // Ниже это типа индийский код (:
        // if (SD.exists("01.bmp")) { bmpDraw("01.bmp", 0, 0); scan(); }
        // if (SD.exists("02.bmp")) { bmpDraw("02.bmp", 0, 0); scan(); }
        // if (SD.exists("03.bmp")) { bmpDraw("03.bmp", 0, 0); scan(); }
        // if (SD.exists("04.bmp")) { bmpDraw("04.bmp", 0, 0); scan(); }
        // if (SD.exists("05.bmp")) { bmpDraw("05.bmp", 0, 0); scan(); }
        // if (SD.exists("06.bmp")) { bmpDraw("06.bmp", 0, 0); scan(); }
        // if (SD.exists("07.bmp")) { bmpDraw("07.bmp", 0, 0); scan(); }
        // if (SD.exists("08.bmp")) { bmpDraw("08.bmp", 0, 0); scan(); }
        // if (SD.exists("09.bmp")) { bmpDraw("09.bmp", 0, 0); scan(); }
        // if (SD.exists("10.bmp")) { bmpDraw("10.bmp", 0, 0); scan(); }
      }
      
      // начальное меню
      show_tft();
    }
  }
}

//
void show_tft(void)
{
  
  fillScreen(BLACK);
  drawRectWide(90, 160, 40, 60, WHITE);
  
  setCursor(100, 185);
  print("Run");
  
  while (1) {    
    tp = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
    if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE) continue;
    if (tp.x > 450 && tp.x < 690  && tp.y > 450 && tp.y < 570) break;
  }
  
  BOXSIZE = _width / 8;
  fillScreen(BLACK);  
  // блок кнопок (выход, очистка экрана, ...)
  buttons();
  
  fillRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
  fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, RED);
  fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ORANGE);
  fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, YELLOW);
  fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, GREEN);
  fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, CYAN);
  fillRect(BOXSIZE * 6, 0, BOXSIZE, BOXSIZE, BLUE);
  fillRect(BOXSIZE * 7, 0, BOXSIZE, BOXSIZE, MAGENTA);

  drawRectWide(0, 0, BOXSIZE, BOXSIZE, BLACK);
  currentcolor = WHITE;
  // delay(1000);
}

//
void buttons(void)
{  
  drawRectWide(0, 280, 40, 60, WHITE);  
  setCursor(190, 305);
  print("End");
  drawRectWide(60, 290, 30, 120, WHITE);
  setCursor(85, 310);
  print("CLEAR");
  drawRectWide(180, 280, 40, 60, WHITE);
  setCursor(10, 305);
  print("Bmp");
}



