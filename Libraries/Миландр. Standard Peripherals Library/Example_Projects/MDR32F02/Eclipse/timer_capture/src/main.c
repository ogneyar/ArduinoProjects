#include <stdlib.h>
#include <stdio.h>

#include <MLDR187_uart.h>
#include <MLDR187_timer.h>
#include <MLDR187_gpio.h>
#include <MLDR187_it.h>

#define __ramfunc       __attribute__ ((section (".ramfunc")))
#define __ahbram_data   __attribute__ ((section (".ahbram_data")))
#define __ahbram_bss    __attribute__ ((section (".ahbram_bss")))

#define CAPTURE_TIMER   MDR_TIMER3
#define CAPTURE_IRQ_N   TIM3_IRQn
#define CAPTURE_CHANNEL timCh4
#define CAPTURE_EVENT   timEventCCRch4
#define CAPTURE_IN_PORT MDR_PORTB
#define CAPTURE_IN_PIN  pin6
#define CAPTURE_IN_FUNC PORT_FUNC_OVERRID

#define DISPLAY_LINE_LENGTH 50
#define DELAY_TICKS 0x1000


static uint32_t PREV_CCR = 0;
static uint32_t PERIOD;
static uint32_t DUTY;

void init_clock();
void init_uart();
void setup_timer();


__ramfunc int main()
{
    init_clock();
    init_uart();
    setup_timer();

    for (;;)
    {
        uint32_t period = PERIOD;
        uint32_t duty = DUTY;

        double frequency = (double)RST_CLK_PER1C2_Speed / (double)period;
        double duty_fr = (double)duty / (double)period;

        char bar[DISPLAY_LINE_LENGTH+1];
        for (int i = 0; i < DISPLAY_LINE_LENGTH; ++i)
            bar[i] = (i < duty_fr * DISPLAY_LINE_LENGTH) ? '*' : ' ';
        bar[DISPLAY_LINE_LENGTH] = '\0';

        printf("%d Hz; Duty %3d%% |%s|\n", (int)frequency, (int)(duty_fr * 100), bar);

        for (int i = 0; i < DELAY_TICKS; ++i);
    }
}

__ramfunc void Timer3_IRQHandler(void)
{
    TIMER_ClearFlag(CAPTURE_TIMER, CAPTURE_EVENT);
    uint32_t CCR = TIMER_GetChCCR(CAPTURE_TIMER, CAPTURE_CHANNEL, timCCR);
    uint32_t CCR1 = TIMER_GetChCCR(CAPTURE_TIMER, CAPTURE_CHANNEL, timCCR1);
    uint32_t period = CCR - PREV_CCR;
    uint32_t duty = CCR1 - PREV_CCR;
    if (duty > period) {
        duty %= period;
    }
    PREV_CCR = CCR;
    PERIOD = period;
    DUTY = duty;
}

void setup_timer()
{
    TIMER_DeInit(CAPTURE_TIMER);

    TIMER_CntInitTypeDef timInit;
    TIMER_StructInitDefault(&timInit);
    timInit.period          = 0xffffffff;
    TIMER_Init(CAPTURE_TIMER, &timInit);

    TIMER_ChannelInitTypeDef chnInit;
    TIMER_ChnStructInitDefault(&chnInit);
    chnInit.chMode          = timChCapture;
    chnInit.CCR1enable      = ENABLE;
    chnInit.EVTsrcCCR       = timChEvPositiveEdge;
    chnInit.EVTsrcCCR1      = timChEvNegativeEdge;
    TIMER_ChnInit(CAPTURE_TIMER, CAPTURE_CHANNEL, &chnInit);

    TIMER_OuputInitTypeDef outInit;
    TIMER_ChnOutStructInitDefault(&outInit);
    outInit.outEn           = timChOutAlwaysOff;
    TIMER_ChnOutInit(CAPTURE_TIMER, CAPTURE_CHANNEL, timChOutDirect, &outInit);

    PORT_InitTypeDef portInit = {
            .PORT_OE = PORT_OE_IN,
            .PORT_MODE  = PORT_MODE_DIGITAL,
            .PORT_FUNC = CAPTURE_IN_FUNC
    };
    PORT_Init(CAPTURE_IN_PORT, CAPTURE_IN_PIN, &portInit);

    TIMER_ItSetNewState(CAPTURE_TIMER, CAPTURE_EVENT, ENABLE);

    PLIC_SetMinPermPriority(0);
    PLIC_ReleaseIRQ(CAPTURE_IRQ_N);
    PLIC_SetPriority(CAPTURE_IRQ_N, 1);
    PLIC_EnableIRQ(CAPTURE_IRQ_N);
    enable_irq_extm();

    TIMER_Cmd(CAPTURE_TIMER, ENABLE);
}

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

