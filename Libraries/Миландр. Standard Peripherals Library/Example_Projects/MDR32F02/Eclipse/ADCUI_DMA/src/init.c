#include <init.h>
#include <stdlib.h>
#include <MLDR187_lib.h>
#include <MLDR187_uart.h>
#include <MLDR187_gpio.h>
#include <MLDR187_bkp.h>
#include <MLDR187_it.h>
#include <stdbool.h>
#include <MLDR187_dma.h>
#include <MLDR187_adcui.h>


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

void init_interrupts() {
    PLIC_SetMinPermPriority(0);
    enable_irq_extm();
}

void init_dma() {
    DMA_Init((uint8_t *) DMA_CONFIG_BASE, 0);
    DMA_IrqPreInit();
}

void init_adc() {
    ADCUI_InitTypeDef initStruct;
    ADCUI_StructInitDefault(&initStruct);
    initStruct.i3En = DISABLE;
    initStruct.i0En = DISABLE;
    initStruct.v0En = DISABLE;
    initStruct.i1En = DISABLE;
    initStruct.v1En = DISABLE;
    initStruct.i2En = DISABLE;
    initStruct.v2En = DISABLE;
    ADCUI_Init(&initStruct);
    MDR_ADCUI->CTRL3 = 0;

    ADCUI_CH_InitTypeDef chInitStruct;
    ADCUI_ChannelStructInitDefault(&chInitStruct);
    chInitStruct.IaltEnInt = DISABLE;
    chInitStruct.IEnInt = DISABLE;
    ADCUI_InitChannel(adcuiCh0 ,&chInitStruct);
    ADCUI_InitChannel(adcuiCh1 ,&chInitStruct);
    ADCUI_InitChannel(adcuiCh2 ,&chInitStruct);
}

