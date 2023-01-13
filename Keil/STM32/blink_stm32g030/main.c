
#include "main.h"

// all functions
void GPIO_Init(void);
//void delay(uint16_t inter);
void delay(uint32_t dly);


static uint16_t interval = 500;

	
// main function
int main(void)
{
  /* Initialize all configured peripherals */
	//GPIO_Init();
	/*
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS0);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS1);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS2);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS3);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS4);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS5);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS6);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS7);
	*/
	/*
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS8);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS9);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS10);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS11);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS12);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS13);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS14);
	SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS15);
	*/
	/*
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS1);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS2);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS3);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS4);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS5);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS6);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS7);
	*/
	/*
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS8);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS9);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS10);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS11);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS12);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS13);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS14);
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS15);
	*/
	
	//SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS1_Pos);
	//GPIOB->ODR &= ~(1 << 17);		
	/*
	delay(interval);
	GPIOB->BSRR |= (1 << GPIO_BSRR_BS1_Pos);
	delay(interval);
	GPIOB->BSRR &= ~(1 << GPIO_BSRR_BS1_Pos);
	delay(interval);
	GPIOB->BSRR |= (1 << GPIO_BSRR_BR1_Pos);
	delay(interval);
	GPIOB->BSRR &= ~(1 << GPIO_BSRR_BR1_Pos);
	delay(interval);
	*/
	
	RCC->IOPENR |= 0x10; // enable Port B   
  GPIOB->MODER |= 0x10;
	
  while (1)
  {
		GPIOB->ODR |= 0x10;
    delay(300000);
    GPIOB->ODR &= ~2UL;
    delay(300000);
		
		/*
		delay(interval);
		SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS1);
		delay(interval);
		SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR1);
		*/
  }	
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {
	
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN; // Popt B	
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE1_Pos); // 01: General purpose output mode
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT1; // 0: Output push-pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED1_Msk; // 0x11: Very high speed
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD1_0;
	
	/*
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN; // Popt A 	
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE0_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT0_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED0_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE1_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT1_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED1_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE2_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT2_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED2_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE3_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT3_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED3_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE4_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT4_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED4_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE5_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT5_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED5_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE6_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT6_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED6_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE7_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT7_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED7_Pos); // 0x11: Very high speed
	*/
	/*
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT8_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED8_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE9_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT9_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED9_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE10_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT10_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED10_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE11_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT11_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED11_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE12_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT12_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED12_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE13_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT13_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED13_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE14_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT14_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED14_Pos); // 0x11: Very high speed
	
	GPIOA->MODER |= (1 << GPIO_MODER_MODE15_Pos); // 01: General purpose output mode
	GPIOA->OTYPER |= (0 << GPIO_OTYPER_OT15_Pos); // 0: Output push-pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_Msk; // 0x11: Very high speed
	*/
	/*
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN; // Popt B 
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE0_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT0_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED0_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE1_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT1_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED1_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE2_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT2_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED2_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE3_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT3_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED3_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE4_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT4_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED4_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE5_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT5_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED5_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE6_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT6_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED6_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE7_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT7_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED7_Pos); // 0x11: Very high speed
	*/
	/*
	GPIOB->MODER |= (1 << GPIO_MODER_MODE8_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT8_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED8_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE9_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT9_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED9_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE10_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT10_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED10_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE11_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT11_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED11_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE12_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT12_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED12_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE13_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT13_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED13_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE14_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT14_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED14_Pos); // 0x11: Very high speed
	
	GPIOB->MODER |= (1 << GPIO_MODER_MODE15_Pos); // 01: General purpose output mode
	GPIOB->OTYPER |= (0 << GPIO_OTYPER_OT15_Pos); // 0: Output push-pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_Msk; // 0x11: Very high speed
	*/
}

// delay
/*
void delay(uint16_t inter) {
	for(uint32_t i = 0; i < (uint32_t)(inter<<8); i++) __asm("nop");
}
*/

void delay(uint32_t dly)
{
    while(dly--);
}

