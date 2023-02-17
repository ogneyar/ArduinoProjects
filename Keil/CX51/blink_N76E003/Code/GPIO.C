
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"


void main (void) 
{
	//Set_All_GPIO_Quasi_Mode;	// Define in Function_define.h
	//P0M1=0;P0M2=0;P1M1=0;P1M2=0;P3M1=0;P3M2=0;
	// для N76E003 чёрного цвета	
	P1M2=0;
	// для N76E003 синего  цвета
	P1M1=0;
	  
  while(1)
  {
		// P12 - LED на N76E003 синего  цвета при подаче 1 светится
		// P12 - LED на N76E003 чёрного цвета при подаче 0 светится
		
		//set_GPIO1;							
		P12 = 0; // типа PORTB&=~(1<<PB12);
		Timer0_Delay1ms(800);
		//clr_GPIO1;
		P12 = 1; // типа PORTB|=(1<<PB12);
		Timer0_Delay1ms(200);
  }
	
}
