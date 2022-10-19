/**
  * FILE MLDR187_rst_clk.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_RST_CLK_H
#define __MLDR187_RST_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MLDR187_lib.h"
#include "MLDR187.h"

#include <stdint.h>

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup RST_CLK
  * @{
  */

/** @defgroup RST_CLK_Exported_Types
  * @{
  */

/**
  * @brief possible clock source for CPU_C2
  */
typedef enum
{
    RST_CLK_CpuC2SelCpuC1  = RST_CLK_CPU_CLOCK_CPUC2SEL_CPUC1,
    RST_CLK_CpuC2SelPllCpu = RST_CLK_CPU_CLOCK_CPUC2SEL_PLLCPU
} RST_CLK_CpuC2Src;

/**
  * @brief possible clock source for CPU_C1
  */
typedef enum
{
    RST_CLK_CpuC1SelHsi  = RST_CLK_CPU_CLOCK_CPUC1SEL_HSI,
    RST_CLK_CpuC1SelHsi2 = RST_CLK_CPU_CLOCK_CPUC1SEL_HSI_2,
    RST_CLK_CpuC1SelHse  = RST_CLK_CPU_CLOCK_CPUC1SEL_HSE,
    RST_CLK_CpuC1SelHse2 = RST_CLK_CPU_CLOCK_CPUC1SEL_HSE_2
} RST_CLK_CpuC1Src;

/**
  * @brief possible states of the HSE osc
  */
typedef enum
{
    RST_CLK_HseOff,                 /*!< HSE oscillator is off, HSI must be used */
    RST_CLK_HseOscillator,          /*!< HSE act as oscillator (XTAL) */
    RST_CLK_HseBypass               /*!< HSE act as external hi-speed generator input */
} RST_CLK_HseOscState;

/**
  * @brief possible states of the PLL module
  */
typedef enum
{
    RST_CLK_PllOff,                 /*!< PLL module is off */
    RST_CLK_PllFromHse,             /*!< PLL module is on and multiply HSE frequency */
    RST_CLK_PllFromCpuC1,           /*!< PLL module is on and multiply CPU C1 frequency */
} RST_CLK_PllState;

/**
  * @brief possible clock source for HCLK
  */
typedef enum
{
    RST_CLK_HclkSelHsi   = RST_CLK_CPU_CLOCK_HCLKSEL_HSI,
    RST_CLK_HclkSelCpuC3 = RST_CLK_CPU_CLOCK_HCLKSEL_CPUC3,
    RST_CLK_HclkSelLse   = RST_CLK_CPU_CLOCK_HCLKSEL_LSE,
    RST_CLK_HclkSelLsi   = RST_CLK_CPU_CLOCK_HCLKSEL_LSI
} RST_CLK_HclkSrc;

/**
  * @brief hi-speed peripherals
  */
typedef enum
{
    RST_CLK_Clk_ADC_C1,
    RST_CLK_Clk_ADCUI_C1,
    RST_CLK_Clk_WDG_C2,
    RST_CLK_Clk_PER1_C2
} RST_CLK_HsClks;

/**
  * @brief hi-speed clock sources for peripheral
  */
typedef enum
{
    RST_CLK_ClkSrc_CPU_C1,
    RST_CLK_ClkSrc_PER_OR_WDG_C1,
    RST_CLK_ClkSrc_PLLCPU,
    RST_CLK_ClkSrc_HSE_HSI_CLK
} RST_CLK_HsClkSrc;

/**
  * @brief low-speed peripherals
  */
typedef enum
{
    RST_CLK_Clk_WDG_C1,
    RST_CLK_Clk_PER1_C1,
} RST_CLK_LsClks;

/**
  * @brief low-speed clock sources for peripheral
  */
typedef enum
{
    RST_CLK_ClkSrc_LSI,
    RST_CLK_ClkSrc_LSI_2,
    RST_CLK_ClkSrc_LSE,
    RST_CLK_ClkSrc_LSE_2
} RST_CLK_LsClkSrc;

/**
  * @brief enumeration of the peripheral clock switch
  */
