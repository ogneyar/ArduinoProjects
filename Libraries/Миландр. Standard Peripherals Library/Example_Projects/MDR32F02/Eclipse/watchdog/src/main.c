//
// Created by panukov.a on 05.03.2021.
//

#include <MLDR187_bkp.h>
#include <MLDR187_iwdg.h>
#include <stdlib.h>

#include <wait.h>
#include <stdio.h>
#include <math.h>
#include <MLDR187_uart.h>
#include <MLDR187_gpio.h>

#define TRIMMING    1.55
#define TEST_N      10
#define TEST_PERIOD 1

void init_clock();
void init_uart();
ErrorStatus enable_watchdog(double seconds);
void refresh_watchdog();

int main() {
    init_clock();
    init_uart();

    // Refresh test
    enable_watchdog(1.1 * (double)TEST_PERIOD / (double)TRIMMING);
    printf("\nCounting to %d\n", TEST_N);
    for (int i = 0; i < TEST_N; i++) {
        wait(TEST_PERIOD, MDR_TIMER1);
        printf("%d ", i + 1);
        fflush(stdout);
        refresh_watchdog();
    }
    printf("Goodbye!\n");

    // Not refresh test
    enable_watchdog((double)TEST_PERIOD * TEST_N / (double)TRIMMING);
    printf("\nCounting to %d\n", TEST_N);
    for (int i = 0; i < TEST_N; i++) {
        wait(TEST_PERIOD, MDR_TIMER1);
        printf("%d ", i + 1);
        fflush(stdout);
    }
    printf("Goodbye!\n");

    return 0;
}

ErrorStatus enable_watchdog(double seconds) {
    double delay_ticks = RST_CLK_LSI_FREQUENCY * seconds;
    if (delay_ticks > 0x1000 * 256 || delay_ticks < 4)
        return ERROR;

    uint16_t prescaler = ceil(delay_ticks / 0x1000);
    int pow;
    for (pow = 2; pow <= 8; pow++)
        if (prescaler >> pow == 1)
            break;

    if (prescaler >> pow != 1)
        return ERROR;

    prescaler = (prescaler >> pow) << pow;

    uint32_t counter = delay_ticks / prescaler - 1;

    if (counter > 0xfff) {
        prescaler <<= 1;
        counter >>= 1;
        pow += 1;
    }

    IWDG_Prescaler iwdgPrescaler = pow - 2;

    IWDG_SetupAndActivate(iwdgPrescaler, counter);

    return SUCCESS;
}

void refresh_watchdog() {
    IWDG_Refresh();
}

void init_clock() {
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

    BKP_InitTypeDef bkpInit;
    BKP_StructInitDefault(&bkpInit);
    bkpInit.RTCsrc = bkpRtc_HSI;
    BKP_Init(&bkpInit);

    BKP_FreqGenCmd(bkpLsi, ENABLE, DISABLE);
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
