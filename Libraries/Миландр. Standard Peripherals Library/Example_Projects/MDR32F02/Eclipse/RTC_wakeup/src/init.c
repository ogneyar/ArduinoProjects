//
// Created by panukov.a on 17.03.2021.
//

#include <init.h>
#include <stdlib.h>
#include <MLDR187_lib.h>
#include <MLDR187_uart.h>
#include <MLDR187_gpio.h>
#include <MLDR187_bkp.h>
#include <MLDR187_it.h>

struct {MDR_GPIO_TypeDef* port; uint16_t pin; bool state;}
LED_PINS[] = {
        {MDR_PORTD, pin0, false},
        {MDR_PORTD, pin1, false}
};

void init_clock()
{
    ErrorStatus erCode;
    RST_CLK_CpuSpeed_InitTypeDef clkInit;

    clkInit.hseState = RST_CLK_HseOscillator;
    clkInit.hseSpeed = 8000000U;
    clkInit.cpuC1Src = RST_CLK_CpuC1SelHse;
    clkInit.pllState = RST_CLK_PllFromHse;
    clkInit.pllMult = 6;
    clkInit.cpuC2Src = RST_CLK_CpuC2SelPllCpu;
    clkInit.cpuC3Div = RST_CLK_Div1;
    clkInit.hclkSrc = RST_CLK_HclkSelCpuC3;
    erCode = RST_CLK_SetupCpuSpeed(&clkInit);
    if (erCode != SUCCESS) {
        exit(EXIT_FAILURE);
    }

    erCode = RST_CLK_SetupHsPeripheralClock(RST_CLK_Clk_PER1_C2, RST_CLK_ClkSrc_CPU_C1);
    if (erCode != SUCCESS) {
        exit(EXIT_FAILURE);
    }
}

void init_uart()
{
    UART_InitTypeDef initStruct;
    UART_StructInitDefault(&initStruct);
    initStruct.baudRate = 115200;
    UART_Init(MDR_UART1, &initStruct);

    PORT_InitTypeDef PORT_InitStructure;

    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_MAIN;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST_2mA;
    PORT_InitStructure.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
    PORT_Init(MDR_PORTB, (PORT_Pin_0), &PORT_InitStructure); // UART1_TX

    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_Init(MDR_PORTB, (PORT_Pin_1), &PORT_InitStructure); // UART1_RX

    UART_Cmd(MDR_UART1, ENABLE);
}

void init_bkp() {
    BKP_InitTypeDef bkpInit;
    BKP_StructInitDefault(&bkpInit);

    // Enable RTC clk source. You'd prefer (LSE, bypass), but you can change this to (LSI, non-bypass)
    BKP_FreqGenCmd(bkpLse, ENABLE, ENABLE);

    bkpInit.RTCsrc = bkpRtc_LSE;
    bkpInit.SWenable = ENABLE;
    BKP_Init(&bkpInit);

    BKP_TampEventInitTypeDef tampInit;
    tampInit.enable = ENABLE;
    tampInit.interrupt = ENABLE;
    tampInit.wakeup1 = BKP_FALLING_LOW;
    tampInit.wakeup2 = BKP_FALLING_LOW;
    tampInit.wakeup3 = BKP_FALLING_LOW;
    BKP_InitTamper(&tampInit);
}

void init_leds() {
    for (int i = 0; i < (int)(sizeof(LED_PINS) / sizeof(LED_PINS[0])); i++) {
        PORT_InitTypeDef portInit = {
                .PORT_MODE = PORT_MODE_DIGITAL,
                .PORT_OE = PORT_OE_OUT,
                .PORT_FUNC = PORT_FUNC_PORT,
                .PORT_SPEED = PORT_SPEED_SLOW_4mA,
                .PORT_PULL_DOWN = PORT_PULL_DOWN_OFF
        };

        PORT_SetReset(LED_PINS[i].port, LED_PINS[i].pin, !LED_PINS[i].state);
        PORT_Init(LED_PINS[i].port, LED_PINS[i].pin, &portInit);
    }
}

void toggle_led(int i) {
    LED_PINS[i].state = !LED_PINS[i].state;
    PORT_SetReset(LED_PINS[i].port, LED_PINS[i].pin, !LED_PINS[i].state);
}

void set_led(int i, BitStatus state) {
    LED_PINS[i].state = state;
    PORT_SetReset(LED_PINS[i].port, LED_PINS[i].pin, !state);
}

void init_interrupts() {
    PLIC_SetMinPermPriority(0);
    PLIC_SetPriority(BACKUP_IRQn, 1);
    PLIC_DisableIRQ(BACKUP_IRQn);
    PLIC_ReleaseIRQ(BACKUP_IRQn);
    PLIC_EnableIRQ(BACKUP_IRQn);
    enable_irq_extm();
}

