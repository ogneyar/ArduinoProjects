#include "init.h"

#include <MLDR187_rst_clk.h>
#include <MLDR187_eeprom.h>
#include <stdlib.h>
#include <MLDR187_otp.h>

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

    uint32_t perClk = RST_CLK_EnablePeripheralClock(RST_CLK_EEPROM, RST_CLK_Div1);
    if (perClk == 0) {
        exit(EXIT_FAILURE);
    }

    EEPROM_SetLatency(flashCoreSpeedUpTo60MHz);

    OTP_Init();
}

