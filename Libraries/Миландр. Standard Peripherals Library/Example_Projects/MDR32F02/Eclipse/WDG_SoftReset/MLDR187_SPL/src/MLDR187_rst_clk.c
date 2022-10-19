/**
  * FILE MLDR187_rst_clk.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_rst_clk.h"
#include "MLDR187_bkp.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_RST_CLK_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup RST_CLK
  * @{
  */

/** @defgroup RST_CLK_GlobalVariables
  * @{
  */

/* CPU speed (this variable will be updated during configuration) */
uint32_t RST_CLK_CpuSpeed = RST_CLK_HSI_FREQUENCY;

/* HCLK speed (this variable will be updated during configuration) */
uint32_t RST_CLK_HclkSpeed = RST_CLK_HSI_FREQUENCY;

/* peripheral source clock speed (for legacy interface support) */
uint32_t RST_CLK_PER1C2_Speed = 0;

/** @} */ /* End of group RST_CLK_GlobalVariables */

/** @defgroup RST_CLK_PrivateVariables
  * @{
  */

/* reference clock speed within MCU */
static uint32_t rccHseSpeed = 0;
static uint32_t rccCpuC1Speed = 0;
static uint32_t rccPllSpeed = 0;
static uint32_t rccCpuC3Speed = 0;
static uint32_t rccPer1C1Speed = 0;
static uint32_t rccAdcUIC1Speed = 0;
static uint32_t rccAdcC1Speed = 0;
static uint32_t rccWwdgSpeed = 0;

/** @} */ /* End of group RST_CLK_PrivateVariables */


/** @defgroup RST_CLK_Private_Defines
  * @{
  */

/* timeout till RCC HSE and PLL stabilized */
#define RST_CLK_CLOCK_STABILIZATION_TIMEOUT     100000U

/* maximum support speed for PLL module */
#define RST_CLK_PLL_MAXIMUM_OUTPUT_FREQ         60000000U

/** @} */ /* End of group RST_CLK_Private_Defines */

/** @defgroup RST_CLK_Private_Macros
  * @{
  */

/* macro for HSE state */
#define RST_CLK_IS_HSE_STATE(HSE)           (((HSE) == RST_CLK_HseOff) || \
                                             ((HSE) == RST_CLK_HseOscillator) || \
                                             ((HSE) == RST_CLK_HseBypass))

/* macro for HSE speed */
#define RST_CLK_IS_HSE_SPEED_VALID(HSESPEED) (((HSESPEED) >= 8000000U) && \
                                              ((HSESPEED) <= 16000000U))

/* macro for CPU C1 source */
#define RST_CLK_IS_CPUC1_SOURCE(SOURCE)     (((SOURCE) == RST_CLK_CPU_CLOCK_CPUC1SEL_HSI) || \
                                             ((SOURCE) == RST_CLK_CPU_CLOCK_CPUC1SEL_HSI_2) || \
                                             ((SOURCE) == RST_CLK_CPU_CLOCK_CPUC1SEL_HSE) || \
                                             ((SOURCE) == RST_CLK_CPU_CLOCK_CPUC1SEL_HSE_2))

/* macro for PLL state */
#define RST_CLK_IS_PLL_STATE(STATE)         (((STATE) == RST_CLK_PllOff) || \
                                             ((STATE) == RST_CLK_PllFromHse) || \
                                             ((STATE) == RST_CLK_PllFromCpuC1))

/* macro for PLL multiplication factor */
/* PLLMULT is unsigned number and 0 is valid item, so we could check only high end */
#define RST_CLK_IS_PLL_MULT_VALID(PLLMULT)  ((PLLMULT) <= 7)

/* macro for CPU C2 source */
#define RST_CLK_IS_CPUC2_SOURCE(SOURCE)     (((SOURCE) == RST_CLK_CPU_CLOCK_CPUC2SEL_CPUC1) || \
                                             ((SOURCE) == RST_CLK_CPU_CLOCK_CPUC2SEL_PLLCPU))

/* macro for HCLK frequency source */
#define RST_CLK_IS_HCLK_CLOCK_SOURCE(HCLK)  (((HCLK) == RST_CLK_CPU_CLOCK_HCLKSEL_HSI) || \
                                             ((HCLK) == RST_CLK_CPU_CLOCK_HCLKSEL_CPUC3) || \
                                             ((HCLK) == RST_CLK_CPU_CLOCK_HCLKSEL_LSE) || \
                                             ((HCLK) == RST_CLK_CPU_CLOCK_HCLKSEL_LSI))

/* macro for hi-speed peripheral clock setup */
#define RST_CLK_IS_HS_PERIPHERAL_CLOCK(PERIPH)  (((PERIPH) == RST_CLK_Clk_ADC_C1) || \
                                             ((PERIPH) == RST_CLK_Clk_ADCUI_C1) || \
                                             ((PERIPH) == RST_CLK_Clk_WDG_C2) || \
                                             ((PERIPH) == RST_CLK_Clk_PER1_C2))

/* macro for hi-speed clock source */
#define RST_CLK_IS_HS_CLK_SOURCE(CLK_SRC)   (((CLK_SRC) == RST_CLK_ClkSrc_CPU_C1) || \
                                             ((CLK_SRC) == RST_CLK_ClkSrc_PER_OR_WDG_C1) || \
                                             ((CLK_SRC) == RST_CLK_ClkSrc_PLLCPU) || \
                                             ((CLK_SRC) == RST_CLK_ClkSrc_HSE_HSI_CLK))

/* macro for low-speed peripheral clock setup */
#define RST_CLK_IS_LS_PERIPHERAL_CLOCK(PERIPH)  (((PERIPH) == RST_CLK_Clk_WDG_C1) || \
                                             ((PERIPH) == RST_CLK_Clk_PER1_C1))

/* macro for low-speed clock source */
#define RST_CLK_IS_LS_CLK_SOURCE(CLK_SRC)   (((CLK_SRC) == RST_CLK_ClkSrc_LSI) || \
                                             ((CLK_SRC) == RST_CLK_ClkSrc_LSI_2) || \
                                             ((CLK_SRC) == RST_CLK_ClkSrc_LSE) || \
                                             ((CLK_SRC) == RST_CLK_ClkSrc_LSE_2))

