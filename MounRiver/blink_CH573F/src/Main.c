
#include "CH57x_common.h"

// LED on PA8
#define LED GPIO_Pin_8

void delay(uint16_t);

int main() {

    SetSysClock(CLK_SOURCE_PLL_60MHz);

    GPIOA_ModeCfg(LED, GPIO_ModeOut_PP_5mA);

    while(1){
        delay(100);
        GPIOA_ResetBits(LED);
        delay(100);
        GPIOA_SetBits(LED);
    }
}

void delay(uint16_t value) {
    for (uint32_t i = 0; i < (value<<10); i++) asm("nop");
}
