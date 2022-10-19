#include <MLDR187_rst_clk.h>
#include <MLDR187_clk_msr.h>
#include <MLDR187_bkp.h>
#include <MLDR187_it.h>

#include <init.h>

/* --------------- Configuration ---------------- */

/* Adjust HSI frequency to match specified value by varying HSI_TRIM */
#define HSI_SPEED 8000000
#define HSI_TRIM 38

/* Counters typically will be reset after SLOWEST_TICKS * K_NORMAL ticks of a slower clock source */
/* If any of counters reaches K_ALARM ticks, interrupt occurs */
/* Perfect case: SLOWEST_TICKS = min(HCLK, HSI) / GCD(HCLK, HSI) */
#define SLOWEST_TICKS 1
#define K_NORMAL 8
#define K_ALARM 9

/* ---------------------------------------------- */


void CLK_MEASURE_IRQHandler(void) {
    set_led(0, RESET);
    for (;;) {
        for (int i = 0; i < 0x200000; ++i);
        toggle_led(1);
    }
}


int main() {
    init_clock();
    init_interrupts();
    init_leds();

    RST_CLK_EnablePeripheralClock(RST_CLK_BKP, RST_CLK_Div1);
    MDR_BKP->WPR = BKP_WPR_KEY;
    while ((MDR_BKP->CS & BKP_RTC_CS_WEC) != 0);
    MDR_BKP->CLK = (MDR_BKP->CLK & ~BKP_CLK_HSITRIM_Msk) | ((HSI_TRIM << BKP_CLK_HSITRIM_Pos) & BKP_CLK_HSITRIM_Msk);
    MDR_BKP->WPR = 0;

    CLK_MSR_InitTypeDef initStruct = {
            .itEn = ENABLE,
            .it_MaxSft0 = ~-(1 << K_ALARM),
            .it_MaxSft1 = ~-(1 << K_ALARM)
    };

    if (RST_CLK_HclkSpeed < HSI_SPEED) {
        initStruct.preg0 = (uint64_t)SLOWEST_TICKS * K_NORMAL;
        initStruct.preg1 = (uint64_t)SLOWEST_TICKS * K_NORMAL * HSI_SPEED / RST_CLK_HclkSpeed - 1;
        initStruct.preg2 = (uint64_t)SLOWEST_TICKS - 1;
        initStruct.preg3 = (uint64_t)SLOWEST_TICKS * HSI_SPEED / RST_CLK_HclkSpeed - 1;
    } else {
        initStruct.preg0 = (uint64_t)SLOWEST_TICKS * K_NORMAL * RST_CLK_HclkSpeed / HSI_SPEED - 1;
        initStruct.preg1 = (uint64_t)SLOWEST_TICKS * K_NORMAL;
        initStruct.preg2 = (uint64_t)SLOWEST_TICKS * RST_CLK_HclkSpeed / HSI_SPEED - 1;
        initStruct.preg3 = (uint64_t)SLOWEST_TICKS - 1;
    }

    CLK_MSR_Init(&initStruct);

    CLK_MSR_Cmd(ENABLE);

    for (;;) {
        for (int i = 0; i < 0x800000; ++i);
        toggle_led(0);
    }

    return 0;
}