/* macro for peripheral clock enable assert */
#define RST_CLK_IS_CLOCK_PERIPHERAL(PERIPH) (((PERIPH) == RST_CLK_PER2_CLOCK_SPI1EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_UART1EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_UART2EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_EEPROMEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_RST_CLKEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_DMAEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_I2CEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_UART3EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_ADCEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_WWDGEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_IWDGEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_POWEREN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_BKPEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_ADCUIEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_TIMER1EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_TIMER2EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_PORTAEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_PORTBEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_PORTCEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_CRCEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_SENSORSEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_CLKMEASUREEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_RANDOMEN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_ISO7816EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_SPI2EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_SPI3EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_TIMER3EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_TIMER4EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_UART4EN) || \
                                             ((PERIPH) == RST_CLK_PER2_CLOCK_PORTDEN) || \
                                             ((PERIPH) == RST_CLK_RTC_HSE) || \
                                             ((PERIPH) == RST_CLK_RTC_HSI))

/** @} */ /* End of group RST_CLK_Private_Macros */

/** @defgroup RST_CLK_Private_Functions_Declarations
  * @{
  */

static uint32_t rccEncodeDivisor3bit(RST_CLK_ClkDiv divisor);
static uint32_t rccEncodeDivisor4bit(RST_CLK_ClkDiv divisor);
static uint32_t rccEncodeDivisorNumeric(RST_CLK_ClkDiv divisor);

/** @} */ /* End of group RST_CLK_Private_Functions_Declarations */

/** @defgroup RST_CLK_Exported_Functions
  * @{
  */

/**
  * @brief  initialize hi-speed oscillators for the MCUs core
  * @param  rccCpuInit - @ref RST_CLK_CpuSpeed_InitTypeDef - inialization parameters
  * @retval @ErrorStatus,
  *         SUCCESS if hi-speed core initialized successfully,
  *         ERROR if something goes wrong (HSE or PLL oscillator is not stable, resulting frequency is not valid, etc,
  *         when ERROR is returned, CPU is run using HSI at 8 MHz speed
  */