typedef enum
{
    RST_CLK_SSP1        = RST_CLK_PER2_CLOCK_SPI1EN,
    RST_CLK_UART1       = RST_CLK_PER2_CLOCK_UART1EN,
    RST_CLK_UART2       = RST_CLK_PER2_CLOCK_UART2EN,
    RST_CLK_EEPROM      = RST_CLK_PER2_CLOCK_EEPROMEN,
    RST_CLK_RSTCLK      = RST_CLK_PER2_CLOCK_RST_CLKEN,
    RST_CLK_DMA         = RST_CLK_PER2_CLOCK_DMAEN,
    RST_CLK_I2C         = RST_CLK_PER2_CLOCK_I2CEN,
    RST_CLK_UART3       = RST_CLK_PER2_CLOCK_UART3EN,
    RST_CLK_ADC         = RST_CLK_PER2_CLOCK_ADCEN,
    RST_CLK_WWDG        = RST_CLK_PER2_CLOCK_WWDGEN,
    RST_CLK_IWDG        = RST_CLK_PER2_CLOCK_IWDGEN,
    RST_CLK_POWER       = RST_CLK_PER2_CLOCK_POWEREN,
    RST_CLK_BKP         = RST_CLK_PER2_CLOCK_BKPEN,
    RST_CLK_ADCUI       = RST_CLK_PER2_CLOCK_ADCUIEN,
    RST_CLK_TIMER1      = RST_CLK_PER2_CLOCK_TIMER1EN,
    RST_CLK_TIMER2      = RST_CLK_PER2_CLOCK_TIMER2EN,
    RST_CLK_PORTA       = RST_CLK_PER2_CLOCK_PORTAEN,
    RST_CLK_PORTB       = RST_CLK_PER2_CLOCK_PORTBEN,
    RST_CLK_PORTC       = RST_CLK_PER2_CLOCK_PORTCEN,
    RST_CLK_CRC         = RST_CLK_PER2_CLOCK_CRCEN,
    RST_CLK_SENSORS     = RST_CLK_PER2_CLOCK_SENSORSEN,
    RST_CLK_CLKMEASURE  = RST_CLK_PER2_CLOCK_CLKMEASUREEN,
    RST_CLK_RANDOM      = RST_CLK_PER2_CLOCK_RANDOMEN,
    RST_CLK_ISO7816     = RST_CLK_PER2_CLOCK_ISO7816EN,
    RST_CLK_SSP2        = RST_CLK_PER2_CLOCK_SPI2EN,
    RST_CLK_SSP3        = RST_CLK_PER2_CLOCK_SPI3EN,
    RST_CLK_TIMER3      = RST_CLK_PER2_CLOCK_TIMER3EN,
    RST_CLK_TIMER4      = RST_CLK_PER2_CLOCK_TIMER4EN,
    RST_CLK_UART4       = RST_CLK_PER2_CLOCK_UART4EN,
    RST_CLK_PORTD       = RST_CLK_PER2_CLOCK_PORTDEN,
    RST_CLK_RTC_HSE,
    RST_CLK_RTC_HSI,
} RST_CLK_Peripherals;

/**
  * @brief possible peripherals clock divisors
  */
typedef enum
{
    RST_CLK_Div1,
    RST_CLK_Div2,
    RST_CLK_Div4,
    RST_CLK_Div8,
    RST_CLK_Div16,
    RST_CLK_Div32,
    RST_CLK_Div64,
    RST_CLK_Div128,
    RST_CLK_Div256
} RST_CLK_ClkDiv;

/**
  * @brief initialization structure for main MLDR187 core clock
  */
typedef struct
{
    RST_CLK_HseOscState hseState;   /*!< external oscillator state */
    uint32_t            hseSpeed;   /*!< HSE frequency in Hz, doesn't matter when HSE is off
                                         only if hseState != rccHseOff, must be from 8 000 000 to 16 000 000 */
    RST_CLK_CpuC1Src    cpuC1Src;   /*!< frequency source for the CPU C1 frequency */
    RST_CLK_PllState    pllState;   /*!< PLL module state (on/off and source frequency) */
    uint32_t            pllMult;    /*!< PLL multiplication factor, doesn't matter when PLL is off
                                         MUST be less or equal than 7, resulting frequency MUST NOT exceed 60 MHz */
    RST_CLK_CpuC2Src    cpuC2Src;   /*!< frequency source for the CPU C2 frequency */
    RST_CLK_ClkDiv      cpuC3Div;   /*!< frequency divisor for the CPU clock, up to 256 */
    RST_CLK_HclkSrc     hclkSrc;    /*!< frequency source for the HCLK */
} RST_CLK_CpuSpeed_InitTypeDef;

/** @} */ /* End of group RST_CLK_Exported_Types */

/** @defgroup RST_CLK_Exported_Constants
  * @{
  */

/* default HSI frequency is 8MHz */
#define RST_CLK_HSI_FREQUENCY               8000000U

/* default LSI frequency is 32kHz */
#define RST_CLK_LSI_FREQUENCY               32768U

