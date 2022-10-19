#include <MLDR187.h>
#include <MLDR187_lib.h>
#include <MLDR187_it.h>
#include <MLDR187_dma.h>
#include <MLDR187_ssp.h>
#include <MLDR187_gpio.h>
#include <MLDR187_uart.h>

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void init_clock();
void init_uart();
void init_spi();
void init_interrupts();

/* should go first - just reserve space */
MDR_DMAChannel_TypeDef dmaChannelConfigsBasic[32] __attribute__ ((section (".ahbram_data")));
MDR_DMAChannel_TypeDef dmaChannelConfigsAlter[32] __attribute__ ((section (".ahbram_data")));

/* there must be TX and RX buffers in AHB RAM address space */
uint8_t transmitBuffer[128] __attribute__ ((section (".ahbram_data")));
uint8_t receiveBuffer[128] __attribute__ ((section (".ahbram_data")));

/* for W25Qxx devices -- "Read JEDEC ID" command */
const uint8_t dataToSend[] = { 0x9f, 0x00, 0x00, 0x00 };
bool done = false;


void DMA_IRQHandler(void) {
    MDR_DMAChannel_TypeDef* chnlRx = &dmaChannelConfigsBasic[dmaOffsetSsp2Rx];
    MDR_DMAChannel_TypeDef* chnlTx = &dmaChannelConfigsBasic[dmaOffsetSsp2Tx];

    if (chnlTx->CFG != 0 && (chnlTx->CFG & DMACH_CFG_CYCLE_CTRL_Msk) == DMACH_CFG_CYCLE_CTRL_STOP) {
        /* SPI transmission complete */
        /* disable DMA transmission to exit the interrupt  */
        /* SPL v > 0.29 --> */ // SSP_DMACmd(MDR_SSP2, sspDmaTx, DISABLE);
        MDR_SSP2->DMACR &= ~SSP_DMACR_TXDMAE;
    }

    if (chnlRx->CFG != 0 && (chnlRx->CFG & DMACH_CFG_CYCLE_CTRL_Msk) == DMACH_CFG_CYCLE_CTRL_STOP) {
        /* SPI reception complete */
        /* disable DMA reception to exit the interrupt */
        /* SPL v > 0.29 --> */ // SSP_DMACmd(MDR_SSP2, sspDmaRx, DISABLE);
        MDR_SSP2->DMACR &= ~SSP_DMACR_RXDMAE;

        /* Pull CS up to finish SPI frame */
        PORT_SetReset(MDR_PORTA, PORT_Pin_0, SET);

        done = true;
    }
}

int main()
{
    init_clock();
    init_uart();
    init_spi();
    init_interrupts();

    /* Prepare data in TX buffer */
    memcpy(transmitBuffer, dataToSend, sizeof(dataToSend));

    /* Pull CS down to initiate start of SPI frame */
    PORT_SetReset(MDR_PORTA, PORT_Pin_0, RESET);
    /* Initialize DMA and start transmission */
    SSP_DMATransmit(MDR_SSP2, transmitBuffer, sizeof(dataToSend), IRQn_priority_low);
    SSP_DMAReceive(MDR_SSP2, receiveBuffer, sizeof(dataToSend), DISABLE, IRQn_priority_low);

    /* Do some stuff while transmission is running */
    while (!done) {
        asm("nop");
    }

    /* Print results to UART */
    printf("Sent:\n");
    for (int i = 0; i < 4; i++) {
        printf("%02x ", dataToSend[i]);
        fflush(stdout);
    }
    printf("\n");

    printf("Received:\n");
    for (int i = 0; i < 4; i++) {
        printf("%02x ", receiveBuffer[i]);
        fflush(stdout);
    }
    printf("\n");
}


/* Init functions */

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
        while (1);
    }

    erCode = RST_CLK_SetupHsPeripheralClock(RST_CLK_Clk_PER1_C2, RST_CLK_ClkSrc_CPU_C1);
    if (erCode != SUCCESS) {
        while (1);
    }
}

void init_spi()
{
    SSP_InitTypeDef initStruct;
    PORT_InitTypeDef spiPort;

    RST_CLK_SetupHsPeripheralClock(RST_CLK_Clk_PER1_C2, RST_CLK_ClkSrc_CPU_C1);

    SSP_StructInit(&initStruct);
    SSP_Init(MDR_SSP2, &initStruct);

    SSP_Cmd(MDR_SSP2, ENABLE);

    // Init I/O pins
    spiPort.PORT_OE    = PORT_OE_IN;
    spiPort.PORT_FUNC  = PORT_FUNC_ALTER;
    spiPort.PORT_MODE  = PORT_MODE_DIGITAL;
    spiPort.PORT_SPEED = PORT_SPEED_SLOW_4mA;
    spiPort.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
    PORT_Init(MDR_PORTA, (PORT_Pin_2), &spiPort);

    // Setup initial pin values
    spiPort.PORT_OE    = PORT_OE_IN;
    PORT_Init(MDR_PORTA, (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_3), &spiPort);
    PORT_SetReset(MDR_PORTA, PORT_Pin_0 | PORT_Pin_3, SET);
    PORT_SetReset(MDR_PORTA, PORT_Pin_1, RESET);
    spiPort.PORT_OE    = PORT_OE_OUT;
    PORT_Init(MDR_PORTA, (PORT_Pin_1 | PORT_Pin_3), &spiPort);
    spiPort.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_Init(MDR_PORTA, (PORT_Pin_0), &spiPort);
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
    // Enable interrupts
    enable_irq_extm();
    PLIC_SetMinPermPriority(0);
    DMA_IrqPreInit();
}
