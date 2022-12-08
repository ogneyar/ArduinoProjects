
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
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Input Output Port C Enable
	GPIOC->CRH &= ~GPIO_CRH_CNF13; // 0b00 // PC13 Output Push-Pull
	GPIOC->CRH |= GPIO_CRH_MODE13; //50 MHz
}

// delay
void delay(uint16_t inter) {
	for(uint32_t i = 0; i < (uint32_t)(inter<<12); i++) __asm("nop");
}