/** @} */ /* End of group RST_CLK_Exported_Constants */

/** @defgroup RST_CLK_Exported_Variables
  * @{
  */

/* CPU speed (this variable will be updated during configuration) */
extern uint32_t RST_CLK_CpuSpeed;

/* HCLK speed (this variable will be updated during configuration) */
extern uint32_t RST_CLK_HclkSpeed;

/* peripheral source clock speed (for legacy interface support) */
extern uint32_t RST_CLK_PER1C2_Speed;

/** @} */ /* End of group RST_CLK_Exported_Variables */

/** @defgroup RST_CLK_Exported_Macros
  * @{
  */

/* macro for 3-bit encoded clock divisor */
#define RST_CLK_DIV_IS_3BITS(DIVISOR)       (((DIVISOR) == RST_CLK_Div1) || \
                                             ((DIVISOR) == RST_CLK_Div2) || \
                                             ((DIVISOR) == RST_CLK_Div4) || \
                                             ((DIVISOR) == RST_CLK_Div8) || \
                                             ((DIVISOR) == RST_CLK_Div16) || \
                                             ((DIVISOR) == RST_CLK_Div32) || \
                                             ((DIVISOR) == RST_CLK_Div64) || \
                                             ((DIVISOR) == RST_CLK_Div128))

/* macro for 3-bit encoded clock divisor */
#define RST_CLK_DIV_IS_4BITS(DIVISOR)       ((RST_CLK_DIV_IS_3BITS(DIVISOR)) || \
                                             ((DIVISOR) == RST_CLK_rccDiv256))

/** @} */ /* End of group RST_CLK_Exported_Macros */

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
ErrorStatus RST_CLK_SetupCpuSpeed(RST_CLK_CpuSpeed_InitTypeDef* rccCpuInit);

/**
  * @brief  setup clock source for hi-speed peripheral
  *         this function doesn't enable clock signal for peripheral, use rccEnablePeripheral function
  * @param  hsPeripheral - @ref RST_CLK_HsClks - peripheral that should be set up
  * @param  clockSource - @ref RST_CLK_HsClkSrc - clock source selector
  * @retval @ErrorStatus, ERROR if hi-speed frequency source (HSE or PLL) is not ready
  */
ErrorStatus RST_CLK_SetupHsPeripheralClock(RST_CLK_HsClks hsPeripheral, RST_CLK_HsClkSrc clockSource);

/**
  * @brief  setup clock source for low-speed peripheral
  *         this function doesn't enable clock signal for peripheral, use rccEnablePeripheral function
  * @param  lsPeripheral - @ref RST_CLK_LsClks - peripheral that should be set up
  * @param  clockSource - @ref RST_CLK_LsClkSrc - clock source selector
  * @retval @ErrorStatus, ERROR if low-speed source is not ready
  */
ErrorStatus RST_CLK_SetupLsPeripheralCLock(RST_CLK_LsClks lsPeripheral, RST_CLK_LsClkSrc clockSource);

/**
  * @brief  enable clock source for peripheral
  * @param  peripheral - @ref RST_CLK_Peripherals - peripheral to be enabled
  * @param  divisor - @ref RST_CLK_ClkDiv - divisor for C2 clock,
  *         this feature valid only for UART1,2,3,4, SSP1,2,3 and TIMER1,2,3,4, rtcHse, rtcHSI,
  *         WWDG, ADC, ADCUI for all other it will be ignored
  * @return actual peripheral clock in Hz
  */
uint32_t RST_CLK_EnablePeripheralClock(RST_CLK_Peripherals peripheral, RST_CLK_ClkDiv divisor);

/**
  * @brief  check state of the peripheral clock
  * @param  peripheral - @ref RST_CLK_Peripherals - peripheral to be checked
  * @return @ref FunctionalState - enabled or disabled state of the peripheral clock
  */
FunctionalState RST_CLK_IsPeripheralClockEnabled(RST_CLK_Peripherals peripheral);

/**
  * @brief  disable clock source for peripheral to save power
  * @param  peripheral - @ref RST_CLK_Peripherals - peripheral to be disabled
  */
void RST_CLK_DisablePeripheralClock(RST_CLK_Peripherals peripheral);

/**
  * @brief  resets key RAM
  */
void RST_CLK_ResetKeyRAM(void);

/** @} */ /* End of group RST_CLK_Exported_Functions */

/** @} */ /* End of group RST_CLK */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} /* extern "C" block end */
#endif

#endif /* __MLDR187_RST_CLK_H */

/**
 * END OF FILE MLDR187_rst_clk.h
 */