ErrorStatus RST_CLK_SetupCpuSpeed(RST_CLK_CpuSpeed_InitTypeDef* rccCpuInit)
{
    uint32_t spinLockTimeout;
    ErrorStatus erCode = ERROR;

    /* test input parameters */
    assert_param(RST_CLK_IS_HSE_STATE(rccCpuInit->hseState));
    assert_param(RST_CLK_IS_HSE_SPEED_VALID(rccCpuInit->hseSpeed));
    assert_param(RST_CLK_IS_CPUC1_SOURCE(rccCpuInit->cpuC1Src));
    assert_param(RST_CLK_IS_PLL_STATE(rccCpuInit->pllState));
    assert_param(RST_CLK_IS_PLL_MULT_VALID(rccCpuInit->pllMult));
    assert_param(RST_CLK_IS_CPUC2_SOURCE(rccCpuInit->cpuC2Src));
    assert_param(RST_CLK_DIV_IS_4BITS(rccCpuInit->cpuC3Div));
    assert_param(RST_CLK_IS_HCLK_CLOCK_SOURCE(rccCpuInit->hclkSrc));

    /* as MISRA required, use only one return point */
    do
    {
        /*--------- setup HSE ---------*/
        /* store HSE crystal speed */
        rccHseSpeed = rccCpuInit->hseSpeed;

        /* if HSE is not requested, deactivate it */
        if (rccCpuInit->hseState == RST_CLK_HseOff)
        {
            MDR_RST_CLK->HS_CONTROL &= ~RST_CLK_HS_CONTROL_HSEON;
        }
        /* otherwise we should activate HSE and specify it's mode */
        else
        {
            /* specify HSE oscillator mode */
            if (rccCpuInit->hseState == RST_CLK_HseOscillator)
            {
                MDR_RST_CLK->HS_CONTROL &= ~RST_CLK_HS_CONTROL_HSEBYP;
            }
            else
            {
                MDR_RST_CLK->HS_CONTROL |= RST_CLK_HS_CONTROL_HSEBYP;
            }
            /* activate HSE and wait till it stabilized */
            MDR_RST_CLK->HS_CONTROL |= RST_CLK_HS_CONTROL_HSEON;
            for (spinLockTimeout = 0; spinLockTimeout < RST_CLK_CLOCK_STABILIZATION_TIMEOUT; spinLockTimeout++)
            {
                if ((MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSERDY) != 0)
                {
                    break;
                }
            }
            /* this is HW error if HSE is not stabilized in time */
            if (spinLockTimeout >= RST_CLK_CLOCK_STABILIZATION_TIMEOUT)
            {
                break;
            }
        }

        /*--------- setup CPU C1 ---------*/
        /* ensure that specified frequency source for CPU C1 is stable */
        if (rccCpuInit->cpuC1Src == RST_CLK_CpuC1SelHsi || rccCpuInit->cpuC1Src == RST_CLK_CpuC1SelHsi2)
        {
            /* use BKP domain to ensure that HSI is running */
            if (BKP_GenState(bkpHsi) != ENABLE)
            {
                break;
            }
            /* store CPU C1 frequency */
            rccCpuC1Speed = (rccCpuInit->cpuC1Src == RST_CLK_CpuC1SelHsi) ? RST_CLK_HSI_FREQUENCY : (RST_CLK_HSI_FREQUENCY / 2);
        }
        else
        {
            /* ensure that HSE is running and stable */
            if ((MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSERDY) == 0)
            {
                break;
            }
            /* store CPU C1 frequency */
            rccCpuC1Speed = (rccCpuInit->cpuC1Src == RST_CLK_CpuC1SelHse) ? rccCpuInit->hseSpeed : (rccCpuInit->hseSpeed / 2);
        }
        /* setup new CPU C1 frequency source */
        MDR_RST_CLK->CPU_CLOCK &= ~RST_CLK_CPU_CLOCK_CPUC1SEL_Msk;
        MDR_RST_CLK->CPU_CLOCK |= rccCpuInit->cpuC1Src;

        /*--------- setup PLL ---------*/
        /* any input configuration should be proceeded with deactivated PLL */

        // If CPU was tied to PLL, then switch it to PLL source.
        // It may only be CPU C1, because HSE is not available directly for CPU C2
        if ((MDR_RST_CLK->CPU_CLOCK & RST_CLK_CPU_CLOCK_CPUC2SEL_Msk) == RST_CLK_CpuC2SelPllCpu) {
            // Here we can only switch C2 to C1. We need to ensure that C1 is active.
            // It may be inactive only if PLL was tied to HSE and C1 was tied to disabled HSI
            if ((MDR_RST_CLK->PLL_CONTROL & RST_CLK_PLL_CONTROL_PLLSEL_Msk) == RST_CLK_PLL_CONTROL_PLLSEL_HSE) {
                uint32_t c1_sel = MDR_RST_CLK->CPU_CLOCK & RST_CLK_CPU_CLOCK_CPUC1SEL_Msk;
                if ((c1_sel == RST_CLK_CpuC1SelHsi || c1_sel == RST_CLK_CpuC1SelHsi2) && !(MDR_BKP->CLK & BKP_CLK_HSION_Msk)) {
                    // C1 is disabled and we have no other choice where to temporarily switch C2
                    // So if we disable PLL now, CPU will get stuck
                    break;
                }
            }
            // C1 is active
            // Switch C2 to C1
            MDR_RST_CLK->CPU_CLOCK &= ~RST_CLK_CPU_CLOCK_CPUC2SEL_Msk;
        }
        // Disable PLL
        MDR_RST_CLK->PLL_CONTROL &= ~RST_CLK_PLL_CONTROL_PLLON;
        /* if PLL is requested, activate it */
        if (rccCpuInit->pllState != RST_CLK_PllOff)
        {
            /* specify HSE oscillator mode */
            MDR_RST_CLK->PLL_CONTROL &= ~RST_CLK_PLL_CONTROL_PLLSEL_Msk;
            if (rccCpuInit->pllState == RST_CLK_PllFromHse)
            {
                MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLLSEL_HSE;
                rccPllSpeed = rccCpuInit->hseSpeed;
            }
            else
            {
                MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLLSEL_CPUC1;
                rccPllSpeed = rccCpuC1Speed;
            }
            /* ensure that after multiplication we will have valid speed (<= 60 MHz) */
            if ((rccPllSpeed * (rccCpuInit->pllMult + 1)) > RST_CLK_PLL_MAXIMUM_OUTPUT_FREQ)
            {
                break;
            }

            /* setup multiplicator */
            MDR_RST_CLK->PLL_CONTROL &= ~RST_CLK_PLL_CONTROL_PLLMUL_Msk;
            MDR_RST_CLK->PLL_CONTROL |= ((rccCpuInit->pllMult) << RST_CLK_PLL_CONTROL_PLLMUL_Pos);

            /* activate PLL and wait till it stabilized */
            MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLLON;
            for (spinLockTimeout = 0; spinLockTimeout < RST_CLK_CLOCK_STABILIZATION_TIMEOUT; spinLockTimeout++)
            {
                if ((MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLLRDY) != 0)
                {
                    break;
                }
            }
            /* this is HW error if HSE is not stabilized in time */
            if (spinLockTimeout >= RST_CLK_CLOCK_STABILIZATION_TIMEOUT) {
                break;
            }
            /* store PLL speed */
            rccPllSpeed = rccPllSpeed * (rccCpuInit->pllMult + 1);
        }

        /*--------- setup CPU C2 ---------*/
        /* if PLL is selected for C2 clock source, we should ensure that PLL is running and stable */
        if (rccCpuInit->cpuC2Src == RST_CLK_CpuC2SelPllCpu)
        {
            if ((MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLLRDY) == 0) {
                break;
            }
            rccCpuC3Speed = rccPllSpeed;
        }
        else
        {
            rccCpuC3Speed = rccCpuC1Speed;
        }
        MDR_RST_CLK->CPU_CLOCK &= ~RST_CLK_CPU_CLOCK_CPUC2SEL_Msk;
        MDR_RST_CLK->CPU_CLOCK |= rccCpuInit->cpuC2Src;

        /*--------- setup CPU C3 divisor ---------*/
        MDR_RST_CLK->CPU_CLOCK &= ~RST_CLK_CPU_CLOCK_CPUC3SEL_Msk;
        MDR_RST_CLK->CPU_CLOCK |= (rccEncodeDivisor4bit(rccCpuInit->cpuC3Div) << RST_CLK_CPU_CLOCK_CPUC3SEL_Pos);
        rccCpuC3Speed = rccCpuC3Speed / rccEncodeDivisorNumeric(rccCpuInit->cpuC3Div);

        /*--------- setup HCLK ---------*/
        if (rccCpuInit->hclkSrc == RST_CLK_CPU_CLOCK_HCLKSEL_HSI)
        {
            /* use BKP domain to ensure that HSI is running */
            if (BKP_GenState(bkpHsi) != ENABLE)
            {
                break;
            }
        }
        MDR_RST_CLK->CPU_CLOCK &= ~RST_CLK_CPU_CLOCK_HCLKSEL_Msk;
        MDR_RST_CLK->CPU_CLOCK |= rccCpuInit->hclkSrc;

        /* store actual speed */
        RST_CLK_CpuSpeed = rccCpuC3Speed;
        switch (rccCpuInit->hclkSrc)
        {
        case RST_CLK_HclkSelHsi:
            RST_CLK_HclkSpeed = RST_CLK_HSI_FREQUENCY;
            break;
        case RST_CLK_HclkSelCpuC3: 
            RST_CLK_HclkSpeed = rccCpuC3Speed;
            break;
        case RST_CLK_HclkSelLse:
            RST_CLK_HclkSpeed = RST_CLK_LSI_FREQUENCY;
            break;
        case RST_CLK_HclkSelLsi:
            RST_CLK_HclkSpeed = RST_CLK_LSI_FREQUENCY;
            break;
        }

        erCode = SUCCESS;
    } while (0);

    /* if something goes wrong, we should return in safe mode - deactivate HSE and PLL and use plain HSI frequency */
    if (erCode == ERROR) {
        /* call of the backup register to activate HSI if it was deactivated */
        BKP_FreqGenCmd(bkpHsi, ENABLE, DISABLE);

        /* select clock source to run from HSI */
        MDR_RST_CLK->CPU_CLOCK &= ~RST_CLK_CPU_CLOCK_CPUC1SEL_Msk;
        MDR_RST_CLK->CPU_CLOCK |= RST_CLK_CPU_CLOCK_CPUC1SEL_HSI;
        MDR_RST_CLK->CPU_CLOCK &= ~RST_CLK_CPU_CLOCK_CPUC2SEL_Msk;
        MDR_RST_CLK->CPU_CLOCK |= RST_CLK_CPU_CLOCK_CPUC2SEL_CPUC1;

        /* disable PLL and HSE */
        MDR_RST_CLK->PLL_CONTROL &= ~RST_CLK_PLL_CONTROL_PLLON;
        MDR_RST_CLK->HS_CONTROL &= ~RST_CLK_HS_CONTROL_HSEON;
    }

    return erCode;
}

