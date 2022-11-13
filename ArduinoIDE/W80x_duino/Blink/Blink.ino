
//#include "include/driver/wm_hal.h"

void setup(void) {
    GPIOB->DIR |= GPIO_PIN_0;           // пин B0 на выход
//    TIM->TIM0_PRD = 500;                // период таймера 0 - 500 мс
//    TIM->CR &= ~TIM_CR_TIM0_MODE;       // режим счета - непрерывный
//    TIM->CR |= TIM_CR_TIM0_EN;          // включаем таймер

    GPIOB->DIR |= GPIO_PIN_1;           // пин B1 на выход
    GPIOB->DIR |= GPIO_PIN_2;           // пин B2 на выход
    GPIOB->DATA &= ~GPIO_PIN_1;         // зажечь
}

void loop(void) {  
//    if(TIM->CR & TIM_CR_TIM0_TIF) {  // периодически проверяем флаг окончания счета
//        GPIOB->DATA ^= GPIO_PIN_0;   // инвертируем ножку PB0 
//        TIM->CR |= TIM_CR_TIM0_TIF;  // сбрасываем флаг таймера 0
//    }
    
    GPIOB->DATA ^= GPIO_PIN_0;
    for(uint32_t i = 0; i < 10000000; i++) asm("nop");
    GPIOB->DATA ^= GPIO_PIN_2;
    for(uint32_t i = 0; i < 10000000; i++) asm("nop");
    GPIOB->DATA ^= GPIO_PIN_1;
    
}
