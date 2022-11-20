
#include "main.h"

// all functions
void GPIO_Init(void);
void delay(uint16_t inter);

static uint16_t interval = 100;
	
	
// main function
int main(void)
{
  /* Initialize all configured peripherals */
	GPIO_Init();
	
  while (1)
  {
		delay(interval);
		/* GPIO port pull-up/pull-down register (GPIOx_PUPDR) (x = A..E and H) */
		SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS13);
		delay(interval);
		SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR13);
  }	
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {
/* RCC AHB1 peripheral clock enable register (RCC_AHB1ENR) */
	// Bit 2 GPIOCEN: IO port C clock enable
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Input Output Port C Enable
/* ------------------------------------- */
	
/* General-purpose I/Os (GPIO) */
	// GPIO port mode register (GPIOx_MODER) (x = A..E and H)
	GPIOC->MODER |= (0x01 << GPIO_MODER_MODE13_Pos); // 01: General purpose output mode (PC13)
/* --------------------------- */
	
/* GPIO port output type register (GPIOx_OTYPER)(x = A..E and H) */
	// OTy: Port x configuration bits (y = 0..15)
	GPIOC->OTYPER |= GPIO_OTYPER_OT13; // 0: Output push-pull (reset state)
/* ------------------------------------------------------------- */
	
/* GPIO port output speed register (GPIOx_OSPEEDR) (x = A..E and H) */
	// OSPEEDRy[1:0]: Port x configuration bits (y = 0..15)
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED13; // 11: High speed
/* ---------------------------------------------------------------- */
}

// delay
void delay(uint16_t inter) {
	for(uint32_t i = 0; i < (uint32_t)(inter<<10); i++) __asm("nop");
}

