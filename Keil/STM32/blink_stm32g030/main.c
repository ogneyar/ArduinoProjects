
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
	//GPIO_Init();
	
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	GPIOB->MODER |= (1 << GPIO_MODER_MODE2_Pos);
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED2_Msk;
	//SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS2);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR2);
	
	
  while (1)
  {			
		//SET_BIT(GPIOB->ODR, GPIO_ODR_OD1);
		//SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS1);
		//delay(interval);
		//CLEAR_BIT(GPIOB->ODR, GPIO_ODR_OD1);
		//SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR1);
		//delay(interval);
  }	
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {	
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN; // Popt B	
	// PB1
	GPIOB->MODER |= (1 << GPIO_MODER_MODE1_Pos); // 01: General purpose output mode PB1
	//GPIOB->OTYPER &= ~GPIO_OTYPER_OT1; // 0: Output push-pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_Msk; // 0x11: Very high speed
	//GPIOB->PUPDR |= GPIO_PUPDR_PUPD1_0; // pull up
	//GPIOB->PUPDR |= GPIO_PUPDR_PUPD1_1; // pull down	
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

