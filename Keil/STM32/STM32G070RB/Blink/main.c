
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
		GPIOC->ODR ^= GPIO_ODR_OD8;
		delay(interval);
  }	
	
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {		
	RCC->IOPENR |= RCC_IOPENR_GPIOCEN; // Popt C		
	
  GPIOC->MODER &= ~GPIO_MODER_MODE8;	/* clear mode for PC8 */
	GPIOC->MODER |= GPIO_MODER_MODE8_0; // 01: General purpose output mode
}

// delay
void delay(uint16_t inter) {
	for(uint32_t i = 0; i < (uint32_t)(inter<<10); i++) __asm("nop");
}