/**
  * @brief  setup clock source for hi-speed peripheral
  *         this function doesn't enable clock signal for peripheral, use rccEnablePeripheral function
  * @param  hsPeripheral - @ref RST_CLK_HsClks - peripheral that should be set up
  * @param  clockSource - @ref RST_CLK_HsClkSrc - clock source selector
  * @retval @ErrorStatus, ERROR if hi-speed frequency source (HSE or PLL) is not ready
  */
ErrorStatus RST_CLK_SetupHsPeripheralClock(RST_CLK_HsClks hsPeripheral, RST_CLK_HsClkSrc clockSource)
{
    uint32_t newSrc, clkSpeed;
    ErrorStatus erCode = SUCCESS;

    /* test input parameters */
    assert_param(RST_CLK_IS_HS_PERIPHERAL_CLOCK(hsPeripheral));
    assert_param(RST_CLK_IS_HS_CLK_SOURCE(clockSource));

    /* prepare new bit-encoded value */
    switch (clockSource)
    {
    case RST_CLK_ClkSrc_CPU_C1:
        newSrc = RST_CLK_HS_CLK_SRC_CPU_C1;
        clkSpeed = rccCpuC1Speed;
        break;
    case RST_CLK_ClkSrc_PER_OR_WDG_C1:
        newSrc = RST_CLK_HS_CLK_SRC_PER_C1;
        clkSpeed = rccPer1C1Speed;
        break;
    case RST_CLK_ClkSrc_PLLCPU:
        if ((MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLLRDY) == 0)
        {
            erCode = ERROR;
            break;
        }
        newSrc = RST_CLK_HS_CLK_SRC_PLLCPU;
        clkSpeed = rccPllSpeed;
        break;
    case RST_CLK_ClkSrc_HSE_HSI_CLK:
        if ((MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSERDY) == 0)
        {
            erCode = ERROR;
            break;
        }
        newSrc = RST_CLK_HS_CLK_SRC_HSECLK;
        clkSpeed = rccHseSpeed;
        break;
    default:
        break;
    }

    /* if hi-speed frequency source is valid, setup it within peripheral control registers */
    if (erCode == SUCCESS)
    {
        /* write new encoded value to the registers */
        switch (hsPeripheral)
        {
        case RST_CLK_Clk_ADC_C1:
            MDR_RST_CLK->ADC_CLOCK &= ~RST_CLK_ADC_CLOCK_ADCUIC1SEL_Msk;
            MDR_RST_CLK->ADC_CLOCK |= (newSrc << RST_CLK_ADC_CLOCK_ADCC1SEL_Pos);
            rccAdcC1Speed = clkSpeed;
            break;
        case RST_CLK_Clk_ADCUI_C1:
            MDR_RST_CLK->ADC_CLOCK &= ~RST_CLK_ADC_CLOCK_ADCUIC1SEL_Msk;
            MDR_RST_CLK->ADC_CLOCK |= (newSrc << RST_CLK_ADC_CLOCK_ADCUIC1SEL_Pos);
            rccAdcUIC1Speed = clkSpeed;
            break;
        case RST_CLK_Clk_WDG_C2:
            MDR_RST_CLK->PER1_CLOCK &= ~RST_CLK_PER_CLOCK_WDGC2SEL_Msk;
            MDR_RST_CLK->PER1_CLOCK |= (newSrc << RST_CLK_PER_CLOCK_WDGC2SEL_Pos);
            rccWwdgSpeed = clkSpeed;
            break;
        case RST_CLK_Clk_PER1_C2:
            MDR_RST_CLK->PER1_CLOCK &= ~RST_CLK_PER_CLOCK_PERC2SEL_Msk;
            MDR_RST_CLK->PER1_CLOCK |= (newSrc << RST_CLK_PER_CLOCK_PERC2SEL_Pos);
            RST_CLK_PER1C2_Speed = clkSpeed;
            break;
        default:
            break;
        }
    }

    return erCode;
}

/**
  * @brief  setup clock source for low-speed peripheral
  *         this function doesn't enable clock signal for peripheral, use rccEnablePeripheral function
  * @param  lsPeripheral - @ref RST_CLK_LsClks - peripheral that should be set up
  * @param  clockSource - @ref RST_CLK_LsClkSrc - clock source selector
  * @retval @ErrorStatus, ERROR if low-speed source is not ready
  */
