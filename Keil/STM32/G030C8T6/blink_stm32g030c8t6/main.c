
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
		delay(interval);
		SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS13);
		delay(interval);
		SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR13);
  }	
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {
	RCC->IOPENR |= RCC_IOPENR_GPIODEN; // PD2
	GPIOC->MODER |= (1 << GPIO_MODER_MODE2_Pos); // 01: General purpose output mode
	GPIOC->OTYPER |= (0 << GPIO_OTYPER_OT2_Pos); // 0: Output push-pull
	GPIOC->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED2_Pos); // 0x11: Very high speed
}

// delay
void delay(uint16_t inter) {
	for(uint32_t i = 0; i < (uint32_t)(inter<<12); i++) __asm("nop");
}

