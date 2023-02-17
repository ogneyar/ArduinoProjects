
#include "main.h"

// all functions
void GPIO_Init(void);
void delay(uint16_t inter);


static uint16_t interval = 500;

	
// main function
int main(void)
{
  /* Initialize all configured peripherals */
	//GPIO_Init();	
	// PC8
	RCC->IOPENR |= RCC_IOPENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODE8_0;
	GPIOC->BSRR |= GPIO_BSRR_BS1;
	//GPIOC->BSRR |= GPIO_BSRR_BR1;
	
	
  while (1)
  {
		//SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS8);
		//SET_BIT(GPIOC->ODR, GPIO_ODR_OD8);
		//delay(interval);
		//SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR8);
		//CLEAR_BIT(GPIOC->ODR, GPIO_ODR_OD8);
		//delay(interval);
  }	
	
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {		
	RCC->IOPENR |= RCC_IOPENR_GPIOCEN; // Popt C		
	
	GPIOC->MODER |= GPIO_MODER_MODE8_0; // 01: General purpose output mode
	
	//GPIOC->OTYPER &= ~GPIO_OTYPER_OT8; // 0: Output push-pull
	//GPIOC->OTYPER |= GPIO_OTYPER_OT8; // 1: Output open-drain
	
	GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED8_Msk; // 0x11: Very high speed
	//GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED8_1; // 10: High speed
	//GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED8_0; // 01: Low speed
	
	//GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD8;	// 00: No pull-up, pull-down
	//GPIOC->PUPDR |= GPIO_PUPDR_PUPD8_1;	// 10: PushPull + PullDown
}

// delay
void delay(uint16_t inter) {
	for(uint32_t i = 0; i < (uint32_t)(inter<<2); i++) __asm("nop");
}

