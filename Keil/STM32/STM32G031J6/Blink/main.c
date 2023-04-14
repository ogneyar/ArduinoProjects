
#include "stm32g031xx.h"


#define GPIO_Pin7 GPIO_BSRR_BS7
  

// all functions
void GPIO_Init(void);
void delay(uint16_t inter);

static uint16_t interval = 100;


int main(void) 
{
    /* Initialize all configured peripherals */
		GPIO_Init();
	
    while (1)
    {
        // Переключаем пин 7 на порте B
        GPIOB->ODR ^= GPIO_ODR_OD7;
        delay(interval);

        // либо так
        // GPIOB->BSRR |= GPIO_BSRR_BS7; // set
        // delay(interval);
        // GPIOB->BSRR |= GPIO_BSRR_BR7;  // reset
        // delay(interval);

        // либо вот так
        // GPIOB->BSRR |= (uint32_t)GPIO_Pin7; // set
        // delay(interval);
        // GPIOB->BRR |= (uint32_t)GPIO_Pin7;  // reset
        // delay(interval);
    }	
}


// PB7
void GPIO_Init(void) 
{
    //Разрешаем тактирование GPIOB
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN; // Input Output Port B Enable
	
	// включаем порт на выход
  GPIOB->MODER &= ~GPIO_MODER_MODE7;	/* clear mode for PB7 */
	GPIOB->MODER |= GPIO_MODER_MODE7_0; // 01: General purpose output mode (PB7)
}

// delay
void delay(uint16_t inter) {
	for(uint32_t i = 0; i < (uint32_t)(inter<<10); i++) __asm("nop");
}