ErrorStatus RST_CLK_SetupLsPeripheralCLock(RST_CLK_LsClks lsPeripheral, RST_CLK_LsClkSrc clockSource)
{
    uint32_t newSrc;
    ErrorStatus erCode = SUCCESS;

    /* test input parameters */
    assert_param(RST_CLK_IS_LS_PERIPHERAL_CLOCK(lsPeripheral));
    assert_param(RST_CLK_IS_LS_CLK_SOURCE(clockSource));

    /* ensure that LSE and LSI is valid */
    if (clockSource == RST_CLK_ClkSrc_LSI || clockSource == RST_CLK_ClkSrc_LSI_2)
    {
        if (BKP_GenState(bkpLsi) != ENABLE)
        {
            erCode = ERROR;
        }
    }
    else
    {
        if (BKP_GenState(bkpLse) != ENABLE)
        {
            erCode = ERROR;
        }
    }

    /* proceed only if generator is ON and stable */
    if (erCode == SUCCESS)
    {
        /* prepare new bit-encoded value */
        switch (clockSource)
        {
        case RST_CLK_ClkSrc_LSI:
            newSrc = RST_CLK_LS_CLK_SRC_LSI;
            break;
        case RST_CLK_ClkSrc_LSI_2:
            newSrc = RST_CLK_LS_CLK_SRC_LSI_2;
            break;
        case RST_CLK_ClkSrc_LSE:
            newSrc = RST_CLK_LS_CLK_SRC_LSE;
            break;
        case RST_CLK_ClkSrc_LSE_2:
            newSrc = RST_CLK_LS_CLK_SRC_LSE_2;
            break;
        default:
            break;
        }

        /* write new encoded value to the registers */
        switch (lsPeripheral)
        {
        case RST_CLK_Clk_WDG_C1:
            MDR_RST_CLK->PER1_CLOCK &= ~RST_CLK_PER_CLOCK_WDGC1SEL_Msk;
            MDR_RST_CLK->PER1_CLOCK |= (newSrc << RST_CLK_PER_CLOCK_WDGC1SEL_Pos);
            break;
        case RST_CLK_Clk_PER1_C1:
            MDR_RST_CLK->PER1_CLOCK &= ~RST_CLK_PER_CLOCK_PERC1SEL_Msk;
            MDR_RST_CLK->PER1_CLOCK |= (newSrc << RST_CLK_PER_CLOCK_PERC1SEL_Pos);
            break;
        default:
            break;
        }
    }

    return erCode;
}

/**
  * @brief  enable clock source for peripheral
  * @param  peripheral - @ref RST_CLK_Peripherals - peripheral to be enabled
  * @param  divisor - @ref RST_CLK_ClkDiv - divisor for C2 clock,
  *         this feature valid only for UART1,2,3,4, SSP1,2,3 and TIMER1,2,3,4, rtcHse, rtcHSI,
  *         WWDG, ADC, ADCUI for all other it will be ignored
  * @return actual peripheral clock in Hz
  */
