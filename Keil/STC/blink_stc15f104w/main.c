
// RX - P3.0
// TX - P3.1

#include <STC15F2K60S2.H>

#include "main.h"


void delay(unsigned int);

#define 		set_LED1		P33=1
#define 		clr_LED1		P33=0


void main (void) 
{
	P01_PushPull_Mode;

  while(1)
  {
		set_LED1;
		delay(1000);
		clr_LED1;
		delay(1000);
  }
	

}


void delay(unsigned int value) {
	unsigned long iter;
	unsigned long her = 1;
	for (iter = 0; iter < (unsigned long)(value<<5); iter++) her *= value;
	//asm("nop");
}


