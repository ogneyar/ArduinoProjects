
// Nano, LGT8F328P

#include "spi.h"
#include "defines.h"
#include "st7735.h"


void setup(void) {
  SPI_Master_Init();
  // st7735_init();
  st7735_init_minimal();
  st7735_clear();
  
  // НЕ RGB А RBG
  
  delay(1000);
  st7735_fill(_WHITE, 5, 5, 10, 10);
  
  delay(1000);
  st7735_fill(_RED, 10, 10, 20, 20);
  
  delay(1000);
  st7735_fill(_GREEN, 15, 15, 30, 30);
  
  delay(1000);
  st7735_fill(_BLUE, 20, 20, 40, 40);
  
  delay(1000);
  st7735_fill(_RED_BLUE, 25, 25, 50, 50);
  
  delay(1000);
  st7735_fill(_BLUE_GREEN, 30, 30, 60, 60);
  
  delay(1000);
  st7735_fill(_RED_GREEN, 35, 35, 70, 70);
  
}

void loop() {}