uint32_t RST_CLK_EnablePeripheralClock(RST_CLK_Peripherals peripheral, RST_CLK_ClkDiv divisor)
{
    uint32_t value, offsetDiv, enPeripheral, enItem, perClk;

    /* test input parameters */
    assert_param(RST_CLK_IS_CLOCK_PERIPHERAL(peripheral));

    /* SSP1,2,3 */
    if (peripheral == RST_CLK_SSP1 || peripheral == RST_CLK_SSP2 || peripheral == RST_CLK_SSP3)
    {
        assert_param(RST_CLK_DIV_IS_3BITS(divisor));
        value = rccEncodeDivisor3bit(divisor);
        switch (peripheral)
        {
        case RST_CLK_SSP1:
            offsetDiv = RST_CLK_SSP_CLOCK_SSP1BRG_Pos;
            enItem = RST_CLK_SSP_CLOCK_SSP1CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_SPI1EN;
            break;
        case RST_CLK_SSP2:
            offsetDiv = RST_CLK_SSP_CLOCK_SSP2BRG_Pos;
            enItem = RST_CLK_SSP_CLOCK_SSP2CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_SPI2EN;
            break;
        case RST_CLK_SSP3:
            offsetDiv = RST_CLK_SSP_CLOCK_SSP3BRG_Pos;
            enItem = RST_CLK_SSP_CLOCK_SSP3CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_SPI3EN;
            break;
        default:
            break;
        }
        /* setup divisor */
        MDR_RST_CLK->SSP_CLOCK &= ~(RST_CLK_3BIT_DIV_Msk << offsetDiv);
        MDR_RST_CLK->SSP_CLOCK |= (value << offsetDiv);
        /* enable peripheral */
        MDR_RST_CLK->SSP_CLOCK |= enItem;
        MDR_RST_CLK->PER2_CLOCK |= enPeripheral;
        /* calculate peripheral clock */
        perClk = RST_CLK_PER1C2_Speed / rccEncodeDivisorNumeric(divisor);
    }
    /* UART1,2,3,4 */
    else if (peripheral == RST_CLK_UART1 || peripheral == RST_CLK_UART2 || peripheral == RST_CLK_UART3 || peripheral == RST_CLK_UART4)
    {
        assert_param(RST_CLK_DIV_IS_3BITS(divisor));
        value = rccEncodeDivisor3bit(divisor);
        switch (peripheral)
        {
        case RST_CLK_UART1:
            offsetDiv = RST_CLK_UART_CLOCK_UART1BRG_Pos;
            enItem = RST_CLK_UART_CLOCK_UART1CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_UART1EN;
            break;
        case RST_CLK_UART2:
            offsetDiv = RST_CLK_UART_CLOCK_UART2BRG_Pos;
            enItem = RST_CLK_UART_CLOCK_UART2CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_UART2EN;
            break;
        case RST_CLK_UART3:
            offsetDiv = RST_CLK_UART_CLOCK_UART3BRG_Pos;
            enItem = RST_CLK_UART_CLOCK_UART3CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_UART3EN;
            break;
        case RST_CLK_UART4:
            offsetDiv = RST_CLK_UART_CLOCK_UART4BRG_Pos;
            enItem = RST_CLK_UART_CLOCK_UART4CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_UART4EN;
            break;
        default:
            break;
        }
        /* setup divisor */
        MDR_RST_CLK->UART_CLOCK &= ~(RST_CLK_3BIT_DIV_Msk << offsetDiv);
        MDR_RST_CLK->UART_CLOCK |= (value << offsetDiv);
        /* enable peripheral */
        MDR_RST_CLK->UART_CLOCK |= enItem;
        MDR_RST_CLK->PER2_CLOCK |= enPeripheral;
        /* calculate peripheral clock */
        perClk = RST_CLK_PER1C2_Speed / rccEncodeDivisorNumeric(divisor);
    }
    /* TIMER1,2,3,4 */
    else if (peripheral == RST_CLK_TIMER1 || peripheral == RST_CLK_TIMER2 || peripheral == RST_CLK_TIMER3 || peripheral == RST_CLK_TIMER4)
    {
        assert_param(RST_CLK_DIV_IS_3BITS(divisor));
        value = rccEncodeDivisor3bit(divisor);
        switch (peripheral)
        {
        case RST_CLK_TIMER1:
            offsetDiv = RST_CLK_TIM_CLOCK_TIM1BRG_Pos;
            enItem = RST_CLK_TIM_CLOCK_TIM1CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_TIMER1EN;
            break;
        case RST_CLK_TIMER2:
            offsetDiv = RST_CLK_TIM_CLOCK_TIM2BRG_Pos;
            enItem = RST_CLK_TIM_CLOCK_TIM2CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_TIMER2EN;
            break;
        case RST_CLK_TIMER3:
            offsetDiv = RST_CLK_TIM_CLOCK_TIM3BRG_Pos;
            enItem = RST_CLK_TIM_CLOCK_TIM3CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_TIMER3EN;
            break;
        case RST_CLK_TIMER4:
            offsetDiv = RST_CLK_TIM_CLOCK_TIM4BRG_Pos;
            enItem = RST_CLK_TIM_CLOCK_TIM4CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_TIMER4EN;
            break;
        default:
            break;
        }
        /* setup divisor */
        MDR_RST_CLK->TIM_CLOCK &= ~(RST_CLK_3BIT_DIV_Msk << offsetDiv);
        MDR_RST_CLK->TIM_CLOCK |= (value << offsetDiv);
        /* enable peripheral */
        MDR_RST_CLK->TIM_CLOCK |= enItem;
        MDR_RST_CLK->PER2_CLOCK |= enPeripheral;
        /* calculate peripheral clock */
        perClk = RST_CLK_PER1C2_Speed / rccEncodeDivisorNumeric(divisor);
    }
    /* RTC HSI / HSE */
    else if (peripheral == RST_CLK_RTC_HSI || peripheral == RST_CLK_RTC_HSE)
    {
        assert_param(RST_CLK_DIV_IS_4BITS(divisor));
        value = rccEncodeDivisor4bit(divisor);
        switch (peripheral)
        {
        case RST_CLK_RTC_HSI:
            offsetDiv = RST_CLK_RTC_CLOCK_HSISEL_Pos;
            enItem = RST_CLK_RTC_CLOCK_HSIRTCEN;
            break;
        case RST_CLK_RTC_HSE:
            offsetDiv = RST_CLK_RTC_CLOCK_HSESEL_Pos;
            enItem = RST_CLK_RTC_CLOCK_HSERTCEN;
            break;
        default:
            break;
        }
        /* setup divisor */
        MDR_RST_CLK->RTC_CLOCK &= ~(RST_CLK_4BIT_DIV_Msk << offsetDiv);
        MDR_RST_CLK->RTC_CLOCK |= (value << offsetDiv);
        /* enable peripheral */
        MDR_RST_CLK->RTC_CLOCK |= enItem;
        MDR_RST_CLK->PER2_CLOCK |= RST_CLK_PER2_CLOCK_BKPEN;
        /* calculate peripheral clock */
        if (peripheral == RST_CLK_RTC_HSI) {
            perClk = RST_CLK_HSI_FREQUENCY;
        } else {
            perClk = rccHseSpeed;
        }
    }
    /* SAR ADC */
    else if (peripheral == RST_CLK_ADC || peripheral == RST_CLK_ADCUI)
    {
        assert_param(RST_CLK_DIV_IS_4BITS(divisor));
        value = rccEncodeDivisor4bit(divisor);
        switch (peripheral)
        {
        case RST_CLK_ADC:
            offsetDiv = RST_CLK_ADC_CLOCK_ADCC3SEL_Pos;
            enItem = RST_CLK_ADC_CLOCK_ADC_CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_ADCEN;
            break;
        case RST_CLK_ADCUI:
            offsetDiv = RST_CLK_ADC_CLOCK_ADCUIC3SEL_Pos;
            enItem = RST_CLK_ADC_CLOCK_ADCUI_CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_ADCUIEN;
            break;
        default:
            break;
        }
        /* setup divisor */
        MDR_RST_CLK->ADC_CLOCK &= ~(RST_CLK_4BIT_DIV_Msk << offsetDiv);
        MDR_RST_CLK->ADC_CLOCK |= (value << offsetDiv);
        /* enable peripheral */
        MDR_RST_CLK->ADC_CLOCK |= enItem;
        MDR_RST_CLK->PER2_CLOCK |= enPeripheral;
        /* calculate peripheral clock */
        if (peripheral == RST_CLK_ADC) {
            perClk = rccAdcC1Speed / rccEncodeDivisorNumeric(divisor);
        } else {
            perClk = rccAdcUIC1Speed / rccEncodeDivisorNumeric(divisor);
        }
    }
    /* windows watch dog */
    else if (peripheral == RST_CLK_WWDG)
    {
        assert_param(RST_CLK_DIV_IS_3BITS(divisor));
        value = rccEncodeDivisor3bit(divisor);
        MDR_RST_CLK->PER1_CLOCK &= ~(RST_CLK_4BIT_DIV_Msk << RST_CLK_PER_CLOCK_WDGBRG_Pos);
        MDR_RST_CLK->PER1_CLOCK |= (value << RST_CLK_PER_CLOCK_WDGBRG_Pos);
        MDR_RST_CLK->PER1_CLOCK |= RST_CLK_PER_CLOCK_WDGCLKEN;
        MDR_RST_CLK->PER2_CLOCK |= RST_CLK_PER2_CLOCK_WWDGEN;
        perClk = rccWwdgSpeed / rccEncodeDivisorNumeric(divisor);
    }
    /* DMA */
    else if (peripheral == RST_CLK_DMA)
    {
        MDR_RST_CLK->PER1_CLOCK |= RST_CLK_PER_CLOCK_DMAEN;
        MDR_RST_CLK->PER2_CLOCK |= RST_CLK_PER2_CLOCK_DMAEN;
        perClk = RST_CLK_HclkSpeed;
    }
    /* all other features are enabled without clock setup, it takes peripheral bus clock as is:
     * EEPROM,
     * RSTCLK,
     * I2C,
     * IWDG,
     * POWER,
     * PORTA,
     * PORTB,
     * PORTC,
     * CRC,
     * SENSORS,
     * CLKMEASURE
     * RANDOM
     * ISO7816
     * PORTD */
    else
    {
        /* we could use enumeration directly due to it's values taken from CMSIS */
        MDR_RST_CLK->PER2_CLOCK |= peripheral;
        perClk = RST_CLK_HclkSpeed;
    }

    return perClk;
}

