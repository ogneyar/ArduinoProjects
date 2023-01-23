
#include "main.h"

// all functions
void GPIO_Init(void);
void delay(uint16_t inter);
//void delay(uint32_t dly);


static uint16_t interval = 500;

	
// main function
int main(void)
{
  /* Initialize all configured peripherals */
	GPIO_Init();
	
	
	//SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS0);
	//SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
		
	//SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0);
	//SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0);
	
	
  while (1)
  {
		//GPIOA->ODR |= 0x00000001;
    //delay(300000);
		//GPIOA->ODR &= 0x11111110;
    //delay(300000);
				
		
		//delay(interval);
		SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS0);
		SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0);
		//delay(interval);
		SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR0);
		SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0);
		
  }	
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {
		
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // Popt A 		
	// PA0
	GPIOA->MODER |= (0x01 << GPIO_MODER_MODE0_Pos); // 01: General purpose output mode PA0 
	//GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT0_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_Msk; // 0x11: Very high speed
	//GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_0;
	
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN; // Popt B	
	// PB0
	GPIOB->MODER |= (1 << GPIO_MODER_MODE0_Pos); // 01: General purpose output mode PB0
	//GPIOB->OTYPER &= ~GPIO_OTYPER_OT0; // 0: Output push-pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED0_Msk; // 0x11: Very high speed
	//GPIOB->PUPDR |= GPIO_PUPDR_PUPD0_0;
	
}

// delay
void delay(uint16_t inter) {
	for(uint32_t i = 0; i < (uint32_t)(inter<<8); i++) __asm("nop");
}

/*
void delay(uint32_t dly)
{
    while(dly--);
}
*/

