
#include "main.h"

// all functions
void GPIO_Init(void);
void delay(uint16_t inter);


static uint16_t interval = 500;

	
// main function
int main(void)
{
  /* Initialize all configured peripherals */
	GPIO_Init();
		
  while (1)
  {			
		GPIOB->ODR ^= GPIO_ODR_OD1;
		delay(interval);
  }	
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {	
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN; // Popt B	
	// PB1
  GPIOB->MODER &= ~GPIO_MODER_MODE1;	/* clear mode for PB7 */
	GPIOB->MODER |= (1 << GPIO_MODER_MODE1_Pos); // 01: General purpose output mode PB1
}

// delay
void delay(uint16_t inter) {
	for(uint32_t i = 0; i < (uint32_t)(inter<<8); i++) __asm("nop");
}