/**
  * @brief  check state of the peripheral clock
  * @param  peripheral - @ref RST_CLK_Peripherals - peripheral to be checked
  * @return @ref FunctionalState - enabled or disabled state of the peripheral clock
  */
FunctionalState RST_CLK_IsPeripheralClockEnabled(RST_CLK_Peripherals peripheral)
{
	FunctionalState result;

    /* test input parameters */
    assert_param(RST_CLK_IS_CLOCK_PERIPHERAL(peripheral));

    if ((MDR_RST_CLK->PER2_CLOCK & peripheral) != 0) {
    	result = ENABLE;
    } else {
    	result = DISABLE;
    }

    return result;
}

/**
  * @brief  disable clock source for peripheral to save power
  * @param  peripheral - @ref RST_CLK_Peripherals - peripheral to be disabled
  */
void RST_CLK_DisablePeripheralClock(RST_CLK_Peripherals peripheral)
{
    uint32_t enItem, enPeripheral;

    /* test input parameters */
    assert_param(RST_CLK_IS_CLOCK_PERIPHERAL(peripheral));

    /* SSP1,2,3 */
    if (peripheral == RST_CLK_SSP1 || peripheral == RST_CLK_SSP2 || peripheral == RST_CLK_SSP3)
    {
        switch (peripheral)
        {
        case RST_CLK_SSP1:
            enItem = RST_CLK_SSP_CLOCK_SSP1CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_SPI1EN;
            break;
        case RST_CLK_SSP2:
            enItem = RST_CLK_SSP_CLOCK_SSP2CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_SPI2EN;
            break;
        case RST_CLK_SSP3:
            enItem = RST_CLK_SSP_CLOCK_SSP3CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_SPI3EN;
            break;
        default:
            break;
        }
        /* disable peripheral */
        MDR_RST_CLK->SSP_CLOCK &= ~enItem;
        MDR_RST_CLK->PER2_CLOCK &= ~enPeripheral;
    }
    /* UART1,2,3,4 */
    else if (peripheral == RST_CLK_UART1 || peripheral == RST_CLK_UART2 || peripheral == RST_CLK_UART3 || peripheral == RST_CLK_UART4)
    {
        switch (peripheral)
        {
        case RST_CLK_UART1:
            enItem = RST_CLK_UART_CLOCK_UART1CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_UART1EN;
            break;
        case RST_CLK_UART2:
            enItem = RST_CLK_UART_CLOCK_UART2CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_UART2EN;
            break;
        case RST_CLK_UART3:
            enItem = RST_CLK_UART_CLOCK_UART3CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_UART3EN;
            break;
        case RST_CLK_UART4:
            enItem = RST_CLK_UART_CLOCK_UART4CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_UART4EN;
            break;
        default:
            break;
        }
        /* enable peripheral */
        MDR_RST_CLK->UART_CLOCK &= ~enItem;
        MDR_RST_CLK->PER2_CLOCK &= ~enPeripheral;
    }
    /* TIMER1,2,3,4 */
    else if (peripheral == RST_CLK_TIMER1 || peripheral == RST_CLK_TIMER2 || peripheral == RST_CLK_TIMER3 || peripheral == RST_CLK_TIMER4)
    {
        switch (peripheral)
        {
        case RST_CLK_TIMER1:
            enItem = RST_CLK_TIM_CLOCK_TIM1CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_TIMER1EN;
            break;
        case RST_CLK_TIMER2:
            enItem = RST_CLK_TIM_CLOCK_TIM2CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_TIMER2EN;
            break;
        case RST_CLK_TIMER3:
            enItem = RST_CLK_TIM_CLOCK_TIM3CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_TIMER3EN;
            break;
        case RST_CLK_TIMER4:
            enItem = RST_CLK_TIM_CLOCK_TIM4CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_TIMER4EN;
            break;
        default:
            break;
        }
        /* enable peripheral */
        MDR_RST_CLK->TIM_CLOCK &= ~enItem;
        MDR_RST_CLK->PER2_CLOCK &= ~enPeripheral;
    }
    /* RTC HSI / HSE */
    else if (peripheral == RST_CLK_RTC_HSI || peripheral == RST_CLK_RTC_HSE)
    {
        switch (peripheral)
        {
        case RST_CLK_RTC_HSI:
            enItem = RST_CLK_RTC_CLOCK_HSIRTCEN;
            break;
        case RST_CLK_RTC_HSE:
            enItem = RST_CLK_RTC_CLOCK_HSERTCEN;
            break;
        default:
            break;
        }
        /* enable peripheral */
        MDR_RST_CLK->RTC_CLOCK &= ~enItem;
        MDR_RST_CLK->PER2_CLOCK &= ~RST_CLK_PER2_CLOCK_BKPEN;
    }
    /* SAR ADC */
    else if (peripheral == RST_CLK_ADC || peripheral == RST_CLK_ADCUI)
    {
        switch (peripheral)
        {
        case RST_CLK_ADC:
            enItem = RST_CLK_ADC_CLOCK_ADC_CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_ADCEN;
            break;
        case RST_CLK_ADCUI:
            enItem = RST_CLK_ADC_CLOCK_ADCUI_CLKEN;
            enPeripheral = RST_CLK_PER2_CLOCK_ADCUIEN;
            break;
        default:
            break;
        }
        /* enable peripheral */
        MDR_RST_CLK->ADC_CLOCK &= ~enItem;
        MDR_RST_CLK->PER2_CLOCK &= ~enPeripheral;
    }
    /* windows watch dog */
    else if (peripheral == RST_CLK_WWDG)
    {
        MDR_RST_CLK->PER1_CLOCK &= ~RST_CLK_PER_CLOCK_WDGCLKEN;
        MDR_RST_CLK->PER2_CLOCK &= ~RST_CLK_PER2_CLOCK_WWDGEN;
    }
    /* DMA */
    else if (peripheral == RST_CLK_DMA)
    {
        MDR_RST_CLK->PER1_CLOCK &= ~RST_CLK_PER_CLOCK_DMAEN;
        MDR_RST_CLK->PER2_CLOCK &= ~RST_CLK_PER2_CLOCK_DMAEN;
    }
    /* all other features are enabled without clock setup, it takes peripheral bus clock as is:
     * EEPROM,
     * RSTCLK,
     * I2C,
     * IWDG,
     * POWER,
     * PORTA,
     * PORTB,
     * PORTC,
     * CRC,
     * SENSORS,
     * CLKMEASURE
     * RANDOM
     * ISO7816
     * PORTD */
    else
    {
        /* we could use enumeration directly due to it's values taken from CMSIS */
        MDR_RST_CLK->PER2_CLOCK &= ~peripheral;
    }
}

/**
  * @brief  resets key RAM
  */
void RST_CLK_ResetKeyRAM(void)
{
    MDR_RST_CLK->PER1_CLOCK |= RST_CLK_PER_CLOCK_KEYRESPROG;
}

/** @} */ /* End of group RST_CLK_Exported_Functions */

/** @defgroup RST_CLK_Private_Functions
  * @{
  */

/**
  * @brief  encodes divisor in 3-bit format
  * @param  divisor - @ref RST_CLK_ClkDiv - divisor to be encoded
  * @return bit-encoded divisor
  */
static uint32_t rccEncodeDivisor3bit(RST_CLK_ClkDiv divisor)
{
    uint32_t res;

    switch (divisor)
    {
    case RST_CLK_Div1:
        res = RST_CLK_3BIT_DIV_1;
        break;
    case RST_CLK_Div2:
        res = RST_CLK_3BIT_DIV_2;
        break;
    case RST_CLK_Div4:
        res = RST_CLK_3BIT_DIV_4;
        break;
    case RST_CLK_Div8:
        res = RST_CLK_3BIT_DIV_8;
        break;
    case RST_CLK_Div16:
        res = RST_CLK_3BIT_DIV_16;
        break;
    case RST_CLK_Div32:
        res = RST_CLK_3BIT_DIV_32;
        break;
    case RST_CLK_Div64:
        res = RST_CLK_3BIT_DIV_64;
        break;
    case RST_CLK_Div128:
        res = RST_CLK_3BIT_DIV_128;
        break;
    default:
        res = 0;
        break;
    }

    return res;
}

/**
  * @brief  encodes divisor in 4-bit format
  * @param  divisor - @ref RST_CLK_ClkDiv - divisor to be encoded
  * @return bit-encoded divisor
  */
static uint32_t rccEncodeDivisor4bit(RST_CLK_ClkDiv divisor)
{
    uint32_t res;

    switch (divisor)
    {
    case RST_CLK_Div1:
        res = RST_CLK_4BIT_DIV_1;
        break;
    case RST_CLK_Div2:
        res = RST_CLK_4BIT_DIV_2;
        break;
    case RST_CLK_Div4:
        res = RST_CLK_4BIT_DIV_4;
        break;
    case RST_CLK_Div8:
        res = RST_CLK_4BIT_DIV_8;
        break;
    case RST_CLK_Div16:
        res = RST_CLK_4BIT_DIV_16;
        break;
    case RST_CLK_Div32:
        res = RST_CLK_4BIT_DIV_32;
        break;
    case RST_CLK_Div64:
        res = RST_CLK_4BIT_DIV_64;
        break;
    case RST_CLK_Div128:
        res = RST_CLK_4BIT_DIV_128;
        break;
    case RST_CLK_Div256:
        res = RST_CLK_4BIT_DIV_256;
        break;
    default:
        res = 0;
        break;
    }

    return res;
}

/**
  * @brief  encodes divisor as a number
  * @param  divisor - @ref RST_CLK_ClkDiv - divisor to be encoded
  * @return number equal to divisor
  */
static uint32_t rccEncodeDivisorNumeric(RST_CLK_ClkDiv divisor) {
    uint32_t res;

    switch (divisor)
    {
    case RST_CLK_Div1:
        res = 1;
        break;
    case RST_CLK_Div2:
        res = 2;
        break;
    case RST_CLK_Div4:
        res = 4;
        break;
    case RST_CLK_Div8:
        res = 8;
        break;
    case RST_CLK_Div16:
        res = 16;
        break;
    case RST_CLK_Div32:
        res = 32;
        break;
    case RST_CLK_Div64:
        res = 64;
        break;
    case RST_CLK_Div128:
        res = 128;
        break;
    case RST_CLK_Div256:
        res = 256;
        break;
    default:
        res = 1;
        break;
    }

    return res;
}

/** @} */ /* End of group RST_CLK_Private_Functions */

/** @} */ /* End of group RST_CLK */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_rst_clk.c
  */

