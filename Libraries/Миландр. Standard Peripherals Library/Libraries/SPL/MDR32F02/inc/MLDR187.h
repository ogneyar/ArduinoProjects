/**
  ******************************************************************************
  * @file    MLDR187.h
  * @author
  * @version
  * @date
  * @brief   MLDR187 Device Peripheral Access Layer Header File.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - peripherals registers declarations and bits definition
  *           - Macros to access peripheral registers hardware
  ******************************************************************************
  */

#ifndef __MLDR187_HWDEF_H
#define __MLDR187_HWDEF_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include <stdint.h>

#ifndef __IO
#define     __IO    volatile
#endif /* __IO */

/**
 *  @brief  MLDR187 Interrupt Number Definition,
 *          int_globalX, where X - enumerated number of the interrupt
 */
typedef enum
{
    DMA_IRQn                            = 0,    /*!< DMA_ERR, DMA_DONE */
    UART1_IRQn                          = 1,    /*!< UART1 INTR */
    UART2_IRQn                          = 2,    /*!< UART2 INTR */
    SSP1_IRQn                           = 3,    /*!< SSP1 INTR */
    POWER_IRQn                          = 4,    /*!< POWER detector */
    WWDG_IRQn                           = 5,    /*!< WWDG */
    TIM1_IRQn                           = 6,    /*!< Timer1 STATUS, IE */
    TIM2_IRQn                           = 7,    /*!< Timer2 STATUS, IE */
    ADC_IRQn                            = 8,    /*!< ADC EOCIF_1, AWOIF_1, EOCIF_2, AWOIF_2 */
    I2C_IRQn                            = 9,    /*!< I2C INT */
    BACKUP_IRQn                         = 10,   /*!< BKP and RTC */
    EXT1_IRQn                           = 11,   /*!< PA[10] in main mode */
    EXT2_IRQn                           = 12,   /*!< PC[4], PB[6] in alternative mode */
    EXT3_IRQn                           = 13,   /*!< PC[5], PB[7] in alternative mode */
    ADCUI03_IRQn                        = 14,   /*!< S-D ADC channels 0, 3 */
    ADCUI1_IRQn                         = 15,   /*!< S-D ADC channel 1 */
    ADCUI2_IRQn                         = 16,   /*!< S-D ADC channel 2 */
    LBLOCK_IRQn                         = 17,   /*!< security LBLOCK */
    RFU_IRQn                            = 18,
    SENSORS_IRQn                        = 19,   /*!< security sensors */
    CLKMEAUSRE_IRQn                     = 20,   /*!< security frequency measurement */
    RANDOM_IRQn                         = 21,   /*!< random number generator */
    ISO7816_IRQn                        = 22,   /*!< ISO7816 interface */
    UART3_IRQn                          = 23,   /*!< UART3 INTR */
    SSP2_IRQn                           = 24,   /*!< SSP2 INTR */
    SSP3_IRQn                           = 25,   /*!< SSP3 INTR */
    TIM3_IRQn                           = 26,   /*!< Timer3 STATUS, IE */
    TIM4_IRQn                           = 27,   /*!< Timer4 STATUS, IE */
    UART4_IRQn                          = 28,   /*!< UART4 INTR */
    OTP_IRQn                            = 29    /*!< OTP CRC corrupt */
} IRQn_Type;

/**
 *  @brief	MDLR187 interrupt priorities
 */
typedef enum
{
    IRQn_off                            = 0,    /*!< interrupt disabled */
    IRQn_priority_lowest                = 1,
    IRQn_priority_low                   = 2,
    IRQn_priority_below_average         = 3,
    IRQn_priority_average               = 4,
    IRQn_priority_above_average         = 5,
    IRQn_priority_high                  = 6,
    IRQn_priority_highest               = 7
} IRQn_PriorityLevel;

/*!< Peripherals base addresses */
#define MDR_BOOT_OTP_BASE               0x00020000U
#define MDR_CLINT_BASE                  0x02000000U
#define MDR_CLINT_TIMER_CMP             0x02004000U
#define MDR_CLINT_TIMER                 0x0200BFF8U
#define MDR_PLIC_PRI_BASE               0x0C000004U
#define MDR_PLIC_IRM                    0x0C001000U
#define MDR_PLIC_IEM                    0x0C002000U
#define MDR_PLIC_THR                    0x0C200000U
#define MDR_PLIC_ICC                    0x0C200004U
#define MDR_FLASH_BASE                  0x10000000U
#define MDR_RAM_BASE                    0x20000000U
#define MDR_SPI1_BASE                   0x40000000U
#define MDR_UART1_BASE                  0x40008000U
#define MDR_UART2_BASE                  0x40010000U
#define MDR_EEPROM_CTRL_BASE            0x40018000U
#define MDR_RST_CLK_BASE                0x40020000U
#define MDR_DMA_BASE                    0x40028000U
#define MDR_I2C_BASE                    0x40030000U
#define MDR_UART3_BASE                  0x40038000U
#define MDR_ADC_BASE                    0x40040000U
#define MDR_WWDG_BASE                   0x40048000U
#define MDR_IWDG_BASE                   0x40050000U
#define MDR_POWER_BASE                  0x40058000U
#define MDR_BKP_BASE                    0x40060000U
#define MDR_ADCUI_BASE                  0x40068000U
#define MDR_TIMER1_BASE                 0x40070000U
#define MDR_TIMER2_BASE                 0x40078000U
#define MDR_GPIO1_BASE                  0x40080000U
#define MDR_GPIO2_BASE                  0x40088000U
#define MDR_GPIO3_BASE                  0x40090000U
#define MDR_CRC_BASE                    0x40098000U
#define MDR_SENSORS_BASE                0x400A8000U
#define MDR_CLK_MEASURE_BASE            0x400B0000U
#define MDR_RANDOM_BASE                 0x400B8000U
#define MDR_ISO7816_BASE                0x400C0000U
#define MDR_SPI2_BASE                   0x400C8000U
#define MDR_SPI3_BASE                   0x400D0000U
#define MDR_TIMER3_BASE                 0x400D8000U
#define MDR_TIMER4_BASE                 0x400E0000U
#define MDR_UART4_BASE                  0x400E8000U
#define MDR_GPIO4_BASE                  0x400F0000U
#define MDR_L_BLOCK_BASE                0x60004000U
#define MDR_S_BLOCK0_BASE               0x60008000U
#define MDR_S_BLOCK1_BASE               0x6000C000U
#define MDR_S_BLOCK2_BASE               0x60010000U
#define MDR_S_BLOCK3_BASE               0x60014000U
#define MDR_S_BLOCK4_BASE               0x60018000U
#define MDR_S_BLOCK5_BASE               0x6001C000U
#define MDR_S_BLOCK6_BASE               0x60020000U
#define MDR_S_BLOCK7_BASE               0x60024000U
#define MDR_P_BYTE_BASE                 0x60028000U
#define MDR_P_BIT0_BASE                 0x6002C000U
#define MDR_P_BIT1_BASE                 0x60030000U
#define MDR_P_BIT2_BASE                 0x60034000U
#define MDR_P_BIT3_BASE                 0x60038000U
#define MDR_OTP_MEM_BASE                0x70000000U
#define MDR_OTP_REG_BASE                0x70010000U
#define MDR_SYSTEM_RAM_TCMA             0x80000000U
#define MDR_SYSTEM_RAM_TCMB             0x80010000U

/*
 * ==========================================================================
 * ---------------------- Register structures -------------------------------
 * ==========================================================================
 */

/**
  * @brief  SSP control registers
  */
typedef struct
{
    __IO uint32_t CR0;                  /*!< control register */
    __IO uint32_t CR1;                  /*!< additional control register */
    __IO uint32_t DR;                   /*!< FIFO read and FIFO write */
    __IO uint32_t SR;                   /*!< status register */
    __IO uint32_t CPSR;                 /*!< prescaler register */
    __IO uint32_t IMSC;                 /*!< interrupt mask register */
    __IO uint32_t RIS;                  /*!< interrupt status (without mask) */
    __IO uint32_t MIS;                  /*!< interrupt status (with mask) */
    __IO uint32_t ICR;                  /*!< interrupt clear register */
    __IO uint32_t DMACR;                /*!< SSP DMA control register */
} MDR_SSP_TypeDef;

/**
  * @brief  UART control registers
  */
typedef struct
{
    __IO uint32_t DR;                   /*!< input / output FIFO data register */
    __IO uint32_t RSR_ECR;              /*!< receiver status and error clear register */
    __IO uint32_t RFU1;
    __IO uint32_t RFU2;
    __IO uint32_t RFU3;
    __IO uint32_t RFU4;
    __IO uint32_t FR;                   /*!< flag register */
    __IO uint32_t RFU5;
    __IO uint32_t ILPR;                 /*!< low-power infrared control */
    __IO uint32_t IBRD;                 /*!< integer part of divisor */
    __IO uint32_t FBRD;                 /*!< fraction part of divisor */
    __IO uint32_t LCR_H;                /*!< line control register */
    __IO uint32_t CR;                   /*!< control register */
    __IO uint32_t IFLS;                 /*!< FIFO fill threshold */
    __IO uint32_t IMSC;                 /*!< interrupt mask */
    __IO uint32_t RIS;                  /*!< interrupt state */
    __IO uint32_t MIS;                  /*!< masked interrupt state */
    __IO uint32_t ICR;                  /*!< interrupt clear register */
    __IO uint32_t DMACR;                /*!< DMA control register */
    __IO uint32_t RFU6[13];
    __IO uint32_t TCR;                  /*!< test control register */
} MDR_UART_TypeDef;

/**
  * @brief  EEPROM control registers
  */
typedef struct
{
    __IO uint32_t CMD;                  /*!< control register - 0x00 */
    __IO uint32_t ADR;                  /*!< address register - 0x04 */
    __IO uint32_t DI;                   /*!< input data register - 0x08 */
    __IO uint32_t DO;                   /*!< output data register - 0x0C */
    __IO uint32_t KEY;                  /*!< key register - 0x10 */
} MDR_EEPROM_CTRL_TypeDef;

/**
  * @brief Reset and Clock Control
  */

typedef struct
{
    __IO uint32_t CLOCK_STATUS;         /*!< Frequency status register */
    __IO uint32_t PLL_CONTROL;          /*!< PLL control register */
    __IO uint32_t HS_CONTROL;           /*!< Hi speed oscillator control register */
    __IO uint32_t CPU_CLOCK;            /*!< CPU speed control register */
    __IO uint32_t PER1_CLOCK;           /*!< Peripherals(1) speed control register */
    __IO uint32_t ADC_CLOCK;            /*!< Analog-to-digital control register */
    __IO uint32_t RTC_CLOCK;            /*!< Real-time clock speed register */
    __IO uint32_t PER2_CLOCK;           /*!< Peripherals(2) speed control register */
    __IO uint32_t RFU;                  /*!< ??? */
    __IO uint32_t TIM_CLOCK;            /*!< Timers clock control register */
    __IO uint32_t UART_CLOCK;           /*!< UARTs clock control register */
    __IO uint32_t SSP_CLOCK;            /*!< SSPs clock control register */
} MDR_RST_CLK_TypeDef;

/**
  * @brief DMA Channel
  */

typedef struct {
    __IO uint32_t SRC;                  /*!< source end pointer */
    __IO uint32_t DST;                  /*!< destination end pointer */
    __IO uint32_t CFG;                  /*!< configuration register */
    __IO uint32_t RFU;                  /*!< unused */
} MDR_DMAChannel_TypeDef;

/**
  * @brief DMA
  */

typedef struct {
    __IO uint32_t STATUS;               /*!< status register */
    __IO uint32_t CFG;                  /*!< configuration register */
    __IO uint32_t CTRL_BASE_PTR;        /*!< location groop of base registers (MUST be set) */
    __IO uint32_t ALT_CTRL_BASE_PTR;    /*!< location groop of alt registers (read only) */
    __IO uint32_t WAITONREG_STATUS;     /*!< register for waiting requests */
    __IO uint32_t CHNL_SW_REQUESTS;     /*!< software requests */
    __IO uint32_t CHNL_USEBURST_SET;    /*!< setup register for a packet exchange */
    __IO uint32_t CHNL_USEBURST_CLR;    /*!< clear register for a packet exchange */
    __IO uint32_t CHNL_REQMASK_SET;     /*!< setup register for a requests masks */
    __IO uint32_t CHNL_REQMASK_CLR;     /*!< clear register for a requests masks */
    __IO uint32_t CHNL_ENABLE_SET;      /*!< setup register for a channel enable switch */
    __IO uint32_t CHNL_ENABLE_CLR;      /*!< clear register for a channel enable switch */
    __IO uint32_t CHNL_PRIALT_SET;      /*!< setup register for a primary/alternate config */
    __IO uint32_t CHNL_PRIALT_CLR;      /*!< clear register for a primary/alternate config */
    __IO uint32_t CHNL_PRIORITY_SET;    /*!< setup register for a channel priority */
    __IO uint32_t CHNL_PRIORITY_CLR;    /*!< clear register for a channel priority */
    __IO uint32_t RFU1;
    __IO uint32_t RFU2;
    __IO uint32_t RFU3;
    __IO uint32_t ERR_CLR;              /*!< clear register for a error flags */
} MDR_DMA_TypeDef;

/**
  * @brief I2C
  */

typedef struct {
    __IO uint32_t PRL;                  /*!< lower-part of the preloader */
    __IO uint32_t PRH;                  /*!< higher-part of the preloader */
    __IO uint32_t CTR;                  /*!< control register */
    __IO uint32_t RXD;                  /*!< last received byte */
    __IO uint32_t STA;                  /*!< status register */
    __IO uint32_t TXD;                  /*!< next byte to be transmitted */
    __IO uint32_t CMD;                  /*!< command for I2C module */
} MDR_I2C_TypeDef;

/**
  * @brief SAR ADC
  */

typedef struct {
    __IO uint32_t CFG;                  /*!< Configuration register - 0x00 */
    __IO uint32_t RFU;                  /*!< 0x04 */
    __IO uint32_t HLEVEL;               /*!< Hi level of the 'normal' ADC value - 0x08 */
    __IO uint32_t RFU1;                 /*!< 0x0C */
    __IO uint32_t LLEVEL;               /*!< Low level of the 'normal' ADC value - 0x10 */
    __IO uint32_t RFU2;                 /*!< 0x14 */
    __IO uint32_t RESULT;               /*!< Result register for the ADC - 0x18 */
    __IO uint32_t RFU3;                 /*!< 0x18 */
    __IO uint32_t STATUS;               /*!< Status register for the ADC - 0x20 */
    __IO uint32_t RFU4;                 /*!< 0x24 */
    __IO uint32_t CHSEL;                /*!< Channel selection - 0x28 */
    __IO uint32_t RFU5;                 /*!< 0x2C */
    __IO uint32_t TRIM;                 /*!< Temp trimming - 0x30 */
} MDR_ADC_TypeDef;

/**
  * @brief window watch dog timer
  */

typedef struct {
    __IO uint32_t CR;                   /*!< control register */
    __IO uint32_t CFR;                  /*!< configuration register */
    __IO uint32_t SR;                   /*!< status register */
} MDR_WWDG_TypeDef;

/**
  * @brief independent watch dog timer
  */

typedef struct {
    __IO uint32_t KR;                   /*!< key register */
    __IO uint32_t PR;                   /*!< predivisor */
    __IO uint32_t RLR;                  /*!< counter */
    __IO uint32_t SR;                   /*!< status register */
} MDR_IWDG_TypeDef;

/**
  * @brief POWER monitor
  */

typedef struct {
    __IO uint32_t PVDCS;                /*!< POWER monitor control */
} MDR_POWER_TypeDef;

/**
  * @brief Battery domain (BKP) Controller
  */

typedef struct
{
    __IO uint32_t WPR;                  /*!< BKP protection key register */
    __IO uint32_t LDO;                  /*!< BKP LDO control register */
    __IO uint32_t CLK;                  /*!< BKP frequency control register */
    __IO uint32_t RTC;                  /*!< BKP RTC control register */
    __IO uint32_t WUTR;                 /*!< RTC sleep exit control register */
    __IO uint32_t PREDIV_S;             /*!< RTC predivision register */
    __IO uint32_t PRL;                  /*!< RTC Real time load (base for RTC) register */
    __IO uint32_t ALRM;                 /*!< RTC sleep exit control reference register */
    __IO uint32_t CS;                   /*!< RTC control and flags register */
    __IO uint32_t TR;                   /*!< RTC time register */
    __IO uint32_t DR;                   /*!< RTC date register */
    __IO uint32_t ALRMAR;               /*!< RTC ALARM A reference register */
    __IO uint32_t ALRMBR;               /*!< RTC ALARM B reference register */
    __IO uint32_t TSTR1;                /*!< Tamper1 timestamp */
    __IO uint32_t TSTR2;                /*!< Tamper2 timestamp */
    __IO uint32_t TSTR3;                /*!< Tamper3 timestamp */
    __IO uint32_t TSDR1;                /*!< Tamper1 datestamp */
    __IO uint32_t TSDR2;                /*!< Tamper2 datestamp */
    __IO uint32_t TSDR3;                /*!< Tamper3 datestamp */
    __IO uint32_t TAFCR;                /*!< Tamper control register */
    __IO uint32_t MEM;                  /*!< Synthetic register - start of the BKP memory */
} MDR_BKP_TypeDef;

/**
  * @brief Sigma-Delta ADC
  */

typedef struct
{
    __IO uint32_t CTRL1;                /*!< control register 1 */
    __IO uint32_t CTRL2;                /*!< control register 2 */
    __IO uint32_t CTRL3;                /*!< control register 3 */

    __IO uint32_t F0CTR;                /*!< control for channel F0 */
    __IO uint32_t F0WC;                 /*!< control for active power for channel F0 */
    __IO uint32_t F0WATTP;              /*!< positive active power for channel F0 (bits [57..25]) */
    __IO uint32_t F0WATTN;              /*!< negative active power for channel F0 (bits [57..25]) */
    __IO uint32_t F0VC;                 /*!< control for reactive power for channel F0 */
    __IO uint32_t F0VARP;               /*!< positive reactive power for channel F0 (bits [57..25]) */
    __IO uint32_t F0VARN;               /*!< negative active power for channel F0 (bits [57..25]) */
    __IO uint32_t F0AC;                 /*!< control for full power for channel F0 */
    __IO uint32_t F0VR;                 /*!< full power for channel F0 (bits [57..25]) */
    __IO uint32_t F0MD0;                /*!< parameters 0 for channel F0 */
    __IO uint32_t F0MD1;                /*!< parameters 1 for channel F0 */
    __IO uint32_t F0VPEAK;              /*!< peak voltage for channel F0 */
    __IO uint32_t F0IPEAK;              /*!< peak current for channel F0 */
    __IO uint32_t F0VDAT;               /*!< voltage RAW data for channel F0 */
    __IO uint32_t F0I0DAT;              /*!< current RAW data for channel F0 and subchannel I0 */
    __IO uint32_t F0I3DAT;              /*!< current RAW data for channel F0 and subchannel I3 */
    __IO uint32_t F0VRMS;               /*!< voltage RMS for channel F0 */
    __IO uint32_t F0VRMS2;              /*!< square of voltage RMS for channel F0 */
    __IO uint32_t F0IRMS;               /*!< current RMS for channel F0 */
    __IO uint32_t F0IRMS2;              /*!< square of current RMS for channel F0 */
    __IO uint32_t F0STAT;               /*!< state of the channel F0 */
    __IO uint32_t F0MASK;               /*!< interrupt mask for channel F0 */

    __IO uint32_t F1CTR;                /*!< control for channel F1 */
    __IO uint32_t F1WC;                 /*!< control for active power for channel F1 */
    __IO uint32_t F1WATTP;              /*!< positive active power for channel F1 (bits [57..25]) */
    __IO uint32_t F1WATTN;              /*!< negative active power for channel F1 (bits [57..25]) */
    __IO uint32_t F1VC;                 /*!< control for reactive power for channel F1 */
    __IO uint32_t F1VARP;               /*!< positive reactive power for channel F1 (bits [57..25]) */
    __IO uint32_t F1VARN;               /*!< negative active power for channel F1 (bits [57..25]) */
    __IO uint32_t F1AC;                 /*!< control for full power for channel F1 */
    __IO uint32_t F1VR;                 /*!< full power for channel F1 (bits [57..25]) */
    __IO uint32_t F1MD0;                /*!< parameters 0 for channel F1 */
    __IO uint32_t F1MD1;                /*!< parameters 1 for channel F1 */
    __IO uint32_t F1MD2;                /*!< parameters 2 for channel F1 */
    __IO uint32_t F1VPEAK;              /*!< peak voltage for channel F1 */
    __IO uint32_t F1IPEAK;              /*!< peak current for channel F1 */
    __IO uint32_t F1VDAT;               /*!< voltage RAW data for channel F1 */
    __IO uint32_t F1IDAT;              /*!< current RAW data for channel F1 */
    __IO uint32_t F1VRMS;               /*!< voltage RMS for channel F1 */
    __IO uint32_t F1VRMS2;              /*!< square of voltage RMS for channel F1 */
    __IO uint32_t F1IRMS;               /*!< current RMS for channel F1 */
    __IO uint32_t F1IRMS2;              /*!< square of current RMS for channel F1 */
    __IO uint32_t F1STAT;               /*!< state of the channel F1 */
    __IO uint32_t F1MASK;               /*!< interrupt mask for channel F1 */

    __IO uint32_t F2CTR;                /*!< control for channel F2 */
    __IO uint32_t F2WC;                 /*!< control for active power for channel F2 */
    __IO uint32_t F2WATTP;              /*!< positive active power for channel F2 (bits [57..25]) */
    __IO uint32_t F2WATTN;              /*!< negative active power for channel F2 (bits [57..25]) */
    __IO uint32_t F2VC;                 /*!< control for reactive power for channel F2 */
    __IO uint32_t F2VARP;               /*!< positive reactive power for channel F2 (bits [57..25]) */
    __IO uint32_t F2VARN;               /*!< negative active power for channel F2 (bits [57..25]) */
    __IO uint32_t F2AC;                 /*!< control for full power for channel F2 */
    __IO uint32_t F2VR;                 /*!< full power for channel F2 (bits [57..25]) */
    __IO uint32_t F2MD0;                /*!< parameters 0 for channel F2 */
    __IO uint32_t F2MD1;                /*!< parameters 1 for channel F2 */
    __IO uint32_t F2MD2;                /*!< parameters 2 for channel F2 */
    __IO uint32_t F2VPEAK;              /*!< peak voltage for channel F2 */
    __IO uint32_t F2IPEAK;              /*!< peak current for channel F2 */
    __IO uint32_t F2VDAT;               /*!< voltage RAW data for channel F2 */
    __IO uint32_t F2IDAT;              /*!< current RAW data for channel F2 */
    __IO uint32_t F2VRMS;               /*!< voltage RMS for channel F2 */
    __IO uint32_t F2VRMS2;              /*!< square of voltage RMS for channel F2 */
    __IO uint32_t F2IRMS;               /*!< current RMS for channel F2 */
    __IO uint32_t F2IRMS2;              /*!< square of current RMS for channel F2 */
    __IO uint32_t F2STAT;               /*!< state of the channel F2 */
    __IO uint32_t F2MASK;               /*!< interrupt mask for channel F2 */

    __IO uint32_t CCAL1;                /*!< register 1 for current calibration */
    __IO uint32_t CCAL2;                /*!< register 2 for current calibration */
    __IO uint32_t CCAL3;                /*!< register 3 for current calibration */
    __IO uint32_t CCAL4;                /*!< register 4 for current calibration */
    __IO uint32_t F0IRMS_INACTIVE;      /*!< current RMS for inactive current channel */

    __IO uint32_t F0WATTP_L;            /*!< positive active power in channel F0 (bits [24..0]) */
    __IO uint32_t F0WATTN_L;            /*!< negative active power in channel F0 (bits [24..0]) */
    __IO uint32_t F0VARP_L;             /*!< positive reactive power in channel F0 (bits [24..0]) */
    __IO uint32_t F0VARN_L;             /*!< negative reactive power in channel F0 (bits [24..0]) */
    __IO uint32_t F0VR_L;               /*!< full power in channel F0 (bits [24..0]) */
    __IO uint32_t F1WATTP_L;            /*!< positive active power in channel F1 (bits [24..0]) */
    __IO uint32_t F1WATTN_L;            /*!< negative active power in channel F1 (bits [24..0]) */
    __IO uint32_t F1VARP_L;             /*!< positive reactive power in channel F1 (bits [24..0]) */
    __IO uint32_t F1VARN_L;             /*!< negative reactive power in channel F1 (bits [24..0]) */
    __IO uint32_t F1VR_L;               /*!< full power in channel F1 (bits [24..0]) */
    __IO uint32_t F2WATTP_L;            /*!< positive active power in channel F2 (bits [24..0]) */
    __IO uint32_t F2WATTN_L;            /*!< negative active power in channel F2 (bits [24..0]) */
    __IO uint32_t F2VARP_L;             /*!< positive reactive power in channel F2 (bits [24..0]) */
    __IO uint32_t F2VARN_L;             /*!< negative reactive power in channel F2 (bits [24..0]) */
    __IO uint32_t F2VR_L;               /*!< full power in channel F2 (bits [24..0]) */
} MDR_ADCUI_TypeDef;

/**
  * @brief Timers
  */

typedef struct
{
    __IO uint32_t CNT;                  /*!< timer's counter */
    __IO uint32_t PSG;                  /*!< prescaler */
    __IO uint32_t ARR;                  /*!< auto-reload register */
    __IO uint32_t CNTRL;                /*!< control register */
    __IO uint32_t CCR1;                 /*!< compare register for channel 1 */
    __IO uint32_t CCR2;                 /*!< compare register for channel 2 */
    __IO uint32_t CCR3;                 /*!< compare register for channel 3 */
    __IO uint32_t CCR4;                 /*!< compare register for channel 4 */
    __IO uint32_t CH1_CNTRL;            /*!< control register for channel 1 */
    __IO uint32_t CH2_CNTRL;            /*!< control register for channel 2 */
    __IO uint32_t CH3_CNTRL;            /*!< control register for channel 3 */
    __IO uint32_t CH4_CNTRL;            /*!< control register for channel 4 */
    __IO uint32_t CH1_CNTRL1;           /*!< additional control register for channel 1 */
    __IO uint32_t CH2_CNTRL1;           /*!< additional control register for channel 2 */
    __IO uint32_t CH3_CNTRL1;           /*!< additional control register for channel 3 */
    __IO uint32_t CH4_CNTRL1;           /*!< additional control register for channel 4 */
    __IO uint32_t CH1_DTG;              /*!< DTG control for channel 1 */
    __IO uint32_t CH2_DTG;              /*!< DTG control for channel 2 */
    __IO uint32_t CH3_DTG;              /*!< DTG control for channel 3 */
    __IO uint32_t CH4_DTG;              /*!< DTG control for channel 4 */
    __IO uint32_t BRKETR_CNTRL;         /*!< BRK and ETR control */
    __IO uint32_t STATUS;               /*!< status register */
    __IO uint32_t IE;                   /*!< interrupt enable */
    __IO uint32_t DMA_RE;               /*!< timer DMA control */
    __IO uint32_t CH1_CNTRL2;           /*!< additional control register for channel 1 */
    __IO uint32_t CH2_CNTRL2;           /*!< additional control register for channel 2 */
    __IO uint32_t CH3_CNTRL2;           /*!< additional control register for channel 3 */
    __IO uint32_t CH4_CNTRL2;           /*!< additional control register for channel 4 */
    __IO uint32_t CCR11;                /*!< additional compare register for channel 1 */
    __IO uint32_t CCR21;                /*!< additional compare register for channel 2 */
    __IO uint32_t CCR31;                /*!< additional compare register for channel 3 */
    __IO uint32_t CCR41;                /*!< additional compare register for channel 4 */
    __IO uint32_t DMA_RE1;              /*!< DMA setup for channel 1 */
    __IO uint32_t DMA_RE2;              /*!< DMA setup for channel 2 */
    __IO uint32_t DMA_RE3;              /*!< DMA setup for channel 3 */
    __IO uint32_t DMA_RE4;              /*!< DMA setup for channel 4 */
} MDR_TIM_TypeDef;

/**
  * @brief General purpose input-output (GPIO) Controller
  */

typedef struct
{
    __IO uint32_t RXTX;                 /*!< input/output data */
    __IO uint32_t OE;                   /*!< port direction */
    __IO uint32_t FUNC;                 /*!< port function */
    __IO uint32_t ANALOG;               /*!< analog port mode */
    __IO uint32_t PULL;                 /*!< port pull register control */
    __IO uint32_t RFU;                  /*!< RFU */
    __IO uint32_t PWR;                  /*!< port power control */
    __IO uint32_t RFU2;                 /*!< RFU2 */
    __IO uint32_t SETTX;                /*!< bit-setup register for output ports */
    __IO uint32_t CLRTX;                /*!< bit-clear register for output ports */
    __IO uint32_t RDTX;                 /*!< read-back register for output ports */
} MDR_GPIO_TypeDef;

/**
  * @brief Cyclic redundancy check (CRC) Controller
  */

typedef struct
{
    __IO uint32_t CTRL;                 /*!< CRC control register (R/W) */
    __IO uint32_t STAT;                 /*!< CRC status register (R/W) */
    __IO uint32_t DATAI;                /*!< CRC input data FIFO register (RO) */
    __IO uint32_t VAL;                  /*!< CRC calculated or initial value (R/W) */
    __IO uint32_t POL;                  /*!< CRC calculation polynomial, 16 bit (R/W) */
} MDR_CRC_TypeDef;

/**
  * @brief LBLOCK
  */

typedef struct
{
    __IO uint32_t TRM_00;               /*!< transformation register 0 */
    __IO uint32_t TRM_01;               /*!< transformation register 1 */
    __IO uint32_t TRM_02;               /*!< transformation register 2 */
    __IO uint32_t TRM_03;               /*!< transformation register 3 */
    __IO uint32_t TABLE_CNG_00;         /*!< table change register 0 */
    __IO uint32_t TABLE_CNG_01;         /*!< table change register 1 */
    __IO uint32_t TABLE_CNG_02;         /*!< table change register 2 */
    __IO uint32_t TABLE_CNG_03;         /*!< table change register 3 */
    __IO uint32_t SETUP;                /*!< setup register */
    __IO uint32_t MSCTRL;               /*!< memory special control */
} MDR_LBLOCK_TypeDef;

/**
  * @brief SBLOCK
  */

typedef struct
{
    __IO uint32_t TRM_00;               /*!< transformation register 0 */
    __IO uint32_t TRM_01;               /*!< transformation register 1 */
    __IO uint32_t TRM_02;               /*!< transformation register 2 */
    __IO uint32_t TRM_03;               /*!< transformation register 3 */
    __IO uint32_t TRM_04;               /*!< transformation register 4 */
    __IO uint32_t TRM_05;               /*!< transformation register 5 */
    __IO uint32_t TRM_06;               /*!< transformation register 6 */
    __IO uint32_t TRM_07;               /*!< transformation register 7 */
    __IO uint32_t TABLE_CHG;            /*!< table change register */
    __IO uint32_t MSCTRL;               /*!< memory special control */
} MDR_SBLOCK_TypeDef;

/**
  * @brief PBYTE
  */

typedef struct
{
    __IO uint32_t TRM_00;               /*!< transformation register 0 */
    __IO uint32_t TRM_01;               /*!< transformation register 1 */
    __IO uint32_t TRM_02;               /*!< transformation register 2 */
    __IO uint32_t TRM_03;               /*!< transformation register 3 */
    __IO uint32_t TRM_04;               /*!< transformation register 4 */
    __IO uint32_t TRM_05;               /*!< transformation register 5 */
    __IO uint32_t TRM_06;               /*!< transformation register 6 */
    __IO uint32_t TRM_07;               /*!< transformation register 7 */
    __IO uint32_t TRM_08;               /*!< transformation register 8 */
    __IO uint32_t TRM_09;               /*!< transformation register 9 */
    __IO uint32_t TRM_10;               /*!< transformation register 10 */
    __IO uint32_t TRM_11;               /*!< transformation register 11 */
    __IO uint32_t TRM_12;               /*!< transformation register 12 */
    __IO uint32_t TRM_13;               /*!< transformation register 13 */
    __IO uint32_t TRM_14;               /*!< transformation register 14 */
    __IO uint32_t TRM_15;               /*!< transformation register 15 */
    __IO uint32_t MUX_SET;              /*!< setup register */
    __IO uint32_t MUX_VAL;              /*!< value register */
} MDR_PBYTE_TypeDef;

/**
  * @brief PBIT
  */

typedef struct
{
    __IO uint32_t TRM_00;               /*!< transformation register 0 */
    __IO uint32_t TRM_01;               /*!< transformation register 1 */
    __IO uint32_t TRM_02;               /*!< transformation register 2 */
    __IO uint32_t TRM_03;               /*!< transformation register 3 */
    __IO uint32_t MUX_SET;              /*!< setup register */
    __IO uint32_t MUX_VAL;              /*!< value register */
} MDR_PBIT_TypeDef;

/**
  * @brief SENSORS
  */

typedef struct
{
    __IO uint32_t STATE;                /*!< state of the sensors */
    __IO uint32_t REALTIME;             /*!< real-time sensors monitoring */
    __IO uint32_t RFU;                  /*!< 0x08 */
    __IO uint32_t INTMSK;               /*!< interrupt mask */
    __IO uint32_t KRESMSK;              /*!< key reset signal mask */
    __IO uint32_t RFU2;                 /*!< 0x14 */
    __IO uint32_t ENABLE;               /*!< enable switch */
    __IO uint32_t MESHKEY7;             /*!< active mesh key [255 ... 224] */
    __IO uint32_t MESHKEY6;             /*!< active mesh key [223 ... 192] */
    __IO uint32_t MESHKEY5;             /*!< active mesh key [191 ... 160] */
    __IO uint32_t MESHKEY4;             /*!< active mesh key [159 ... 128] */
    __IO uint32_t MESHKEY3;             /*!< active mesh key [127 ... 96] */
    __IO uint32_t MESHKEY2;             /*!< active mesh key [95 ... 64] */
    __IO uint32_t MESHKEY1;             /*!< active mesh key [63 ... 32] */
    __IO uint32_t MESHKEY0;             /*!< active mesh key [31 ... 0] */
    __IO uint32_t MESHINIT1;            /*!< active mesh init value [63 ... 32] */
    __IO uint32_t MESHINIT0;            /*!< active mesh init value [31 ... 0] */
    __IO uint32_t MESHCNTR;             /*!< active mesh control register */
} MDR_SENSORS_TypeDef;

/**
  * @brief CLK_MEASURE
  */

typedef struct
{
    __IO uint32_t CNTR_STAT;            /*!< state and control */
    __IO uint32_t ALRM_RST;             /*!< alarm threshold for key reset */
    __IO uint32_t ALRM_INT;             /*!< alarm threshold for interrupt generation */
    __IO uint32_t PREG0;                /*!< setup register */
    __IO uint32_t PREG1;                /*!< setup register */
    __IO uint32_t STAT;                 /*!< max value for shift registers */
} MDR_CLK_MEASURE_TypeDef;

/**
  * @brief RANDOM
  */

typedef struct
{
    __IO uint32_t STAT;                 /*!< state and control */
    __IO uint32_t INT;                  /*!< interrupt control */
    __IO uint32_t CLKDIV;               /*!< clk division, result should be ~500kHz */
    __IO uint32_t PAUSE;                /*!< pause before generation starts */
    __IO uint32_t OUTPUT;               /*!< output data */
    __IO uint32_t PAUSECNT;             /*!< pause counter value */
    __IO uint32_t TEMP;                 /*!< temprorary value */
} MDR_RANDOM_TypeDef;

/**
  * @brief ISO7816
  */

typedef struct
{
    __IO uint32_t SR;                   /*!< status register */
    __IO uint32_t DR;                   /*!< data register (input / output) */
    __IO uint32_t BRR;                  /*!< baud-rate register */
    __IO uint32_t CR1;                  /*!< control register 1 */
    __IO uint32_t CR2;                  /*!< control register 2 */
    __IO uint32_t CR3;                  /*!< control register 3 */
    __IO uint32_t GTPR;                 /*!< guard time and prescaler register */
} MDR_ISO7816_TypeDef;

/**
  * @brief OTP
  */

typedef struct
{
    __IO uint32_t STAT_CTRL;            /*!< status and control register */
    __IO uint32_t OTP_STAT;             /*!< blocks statuses */
    __IO uint32_t DELAY0;               /*!< delay register 0 */
    __IO uint32_t DELAY1;               /*!< delay register 1 */
    __IO uint32_t RW_CMD;               /*!< read-write register */
    __IO uint32_t READ_DATA;            /*!< readed data register */
    __IO uint32_t WRITE_PROTECT;        /*!< write-protect register */
    __IO uint32_t READ_PROTECT;         /*!< read-protect register */
    __IO uint32_t DIR_CTRL;             /*!< direct control register */
    __IO uint32_t DIR_DATA;             /*!< direct control data */
    __IO uint32_t TEST_OPT;             /*!< test options */
} MDR_OTP_TypeDef;

/** @addtogroup Peripheral_declaration
  * @{
  */

#define MDR_SSP1                        ((MDR_SSP_TypeDef *) MDR_SPI1_BASE)
#define MDR_SSP2                        ((MDR_SSP_TypeDef *) MDR_SPI2_BASE)
#define MDR_SSP3                        ((MDR_SSP_TypeDef *) MDR_SPI3_BASE)
#define MDR_UART1                       ((MDR_UART_TypeDef *) MDR_UART1_BASE)
#define MDR_UART2                       ((MDR_UART_TypeDef *) MDR_UART2_BASE)
#define MDR_UART3                       ((MDR_UART_TypeDef *) MDR_UART3_BASE)
#define MDR_UART4                       ((MDR_UART_TypeDef *) MDR_UART4_BASE)
#define MDR_EEPROM                      ((MDR_EEPROM_CTRL_TypeDef *) MDR_EEPROM_CTRL_BASE)
#define MDR_RST_CLK                     ((MDR_RST_CLK_TypeDef *) MDR_RST_CLK_BASE)
#define MDR_DMA                         ((MDR_DMA_TypeDef* ) MDR_DMA_BASE)
#define MDR_I2C1                        ((MDR_I2C_TypeDef *) MDR_I2C_BASE)
#define MDR_ADC                         ((MDR_ADC_TypeDef *) MDR_ADC_BASE)
#define MDR_WWDG                        ((MDR_WWDG_TypeDef *) MDR_WWDG_BASE)
#define MDR_IWDG                        ((MDR_IWDG_TypeDef *) MDR_IWDG_BASE)
#define MDR_POWER                       ((MDR_POWER_TypeDef *) MDR_POWER_BASE)
#define MDR_BKP                         ((MDR_BKP_TypeDef *) MDR_BKP_BASE)
#define MDR_ADCUI                       ((MDR_ADCUI_TypeDef *) MDR_ADCUI_BASE)
#define MDR_TIMER1                      ((MDR_TIM_TypeDef *)MDR_TIMER1_BASE)
#define MDR_TIMER2                      ((MDR_TIM_TypeDef *)MDR_TIMER2_BASE)
#define MDR_TIMER3                      ((MDR_TIM_TypeDef *)MDR_TIMER3_BASE)
#define MDR_TIMER4                      ((MDR_TIM_TypeDef *)MDR_TIMER4_BASE)
#define MDR_PORTA                       ((MDR_GPIO_TypeDef *) MDR_GPIO1_BASE)
#define MDR_PORTB                       ((MDR_GPIO_TypeDef *) MDR_GPIO2_BASE)
#define MDR_PORTC                       ((MDR_GPIO_TypeDef *) MDR_GPIO3_BASE)
#define MDR_PORTD                       ((MDR_GPIO_TypeDef *) MDR_GPIO4_BASE)
#define MDR_CRC                         ((MDR_CRC_TypeDef *) MDR_CRC_BASE)
#define MDR_LBLOCK                      ((MDR_LBLOCK_TypeDef *) MDR_L_BLOCK_BASE)
#define MDR_SBLOCK0                     ((MDR_SBLOCK_TypeDef *) MDR_S_BLOCK0_BASE)
#define MDR_SBLOCK1                     ((MDR_SBLOCK_TypeDef *) MDR_S_BLOCK1_BASE)
#define MDR_SBLOCK2                     ((MDR_SBLOCK_TypeDef *) MDR_S_BLOCK2_BASE)
#define MDR_SBLOCK3                     ((MDR_SBLOCK_TypeDef *) MDR_S_BLOCK3_BASE)
#define MDR_SBLOCK4                     ((MDR_SBLOCK_TypeDef *) MDR_S_BLOCK4_BASE)
#define MDR_SBLOCK5                     ((MDR_SBLOCK_TypeDef *) MDR_S_BLOCK5_BASE)
#define MDR_SBLOCK6                     ((MDR_SBLOCK_TypeDef *) MDR_S_BLOCK6_BASE)
#define MDR_SBLOCK7                     ((MDR_SBLOCK_TypeDef *) MDR_S_BLOCK7_BASE)
#define MDR_PBYTE                       ((MDR_PBYTE_TypeDef *) MDR_P_BYTE_BASE)
#define MDR_PBIT0                       ((MDR_PBIT_TypeDef *) MDR_P_BIT0_BASE)
#define MDR_PBIT1                       ((MDR_PBIT_TypeDef *) MDR_P_BIT1_BASE)
#define MDR_PBIT2                       ((MDR_PBIT_TypeDef *) MDR_P_BIT2_BASE)
#define MDR_PBIT3                       ((MDR_PBIT_TypeDef *) MDR_P_BIT3_BASE)
#define MDR_SENSORS                     ((MDR_SENSORS_TypeDef *) MDR_SENSORS_BASE)
#define MDR_CLK_MEASURE                 ((MDR_CLK_MEASURE_TypeDef *) MDR_CLK_MEASURE_BASE)
#define MDR_RANDOM                      ((MDR_RANDOM_TypeDef *) MDR_RANDOM_BASE)
#define MDR_ISO7816                     ((MDR_ISO7816_TypeDef *) MDR_ISO7816_BASE)
#define MDR_OTP                         ((MDR_OTP_TypeDef *) MDR_OTP_REG_BASE)

/**
  * @}
  */

/*
 * ==========================================================================
 * ---------------------- SSP registers bits --------------------------------
 * ==========================================================================
 */

/*******************  SSP interrupt sources ***********************************/
/* receiver overflow interrupt */
#define SSP_IT_RX_OVERFLOW_Pos			(0U)
#define SSP_IT_RX_OVERFLOW_Msk			(0x1U << SSP_IT_RX_OVERFLOW_Pos)		/*!< 0x00000001 */
#define SSP_IT_RX_OVERFLOW				SSP_IT_RX_OVERFLOW_Msk
/* receiver timeout interrupt */
#define SSP_IT_RX_TIMEOUT_Pos			(1U)
#define SSP_IT_RX_TIMEOUT_Msk			(0x1U << SSP_IT_RX_TIMEOUT_Pos)			/*!< 0x00000002 */
#define SSP_IT_RX_TIMEOUT				SSP_IT_RX_TIMEOUT_Msk
/* RX FIFO half full */
#define SSP_IT_RX_FIFO_HALFFULL_Pos		(2U)
#define SSP_IT_RX_FIFO_HALFFULL_Msk		(0x1U << SSP_IT_RX_FIFO_HALFFULL_Pos)	/*!< 0x00000004 */
#define SSP_IT_RX_FIFO_HALFFULL			SSP_IT_RX_FIFO_HALFFULL_Msk
/* TX FIFO hafl empty */
#define SSP_IT_TX_FIFO_HALFEMPTY_Pos	(3U)
#define SSP_IT_TX_FIFO_HALFEMPTY_Msk	(0x1U << SSP_IT_TX_FIFO_HALFEMPTY_Pos)	/*!< 0x00000008 */
#define SSP_IT_TX_FIFO_HALFEMPTY		SSP_IT_TX_FIFO_HALFEMPTY_Msk

/*******************  Bit definition for SSP_CR0 register *********************/
/* SSP WORD size, 0b0011 - 4 bits, 0b0100 - 5 bits, ... 0b1111 - 16 bits */
#define SSP_CR0_DSS_Pos                 (0U)
#define SSP_CR0_DSS_Msk                 (0xFU << SSP_CR0_DSS_Pos)               /*!< 0x0000000F */
#define SSP_CR0_DSS_4bit                (3U << SSP_CR0_DSS_Pos)                 /*!< 0x00000003 */
#define SSP_CR0_DSS_5bit                (4U << SSP_CR0_DSS_Pos)                 /*!< 0x00000004 */
#define SSP_CR0_DSS_6bit                (5U << SSP_CR0_DSS_Pos)                 /*!< 0x00000005 */
#define SSP_CR0_DSS_7bit                (6U << SSP_CR0_DSS_Pos)                 /*!< 0x00000006 */
#define SSP_CR0_DSS_8bit                (7U << SSP_CR0_DSS_Pos)                 /*!< 0x00000007 */
#define SSP_CR0_DSS_9bit                (8U << SSP_CR0_DSS_Pos)                 /*!< 0x00000008 */
#define SSP_CR0_DSS_10bit               (9U << SSP_CR0_DSS_Pos)                 /*!< 0x00000009 */
#define SSP_CR0_DSS_11bit               (10U << SSP_CR0_DSS_Pos)                /*!< 0x0000000A */
#define SSP_CR0_DSS_12bit               (11U << SSP_CR0_DSS_Pos)                /*!< 0x0000000B */
#define SSP_CR0_DSS_13bit               (12U << SSP_CR0_DSS_Pos)                /*!< 0x0000000C */
#define SSP_CR0_DSS_14bit               (13U << SSP_CR0_DSS_Pos)                /*!< 0x0000000D */
#define SSP_CR0_DSS_15bit               (14U << SSP_CR0_DSS_Pos)                /*!< 0x0000000E */
#define SSP_CR0_DSS_16bit               (15U << SSP_CR0_DSS_Pos)                /*!< 0x0000000F */
/* SSP mode, 0b00 - SPI, 0b01 - SSI, 0b10 - Microwire */
#define SSP_CR0_FRF_Pos                 (4U)
#define SSP_CR0_FRF_Msk                 (0x3U << SSP_CR0_FRF_Pos)               /*!< 0x00000030 */
#define SSP_CR0_FRF_SPI                 (0x0U << SSP_CR0_FRF_Pos)               /*!< 0x00000000 */
#define SSP_CR0_FRF_SSI                 (0x1U << SSP_CR0_FRF_Pos)               /*!< 0x00000010 */
#define SSP_CR0_FRF_MICROWIRE           (0x2U << SSP_CR0_FRF_Pos)               /*!< 0x00000020 */
/* CLK polarity */
#define SSP_CR0_SPO_Pos                 (6U)
#define SSP_CR0_SPO_Msk                 (0x1U << SSP_CR0_SPO_Pos)               /*!< 0x00000040 */
#define SSP_CR0_SPO_0                   (0x0U << SSP_CR0_SPO_Pos)
#define SSP_CR0_SPO_1                   (0x1U << SSP_CR0_SPO_Pos)
/* CLK phase */
#define SSP_CR0_SPH_Pos                 (7U)
#define SSP_CR0_SPH_Msk                 (0x1U << SSP_CR0_SPH_Pos)               /*!< 0x00000080 */
#define SSP_CR0_SPH_0                   (0x0U << SSP_CR0_SPH_Pos)
#define SSP_CR0_SPH_1                   (0x1U << SSP_CR0_SPH_Pos)
/* communication speed counter, SSP_CLK / (CPSDVR * (1 + SCR)) */
#define SSP_CR0_SCR_Pos                 (8U)
#define SSP_CR0_SCR_Msk                 (0xFFU << SSP_CR0_SCR_Pos)              /*!< 0x0000FF00 */

/*******************  Bit definition for SSP_CR1 register *********************/
/* loop back mode (1 - to interconnect transmitter with reciever) */
#define SSP_CR1_LBM_Pos                 (0U)
#define SSP_CR1_LBM_Msk                 (0x1U << SSP_CR1_LBM_Pos)               /*!< 0x00000001 */
#define SSP_CR1_LBM_LOOPBACK_DISABLED   (0x0U << SSP_CR1_LBM_Pos)
#define SSP_CR1_LBM_LOOPBACK_ENABLED    (0x1U << SSP_CR1_LBM_Pos)
/* module disable switch (0 - disabled, 1 - enabled) */
#define SSP_CR1_SSE_Pos                 (1U)
#define SSP_CR1_SSE_Msk                 (0x1U << SSP_CR1_SSE_Pos)               /*!< 0x00000002 */
#define SSP_CR1_SSE                     SSP_CR1_SSE_Msk
/* master/slave switch (0 - master, 1 - slave) */
#define SSP_CR1_MS_Pos                  (2U)
#define SSP_CR1_MS_Msk                  (0x1U << SSP_CR1_MS_Pos)                /*!< 0x00000004 */
#define SSP_CR1_MS_MASTER               (0x0U << SSP_CR1_MS_Pos)
#define SSP_CR1_MS_SLAVE                (0x1U << SSP_CR1_MS_Pos)
/* transmitter disable for slave mode (0 - transmitter enabled, 1 - transmitter disabled) */
#define SSP_CR1_SOD_Pos                 (3U)
#define SSP_CR1_SOD_Msk                 (0x1U << SSP_CR1_SOD_Pos)               /*!< 0x00000008 */
#define SSP_CR1_SOD						SSP_CR1_SOD_Msk

/*******************  Bit definition for SSP_SR register **********************/
/* transmitter FIFO is empty */
#define SSP_SR_TFE_Pos              	(0U)
#define SSP_SR_TFE_Msk              	(0x1U << SSP_SR_TFE_Pos)           		/*!< 0x00000001 */
#define SSP_SR_TFE    					SSP_SR_TFE_Msk
/* transmitter FIFO is not full */
#define SSP_SR_TNF_Pos              	(1U)
#define SSP_SR_TNF_Msk              	(0x1U << SSP_SR_TNF_Pos)           		/*!< 0x00000002 */
#define SSP_SR_TNF  					SSP_SR_TNF_Msk
/* reciever FIFO is not empty */
#define SSP_SR_RNE_Pos              	(2U)
#define SSP_SR_RNE_Msk              	(0x1U << SSP_SR_RNE_Pos)            	/*!< 0x00000004 */
#define SSP_SR_RNE 						SSP_SR_RNE_Msk
/* receiver FIFO is full */
#define SSP_SR_RFF_Pos              	(3U)
#define SSP_SR_RFF_Msk              	(0x1U << SSP_SR_RFF_Pos)            	/*!< 0x00000008 */
#define SSP_SR_RFF    					SSP_SR_RFF_Msk
/* busy flag */
#define SSP_SR_BSY_Pos              	(4U)
#define SSP_SR_BSY_Msk              	(0x1U << SSP_SR_BSY_Pos)            	/*!< 0x00000010 */
#define SSP_SR_BSY                 		SSP_SR_BSY_Msk

/*******************  Bit definition for SSP_IMSC register ********************/
/*******************  Bit definition for SSP_RIS register *********************/
/*******************  Bit definition for SSP_MIS register *********************/
/* use SSP interrupt sources */

/*******************  Bit definition for SSP_ICR register *********************/
/* clear RX FIFO overflow pending interrupt */
#define SSP_ICR_RORIC_Pos               (0U)
#define SSP_ICR_RORIC_Msk               (0x1U << SSP_ICR_RORIC_Pos)             /*!< 0x00000001 */
#define SSP_ICR_RORIC                   SSP_ICR_RORIC_Msk
/* clear RX FIFO read timeout pending interrupt */
#define SSP_ICR_RTIC_Pos                (1U)
#define SSP_ICR_RTIC_Msk                (0x1U << SSP_ICR_RTIC_Pos)              /*!< 0x00000002 */
#define SSP_ICR_RTIC                    SSP_ICR_RTIC_Msk

/*******************  Bit definition for SSP_DMACR register *******************/
/* SSP DMA RX (0 - disabled, 1 - enabled) */
#define SSP_DMACR_RXDMAE_Pos            (0U)
#define SSP_DMACR_RXDMAE_Msk            (0x1U << SSP_DMACR_RXDMAE_Pos)          /*!< 0x00000001 */
#define SSP_DMACR_RXDMAE                SSP_DMACR_RXDMAE_Msk
/* SSP DMA TX (0 - disabled, 1 - enabled) */
#define SSP_DMACR_TXDMAE_Pos            (1U)
#define SSP_DMACR_TXDMAE_Msk            (0x1U << SSP_DMACR_TXDMAE_Pos)          /*!< 0x00000002 */
#define SSP_DMACR_TXDMAE                SSP_DMACR_TXDMAE_Msk

/*
 * ==========================================================================
 * ---------------------- UART registers bits -------------------------------
 * ==========================================================================
 */

/*******************  UART interrupts *****************************************/
/* RING signal interrupt */
#define UART_IT_RI_Pos					(0U)
#define UART_IT_RI_Msk					(0x1U << UART_IT_RI_Pos)           		/*!< 0x00000001 */
#define UART_IT_RI						UART_IT_RI_Msk
/* CTS signal interrupt */
#define UART_IT_CTS_Pos					(1U)
#define UART_IT_CTS_Msk					(0x1U << UART_IT_CTS_Pos)				/*!< 0x00000002 */
#define UART_IT_CTS						UART_IT_CTS_Msk
/* DCD signal interrupt */
#define UART_IT_DCD_Pos					(2U)
#define UART_IT_DCD_Msk					(0x1U << UART_IT_DCD_Pos)				/*!< 0x00000004 */
#define UART_IT_DCD						UART_IT_DCD_Msk
/* DSR signal interrupt */
#define UART_IT_DSR_Pos					(3U)
#define UART_IT_DSR_Msk					(0x1U << UART_IT_DSR_Pos)				/*!< 0x00000008 */
#define UART_IT_DSR						UART_IT_DSR_Msk
/* receiver interrupt */
#define UART_IT_RX_Pos					(4U)
#define UART_IT_RX_Msk					(0x1U << UART_IT_RX_Pos)				/*!< 0x00000010 */
#define UART_IT_RX						UART_IT_RX_Msk
/* transmitter interrupt */
#define UART_IT_TX_Pos					(5U)
#define UART_IT_TX_Msk					(0x1U << UART_IT_TX_Pos)				/*!< 0x00000020 */
#define UART_IT_TX						UART_IT_TX_Msk
/* receiver timeout interrupt */
#define UART_IT_RT_Pos					(6U)
#define UART_IT_RT_Msk					(0x1U << UART_IT_RT_Pos)				/*!< 0x00000040 */
#define UART_IT_RT						UART_IT_RT_Msk
/* frame error interrupt */
#define UART_IT_FE_Pos					(7U)
#define UART_IT_FE_Msk					(0x1U << UART_IT_FE_Pos)				/*!< 0x00000080 */
#define UART_IT_FE						UART_IT_FE_Msk
/* parity error interrupt */
#define UART_IT_PE_Pos					(8U)
#define UART_IT_PE_Msk					(0x1U << UART_IT_PE_Pos)				/*!< 0x00000100 */
#define UART_IT_PE						UART_IT_PE_Msk
/* break error interrupt */
#define UART_IT_BE_Pos					(9U)
#define UART_IT_BE_Msk					(0x1U << UART_IT_BE_Pos)				/*!< 0x00000200 */
#define UART_IT_BE						UART_IT_BE_Msk
/* overflow interrupt */
#define UART_IT_OE_Pos					(10U)
#define UART_IT_OE_Msk					(0x1U << UART_IT_OE_Pos)				/*!< 0x00000400 */
#define UART_IT_OE						UART_IT_OE_Msk
/* receiver FIFO is not empty interrupt */
#define UART_IT_RNE_Pos					(11U)
#define UART_IT_RNE_Msk					(0x1U << UART_IT_RNE_Pos)				/*!< 0x00000800 */
#define UART_IT_RNE						UART_IT_RNE_Msk
/* transmitter FIFO empty interrupt */
#define UART_IT_TFE_Pos					(12U)
#define UART_IT_TFE_Msk					(0x1U << UART_IT_TFE_Pos)				/*!< 0x00001000 */
#define UART_IT_TFE						UART_IT_TFE_Msk
/* shift register is empty interrupt */
#define UART_IT_TNBSY_Pos				(13U)
#define UART_IT_TNBSY_Msk				(0x1U << UART_IT_TNBSY_Pos)				/*!< 0x00002000 */
#define UART_IT_TNBSY					UART_IT_TNBSY_Msk

/*******************  Bit definition for UART_DR register *********************/
/* FIFO entry point (received data - read, transmitting data - write) */
#define UART_DR_DATA_Pos                (0U)
#define UART_DR_DATA_Msk                (0x1FFU << UART_DR_DATA_Pos)            /*!< 0x000001FF */
/* frame error */
#define UART_DR_FE_Pos                  (9U)
#define UART_DR_FE_Msk                  (0x1U << UART_DR_FE_Pos)                /*!< 0x00000200 */
#define UART_DR_FE                      UART_DR_FE_Msk
/* parity error */
#define UART_DR_PE_Pos                  (10U)
#define UART_DR_PE_Msk                  (0x1U << UART_DR_PE_Pos)                /*!< 0x00000400 */
#define UART_DR_PE                      UART_DR_PE_Msk
/* break detection (idle more than 1 word) */
#define UART_DR_BE_Pos                  (11U)
#define UART_DR_BE_Msk                  (0x1U << UART_DR_BE_Pos)                /*!< 0x00000800 */
#define UART_DR_BE                      UART_DR_BE_Msk
/* overflow detection */
#define UART_DR_OE_Pos                  (12U)
#define UART_DR_OE_Msk                  (0x1U << UART_DR_OE_Pos)                /*!< 0x00001000 */
#define UART_DR_OE                      UART_DR_OE_Msk

/*******************  Bit definition for UART_RSR_ECR register ****************/
/* Framing eror */
#define UART_RSR_ECR_FE_Pos             (0U)
#define UART_RSR_ECR_FE_Msk             (0x1U << UART_RSR_ECR_FE_Pos)           /*!< 0x00000001 */
#define UART_RSR_ECR_FE                 UART_RSR_ECR_FE_Msk
/* parity error */
#define UART_RSR_ECR_PE_Pos             (1U)
#define UART_RSR_ECR_PE_Msk             (0x1U << UART_RSR_ECR_PE_Pos)           /*!< 0x00000002 */
#define UART_RSR_ECR_PE                 UART_RSR_ECR_PE_Msk
/* break error */
#define UART_RSR_ECR_BE_Pos             (2U)
#define UART_RSR_ECR_BE_Msk             (0x1U << UART_RSR_ECR_BE_Pos)           /*!< 0x00000004 */
#define UART_RSR_ECR_BE                 UART_RSR_ECR_BE_Msk
/* overflow error */
#define UART_RSR_ECR_OE_Pos             (3U)
#define UART_RSR_ECR_OE_Msk             (0x1U << UART_RSR_ECR_OE_Pos)           /*!< 0x00000008 */
#define UART_RSR_ECR_OE                 UART_RSR_ECR_OE_Msk

/*******************  Bit definition for UART_FR register *********************/
/* CTS flow control */
#define UART_FR_CTS_Pos                 (0U)
#define UART_FR_CTS_Msk                 (0x1U << UART_FR_CTS_Pos)               /*!< 0x00000001 */
#define UART_FR_CTS                     UART_FR_CTS_Msk
/* DSR flow control */
#define UART_FR_DSR_Pos                 (1U)
#define UART_FR_DSR_Msk                 (0x1U << UART_FR_DSR_Pos)               /*!< 0x00000002 */
#define UART_FR_DSR                     UART_FR_DSR_Msk
/* DCD flow control */
#define UART_FR_DCD_Pos                 (2U)
#define UART_FR_DCD_Msk                 (0x1U << UART_FR_DCD_Pos)               /*!< 0x00000004 */
#define UART_FR_DCD                     UART_FR_DCD_Msk
/* BUSY flag (data is sending or ready to be sent) */
#define UART_FR_BUSY_Pos                (3U)
#define UART_FR_BUSY_Msk                (0x1U << UART_FR_BUSY_Pos)              /*!< 0x00000008 */
#define UART_FR_BUSY                    UART_FR_BUSY_Msk
/* receiver FIFO is empty */
#define UART_FR_RXFE_Pos                (4U)
#define UART_FR_RXFE_Msk                (0x1U << UART_FR_RXFE_Pos)              /*!< 0x00000010 */
#define UART_FR_RXFE                    UART_FR_RXFE_Msk
/* transmitter FIFO is full */
#define UART_FR_TXFF_Pos                (5U)
#define UART_FR_TXFF_Msk                (0x1U << UART_FR_TXFF_Pos)              /*!< 0x00000020 */
#define UART_FR_TXFF                    UART_FR_TXFF_Msk
/* receiver FIFO is full (up to threshold) */
#define UART_FR_RXFF_Pos                (6U)
#define UART_FR_RXFF_Msk                (0x1U << UART_FR_RXFF_Pos)              /*!< 0x00000040 */
#define UART_FR_RXFF                    UART_FR_RXFF_Msk
/* transmitter FIFO is empty (up to threshold) */
#define UART_FR_TXFE_Pos                (7U)
#define UART_FR_TXFE_Msk                (0x1U << UART_FR_TXFE_Pos)              /*!< 0x00000080 */
#define UART_FR_TXFE                    UART_FR_TXFE_Msk
/* RI flow control */
#define UART_FR_RI_Pos                  (8U)
#define UART_FR_RI_Msk                  (0x1U << UART_FR_RI_Pos)                /*!< 0x00000100 */
#define UART_FR_RI                      UART_FR_RI_Msk

/*******************  Bit definition for UART_LCR_H register ******************/
/* break line */
#define UART_LCR_H_BRK_Pos              (0U)
#define UART_LCR_H_BRK_Msk              (0x1U << UART_LCR_H_BRK_Pos)            /*!< 0x00000001 */
#define UART_LCR_H_BRK                  UART_LCR_H_BRK_Msk
/* parity enable (0 - no parity, 1 - parity control activated) */
#define UART_LCR_H_PEN_Pos              (1U)
#define UART_LCR_H_PEN_Msk              (0x1U << UART_LCR_H_PEN_Pos)            /*!< 0x00000002 */
#define UART_LCR_H_PEN                  UART_LCR_H_PEN_Msk
/* parity selection (0 - odd, 1 - even) */
#define UART_LCR_H_EPS_Pos              (2U)
#define UART_LCR_H_EPS_Msk              (0x1U << UART_LCR_H_EPS_Pos)            /*!< 0x00000004 */
#define UART_LCR_H_EPS_ODD              (0x0U << UART_LCR_H_EPS_Pos)
#define UART_LCR_H_EPS_EVEN             (0x1U << UART_LCR_H_EPS_Pos)
/* stop bit count (0 - 1 stop bit, 1 - 2 stop bits) */
#define UART_LCR_H_STP2_Pos             (3U)
#define UART_LCR_H_STP2_Msk             (0x1U << UART_LCR_H_STP2_Pos)           /*!< 0x00000008 */
#define UART_LCR_H_STP2_1STOPBIT        (0x0U << UART_LCR_H_STP2_Pos)
#define UART_LCR_H_STP2_2STOPBITS       (0x1U << UART_LCR_H_STP2_Pos)
/* FIFO enable (0 - disabled, 1 - enabled) */
#define UART_LCR_H_FEN_Pos              (4U)
#define UART_LCR_H_FEN_Msk              (0x1U << UART_LCR_H_FEN_Pos)            /*!< 0x00000010 */
#define UART_LCR_H_FEN                  UART_LCR_H_FEN_Msk
/* number of bits within WORD */
#define UART_LCR_H_WLEN1_Pos            (5U)
#define UART_LCR_H_WLEN1_Msk            (0x3U << UART_LCR_H_WLEN1_Pos)          /*!< 0x00000060 */
#define UART_LCR_H_WLEN1                UART_LCR_H_WLEN1_Msk
/* fixed parity bit (0 - disabled, 1 - inversion of EPS) */
#define UART_LCR_H_SPS_Pos              (7U)
#define UART_LCR_H_SPS_Msk              (0x1U << UART_LCR_H_SPS_Pos)            /*!< 0x00000080 */
#define UART_LCR_H_SPS                  UART_LCR_H_SPS_Msk
/* PEN + EPS + SPS control */
#define UART_LCR_H_PARITY_Msk           (UART_LCR_H_PEN_Msk | UART_LCR_H_EPS_Msk | UART_LCR_H_SPS_Msk)
#define UART_LCR_H_PARITY_NONE          (0x0U << UART_LCR_H_PEN_Pos)
#define UART_LCR_H_PARITY_ODD           (UART_LCR_H_PEN | UART_LCR_H_EPS_ODD)
#define UART_LCR_H_PARITY_EVEN          (UART_LCR_H_PEN | UART_LCR_H_EPS_EVEN)
#define UART_LCR_H_PARITY_ALWAYS0       (UART_LCR_H_PEN | UART_LCR_H_EPS_EVEN | UART_LCR_H_SPS)
#define UART_LCR_H_PARITY_ALWAYS1       (UART_LCR_H_PEN | UART_LCR_H_EPS_ODD | UART_LCR_H_SPS)
/* number of bits within WORD (additional) */
#define UART_LCR_H_WLEN2_Pos            (8U)
#define UART_LCR_H_WLEN2_Msk            (0x1U << UART_LCR_H_WLEN2_Pos)          /*!< 0x00000100 */
#define UART_LCR_H_WLEN2                UART_LCR_H_WLEN2_Msk
#define UART_LCR_H_WLEN_Msk             (UART_LCR_H_WLEN1_Msk | UART_LCR_H_WLEN2_Msk)
#define UART_LCR_H_WLEN_5bit            (0x0U << UART_LCR_H_WLEN1_Pos)
#define UART_LCR_H_WLEN_6bit            (0x1U << UART_LCR_H_WLEN1_Pos)
#define UART_LCR_H_WLEN_7bit            (0x2U << UART_LCR_H_WLEN1_Pos)
#define UART_LCR_H_WLEN_8bit            (0x3U << UART_LCR_H_WLEN1_Pos)
#define UART_LCR_H_WLEN_9bit            UART_LCR_H_WLEN2

/*******************  Bit definition for UART_CR register *********************/
/* UART enable switch (0 - disabled, 1 - enabled) */
#define UART_CR_UARTEN_Pos              (0U)
#define UART_CR_UARTEN_Msk              (0x1U << UART_CR_UARTEN_Pos)            /*!< 0x00000001 */
#define UART_CR_UARTEN                  UART_CR_UARTEN_Msk
/* IrDA SIR enable switch (0 - disabled, 1 - enabled) */
#define UART_CR_SIREN_Pos               (1U)
#define UART_CR_SIREN_Msk               (0x1U << UART_CR_SIREN_Pos)             /*!< 0x00000002 */
#define UART_CR_SIREN                   UART_CR_SIREN_Msk
/* low-power IrDA enable switch (0 - disabled, 1 - enabled) */
#define UART_CR_SIRLP_Pos               (2U)
#define UART_CR_SIRLP_Msk               (0x1U << UART_CR_SIRLP_Pos)             /*!< 0x00000004 */
#define UART_CR_SIRLP                   UART_CR_SIRLP_Msk
/* loop-back enable switch (0 - disabled, 1 - enabled) */
#define UART_CR_LBE_Pos                 (7U)
#define UART_CR_LBE_Msk                 (0x1U << UART_CR_LBE_Pos)               /*!< 0x00000080 */
#define UART_CR_LBE                     UART_CR_LBE_Msk
/* transmit enable switch */
#define UART_CR_TXE_Pos                 (8U)
#define UART_CR_TXE_Msk                 (0x1U << UART_CR_TXE_Pos)               /*!< 0x00000100 */
#define UART_CR_TXE                     UART_CR_TXE_Msk
/* receive enable switch */
#define UART_CR_RXE_Pos                 (9U)
#define UART_CR_RXE_Msk                 (0x1U << UART_CR_RXE_Pos)               /*!< 0x00000200 */
#define UART_CR_RXE                     UART_CR_RXE_Msk
/* DTR inversion switch */
#define UART_CR_DTR_Pos                 (10U)
#define UART_CR_DTR_Msk                 (0x1U << UART_CR_DTR_Pos)               /*!< 0x00000400 */
#define UART_CR_DTR                     UART_CR_DTR_Msk
/* RTS inversion switch */
#define UART_CR_RTS_Pos                 (11U)
#define UART_CR_RTS_Msk                 (0x1U << UART_CR_RTS_Pos)               /*!< 0x00000800 */
#define UART_CR_RTS                     UART_CR_RTS_Msk
/* DTE inversion switch */
#define UART_CR_OUT1_Pos                (12U)
#define UART_CR_OUT1_Msk                (0x1U << UART_CR_OUT1_Pos)              /*!< 0x00001000 */
#define UART_CR_OUT1                    UART_CR_OUT1_Msk
/* RI inversion switch */
#define UART_CR_OUT2_Pos                (13U)
#define UART_CR_OUT2_Msk                (0x1U << UART_CR_OUT2_Pos)              /*!< 0x00002000 */
#define UART_CR_OUT2                    UART_CR_OUT2_Msk
/* RTS enable switch */
#define UART_CR_RTSEN_Pos               (14U)
#define UART_CR_RTSEN_Msk               (0x1U << UART_CR_RTSEN_Pos)             /*!< 0x00004000 */
#define UART_CR_RTSEN                   UART_CR_RTSEN_Msk
/* CTS enable switch */
#define UART_CR_CTSEN_Pos               (15U)
#define UART_CR_CTSEN_Msk               (0x1U << UART_CR_CTSEN_Pos)             /*!< 0x00008000 */
#define UART_CR_CTSEN                   UART_CR_CTSEN_Msk

/*******************  Bit definition for UART_IFLS register *******************/
#define UART_IFL_1_8                    0x0U
#define UART_IFL_1_4                    0x1U
#define UART_IFL_1_2                    0x2U
#define UART_IFL_3_4                    0x3U
#define UART_IFL_7_8                    0x4U
/* transmitter FIFO threshold */
#define UART_IFLS_TXIFLSEL_Pos          (0U)
#define UART_IFLS_TXIFLSEL_Msk          (0x7U << UART_IFLS_TXIFLSEL_Pos)        /*!< 0x00000007 */
/* reciever FIFO threshold */
#define UART_IFLS_RXIFLSEL_Pos          (3U)
#define UART_IFLS_RXIFLSEL_Msk          (0x7U << UART_IFLS_RXIFLSEL_Pos)        /*!< 0x00000038 */

/*******************  Bit definition for UART_IMSC register *******************/
/*******************  Bit definition for UART_RIS register ********************/
/*******************  Bit definition for UART_MIS register ********************/
/*******************  Bit definition for UART_ICR register ********************/

/*******************  Bit definition for UART_DMACR register ******************/
/* DMA receive enable */
#define UART_DMACR_RXDMAE_Pos           (0U)
#define UART_DMACR_RXDMAE_Msk           (0x1U << UART_DMACR_RXDMAE_Pos)         /*!< 0x00000001 */
#define UART_DMACR_RXDMAE               UART_DMACR_RXDMAE_Msk
/* DMA transmit enable */
#define UART_DMACR_TXDMAE_Pos           (1U)
#define UART_DMACR_TXDMAE_Msk           (0x1U << UART_DMACR_TXDMAE_Pos)         /*!< 0x00000002 */
#define UART_DMACR_TXDMAE               UART_DMACR_TXDMAE_Msk
/* stop DMA on error */
#define UART_DMACR_DMAONERR_Pos         (2U)
#define UART_DMACR_DMAONERR_Msk         (0x1U << UART_DMACR_DMAONERR_Pos)       /*!< 0x00000004 */
#define UART_DMACR_DMAONERR             UART_DMACR_DMAONERR_Msk

/*******************  Bit definition for UART_TCR register ********************/
/* test mode enable (1 - test mode, 0 - normal mode) */
#define UART_TCR_ITEN_Pos               (0U)
#define UART_TCR_ITEN_Msk               (0x1U << UART_TCR_ITEN_Pos)             /*!< 0x00000001 */
#define UART_TCR_ITEN                   UART_TCR_ITEN_Msk
/* FIFO test */
#define UART_TCR_TESTFIFO_Pos           (1U)
#define UART_TCR_TESTFIFO_Msk           (0x1U << UART_TCR_TESTFIFO_Pos)         /*!< 0x00000002 */
#define UART_TCR_TESTFIFO               UART_TCR_TESTFIFO_Msk
/* SIR test */
#define UART_TCR_SIRTEST_Pos            (2U)
#define UART_TCR_SIRTEST_Msk            (0x1U << UART_TCR_SIRTEST_Pos)          /*!< 0x00000004 */
#define UART_TCR_SIRTEST                UART_TCR_SIRTEST_Msk

/*
 * ==========================================================================
 * ---------------------- EEPROM registers bits -----------------------------
 * ==========================================================================
 */

/* protection key */
#define EEPROM_KEY_UNLOCK_KEY			(0x8AAA5551U)
#define EEPROM_KEY_LOCK_KEY				(0x0U)

/*******************  Bit definition for FLASH_CMD register *******************/
/* FLASH control (0 - normal mode, 1 - flash programming mode) */
#define EEPROM_CMD_CON_Pos              (0U)
#define EEPROM_CMD_CON_Msk              (0x1U << EEPROM_CMD_CON_Pos)            /*!< 0x00000001 */
#define EEPROM_CMD_CON_NORMAL           (0x0U << EEPROM_CMD_CON_Pos)            /*!< 0x00000000 */
#define EEPROM_CMD_CON_PROGRAMMING      (0x1U << EEPROM_CMD_CON_Pos)            /*!< 0x00000001 */
/* FLASH delay (maximum speed of the FLASH is 30 MHz, use delay = 1 for greater core speed) */
#define EEPROM_CMD_DELAY_Pos            (3U)
#define EEPROM_CMD_DELAY_Msk            (0x7U << EEPROM_CMD_DELAY_Pos)          /*!< 0x00000038 */
#define EEPROM_CMD_DELAY_0_CYCLE        (0x0U << EEPROM_CMD_DELAY_Pos)          /*!< 0x00000000 */
#define EEPROM_CMD_DELAY_1_CYCLE        (0x1U << EEPROM_CMD_DELAY_Pos)          /*!< 0x00000008 */
/* upper part of the address [17:9] feeding enable (0 - disabled, 1 - enabled) */
#define EEPROM_CMD_XE_Pos               (6U)
#define EEPROM_CMD_XE_Msk               (0x1U << EEPROM_CMD_XE_Pos)             /*!< 0x00000040 */
#define EEPROM_CMD_XE                   EEPROM_CMD_XE_Msk
/* lower part of the address [8:2] feeding enable (0 - disabled, 1 - enabled) */
#define EEPROM_CMD_YE_Pos               (7U)
#define EEPROM_CMD_YE_Msk               (0x1U << EEPROM_CMD_YE_Pos)             /*!< 0x00000080 */
#define EEPROM_CMD_YE                   EEPROM_CMD_YE_Msk
/* readout apmlifier (0 - disabled, 1 - enabled) */
#define EEPROM_CMD_SE_Pos               (8U)
#define EEPROM_CMD_SE_Msk               (0x1U << EEPROM_CMD_SE_Pos)             /*!< 0x00000100 */
#define EEPROM_CMD_SE                   EEPROM_CMD_SE_Msk
/* information block selection (0 - main block, 1 - information block) */
#define EEPROM_CMD_IFREN_Pos            (9U)
#define EEPROM_CMD_IFREN_Msk            (0x1U << EEPROM_CMD_IFREN_Pos)          /*!< 0x00000200 */
#define EEPROM_CMD_IFREN                EEPROM_CMD_IFREN_Msk
/* erase page (0 - do not erase, 1 - erase) (lower part of the address [8:2] do no sence here) */
#define EEPROM_CMD_ERASE_Pos            (10U)
#define EEPROM_CMD_ERASE_Msk            (0x1U << EEPROM_CMD_ERASE_Pos)          /*!< 0x00000400 */
#define EEPROM_CMD_ERASE                EEPROM_CMD_ERASE_Msk
/* mass erase whole memory (0 - do not erase, 1 - erase) */
#define EEPROM_CMD_MAS1_Pos             (11U)
#define EEPROM_CMD_MAS1_Msk             (0x1U << EEPROM_CMD_MAS1_Pos)           /*!< 0x00000800 */
#define EEPROM_CMD_MAS1                 EEPROM_CMD_MAS1_Msk
/* write data from EEPROM_DI to address [17:2], (0 - do not write, 1 - write) */
#define EEPROM_CMD_PROG_Pos             (12U)
#define EEPROM_CMD_PROG_Msk             (0x1U << EEPROM_CMD_PROG_Pos)           /*!< 0x00001000 */
#define EEPROM_CMD_PROG                 EEPROM_CMD_PROG_Msk
/* write / read operation (0 - read, 1 - write/erase) */
#define EEPROM_CMD_NVSTR_Pos            (13U)
#define EEPROM_CMD_NVSTR_Msk            (0x1U << EEPROM_CMD_NVSTR_Pos)          /*!< 0x00002000 */
#define EEPROM_CMD_NVSTR                EEPROM_CMD_NVSTR_Msk
/* EEPROM test mode (0 - test enable, 1 - no test) */
#define EEPROM_CMD_TMR_Pos              (14U)
#define EEPROM_CMD_TMR_Msk              (0x1U << EEPROM_CMD_TMR_Pos)            /*!< 0x00004000 */
#define EEPROM_CMD_TMR                  EEPROM_CMD_TMR_Msk

/*
 * ==========================================================================
 * ---------------------- RCC registers bits --------------------------------
 * ==========================================================================
 */

/*******************  hi-speed clock sources **********************************/
#define RST_CLK_HS_CLK_SRC_CPU_C1           (0U)
#define RST_CLK_HS_CLK_SRC_PER_C1           (1U)
#define RST_CLK_HS_CLK_SRC_WDG_C1           (1U)
#define RST_CLK_HS_CLK_SRC_PLLCPU           (2U)
#define RST_CLK_HS_CLK_SRC_HSICLK           (3U)
#define RST_CLK_HS_CLK_SRC_HSECLK           (3U)

/*******************  low-speed clock sources *********************************/
#define RST_CLK_LS_CLK_SRC_LSI				(0U)
#define RST_CLK_LS_CLK_SRC_LSI_2			(1U)
#define RST_CLK_LS_CLK_SRC_LSE				(2U)
#define RST_CLK_LS_CLK_SRC_LSE_2			(3U)

/*******************  3-bit encoded divisors (up to 128) **********************/
#define RST_CLK_3BIT_DIV_1                  (0U)
#define RST_CLK_3BIT_DIV_2                  (1U)
#define RST_CLK_3BIT_DIV_4                  (2U)
#define RST_CLK_3BIT_DIV_8                  (3U)
#define RST_CLK_3BIT_DIV_16                 (4U)
#define RST_CLK_3BIT_DIV_32                 (5U)
#define RST_CLK_3BIT_DIV_64                 (6U)
#define RST_CLK_3BIT_DIV_128                (7U)
#define RST_CLK_3BIT_DIV_Msk				(7U)

/*******************  4-bit encoded divisors (up to 256) **********************/
#define RST_CLK_4BIT_DIV_1                  (0U)
#define RST_CLK_4BIT_DIV_2                  (8U)
#define RST_CLK_4BIT_DIV_4                  (9U)
#define RST_CLK_4BIT_DIV_8                  (10U)
#define RST_CLK_4BIT_DIV_16                 (11U)
#define RST_CLK_4BIT_DIV_32                 (12U)
#define RST_CLK_4BIT_DIV_64                 (13U)
#define RST_CLK_4BIT_DIV_128                (14U)
#define RST_CLK_4BIT_DIV_256                (15U)
#define RST_CLK_4BIT_DIV_Msk				(15U)

/*******************  Bit definition for RST_CLK_CLOCK_STATUS register ************/
/* PLL CPU RDY flag, 0 - PLL is not activated or not stable, 1 - PLL ongoing and stable */
#define RST_CLK_CLOCK_STATUS_PLLRDY_Pos     (1U)
#define RST_CLK_CLOCK_STATUS_PLLRDY_Msk     (0x1U << RST_CLK_CLOCK_STATUS_PLLRDY_Pos)   /*!< 0x00000002 */
#define RST_CLK_CLOCK_STATUS_PLLRDY         RST_CLK_CLOCK_STATUS_PLLRDY_Msk
/* PLL HSE RDY flag, 0 - HSE is not activate or not stable, 1 - HSE ongoing and stable */
#define RST_CLK_CLOCK_STATUS_HSERDY_Pos     (2U)
#define RST_CLK_CLOCK_STATUS_HSERDY_Msk     (0x1U << RST_CLK_CLOCK_STATUS_HSERDY_Pos)   /*!< 0x00000004 */
#define RST_CLK_CLOCK_STATUS_HSERDY         RST_CLK_CLOCK_STATUS_HSERDY_Msk

/*******************  Bit definition for RST_CLK_PLL_CONTROL register *************/
/* PLL CPU ON, 0 - PLL disabled, 1 - PLL enabled */
#define RST_CLK_PLL_CONTROL_PLLON_Pos       (2U)
#define RST_CLK_PLL_CONTROL_PLLON_Msk       (0x1U << RST_CLK_PLL_CONTROL_PLLON_Pos)     /*!< 0x00000004 */
#define RST_CLK_PLL_CONTROL_PLLON           RST_CLK_PLL_CONTROL_PLLON_Msk
/* PLL CPU SEL, 0 - HSE, 1 - CPU_C1_SEL[1:0] */
#define RST_CLK_PLL_CONTROL_PLLSEL_Pos      (3U)
#define RST_CLK_PLL_CONTROL_PLLSEL_Msk      (0x1U << RST_CLK_PLL_CONTROL_PLLSEL_Pos)    /*!< 0x00000008 */
#define RST_CLK_PLL_CONTROL_PLLSEL_HSE	    (0x0U << RST_CLK_PLL_CONTROL_PLLSEL_Pos)
#define RST_CLK_PLL_CONTROL_PLLSEL_CPUC1	(0x1U << RST_CLK_PLL_CONTROL_PLLSEL_Pos)
/* PLL CPU MUL, PLL multiplication (MUL[2:0] + 1) */
#define RST_CLK_PLL_CONTROL_PLLMUL_Pos      (8U)
#define RST_CLK_PLL_CONTROL_PLLMUL_Msk      (0x7U << RST_CLK_PLL_CONTROL_PLLMUL_Pos)    /*!< 0x00000070 */

/*******************  Bit definition for RST_CLK_HS_CONTROL register **************/
/* HSE ON, 0 - HSE disabled, 1 - HSE enabled */
#define RST_CLK_HS_CONTROL_HSEON_Pos        (0U)
#define RST_CLK_HS_CONTROL_HSEON_Msk        (0x1U << RST_CLK_HS_CONTROL_HSEON_Pos)      /*!< 0x00000001 */
#define RST_CLK_HS_CONTROL_HSEON            RST_CLK_HS_CONTROL_HSEON_Msk
/* HSE BYP, 0 - HSE active, 1 - HSE bypassed (external HS sygnal) */
#define RST_CLK_HS_CONTROL_HSEBYP_Pos       (1U)
#define RST_CLK_HS_CONTROL_HSEBYP_Msk       (0x1U << RST_CLK_HS_CONTROL_HSEBYP_Pos)     /*!< 0x00000002 */
#define RST_CLK_HS_CONTROL_HSEBYP           RST_CLK_HS_CONTROL_HSEBYP_Msk

/*******************  Bit definition for RST_CLK_CPU_CLOCK register ***************/
/* CPU_C1 frequency source - HSI, HSE or HSI/2, HSE/2 */
#define RST_CLK_CPU_CLOCK_CPUC1SEL_Pos      (0U)
#define RST_CLK_CPU_CLOCK_CPUC1SEL_Msk      (0x3U << RST_CLK_CPU_CLOCK_CPUC1SEL_Pos)    /*!< 0x00000003 */
#define RST_CLK_CPU_CLOCK_CPUC1SEL          RST_CLK_CPU_CLOCK_CPUC1SEL_Msk
#define RST_CLK_CPU_CLOCK_CPUC1SEL_HSI      (0x0U << RST_CLK_CPU_CLOCK_CPUC1SEL_Pos)    /*!< 0x00000000 */
#define RST_CLK_CPU_CLOCK_CPUC1SEL_HSI_2    (0x1U << RST_CLK_CPU_CLOCK_CPUC1SEL_Pos)    /*!< 0x00000001 */
#define RST_CLK_CPU_CLOCK_CPUC1SEL_HSE      (0x2U << RST_CLK_CPU_CLOCK_CPUC1SEL_Pos)    /*!< 0x00000002 */
#define RST_CLK_CPU_CLOCK_CPUC1SEL_HSE_2    (0x3U << RST_CLK_CPU_CLOCK_CPUC1SEL_Pos)    /*!< 0x00000003 */
/* CPU_C2 frequency source (0 - CPU_C1, 1 - PLLCPU) */
#define RST_CLK_CPU_CLOCK_CPUC2SEL_Pos      (2U)
#define RST_CLK_CPU_CLOCK_CPUC2SEL_Msk      (0x1U << RST_CLK_CPU_CLOCK_CPUC2SEL_Pos)    /*!< 0x00000004 */
#define RST_CLK_CPU_CLOCK_CPUC2SEL_CPUC1	(0x0U << RST_CLK_CPU_CLOCK_CPUC2SEL_Pos)
#define RST_CLK_CPU_CLOCK_CPUC2SEL_PLLCPU	(0x1U << RST_CLK_CPU_CLOCK_CPUC2SEL_Pos)
/* CPU_C3 divisor (0b0*** - CPU_C2, 0b1000 - CPU_C2 / 2, 0b1001 - CPU_C2 / 4 ... 0b1111 - CPU_C2 / 256) */
#define RST_CLK_CPU_CLOCK_CPUC3SEL_Pos      (4U)
#define RST_CLK_CPU_CLOCK_CPUC3SEL_Msk      (0xFU << RST_CLK_CPU_CLOCK_CPUC3SEL_Pos)    /*!< 0x000000F0 */
#define RST_CLK_CPU_CLOCK_CPUC3SEL          RST_CLK_CPU_CLOCK_CPUC3SEL_Pos
/* HCLK_SEL source (0b00 - HSI, 0b01 - CPU_C3, 0b10 - LSE, 0b11 - LSI) */
#define RST_CLK_CPU_CLOCK_HCLKSEL_Pos       (8U)
#define RST_CLK_CPU_CLOCK_HCLKSEL_Msk       (0x3U << RST_CLK_CPU_CLOCK_HCLKSEL_Pos)     /*!< 0x00000300 */
#define RST_CLK_CPU_CLOCK_HCLKSEL           RST_CLK_CPU_CLOCK_HCLKSEL_Pos
#define RST_CLK_CPU_CLOCK_HCLKSEL_HSI       (0x0U << RST_CLK_CPU_CLOCK_HCLKSEL_Pos)     /*!< 0x00000000 */
#define RST_CLK_CPU_CLOCK_HCLKSEL_CPUC3     (0x1U << RST_CLK_CPU_CLOCK_HCLKSEL_Pos)     /*!< 0x00000100 */
#define RST_CLK_CPU_CLOCK_HCLKSEL_LSE       (0x2U << RST_CLK_CPU_CLOCK_HCLKSEL_Pos)     /*!< 0x00000200 */
#define RST_CLK_CPU_CLOCK_HCLKSEL_LSI       (0x3U << RST_CLK_CPU_CLOCK_HCLKSEL_Pos)     /*!< 0x00000300 */

/*******************  Bit definition for RST_CLK_PER1_CLOCK register **************/
/* PER1_CLOCK C1 frequency source (0b00 - LSI, 0b01 - LSI/2, 0b10 - LSE, 0b11 - LSE/2) */
#define RST_CLK_PER_CLOCK_PERC1SEL_Pos      (0U)
#define RST_CLK_PER_CLOCK_PERC1SEL_Msk      (0x3U << RST_CLK_PER_CLOCK_PERC1SEL_Pos)    /*!< 0x00000003 */
#define RST_CLK_PER_CLOCK_PERC1SEL          RST_CLK_PER_CLOCK_PERC1SEL_Msk
#define RST_CLK_PER_CLOCK_PERC1SEL_LSI      (RST_CLK_LS_CLK_SRC_LSI << RST_CLK_PER_CLOCK_PERC1SEL_Pos)
#define RST_CLK_PER_CLOCK_PERC1SEL_LSI_2    (RST_CLK_LS_CLK_SRC_LSI_2 << RST_CLK_PER_CLOCK_PERC1SEL_Pos)
#define RST_CLK_PER_CLOCK_PERC1SEL_LSE      (RST_CLK_LS_CLK_SRC_LSE << RST_CLK_PER_CLOCK_PERC1SEL_Pos)
#define RST_CLK_PER_CLOCK_PERC1SEL_LSE_2    (RST_CLK_LS_CLK_SRC_LSE_2 << RST_CLK_PER_CLOCK_PERC1SEL_Pos)
/* PER1_CLOCK C2 frequency source (0b00 - CPU_C1, 0b01 - PER1_C1, 0b10 - PLLCPU, 0b11 - HSI_CLK) */
#define RST_CLK_PER_CLOCK_PERC2SEL_Pos      (2U)
#define RST_CLK_PER_CLOCK_PERC2SEL_Msk      (0x3U << RST_CLK_PER_CLOCK_PERC2SEL_Pos)    /*!< 0x0000000C */
#define RST_CLK_PER_CLOCK_PERC2SEL          RST_CLK_PER_CLOCK_PERC2SEL_Msk
#define RST_CLK_PER_CLOCK_PERC2SEL_CPUC1    (RST_CLK_HS_CLK_SRC_CPU_C1 << RST_CLK_PER_CLOCK_PERC2SEL_Pos)
#define RST_CLK_PER_CLOCK_PERC2SEL_PER1C1   (RST_CLK_HS_CLK_SRC_PER_C1 << RST_CLK_PER_CLOCK_PERC2SEL_Pos)
#define RST_CLK_PER_CLOCK_PERC2SEL_PLLCPU   (RST_CLK_HS_CLK_SRC_PLLCPU << RST_CLK_PER_CLOCK_PERC2SEL_Pos)
#define RST_CLK_PER_CLOCK_PERC2SEL_HSICLK   (RST_CLK_HS_CLK_SRC_HSICLK << RST_CLK_PER_CLOCK_PERC2SEL_Pos)
/* Key reset prog - resets all crypto keys */
#define RST_CLK_PER_CLOCK_KEYRESPROG_Pos    (4U)
#define RST_CLK_PER_CLOCK_KEYRESPROG_Msk    (0x1U << RST_CLK_PER_CLOCK_KEYRESPROG_Pos)  /*!< 0x00000010 */
#define RST_CLK_PER_CLOCK_KEYRESPROG        RST_CLK_PER_CLOCK_KEYRESPROG_Msk
/* DMA enable register (0 - DMA disabled , 1 - DMA enabled) */
#define RST_CLK_PER_CLOCK_DMAEN_Pos         (5U)
#define RST_CLK_PER_CLOCK_DMAEN_Msk         (0x1U << RST_CLK_PER_CLOCK_DMAEN_Pos)       /*!< 0x00000020 */
#define RST_CLK_PER_CLOCK_DMAEN             RST_CLK_PER_CLOCK_DMAEN_Msk
/* WDG_C1 frequency source (0b00 - LSI, 0b01 - LSI/2, 0b10 - LSE, 0b11 - LSE/2) */
#define RST_CLK_PER_CLOCK_WDGC1SEL_Pos      (6U)
#define RST_CLK_PER_CLOCK_WDGC1SEL_Msk      (0x3U << RST_CLK_PER_CLOCK_WDGC1SEL_Pos)    /*!< 0x000000C0 */
#define RST_CLK_PER_CLOCK_WDGC1SEL          RST_CLK_PER_CLOCK_WDGC1SEL_Msk
#define RST_CLK_PER_CLOCK_WDGC1SEL_LSI      (RST_CLK_LS_CLK_SRC_LSI << RST_CLK_PER_CLOCK_WDGC1SEL_Pos)
#define RST_CLK_PER_CLOCK_WDGC1SEL_LSI_2    (RST_CLK_LS_CLK_SRC_LSI_2 << RST_CLK_PER_CLOCK_WDGC1SEL_Pos)
#define RST_CLK_PER_CLOCK_WDGC1SEL_LSE      (RST_CLK_LS_CLK_SRC_LSE << RST_CLK_PER_CLOCK_WDGC1SEL_Pos)
#define RST_CLK_PER_CLOCK_WDGC1SEL_LSE_2    (RST_CLK_LS_CLK_SRC_LSE_2 << RST_CLK_PER_CLOCK_WDGC1SEL_Pos)
/* WDG C2 frequency source (0b00 - CPU_C1, 0b01 - WDG_C1, 0b10 - PLLCPU, 0b11 - HSI_CLK) */
#define RST_CLK_PER_CLOCK_WDGC2SEL_Pos      (8U)
#define RST_CLK_PER_CLOCK_WDGC2SEL_Msk      (0x3U << RST_CLK_PER_CLOCK_WDGC2SEL_Pos)    /*!< 0x00000300 */
#define RST_CLK_PER_CLOCK_WDGC2SEL          RST_CLK_PER_CLOCK_WDGC2SEL_Msk
#define RST_CLK_PER_CLOCK_WDGC2SEL_CPUC1    (RST_CLK_HS_CLK_SRC_CPU_C1 << RST_CLK_PER_CLOCK_WDGC2SEL_Pos)
#define RST_CLK_PER_CLOCK_WDGC2SEL_WDGC1    (RST_CLK_HS_CLK_SRC_WDG_C1 << RST_CLK_PER_CLOCK_WDGC2SEL_Pos)
#define RST_CLK_PER_CLOCK_WDGC2SEL_PLLCPU   (RST_CLK_HS_CLK_SRC_PLLCPU << RST_CLK_PER_CLOCK_WDGC2SEL_Pos)
#define RST_CLK_PER_CLOCK_WDGC2SEL_HSICLK   (RST_CLK_HS_CLK_SRC_HSICLK << RST_CLK_PER_CLOCK_WDGC2SEL_Pos)
/* WDG BRG - divisior of the WDG frequency - 2^n */
#define RST_CLK_PER_CLOCK_WDGBRG_Pos        (10U)
#define RST_CLK_PER_CLOCK_WDGBRG_Msk        (0x7U << RST_CLK_PER_CLOCK_WDGBRG_Pos)      /*!< 0x00001C00 */
#define RST_CLK_PER_CLOCK_WDGBRG            RST_CLK_PER_CLOCK_WDGBRG_Msk
/* WDG CLK EN - enable watchdog (0 - disabled, 1 - enabled) */
#define RST_CLK_PER_CLOCK_WDGCLKEN_Pos      (13U)
#define RST_CLK_PER_CLOCK_WDGCLKEN_Msk      (0x1U << RST_CLK_PER_CLOCK_WDGCLKEN_Pos)    /*!< 0x00002000 */
#define RST_CLK_PER_CLOCK_WDGCLKEN          RST_CLK_PER_CLOCK_WDGCLKEN_Msk

/*******************  Bit definition for RST_CLK_ADC_CLOCK register ***************/
/* ADC_C1 frequency source (0b00 - CPU_C1, 0b01 - PER1_C1, 0b10 - PLLCPU, 0b11 - HSECLK) */
#define RST_CLK_ADC_CLOCK_ADCC1SEL_Pos      (0U)
#define RST_CLK_ADC_CLOCK_ADCC1SEL_Msk      (0x3U << RST_CLK_ADC_CLOCK_ADCC1SEL_Pos)    /*!< 0x00000003 */
#define RST_CLK_ADC_CLOCK_ADCC1SEL          RST_CLK_ADC_CLOCK_ADCC1SEL_Msk
#define RST_CLK_ADC_CLOCK_ADCC1SEL_CPUC1    (RST_CLK_HS_CLK_SRC_CPU_C1 << RST_CLK_ADC_CLOCK_ADCC1SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADCC1SEL_PER1C1   (RST_CLK_HS_CLK_SRC_PER_C1 << RST_CLK_ADC_CLOCK_ADCC1SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADCC1SEL_PLLCPU   (RST_CLK_HS_CLK_SRC_PLLCPU << RST_CLK_ADC_CLOCK_ADCC1SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADCC1SEL_HSECLK   (RST_CLK_HS_CLK_SRC_HSECLK << RST_CLK_ADC_CLOCK_ADCC1SEL_Pos)
/* ADC IU C1 frequency source (0b00 - CPU_C1, 0b01 - PER1_C1, 0b10 - PLLCPU, 0b11 - HSECLK) */
#define RST_CLK_ADC_CLOCK_ADCUIC1SEL_Pos    (2U)
#define RST_CLK_ADC_CLOCK_ADCUIC1SEL_Msk    (0x3U << RST_CLK_ADC_CLOCK_ADCUIC1SEL_Pos)  /*!< 0x0000000C */
#define RST_CLK_ADC_CLOCK_ADCUIC1SEL        RST_CLK_ADC_CLOCK_ADCUIC1SEL_Msk
#define RST_CLK_ADC_CLOCK_ADCUIC1SEL_CPUC1  (RST_CLK_HS_CLK_SRC_CPU_C1 << RST_CLK_ADC_CLOCK_ADCUIC1SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADCUIC1SEL_PER1C1 (RST_CLK_HS_CLK_SRC_PER_C1 << RST_CLK_ADC_CLOCK_ADCUIC1SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADCUIC1SEL_PLLCPU (RST_CLK_HS_CLK_SRC_PLLCPU << RST_CLK_ADC_CLOCK_ADCUIC1SEL_Pos)
#define RST_CLK_ADC_CLOCK_ADCUIC1SEL_HSECLK (RST_CLK_HS_CLK_SRC_HSECLK << RST_CLK_ADC_CLOCK_ADCUIC1SEL_Pos)
/* ADCUI C3 divisor (ADCUIC3 = ADCUIC1 / div, 0b0*** - 1, 0b1000 - 2, 0b1001 - 4, ... 0b1111 - 256) */
#define RST_CLK_ADC_CLOCK_ADCUIC3SEL_Pos    (4U)
#define RST_CLK_ADC_CLOCK_ADCUIC3SEL_Msk    (0xFU << RST_CLK_ADC_CLOCK_ADCUIC3SEL_Pos)  /*!< 0x000000F0 */
#define RST_CLK_ADC_CLOCK_ADCUIC3SEL        RST_CLK_ADC_CLOCK_ADCUIC3SEL_Msk
/* ADC C3 divisor (ADCC3 = ADCC1 / div, 0b0*** - 1, 0b1000 - 2, 0b1001 - 4, ... 0b1111 - 256) */
#define RST_CLK_ADC_CLOCK_ADCC3SEL_Pos      (8U)
#define RST_CLK_ADC_CLOCK_ADCC3SEL_Msk      (0xFU << RST_CLK_ADC_CLOCK_ADCC3SEL_Pos)    /*!< 0x00000F00 */
#define RST_CLK_ADC_CLOCK_ADCC3SEL          RST_CLK_ADC_CLOCK_ADCC3SEL_Msk
/* ADC IU CLK enable (0 - disabled, 1 - enabled) */
#define RST_CLK_ADC_CLOCK_ADCUI_CLKEN_Pos   (12U)
#define RST_CLK_ADC_CLOCK_ADCUI_CLKEN_Msk   (0x1U << RST_CLK_ADC_CLOCK_ADCUI_CLKEN_Pos) /*!< 0x00001000 */
#define RST_CLK_ADC_CLOCK_ADCUI_CLKEN       RST_CLK_ADC_CLOCK_ADCUI_CLKEN_Msk
/* ADC CLK enable (0 - disabled, 1 - enabled) */
#define RST_CLK_ADC_CLOCK_ADC_CLKEN_Pos     (13U)
#define RST_CLK_ADC_CLOCK_ADC_CLKEN_Msk     (0x1U << RST_CLK_ADC_CLOCK_ADC_CLKEN_Pos)   /*!< 0x00002000 */
#define RST_CLK_ADC_CLOCK_ADC_CLKEN         RST_CLK_ADC_CLOCK_ADC_CLKEN_Msk

/*******************  Bit definition for RST_CLK_RTC_CLOCK register ***************/
/* HSE C1 clock divisor (HSE_C1 = HSE / div, 0b0*** - 1, 0b1000 - 2, 0b1001 - 4, ... 0b1111 - 256) */
#define RST_CLK_RTC_CLOCK_HSESEL_Pos        (0U)
#define RST_CLK_RTC_CLOCK_HSESEL_Msk        (0xFU << RST_CLK_RTC_CLOCK_HSESEL_Pos)      /*!< 0x0000000F */
#define RST_CLK_RTC_CLOCK_HSESEL            RST_CLK_RTC_CLOCK_HSESEL_Msk
/* HSI C1 clock divisor (HSI_C1 = HSI / div, 0b0*** - 1, 0b1000 - 2, 0b1001 - 4, ... 0b1111 - 256) */
#define RST_CLK_RTC_CLOCK_HSISEL_Pos        (4U)
#define RST_CLK_RTC_CLOCK_HSISEL_Msk        (0xFU << RST_CLK_RTC_CLOCK_HSISEL_Pos)      /*!< 0x000000F0 */
#define RST_CLK_RTC_CLOCK_HSISEL            RST_CLK_RTC_CLOCK_HSISEL_Msk
/* HSE RTC enable (0 - disabled, 1 - enabled) */
#define RST_CLK_RTC_CLOCK_HSERTCEN_Pos      (8U)
#define RST_CLK_RTC_CLOCK_HSERTCEN_Msk      (0x1U << RST_CLK_RTC_CLOCK_HSERTCEN_Pos)    /*!< 0x00000100 */
#define RST_CLK_RTC_CLOCK_HSERTCEN          RST_CLK_RTC_CLOCK_HSERTCEN_Msk
/* HSI RTC enable (0 - disabled, 1 - enabled) */
#define RST_CLK_RTC_CLOCK_HSIRTCEN_Pos      (9U)
#define RST_CLK_RTC_CLOCK_HSIRTCEN_Msk      (0x1U << RST_CLK_RTC_CLOCK_HSIRTCEN_Pos)    /*!< 0x00000200 */
#define RST_CLK_RTC_CLOCK_HSIRTCEN          RST_CLK_RTC_CLOCK_HSIRTCEN_Msk

/*******************  Bit definition for RST_CLK_PER2_CLOCK register **************/
/* SPI1 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_SPI1EN_Pos       (0U)
#define RST_CLK_PER2_CLOCK_SPI1EN_Msk       (0x1U << RST_CLK_PER2_CLOCK_SPI1EN_Pos)     /*!< 0x00000001 */
#define RST_CLK_PER2_CLOCK_SPI1EN           RST_CLK_PER2_CLOCK_SPI1EN_Msk
/* UART1 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_UART1EN_Pos      (1U)
#define RST_CLK_PER2_CLOCK_UART1EN_Msk      (0x1U << RST_CLK_PER2_CLOCK_UART1EN_Pos)    /*!< 0x00000002 */
#define RST_CLK_PER2_CLOCK_UART1EN          RST_CLK_PER2_CLOCK_UART1EN_Msk
/* UART2 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_UART2EN_Pos      (2U)
#define RST_CLK_PER2_CLOCK_UART2EN_Msk      (0x1U << RST_CLK_PER2_CLOCK_UART2EN_Pos)    /*!< 0x00000004 */
#define RST_CLK_PER2_CLOCK_UART2EN          RST_CLK_PER2_CLOCK_UART2EN_Msk
/* EEPROM clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_EEPROMEN_Pos     (3U)
#define RST_CLK_PER2_CLOCK_EEPROMEN_Msk     (0x1U << RST_CLK_PER2_CLOCK_EEPROMEN_Pos)   /*!< 0x00000008 */
#define RST_CLK_PER2_CLOCK_EEPROMEN         RST_CLK_PER2_CLOCK_EEPROMEN_Msk
/* RST_CLK clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_RST_CLKEN_Pos    (4U)
#define RST_CLK_PER2_CLOCK_RST_CLKEN_Msk    (0x1U << RST_CLK_PER2_CLOCK_RST_CLKEN_Pos)  /*!< 0x00000010 */
#define RST_CLK_PER2_CLOCK_RST_CLKEN        RST_CLK_PER2_CLOCK_RST_CLKEN_Msk
/* DMA clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_DMAEN_Pos        (5U)
#define RST_CLK_PER2_CLOCK_DMAEN_Msk        (0x1U << RST_CLK_PER2_CLOCK_DMAEN_Pos)      /*!< 0x00000020 */
#define RST_CLK_PER2_CLOCK_DMAEN            RST_CLK_PER2_CLOCK_DMAEN_Msk
/* I2C clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_I2CEN_Pos        (6U)
#define RST_CLK_PER2_CLOCK_I2CEN_Msk        (0x1U << RST_CLK_PER2_CLOCK_I2CEN_Pos)      /*!< 0x00000040 */
#define RST_CLK_PER2_CLOCK_I2CEN            RST_CLK_PER2_CLOCK_I2CEN_Msk
/* UART3 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_UART3EN_Pos      (7U)
#define RST_CLK_PER2_CLOCK_UART3EN_Msk      (0x1U << RST_CLK_PER2_CLOCK_UART3EN_Pos)    /*!< 0x00000080 */
#define RST_CLK_PER2_CLOCK_UART3EN          RST_CLK_PER2_CLOCK_UART3EN_Msk
/* ADC clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_ADCEN_Pos        (8U)
#define RST_CLK_PER2_CLOCK_ADCEN_Msk        (0x1U << RST_CLK_PER2_CLOCK_ADCEN_Pos)      /*!< 0x00000100 */
#define RST_CLK_PER2_CLOCK_ADCEN            RST_CLK_PER2_CLOCK_ADCEN_Msk
/* WWDG clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_WWDGEN_Pos       (9U)
#define RST_CLK_PER2_CLOCK_WWDGEN_Msk       (0x1U << RST_CLK_PER2_CLOCK_WWDGEN_Pos)     /*!< 0x00000200 */
#define RST_CLK_PER2_CLOCK_WWDGEN           RST_CLK_PER2_CLOCK_WWDGEN_Msk
/* IWDG clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_IWDGEN_Pos       (10U)
#define RST_CLK_PER2_CLOCK_IWDGEN_Msk       (0x1U << RST_CLK_PER2_CLOCK_IWDGEN_Pos)     /*!< 0x00000400 */
#define RST_CLK_PER2_CLOCK_IWDGEN           RST_CLK_PER2_CLOCK_IWDGEN_Msk
/* POWER clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_POWEREN_Pos      (11U)
#define RST_CLK_PER2_CLOCK_POWEREN_Msk      (0x1U << RST_CLK_PER2_CLOCK_POWEREN_Pos)    /*!< 0x00000800 */
#define RST_CLK_PER2_CLOCK_POWEREN          RST_CLK_PER2_CLOCK_POWEREN_Msk
/* BKP clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_BKPEN_Pos        (12U)
#define RST_CLK_PER2_CLOCK_BKPEN_Msk        (0x1U << RST_CLK_PER2_CLOCK_BKPEN_Pos)      /*!< 0x00001000 */
#define RST_CLK_PER2_CLOCK_BKPEN            RST_CLK_PER2_CLOCK_BKPEN_Msk
/* ADCUI clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_ADCUIEN_Pos      (13U)
#define RST_CLK_PER2_CLOCK_ADCUIEN_Msk      (0x1U << RST_CLK_PER2_CLOCK_ADCUIEN_Pos)    /*!< 0x00002000 */
#define RST_CLK_PER2_CLOCK_ADCUIEN          RST_CLK_PER2_CLOCK_ADCUIEN_Msk
/* TIMER1 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_TIMER1EN_Pos     (14U)
#define RST_CLK_PER2_CLOCK_TIMER1EN_Msk     (0x1U << RST_CLK_PER2_CLOCK_TIMER1EN_Pos)   /*!< 0x00004000 */
#define RST_CLK_PER2_CLOCK_TIMER1EN         RST_CLK_PER2_CLOCK_TIMER1EN_Msk
/* TIMER2 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_TIMER2EN_Pos     (15U)
#define RST_CLK_PER2_CLOCK_TIMER2EN_Msk     (0x1U << RST_CLK_PER2_CLOCK_TIMER2EN_Pos)   /*!< 0x00008000 */
#define RST_CLK_PER2_CLOCK_TIMER2EN         RST_CLK_PER2_CLOCK_TIMER2EN_Msk
/* PORTA clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_PORTAEN_Pos      (16U)
#define RST_CLK_PER2_CLOCK_PORTAEN_Msk      (0x1U << RST_CLK_PER2_CLOCK_PORTAEN_Pos)    /*!< 0x00010000 */
#define RST_CLK_PER2_CLOCK_PORTAEN          RST_CLK_PER2_CLOCK_PORTAEN_Msk
/* PORTB clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_PORTBEN_Pos      (17U)
#define RST_CLK_PER2_CLOCK_PORTBEN_Msk      (0x1U << RST_CLK_PER2_CLOCK_PORTBEN_Pos)    /*!< 0x00020000 */
#define RST_CLK_PER2_CLOCK_PORTBEN          RST_CLK_PER2_CLOCK_PORTBEN_Msk
/* PORTC clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_PORTCEN_Pos      (18U)
#define RST_CLK_PER2_CLOCK_PORTCEN_Msk      (0x1U << RST_CLK_PER2_CLOCK_PORTCEN_Pos)    /*!< 0x00040000 */
#define RST_CLK_PER2_CLOCK_PORTCEN          RST_CLK_PER2_CLOCK_PORTCEN_Msk
/* CRC clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_CRCEN_Pos        (19U)
#define RST_CLK_PER2_CLOCK_CRCEN_Msk        (0x1U << RST_CLK_PER2_CLOCK_CRCEN_Pos)      /*!< 0x00080000 */
#define RST_CLK_PER2_CLOCK_CRCEN            RST_CLK_PER2_CLOCK_CRCEN_Msk
/* SENSORS clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_SENSORSEN_Pos    (21U)
#define RST_CLK_PER2_CLOCK_SENSORSEN_Msk    (0x1U << RST_CLK_PER2_CLOCK_SENSORSEN_Pos)  /*!< 0x00200000 */
#define RST_CLK_PER2_CLOCK_SENSORSEN        RST_CLK_PER2_CLOCK_SENSORSEN_Msk
/* CLK_MEASURE clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_CLKMEASUREEN_Pos (22U)
#define RST_CLK_PER2_CLOCK_CLKMEASUREEN_Msk (0x1U << RST_CLK_PER2_CLOCK_CLKMEASUREEN_Pos) /*!< 0x00400000 */
#define RST_CLK_PER2_CLOCK_CLKMEASUREEN     RST_CLK_PER2_CLOCK_CLKMEASUREEN_Msk
/* RANDOM clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_RANDOMEN_Pos     (23U)
#define RST_CLK_PER2_CLOCK_RANDOMEN_Msk     (0x1U << RST_CLK_PER2_CLOCK_RANDOMEN_Pos)   /*!< 0x00800000 */
#define RST_CLK_PER2_CLOCK_RANDOMEN         RST_CLK_PER2_CLOCK_RANDOMEN_Msk
/* ISO7816 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_ISO7816EN_Pos    (24U)
#define RST_CLK_PER2_CLOCK_ISO7816EN_Msk    (0x1U << RST_CLK_PER2_CLOCK_ISO7816EN_Pos)  /*!< 0x01000000 */
#define RST_CLK_PER2_CLOCK_ISO7816EN        RST_CLK_PER2_CLOCK_ISO7816EN_Msk
/* SPI2 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_SPI2EN_Pos       (25U)
#define RST_CLK_PER2_CLOCK_SPI2EN_Msk       (0x1U << RST_CLK_PER2_CLOCK_SPI2EN_Pos)     /*!< 0x02000000 */
#define RST_CLK_PER2_CLOCK_SPI2EN           RST_CLK_PER2_CLOCK_SPI2EN_Msk
/* SPI3 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_SPI3EN_Pos       (26U)
#define RST_CLK_PER2_CLOCK_SPI3EN_Msk       (0x1U << RST_CLK_PER2_CLOCK_SPI3EN_Pos)     /*!< 0x04000000 */
#define RST_CLK_PER2_CLOCK_SPI3EN           RST_CLK_PER2_CLOCK_SPI3EN_Msk
/* TIMER3 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_TIMER3EN_Pos     (27U)
#define RST_CLK_PER2_CLOCK_TIMER3EN_Msk     (0x1U << RST_CLK_PER2_CLOCK_TIMER3EN_Pos)   /*!< 0x08000000 */
#define RST_CLK_PER2_CLOCK_TIMER3EN         RST_CLK_PER2_CLOCK_TIMER3EN_Msk
/* TIMER4 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_TIMER4EN_Pos     (28U)
#define RST_CLK_PER2_CLOCK_TIMER4EN_Msk     (0x1U << RST_CLK_PER2_CLOCK_TIMER4EN_Pos)   /*!< 0x10000000 */
#define RST_CLK_PER2_CLOCK_TIMER4EN         RST_CLK_PER2_CLOCK_TIMER4EN_Msk
/* UART4 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_UART4EN_Pos      (29U)
#define RST_CLK_PER2_CLOCK_UART4EN_Msk      (0x1U << RST_CLK_PER2_CLOCK_UART4EN_Pos)    /*!< 0x20000000 */
#define RST_CLK_PER2_CLOCK_UART4EN          RST_CLK_PER2_CLOCK_UART4EN_Msk
/* PORTD clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_PER2_CLOCK_PORTDEN_Pos      (30U)
#define RST_CLK_PER2_CLOCK_PORTDEN_Msk      (0x1U << RST_CLK_PER2_CLOCK_PORTDEN_Pos)    /*!< 0x40000000 */
#define RST_CLK_PER2_CLOCK_PORTDEN          RST_CLK_PER2_CLOCK_PORTDEN_Msk

/*******************  Bit definition for RST_CLK_TIM_CLOCK register ***************/
/* TIM1 frequency divisor, TIM1_CLK = PER1_C2 / div, div = 2^TIM1_BRG, only 3 LSB make sense */
#define RST_CLK_TIM_CLOCK_TIM1BRG_Pos       (0U)
#define RST_CLK_TIM_CLOCK_TIM1BRG_Msk       (0xFFU << RST_CLK_TIM_CLOCK_TIM1BRG_Pos)    /*!< 0x000000FF */
#define RST_CLK_TIM_CLOCK_TIM1BRG           RST_CLK_TIM_CLOCK_TIM1BRG_Msk
/* TIM2 frequency divisor, TIM2_CLK = PER1_C2 / div, div = 2^TIM2_BRG, only 3 LSB make sense */
#define RST_CLK_TIM_CLOCK_TIM2BRG_Pos       (8U)
#define RST_CLK_TIM_CLOCK_TIM2BRG_Msk       (0xFFU << RST_CLK_TIM_CLOCK_TIM2BRG_Pos)    /*!< 0x0000FF00 */
#define RST_CLK_TIM_CLOCK_TIM2BRG           RST_CLK_TIM_CLOCK_TIM2BRG_Msk
/* TIM3 frequency divisor, TIM3_CLK = PER1_C2 / div, div = 2^TIM3_BRG, only 3 LSB make sense */
#define RST_CLK_TIM_CLOCK_TIM3BRG_Pos       (16U)
#define RST_CLK_TIM_CLOCK_TIM3BRG_Msk       (0x7U << RST_CLK_TIM_CLOCK_TIM3BRG_Pos)     /*!< 0x00070000 */
#define RST_CLK_TIM_CLOCK_TIM3BRG           RST_CLK_TIM_CLOCK_TIM3BRG_Msk
/* TIM4 frequency divisor, TIM4_CLK = PER1_C2 / div, div = 2^TIM4_BRG, only 3 LSB make sense */
#define RST_CLK_TIM_CLOCK_TIM4BRG_Pos       (19U)
#define RST_CLK_TIM_CLOCK_TIM4BRG_Msk       (0x1FU << RST_CLK_TIM_CLOCK_TIM4BRG_Pos)    /*!< 0x00F80000 */
#define RST_CLK_TIM_CLOCK_TIM4BRG           RST_CLK_TIM_CLOCK_TIM4BRG_Msk
/* TIM1 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_TIM_CLOCK_TIM1CLKEN_Pos     (24U)
#define RST_CLK_TIM_CLOCK_TIM1CLKEN_Msk     (0x1FU << RST_CLK_TIM_CLOCK_TIM1CLKEN_Pos)  /*!< 0x01000000 */
#define RST_CLK_TIM_CLOCK_TIM1CLKEN         RST_CLK_TIM_CLOCK_TIM1CLKEN_Msk
/* TIM2 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_TIM_CLOCK_TIM2CLKEN_Pos     (25U)
#define RST_CLK_TIM_CLOCK_TIM2CLKEN_Msk     (0x1FU << RST_CLK_TIM_CLOCK_TIM2CLKEN_Pos)  /*!< 0x02000000 */
#define RST_CLK_TIM_CLOCK_TIM2CLKEN         RST_CLK_TIM_CLOCK_TIM2CLKEN_Msk
/* TIM3 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_TIM_CLOCK_TIM3CLKEN_Pos     (26U)
#define RST_CLK_TIM_CLOCK_TIM3CLKEN_Msk     (0x1FU << RST_CLK_TIM_CLOCK_TIM3CLKEN_Pos)  /*!< 0x04000000 */
#define RST_CLK_TIM_CLOCK_TIM3CLKEN         RST_CLK_TIM_CLOCK_TIM3CLKEN_Msk
/* TIM4 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_TIM_CLOCK_TIM4CLKEN_Pos     (27U)
#define RST_CLK_TIM_CLOCK_TIM4CLKEN_Msk     (0x1FU << RST_CLK_TIM_CLOCK_TIM4CLKEN_Pos)  /*!< 0x08000000 */
#define RST_CLK_TIM_CLOCK_TIM4CLKEN         RST_CLK_TIM_CLOCK_TIM4CLKEN_Msk

/*******************  Bit definition for RST_CLK_UART_CLOCK register ***************/
/* UART1 frequency divisor, UART1_CLK = PER1_C2 / div, div = 2^UART1_BRG, only 3 LSB make sense */
#define RST_CLK_UART_CLOCK_UART1BRG_Pos     (0U)
#define RST_CLK_UART_CLOCK_UART1BRG_Msk     (0xFFU << RST_CLK_UART_CLOCK_UART1BRG_Pos)  /*!< 0x000000FF */
#define RST_CLK_UART_CLOCK_UART1BRG         RST_CLK_UART_CLOCK_UART1BRG_Msk
/* UART2 frequency divisor, UART2_CLK = PER1_C2 / div, div = 2^UART2_BRG, only 3 LSB make sense */
#define RST_CLK_UART_CLOCK_UART2BRG_Pos     (8U)
#define RST_CLK_UART_CLOCK_UART2BRG_Msk     (0xFFU << RST_CLK_UART_CLOCK_UART2BRG_Pos)  /*!< 0x0000FF00 */
#define RST_CLK_UART_CLOCK_UART2BRG         RST_CLK_UART_CLOCK_UART2BRG_Msk
/* UART3 frequency divisor, UART3_CLK = PER1_C2 / div, div = 2^UART3_BRG, only 3 LSB make sense */
#define RST_CLK_UART_CLOCK_UART3BRG_Pos     (16U)
#define RST_CLK_UART_CLOCK_UART3BRG_Msk     (0xFFU << RST_CLK_UART_CLOCK_UART3BRG_Pos)  /*!< 0x00FF0000 */
#define RST_CLK_UART_CLOCK_UART3BRG         RST_CLK_UART_CLOCK_UART3BRG_Msk
/* UART1 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_UART_CLOCK_UART1CLKEN_Pos   (24U)
#define RST_CLK_UART_CLOCK_UART1CLKEN_Msk   (0x1U << RST_CLK_UART_CLOCK_UART1CLKEN_Pos) /*!< 0x01000000 */
#define RST_CLK_UART_CLOCK_UART1CLKEN       RST_CLK_UART_CLOCK_UART1CLKEN_Msk
/* UART2 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_UART_CLOCK_UART2CLKEN_Pos   (25U)
#define RST_CLK_UART_CLOCK_UART2CLKEN_Msk   (0x1U << RST_CLK_UART_CLOCK_UART2CLKEN_Pos) /*!< 0x02000000 */
#define RST_CLK_UART_CLOCK_UART2CLKEN       RST_CLK_UART_CLOCK_UART2CLKEN_Msk
/* UART3 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_UART_CLOCK_UART3CLKEN_Pos   (26U)
#define RST_CLK_UART_CLOCK_UART3CLKEN_Msk   (0x1U << RST_CLK_UART_CLOCK_UART3CLKEN_Pos) /*!< 0x04000000 */
#define RST_CLK_UART_CLOCK_UART3CLKEN       RST_CLK_UART_CLOCK_UART3CLKEN_Msk
/* UART4 frequency divisor, UART4_CLK = PER1_C2 / div, div = 2^UART4_BRG, only 3 LSB make sense */
#define RST_CLK_UART_CLOCK_UART4BRG_Pos     (27U)
#define RST_CLK_UART_CLOCK_UART4BRG_Msk     (0x7U << RST_CLK_UART_CLOCK_UART4BRG_Pos)   /*!< 0x38000000 */
#define RST_CLK_UART_CLOCK_UART4BRG         RST_CLK_UART_CLOCK_UART4BRG_Msk
/* UART4 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_UART_CLOCK_UART4CLKEN_Pos   (30U)
#define RST_CLK_UART_CLOCK_UART4CLKEN_Msk   (0x1U << RST_CLK_UART_CLOCK_UART4CLKEN_Pos) /*!< 0x40000000 */
#define RST_CLK_UART_CLOCK_UART4CLKEN       RST_CLK_UART_CLOCK_UART4CLKEN_Msk

/*******************  Bit definition for RST_CLK_SSP_CLOCK register ***************/
/* SSP1 frequency divisor, SSP1_CLK = PER1_C2 / div, div = 2^SSP1_BRG, only 3 LSB make sense */
#define RST_CLK_SSP_CLOCK_SSP1BRG_Pos       (0U)
#define RST_CLK_SSP_CLOCK_SSP1BRG_Msk       (0xFFU << RST_CLK_SSP_CLOCK_SSP1BRG_Pos)    /*!< 0x000000FF */
#define RST_CLK_SSP_CLOCK_SSP1BRG           RST_CLK_SSP_CLOCK_SSP1BRG_Msk
/* SSP2 frequency divisor, SSP2_CLK = PER1_C2 / div, div = 2^SSP2_BRG, only 3 LSB make sense */
#define RST_CLK_SSP_CLOCK_SSP2BRG_Pos       (8U)
#define RST_CLK_SSP_CLOCK_SSP2BRG_Msk       (0xFFU << RST_CLK_SSP_CLOCK_SSP2BRG_Pos)    /*!< 0x0000FF00 */
#define RST_CLK_SSP_CLOCK_SSP2BRG           RST_CLK_SSP_CLOCK_SSP2BRG_Msk
/* SSP3 frequency divisor, SSP3_CLK = PER1_C2 / div, div = 2^SSP3_BRG, only 3 LSB make sense */
#define RST_CLK_SSP_CLOCK_SSP3BRG_Pos       (16U)
#define RST_CLK_SSP_CLOCK_SSP3BRG_Msk       (0xFFU << RST_CLK_SSP_CLOCK_SSP3BRG_Pos)    /*!< 0x00FF0000 */
#define RST_CLK_SSP_CLOCK_SSP3BRG           RST_CLK_SSP_CLOCK_SSP3BRG_Msk
/* SSP1 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_SSP_CLOCK_SSP1CLKEN_Pos     (24U)
#define RST_CLK_SSP_CLOCK_SSP1CLKEN_Msk     (0x1U << RST_CLK_SSP_CLOCK_SSP1CLKEN_Pos)  /*!< 0x01000000 */
#define RST_CLK_SSP_CLOCK_SSP1CLKEN         RST_CLK_SSP_CLOCK_SSP1CLKEN_Msk
/* SSP2 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_SSP_CLOCK_SSP2CLKEN_Pos     (25U)
#define RST_CLK_SSP_CLOCK_SSP2CLKEN_Msk     (0x1U << RST_CLK_SSP_CLOCK_SSP2CLKEN_Pos)  /*!< 0x02000000 */
#define RST_CLK_SSP_CLOCK_SSP2CLKEN         RST_CLK_SSP_CLOCK_SSP2CLKEN_Msk
/* SSP3 clock enable (0 - disabled, 1 - enabled) */
#define RST_CLK_SSP_CLOCK_SSP3CLKEN_Pos     (26U)
#define RST_CLK_SSP_CLOCK_SSP3CLKEN_Msk     (0x1U << RST_CLK_SSP_CLOCK_SSP3CLKEN_Pos)  /*!< 0x04000000 */
#define RST_CLK_SSP_CLOCK_SSP3CLKEN         RST_CLK_SSP_CLOCK_SSP3CLKEN_Msk

/*
 * ==========================================================================
 * ---------------------- DMA CHANNEL registers bits ------------------------
 * ==========================================================================
 */

/*******************  Bit definition for DMACH_CFG register *******************/
/* transfer size, addr increment size */
#define DMACH_SIZE_BYTE                 (0U)
#define DMACH_SIZE_2BYTES               (1U)
#define DMACH_SIZE_4BYTES               (2U)
#define DMACH_SIZE_DONOT_INC            (3U)
/* HPROT control bits for DST and SRC HPROT controls */
#define DMACH_HPROT_BIT_CACHE           (4U)
#define DMACH_HPROT_BIT_BUFFER          (2U)
#define DMACH_HPROT_BIT_PRIVILEGED      (1U)
/* channel cycle control */
#define DMACH_CFG_CYCLE_CTRL_Pos        (0U)
#define DMACH_CFG_CYCLE_CTRL_Msk        (0x7U << DMACH_CFG_CYCLE_CTRL_Pos)      /*!< 0x00000007 */
#define DMACH_CFG_CYCLE_CTRL_STOP       (0x0U << DMACH_CFG_CYCLE_CTRL_Pos)
#define DMACH_CFG_CYCLE_CTRL_NORMAL     (0x1U << DMACH_CFG_CYCLE_CTRL_Pos)
#define DMACH_CFG_CYCLE_CTRL_AUTO		(0x2U << DMACH_CFG_CYCLE_CTRL_Pos)
#define DMACH_CFG_CYCLE_CTRL_PINGPONG   (0x3U << DMACH_CFG_CYCLE_CTRL_Pos)
#define DMACH_CFG_CYCLE_CTRL_MEMPROG1   (0x4U << DMACH_CFG_CYCLE_CTRL_Pos)
#define DMACH_CFG_CYCLE_CTRL_MEMPROG2   (0x5U << DMACH_CFG_CYCLE_CTRL_Pos)
#define DMACH_CFG_CYCLE_CTRL_PERPROG1   (0x6U << DMACH_CFG_CYCLE_CTRL_Pos)
#define DMACH_CFG_CYCLE_CTRL_PERPROG2   (0x7U << DMACH_CFG_CYCLE_CTRL_Pos)
/* next use burst */
#define DMACH_CFG_NEXTUSEBURST_Pos      (3U)
#define DMACH_CFG_NEXTUSEBURST_Msk      (0x1U << DMACH_CFG_NEXTUSEBURST_Pos)    /*!< 0x00000008 */
#define DMACH_CFG_NEXTUSEBURST          DMACH_CFG_NEXTUSEBURST_Msk
/* number of transfers */
#define DMACH_CFG_N_MINUS_1_Pos         (4U)
#define DMACH_CFG_N_MINUS_1_Msk         (0x3FFU << DMACH_CFG_N_MINUS_1_Pos)     /*!< 0x00003FF0 */
/* R power - arbitration reqest after R^2 transfers */
#define DMACH_CFG_R_POWER_Pos           (14U)
#define DMACH_CFG_R_POWER_Msk           (0xFU << DMACH_CFG_R_POWER_Pos)         /*!< 0x0003C000 */
#define DMACH_CFG_R_POWER_ARBAFTER_1    (0x0U << DMACH_CFG_R_POWER_Pos)
#define DMACH_CFG_R_POWER_ARBAFTER_2    (0x1U << DMACH_CFG_R_POWER_Pos)
#define DMACH_CFG_R_POWER_ARBAFTER_4    (0x2U << DMACH_CFG_R_POWER_Pos)
#define DMACH_CFG_R_POWER_ARBAFTER_8    (0x3U << DMACH_CFG_R_POWER_Pos)
#define DMACH_CFG_R_POWER_ARBAFTER_16   (0x4U << DMACH_CFG_R_POWER_Pos)
#define DMACH_CFG_R_POWER_ARBAFTER_32   (0x5U << DMACH_CFG_R_POWER_Pos)
#define DMACH_CFG_R_POWER_ARBAFTER_64   (0x6U << DMACH_CFG_R_POWER_Pos)
#define DMACH_CFG_R_POWER_ARBAFTER_128  (0x7U << DMACH_CFG_R_POWER_Pos)
#define DMACH_CFG_R_POWER_ARBAFTER_256  (0x8U << DMACH_CFG_R_POWER_Pos)
#define DMACH_CFG_R_POWER_ARBAFTER_512  (0x9U << DMACH_CFG_R_POWER_Pos)
#define DMACH_CFG_R_POWER_ARBAFTER_1024 (0xAU << DMACH_CFG_R_POWER_Pos)
/* SRC HPROT control */
#define DMACH_CFG_SRCPROTCTRL_Pos       (18U)
#define DMACH_CFG_SRCPROTCTRL_Msk       (0x7U << DMACH_CFG_SRCPROTCTRL_Pos)     /*!< 0x001C0000 */
/* DST HPROT control */
#define DMACH_CFG_DSTPROTCTRL_Pos       (21U)
#define DMACH_CFG_DSTPROTCTRL_Msk       (0x7U << DMACH_CFG_DSTPROTCTRL_Pos)     /*!< 0x00E00000 */
/* SRC size */
#define DMACH_CFG_SRC_SIZE_Pos          (24U)
#define DMACH_CFG_SRC_SIZE_Msk          (0x3U << DMACH_CFG_SRC_SIZE_Pos)        /*!< 0x03000000 */
/* SRC increment size */
#define DMACH_CFG_SRC_INC_SIZE_Pos      (26U)
#define DMACH_CFG_SRC_INC_SIZE_Msk      (0x3U << DMACH_CFG_SRC_INC_SIZE_Pos)    /*!< 0x0C000000 */
/* DST size */
#define DMACH_CFG_DST_SIZE_Pos          (28U)
#define DMACH_CFG_DST_SIZE_Msk          (0x3U << DMACH_CFG_DST_SIZE_Pos)        /*!< 0x30000000 */
/* DST increment size */
#define DMACH_CFG_DST_INC_SIZE_Pos      (30U)
#define DMACH_CFG_DST_INC_SIZE_Msk      (0x3U << DMACH_CFG_DST_INC_SIZE_Pos)    /*!< 0xC0000000 */

/*
 * ==========================================================================
 * ---------------------- DMA registers bits --------------------------------
 * ==========================================================================
 */

/* DMA requests */
/* UART1TXDMABREQ, UART1TXDMASREQ */
#define DMA_UART1_TX_Pos				(0U)
#define DMA_UART1_TX_Msk				(0x1U << DMA_UART1_TX_Pos)				/*!< 0x00000001 */
#define DMA_UART1_TX					DMA_UART1_TX_Msk
/* UART1RXDMABREQ, UART1RXDMASREQ */
#define DMA_UART1_RX_Pos				(1U)
#define DMA_UART1_RX_Msk				(0x1U << DMA_UART1_RX_Pos)				/*!< 0x00000002 */
#define DMA_UART1_RX					DMA_UART1_RX_Msk
/* UART2TXDMABREQ, UART2TXDMASREQ */
#define DMA_UART2_TX_Pos				(2U)
#define DMA_UART2_TX_Msk				(0x1U << DMA_UART2_TX_Pos)				/*!< 0x00000004 */
#define DMA_UART2_TX					DMA_UART2_TX_Msk
/* UART2RXDMABREQ, UART2RXDMASREQ */
#define DMA_UART2_RX_Pos				(3U)
#define DMA_UART2_RX_Msk				(0x1U << DMA_UART2_RX_Pos)				/*!< 0x00000008 */
#define DMA_UART2_RX					DMA_UART2_RX_Msk
/* SSP1TXDMABREQ, SSP1TXDMASREQ */
#define DMA_SSP1_TX_Pos					(4U)
#define DMA_SSP1_TX_Msk					(0x1U << DMA_SSP1_TX_Pos)				/*!< 0x00000010 */
#define DMA_SSP1_TX						DMA_SSP1_TX_Msk
/* SSP1RXDMABREQ, SSP1RXDMASREQ */
#define DMA_SSP1_RX_Pos					(5U)
#define DMA_SSP1_RX_Msk					(0x1U << DMA_SSP1_RX_Pos)				/*!< 0x00000020 */
#define DMA_SSP1_RX						DMA_SSP1_RX_Msk
/* CRCDMABREQ, CRCDMASREQ */
#define DMA_CRC_Pos						(6U)
#define DMA_CRC_Msk						(0x1U << DMA_CRC_Pos)					/*!< 0x00000040 */
#define DMA_CRC							DMA_CRC_Msk
/* UART3TXDMABREQ, UART3TXDMASREQ */
#define DMA_UART3_TX_Pos				(7U)
#define DMA_UART3_TX_Msk				(0x1U << DMA_UART3_TX_Pos)				/*!< 0x00000080 */
#define DMA_UART3_TX					DMA_UART3_TX_Msk
/* UART3RXDMABREQ, UART3RXDMASREQ */
#define DMA_UART3_RX_Pos				(8U)
#define DMA_UART3_RX_Msk				(0x1U << DMA_UART3_RX_Pos)				/*!< 0x00000100 */
#define DMA_UART3_RX					DMA_UART3_RX_Msk
/* TIM3DMAREQ */
#define DMA_TIM3_Pos					(9U)
#define DMA_TIM3_Msk					(0x1U << DMA_TIM3_Pos)					/*!< 0x00000200 */
#define DMA_TIM3						DMA_TIM3_Msk
/* TIM1DMAREQ */
#define DMA_TIM1_Pos					(10U)
#define DMA_TIM1_Msk					(0x1U << DMA_TIM1_Pos)					/*!< 0x00000400 */
#define DMA_TIM1						DMA_TIM1_Msk
/* TIM2DMAREQ */
#define DMA_TIM2_Pos					(11U)
#define DMA_TIM2_Msk					(0x1U << DMA_TIM2_Pos)					/*!< 0x00000800 */
#define DMA_TIM2						DMA_TIM2_Msk
/* ADCUIDMABREQ1, ADCUIDMASREQ1 */
#define DMA_ADCUI1_Pos					(12U)
#define DMA_ADCUI1_Msk					(0x1U << DMA_ADCUI1_Pos)				/*!< 0x00001000 */
#define DMA_ADCUI1						DMA_ADCUI1_Msk
/* ADCUIDMABREQ2, ADCUIDMASREQ2 */
#define DMA_ADCUI2_Pos					(13U)
#define DMA_ADCUI2_Msk					(0x1U << DMA_ADCUI2_Pos)				/*!< 0x00002000 */
#define DMA_ADCUI2						DMA_ADCUI2_Msk
/* ADCUIDMABREQ3, ADCUIDMASREQ3 */
#define DMA_ADCUI3_Pos					(14U)
#define DMA_ADCUI3_Msk					(0x1U << DMA_ADCUI3_Pos)				/*!< 0x00004000 */
#define DMA_ADCUI3						DMA_ADCUI3_Msk
/* ADCUIDMABREQ4, ADCUIDMASREQ4 */
#define DMA_ADCUI4_Pos					(15U)
#define DMA_ADCUI4_Msk					(0x1U << DMA_ADCUI4_Pos)				/*!< 0x00008000 */
#define DMA_ADCUI4						DMA_ADCUI4_Msk
/* ADCUIDMABREQ5, ADCUIDMASREQ5 */
#define DMA_ADCUI5_Pos					(16U)
#define DMA_ADCUI5_Msk					(0x1U << DMA_ADCUI5_Pos)				/*!< 0x00010000 */
#define DMA_ADCUI5						DMA_ADCUI5_Msk
/* ADCUIDMABREQ6, ADCUIDMASREQ6 */
#define DMA_ADCUI6_Pos					(17U)
#define DMA_ADCUI6_Msk					(0x1U << DMA_ADCUI6_Pos)				/*!< 0x00020000 */
#define DMA_ADCUI6						DMA_ADCUI6_Msk
/* ADCUIDMABREQ7, ADCUIDMASREQ7 */
#define DMA_ADCUI7_Pos					(18U)
#define DMA_ADCUI7_Msk					(0x1U << DMA_ADCUI7_Pos)				/*!< 0x00040000 */
#define DMA_ADCUI7						DMA_ADCUI7_Msk
/* SSP2TXDMABREQ, SSP2TXDMASREQ */
#define DMA_SSP2_TX_Pos					(19U)
#define DMA_SSP2_TX_Msk					(0x1U << DMA_SSP2_TX_Pos)				/*!< 0x00080000 */
#define DMA_SSP2_TX						DMA_SSP2_TX_Msk
/* SSP2RXDMABREQ, SSP2RXDMASREQ */
#define DMA_SSP2_RX_Pos					(20U)
#define DMA_SSP2_RX_Msk					(0x1U << DMA_SSP2_RX_Pos)				/*!< 0x00100000 */
#define DMA_SSP2_RX						DMA_SSP2_RX_Msk
/* SSP3TXDMABREQ, SSP3TXDMASREQ */
#define DMA_SSP3_TX_Pos					(21U)
#define DMA_SSP3_TX_Msk					(0x1U << DMA_SSP3_TX_Pos)				/*!< 0x00200000 */
#define DMA_SSP3_TX						DMA_SSP3_TX_Msk
/* SSP3RXDMABREQ, SSP3RXDMASREQ */
#define DMA_SSP3_RX_Pos					(22U)
#define DMA_SSP3_RX_Msk					(0x1U << DMA_SSP3_RX_Pos)				/*!< 0x00400000 */
#define DMA_SSP3_RX						DMA_SSP3_RX_Msk
/* TIM4DMAREQ */
#define DMA_TIM4_Pos					(23U)
#define DMA_TIM4_Msk					(0x1U << DMA_TIM4_Pos)					/*!< 0x00800000 */
#define DMA_TIM4						DMA_TIM4_Msk
/* UART4TXDMABREQ, UART4TXDMASREQ */
#define DMA_UART4_TX_Pos				(24U)
#define DMA_UART4_TX_Msk				(0x1U << DMA_UART4_TX_Pos)				/*!< 0x01000000 */
#define DMA_UART4_TX					DMA_UART4_TX_Msk
/* UART4RXDMABREQ, UART4RXDMASREQ */
#define DMA_UART4_RX_Pos				(25U)
#define DMA_UART4_RX_Msk				(0x1U << DMA_UART4_RX_Pos)				/*!< 0x02000000 */
#define DMA_UART4_RX					DMA_UART4_RX_Msk
/* ADCDMASREQ */
#define DMA_SARADC_Pos					(30U)
#define DMA_SARADC_Msk					(0x1U << DMA_SARADC_Pos)				/*!< 0x40000000 */
#define DMA_SARADC						DMA_SARADC_Msk

/*******************  Bit definition for DMA_STATUS register ******************/
/* master enable */
#define DMA_STATUS_MASTER_ENABLE_Pos    (0U)
#define DMA_STATUS_MASTER_ENABLE_Msk    (0x1U << DMA_STATUS_MASTER_ENABLE_Pos)  /*!< 0x00000001 */
#define DMA_STATUS_MASTER_ENABLE        DMA_STATUS_MASTER_ENABLE_Msk
/* actual state */
#define DMA_STATUS_STATE_Pos            (4U)
#define DMA_STATUS_STATE_Msk            (0xFU << DMA_STATUS_STATE_Pos)          /*!< 0x000000F0 */
#define DMA_STATUS_STATE_IDLE           (0x0U << DMA_STATUS_STATE_Pos)
#define DMA_STATUS_STATE_RDCTRL         (0x1U << DMA_STATUS_STATE_Pos)
#define DMA_STATUS_STATE_RDSRCADDR      (0x2U << DMA_STATUS_STATE_Pos)
#define DMA_STATUS_STATE_RDDSTADDR      (0x3U << DMA_STATUS_STATE_Pos)
#define DMA_STATUS_STATE_RDSRC          (0x4U << DMA_STATUS_STATE_Pos)
#define DMA_STATUS_STATE_WRDST          (0x5U << DMA_STATUS_STATE_Pos)
#define DMA_STATUS_STATE_REQWAIT        (0x6U << DMA_STATUS_STATE_Pos)
#define DMA_STATUS_STATE_UPDCTRL        (0x7U << DMA_STATUS_STATE_Pos)
#define DMA_STATUS_STATE_HALT           (0x8U << DMA_STATUS_STATE_Pos)
#define DMA_STATUS_STATE_COMPLETE       (0x9U << DMA_STATUS_STATE_Pos)
#define DMA_STATUS_STATE_PROGMODE       (0xAU << DMA_STATUS_STATE_Pos)
/* number of channels (minus 1) */
#define DMA_STATUS_CHNLS_Pos            (16U)
#define DMA_STATUS_CHNLS_Msk            (0x1FU << DMA_STATUS_CHNLS_Pos)         /*!< 0x001F0000 */
/* test status */
#define DMA_STATUS_TEST_STATUS_Pos      (28U)
#define DMA_STATUS_TEST_STATUS_Msk      (0xFU << DMA_STATUS_TEST_STATUS_Pos)    /*!< 0xF0000000 */

/*******************  Bit definition for DMA_CFG register *********************/
/* master enable switch */
#define DMA_CFG_MASTER_ENABLE_Pos       (0U)
#define DMA_CFG_MASTER_ENABLE_Msk       (0x1U << DMA_CFG_MASTER_ENABLE_Pos)     /*!< 0x00000001 */
#define DMA_CFG_MASTER_ENABLE           DMA_CFG_MASTER_ENABLE_Msk
/* AHB-Lite protection */
#define DMA_CFG_CHNL_PROT_CTRL_Pos      (5U)
#define DMA_CFG_CHNL_PROT_CTRL_Msk      (0x7U << DMA_CFG_CHNL_PROT_CTRL_Pos)    /*!< 0x000000E0 */

/*
 * ==========================================================================
 * ---------------------- I2C registers bits --------------------------------
 * ==========================================================================
 */

/*******************  Bit definition for I2C_CTR register *********************/
/* speed selection (0 - <= 400kHz, 1 - <=  1 MHz) */
#define I2C_CTR_S_I2C_Pos               (5U)
#define I2C_CTR_S_I2C_Msk               (0x1U << I2C_CTR_S_I2C_Pos)             /*!< 0x00000010 */
#define I2C_CTR_S_I2C_upto400kHz        (0x0U >> I2C_CTR_S_I2C_Pos)
#define I2C_CTR_S_I2C_upto1MHz          (0x1U >> I2C_CTR_S_I2C_Pos)
/* interrupt enabled (0 - disabled, 1 - enabled) */
#define I2C_CTR_EN_INT_Pos              (6U)
#define I2C_CTR_EN_INT_Msk              (0x1U << I2C_CTR_EN_INT_Pos)            /*!< 0x00000020 */
#define I2C_CTR_EN_INT                  I2C_CTR_EN_INT_Msk
/* I2C enable switch (0 - disabled, 1 - enabled) */
#define I2C_CTR_EN_I2C_Pos              (7U)
#define I2C_CTR_EN_I2C_Msk              (0x1U << I2C_CTR_EN_I2C_Pos)            /*!< 0x00000040 */
#define I2C_CTR_EN_I2C                  I2C_CTR_EN_I2C_Msk

/********************  Bit definition for I2C_STA register *********************/
/* interrupt flag: -byte transfer is complete or -arbitration lost */
#define I2C_STA_INT_Pos                 (0U)
#define I2C_STA_INT_Msk                 (0x1U << I2C_STA_INT_Pos)               /*!< 0x00000001 */
#define I2C_STA_INT                     I2C_STA_INT_Msk
/* transfer in progress */
#define I2C_STA_TR_PROG_Pos             (1U)
#define I2C_STA_TR_PROG_Msk             (0x1U << I2C_STA_TR_PROG_Pos)           /*!< 0x00000002 */
#define I2C_STA_TR_PROG      			I2C_STA_TR_PROG_Msk
/* arbitration lost (0 - arbitration was not lost, 1 - arbitration lost) */
#define I2C_STA_LOST_ARB_Pos            (5U)
#define I2C_STA_LOST_ARB_Msk            (0x1U << I2C_STA_LOST_ARB_Pos)          /*!< 0x00000020 */
#define I2C_STA_LOST_ARB				I2C_STA_LOST_ARB_Msk
/* bus busy (0 - stop bit received, 1 - start bit received) */
#define I2C_STA_BUSY_Pos                (6U)
#define I2C_STA_BUSY_Msk                (0x1U << I2C_STA_BUSY_Pos)              /*!< 0x00000040 */
#define I2C_STA_BUSY                    I2C_STA_BUSY_Msk
/* ACK received (0 - ACK was received, 1 - ACK was not received (NACK)) */
#define I2C_STA_RX_ACK_Pos              (7U)
#define I2C_STA_RX_ACK_Msk              (0x1U << I2C_STA_RX_ACK_Pos)            /*!< 0x00000080 */
#define I2C_STA_RX_ACK                  I2C_STA_RX_ACK_Msk

/*******************  Bit definition for I2C_TXD register *********************/
/* 7-bit address, move to the left */
#define I2C_TXD_ADDR_OFFSET             (1U)
#define I2C_TXD_NWR_RD                  (0x1U)

/*******************  Bit definition for I2C_CMD register *********************/
/* clear interrupt flag (write 1 to clear interrupt) */
#define I2C_CMD_CLR_INT_Pos             (0U)
#define I2C_CMD_CLR_INT_Msk             (0x1U << I2C_CMD_CLR_INT_Pos)           /*!< 0x00000001 */
#define I2C_CMD_CLR_INT                 I2C_CMD_CLR_INT_Msk
/* send ACK */
#define I2C_CMD_ACK_Pos                 (3U)
#define I2C_CMD_ACK_Msk                 (0x1U << I2C_CMD_ACK_Pos)               /*!< 0x00000008 */
#define I2C_CMD_ACK                     I2C_CMD_ACK_Msk
/* write single byte */
#define I2C_CMD_WR_Pos                  (4U)
#define I2C_CMD_WR_Msk                  (0x1U << I2C_CMD_WR_Pos)                /*!< 0x00000010 */
#define I2C_CMD_WR                      I2C_CMD_WR_Msk
/* read single byte */
#define I2C_CMD_RD_Pos                  (5U)
#define I2C_CMD_RD_Msk                  (0x1U << I2C_CMD_RD_Pos)                /*!< 0x00000020 */
#define I2C_CMD_RD                      I2C_CMD_RD_Msk
/* send stop bit */
#define I2C_CMD_STOP_Pos                (6U)
#define I2C_CMD_STOP_Msk                (0x1U << I2C_CMD_STOP_Pos)              /*!< 0x00000040 */
#define I2C_CMD_STOP                    I2C_CMD_STOP_Msk
/* send start bit */
#define I2C_CMD_START_Pos               (7U)
#define I2C_CMD_START_Msk               (0x1U << I2C_CMD_START_Pos)             /*!< 0x00000080 */
#define I2C_CMD_START                   I2C_CMD_START_Msk

/*
 * ==========================================================================
 * ---------------------- ADC registers bits --------------------------------
 * ==========================================================================
 */

/* ADC channel enumeration */
#define ADC_CHNL_TEMP                   (0x7U)
#define ADC_CHNL_AIN1                   (0x6U)
#define ADC_CHNL_AIN2                   (0x5U)
#define ADC_CHNL_AIN3                   (0x4U)
#define ADC_CHNL_VBAT                   (0x2U)
#define ADC_CHNL_VREF                   (0x1U)

/*******************  Bit definition for ADC_CFG register *********************/
/* SAR ADC enable (0 - disabled, 1 - enabled) */
#define ADC_CFG_ADON_Pos                (0U)
#define ADC_CFG_ADON_Msk                (0x1U << ADC_CFG_ADON_Pos)              /*!< 0x00000001 */
#define ADC_CFG_ADON                    ADC_CFG_ADON_Msk
/* conversion start (write 1 to start conversion) */
#define ADC_CFG_GO_Pos                  (1U)
#define ADC_CFG_GO_Msk                  (0x1U << ADC_CFG_GO_Pos)                /*!< 0x00000002 */
#define ADC_CFG_GO                      ADC_CFG_GO_Msk
/* freq source (0 - peripheral clock, 1 - internal ADC clock) */
#define ADC_CFG_CLKS_Pos                (2U)
#define ADC_CFG_CLKS_Msk                (0x1U << ADC_CFG_CLKS_Pos)              /*!< 0x00000004 */
#define ADC_CFG_CLKS                    ADC_CFG_CLKS_Msk
/* sequential mode (0 - signle conversion, 1 - sequential mode) */
#define ADC_CFG_SAMPLE_Pos              (3U)
#define ADC_CFG_SAMPLE_Msk              (0x1U << ADC_CFG_SAMPLE_Pos)            /*!< 0x00000008 */
#define ADC_CFG_SAMPLE_SINGLE           (0x0U << ADC_CFG_SAMPLE_Pos)
#define ADC_CFG_SAMPLE_SEQUENCE         (0x1U << ADC_CFG_SAMPLE_Pos)
/* channel selection */
#define ADC_CFG_CHS_Pos                 (4U)
#define ADC_CFG_CHS_Msk                 (0x7U << ADC_CFG_CHS_Pos)               /*!< 0x00000070 */
#define ADC_CFG_CHS_TEMP                (ADC_CHNL_TEMP << ADC_CFG_CHS_Pos)
#define ADC_CFG_CHS_AIN1                (ADC_CHNL_AIN1 << ADC_CFG_CHS_Pos)
#define ADC_CFG_CHS_AIN2                (ADC_CHNL_AIN2 << ADC_CFG_CHS_Pos)
#define ADC_CFG_CHS_AIN3                (ADC_CHNL_AIN3 << ADC_CFG_CHS_Pos)
#define ADC_CFG_CHS_VB                  (ADC_CHNL_VBAT << ADC_CFG_CHS_Pos)
#define ADC_CFG_CHS_2p4V                (ADC_CHNL_VREF << ADC_CFG_CHS_Pos)
/* channel selection source (0 - as specified in CHS, 1 - use CHSEL register) */
#define ADC_CFG_CHCH_Pos                (9U)
#define ADC_CFG_CHCH_Msk                (0x1U << ADC_CFG_CHCH_Pos)              /*!< 0x00000200 */
#define ADC_CFG_CHCH_USE_CFG_CHS        (0x0U << ADC_CFG_CHCH_Pos)
#define ADC_CFG_CHCH_USE_CHSEL          (0x1U << ADC_CFG_CHCH_Pos)
/* threshold detection (0 - disabled, 1 - enabled) */
#define ADC_CFG_RNGC_Pos                (10U)
#define ADC_CFG_RNGC_Msk                (0x1U << ADC_CFG_RNGC_Pos)              /*!< 0x00000400 */
#define ADC_CFG_RNGC                    ADC_CFG_RNGC_Msk
/* scale selection (0 - upto AUCC, 1 - upto VR_2p4V) */
#define ADC_CFG_MREF_Pos                (11U)
#define ADC_CFG_MREF_Msk                (0x1U << ADC_CFG_MREF_Pos)              /*!< 0x00000800 */
#define ADC_CFG_MREF                    ADC_CFG_MREF_Msk
/* frequency prescaler (PCLKd = HCLK / 2^N) */
#define ADC_CFG_DIVCLK_Pos              (12U)
#define ADC_CFG_DIVCLK_Msk              (0xFU << ADC_CFG_DIVCLK_Pos)            /*!< 0x0000f000 */
#define ADC_CFG_DIVCLK_1				(0x0U << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_2				(0x1U << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_4				(0x2U << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_8				(0x3U << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_16				(0x4U << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_32				(0x5U << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_64				(0x6U << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_128				(0x7U << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_256				(0x8U << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_512				(0x9U << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_1024				(0xAU << ADC_CFG_DIVCLK_Pos)
#define ADC_CFG_DIVCLK_2048  			(0xBU << ADC_CFG_DIVCLK_Pos)
/* hardcoded hw selection */
#define ADC_CFG_MAGIC_Pos               (16U)
#define ADC_CFG_MAGIC_Val               0x2
#define ADC_CFG_MAGIC                   (ADC_CFG_MAGIC_Val << ADC_CFG_MAGIC_Pos)
/* noise generator activation (0 - disabled, 1 - enabled) */
#define ADC_CFG_EN_NOISE_RNG_Pos        (19U)
#define ADC_CFG_EN_NOISE_RNG_Msk        (0x1U << ADC_CFG_EN_NOISE_RNG_Pos)      /*!< 0x00080000 */
#define ADC_CFG_EN_NOISE_RNG            ADC_CFG_EN_NOISE_RNG_Msk
/* delay before conversion (linear) */
#define ADC_CFG_DELAYGO_Pos             (25U)
#define ADC_CFG_DELAYGO_Msk             (0x7U << ADC_CFG_DELAYGO_Pos)           /*!< 0x0E000000 */

/*******************  Bit definition for ADC_RESULT register ******************/
/* conversion result */
#define ADC_RESULT_RESULT_Pos           (0U)
#define ADC_RESULT_RESULT_Msk           (0x3FFU << ADC_RESULT_RESULT_Pos)       /*!< 0x000003FF */
/* channel used for conversion */
#define ADC_RESULT_CHANNEL_Pos          (16U)
#define ADC_RESULT_CHANNEL_Msk          (0x7U << ADC_RESULT_CHANNEL_Pos)        /*!< 0x00070000 */
#define ADC_RESULT_CHANNEL_TEMP         (ADC_CHNL_TEMP << ADC_RESULT_CHANNEL_Pos)
#define ADC_RESULT_CHANNEL_AIN1         (ADC_CHNL_AIN1 << ADC_RESULT_CHANNEL_Pos)
#define ADC_RESULT_CHANNEL_AIN2         (ADC_CHNL_AIN2 << ADC_RESULT_CHANNEL_Pos)
#define ADC_RESULT_CHANNEL_AIN3         (ADC_CHNL_AIN3 << ADC_RESULT_CHANNEL_Pos)
#define ADC_RESULT_CHANNEL_VB           (ADC_CHNL_VBAT << ADC_RESULT_CHANNEL_Pos)
#define ADC_RESULT_CHANNEL_2p4V         (ADC_CHNL_VREF << ADC_RESULT_CHANNEL_Pos)

/*******************  Bit definition for ADC_STATUS register ******************/
/* result overwrite (0 - no data was lost, 1 - some data was lost) */
#define ADC_STATUS_OVERWRITE_Pos        (0U)
#define ADC_STATUS_OVERWRITE_Msk        (0x1U << ADC_STATUS_OVERWRITE_Pos)      /*!< 0x00000001 */
#define ADC_STATUS_OVERWRITE            ADC_STATUS_OVERWRITE_Msk
/* threshold detection */
#define ADC_STATUS_AWOIFEN_Pos          (1U)
#define ADC_STATUS_AWOIFEN_Msk          (0x1U << ADC_STATUS_AWOIFEN_Pos)        /*!< 0x00000002 */
#define ADC_STATUS_AWOIFEN_OK           (0x0U << ADC_STATUS_AWOIFEN_Pos)
#define ADC_STATUS_AWOIFEN_FAIL         (0x1U << ADC_STATUS_AWOIFEN_Pos)
#define ADC_STATUS_AWOIFEN_CLEAR        (0x0U << ADC_STATUS_AWOIFEN_Pos)
/* conversion complete */
#define ADC_STATUS_EOCIF_Pos            (2U)
#define ADC_STATUS_EOCIF_Msk            (0x1U << ADC_STATUS_EOCIF_Pos)          /*!< 0x00000004 */
#define ADC_STATUS_EOCIF                ADC_STATUS_EOCIF_Msk
/* interrupt enable for threshold detection */
#define ADC_STATUS_AWOIF_IE_Pos         (3U)
#define ADC_STATUS_AWOIF_IE_Msk         (0x1U << ADC_STATUS_AWOIF_IE_Pos)       /*!< 0x00000008 */
#define ADC_STATUS_AWOIF_IE             ADC_STATUS_AWOIF_IE_Msk
/* interrupt enable for conversion complete */
#define ADC_STATUS_ECOIF_IE_Pos         (4U)
#define ADC_STATUS_ECOIF_IE_Msk         (0x1U << ADC_STATUS_ECOIF_IE_Pos)       /*!< 0x00000010 */
#define ADC_STATUS_ECOIF_IE             ADC_STATUS_ECOIF_IE_Msk

/*******************  Bit definition for ADC_CHSEL register *******************/
/* channel selection - setup '1' bit to include channel */
#define ADC_CHSEL_TEMP_Pos              (0U)
#define ADC_CHSEL_TEMP_Msk              (0x1U << ADC_CHSEL_TEMP_Pos)            /*!< 0x00000001 */
#define ADC_CHSEL_TEMP                  ADC_CHSEL_TEMP_Msk
#define ADC_CHSEL_AIN1_Pos              (1U)
#define ADC_CHSEL_AIN1_Msk              (0x1U << ADC_CHSEL_AIN1_Pos)            /*!< 0x00000002 */
#define ADC_CHSEL_AIN1                  ADC_CHSEL_AIN1_Msk
#define ADC_CHSEL_AIN2_Pos              (2U)
#define ADC_CHSEL_AIN2_Msk              (0x1U << ADC_CHSEL_AIN2_Pos)            /*!< 0x00000004 */
#define ADC_CHSEL_AIN2                  ADC_CHSEL_AIN2_Msk
#define ADC_CHSEL_AIN3_Pos              (3U)
#define ADC_CHSEL_AIN3_Msk              (0x1U << ADC_CHSEL_AIN3_Pos)            /*!< 0x00000008 */
#define ADC_CHSEL_AIN3                  ADC_CHSEL_AIN3_Msk
#define ADC_CHSEL_VB_Pos                (5U)
#define ADC_CHSEL_VB_Msk                (0x1U << ADC_CHSEL_VB_Pos)              /*!< 0x00000020 */
#define ADC_CHSEL_VB                    ADC_CHSEL_VB_Msk
#define ADC_CHSEL_2p4V_Pos              (6U)
#define ADC_CHSEL_2p4V_Msk              (0x1U << ADC_CHSEL_2p4V_Pos)            /*!< 0x00000040 */
#define ADC_CHSEL_2p4V                  ADC_CHSEL_2p4V_Msk

/*******************  Bit definition for ADC_TRIM register ********************/
/* bandgap trimming */
#define ADC_TRIM_BG_TRIM_Pos            (1U)
#define ADC_TRIM_BG_TRIM_Msk            (0x1FU << ADC_TRIM_BG_TRIM_Pos)          /*!< 0x0000003E */

/*
 * ==========================================================================
 * ---------------------- WWDG registers bits -------------------------------
 * ==========================================================================
 */

/*******************  Bit definition for WWDG_CR register *********************/
/* counter value */
#define WWDG_CR_T_Pos                   (0U)
#define WWDG_CR_T_Msk                   (0x7FU << WWDG_CR_T_Pos)                /*!< 0x0000007F */
/* enable switch (0 - disabled, 1 - enabled) */
#define WWDG_CR_WDGA_Pos                (7U)
#define WWDG_CR_WDGA_Msk                (0x1U << WWDG_CR_WDGA_Pos)              /*!< 0x00000080 */
#define WWDG_CR_WDGA                    WWDG_CR_WDGA_Msk

/*******************  Bit definition for WWDG_CFR register ********************/
/* window size */
#define WWDG_CFR_W_Pos                  (0U)
#define WWDG_CFR_W_Msk                  (0x7FU << WWDG_CFR_W_Pos)               /*!< 0x0000007F */
/* clock prescaler */
#define WWDG_CFR_WGTB_Pos               (7U)
#define WWDG_CFR_WGTB_Msk               (0x3U << WWDG_CFR_WGTB_Pos)             /*!< 0x00000180 */
#define WWDG_CFR_WGTB_DIV_1             (0x0U << WWDG_CFR_WGTB_Pos)
#define WWDG_CFR_WGTB_DIV_2             (0x1U << WWDG_CFR_WGTB_Pos)
#define WWDG_CFR_WGTB_DIV_4             (0x2U << WWDG_CFR_WGTB_Pos)
#define WWDG_CFR_WGTB_DIV_8             (0x3U << WWDG_CFR_WGTB_Pos)
/* early warning interrupt */
#define WWDG_CFR_EWI_Pos                (9U)
#define WWDG_CFR_EWI_Msk                (0x1U << WWDG_CFR_EWI_Pos)              /*!< 0x00000200 */
#define WWDG_CFR_EWI                    WWDG_CFR_EWI_Msk

/*******************  Bit definition for WWDG_SR register *********************/
/* early warning interrupt flag */
#define WWDG_SR_EWIF_Pos                (0U)
#define WWDG_SR_EWIF_Msk                (0x1U << WWDG_SR_EWIF_Pos)              /*!< 0x00000001 */
#define WWDG_SR_EWIF                    WWDG_SR_EWIF_Msk
/* WWDG_CR and WWDG_CFR registers are ready */
#define WWDG_SR_WDG_WEC_Pos             (1U)
#define WWDG_SR_WDG_WEC_Msk             (0x1U << WWDG_SR_WDG_WEC_Pos)           /*!< 0x00000002 */
#define WWDG_SR_WDG_WEC                 WWDG_SR_WDG_WEC_Msk

/*
 * ==========================================================================
 * ---------------------- IWDG registers bits -------------------------------
 * ==========================================================================
 */

/*******************  Bit definition for IWDG_KR register *********************/
/* key to refresh timer */
#define IWDG_KR_REFRESH                 (0xAAAAU)
/* key to disable write-protection of the configuration */
#define IWDG_KR_CONFIG_KEY              (0x5555U)
/* key to start watch dog */
#define IWDG_KR_START                   (0xCCCCU)

/*******************  Bit definition for IWDG_PR register *********************/
#define IWDG_PR_DIV_4                   (0U)
#define IWDG_PR_DIV_8                   (1U)
#define IWDG_PR_DIV_16                  (2U)
#define IWDG_PR_DIV_32                  (3U)
#define IWDG_PR_DIV_64                  (4U)
#define IWDG_PR_DIV_128                 (5U)
#define IWDG_PR_DIV_256                 (6U)

/*******************  Bit definition for IWDG_SR register *********************/
/* predivisor update flag */
#define IWDG_SR_PVU_Pos                 (0U)
#define IWDG_SR_PVU_Msk                 (0x1U << IWDG_SR_PVU_Pos)               /*!< 0x00000001 */
#define IWDG_SR_PVU                     IWDG_SR_PVU_Msk
/* reload update flag */
#define IWDG_SR_RVU_Pos                 (1U)
#define IWDG_SR_RVU_Msk                 (0x1U << IWDG_SR_RVU_Pos)               /*!< 0x00000002 */
#define IWDG_SR_RVU                     IWDG_SR_RVU_Msk

/*
 * ==========================================================================
 * ---------------------- POWER registers bits ------------------------------
 * ==========================================================================
 */

/*******************  Bit definition for POWER_PVDCS register *****************/
/* POWER control for battery domain (0 - disabled, 1 - enabled) */
#define POWER_PVDCS_PVDBEN_Pos          (0U)
#define POWER_PVDCS_PVDBEN_Msk          (0x1U << POWER_PVDCS_PVDBEN_Pos)        /*!< 0x00000001 */
#define POWER_PVDCS_PVDBEN              POWER_PVDCS_PVDBEN_Msk
/* POWER control for main domain (0 - disabled, 1 - enabled) */
#define POWER_PVDCS_PVDEN_Pos           (2U)
#define POWER_PVDCS_PVDEN_Msk           (0x1U << POWER_PVDCS_PVDEN_Pos)         /*!< 0x00000004 */
#define POWER_PVDCS_PVDEN               POWER_PVDCS_PVDEN_Msk
/* Battery voltage threshold */
#define POWER_PVDCS_PLSB_Pos            (3U)
#define POWER_PVDCS_PLSB_Msk            (0x7U << POWER_PVDCS_PLSB_Pos)          /*!< 0x00000038 */
#define POWER_PVDCS_PLSB_1_8V           (0x0U << POWER_PVDCS_PLSB_Pos)          /*!< 0x00000000 */
#define POWER_PVDCS_PLSB_2_0V           (0x1U << POWER_PVDCS_PLSB_Pos)          /*!< 0x00000008 */
#define POWER_PVDCS_PLSB_2_2V           (0x2U << POWER_PVDCS_PLSB_Pos)          /*!< 0x00000010 */
#define POWER_PVDCS_PLSB_2_4V           (0x3U << POWER_PVDCS_PLSB_Pos)          /*!< 0x00000018 */
#define POWER_PVDCS_PLSB_2_6V           (0x4U << POWER_PVDCS_PLSB_Pos)          /*!< 0x00000020 */
#define POWER_PVDCS_PLSB_2_8V           (0x5U << POWER_PVDCS_PLSB_Pos)          /*!< 0x00000028 */
#define POWER_PVDCS_PLSB_3_0V           (0x6U << POWER_PVDCS_PLSB_Pos)          /*!< 0x00000030 */
#define POWER_PVDCS_PLSB_3_2V           (0x7U << POWER_PVDCS_PLSB_Pos)          /*!< 0x00000038 */
/* Main domain voltage threshold */
#define POWER_PVDCS_PLS_Pos             (13U)
#define POWER_PVDCS_PLS_Msk             (0x7U << POWER_PVDCS_PLS_Pos)           /*!< 0x0000E000 */
#define POWER_PVDCS_PLS_2_3V            (0x0U << POWER_PVDCS_PLS_Pos)           /*!< 0x00000000 */
#define POWER_PVDCS_PLS_2_4V            (0x1U << POWER_PVDCS_PLS_Pos)           /*!< 0x00002000 */
#define POWER_PVDCS_PLS_2_5V            (0x2U << POWER_PVDCS_PLS_Pos)           /*!< 0x00004000 */
#define POWER_PVDCS_PLS_2_6V            (0x3U << POWER_PVDCS_PLS_Pos)           /*!< 0x00006000 */
#define POWER_PVDCS_PLS_2_7V            (0x4U << POWER_PVDCS_PLS_Pos)           /*!< 0x00008000 */
#define POWER_PVDCS_PLS_2_8V            (0x5U << POWER_PVDCS_PLS_Pos)           /*!< 0x0000A000 */
#define POWER_PVDCS_PLS_2_9V            (0x6U << POWER_PVDCS_PLS_Pos)           /*!< 0x0000C000 */
#define POWER_PVDCS_PLS_3_0V            (0x7U << POWER_PVDCS_PLS_Pos)           /*!< 0x0000E000 */
/* compare result between battery voltage and battery voltage threshold (0 - Vb < Vb_thres, 1 - Vb > Vb_thres */
/* write '0' twice to clear register */
#define POWER_PVDCS_PVDB_Pos            (18U)
#define POWER_PVDCS_PVDB_Msk            (0x1U << POWER_PVDCS_PVDB_Pos)          /*!< 0x00040000 */
#define POWER_PVDCS_PVDB_VB_LESS_THR    (0x0U << POWER_PVDCS_PVDB_Pos)
#define POWER_PVDCS_PVDB_VB_GREATER_THR (0x1U << POWER_PVDCS_PVDB_Pos)
/* compare result between main voltage and main voltage threshold (0 - Vm < Vm_thres, 1 - Vm > Vm_thres */
/* write '0' twice to clear register */
#define POWER_PVDCS_PVD_Pos             (20U)
#define POWER_PVDCS_PVD_Msk             (0x1U << POWER_PVDCS_PVD_Pos)           /*!< 0x00100000 */
#define POWER_PVDCS_PVD_VM_LESS_THR     (0x0U << POWER_PVDCS_PVD_Pos)
#define POWER_PVDCS_PVD_VM_GREATER_THR  (0x1U << POWER_PVDCS_PVD_Pos)
/* interrupt enable for battery voltage monitor (0 - disabled, 1 - enabled) */
#define POWER_PVDCS_IEPVDB_Pos          (21U)
#define POWER_PVDCS_IEPVDB_Msk          (0x1U << POWER_PVDCS_IEPVDB_Pos)        /*!< 0x00200000 */
#define POWER_PVDCS_IEPVDB              POWER_PVDCS_IEPVDB_Msk
/* interrupt enable for main voltage monitor (0 - disabled, 1 - enabled) */
#define POWER_PVDCS_IEPVD_Pos           (22U)
#define POWER_PVDCS_IEPVD_Msk           (0x1U << POWER_PVDCS_IEPVD_Pos)         /*!< 0x00400000 */
#define POWER_PVDCS_IEPVD               POWER_PVDCS_IEPVD_Msk
/* inversion of the battery domain power monitor (0 - setup flag if voltage lower than threshold, 1 - if higher) */
#define POWER_PVDCS_INVB_Pos            (24U)
#define POWER_PVDCS_INVB_Msk            (0x1U << POWER_PVDCS_INVB_Pos)          /*!< 0x01000000 */
#define POWER_PVDCS_INVB                POWER_PVDCS_INVB_Msk
/* inversion of the main domain power monitor (0 - setup flag if voltage lower than threshold, 1 - if higher) */
#define POWER_PVDCS_INV_Pos             (26U)
#define POWER_PVDCS_INV_Msk             (0x1U << POWER_PVDCS_INV_Pos)           /*!< 0x04000000 */
#define POWER_PVDCS_INV                 POWER_PVDCS_INV_Msk

/*
 * ==========================================================================
 * ---------------------- BKP registers bits --------------------------------
 * ==========================================================================
 */

/*******************  BKP key register - valid key value **********************/
#define BKP_WPR_KEY                     0x8555AAA1U

/* PREDIV_S and PRL registers masks */
#define BKP_PREDIV_PRL_Msk				(0xFFFFFU)

/*******************  BKP RTC week days ***************************************/
#define BKP_RTC_WDU_Monday              0x1U
#define BKP_RTC_WDU_Tuesday             0x2U
#define BKP_RTC_WDU_Wednesday           0x3U
#define BKP_RTC_WDU_Thursday            0x4U
#define BKP_RTC_WDU_Friday              0x5U
#define BKP_RTC_WDU_Saturday            0x6U
#define BKP_RTC_WDU_Sunday              0x7U

/*******************  Bit definition for BKP_LDO register *********************/
/* Battery domain power trimming, 0b00 - basic voltage, 0b01 +2%, 0b10 +4%, 0b11 +6% */
#define BKP_LDO_BLDO_TRIM_Pos           (0U)
#define BKP_LDO_BLDO_TRIM_Msk           (0x3U << BKP_LDO_BLDO_TRIM_Pos)         /*!< 0x00000003 */
#define BKP_LDO_BLDO_TRIM               BKP_LDO_BLDO_TRIM_Msk
#define BKP_LDO_BLDO_TRIM_NO            (0x0U << BKP_LDO_BLDO_TRIM_Pos)         /*!< 0x00000000 */
#define BKP_LDO_BLDO_TRIM_p2pr          (0x1U << BKP_LDO_BLDO_TRIM_Pos)         /*!< 0x00000001 */
#define BKP_LDO_BLDO_TRIM_p4pr          (0x2U << BKP_LDO_BLDO_TRIM_Pos)         /*!< 0x00000002 */
#define BKP_LDO_BLDO_TRIM_p6pr          (0x3U << BKP_LDO_BLDO_TRIM_Pos)         /*!< 0x00000003 */
/* Battery domain power trimming enable (0 - disabled, 1 - enabled) */
#define BKP_LDO_BLDO_BOOST_Pos          (2U)
#define BKP_LDO_BLDO_BOOST_Msk          (0x1U << BKP_LDO_BLDO_BOOST_Pos)        /*!< 0x00000004 */
#define BKP_LDO_BLDO_BOOST              BKP_LDO_BLDO_BOOST_Msk
/* Main domain power trimming enable (0 - disabled, 1 - enabled) */
#define BKP_LDO_LDO_BOOST_Pos           (3U)
#define BKP_LDO_LDO_BOOST_Msk           (0x3U << BKP_LDO_LDO_BOOST_Pos)         /*!< 0x00000018 */
#define BKP_LDO_LDO_BOOST               BKP_LDO_LDO_BOOST_Msk
/* Power switch enable (activate battery power for whole IC if any WAKEUP detected) (0 - disabled, 1 - enabled) */
#define BKP_LDO_SW_CNTRL_Pos            (5U)
#define BKP_LDO_SW_CNTRL_Msk            (0x1U << BKP_LDO_SW_CNTRL_Pos)          /*!< 0x00000020 */
#define BKP_LDO_SW_CNTRL                BKP_LDO_SW_CNTRL_Msk
/* Jtag enable (0 - disabled, 1 - enabled) */
#define BKP_LDO_JTAGON_Pos              (6U)
#define BKP_LDO_JTAGON_Msk              (0x1U << BKP_LDO_JTAGON_Pos)            /*!< 0x00000040 */
#define BKP_LDO_JTAGON                  BKP_LDO_JTAGON_Msk
/* WAKEUP1 state (0 - low voltage level, 1 - hi voltage level) */
#define BKP_LDO_WAKEUP1_Pos             (7U)
#define BKP_LDO_WAKEUP1_Msk             (0x1U << BKP_LDO_WAKEUP1_Pos)           /*!< 0x00000080 */
#define BKP_LDO_WAKEUP1                 BKP_LDO_WAKEUP1_Msk
/* WAKEUP2 state (0 - low voltage level, 1 - hi voltage level) */
#define BKP_LDO_WAKEUP2_Pos             (8U)
#define BKP_LDO_WAKEUP2_Msk             (0x1U << BKP_LDO_WAKEUP2_Pos)           /*!< 0x00000100 */
#define BKP_LDO_WAKEUP2                 BKP_LDO_WAKEUP2_Msk
/* WAKEUP3 state (0 - low voltage level, 1 - hi voltage level) */
#define BKP_LDO_WAKEUP3_Pos             (9U)
#define BKP_LDO_WAKEUP3_Msk             (0x1U << BKP_LDO_WAKEUP3_Pos)           /*!< 0x00000200 */
#define BKP_LDO_WAKEUP3                 BKP_LDO_WAKEUP3_Msk
/* all wake up lines */
#define BKP_LDO_WAKEUPS_Msk				(BKP_LDO_WAKEUP1_Msk | BKP_LDO_WAKEUP2_Msk | BKP_LDO_WAKEUP3_Msk)
/* FPOR flag (0 - power down, 1 - software reset) */
#define BKP_LDO_FPOR_Pos                (25U)
#define BKP_LDO_FPOR_Msk                (0x1U << BKP_LDO_FPOR_Pos)              /*!< 0x02000000 */
#define BKP_LDO_FPOR                    BKP_LDO_FPOR_Msk
/* COVDET invasion detection flag (0 - invasion was not detected, 1 - invasion detected) */
#define BKP_LDO_COVDET_Pos              (26U)
#define BKP_LDO_COVDET_Msk              (0x1U << BKP_LDO_COVDET_Pos)            /*!< 0x04000000 */
#define BKP_LDO_COVDET                  BKP_LDO_COVDET_Msk
/* boot MODE[1:0] from the pins */
#define BKP_LDO_MODE_Pos                (27U)
#define BKP_LDO_MODE_Msk                (0x3U << BKP_LDO_MODE_Pos)              /*!< 0x18000000 */
/* switch off whole IC power from the battery, (write 1 to switch battery power off) */
#define BKP_LDO_SWOFF_Pos               (29U)
#define BKP_LDO_SWOFF_Msk               (0x1U << BKP_LDO_SWOFF_Pos)             /*!< 0x20000000 */
#define BKP_LDO_SWOFF                   BKP_LDO_SWOFF_Msk

/*******************  Bit definition for BKP_CLK register *********************/
/* LSE osc enable (0 - disabled, 1 - enabled) */
#define BKP_CLK_LSEON_Pos               (0U)
#define BKP_CLK_LSEON_Msk               (0x1U << BKP_CLK_LSEON_Pos)             /*!< 0x00000001 */
#define BKP_CLK_LSEON                   BKP_CLK_LSEON_Msk
/* LSE osc bypassed (0 - LSE osc enabled, 1 - LSE bypassed, use external sygnal) */
#define BKP_CLK_LSEBYP_Pos              (1U)
#define BKP_CLK_LSEBYP_Msk              (0x1U << BKP_CLK_LSEBYP_Pos)            /*!< 0x00000002 */
#define BKP_CLK_LSEBYP                  BKP_CLK_LSEBYP_Msk
/* LSE osc ready (0 - LSE not enabled or not ready, 1 - LSE ongoing and stable) */
#define BKP_CLK_LSERDY_Pos              (2U)
#define BKP_CLK_LSERDY_Msk              (0x1U << BKP_CLK_LSERDY_Pos)            /*!< 0x00000004 */
#define BKP_CLK_LSERDY                  BKP_CLK_LSERDY_Msk
/* LSE osc config (0b00 - default) */
#define BKP_CLK_LSECONFIG_Pos           (3U)
#define BKP_CLK_LSECONFIG_Msk           (0x3U << BKP_CLK_LSECONFIG_Pos)         /*!< 0x00000018 */
#define BKP_CLK_LSECONFIG_DEFAULT       (0x0U << BKP_CLK_LSECONFIG_Pos)         /*!< 0x00000000 */
/* LSI osc enable (0 - disabled, 1 - enabled) */
#define BKP_CLK_LSION_Pos               (5U)
#define BKP_CLK_LSION_Msk               (0x1U << BKP_CLK_LSION_Pos)             /*!< 0x00000040 */
#define BKP_CLK_LSION                   BKP_CLK_LSION_Msk
/* LSI osc ready (0 - LSI not enabled or not ready, 1 - LSI ongoing and stable) */
#define BKP_CLK_LSIRDY_Pos              (12U)
#define BKP_CLK_LSIRDY_Msk              (0x1U << BKP_CLK_LSIRDY_Pos)            /*!< 0x00001000 */
#define BKP_CLK_LSIRDY                  BKP_CLK_LSIRDY_Msk
/* HSI osc enable (0 - disabled, 1 - enabled) */
#define BKP_CLK_HSION_Pos               (13U)
#define BKP_CLK_HSION_Msk               (0x1U << BKP_CLK_HSION_Pos)             /*!< 0x00002000 */
#define BKP_CLK_HSION                   BKP_CLK_HSION_Msk
/* HSI osc ready (0 - HSI osc not enabled or not ready, 1 - HSI ongoing and stable) */
#define BKP_CLK_HSIRDY_Pos              (14U)
#define BKP_CLK_HSIRDY_Msk              (0x1U << BKP_CLK_HSIRDY_Pos)            /*!< 0x00004000 */
#define BKP_CLK_HSIRDY                  BKP_CLK_HSIRDY_Msk
/* HSI osc trimming */
#define BKP_CLK_HSITRIM_Pos             (15U)
#define BKP_CLK_HSITRIM_Msk             (0x3FU << BKP_CLK_HSITRIM_Pos)          /*!< 0x001F8000 */

/*******************  Bit definition for BKP_RTC register *********************/
/* Frequency source for RTC: 0b00 - LSI, 0b01 - LSE, 0b10 - HSI, 0b11 - HSE */
#define BKP_RTC_RTCSEL_Pos              (0U)
#define BKP_RTC_RTCSEL_Msk              (0x3U << BKP_RTC_RTCSEL_Pos)            /*!< 0x00000003 */
#define BKP_RTC_RTCSEL_LSI              (0x0U << BKP_RTC_RTCSEL_Pos)            /*!< 0x00000000 */
#define BKP_RTC_RTCSEL_LSE              (0x1U << BKP_RTC_RTCSEL_Pos)            /*!< 0x00000001 */
#define BKP_RTC_RTCSEL_HSI              (0x2U << BKP_RTC_RTCSEL_Pos)            /*!< 0x00000002 */
#define BKP_RTC_RTCSEL_HSE              (0x3U << BKP_RTC_RTCSEL_Pos)            /*!< 0x00000003 */
/* RTC enable (0 - disabled, 1 - enabled) */
#define BKP_RTC_RTCEN_Pos               (2U)
#define BKP_RTC_RTCEN_Msk               (0x1U << BKP_RTC_RTCEN_Pos)             /*!< 0x00000004 */
#define BKP_RTC_RTCEN                   BKP_RTC_RTCEN_Msk
/* RTC calibration (number of ticks that will be masked within 2^20 interval) */
#define BKP_RTC_RTCCAL_Pos              (3U)
#define BKP_RTC_RTCCAL_Msk              (0xFFU << BKP_RTC_RTCCAL_Pos)           /*!< 0x000007F8 */
/* RTC reset (0 - do not reset RTC, 1 - reset RTC) */
#define BKP_RTC_RTCRESET_Pos            (11U)
#define BKP_RTC_RTCRESET_Msk            (0x1U << BKP_RTC_RTCRESET_Pos)          /*!< 0x00000800 */
#define BKP_RTC_RTCRESET                BKP_RTC_RTCRESET_Msk
/* wakeup timer divisor, 0b00 - RTC time / 16, 0b01 - RTC time / 8, 0b10 - RTC time / 4, 0b11 - RTC time / 2 */
#define BKP_RTC_WUCKDIV_Pos             (12U)
#define BKP_RTC_WUCKDIV_Msk             (0x3U << BKP_RTC_WUCKDIV_Pos)           /*!< 0x00003000 */
#define BKP_RTC_WUCKDIV_DIV2            (0x3U << BKP_RTC_WUCKDIV_Pos)           /*!< 0x00003000 */
#define BKP_RTC_WUCKDIV_DIV4            (0x2U << BKP_RTC_WUCKDIV_Pos)           /*!< 0x00002000 */
#define BKP_RTC_WUCKDIV_DIV8            (0x1U << BKP_RTC_WUCKDIV_Pos)           /*!< 0x00001000 */
#define BKP_RTC_WUCKDIV_DIV16           (0x0U << BKP_RTC_WUCKDIV_Pos)           /*!< 0x00000000 */
/* usage of wakeup timer divisor (1 - disabled (no division of the RTC time), 0 - enabled, use divisor) */
#define BKP_RTC_WUCKDIVNEN_Pos          (14U)
#define BKP_RTC_WUCKDIVNEN_Msk          (0x1U << BKP_RTC_WUCKDIVNEN_Pos)        /*!< 0x00004000 */
#define BKP_RTC_WUCKDIVNEN              BKP_RTC_WUCKDIVNEN_Msk
/* 12/24 hour time format (0 - 24h format, 1 - 12h format) */
#define BKP_RTC_FMT_Pos                 (25U)
#define BKP_RTC_FMT_Msk                 (0x1U << BKP_RTC_FMT_Pos)               /*!< 0x02000000 */
#define BKP_RTC_FMT_12H                 (0x1U << BKP_RTC_FMT_Pos)               /*!< 0x02000000 */
#define BKP_RTC_FMT_24H                 (0x0U << BKP_RTC_FMT_Pos)               /*!< 0x00000000 */

/*******************  Bit definition for RTC_CS register **********************/
/* wakeup register overflow (0 - no overflow, 1 - overflow detected) */
#define BKP_RTC_CS_OWF_Pos              (0U)
#define BKP_RTC_CS_OWF_Msk              (0x1U << BKP_RTC_CS_OWF_Pos)            /*!< 0x00000001 */
#define BKP_RTC_CS_OWF                  BKP_RTC_CS_OWF_Msk
/* activate second counter (0 - disabled, 1 - enabled) */
#define BKP_RTC_CS_SECF_Pos             (1U)
#define BKP_RTC_CS_SECF_Msk             (0x1U << BKP_RTC_CS_SECF_Pos)           /*!< 0x00000002 */
#define BKP_RTC_CS_SECF                 BKP_RTC_CS_SECF_Msk
/* wakeup condition (0 - not reached, 1 - reached) */
#define BKP_RTC_CS_WUTF_Pos             (2U)
#define BKP_RTC_CS_WUTF_Msk             (0x1U << BKP_RTC_CS_WUTF_Pos)           /*!< 0x00000004 */
#define BKP_RTC_CS_WUTF                 BKP_RTC_CS_WUTF_Msk
/* wakeup register interrupt enabled (0 - disabled, 1 - enabled) */
#define BKP_RTC_CS_OWFIE_Pos            (3U)
#define BKP_RTC_CS_OWFIE_Msk            (0x1U << BKP_RTC_CS_OWFIE_Pos)          /*!< 0x00000008 */
#define BKP_RTC_CS_OWFIE                BKP_RTC_CS_OWFIE_Msk
/* sec counter interrupt enable (0 - disabled, 1 - enabled) */
#define BKP_RTC_CS_SECFIE_Pos           (4U)
#define BKP_RTC_CS_SECFIE_Msk           (0x1U << BKP_RTC_CS_SECFIE_Pos)         /*!< 0x00000010 */
#define BKP_RTC_CS_SECFIE               BKP_RTC_CS_SECFIE_Msk
/* wakeup register and alarm register equality interrupt enable (0 - disabled, 1 - enabled) */
#define BKP_RTC_CS_WUTFIE_Pos           (5U)
#define BKP_RTC_CS_WUTFIE_Msk           (0x1U << BKP_RTC_CS_WUTFIE_Pos)         /*!< 0x00000020 */
#define BKP_RTC_CS_WUTFIE               BKP_RTC_CS_WUTFIE_Msk
/* write enable control (0 - write enabled, 1 - write disabled) */
#define BKP_RTC_CS_WEC_Pos              (6U)
#define BKP_RTC_CS_WEC_Msk              (0x1U << BKP_RTC_CS_WEC_Pos)            /*!< 0x00000040 */
#define BKP_RTC_CS_WEC					BKP_RTC_CS_WEC_Msk
/* alarm A (0 - disabled, 1 - enabled) */
#define BKP_RTC_CS_ALRAE_Pos            (7U)
#define BKP_RTC_CS_ALRAE_Msk            (0x1U << BKP_RTC_CS_ALRAE_Pos)          /*!< 0x00000080 */
#define BKP_RTC_CS_ALRAENABLED          BKP_RTC_CS_ALRAE_Msk
/* alarm B (0 - disabled, 1 - enabled) */
#define BKP_RTC_CS_ALRBE_Pos            (8U)
#define BKP_RTC_CS_ALRBE_Msk            (0x1U << BKP_RTC_CS_ALRBE_Pos)          /*!< 0x00000100 */
#define BKP_RTC_CS_ALRBENABLED          BKP_RTC_CS_ALRBE_Msk
/* alarm A flag (0 - alarm A was not activated, 1 - alarm A was activated) */
#define BKP_RTC_CS_ALRAF_Pos            (9U)
#define BKP_RTC_CS_ALRAF_Msk            (0x1U << BKP_RTC_CS_ALRAF_Pos)          /*!< 0x00000200 */
#define BKP_RTC_CS_ALRAFLAG             BKP_RTC_CS_ALRAF_Msk
/* alarm B flag (0 - alarm B was not activated, 1 - alarm B was activated) */
#define BKP_RTC_CS_ALRBF_Pos            (10U)
#define BKP_RTC_CS_ALRBF_Msk            (0x1U << BKP_RTC_CS_ALRBF_Pos)          /*!< 0x00000400 */
#define BKP_RTC_CS_ALRBFLAG             BKP_RTC_CS_ALRBF_Msk
/* alarm A interrupt (0 - disabled, 1 - enabled) */
#define BKP_RTC_CS_ALRAIE_Pos           (11U)
#define BKP_RTC_CS_ALRAIE_Msk           (0x1U << BKP_RTC_CS_ALRAIE_Pos)         /*!< 0x00000800 */
#define BKP_RTC_CS_ALRAIE               BKP_RTC_CS_ALRAIE_Msk
/* alarm B interrupt (0 - disabled, 1 - enabled) */
#define BKP_RTC_CS_ALRBIE_Pos           (12U)
#define BKP_RTC_CS_ALRBIE_Msk           (0x1U << BKP_RTC_CS_ALRBIE_Pos)         /*!< 0x00001000 */
#define BKP_RTC_CS_ALRBIE               BKP_RTC_CS_ALRBIE_Msk
/* external event flag */
#define BKP_RTC_CS_TSF_Pos              (13U)
#define BKP_RTC_CS_TSF_Msk              (0x1U << BKP_RTC_CS_TSF_Pos)            /*!< 0x00002000 */
#define BKP_RTC_CS_TSF                  BKP_RTC_CS_TSF_Msk

/*******************  Bit definition for BKP_RTC_TR register ******************/
/* seconds in BCD format */
#define BKP_RTC_TR_SU_Pos               (0U)
#define BKP_RTC_TR_SU_Msk               (0xFU << BKP_RTC_TR_SU_Pos)             /*!< 0x0000000F */
/* tens of seconds in BCD format */
#define BKP_RTC_TR_ST_Pos               (4U)
#define BKP_RTC_TR_ST_Msk               (0x7U << BKP_RTC_TR_ST_Pos)             /*!< 0x00000070 */
/* minutes in BCD format */
#define BKP_RTC_TR_MNU_Pos              (8U)
#define BKP_RTC_TR_MNU_Msk              (0xFU << BKP_RTC_TR_MNU_Pos)            /*!< 0x00000F00 */
/* tens of minutes in BCD format */
#define BKP_RTC_TR_MNT_Pos              (12U)
#define BKP_RTC_TR_MNT_Msk              (0x7U << BKP_RTC_TR_MNT_Pos)            /*!< 0x00007000 */
/* hours in BCD format */
#define BKP_RTC_TR_HU_Pos               (16U)
#define BKP_RTC_TR_HU_Msk               (0xFU << BKP_RTC_TR_HU_Pos)             /*!< 0x000F0000 */
/* tens of hours in BCD format */
#define BKP_RTC_TR_HT_Pos               (20U)
#define BKP_RTC_TR_HT_Msk               (0x3U << BKP_RTC_TR_HT_Pos)             /*!< 0x003F0000 */
/* PM indicator, (0 - AM or 24 hour format, 1 - PM) */
#define BKP_RTC_TR_PM_Pos               (22U)
#define BKP_RTC_TR_PM_Msk               (0x1U << BKP_RTC_TR_PM_Pos)             /*!< 0x00400000 */
#define BKP_RTC_TR_PM                   BKP_RTC_TR_PM_Msk

/*******************  Bit definition for BKP_RTC_DR register ******************/
/* days in BCD format */
#define BKP_RTC_DR_DU_Pos               (0U)
#define BKP_RTC_DR_DU_Msk               (0xFU << BKP_RTC_DR_DU_Pos)             /*!< 0x0000000F */
/* tens of the days in BCD format */
#define BKP_RTC_DR_DT_Pos               (4U)
#define BKP_RTC_DR_DT_Msk               (0x3U << BKP_RTC_DR_DT_Pos)             /*!< 0x00000030 */
/* months in BCD format */
#define BKP_RTC_DR_MU_Pos               (8U)
#define BKP_RTC_DR_MU_Msk               (0xFU << BKP_RTC_DR_MU_Pos)             /*!< 0x00000F00 */
/* tens of the months in BCD format */
#define BKP_RTC_DR_MT_Pos               (12U)
#define BKP_RTC_DR_MT_Msk               (0x1U << BKP_RTC_DR_MT_Pos)             /*!< 0x00001000 */
/* week's day number, 0b000 - not used, 0b001 - monday, 0b010 - tuesday, ... 0b111 - sunday */
#define BKP_RTC_DR_WDU_Pos              (13U)
#define BKP_RTC_DR_WDU_Msk              (0x7U << BKP_RTC_DR_WDU_Pos)            /*!< 0x0000E000 */
/* years in BCD format */
#define BKP_RTC_DR_YU_Pos               (16U)
#define BKP_RTC_DR_YU_Msk               (0xFU << BKP_RTC_DR_YU_Pos)             /*!< 0x000F0000 */
/* tens of years in BCD format */
#define BKP_RTC_DR_YT_Pos               (20U)
#define BKP_RTC_DR_YT_Msk               (0xFU << BKP_RTC_DR_YT_Pos)             /*!< 0x00F00000 */

/**********  Bit definition for BKP_RTC_ALRMAR and BKP_RTC_ALRMBR register ****/
/* seconds in BCD format */
#define BKP_RTC_ALRMxR_SU_Pos           (0U)
#define BKP_RTC_ALRMxR_SU_Msk           (0xFU << BKP_RTC_ALRMxR_SU_Pos)         /*!< 0x0000000F */
/* tens of seconds in BCD format */
#define BKP_RTC_ALRMxR_ST_Pos           (4U)
#define BKP_RTC_ALRMxR_ST_Msk           (0x7U << BKP_RTC_ALRMxR_ST_Pos)         /*!< 0x0000007F */
/* mask of the seconds within alarm (0 - seconds is used, 1 - seconds ignored) */
#define BKP_RTC_ALRMxR_MSK1_Pos         (7U)
#define BKP_RTC_ALRMxR_MSK1_Msk         (0x1U << BKP_RTC_ALRMxR_MSK1_Pos)       /*!< 0x00000080 */
#define BKP_RTC_ALRMxR_MSK1				BKP_RTC_ALRMxR_MSK1_Msk
/* minutes in BCD foramt */
#define BKP_RTC_ALRMxR_MNU_Pos          (8U)
#define BKP_RTC_ALRMxR_MNU_Msk          (0xFU << BKP_RTC_ALRMxR_MNU_Pos)        /*!< 0x00000F00 */
/* tens of minutes in BCD format */
#define BKP_RTC_ALRMxR_MNT_Pos          (12U)
#define BKP_RTC_ALRMxR_MNT_Msk          (0x7U << BKP_RTC_ALRMxR_MNT_Pos)        /*!< 0x00007000 */
/* mask of the minutes within alarm (0 - minutes is used, 1 - minutes ignored) */
#define BKP_RTC_ALRMxR_MSK2_Pos         (15U)
#define BKP_RTC_ALRMxR_MSK2_Msk         (0x1U << BKP_RTC_ALRMxR_MSK2_Pos)       /*!< 0x00008000 */
#define BKP_RTC_ALRMxR_MSK2				BKP_RTC_ALRMxR_MSK2_Msk
/* hours in BCD format */
#define BKP_RTC_ALRMxR_HU_Pos           (16U)
#define BKP_RTC_ALRMxR_HU_Msk           (0xFU << BKP_RTC_ALRMxR_HU_Pos)         /*!< 0x000F0000 */
/* tens of hours in BCD format */
#define BKP_RTC_ALRMxR_HT_Pos           (20U)
#define BKP_RTC_ALRMxR_HT_Msk           (0x3U << BKP_RTC_ALRMxR_HT_Pos)         /*!< 0x003F0000 */
/* PM flag (0 - 24 hour format or AM, 1 - PM) */
#define BKP_RTC_ALRMxR_PM_Pos           (22U)
#define BKP_RTC_ALRMxR_PM_Msk           (0x1U << BKP_RTC_ALRMxR_PM_Pos)         /*!< 0x00400000 */
#define BKP_RTC_ALRMxR_PM               BKP_RTC_ALRMxR_PM_Msk
/* mask of the hours within alarm (0 - hours is used, 1 - hours ignored) */
#define BKP_RTC_ALRMxR_MSK3_Pos         (23U)
#define BKP_RTC_ALRMxR_MSK3_Msk         (0x1U << BKP_RTC_ALRMxR_MSK3_Pos)       /*!< 0x00800000 */
#define BKP_RTC_ALRMxR_MSK3				BKP_RTC_ALRMxR_MSK3_Msk
/* day of the month in BCD format */
#define BKP_RTC_ALRMxR_DU_Pos           (24U)
#define BKP_RTC_ALRMxR_DU_Msk           (0xFU << BKP_RTC_ALRMxR_DU_Pos)         /*!< 0x0F000000 */
/* day of the week, 0b000 - not used, 0b001 - monday, 0b010 - tuesday, ... 0b111 - sunday */
#define BKP_RTC_ALRMxR_WDU_Pos          (24U)
#define BKP_RTC_ALRMxR_WDU_Msk          (0x7U << BKP_RTC_ALRMxR_WDU_Pos)        /*!< 0x07000000 */
/* tens of days in BCD format */
#define BKP_RTC_ALRMxR_DT_Pos           (28U)
#define BKP_RTC_ALRMxR_DT_Msk           (0x3U << BKP_RTC_ALRMxR_DT_Pos)         /*!< 0x30000000 */
/* day switch (0 - day of the month, 1 - day of the week) */
#define BKP_RTC_ALRMxR_WDSEL_Pos        (30U)
#define BKP_RTC_ALRMxR_WDSEL_Msk        (0x1U << BKP_RTC_ALRMxR_WDSEL_Pos)      /*!< 0x40000000 */
#define BKP_RTC_ALRMxR_WDSEL			BKP_RTC_ALRMxR_WDSEL_Msk
/* mask of the days (0 - days is used, 1 - days ignored) */
#define BKP_RTC_ALRMxR_MSK4_Pos         (31U)
#define BKP_RTC_ALRMxR_MSK4_Msk         (0x1U << BKP_RTC_ALRMxR_MSK4_Pos)       /*!< 0x80000000 */
#define BKP_RTC_ALRMxR_MSK4				BKP_RTC_ALRMxR_MSK4_Msk

/***  Bit definition for BKP_RTC_TSTR1, BKP_RTC_TSTR2, BKP_RTC_TSTR3 register */
/* seconds in BCD format */
#define BKP_RTC_TSTRx_SU_Pos            BKP_RTC_TR_SU_Pos
#define BKP_RTC_TSTRx_SU_Msk            BKP_RTC_TR_SU_Msk
/* tens of seconds in BCD format */
#define BKP_RTC_TSTRx_ST_Pos            BKP_RTC_TR_ST_Pos
#define BKP_RTC_TSTRx_ST_Msk            BKP_RTC_TR_ST_Msk
/* minutes in BCD format */
#define BKP_RTC_TSTRx_MNU_Pos           BKP_RTC_TR_MNU_Pos
#define BKP_RTC_TSTRx_MNU_Msk           BKP_RTC_TR_MNU_Msk
/* tens of minutes in BCD format */
#define BKP_RTC_TSTRx_MNT_Pos           BKP_RTC_TR_MNT_Pos
#define BKP_RTC_TSTRx_MNT_Msk           BKP_RTC_TR_MNT_Msk
/* hours in BCD format */
#define BKP_RTC_TSTRx_HU_Pos            BKP_RTC_TR_HU_Pos
#define BKP_RTC_TSTRx_HU_Msk            BKP_RTC_TR_HU_Msk
/* tens of hours in BCD format */
#define BKP_RTC_TSTRx_HT_Pos            BKP_RTC_TR_HT_Pos
#define BKP_RTC_TSTRx_HT_Msk            BKP_RTC_TR_HT_Msk
/* PM indicator, (0 - AM or 24 hour format, 1 - PM) */
#define BKP_RTC_TSTRx_PM_Pos            BKP_RTC_TR_PM_Pos
#define BKP_RTC_TSTRx_PM_Msk            BKP_RTC_TR_PM_Msk
#define BKP_RTC_TSTRx_PM                BKP_RTC_TR_PM

/***  Bit definition for BKP_RTC_TSDR1, BKP_RTC_TSDR2, BKP_RTC_TSDR3 register */
/* days in BCD format */
#define BKP_RTC_TSDRx_DU_Pos            BKP_RTC_DR_DU_Pos
#define BKP_RTC_TSDRx_DU_Msk            BKP_RTC_DR_DU_Msk
/* tens of the days in BCD format */
#define BKP_RTC_TSDRx_DT_Pos            BKP_RTC_DR_DT_Pos
#define BKP_RTC_TSDRx_DT_Msk            BKP_RTC_DR_DT_Msk
/* months in BCD format */
#define BKP_RTC_TSDRx_MU_Pos            BKP_RTC_DR_MU_Pos
#define BKP_RTC_TSDRx_MU_Msk            BKP_RTC_DR_MU_Msk
/* tens of the months in BCD format */
#define BKP_RTC_TSDRx_MT_Pos            BKP_RTC_DR_MT_Pos
#define BKP_RTC_TSDRx_MT_Msk            BKP_RTC_DR_MT_Msk
/* week's day number, 0b000 - not used, 0b001 - monday, 0b010 - tuesday, ... 0b111 - sunday */
#define BKP_RTC_TSDRx_WDU_Pos           BKP_RTC_DR_WDU_Pos
#define BKP_RTC_TSDRx_WDU_Msk           BKP_RTC_DR_WDU_Msk
/* years in BCD format */
#define BKP_RTC_TSDRx_YU_Pos            BKP_RTC_DR_YU_Pos
#define BKP_RTC_TSDRx_YU_Msk            BKP_RTC_DR_YU_Msk
/* tens of years in BCD format */
#define BKP_RTC_TSDRx_YT_Pos            BKP_RTC_DR_YT_Pos
#define BKP_RTC_TSDRx_YT_Msk            BKP_RTC_DR_YT_Msk

/*******************  Bit definition for RTC_TAFCR register  ******************/
/* active level for tamper1 detection (0 - hi level, rising edge, 0 - low level, falling edge) */
#define BKP_RTC_TAFCR_TAMPEV_RISING    (0U)
#define BKP_RTC_TAFCR_TAMPEV_FALLING   (1U)
/* tamper detection activation (0 - disabled, 1 - enabled) */
#define BKP_RTC_TAFCR_TAMPE_Pos         (0U)
#define BKP_RTC_TAFCR_TAMPE_Msk         (0x1U << BKP_RTC_TAFCR_TAMPE_Pos)       /*!< 0x00000001 */
#define BKP_RTC_TAFCR_TAMPE             BKP_RTC_TAFCR_TAMPE_Msk
#define BKP_RTC_TAFCR_TAMPTRG1_Pos      (1U)
#define BKP_RTC_TAFCR_TAMPTRG1_Msk      (0x1U << BKP_RTC_TAFCR_TAMPTRG1_Pos)    /*!< 0x00000002 */
#define BKP_RTC_TAFCR_TAMPTRG2_Pos      (2U)
#define BKP_RTC_TAFCR_TAMPTRG2_Msk      (0x1U << BKP_RTC_TAFCR_TAMPTRG2_Pos)    /*!< 0x00000004 */
#define BKP_RTC_TAFCR_TAMPTRG3_Pos      (3U)
#define BKP_RTC_TAFCR_TAMPTRG3_Msk      (0x1U << BKP_RTC_TAFCR_TAMPTRG3_Pos)    /*!< 0x00000008 */
/* tamper interrupt enable (0 - disabled, 1 - enabled) */
#define BKP_RTC_TAFCR_TAMPIE_Pos        (4U)
#define BKP_RTC_TAFCR_TAMPIE_Msk        (0x1U << BKP_RTC_TAFCR_TAMPIE_Pos)      /*!< 0x00000010 */
#define BKP_RTC_TAFCR_TAMPIE            BKP_RTC_TAFCR_TAMPIE_Msk
/* tamper time stamp enable (0 - disabled, 1 - enabled) */
#define BKP_RTC_TAFCR_TSE_Pos           (5U)
#define BKP_RTC_TAFCR_TSE_Msk           (0x1U << BKP_RTC_TAFCR_TSE_Pos)         /*!< 0x00000020 */
#define BKP_RTC_TAFCR_TSE               BKP_RTC_TAFCR_TSE_Msk
#define BKP_RTC_TAFCR_TSEEDGE1_Pos      (6U)
#define BKP_RTC_TAFCR_TSEEDGE1_Msk      (0x1U << BKP_RTC_TAFCR_TSEEDGE1_Pos)    /*!< 0x00000040 */
#define BKP_RTC_TAFCR_TSEEDGE2_Pos      (7U)
#define BKP_RTC_TAFCR_TSEEDGE2_Msk      (0x1U << BKP_RTC_TAFCR_TSEEDGE2_Pos)    /*!< 0x00000080 */
#define BKP_RTC_TAFCR_TSEEDGE3_Pos      (8U)
#define BKP_RTC_TAFCR_TSEEDGE3_Msk      (0x1U << BKP_RTC_TAFCR_TSEEDGE3_Pos)    /*!< 0x00000080 */
/* timestamp interrupt enable (0 - disabled, 1 - enabled) */
#define BKP_RTC_TAFCR_TSIE_Pos          (9U)
#define BKP_RTC_TAFCR_TSIE_Msk          (0x1U << BKP_RTC_TAFCR_TSIE_Pos)        /*!< 0x00000100 */
#define BKP_RTC_TAFCR_TSIE              BKP_RTC_TAFCR_TSIE_Msk
/* tamper history for WAKEUP1 - WAKEUP3 */
#define BKP_RTC_TAFCR_TAMPINSEL_Pos     (16U)
#define BKP_RTC_TAFCR_TAMPINSEL_Msk     (0x7U << BKP_RTC_TAFCR_TAMPINSEL_Pos)   /*!< 0x00070000 */
#define BKP_RTC_TAFCR_TAMPINSEL_WAKEUP1 (0x1U << BKP_RTC_TAFCR_TAMPINSEL_Pos)   /*!< 0x00010000 */
#define BKP_RTC_TAFCR_TAMPINSEL_WAKEUP2 (0x2U << BKP_RTC_TAFCR_TAMPINSEL_Pos)   /*!< 0x00020000 */
#define BKP_RTC_TAFCR_TAMPINSEL_WAKEUP3 (0x4U << BKP_RTC_TAFCR_TAMPINSEL_Pos)   /*!< 0x00040000 */
/* timestamp history for WAKEUP1 - WAKEUP3 */
#define BKP_RTC_TAFCR_TSINSEL_Pos       (19U)
#define BKP_RTC_TAFCR_TSINSEL_Msk       (0x7U << BKP_RTC_TAFCR_TSINSEL_Pos)     /*!< 0x00380000 */
#define BKP_RTC_TAFCR_TSINSEL_WAKEUP1   (0x1U << BKP_RTC_TAFCR_TSINSEL_Pos)     /*!< 0x00080000 */
#define BKP_RTC_TAFCR_TSINSEL_WAKEUP2   (0x2U << BKP_RTC_TAFCR_TSINSEL_Pos)     /*!< 0x00100000 */
#define BKP_RTC_TAFCR_TSINSEL_WAKEUP3   (0x4U << BKP_RTC_TAFCR_TSINSEL_Pos)     /*!< 0x00200000 */

/*
 * ==========================================================================
 * ---------------------- ADCUI registers bits ------------------------------
 * ==========================================================================
 */

/*******************  Bit definition for ADCUI_CTRL1 register  ****************/
/* integration threshold
 * 0b00 - zero threshold,
 * 0b01 - threshold 0,012% of the full scale
 * 0b10 - threshold 0,0061% of the full scale
 * 0b11 - threshold 0,00305% of the full scale */
#define ADCUI_CTRL1_THRESHOLD_0         (0U)
#define ADCUI_CTRL1_THRESHOLD_0012      (1U)
#define ADCUI_CTRL1_THRESHOLD_00061     (2U)
#define ADCUI_CTRL1_THRESHOLD_000305    (3U)

/* programmable gain amplifier options */
#define ADCUI_PGA_0dB					(0U)
#define ADCUI_PGA_6dB					(1U)
#define ADCUI_PGA_12dB					(2U)
#define ADCUI_PGA_18dB					(3U)

/* programmable channel gain */
#define ADCUI_GAIN_0dB					(0U)
#define ADCUI_GAIN_6dB					(1U)

/* FIFO source selection */
#define ADCUI_FIFO_RAW					(0U)
#define ADCUI_FIFO_ACT_POWER			(1U)
#define ADCUI_FIFO_REACT_POWER			(2U)
#define ADCUI_FIFO_FULL_POWER			(3U)

/* channel I0 enable (0 - disabled, 1 - enabled) */
#define ADCUI_CTRL1_I0EN_Pos            (0U)
#define ADCUI_CTRL1_I0EN_Msk            (0x1U << ADCUI_CTRL1_I0EN_Pos)          /*!< 0x00000001 */
#define ADCUI_CTRL1_I0EN                ADCUI_CTRL1_I0EN_Msk
/* channel V0 enable (0 - disabled, 1 - enabled) */
#define ADCUI_CTRL1_V0EN_Pos            (1U)
#define ADCUI_CTRL1_V0EN_Msk            (0x1U << ADCUI_CTRL1_V0EN_Pos)          /*!< 0x00000002 */
#define ADCUI_CTRL1_V0EN                ADCUI_CTRL1_V0EN_Msk
/* channel I1 enable (0 - disabled, 1 - enabled) */
#define ADCUI_CTRL1_I1EN_Pos            (2U)
#define ADCUI_CTRL1_I1EN_Msk            (0x1U << ADCUI_CTRL1_I1EN_Pos)          /*!< 0x00000004 */
#define ADCUI_CTRL1_I1EN                ADCUI_CTRL1_I1EN_Msk
/* channel V1 enable (0 - disabled, 1 - enabled) */
#define ADCUI_CTRL1_V1EN_Pos            (3U)
#define ADCUI_CTRL1_V1EN_Msk            (0x1U << ADCUI_CTRL1_V1EN_Pos)          /*!< 0x00000008 */
#define ADCUI_CTRL1_V1EN                ADCUI_CTRL1_V1EN_Msk
/* channel I2 enable (0 - disabled, 1 - enabled) */
#define ADCUI_CTRL1_I2EN_Pos            (4U)
#define ADCUI_CTRL1_I2EN_Msk            (0x1U << ADCUI_CTRL1_I2EN_Pos)          /*!< 0x00000010 */
#define ADCUI_CTRL1_I2EN                ADCUI_CTRL1_I2EN_Msk
/* channel V2 enable (0 - disabled, 1 - enabled) */
#define ADCUI_CTRL1_V2EN_Pos            (5U)
#define ADCUI_CTRL1_V2EN_Msk            (0x1U << ADCUI_CTRL1_V2EN_Pos)          /*!< 0x00000020 */
#define ADCUI_CTRL1_V2EN                ADCUI_CTRL1_V2EN_Msk
/* channel I3 enable (0 - disabled, 1 - enabled) */
#define ADCUI_CTRL1_I3EN_Pos            (6U)
#define ADCUI_CTRL1_I3EN_Msk            (0x1U << ADCUI_CTRL1_I3EN_Pos)          /*!< 0x00000040 */
#define ADCUI_CTRL1_I3EN                ADCUI_CTRL1_I3EN_Msk
/* resolution (0 - 16 bit / 1 - 24 bit) */
#define ADCUI_CTRL1_RESOL_Pos           (7U)
#define ADCUI_CTRL1_RESOL_Msk           (0x1U << ADCUI_CTRL1_RESOL_Pos)         /*!< 0x00000080 */
#define ADCUI_CTRL1_RESOL_16BIT         (0x0U << ADCUI_CTRL1_RESOL_Pos)         /*!< 0x00000000 */
#define ADCUI_CTRL1_RESOL_24BIT         (0x1U << ADCUI_CTRL1_RESOL_Pos)         /*!< 0x00000080 */
/* low-pass filter for zero-cross detection (0 - enabled, 1 - disabled) */
#define ADCUI_CTRL1_ZXLPF_Pos           (8U)
#define ADCUI_CTRL1_ZXLPF_Msk           (0x1U << ADCUI_CTRL1_ZXLPF_Pos)         /*!< 0x00000100 */
#define ADCUI_CTRL1_ZXLPF_DISABLE       ADCUI_CTRL1_ZXLPF_Msk
/* frequency and phase-shift integration interval (2^N) */
#define ADCUI_CTRL1_PER_LENGTH_Pos      (9U)
#define ADCUI_CTRL1_PER_LENGTH_Msk      (0x7U << ADCUI_CTRL1_PER_LENGTH_Pos)    /*!< 0x00000E00 */
#define ADCUI_CTRL1_PER_LENGTH_1		(0x0U << ADCUI_CTRL1_PER_LENGTH_Pos)
#define ADCUI_CTRL1_PER_LENGTH_2		(0x1U << ADCUI_CTRL1_PER_LENGTH_Pos)
#define ADCUI_CTRL1_PER_LENGTH_4		(0x2U << ADCUI_CTRL1_PER_LENGTH_Pos)
#define ADCUI_CTRL1_PER_LENGTH_8		(0x3U << ADCUI_CTRL1_PER_LENGTH_Pos)
#define ADCUI_CTRL1_PER_LENGTH_16		(0x4U << ADCUI_CTRL1_PER_LENGTH_Pos)
#define ADCUI_CTRL1_PER_LENGTH_32		(0x5U << ADCUI_CTRL1_PER_LENGTH_Pos)
#define ADCUI_CTRL1_PER_LENGTH_64		(0x6U << ADCUI_CTRL1_PER_LENGTH_Pos)
#define ADCUI_CTRL1_PER_LENGTH_128		(0x7U << ADCUI_CTRL1_PER_LENGTH_Pos)
/* no-load threshold for active power */
#define ADCUI_CTRL1_APNOLOAD_Pos        (12U)
#define ADCUI_CTRL1_APNOLOAD_Msk        (0x3U << ADCUI_CTRL1_APNOLOAD_Pos)      /*!< 0x00003000 */
/* no-load threshold for reactive power */
#define ADCUI_CTRL1_VARNOLOAD_Pos       (15U)
#define ADCUI_CTRL1_VARNOLOAD_Msk       (0x3U << ADCUI_CTRL1_VARNOLOAD_Pos)     /*!< 0x00018000 */
/* no-load threshold for full power */
#define ADCUI_CTRL1_VANOLOAD_Pos        (17U)
#define ADCUI_CTRL1_VANOLOAD_Msk        (0x3U << ADCUI_CTRL1_VANOLOAD_Pos)      /*!< 0x00060000 */
/* refresh frequency for voltage channels (0 - use last calculated, 1 - refresh enabled) */
#define ADCUI_CTRL1_FREQSEL_Pos         (19U)
#define ADCUI_CTRL1_FREQSEL_Msk         (0x1U << ADCUI_CTRL1_FREQSEL_Pos)       /*!< 0x00080000 */
#define ADCUI_CTRL1_FREQSEL             ADCUI_CTRL1_FREQSEL_Msk
/* reference voltage selection (0 - external reference, 1 - internal reference) */
#define ADCUI_CTRL1_VREFSEL_Pos         (20U)
#define ADCUI_CTRL1_VREFSEL_Msk         (0x1U << ADCUI_CTRL1_VREFSEL_Pos)       /*!< 0x00100000 */
#define ADCUI_CTRL1_VREFSEL				ADCUI_CTRL1_VREFSEL_Msk
/* update RMS at zero-crossing (0 - immediately, 1 - only at zero-cross) */
#define ADCUI_CTRL1_ZXRMS_Pos           (27U)
#define ADCUI_CTRL1_ZXRMS_Msk           (0x1U << ADCUI_CTRL1_ZXRMS_Pos)         /*!< 0x08000000 */
#define ADCUI_CTRL1_ZXRMS_ZeroCross     ADCUI_CTRL1_ZXRMS_Msk
/* reset digital ADC processing (0 - no reset, 1 - reset) */
#define ADCUI_CTRL1_RESETDIG_Pos        (28U)
#define ADCUI_CTRL1_RESETDIG_Msk        (0x1U << ADCUI_CTRL1_RESETDIG_Pos)      /*!< 0x10000000 */
#define ADCUI_CTRL1_RESETDIG            ADCUI_CTRL1_RESETDIG_Msk
/* speed selection (0b00 - 4kHz, 0b01 - 8kHz, 0b11 - 16kHz) */
#define ADCUI_CTRL1_OSR_CONF_Pos        (30U)
#define ADCUI_CTRL1_OSR_CONF_Msk        (0x3U << ADCUI_CTRL1_OSR_CONF_Pos)      /*!< 0xC0000000 */
#define ADCUI_CTRL1_OSR_CONF_4KHZ       (0x0U << ADCUI_CTRL1_OSR_CONF_Pos)      /*!< 0x00000000 */
#define ADCUI_CTRL1_OSR_CONF_8KHZ       (0x1U << ADCUI_CTRL1_OSR_CONF_Pos)      /*!< 0x40000000 */
#define ADCUI_CTRL1_OSR_CONF_16KHZ      (0x2U << ADCUI_CTRL1_OSR_CONF_Pos)      /*!< 0x80000000 */

/*******************  Bit definition for ADCUI_CTRL2 register  ****************/
/* low voltage threshold */
#define ADCUI_CTRL2_SAGLVL_Pos          (0U)
#define ADCUI_CTRL2_SAGLVL_Msk          (0xFFFFU << ADCUI_CTRL2_SAGLVL_Pos)     /*!< 0x0000FFFF */
/* number of half-period integration interval for low voltage threshold */
#define ADCUI_CTRL2_SAGCYC_Pos          (16U)
#define ADCUI_CTRL2_SAGCYC_Msk          (0xFFU << ADCUI_CTRL2_SAGCYC_Pos)       /*!< 0x00FF0000 */

/*******************  Bit definition for ADCUI_CTRL3 register  ****************/
/* timeout without voltage */
#define ADCUI_CTRL3_ZXTOUT_Pos          (0U)
#define ADCUI_CTRL3_ZXTOUT_Msk          (0xFFFU << ADCUI_CTRL3_ZXTOUT_Pos)      /*!< 0x00000FFF */

/*******************  Bit definition for ADCUI_F0CTR register  ****************/
/* integration for I0 (0 - integration enabled, 1 - disabled) */
#define ADCUI_F0CTR_F0I0NTEN_Pos        (0U)
#define ADCUI_F0CTR_F0I0NTEN_Msk        (0x1U << ADCUI_F0CTR_F0I0NTEN_Pos)      /*!< 0x00000001 */
#define ADCUI_F0CTR_F0I0NTEN            ADCUI_F0CTR_F0I0NTEN_Msk
/* integration for I3 (0 - disabled, 1 - enabled) */
#define ADCUI_F0CTR_F0I3NTEN_Pos        (1U)
#define ADCUI_F0CTR_F0I3NTEN_Msk        (0x1U << ADCUI_F0CTR_F0I3NTEN_Pos)      /*!< 0x00000002 */
#define ADCUI_F0CTR_F0I3NTEN            ADCUI_F0CTR_F0I3NTEN_Msk
/* source for full energy (0 - full energy, 1 - current RMS) */
#define ADCUI_F0CTR_F0VASEL_Pos         (2U)
#define ADCUI_F0CTR_F0VASEL_Msk         (0x1U << ADCUI_F0CTR_F0VASEL_Pos)       /*!< 0x00000004 */
#define ADCUI_F0CTR_F0VASEL_FULLPOWER   (0x0U << ADCUI_F0CTR_F0VASEL_Pos)
#define ADCUI_F0CTR_F0VASEL_IRMS        (0x1U << ADCUI_F0CTR_F0VASEL_Pos)
/* reset active power register (write 1 to reset value) */
#define ADCUI_F0CTR_F0RARS_Pos          (3U)
#define ADCUI_F0CTR_F0RARS_Msk          (0x1U << ADCUI_F0CTR_F0RARS_Pos)        /*!< 0x00000008 */
#define ADCUI_F0CTR_F0RARS              ADCUI_F0CTR_F0RARS_Msk
/* reset reactive power register (write 1 to reset value) */
#define ADCUI_F0CTR_F0RRRS_Pos          (4U)
#define ADCUI_F0CTR_F0RRRS_Msk          (0x1U << ADCUI_F0CTR_F0RRRS_Pos)        /*!< 0x00000010 */
#define ADCUI_F0CTR_F0RRRS              ADCUI_F0CTR_F0RRRS_Msk
/* reset full power register (write 1 to reset value) */
#define ADCUI_F0CTR_F0RVRS_Pos          (5U)
#define ADCUI_F0CTR_F0RVRS_Msk          (0x1U << ADCUI_F0CTR_F0RVRS_Pos)        /*!< 0x00000020 */
#define ADCUI_F0CTR_F0RVRS              ADCUI_F0CTR_F0RVRS_Msk
/* gain for V0, use ADCUI_PGA */
#define ADCUI_F0CTR_F0VGAIN_Pos         (6U)
#define ADCUI_F0CTR_F0VGAIN_Msk         (0x3U << ADCUI_F0CTR_F0VGAIN_Pos)       /*!< 0x000000C0 */
/* gain for I0, use ADCUI_PGA */
#define ADCUI_F0CTR_F0I0GAIN_Pos        (8U)
#define ADCUI_F0CTR_F0I0GAIN_Msk        (0x3U << ADCUI_F0CTR_F0I0GAIN_Pos)      /*!< 0x00000300 */
/* phase shift between voltage and current (-126 (-123us) ... +127 (+124us)) */
#define ADCUI_F0CTR_F0VPHASE_Pos        (10U)
#define ADCUI_F0CTR_F0VPHASE_Msk        (0xFFU << ADCUI_F0CTR_F0VPHASE_Pos)      /*!< 0x003FC00 */
/* gain for I3, use ADCUI_PGA */
#define ADCUI_F0CTR_F0I3GAIN_Pos        (18U)
#define ADCUI_F0CTR_F0I3GAIN_Msk        (0x3U << ADCUI_F0CTR_F0I3GAIN_Pos)      /*!< 0x000C0000 */
/* calibration for I RMS */
#define ADCUI_F0CTR_F0IRMSOS_Pos        (20U)
#define ADCUI_F0CTR_F0IRMSOS_Msk        (0xFFFU << ADCUI_F0CTR_F0IRMSOS_Pos)    /*!< 0xFFF00000 */

/*******************  Bit definition for ADCUI_F0WC register  *****************/
/* calibration offset for active power */
#define ADCUI_F0WC_F0WATTOS_Pos         (0U)
#define ADCUI_F0WC_F0WATTOS_Msk         (0xFFFFU << ADCUI_F0WC_F0WATTOS_Pos)    /*!< 0x0000FFFF */
/* calibration gain for active power */
#define ADCUI_F0WC_F0WGAIN_Pos          (16U)
#define ADCUI_F0WC_F0WGAIN_Msk          (0xFFFU << ADCUI_F0WC_F0WGAIN_Pos)      /*!< 0x0FFF0000 */

/*******************  Bit definition for ADCUI_F0VC register  *****************/
/* calibration offset for reactive power */
#define ADCUI_F0VC_F0VAROS_Pos          (0U)
#define ADCUI_F0VC_F0VAROS_Msk          (0xFFFFU << ADCUI_F0VC_F0VAROS_Pos)     /*!< 0x0000FFFF */
/* calibration gain for reactive power */
#define ADCUI_F0VC_F0VARGAIN_Pos        (16U)
#define ADCUI_F0VC_F0VARGAIN_Msk        (0xFFFU << ADCUI_F0VC_F0VARGAIN_Pos)    /*!< 0x0FFF0000 */

/*******************  Bit definition for ADCUI_F0AC register  *****************/
/* voltage RMS calibration */
#define ADCUI_F0AC_F0VRMSOS_Pos         (0U)
#define ADCUI_F0AC_F0VRMSOS_Msk         (0xFFFU << ADCUI_F0AC_F0VRMSOS_Pos)     /*!< 0x00000FFF */
/* source for ADCUI_F0I3DAT: (0 - after HPF, 1 - before HPF) */
#define ADCUI_F0AC_F0I3SEL_Pos          (12U)
#define ADCUI_F0AC_F0I3SEL_Msk          (0x1U << ADCUI_F0AC_F0I3SEL_Pos)        /*!< 0x00001000 */
#define ADCUI_F0AC_F0I3SEL_AfterHPF     (0x0U << ADCUI_F0AC_F0I3SEL_Pos)        /*!< 0x00000000 */
#define ADCUI_F0AC_F0I3SEL_BeforeHPF    (0x1U << ADCUI_F0AC_F0I3SEL_Pos)        /*!< 0x00001000 */
/* voltage gain calibration */
#define ADCUI_F0AC_F0VAGAIN_Pos         (16U)
#define ADCUI_F0AC_F0VAGAIN_Msk         (0xFFFU << ADCUI_F0AC_F0VAGAIN_Pos)     /*!< 0x0FFF0000 */

/*******************  Bit definition for ADCUI_F0MD0 register  ****************/
/* source for ADCUI_F0VDAT (0b00 - voltage, 0b01 - active power, 0b10 - reactive power, 0b11 - full power)
 * use ADCUI_FIFO_XX options */
#define ADCUI_F0MD0_F0VSEL_Pos          (0U)
#define ADCUI_F0MD0_F0VSEL_Msk          (0x3U << ADCUI_F0MD0_F0VSEL_Pos)        /*!< 0x00000003 */
/* source for ADCUI_F0IDAT (0b00 - current, 0b01 - active power, 0b10 - reactive power, 0b11 - full power)
 * use ADCUI_FIFO_XX options */
#define ADCUI_F0MD0_F0ISEL_Pos          (2U)
#define ADCUI_F0MD0_F0ISEL_Msk          (0x3U << ADCUI_F0MD0_F0ISEL_Pos)        /*!< 0x0000000C */
/* active power polarity at last time (0 - positive, 1 - negative) */
#define ADCUI_F0MD0_F0ACTS_Pos          (4U)
#define ADCUI_F0MD0_F0ACTS_Msk          (0x1U << ADCUI_F0MD0_F0ACTS_Pos)        /*!< 0x00000010 */
#define ADCUI_F0MD0_F0ACTS_POSITIVE     (0x0U << ADCUI_F0MD0_F0ACTS_Pos)
#define ADCUI_F0MD0_F0ACTS_NEGATIVE     (0x1U << ADCUI_F0MD0_F0ACTS_Pos)
/* reactive power polarity at last time (0 - positive, 1 - negative) */
#define ADCUI_F0MD0_F0REACTS_Pos        (5U)
#define ADCUI_F0MD0_F0REACTS_Msk        (0x1U << ADCUI_F0MD0_F0REACTS_Pos)      /*!< 0x00000020 */
#define ADCUI_F0MD0_F0REACTS_POSITIVE   (0x0U << ADCUI_F0MD0_F0REACTS_Pos)
#define ADCUI_F0MD0_F0REACTS_NEGATIVE   (0x1U << ADCUI_F0MD0_F0REACTS_Pos)
/* I0 gain (0 - 0dB, 1 - +6dB), use ADC_GAIN */
#define ADCUI_F0MD0_I0GAIN_Pos          (6U)
#define ADCUI_F0MD0_I0GAIN_Msk          (0x1U << ADCUI_F0MD0_I0GAIN_Pos)        /*!< 0x00000040 */
/* V0 gain (0 - 0dB, 1 - +6dB), use ADC_GAIN */
#define ADCUI_F0MD0_V0GAIN_Pos          (7U)
#define ADCUI_F0MD0_V0GAIN_Msk          (0x1U << ADCUI_F0MD0_V0GAIN_Pos)        /*!< 0x00000080 */
/* I3 gain (0 - 0dB, 1 - +6dB), use ADC_GAIN */
#define ADCUI_F0MD0_I3GAIN_Pos          (8U)
#define ADCUI_F0MD0_I3GAIN_Msk          (0x1U << ADCUI_F0MD0_I3GAIN_Pos)        /*!< 0x00000100 */
/* period frequency (period duriation) */
#define ADCUI_F0MD0_F0PER_FREQ_Pos      (9U)
#define ADCUI_F0MD0_F0PER_FREQ_Msk      (0x1FFFFFU << ADCUI_F0MD0_F0PER_FREQ_Pos) /*!< 0x3FFFFE00 */
/* I active channel (0b00, 0b11 - auto select, 0b01 - active I0, 0b10 - active I3) */
#define ADCUI_F0MD0_F0SEL_I_CH_Pos      (30U)
#define ADCUI_F0MD0_F0SEL_I_CH_Msk      (0x3U << ADCUI_F0MD0_F0SEL_I_CH_Pos)    /*!< 0xC0000000 */
#define ADCUI_F0MD0_F0SEL_I_CH_AUTO     (0x0U << ADCUI_F0MD0_F0SEL_I_CH_Pos)
#define ADCUI_F0MD0_F0SEL_I_CH_I0       (0x1U << ADCUI_F0MD0_F0SEL_I_CH_Pos)
#define ADCUI_F0MD0_F0SEL_I_CH_I3       (0x2U << ADCUI_F0MD0_F0SEL_I_CH_Pos)

/*******************  Bit definition for ADCUI_F0MD1 register  ****************/
/* maximum permitted current */
#define ADCUI_F0MD1_F0IPKLVL_Pos        (0U)
#define ADCUI_F0MD1_F0IPKLVL_Msk        (0xFFFFU << ADCUI_F0MD1_F0IPKLVL_Pos)   /*!< 0x0000FFFF */
/* maximum permitted voltage */
#define ADCUI_F0MD1_F0VPKLVL_Pos        (16U)
#define ADCUI_F0MD1_F0VPKLVL_Msk        (0xFFFFU << ADCUI_F0MD1_F0VPKLVL_Pos)   /*!< 0xFFFF0000 */

/*******************  Bit definition for ADCUI_F0STAT register  ***************/
/* FIFO F0VDAT empty */
#define ADCUI_F0STAT_F0VF_EMP_Pos       (0U)
#define ADCUI_F0STAT_F0VF_EMP_Msk       (0x1U << ADCUI_F0STAT_F0VF_EMP_Pos)     /*!< 0x00000001 */
#define ADCUI_F0STAT_F0VF_EMP           ADCUI_F0STAT_F0VF_EMP_Msk
/* FIFO F0VDAT full */
#define ADCUI_F0STAT_F0VF_FLL_Pos       (1U)
#define ADCUI_F0STAT_F0VF_FLL_Msk       (0x1U << ADCUI_F0STAT_F0VF_FLL_Pos)     /*!< 0x00000002 */
#define ADCUI_F0STAT_F0VF_FLL           ADCUI_F0STAT_F0VF_FLL_Msk
/* FIFO F0VDAT overflow */
#define ADCUI_F0STAT_F0VF_OVR_Pos       (2U)
#define ADCUI_F0STAT_F0VF_OVR_Msk       (0x1U << ADCUI_F0STAT_F0VF_OVR_Pos)     /*!< 0x00000004 */
#define ADCUI_F0STAT_F0VF_OVR           ADCUI_F0STAT_F0VF_OVR_Msk
/* FIFO F0IDAT empty */
#define ADCUI_F0STAT_F0IF_EMP_Pos       (3U)
#define ADCUI_F0STAT_F0IF_EMP_Msk       (0x1U << ADCUI_F0STAT_F0IF_EMP_Pos)     /*!< 0x00000008 */
#define ADCUI_F0STAT_F0IF_EMP           ADCUI_F0STAT_F0IF_EMP_Msk
/* FIFO F0IDAT full */
#define ADCUI_F0STAT_F0IF_FLL_Pos       (4U)
#define ADCUI_F0STAT_F0IF_FLL_Msk       (0x1U << ADCUI_F0STAT_F0IF_FLL_Pos)     /*!< 0x00000010 */
#define ADCUI_F0STAT_F0IF_FLL           ADCUI_F0STAT_F0IF_FLL_Msk
/* FIFO F0IDAT overflow */
#define ADCUI_F0STAT_F0IF_OVR_Pos       (5U)
#define ADCUI_F0STAT_F0IF_OVR_Msk       (0x1U << ADCUI_F0STAT_F0IF_OVR_Pos)     /*!< 0x00000020 */
#define ADCUI_F0STAT_F0IF_OVR           ADCUI_F0STAT_F0IF_OVR_Msk
/* voltage drop detected */
#define ADCUI_F0STAT_F0SAGF_Pos         (6U)
#define ADCUI_F0STAT_F0SAGF_Msk         (0x1U << ADCUI_F0STAT_F0SAGF_Pos)       /*!< 0x00000040 */
#define ADCUI_F0STAT_F0SAGF             ADCUI_F0STAT_F0SAGF_Msk
/* overvoltage detected */
#define ADCUI_F0STAT_F0PEAKVF_Pos       (7U)
#define ADCUI_F0STAT_F0PEAKVF_Msk       (0x1U << ADCUI_F0STAT_F0PEAKVF_Pos)     /*!< 0x00000080 */
#define ADCUI_F0STAT_F0PEAKVF           ADCUI_F0STAT_F0PEAKVF_Msk
/* overcurrnet detected */
#define ADCUI_F0STAT_F0PEAKIF_Pos       (8U)
#define ADCUI_F0STAT_F0PEAKIF_Msk       (0x1U << ADCUI_F0STAT_F0PEAKIF_Pos)     /*!< 0000000100 */
#define ADCUI_F0STAT_F0PEAKIF           ADCUI_F0STAT_F0PEAKIF_Msk
/* positive active power overflow */
#define ADCUI_F0STAT_F0WATTOVP_Pos      (9U)
#define ADCUI_F0STAT_F0WATTOVP_Msk      (0x1U << ADCUI_F0STAT_F0WATTOVP_Pos)    /*!< 0x00000200 */
#define ADCUI_F0STAT_F0WATTOVP          ADCUI_F0STAT_F0WATTOVP_Msk
/* positive reactive power overflow */
#define ADCUI_F0STAT_F0VAROVP_Pos       (10U)
#define ADCUI_F0STAT_F0VAROVP_Msk       (0x1U << ADCUI_F0STAT_F0VAROVP_Pos)     /*!< 0x00000400 */
#define ADCUI_F0STAT_F0VAROVP           ADCUI_F0STAT_F0VAROVP_Msk
/* full power overflow */
#define ADCUI_F0STAT_F0VAOV_Pos         (11U)
#define ADCUI_F0STAT_F0VAOV_Msk         (0x1U << ADCUI_F0STAT_F0VAOV_Pos)       /*!< 0000000800 */
#define ADCUI_F0STAT_F0VAOV             ADCUI_F0STAT_F0VAOV_Msk
/* no voltage timeout */
#define ADCUI_F0STAT_F0ZXTOF_Pos        (12U)
#define ADCUI_F0STAT_F0ZXTOF_Msk        (0x1U << ADCUI_F0STAT_F0ZXTOF_Pos)      /*!< 0x00001000 */
#define ADCUI_F0STAT_F0ZXTOF            ADCUI_F0STAT_F0ZXTOF_Msk
/* active current channel (0 - I0, 1 - I3) */
#define ADCUI_F0STAT_F0ICHANNEL_Pos     (13U)
#define ADCUI_F0STAT_F0ICHANNEL_Msk     (0x1U << ADCUI_F0STAT_F0ICHANNEL_Pos)   /*!< 0x00002000 */
#define ADCUI_F0STAT_F0ICHANNEL_I0      (0x0U << ADCUI_F0STAT_F0ICHANNEL_Pos)
#define ADCUI_F0STAT_F0ICHANNEL_I3      (0x1U << ADCUI_F0STAT_F0ICHANNEL_Pos)
/* active current channel switch detected (write 1 to drop this flag) */
#define ADCUI_F0STAT_F0FAULTCON_Pos     (14U)
#define ADCUI_F0STAT_F0FAULTCON_Msk     (0x1U << ADCUI_F0STAT_F0FAULTCON_Pos)   /*!< 0x00004000 */
#define ADCUI_F0STAT_F0FAULTCON         ADCUI_F0STAT_F0FAULTCON_Msk
/* active power direction change (write 1 to drop this flag) */
#define ADCUI_F0STAT_F0APSIGN_Pos       (15U)
#define ADCUI_F0STAT_F0APSIGN_Msk       (0x1U << ADCUI_F0STAT_F0APSIGN_Pos)     /*!< 0x00008000 */
#define ADCUI_F0STAT_F0APSIGN           ADCUI_F0STAT_F0APSIGN_Msk
/* active power is under threshold */
#define ADCUI_F0STAT_F0APNLDFL_Pos      (16U)
#define ADCUI_F0STAT_F0APNLDFL_Msk      (0x1U << ADCUI_F0STAT_F0APNLDFL_Pos)    /*!< 0x00010000 */
#define ADCUI_F0STAT_F0APNLDFL          ADCUI_F0STAT_F0APNLDFL_Msk
/* reactive power direction change (write 1 to drop this flag) */
#define ADCUI_F0STAT_F0VARSIGN_Pos      (17U)
#define ADCUI_F0STAT_F0VARSIGN_Msk      (0x1U << ADCUI_F0STAT_F0VARSIGN_Pos)    /*!< 0x00020000 */
#define ADCUI_F0STAT_F0VARSIGN          ADCUI_F0STAT_F0VARSIGN_Msk
/* reactive power is under threshold */
#define ADCUI_F0STAT_F0VARNLDFL_Pos     (18U)
#define ADCUI_F0STAT_F0VARNLDFL_Msk     (0x1U <ADCUI_F0STAT_F0VARNLDFL_Pos)     /*!< 0x00040000 */
#define ADCUI_F0STAT_F0VARNLDFL         ADCUI_F0STAT_F0VARNLDFL_Msk
/* full power is under threshold */
#define ADCUI_F0STAT_F0ANLDFL_Pos       (20U)
#define ADCUI_F0STAT_F0ANLDFL_Msk       (0x1U << ADCUI_F0STAT_F0ANLDFL_Pos)     /*!< 0x00100000 */
#define ADCUI_F0STAT_F0ANLDFL           ADCUI_F0STAT_F0ANLDFL_Msk
/* zero-cross detected (write 1 to drop this flag) */
#define ADCUI_F0STAT_F0ZEROCRS_Pos      (21U)
#define ADCUI_F0STAT_F0ZEROCRS_Msk      (0x1U << ADCUI_F0STAT_F0ZEROCRS_Pos)    /*!< 0x00200000 */
#define ADCUI_F0STAT_F0ZEROCRS          ADCUI_F0STAT_F0ZEROCRS_Msk
/* FIFO C3IDAT empty */
#define ADCUI_F0STAT_C3IF_EMP_Pos       (22U)
#define ADCUI_F0STAT_C3IF_EMP_Msk       (0x1U << ADCUI_F0STAT_C3IF_EMP_Pos)     /*!< 0x00400000 */
#define ADCUI_F0STAT_C3IF_EMP           ADCUI_F0STAT_C3IF_EMP_Msk
/* FIFO C3IDAT full */
#define ADCUI_F0STAT_C3IF_FLL_Pos       (23U)
#define ADCUI_F0STAT_C3IF_FLL_Msk       (0x1U << ADCUI_F0STAT_C3IF_FLL_Pos)     /*!< 0x00800000 */
#define ADCUI_F0STAT_C3IF_FLL           ADCUI_F0STAT_C3IF_FLL_Msk
/* FIFO C3IDAT overflow (write 1 to drop this flag) */
#define ADCUI_F0STAT_C3IF_OVR_Pos       (24U)
#define ADCUI_F0STAT_C3IF_OVR_Msk       (0x1U << ADCUI_F0STAT_C3IF_OVR_Pos)     /*!< 0x01000000 */
#define ADCUI_F0STAT_C3IF_OVR           ADCUI_F0STAT_C3IF_OVR_Msk
/* negative active power overflow (write 1 to drop this flag) */
#define ADCUI_F0STAT_F0WATTOVN_Pos      (25U)
#define ADCUI_F0STAT_F0WATTOVN_Msk      (0x1U << ADCUI_F0STAT_F0WATTOVN_Pos)    /*!< 0x02000000 */
#define ADCUI_F0STAT_F0WATTOVN          ADCUI_F0STAT_F0WATTOVN_Msk
/* negative reactive power overflow (write 1 to drop this flag) */
#define ADCUI_F0STAT_F0VAROVN_Pos       (26U)
#define ADCUI_F0STAT_F0VAROVN_Msk       (0x1U << ADCUI_F0STAT_F0VAROVN_Pos)     /*!< 0x04000000 */
#define ADCUI_F0STAT_F0VAROVN           ADCUI_F0STAT_F0VAROVN_Msk

/*******************  Bit definition for ADCUI_F0MASK register  ***************/
/* bit mask F0VF_EMP */
#define ADCUI_F0MASK_F0VF_EMPM_Pos      (0U)
#define ADCUI_F0MASK_F0VF_EMPM_Msk      (0x1U << ADCUI_F0MASK_F0VF_EMPM_Pos)    /*!< 0x00000001 */
#define ADCUI_F0MASK_F0VF_EMPM          ADCUI_F0MASK_F0VF_EMPM_Msk
/* bit mask F0VF_FLL */
#define ADCUI_F0MASK_F0VF_FLLM_Pos      (1U)
#define ADCUI_F0MASK_F0VF_FLLM_Msk      (0x1U << ADCUI_F0MASK_F0VF_FLLM_Pos)    /*!< 0x00000002 */
#define ADCUI_F0MASK_F0VF_FLLM          ADCUI_F0MASK_F0VF_FLLM_Msk
/* bit mask F0VF_OVR */
#define ADCUI_F0MASK_F0VF_OVRM_Pos      (2U)
#define ADCUI_F0MASK_F0VF_OVRM_Msk      (0x1U << ADCUI_F0MASK_F0VF_OVRM_Pos)    /*!< 0x00000004 */
#define ADCUI_F0MASK_F0VF_OVRM          ADCUI_F0MASK_F0VF_OVRM_Msk
/* bit mask F0IF_EMP */
#define ADCUI_F0MASK_F0IF_EMPM_Pos      (3U)
#define ADCUI_F0MASK_F0IF_EMPM_Msk      (0x1U << ADCUI_F0MASK_F0IF_EMPM_Pos)    /*!< 0x00000008 */
#define ADCUI_F0MASK_F0IF_EMPM          ADCUI_F0MASK_F0IF_EMPM_Msk
/* bit mask F0IF_FLL */
#define ADCUI_F0MASK_F0IF_FLLM_Pos      (4U)
#define ADCUI_F0MASK_F0IF_FLLM_Msk      (0x1U << ADCUI_F0MASK_F0IF_FLLM_Pos)    /*!< 0x00000010 */
#define ADCUI_F0MASK_F0IF_FLLM          ADCUI_F0MASK_F0IF_FLLM_Msk
/* bit mask F0IF_OVR */
#define ADCUI_F0MASK_F0IF_OVRM_Pos      (5U)
#define ADCUI_F0MASK_F0IF_OVRM_Msk      (0x1U << ADCUI_F0MASK_F0IF_OVRM_Pos)    /*!< 0x00000020 */
#define ADCUI_F0MASK_F0IF_OVRM          ADCUI_F0MASK_F0IF_OVRM_Msk
/* bit mask F0SAGF */
#define ADCUI_F0MASK_F0SAGFM_Pos        (6U)
#define ADCUI_F0MASK_F0SAGFM_Msk        (0x1U << ADCUI_F0MASK_F0SAGFM_Pos)      /*!< 0x00000040 */
#define ADCUI_F0MASK_F0SAGFM            ADCUI_F0MASK_F0SAGFM_Msk
/* bit mask F0PEAKVF */
#define ADCUI_F0MASK_F0PEAKVFM_Pos      (7U)
#define ADCUI_F0MASK_F0PEAKVFM_Msk      (0x1U << ADCUI_F0MASK_F0PEAKVFM_Pos)    /*!< 0x00000080 */
#define ADCUI_F0MASK_F0PEAKVFM          ADCUI_F0MASK_F0PEAKVFM_Msk
/* bit mask F0PEAKIF */
#define ADCUI_F0MASK_F0PEAKIFM_Pos      (8U)
#define ADCUI_F0MASK_F0PEAKIFM_Msk      (0x1U << ADCUI_F0MASK_F0PEAKIFM_Pos)    /*!< 0x00000100 */
#define ADCUI_F0MASK_F0PEAKIFM          ADCUI_F0MASK_F0PEAKIFM_Msk
/* bit mask F0WATTOVP */
#define ADCUI_F0MASK_F0WATTOVPM_Pos     (9U)
#define ADCUI_F0MASK_F0WATTOVPM_Msk     (0x1U << ADCUI_F0MASK_F0WATTOVPM_Pos)   /*!< 0x00000200 */
#define ADCUI_F0MASK_F0WATTOVPM         ADCUI_F0MASK_F0WATTOVPM_Msk
/* bit mask F0VAROVP */
#define ADCUI_F0MASK_F0VAROVPM_Pos      (10U)
#define ADCUI_F0MASK_F0VAROVPM_Msk      (0x1U << ADCUI_F0MASK_F0VAROVPM_Pos)    /*!< 0x00000400 */
#define ADCUI_F0MASK_F0VAROVPM          ADCUI_F0MASK_F0VAROVPM_Msk
/* bit mask F0VAOV */
#define ADCUI_F0MASK_F0VAOVM_Pos        (11U)
#define ADCUI_F0MASK_F0VAOVM_Msk        (0x1U << ADCUI_F0MASK_F0VAOVM_Pos)      /*!< 0x00000800 */
#define ADCUI_F0MASK_F0VAOVM            ADCUI_F0MASK_F0VAOVM_Msk
/* bit mask F0ZXTOFM */
#define ADCUI_F0MASK_F0ZXTOFM_Pos       (12U)
#define ADCUI_F0MASK_F0ZXTOFM_Msk       (0x1U << ADCUI_F0MASK_F0ZXTOFM_Pos)     /*!< 0x00001000 */
#define ADCUI_F0MASK_F0ZXTOFM           ADCUI_F0MASK_F0ZXTOFM_Msk
/* bit mask F0FAULTCON */
#define ADCUI_F0MASK_F0FAULTCONM_Pos    (14U)
#define ADCUI_F0MASK_F0FAULTCONM_Msk    (0x1U << ADCUI_F0MASK_F0FAULTCONM_Pos)  /*!< 0x00004000 */
#define ADCUI_F0MASK_F0FAULTCONM        ADCUI_F0MASK_F0FAULTCONM_Msk
/* bit mask F0APSIGN */
#define ADCUI_F0MASK_F0APSIGNM_Pos      (15U)
#define ADCUI_F0MASK_F0APSIGNM_Msk      (0x1U << ADCUI_F0MASK_F0APSIGNM_Pos)    /*!< 0x00008000 */
#define ADCUI_F0MASK_F0APSIGNM          ADCUI_F0MASK_F0APSIGNM_Msk
/* bit mask F0APNLDFL */
#define ADCUI_F0MASK_F0APNLDFLM_Pos     (16U)
#define ADCUI_F0MASK_F0APNLDFLM_Msk     (0x1U << ADCUI_F0MASK_F0APNLDFLM_Pos)   /*!< 0x00010000 */
#define ADCUI_F0MASK_F0APNLDFLM         ADCUI_F0MASK_F0APNLDFLM_Msk
/* bit mask F0VARSIGN */
#define ADCUI_F0MASK_F0VARSIGNM_Pos     (17U)
#define ADCUI_F0MASK_F0VARSIGNM_Msk     (0x1U << ADCUI_F0MASK_F0VARSIGNM_Pos)   /*!< 0x00020000 */
#define ADCUI_F0MASK_F0VARSIGNM         ADCUI_F0MASK_F0VARSIGNM_Msk
/* bit mask F0VARNLDFL */
#define ADCUI_F0MASK_F0VARNLDFLM_Pos    (18U)
#define ADCUI_F0MASK_F0VARNLDFLM_Msk    (0x1U << ADCUI_F0MASK_F0VARNLDFLM_Pos)  /*!< 0x00040000 */
#define ADCUI_F0MASK_F0VARNLDFLM        ADCUI_F0MASK_F0VARNLDFLM_Msk
/* bit mask F0VANLDFL */
#define ADCUI_F0MASK_F0VANLDFLM_Pos     (20U)
#define ADCUI_F0MASK_F0VANLDFLM_Msk     (0x1U << ADCUI_F0MASK_F0VANLDFLM_Pos)   /*!< 0x00100000 */
#define ADCUI_F0MASK_F0VANLDFLM         ADCUI_F0MASK_F0VANLDFLM_Msk
/* bit mask F0ZEROCRS */
#define ADCUI_F0MASK_F0ZEROCRSM_Pos     (21U)
#define ADCUI_F0MASK_F0ZEROCRSM_Msk     (0x1U << ADCUI_F0MASK_F0ZEROCRSM_Pos)   /*!< 0x00200000 */
#define ADCUI_F0MASK_F0ZEROCRSM         ADCUI_F0MASK_F0ZEROCRSM_Msk
/* bit mask C3IF_EMP */
#define ADCUI_F0MASK_C3IF_EMPM_Pos      (22U)
#define ADCUI_F0MASK_C3IF_EMPM_Msk      (0x1U << ADCUI_F0MASK_C3IF_EMPM_Pos)    /*!< 0x00400000 */
#define ADCUI_F0MASK_C3IF_EMPM          ADCUI_F0MASK_C3IF_EMPM_Msk
/* bit mask C3IF_FLL */
#define ADCUI_F0MASK_C3IF_FLLM_Pos      (23U)
#define ADCUI_F0MASK_C3IF_FLLM_Msk      (0x1U << ADCUI_F0MASK_C3IF_FLLM_Pos)    /*!< 0x00800000 */
#define ADCUI_F0MASK_C3IF_FLLM          ADCUI_F0MASK_C3IF_FLLM_Msk
/* bit mask C3IF_OVR */
#define ADCUI_F0MASK_C3IF_OVRM_Pos      (24U)
#define ADCUI_F0MASK_C3IF_OVRM_Msk      (0x1U << ADCUI_F0MASK_C3IF_OVRM_Pos)    /*!< 0x01000000 */
#define ADCUI_F0MASK_C3IF_OVRM          ADCUI_F0MASK_C3IF_OVRM_Msk
/* bit mask F0WATTOVN */
#define ADCUI_F0MASK_F0WATTOVNM_Pos     (25U)
#define ADCUI_F0MASK_F0WATTOVNM_Msk     (0x1U << ADCUI_F0MASK_F0WATTOVNM_Pos)   /*!< 0x02000000 */
#define ADCUI_F0MASK_F0WATTOVNM         ADCUI_F0MASK_F0WATTOVNM_Msk
/* bit mask F0VAROVNM */
#define ADCUI_F0MASK_F0VAROVNM_Pos      (26U)
#define ADCUI_F0MASK_F0VAROVNM_Msk      (0x1U << ADCUI_F0MASK_F0VAROVNM_Pos)    /*!< 0x04000000 */
#define ADCUI_F0MASK_F0VAROVNM          ADCUI_F0MASK_F0VAROVNM_Msk

/*******************  Bit definition for ADCUI_F1CTR register  ****************/
/* integration for I1 (0 - integration enabled, 1 - disabled) */
#define ADCUI_F1CTR_F1I0NTEN_Pos        (0U)
#define ADCUI_F1CTR_F1I0NTEN_Msk        (0x1U << ADCUI_F1CTR_F1I0NTEN_Pos)      /*!< 0x00000001 */
#define ADCUI_F1CTR_F1I0NTEN            ADCUI_F1CTR_F1I0NTEN_Msk
/* source for full energy (0 - full energy, 1 - current RMS) */
#define ADCUI_F1CTR_F1VASEL_Pos         (2U)
#define ADCUI_F1CTR_F1VASEL_Msk         (0x1U << ADCUI_F1CTR_F1VASEL_Pos)       /*!< 0x00000004 */
#define ADCUI_F1CTR_F1VASEL_FULLPOWER   (0x0U << ADCUI_F1CTR_F1VASEL_Pos)
#define ADCUI_F1CTR_F1VASEL_IRMS        (0x1U << ADCUI_F1CTR_F1VASEL_Pos)
/* reset active power register (write 1 to reset value) */
#define ADCUI_F1CTR_F1RARS_Pos          (3U)
#define ADCUI_F1CTR_F1RARS_Msk          (0x1U << ADCUI_F1CTR_F1RARS_Pos)        /*!< 0x00000008 */
#define ADCUI_F1CTR_F1RARS              ADCUI_F1CTR_F1RARS_Msk
/* reset reactive power register (write 1 to reset value) */
#define ADCUI_F1CTR_F1RRRS_Pos          (4U)
#define ADCUI_F1CTR_F1RRRS_Msk          (0x1U << ADCUI_F1CTR_F1RRRS_Pos)        /*!< 0x00000010 */
#define ADCUI_F1CTR_F1RRRS              ADCUI_F1CTR_F1RRRS_Msk
/* reset full power register (write 1 to reset value) */
#define ADCUI_F1CTR_F1RVRS_Pos          (5U)
#define ADCUI_F1CTR_F1RVRS_Msk          (0x1U << ADCUI_F1CTR_F1RVRS_Pos)        /*!< 0x00000020 */
#define ADCUI_F1CTR_F1RVRS              ADCUI_F1CTR_F1RVRS_Msk
/* gain for I1 */
#define ADCUI_F1CTR_F1I1GAIN_Pos        (6U)
#define ADCUI_F1CTR_F1I1GAIN_Msk        (0x3U << ADCUI_F1CTR_F1I1GAIN_Pos)      /*!< 0x000000C0 */
/* gain for V0 */
#define ADCUI_F1CTR_F1VGAIN_Pos         (8U)
#define ADCUI_F1CTR_F1VGAIN_Msk         (0x3U << ADCUI_F1CTR_F1VGAIN_Pos)       /*!< 0x00000300 */
/* phase shift between voltage and current (-126 (-123us) ... +127 (+124us)) */
#define ADCUI_F1CTR_F1VPHASE_Pos        (10U)
#define ADCUI_F1CTR_F1VPHASE_Msk        (0xFFU << ADCUI_F1CTR_F1VPHASE_Pos)      /*!< 0x003FC00 */
/* calibration for I RMS */
#define ADCUI_F1CTR_F1IRMSOS_Pos        (20U)
#define ADCUI_F1CTR_F1IRMSOS_Msk        (0xFFFU << ADCUI_F1CTR_F1IRMSOS_Pos)    /*!< 0xFFF00000 */

/*******************  Bit definition for ADCUI_F1WC register  *****************/
/* calibration offset for active power */
#define ADCUI_F1WC_F1WATTOS_Pos         (0U)
#define ADCUI_F1WC_F1WATTOS_Msk         (0xFFFFU << ADCUI_F1WC_F1WATTOS_Pos)    /*!< 0x0000FFFF */
/* calibration gain for active power */
#define ADCUI_F1WC_F1WGAIN_Pos          (16U)
#define ADCUI_F1WC_F1WGAIN_Msk          (0xFFFU << ADCUI_F1WC_F1WGAIN_Pos)      /*!< 0x0FFF0000 */

/*******************  Bit definition for ADCUI_F1VC register  *****************/
/* calibration offset for reactive power */
#define ADCUI_F1VC_F1VAROS_Pos          (0U)
#define ADCUI_F1VC_F1VAROS_Msk          (0xFFFFU << ADCUI_F1VC_F1VAROS_Pos)     /*!< 0x0000FFFF */
/* calibration gain for reactive power */
#define ADCUI_F1VC_F1VARGAIN_Pos        (16U)
#define ADCUI_F1VC_F1VARGAIN_Msk        (0xFFFU << ADCUI_F1VC_F1VARGAIN_Pos)    /*!< 0x0FFF0000 */

/*******************  Bit definition for ADCUI_F1AC register  *****************/
/* voltage RMS calibration */
#define ADCUI_F1AC_F1VRMSOS_Pos         (0U)
#define ADCUI_F1AC_F1VRMSOS_Msk         (0xFFFU << ADCUI_F1AC_F1VRMSOS_Pos)     /*!< 0x00000FFF */
/* voltage gain calibration */
#define ADCUI_F1AC_F1VAGAIN_Pos         (16U)
#define ADCUI_F1AC_F1VAGAIN_Msk         (0xFFFU << ADCUI_F1AC_F1VAGAIN_Pos)     /*!< 0x0FFF0000 */

/*******************  Bit definition for ADCUI_F1MD0 register  ****************/
/* source for ADCUI_F1VDAT (0b00 - voltage, 0b01 - active power, 0b10 - reactive power, 0b11 - full power) */
#define ADCUI_F1MD0_F1VSEL_Pos          (0U)
#define ADCUI_F1MD0_F1VSEL_Msk          (0x3U << ADCUI_F1MD0_F1VSEL_Pos)        /*!< 0x00000003 */
/* source for ADCUI_F1IDAT (0b00 - current, 0b01 - active power, 0b10 - reactive power, 0b11 - full power) */
#define ADCUI_F1MD0_F1ISEL_Pos          (2U)
#define ADCUI_F1MD0_F1ISEL_Msk          (0x3U << ADCUI_F1MD0_F1ISEL_Pos)        /*!< 0x0000000C */
/* active power polarity at last time (0 - positive, 1 - negative) */
#define ADCUI_F1MD0_F1ACTS_Pos          (4U)
#define ADCUI_F1MD0_F1ACTS_Msk          (0x1U << ADCUI_F1MD0_F1ACTS_Pos)        /*!< 0x00000010 */
#define ADCUI_F1MD0_F1ACTS_POSITIVE     (0x0U << ADCUI_F1MD0_F1ACTS_Pos)
#define ADCUI_F1MD0_F1ACTS_NEGATIVE     (0x1U << ADCUI_F1MD0_F1ACTS_Pos)
/* reactive power polarity at last time (0 - positive, 1 - negative) */
#define ADCUI_F1MD0_F1REACTS_Pos        (5U)
#define ADCUI_F1MD0_F1REACTS_Msk        (0x1U << ADCUI_F1MD0_F1REACTS_Pos)      /*!< 0x00000020 */
#define ADCUI_F1MD0_F1REACTS_POSITIVE   (0x0U << ADCUI_F1MD0_F1REACTS_Pos)
#define ADCUI_F1MD0_F1REACTS_NEGATIVE   (0x1U << ADCUI_F1MD0_F1REACTS_Pos)
/* I1 gain (0 - 0dB, 1 - +6dB), use ADCUI_GAIN */
#define ADCUI_F1MD0_I1GAIN_Pos          (6U)
#define ADCUI_F1MD0_I1GAIN_Msk          (0x1U << ADCUI_F1MD0_I1GAIN_Pos)        /*!< 0x00000040 */
/* V1 gain (0 - 0dB, 1 - +6dB) */
#define ADCUI_F1MD0_V1GAIN_Pos          (7U)
#define ADCUI_F1MD0_V1GAIN_Msk          (0x1U << ADCUI_F1MD0_V1GAIN_Pos)        /*!< 0x00000080 */
/* period frequency (period duriation) */
#define ADCUI_F1MD0_F1PER_FREQ_Pos      (8U)
#define ADCUI_F1MD0_F1PER_FREQ_Msk      (0x1FFFFFU << ADCUI_F1MD0_F1PER_FREQ_Pos) /*!< 0x1FFFFF00 */

/*******************  Bit definition for ADCUI_F1MD1 register  ****************/
/* maximum permitted current */
#define ADCUI_F1MD1_F1IPKLVL_Pos        (0U)
#define ADCUI_F1MD1_F1IPKLVL_Msk        (0xFFFFU << ADCUI_F1MD1_F1IPKLVL_Pos)   /*!< 0x0000FFFF */
/* maximum permitted voltage */
#define ADCUI_F1MD1_F1VPKLVL_Pos        (16U)
#define ADCUI_F1MD1_F1VPKLVL_Msk        (0xFFFFU << ADCUI_F1MD1_F1VPKLVL_Pos)   /*!< 0xFFFF0000 */

/*******************  Bit definition for ADCUI_F1STAT register  ***************/
/* FIFO F1VDAT empty */
#define ADCUI_F1STAT_F1VF_EMP_Pos       (0U)
#define ADCUI_F1STAT_F1VF_EMP_Msk       (0x1U << ADCUI_F1STAT_F1VF_EMP_Pos)     /*!< 0x00000001 */
#define ADCUI_F1STAT_F1VF_EMP           ADCUI_F1STAT_F1VF_EMP_Msk
/* FIFO F1VDAT full */
#define ADCUI_F1STAT_F1VF_FLL_Pos       (1U)
#define ADCUI_F1STAT_F1VF_FLL_Msk       (0x1U << ADCUI_F1STAT_F1VF_FLL_Pos)     /*!< 0x00000002 */
#define ADCUI_F1STAT_F1VF_FLL           ADCUI_F1STAT_F1VF_FLL_Msk
/* FIFO F1VDAT overflow */
#define ADCUI_F1STAT_F1VF_OVR_Pos       (2U)
#define ADCUI_F1STAT_F1VF_OVR_Msk       (0x1U << ADCUI_F1STAT_F1VF_OVR_Pos)     /*!< 0x00000004 */
#define ADCUI_F1STAT_F1VF_OVR           ADCUI_F1STAT_F1VF_OVR_Msk
/* FIFO F1IDAT empty */
#define ADCUI_F1STAT_F1IF_EMP_Pos       (3U)
#define ADCUI_F1STAT_F1IF_EMP_Msk       (0x1U << ADCUI_F1STAT_F1IF_EMP_Pos)     /*!< 0x00000008 */
#define ADCUI_F1STAT_F1IF_EMP           ADCUI_F1STAT_F1IF_EMP_Msk
/* FIFO F1IDAT full */
#define ADCUI_F1STAT_F1IF_FLL_Pos       (4U)
#define ADCUI_F1STAT_F1IF_FLL_Msk       (0x1U << ADCUI_F1STAT_F1IF_FLL_Pos)     /*!< 0x00000010 */
#define ADCUI_F1STAT_F1IF_FLL           ADCUI_F1STAT_F1IF_FLL_Msk
/* FIFO F1IDAT overflow */
#define ADCUI_F1STAT_F1IF_OVR_Pos       (5U)
#define ADCUI_F1STAT_F1IF_OVR_Msk       (0x1U << ADCUI_F1STAT_F1IF_OVR_Pos)     /*!< 0x00000020 */
#define ADCUI_F1STAT_F1IF_OVR           ADCUI_F1STAT_F1IF_OVR_Msk
/* voltage drop detected */
#define ADCUI_F1STAT_F1SAGF_Pos         (6U)
#define ADCUI_F1STAT_F1SAGF_Msk         (0x1U << ADCUI_F1STAT_F1SAGF_Pos)       /*!< 0x00000040 */
#define ADCUI_F1STAT_F1SAGF             ADCUI_F1STAT_F1SAGF_Msk
/* overvoltage detected */
#define ADCUI_F1STAT_F1PEAKVF_Pos       (7U)
#define ADCUI_F1STAT_F1PEAKVF_Msk       (0x1U << ADCUI_F1STAT_F1PEAKVF_Pos)     /*!< 0x00000080 */
#define ADCUI_F1STAT_F1PEAKVF           ADCUI_F1STAT_F1PEAKVF_Msk
/* overcurrnet detected */
#define ADCUI_F1STAT_F1PEAKIF_Pos       (8U)
#define ADCUI_F1STAT_F1PEAKIF_Msk       (0x1U << ADCUI_F1STAT_F1PEAKIF_Pos)     /*!< 0000000100 */
#define ADCUI_F1STAT_F1PEAKIF           ADCUI_F1STAT_F1PEAKIF_Msk
/* positive active power overflow */
#define ADCUI_F1STAT_F1WATTOVP_Pos      (9U)
#define ADCUI_F1STAT_F1WATTOVP_Msk      (0x1U << ADCUI_F1STAT_F1WATTOVP_Pos)    /*!< 0x00000200 */
#define ADCUI_F1STAT_F1WATTOVP          ADCUI_F1STAT_F1WATTOVP_Msk
/* positive reactive power overflow */
#define ADCUI_F1STAT_F1VAROVP_Pos       (10U)
#define ADCUI_F1STAT_F1VAROVP_Msk       (0x1U << ADCUI_F1STAT_F1VAROVP_Pos)     /*!< 0x00000400 */
#define ADCUI_F1STAT_F1VAROVP           ADCUI_F1STAT_F1VAROVP_Msk
/* full power overflow */
#define ADCUI_F1STAT_F1VAOV_Pos         (11U)
#define ADCUI_F1STAT_F1VAOV_Msk         (0x1U << ADCUI_F1STAT_F1VAOV_Pos)       /*!< 0000000800 */
#define ADCUI_F1STAT_F1VAOV             ADCUI_F1STAT_F1VAOV_Msk
/* no voltage timeout */
#define ADCUI_F1STAT_F1ZXTOF_Pos        (12U)
#define ADCUI_F1STAT_F1ZXTOF_Msk        (0x1U << ADCUI_F1STAT_F1ZXTOF_Pos)      /*!< 0x00001000 */
#define ADCUI_F1STAT_F1ZXTOF            ADCUI_F1STAT_F1ZXTOF_Msk
/* active power direction change (write 1 to drop this flag) */
#define ADCUI_F1STAT_F1APSIGN_Pos       (15U)
#define ADCUI_F1STAT_F1APSIGN_Msk       (0x1U << ADCUI_F1STAT_F1APSIGN_Pos)     /*!< 0x00008000 */
#define ADCUI_F1STAT_F1APSIGN           ADCUI_F1STAT_F1APSIGN_Msk
/* active power is under threshold */
#define ADCUI_F1STAT_F1APNLDFL_Pos      (16U)
#define ADCUI_F1STAT_F1APNLDFL_Msk      (0x1U << ADCUI_F1STAT_F1APNLDFL_Pos)    /*!< 0x00010000 */
#define ADCUI_F1STAT_F1APNLDFL          ADCUI_F1STAT_F1APNLDFL_Msk
/* reactive power direction change (write 1 to drop this flag) */
#define ADCUI_F1STAT_F1VARSIGN_Pos      (17U)
#define ADCUI_F1STAT_F1VARSIGN_Msk      (0x1U << ADCUI_F1STAT_F1VARSIGN_Pos)    /*!< 0x00020000 */
#define ADCUI_F1STAT_F1VARSIGN          ADCUI_F1STAT_F1VARSIGN_Msk
/* reactive power is under threshold */
#define ADCUI_F1STAT_F1VARNLDFL_Pos     (18U)
#define ADCUI_F1STAT_F1VARNLDFL_Msk     (0x1U <ADCUI_F1STAT_F1VARNLDFL_Pos)     /*!< 0x00040000 */
#define ADCUI_F1STAT_F1VARNLDFL         ADCUI_F1STAT_F1VARNLDFL_Msk
/* full power is under threshold */
#define ADCUI_F1STAT_F1ANLDFL_Pos       (20U)
#define ADCUI_F1STAT_F1ANLDFL_Msk       (0x1U << ADCUI_F1STAT_F1ANLDFL_Pos)     /*!< 0x00100000 */
#define ADCUI_F1STAT_F1ANLDFL           ADCUI_F1STAT_F1ANLDFL_Msk
/* zero-cross detected (write 1 to drop this flag) */
#define ADCUI_F1STAT_F1ZEROCRS_Pos      (21U)
#define ADCUI_F1STAT_F1ZEROCRS_Msk      (0x1U << ADCUI_F1STAT_F1ZEROCRS_Pos)    /*!< 0x00200000 */
#define ADCUI_F1STAT_F1ZEROCRS          ADCUI_F1STAT_F1ZEROCRS_Msk
/* negative active power overflow (write 1 to drop this flag) */
#define ADCUI_F1STAT_F1WATTOVN_Pos      (25U)
#define ADCUI_F1STAT_F1WATTOVN_Msk      (0x1U << ADCUI_F1STAT_F1WATTOVN_Pos)    /*!< 0x02000000 */
#define ADCUI_F1STAT_F1WATTOVN          ADCUI_F1STAT_F1WATTOVN_Msk
/* negative reactive power overflow (write 1 to drop this flag) */
#define ADCUI_F1STAT_F1VAROVN_Pos       (26U)
#define ADCUI_F1STAT_F1VAROVN_Msk       (0x1U << ADCUI_F1STAT_F1VAROVN_Pos)     /*!< 0x04000000 */
#define ADCUI_F1STAT_F1VAROVN           ADCUI_F1STAT_F1VAROVN_Msk

/*******************  Bit definition for ADCUI_F1MASK register  ***************/
/* bit mask F1VF_EMP */
#define ADCUI_F1MASK_F1VF_EMPM_Pos      (0U)
#define ADCUI_F1MASK_F1VF_EMPM_Msk      (0x1U << ADCUI_F1MASK_F1VF_EMPM_Pos)    /*!< 0x00000001 */
#define ADCUI_F1MASK_F1VF_EMPM          ADCUI_F1MASK_F1VF_EMPM_Msk
/* bit mask F1VF_FLL */
#define ADCUI_F1MASK_F1VF_FLLM_Pos      (1U)
#define ADCUI_F1MASK_F1VF_FLLM_Msk      (0x1U << ADCUI_F1MASK_F1VF_FLLM_Pos)    /*!< 0x00000002 */
#define ADCUI_F1MASK_F1VF_FLLM          ADCUI_F1MASK_F1VF_FLLM_Msk
/* bit mask F1VF_OVR */
#define ADCUI_F1MASK_F1VF_OVRM_Pos      (2U)
#define ADCUI_F1MASK_F1VF_OVRM_Msk      (0x1U << ADCUI_F1MASK_F1VF_OVRM_Pos)    /*!< 0x00000004 */
#define ADCUI_F1MASK_F1VF_OVRM          ADCUI_F1MASK_F1VF_OVRM_Msk
/* bit mask F1IF_EMP */
#define ADCUI_F1MASK_F1IF_EMPM_Pos      (3U)
#define ADCUI_F1MASK_F1IF_EMPM_Msk      (0x1U << ADCUI_F1MASK_F1IF_EMPM_Pos)    /*!< 0x00000008 */
#define ADCUI_F1MASK_F1IF_EMPM          ADCUI_F1MASK_F1IF_EMPM_Msk
/* bit mask F1IF_FLL */
#define ADCUI_F1MASK_F1IF_FLLM_Pos      (4U)
#define ADCUI_F1MASK_F1IF_FLLM_Msk      (0x1U << ADCUI_F1MASK_F1IF_FLLM_Pos)    /*!< 0x00000010 */
#define ADCUI_F1MASK_F1IF_FLLM          ADCUI_F1MASK_F1IF_FLLM_Msk
/* bit mask F1IF_OVR */
#define ADCUI_F1MASK_F1IF_OVRM_Pos      (5U)
#define ADCUI_F1MASK_F1IF_OVRM_Msk      (0x1U << ADCUI_F1MASK_F1IF_OVRM_Pos)    /*!< 0x00000020 */
#define ADCUI_F1MASK_F1IF_OVRM          ADCUI_F1MASK_F1IF_OVRM_Msk
/* bit mask F1SAGF */
#define ADCUI_F1MASK_F1SAGFM_Pos        (6U)
#define ADCUI_F1MASK_F1SAGFM_Msk        (0x1U << ADCUI_F1MASK_F1SAGFM_Pos)      /*!< 0x00000040 */
#define ADCUI_F1MASK_F1SAGFM            ADCUI_F1MASK_F1SAGFM_Msk
/* bit mask F1PEAKVF */
#define ADCUI_F1MASK_F1PEAKVFM_Pos      (7U)
#define ADCUI_F1MASK_F1PEAKVFM_Msk      (0x1U << ADCUI_F1MASK_F1PEAKVFM_Pos)    /*!< 0x00000080 */
#define ADCUI_F1MASK_F1PEAKVFM          ADCUI_F1MASK_F1PEAKVFM_Msk
/* bit mask F1PEAKIF */
#define ADCUI_F1MASK_F1PEAKIFM_Pos      (8U)
#define ADCUI_F1MASK_F1PEAKIFM_Msk      (0x1U << ADCUI_F1MASK_F1PEAKIFM_Pos)    /*!< 0x00000100 */
#define ADCUI_F1MASK_F1PEAKIFM          ADCUI_F1MASK_F1PEAKIFM_Msk
/* bit mask F1WATTOVP */
#define ADCUI_F1MASK_F1WATTOVPM_Pos     (9U)
#define ADCUI_F1MASK_F1WATTOVPM_Msk     (0x1U << ADCUI_F1MASK_F1WATTOVPM_Pos)   /*!< 0x00000200 */
#define ADCUI_F1MASK_F1WATTOVPM         ADCUI_F1MASK_F1WATTOVPM_Msk
/* bit mask F1VAROVP */
#define ADCUI_F1MASK_F1VAROVPM_Pos      (10U)
#define ADCUI_F1MASK_F1VAROVPM_Msk      (0x1U << ADCUI_F1MASK_F1VAROVPM_Pos)    /*!< 0x00000400 */
#define ADCUI_F1MASK_F1VAROVPM          ADCUI_F1MASK_F1VAROVPM_Msk
/* bit mask F1VAOV */
#define ADCUI_F1MASK_F1VAOVM_Pos        (11U)
#define ADCUI_F1MASK_F1VAOVM_Msk        (0x1U << ADCUI_F1MASK_F1VAOVM_Pos)      /*!< 0x00000800 */
#define ADCUI_F1MASK_F1VAOVM            ADCUI_F1MASK_F1VAOVM_Msk
/* bit mask F1ZXTOFM */
#define ADCUI_F1MASK_F1ZXTOFM_Pos       (12U)
#define ADCUI_F1MASK_F1ZXTOFM_Msk       (0x1U << ADCUI_F1MASK_F1ZXTOFM_Pos)     /*!< 0x00001000 */
#define ADCUI_F1MASK_F1ZXTOFM           ADCUI_F1MASK_F1ZXTOFM_Msk
/* bit mask F1APSIGN */
#define ADCUI_F1MASK_F1APSIGNM_Pos      (15U)
#define ADCUI_F1MASK_F1APSIGNM_Msk      (0x1U << ADCUI_F1MASK_F1APSIGNM_Pos)    /*!< 0x00008000 */
#define ADCUI_F1MASK_F1APSIGNM          ADCUI_F1MASK_F1APSIGNM_Msk
/* bit mask F1APNLDFL */
#define ADCUI_F1MASK_F1APNLDFLM_Pos     (16U)
#define ADCUI_F1MASK_F1APNLDFLM_Msk     (0x1U << ADCUI_F1MASK_F1APNLDFLM_Pos)   /*!< 0x00010000 */
#define ADCUI_F1MASK_F1APNLDFLM         ADCUI_F1MASK_F1APNLDFLM_Msk
/* bit mask F1VARSIGN */
#define ADCUI_F1MASK_F1VARSIGNM_Pos     (17U)
#define ADCUI_F1MASK_F1VARSIGNM_Msk     (0x1U << ADCUI_F1MASK_F1VARSIGNM_Pos)   /*!< 0x00020000 */
#define ADCUI_F1MASK_F1VARSIGNM         ADCUI_F1MASK_F1VARSIGNM_Msk
/* bit mask F1VARNLDFL */
#define ADCUI_F1MASK_F1VARNLDFLM_Pos    (18U)
#define ADCUI_F1MASK_F1VARNLDFLM_Msk    (0x1U << ADCUI_F1MASK_F1VARNLDFLM_Pos)  /*!< 0x00040000 */
#define ADCUI_F1MASK_F1VARNLDFLM        ADCUI_F1MASK_F1VARNLDFLM_Msk
/* bit mask F1VANLDFL */
#define ADCUI_F1MASK_F1VANLDFLM_Pos     (20U)
#define ADCUI_F1MASK_F1VANLDFLM_Msk     (0x1U << ADCUI_F1MASK_F1VANLDFLM_Pos)   /*!< 0x00100000 */
#define ADCUI_F1MASK_F1VANLDFLM         ADCUI_F1MASK_F1VANLDFLM_Msk
/* bit mask F1ZEROCRS */
#define ADCUI_F1MASK_F1ZEROCRSM_Pos     (21U)
#define ADCUI_F1MASK_F1ZEROCRSM_Msk     (0x1U << ADCUI_F1MASK_F1ZEROCRSM_Pos)   /*!< 0x00200000 */
#define ADCUI_F1MASK_F1ZEROCRSM         ADCUI_F1MASK_F1ZEROCRSM_Msk
/* bit mask F1WATTOVN */
#define ADCUI_F1MASK_F1WATTOVNM_Pos     (25U)
#define ADCUI_F1MASK_F1WATTOVNM_Msk     (0x1U << ADCUI_F1MASK_F1WATTOVNM_Pos)   /*!< 0x02000000 */
#define ADCUI_F1MASK_F1WATTOVNM         ADCUI_F1MASK_F1WATTOVNM_Msk
/* bit mask F1VAROVNM */
#define ADCUI_F1MASK_F1VAROVNM_Pos      (26U)
#define ADCUI_F1MASK_F1VAROVNM_Msk      (0x1U << ADCUI_F1MASK_F1VAROVNM_Pos)    /*!< 0x04000000 */
#define ADCUI_F1MASK_F1VAROVNM          ADCUI_F1MASK_F1VAROVNM_Msk

/*******************  Bit definition for ADCUI_F2CTR register  ****************/
/* integration for I1 (0 - integration enabled, 1 - disabled) */
#define ADCUI_F2CTR_F2I0NTEN_Pos        (0U)
#define ADCUI_F2CTR_F2I0NTEN_Msk        (0x1U << ADCUI_F2CTR_F2I0NTEN_Pos)      /*!< 0x00000001 */
#define ADCUI_F2CTR_F2I0NTEN            ADCUI_F2CTR_F2I0NTEN_Msk
/* source for full energy (0 - full energy, 1 - current RMS) */
#define ADCUI_F2CTR_F2VASEL_Pos         (2U)
#define ADCUI_F2CTR_F2VASEL_Msk         (0x1U << ADCUI_F2CTR_F2VASEL_Pos)       /*!< 0x00000004 */
#define ADCUI_F2CTR_F2VASEL_FULLPOWER   (0x0U << ADCUI_F2CTR_F2VASEL_Pos)
#define ADCUI_F2CTR_F2VASEL_IRMS        (0x1U << ADCUI_F2CTR_F2VASEL_Pos)
/* reset active power register (write 1 to reset value) */
#define ADCUI_F2CTR_F2RARS_Pos          (3U)
#define ADCUI_F2CTR_F2RARS_Msk          (0x1U << ADCUI_F2CTR_F2RARS_Pos)        /*!< 0x00000008 */
#define ADCUI_F2CTR_F2RARS              ADCUI_F2CTR_F2RARS_Msk
/* reset reactive power register (write 1 to reset value) */
#define ADCUI_F2CTR_F2RRRS_Pos          (4U)
#define ADCUI_F2CTR_F2RRRS_Msk          (0x1U << ADCUI_F2CTR_F2RRRS_Pos)        /*!< 0x00000010 */
#define ADCUI_F2CTR_F2RRRS              ADCUI_F2CTR_F2RRRS_Msk
/* reset full power register (write 1 to reset value) */
#define ADCUI_F2CTR_F2RVRS_Pos          (5U)
#define ADCUI_F2CTR_F2RVRS_Msk          (0x1U << ADCUI_F2CTR_F2RVRS_Pos)        /*!< 0x00000020 */
#define ADCUI_F2CTR_F2RVRS              ADCUI_F2CTR_F2RVRS_Msk
/* gain for I1 */
#define ADCUI_F2CTR_F2I1GAIN_Pos        (6U)
#define ADCUI_F2CTR_F2I1GAIN_Msk        (0x3U << ADCUI_F2CTR_F2I1GAIN_Pos)      /*!< 0x000000C0 */
/* gain for V0 */
#define ADCUI_F2CTR_F2VGAIN_Pos         (8U)
#define ADCUI_F2CTR_F2VGAIN_Msk         (0x3U << ADCUI_F2CTR_F2VGAIN_Pos)       /*!< 0x00000300 */
/* phase shift between voltage and current (-126 (-123us) ... +127 (+124us)) */
#define ADCUI_F2CTR_F2VPHASE_Pos        (10U)
#define ADCUI_F2CTR_F2VPHASE_Msk        (0xFFU << ADCUI_F2CTR_F2VPHASE_Pos)      /*!< 0x003FC00 */
/* calibration for I RMS */
#define ADCUI_F2CTR_F2IRMSOS_Pos        (20U)
#define ADCUI_F2CTR_F2IRMSOS_Msk        (0xFFFU << ADCUI_F2CTR_F2IRMSOS_Pos)    /*!< 0xFFF00000 */

/*******************  Bit definition for ADCUI_F2WC register  *****************/
/* calibration offset for active power */
#define ADCUI_F2WC_F2WATTOS_Pos         (0U)
#define ADCUI_F2WC_F2WATTOS_Msk         (0xFFFFU << ADCUI_F2WC_F2WATTOS_Pos)    /*!< 0x0000FFFF */
/* calibration gain for active power */
#define ADCUI_F2WC_F2WGAIN_Pos          (16U)
#define ADCUI_F2WC_F2WGAIN_Msk          (0xFFFU << ADCUI_F2WC_F2WGAIN_Pos)      /*!< 0x0FFF0000 */

/*******************  Bit definition for ADCUI_F2VC register  *****************/
/* calibration offset for reactive power */
#define ADCUI_F2VC_F2VAROS_Pos          (0U)
#define ADCUI_F2VC_F2VAROS_Msk          (0xFFFFU << ADCUI_F2VC_F2VAROS_Pos)     /*!< 0x0000FFFF */
/* calibration gain for reactive power */
#define ADCUI_F2VC_F2VARGAIN_Pos        (16U)
#define ADCUI_F2VC_F2VARGAIN_Msk        (0xFFFU << ADCUI_F2VC_F2VARGAIN_Pos)    /*!< 0x0FFF0000 */

/*******************  Bit definition for ADCUI_F2AC register  *****************/
/* voltage RMS calibration */
#define ADCUI_F2AC_F2VRMSOS_Pos         (0U)
#define ADCUI_F2AC_F2VRMSOS_Msk         (0xFFFU << ADCUI_F2AC_F2VRMSOS_Pos)     /*!< 0x00000FFF */
/* voltage gain calibration */
#define ADCUI_F2AC_F2VAGAIN_Pos         (16U)
#define ADCUI_F2AC_F2VAGAIN_Msk         (0xFFFU << ADCUI_F2AC_F2VAGAIN_Pos)     /*!< 0x0FFF0000 */

/*******************  Bit definition for ADCUI_F2MD0 register  ****************/
/* source for ADCUI_F2VDAT (0b00 - voltage, 0b01 - active power, 0b10 - reactive power, 0b11 - full power) */
#define ADCUI_F2MD0_F2VSEL_Pos          (0U)
#define ADCUI_F2MD0_F2VSEL_Msk          (0x3U << ADCUI_F2MD0_F2VSEL_Pos)        /*!< 0x00000003 */
/* source for ADCUI_F2IDAT (0b00 - current, 0b01 - active power, 0b10 - reactive power, 0b11 - full power) */
#define ADCUI_F2MD0_F2ISEL_Pos          (2U)
#define ADCUI_F2MD0_F2ISEL_Msk          (0x3U << ADCUI_F2MD0_F2ISEL_Pos)        /*!< 0x0000000C */
/* active power polarity at last time (0 - positive, 1 - negative) */
#define ADCUI_F2MD0_F2ACTS_Pos          (4U)
#define ADCUI_F2MD0_F2ACTS_Msk          (0x1U << ADCUI_F2MD0_F2ACTS_Pos)        /*!< 0x00000010 */
#define ADCUI_F2MD0_F2ACTS_POSITIVE     (0x0U << ADCUI_F2MD0_F2ACTS_Pos)
#define ADCUI_F2MD0_F2ACTS_NEGATIVE     (0x1U << ADCUI_F2MD0_F2ACTS_Pos)
/* reactive power polarity at last time (0 - positive, 1 - negative) */
#define ADCUI_F2MD0_F2REACTS_Pos        (5U)
#define ADCUI_F2MD0_F2REACTS_Msk        (0x1U << ADCUI_F2MD0_F2REACTS_Pos)      /*!< 0x00000020 */
#define ADCUI_F2MD0_F2REACTS_POSITIVE   (0x0U << ADCUI_F2MD0_F2REACTS_Pos)
#define ADCUI_F2MD0_F2REACTS_NEGATIVE   (0x1U << ADCUI_F2MD0_F2REACTS_Pos)
/* I1 gain (0 - 0dB, 1 - +6dB), use ADCUI_GAIN */
#define ADCUI_F2MD0_I1GAIN_Pos          (6U)
#define ADCUI_F2MD0_I1GAIN_Msk          (0x1U << ADCUI_F2MD0_I1GAIN_Pos)        /*!< 0x00000040 */
/* V1 gain (0 - 0dB, 1 - +6dB), use ADCUI_GAIN */
#define ADCUI_F2MD0_V1GAIN_Pos          (7U)
#define ADCUI_F2MD0_V1GAIN_Msk          (0x1U << ADCUI_F2MD0_V1GAIN_Pos)        /*!< 0x00000080 */
/* period frequency (period duriation) */
#define ADCUI_F2MD0_F2PER_FREQ_Pos      (8U)
#define ADCUI_F2MD0_F2PER_FREQ_Msk      (0x1FFFFFU << ADCUI_F2MD0_F2PER_FREQ_Pos) /*!< 0x1FFFFF00 */

/*******************  Bit definition for ADCUI_F2MD1 register  ****************/
/* maximum permitted current */
#define ADCUI_F2MD1_F2IPKLVL_Pos        (0U)
#define ADCUI_F2MD1_F2IPKLVL_Msk        (0xFFFFU << ADCUI_F2MD1_F2IPKLVL_Pos)   /*!< 0x0000FFFF */
/* maximum permitted voltage */
#define ADCUI_F2MD1_F2VPKLVL_Pos        (16U)
#define ADCUI_F2MD1_F2VPKLVL_Msk        (0xFFFFU << ADCUI_F2MD1_F2VPKLVL_Pos)   /*!< 0xFFFF0000 */

/*******************  Bit definition for ADCUI_F2STAT register  ***************/
/* FIFO F2VDAT empty */
#define ADCUI_F2STAT_F2VF_EMP_Pos       (0U)
#define ADCUI_F2STAT_F2VF_EMP_Msk       (0x1U << ADCUI_F2STAT_F2VF_EMP_Pos)     /*!< 0x00000001 */
#define ADCUI_F2STAT_F2VF_EMP           ADCUI_F2STAT_F2VF_EMP_Msk
/* FIFO F2VDAT full */
#define ADCUI_F2STAT_F2VF_FLL_Pos       (1U)
#define ADCUI_F2STAT_F2VF_FLL_Msk       (0x1U << ADCUI_F2STAT_F2VF_FLL_Pos)     /*!< 0x00000002 */
#define ADCUI_F2STAT_F2VF_FLL           ADCUI_F2STAT_F2VF_FLL_Msk
/* FIFO F2VDAT overflow */
#define ADCUI_F2STAT_F2VF_OVR_Pos       (2U)
#define ADCUI_F2STAT_F2VF_OVR_Msk       (0x1U << ADCUI_F2STAT_F2VF_OVR_Pos)     /*!< 0x00000004 */
#define ADCUI_F2STAT_F2VF_OVR           ADCUI_F2STAT_F2VF_OVR_Msk
/* FIFO F2IDAT empty */
#define ADCUI_F2STAT_F2IF_EMP_Pos       (3U)
#define ADCUI_F2STAT_F2IF_EMP_Msk       (0x1U << ADCUI_F2STAT_F2IF_EMP_Pos)     /*!< 0x00000008 */
#define ADCUI_F2STAT_F2IF_EMP           ADCUI_F2STAT_F2IF_EMP_Msk
/* FIFO F2IDAT full */
#define ADCUI_F2STAT_F2IF_FLL_Pos       (4U)
#define ADCUI_F2STAT_F2IF_FLL_Msk       (0x1U << ADCUI_F2STAT_F2IF_FLL_Pos)     /*!< 0x00000010 */
#define ADCUI_F2STAT_F2IF_FLL           ADCUI_F2STAT_F2IF_FLL_Msk
/* FIFO F2IDAT overflow */
#define ADCUI_F2STAT_F2IF_OVR_Pos       (5U)
#define ADCUI_F2STAT_F2IF_OVR_Msk       (0x1U << ADCUI_F2STAT_F2IF_OVR_Pos)     /*!< 0x00000020 */
#define ADCUI_F2STAT_F2IF_OVR           ADCUI_F2STAT_F2IF_OVR_Msk
/* voltage drop detected */
#define ADCUI_F2STAT_F2SAGF_Pos         (6U)
#define ADCUI_F2STAT_F2SAGF_Msk         (0x1U << ADCUI_F2STAT_F2SAGF_Pos)       /*!< 0x00000040 */
#define ADCUI_F2STAT_F2SAGF             ADCUI_F2STAT_F2SAGF_Msk
/* overvoltage detected */
#define ADCUI_F2STAT_F2PEAKVF_Pos       (7U)
#define ADCUI_F2STAT_F2PEAKVF_Msk       (0x1U << ADCUI_F2STAT_F2PEAKVF_Pos)     /*!< 0x00000080 */
#define ADCUI_F2STAT_F2PEAKVF           ADCUI_F2STAT_F2PEAKVF_Msk
/* overcurrnet detected */
#define ADCUI_F2STAT_F2PEAKIF_Pos       (8U)
#define ADCUI_F2STAT_F2PEAKIF_Msk       (0x1U << ADCUI_F2STAT_F2PEAKIF_Pos)     /*!< 0000000100 */
#define ADCUI_F2STAT_F2PEAKIF           ADCUI_F2STAT_F2PEAKIF_Msk
/* positive active power overflow */
#define ADCUI_F2STAT_F2WATTOVP_Pos      (9U)
#define ADCUI_F2STAT_F2WATTOVP_Msk      (0x1U << ADCUI_F2STAT_F2WATTOVP_Pos)    /*!< 0x00000200 */
#define ADCUI_F2STAT_F2WATTOVP          ADCUI_F2STAT_F2WATTOVP_Msk
/* positive reactive power overflow */
#define ADCUI_F2STAT_F2VAROVP_Pos       (10U)
#define ADCUI_F2STAT_F2VAROVP_Msk       (0x1U << ADCUI_F2STAT_F2VAROVP_Pos)     /*!< 0x00000400 */
#define ADCUI_F2STAT_F2VAROVP           ADCUI_F2STAT_F2VAROVP_Msk
/* full power overflow */
#define ADCUI_F2STAT_F2VAOV_Pos         (11U)
#define ADCUI_F2STAT_F2VAOV_Msk         (0x1U << ADCUI_F2STAT_F2VAOV_Pos)       /*!< 0000000800 */
#define ADCUI_F2STAT_F2VAOV             ADCUI_F2STAT_F2VAOV_Msk
/* no voltage timeout */
#define ADCUI_F2STAT_F2ZXTOF_Pos        (12U)
#define ADCUI_F2STAT_F2ZXTOF_Msk        (0x1U << ADCUI_F2STAT_F2ZXTOF_Pos)      /*!< 0x00001000 */
#define ADCUI_F2STAT_F2ZXTOF            ADCUI_F2STAT_F2ZXTOF_Msk
/* active power direction change (write 1 to drop this flag) */
#define ADCUI_F2STAT_F2APSIGN_Pos       (15U)
#define ADCUI_F2STAT_F2APSIGN_Msk       (0x1U << ADCUI_F2STAT_F2APSIGN_Pos)     /*!< 0x00008000 */
#define ADCUI_F2STAT_F2APSIGN           ADCUI_F2STAT_F2APSIGN_Msk
/* active power is under threshold */
#define ADCUI_F2STAT_F2APNLDFL_Pos      (16U)
#define ADCUI_F2STAT_F2APNLDFL_Msk      (0x1U << ADCUI_F2STAT_F2APNLDFL_Pos)    /*!< 0x00010000 */
#define ADCUI_F2STAT_F2APNLDFL          ADCUI_F2STAT_F2APNLDFL_Msk
/* reactive power direction change (write 1 to drop this flag) */
#define ADCUI_F2STAT_F2VARSIGN_Pos      (17U)
#define ADCUI_F2STAT_F2VARSIGN_Msk      (0x1U << ADCUI_F2STAT_F2VARSIGN_Pos)    /*!< 0x00020000 */
#define ADCUI_F2STAT_F2VARSIGN          ADCUI_F2STAT_F2VARSIGN_Msk
/* reactive power is under threshold */
#define ADCUI_F2STAT_F2VARNLDFL_Pos     (18U)
#define ADCUI_F2STAT_F2VARNLDFL_Msk     (0x1U <ADCUI_F2STAT_F2VARNLDFL_Pos)     /*!< 0x00040000 */
#define ADCUI_F2STAT_F2VARNLDFL         ADCUI_F2STAT_F2VARNLDFL_Msk
/* full power is under threshold */
#define ADCUI_F2STAT_F2ANLDFL_Pos       (20U)
#define ADCUI_F2STAT_F2ANLDFL_Msk       (0x1U << ADCUI_F2STAT_F2ANLDFL_Pos)     /*!< 0x00100000 */
#define ADCUI_F2STAT_F2ANLDFL           ADCUI_F2STAT_F2ANLDFL_Msk
/* zero-cross detected (write 1 to drop this flag) */
#define ADCUI_F2STAT_F2ZEROCRS_Pos      (21U)
#define ADCUI_F2STAT_F2ZEROCRS_Msk      (0x1U << ADCUI_F2STAT_F2ZEROCRS_Pos)    /*!< 0x00200000 */
#define ADCUI_F2STAT_F2ZEROCRS          ADCUI_F2STAT_F2ZEROCRS_Msk
/* negative active power overflow (write 1 to drop this flag) */
#define ADCUI_F2STAT_F2WATTOVN_Pos      (25U)
#define ADCUI_F2STAT_F2WATTOVN_Msk      (0x1U << ADCUI_F2STAT_F2WATTOVN_Pos)    /*!< 0x02000000 */
#define ADCUI_F2STAT_F2WATTOVN          ADCUI_F2STAT_F2WATTOVN_Msk
/* negative reactive power overflow (write 1 to drop this flag) */
#define ADCUI_F2STAT_F2VAROVN_Pos       (26U)
#define ADCUI_F2STAT_F2VAROVN_Msk       (0x1U << ADCUI_F2STAT_F2VAROVN_Pos)     /*!< 0x04000000 */
#define ADCUI_F2STAT_F2VAROVN           ADCUI_F2STAT_F2VAROVN_Msk

/*******************  Bit definition for ADCUI_F2MASK register  ***************/
/* bit mask F2VF_EMP */
#define ADCUI_F2MASK_F2VF_EMPM_Pos      (0U)
#define ADCUI_F2MASK_F2VF_EMPM_Msk      (0x1U << ADCUI_F2MASK_F2VF_EMPM_Pos)    /*!< 0x00000001 */
#define ADCUI_F2MASK_F2VF_EMPM          ADCUI_F2MASK_F2VF_EMPM_Msk
/* bit mask F2VF_FLL */
#define ADCUI_F2MASK_F2VF_FLLM_Pos      (1U)
#define ADCUI_F2MASK_F2VF_FLLM_Msk      (0x1U << ADCUI_F2MASK_F2VF_FLLM_Pos)    /*!< 0x00000002 */
#define ADCUI_F2MASK_F2VF_FLLM          ADCUI_F2MASK_F2VF_FLLM_Msk
/* bit mask F2VF_OVR */
#define ADCUI_F2MASK_F2VF_OVRM_Pos      (2U)
#define ADCUI_F2MASK_F2VF_OVRM_Msk      (0x1U << ADCUI_F2MASK_F2VF_OVRM_Pos)    /*!< 0x00000004 */
#define ADCUI_F2MASK_F2VF_OVRM          ADCUI_F2MASK_F2VF_OVRM_Msk
/* bit mask F2IF_EMP */
#define ADCUI_F2MASK_F2IF_EMPM_Pos      (3U)
#define ADCUI_F2MASK_F2IF_EMPM_Msk      (0x1U << ADCUI_F2MASK_F2IF_EMPM_Pos)    /*!< 0x00000008 */
#define ADCUI_F2MASK_F2IF_EMPM          ADCUI_F2MASK_F2IF_EMPM_Msk
/* bit mask F2IF_FLL */
#define ADCUI_F2MASK_F2IF_FLLM_Pos      (4U)
#define ADCUI_F2MASK_F2IF_FLLM_Msk      (0x1U << ADCUI_F2MASK_F2IF_FLLM_Pos)    /*!< 0x00000010 */
#define ADCUI_F2MASK_F2IF_FLLM          ADCUI_F2MASK_F2IF_FLLM_Msk
/* bit mask F2IF_OVR */
#define ADCUI_F2MASK_F2IF_OVRM_Pos      (5U)
#define ADCUI_F2MASK_F2IF_OVRM_Msk      (0x1U << ADCUI_F2MASK_F2IF_OVRM_Pos)    /*!< 0x00000020 */
#define ADCUI_F2MASK_F2IF_OVRM          ADCUI_F2MASK_F2IF_OVRM_Msk
/* bit mask F2SAGF */
#define ADCUI_F2MASK_F2SAGFM_Pos        (6U)
#define ADCUI_F2MASK_F2SAGFM_Msk        (0x1U << ADCUI_F2MASK_F2SAGFM_Pos)      /*!< 0x00000040 */
#define ADCUI_F2MASK_F2SAGFM            ADCUI_F2MASK_F2SAGFM_Msk
/* bit mask F2PEAKVF */
#define ADCUI_F2MASK_F2PEAKVFM_Pos      (7U)
#define ADCUI_F2MASK_F2PEAKVFM_Msk      (0x1U << ADCUI_F2MASK_F2PEAKVFM_Pos)    /*!< 0x00000080 */
#define ADCUI_F2MASK_F2PEAKVFM          ADCUI_F2MASK_F2PEAKVFM_Msk
/* bit mask F2PEAKIF */
#define ADCUI_F2MASK_F2PEAKIFM_Pos      (8U)
#define ADCUI_F2MASK_F2PEAKIFM_Msk      (0x1U << ADCUI_F2MASK_F2PEAKIFM_Pos)    /*!< 0x00000100 */
#define ADCUI_F2MASK_F2PEAKIFM          ADCUI_F2MASK_F2PEAKIFM_Msk
/* bit mask F2WATTOVP */
#define ADCUI_F2MASK_F2WATTOVPM_Pos     (9U)
#define ADCUI_F2MASK_F2WATTOVPM_Msk     (0x1U << ADCUI_F2MASK_F2WATTOVPM_Pos)   /*!< 0x00000200 */
#define ADCUI_F2MASK_F2WATTOVPM         ADCUI_F2MASK_F2WATTOVPM_Msk
/* bit mask F2VAROVP */
#define ADCUI_F2MASK_F2VAROVPM_Pos      (10U)
#define ADCUI_F2MASK_F2VAROVPM_Msk      (0x1U << ADCUI_F2MASK_F2VAROVPM_Pos)    /*!< 0x00000400 */
#define ADCUI_F2MASK_F2VAROVPM          ADCUI_F2MASK_F2VAROVPM_Msk
/* bit mask F2VAOV */
#define ADCUI_F2MASK_F2VAOVM_Pos        (11U)
#define ADCUI_F2MASK_F2VAOVM_Msk        (0x1U << ADCUI_F2MASK_F2VAOVM_Pos)      /*!< 0x00000800 */
#define ADCUI_F2MASK_F2VAOVM            ADCUI_F2MASK_F2VAOVM_Msk
/* bit mask F2ZXTOFM */
#define ADCUI_F2MASK_F2ZXTOFM_Pos       (12U)
#define ADCUI_F2MASK_F2ZXTOFM_Msk       (0x1U << ADCUI_F2MASK_F2ZXTOFM_Pos)     /*!< 0x00001000 */
#define ADCUI_F2MASK_F2ZXTOFM           ADCUI_F2MASK_F2ZXTOFM_Msk
/* bit mask F2APSIGN */
#define ADCUI_F2MASK_F2APSIGNM_Pos      (15U)
#define ADCUI_F2MASK_F2APSIGNM_Msk      (0x1U << ADCUI_F2MASK_F2APSIGNM_Pos)    /*!< 0x00008000 */
#define ADCUI_F2MASK_F2APSIGNM          ADCUI_F2MASK_F2APSIGNM_Msk
/* bit mask F2APNLDFL */
#define ADCUI_F2MASK_F2APNLDFLM_Pos     (16U)
#define ADCUI_F2MASK_F2APNLDFLM_Msk     (0x1U << ADCUI_F2MASK_F2APNLDFLM_Pos)   /*!< 0x00010000 */
#define ADCUI_F2MASK_F2APNLDFLM         ADCUI_F2MASK_F2APNLDFLM_Msk
/* bit mask F2VARSIGN */
#define ADCUI_F2MASK_F2VARSIGNM_Pos     (17U)
#define ADCUI_F2MASK_F2VARSIGNM_Msk     (0x1U << ADCUI_F2MASK_F2VARSIGNM_Pos)   /*!< 0x00020000 */
#define ADCUI_F2MASK_F2VARSIGNM         ADCUI_F2MASK_F2VARSIGNM_Msk
/* bit mask F2VARNLDFL */
#define ADCUI_F2MASK_F2VARNLDFLM_Pos    (18U)
#define ADCUI_F2MASK_F2VARNLDFLM_Msk    (0x1U << ADCUI_F2MASK_F2VARNLDFLM_Pos)  /*!< 0x00040000 */
#define ADCUI_F2MASK_F2VARNLDFLM        ADCUI_F2MASK_F2VARNLDFLM_Msk
/* bit mask F2VANLDFL */
#define ADCUI_F2MASK_F2VANLDFLM_Pos     (20U)
#define ADCUI_F2MASK_F2VANLDFLM_Msk     (0x1U << ADCUI_F2MASK_F2VANLDFLM_Pos)   /*!< 0x00100000 */
#define ADCUI_F2MASK_F2VANLDFLM         ADCUI_F2MASK_F2VANLDFLM_Msk
/* bit mask F2ZEROCRS */
#define ADCUI_F2MASK_F2ZEROCRSM_Pos     (21U)
#define ADCUI_F2MASK_F2ZEROCRSM_Msk     (0x1U << ADCUI_F2MASK_F2ZEROCRSM_Pos)   /*!< 0x00200000 */
#define ADCUI_F2MASK_F2ZEROCRSM         ADCUI_F2MASK_F2ZEROCRSM_Msk
/* bit mask F2WATTOVN */
#define ADCUI_F2MASK_F2WATTOVNM_Pos     (25U)
#define ADCUI_F2MASK_F2WATTOVNM_Msk     (0x1U << ADCUI_F2MASK_F2WATTOVNM_Pos)   /*!< 0x02000000 */
#define ADCUI_F2MASK_F2WATTOVNM         ADCUI_F2MASK_F2WATTOVNM_Msk
/* bit mask F2VAROVNM */
#define ADCUI_F2MASK_F2VAROVNM_Pos      (26U)
#define ADCUI_F2MASK_F2VAROVNM_Msk      (0x1U << ADCUI_F2MASK_F2VAROVNM_Pos)    /*!< 0x04000000 */
#define ADCUI_F2MASK_F2VAROVNM          ADCUI_F2MASK_F2VAROVNM_Msk

/*******************  Bit definition for ADCUI_CCAL1 register  ****************/
/* voltage 0 calibration gain */
#define ADCUI_CCAL1_V0BGAIN_Pos         (0U)
#define ADCUI_CCAL1_V0BGAIN_Msk         (0xFFFU << ADCUI_CCAL1_V0BGAIN_Pos)     /*!< 0x00000FFF */
#define ADCUI_CCAL1_V0BGAIN             ADCUI_CCAL1_V0BGAIN_Msk
/* current 0 calibration gain */
#define ADCUI_CCAL1_I0BGAIN_Pos         (12U)
#define ADCUI_CCAL1_I0BGAIN_Msk         (0xFFFU << ADCUI_CCAL1_I0BGAIN_Pos)     /*!< 0x00FFF000 */
#define ADCUI_CCAL1_I0BGAIN             ADCUI_CCAL1_I0BGAIN_Msk

/*******************  Bit definition for ADCUI_CCAL2 register  ****************/
/* voltage 1 calibration gain */
#define ADCUI_CCAL2_V1BGAIN_Pos         (0U)
#define ADCUI_CCAL2_V1BGAIN_Msk         (0xFFFU << ADCUI_CCAL2_V1BGAIN_Pos)     /*!< 0x00000FFF */
#define ADCUI_CCAL2_V1BGAIN             ADCUI_CCAL2_V1BGAIN_Msk
/* current 1 calibration gain */
#define ADCUI_CCAL2_I1BGAIN_Pos         (12U)
#define ADCUI_CCAL2_I1BGAIN_Msk         (0xFFFU << ADCUI_CCAL2_I1BGAIN_Pos)     /*!< 0x00FFF000 */
#define ADCUI_CCAL2_I1BGAIN             ADCUI_CCAL2_I1BGAIN_Msk

/*******************  Bit definition for ADCUI_CCAL3 register  ****************/
/* voltage 2 calibration gain */
#define ADCUI_CCAL3_V2BGAIN_Pos         (0U)
#define ADCUI_CCAL3_V2BGAIN_Msk         (0xFFFU << ADCUI_CCAL3_V2BGAIN_Pos)     /*!< 0x00000FFF */
#define ADCUI_CCAL3_V2BGAIN             ADCUI_CCAL3_V2BGAIN_Msk
/* current 2 calibration gain */
#define ADCUI_CCAL3_I2BGAIN_Pos         (12U)
#define ADCUI_CCAL3_I2BGAIN_Msk         (0xFFFU << ADCUI_CCAL3_I2BGAIN_Pos)     /*!< 0x00FFF000 */
#define ADCUI_CCAL3_I2BGAIN             ADCUI_CCAL3_I2BGAIN_Msk

/*******************  Bit definition for ADCUI_CCAL4 register  ****************/
/* current 3 calibration gain */
#define ADCUI_CCAL4_I3BGAIN_Pos         (0U)
#define ADCUI_CCAL4_I3BGAIN_Msk         (0xFFFU << ADCUI_CCAL4_I3BGAIN_Pos)     /*!< 0x00000FFF */
#define ADCUI_CCAL4_I3BGAIN             ADCUI_CCAL4_I3BGAIN_Msk

/* low part energy accumulator mask */
#define ADCUI_HP_ACCUM_Pos				(25U)
#define ADCUI_LP_ACCUM_Msk				(0x1FFFFFFU)

/*
 * ==========================================================================
 * ---------------------- TIMER registers bits ------------------------------
 * ==========================================================================
 */

/* filter configuration (ETR and CHFLTR) */
#define TIM_FLTR_1_CLK					(0x0U)
#define TIM_FLTR_2_CLK					(0x1U)
#define TIM_FLTR_4_CLK					(0x2U)
#define TIM_FLTR_8_CLK					(0x3U)
#define TIM_FLTR_6_FDTS_2				(0x4U)
#define TIM_FLTR_8_FDTS_2				(0x5U)
#define TIM_FLTR_6_FDTS_4				(0x6U)
#define TIM_FLTR_8_FDTS_4				(0x7U)
#define TIM_FLTR_6_FDTS_8				(0x8U)
#define TIM_FLTR_8_FDTS_8				(0x9U)
#define TIM_FLTR_5_FDTS_16				(0xAU)
#define TIM_FLTR_6_FDTS_16				(0xBU)
#define TIM_FLTR_8_FDTS_16				(0xCU)
#define TIM_FLTR_5_FDTS_32				(0xDU)
#define TIM_FLTR_6_FDTS_32				(0xEU)
#define TIM_FLTR_8_FDTS_32				(0xFU)

/* TIMER events */
/* CNT zero event */
#define TIM_CNTZEROEVENT_Pos     		(0U)
#define TIM_CNTZEROEVENT_Msk     		(0x1U << TIM_CNTZEROEVENT_Pos)   		/*!< 0x00000001 */
#define TIM_CNTZEROEVENT         		TIM_CNTZEROEVENT_Msk
/* CNT ARR event */
#define TIM_CNTARREVENT_Pos      		(1U)
#define TIM_CNTARREVENT_Msk      		(0x1U << TIM_CNTARREVENT_Pos)    		/*!< 0x00000002 */
#define TIM_CNTARREVENT         		TIM_CNTARREVENT_Msk
/* ETR rising event */
#define TIM_ETRREEVENT_Pos       		(2U)
#define TIM_ETRREEVENT_Msk      		(0x1U << TIM_ETRREEVENT_Pos)     		/*!< 0x00000004 */
#define TIM_ETRREEVENT           		TIM_ETRREEVENT_Msk
/* ETR falling event */
#define TIM_ETRFEEVENT_Pos       		(3U)
#define TIM_ETRFEEVENT_Msk       		(0x1U << TIM_ETRFEEVENT_Pos)    		/*!< 0x00000008 */
#define TIM_ETRFEEVENT           		TIM_ETRFEEVENT_Msk
/* BRK event (0 - BRK = 0, 1 - BRK = 1) */
#define TIM_BRKEVENT_Pos         		(4U)
#define TIM_BRKEVENT_Msk         		(0x1U << TIM_BRKEVENT_Pos)       		/*!< 0x00000010 */
#define TIM_BRKEVENT             		TIM_BRKEVENT_Msk
/* CCR capture events */
#define TIM_CCRCAPEVENT_CH1_Pos  		(5U)
#define TIM_CCRCAPEVENT_CH1_Msk  		(0x1U << TIM_CCRCAPEVENT_CH1_Pos) 		/*!< 0x00000020 */
#define TIM_CCRCAPEVENT_CH1      		TIM_CCRCAPEVENT_CH1_Msk
#define TIM_CCRCAPEVENT_CH2_Pos  		(6U)
#define TIM_CCRCAPEVENT_CH2_Msk  		(0x1U << TIM_CCRCAPEVENT_CH2_Pos)		/*!< 0x00000040 */
#define TIM_CCRCAPEVENT_CH2      		TIM_CCRCAPEVENT_CH2_Msk
#define TIM_CCRCAPEVENT_CH3_Pos  		(7U)
#define TIM_CCRCAPEVENT_CH3_Msk  		(0x1U << TIM_CCRCAPEVENT_CH3_Pos)		/*!< 0x00000080 */
#define TIM_CCRCAPEVENT_CH3      		TIM_CCRCAPEVENT_CH3_Msk
#define TIM_CCRCAPEVENT_CH4_Pos  		(8U)
#define TIM_CCRCAPEVENT_CH4_Msk  		(0x1U << TIM_CCRCAPEVENT_CH4_Pos)		/*!< 0x00000100 */
#define TIM_CCRCAPEVENT_CH4      		TIM_CCRCAPEVENT_CH4_Msk
/* capture REF events */
#define TIM_CCRREFEVENT_CH1_Pos  		(9U)
#define TIM_CCRREFEVENT_CH1_Msk  		(0x1U << TIM_CCRREFEVENT_CH1_Pos)		/*!< 0x00000200 */
#define TIM_CCRREFEVENT_CH1      		TIM_CCRREFEVENT_CH1_Msk
#define TIM_CCRREFEVENT_CH2_Pos  		(10U)
#define TIM_CCRREFEVENT_CH2_Msk  		(0x1U << TIM_CCRREFEVENT_CH2_Pos)		/*!< 0x00000400 */
#define TIM_CCRREFEVENT_CH2      		TIM_CCRREFEVENT_CH2_Msk
#define TIM_CCRREFEVENT_CH3_Pos  		(11U)
#define TIM_CCRREFEVENT_CH3_Msk  		(0x1U << TIM_CCRREFEVENT_CH3_Pos)		/*!< 0x00000800 */
#define TIM_CCRREFEVENT_CH3      		TIM_CCRREFEVENT_CH3_Msk
#define TIM_CCRREFEVENT_CH4_Pos  		(12U)
#define TIM_CCRREFEVENT_CH4_Msk  		(0x1U << TIM_CCRREFEVENT_CH4_Pos)		/*!< 0x00001000 */
#define TIM_CCRREFEVENT_CH4      		TIM_CCRREFEVENT_CH4_Msk
/* CCR1 capture events */
#define TIM_CCR1CAPEVENT_CH1_Pos 		(13U)
#define TIM_CCR1CAPEVENT_CH1_Msk 		(0x1U << TIM_CCR1CAPEVENT_CH1_Pos)		/*!< 0x00000020 */
#define TIM_CCR1CAPEVENT_CH1     		TIM_CCR1CAPEVENT_CH1_Msk
#define TIM_CCR1CAPEVENT_CH2_Pos 		(14U)
#define TIM_CCR1CAPEVENT_CH2_Msk 		(0x1U << TIM_CCR1CAPEVENT_CH2_Pos)		/*!< 0x00000040 */
#define TIM_CCR1CAPEVENT_CH2     		TIM_CCR1CAPEVENT_CH2_Msk
#define TIM_CCR1CAPEVENT_CH3_Pos 		(15U)
#define TIM_CCR1CAPEVENT_CH3_Msk 		(0x1U << TIM_CCR1CAPEVENT_CH3_Pos)		/*!< 0x00000080 */
#define TIM_CCR1CAPEVENT_CH3     		TIM_CCR1CAPEVENT_CH3_Msk
#define TIM_CCR1CAPEVENT_CH4_Pos 		(16U)
#define TIM_CCR1CAPEVENT_CH4_Msk 		(0x1U << TIM_CCR1CAPEVENT_CH4_Pos)		/*!< 0x00000100 */
#define TIM_CCR1CAPEVENT_CH4     		TIM_CCR1CAPEVENT_CH4_Msk
/* all timer events mask */
#define TIM_EVENTS_Msk					(0x1FF)

/*******************  Bit definition for TIM_CNTR register  *******************/
/* timer enable switch (0 - disabled, 1 - enabled) */
#define TIM_CNTRL_CNT_EN_Pos            (0U)
#define TIM_CNTRL_CNT_EN_Msk            (0x1U << TIM_CNTRL_CNT_EN_Pos)          /*!< 0x00000001 */
#define TIM_CNTRL_CNT_EN                TIM_CNTRL_CNT_EN_Msk
/* ARR update (0 - ARR will be updated immediately, ARR will be updated at update event) */
#define TIM_CNTRL_ARRB_EN_Pos           (1U)
#define TIM_CNTRL_ARRB_EN_Msk           (0x1U << TIM_CNTRL_ARRB_EN_Pos)         /*!< 0x00000002 */
#define TIM_CNTRL_ARRB_IMMEDIATE        (0x0U << TIM_CNTRL_ARRB_EN_Pos)
#define TIM_CNTRL_ARRB_DELAYED			(0x1U << TIM_CNTRL_ARRB_EN_Pos)
/* update state (0 - new data could be written to CNT,PSG,ARR, 1 - write ongoing) */
#define TIM_CNTRL_WR_CMPL_Pos           (2U)
#define TIM_CNTRL_WR_CMPL_Msk           (0x1U << TIM_CNTRL_WR_CMPL_Pos)         /*!< 0x00000004 */
#define TIM_CNTRL_WR_CMPL               TIM_CNTRL_WR_CMPL_Msk
/* direction (0 - up 0->ARR, 1 - down ARR->0) */
#define TIM_CNTRL_DIR_Pos               (3U)
#define TIM_CNTRL_DIR_Msk               (0x1U << TIM_CNTRL_DIR_Pos)             /*!< 0x00000008 */
#define TIM_CNTRL_DIR_UP                (0x0U << TIM_CNTRL_DIR_Pos)
#define TIM_CNTRL_DIR_DOWN              (0x1U << TIM_CNTRL_DIR_Pos)
/* samping rate (0b00 - every TIM_CLK, 0b01 - every second TIM_CLK, 0b10 - third TIM_CLK, 0b11 - fourth TIM_CLK) */
#define TIM_CNTRL_FDTS_Pos              (4U)
#define TIM_CNTRL_FDTS_Msk              (0x3U << TIM_CNTRL_FDTS_Pos)            /*!< 0x00000030 */
#define TIM_CNTRL_FDTS_1                (0x0U << TIM_CNTRL_FDTS_Pos)            /*!< 0x00000000 */
#define TIM_CNTRL_FDTS_2                (0x1U << TIM_CNTRL_FDTS_Pos)            /*!< 0x00000010 */
#define TIM_CNTRL_FDTS_3                (0x2U << TIM_CNTRL_FDTS_Pos)            /*!< 0x00000020 */
#define TIM_CNTRL_FDTS_4                (0x3U << TIM_CNTRL_FDTS_Pos)            /*!< 0x00000030 */
/* counting mode */
#define TIM_CNTRL_CNT_MODE_Pos          (6U)
#define TIM_CNTRL_CNT_MODE_Msk          (0x3U << TIM_CNTRL_CNT_MODE_Pos)        /*!< 0x000000C0 */
#define TIM_CNTRL_CNT_MODE_CLK_FIXED    (0x0U << TIM_CNTRL_CNT_MODE_Pos)        /*!< 0x00000000 */
#define TIM_CNTRL_CNT_MODE_CLK_PINGPONG (0x1U << TIM_CNTRL_CNT_MODE_Pos)        /*!< 0x00000040 */
#define TIM_CNTRL_CNT_MODE_EVT_FIXED    (0x2U << TIM_CNTRL_CNT_MODE_Pos)        /*!< 0x00000080 */
#define TIM_CNTRL_CNT_MODE_EVT_PINGPONG (0x3U << TIM_CNTRL_CNT_MODE_Pos)        /*!< 0x00000080 */
/* event selection */
#define TIM_CNTRL_EVENT_SEL_Pos         (8U)
#define TIM_CNTRL_EVENT_SEL_Msk         (0xFU << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000F00 */
#define TIM_CNTRL_EVENT_SEL_TIMCLK      (0x0U << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000000 */
#define TIM_CNTRL_EVENT_SEL_TIMUDP1     (0x1U << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000100 */
#define TIM_CNTRL_EVENT_SEL_TIMUPD2     (0x2U << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000200 */
#define TIM_CNTRL_EVENT_SEL_TIMUPD3     (0x3U << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000300 */
#define TIM_CNTRL_EVENT_SEL_EVENTCH1    (0x4U << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000400 */
#define TIM_CNTRL_EVENT_SEL_EVENTCH2    (0x5U << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000500 */
#define TIM_CNTRL_EVENT_SEL_EVENTCH3    (0x6U << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000600 */
#define TIM_CNTRL_EVENT_SEL_EVENTCH4    (0x7U << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000700 */
#define TIM_CNTRL_EVENT_SEL_ETRRISING   (0x8U << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000800 */
#define TIM_CNTRL_EVENT_SEL_ETRFALLING  (0x9U << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000900 */
#define TIM_CNTRL_EVENT_SEL_TIMUPD4     (0xAU << TIM_CNTRL_EVENT_SEL_Pos)       /*!< 0x00000A00 */

/*******************  Bit definition for TIM_CHy_CNTRL register  **************/
/* channel filter, should be used TIM_FLTR_xx bits */
#define TIM_CHy_CNTRL_CHFLTR_Pos        (0U)
#define TIM_CHy_CNTRL_CHFLTR_Msk        (0xFU << TIM_CHy_CNTRL_CHFLTR_Pos)      /*!< 0x0000000F */
/* compare source control register */
#define TIM_CHy_CNTRL_CHSEL_Pos         (4U)
#define TIM_CHy_CNTRL_CHSEL_Msk         (0x3U << TIM_CHy_CNTRL_CHSEL_Pos)       /*!< 0x00000030 */
#define TIM_CHy_CNTRL_CHSEL_CHxiRISING  (0x0U << TIM_CHy_CNTRL_CHSEL_Pos)       /*!< 0x00000000 */
#define TIM_CHy_CNTRL_CHSEL_CHxiFALLING (0x1U << TIM_CHy_CNTRL_CHSEL_Pos)       /*!< 0x00000010 */
#define TIM_CHy_CNTRL_CHSEL_CHp1RISING  (0x2U << TIM_CHy_CNTRL_CHSEL_Pos)       /*!< 0x00000020 */
#define TIM_CHy_CNTRL_CHSEL_CHp2RISING  (0x3U << TIM_CHy_CNTRL_CHSEL_Pos)       /*!< 0x00000030 */
/* prescaler for input channel */
#define TIM_CHy_CNTRL_CHPSC_Pos         (6U)
#define TIM_CHy_CNTRL_CHPSC_Msk         (0x3U << TIM_CHy_CNTRL_CHPSC_Pos)       /*!< 0x000000C0 */
#define TIM_CHy_CNTRL_CHPSC_DIV1        (0x0U << TIM_CHy_CNTRL_CHPSC_Pos)       /*!< 0x00000000 */
#define TIM_CHy_CNTRL_CHPSC_DIV2        (0x1U << TIM_CHy_CNTRL_CHPSC_Pos)       /*!< 0x00000040 */
#define TIM_CHy_CNTRL_CHPSC_DIV4        (0x2U << TIM_CHy_CNTRL_CHPSC_Pos)       /*!< 0x00000080 */
#define TIM_CHy_CNTRL_CHPSC_DIV8        (0x3U << TIM_CHy_CNTRL_CHPSC_Pos)       /*!< 0x000000C0 */
/* ETR enable (0 - disabled, 1 - enabled) */
#define TIM_CHy_CNTRL_OCCE_Pos          (8U)
#define TIM_CHy_CNTRL_OCCE_Msk          (0x1U << TIM_CHy_CNTRL_OCCE_Pos)        /*!< 0x00000100 */
#define TIM_CHy_CNTRL_OCCE              TIM_CHy_CNTRL_OCCE_Msk
/* REF for PWM */
#define TIM_CHy_CNTRL_OCCM_Pos          (9U)
#define TIM_CHy_CNTRL_OCCM_Msk          (0x7U << TIM_CHy_CNTRL_OCCM_Pos)        /*!< 0x00000E00 */
#define TIM_CHy_CNTRL_OCCM_ALW0         (0x0U << TIM_CHy_CNTRL_OCCM_Pos)        /*!< 0x00000000 */
#define TIM_CHy_CNTRL_OCCM_1_CCR        (0x1U << TIM_CHy_CNTRL_OCCM_Pos)        /*!< 0x00000200 */
#define TIM_CHy_CNTRL_OCCM_0_CCR        (0x2U << TIM_CHy_CNTRL_OCCM_Pos)        /*!< 0x00000400 */
#define TIM_CHy_CNTRL_OCCM_REF          (0x3U << TIM_CHy_CNTRL_OCCM_Pos)        /*!< 0x00000600 */
#define TIM_CHy_CNTRL_OCCM_ALW1         (0x5U << TIM_CHy_CNTRL_OCCM_Pos)        /*!< 0x00000A00 */
#define TIM_CHy_CNTRL_OCCM_GR_CCR       (0x6U << TIM_CHy_CNTRL_OCCM_Pos)        /*!< 0x00000C00 */
#define TIM_CHy_CNTRL_OCCM_LESS_CCR     (0x7U << TIM_CHy_CNTRL_OCCM_Pos)        /*!< 0x00000E00 */
/* BRK enable (0 - disabled, 1 - enabled) */
#define TIM_CHy_CNTRL_BRKEN_Pos         (12U)
#define TIM_CHy_CNTRL_BRKEN_Msk         (0x1U << TIM_CHy_CNTRL_BRKEN_Pos)       /*!< 0x00001000 */
#define TIM_CHy_CNTRL_BRKEN             TIM_CHy_CNTRL_BRKEN_Msk
/* ETR enable (0 - disabled, 1 - enabled) */
#define TIM_CHy_CNTRL_ETREN_Pos         (13U)
#define TIM_CHy_CNTRL_ETREN_Msk         (0x1U << TIM_CHy_CNTRL_ETREN_Pos)       /*!< 00x0002000 */
#define TIM_CHy_CNTRL_ETREN             TIM_CHy_CNTRL_ETREN_Msk
/* WR CMPL  (0 - write not active, new data could be written, 1 - write protection) */
#define TIM_CHy_CNTRL_WRCMPL_Pos        (14U)
#define TIM_CHy_CNTRL_WRCMPL_Msk        (0x1U << TIM_CHy_CNTRL_WRCMPL_Pos)      /*!< 0x00004000 */
#define TIM_CHy_CNTRL_WRCMPL            TIM_CHy_CNTRL_WRCMPL_Msk
/* capture or PWM (0 - PWM, 1 - Capture) */
#define TIM_CHy_CNTRL_CAPnPMW_Pos       (15U)
#define TIM_CHy_CNTRL_CAPnPMW_Msk       (0x1U << TIM_CHy_CNTRL_CAPnPMW_Pos)     /*!< 0x00008000 */
#define TIM_CHy_CNTRL_CAPnPWM_PWM       (0x0U << TIM_CHy_CNTRL_CAPnPMW_Pos)     /*!< 0x00000000 */
#define TIM_CHy_CNTRL_CAPnPMW_CAPTURE   (0x1U << TIM_CHy_CNTRL_CAPnPMW_Pos)     /*!< 0x00008000 */

/*******************  Bit definition for TIM_CHy_CNTRL1 register  *************/
/* output mode for direct channel */
#define TIM_CHy_CNTRL1_SELOE_Pos        (0U)
#define TIM_CHy_CNTRL1_SELOE_Msk        (0x3U << TIM_CHy_CNTRL1_SELOE_Pos)      /*!< 0x00000003 */
#define TIM_CHy_CNTRL1_SELOE_OE0        (0x0U << TIM_CHy_CNTRL1_SELOE_Pos)      /*!< 0x00000000 */
#define TIM_CHy_CNTRL1_SELOE_OE1        (0x1U << TIM_CHy_CNTRL1_SELOE_Pos)      /*!< 0x00000001 */
#define TIM_CHy_CNTRL1_SELOE_REF        (0x2U << TIM_CHy_CNTRL1_SELOE_Pos)      /*!< 0x00000002 */
#define TIM_CHy_CNTRL1_SELOE_DTG        (0x3U << TIM_CHy_CNTRL1_SELOE_Pos)      /*!< 0x00000003 */
/* output for direct channel */
#define TIM_CHy_CNTRL1_SELO_Pos         (2U)
#define TIM_CHy_CNTRL1_SELO_Msk         (0x3U << TIM_CHy_CNTRL1_SELO_Pos)       /*!< 0x0000000C */
#define TIM_CHy_CNTRL1_SELO_OE0         (0x0U << TIM_CHy_CNTRL1_SELO_Pos)       /*!< 0x00000000 */
#define TIM_CHy_CNTRL1_SELO_OE1         (0x1U << TIM_CHy_CNTRL1_SELO_Pos)       /*!< 0x00000004 */
#define TIM_CHy_CNTRL1_SELO_REF         (0x2U << TIM_CHy_CNTRL1_SELO_Pos)       /*!< 0x00000008 */
#define TIM_CHy_CNTRL1_SELO_DTG         (0x3U << TIM_CHy_CNTRL1_SELO_Pos)       /*!< 0x0000000C */
/* inversion of the direct channel */
#define TIM_CHy_CNTRL1_INV_Pos          (4U)
#define TIM_CHy_CNTRL1_INV_Msk          (0x1U << TIM_CHy_CNTRL1_INV_Pos)        /*!< 0x00000010 */
#define TIM_CHy_CNTRL1_INV              TIM_CHy_CNTRL1_INV_Msk
/* output mode for non-inverted channel */
#define TIM_CHy_CNTRL1_NSELOE_Pos       (8U)
#define TIM_CHy_CNTRL1_NSELOE_Msk       (0x3U << TIM_CHy_CNTRL1_NSELOE_Pos)     /*!< 0x00000300 */
#define TIM_CHy_CNTRL1_NSELOE_OE0       (0x0U << TIM_CHy_CNTRL1_NSELOE_Pos)     /*!< 0x00000000 */
#define TIM_CHy_CNTRL1_NSELOE_OE1       (0x1U << TIM_CHy_CNTRL1_NSELOE_Pos)     /*!< 0x00000100 */
#define TIM_CHy_CNTRL1_NSELOE_REF       (0x2U << TIM_CHy_CNTRL1_NSELOE_Pos)     /*!< 0x00000200 */
#define TIM_CHy_CNTRL1_NSELOE_DTG       (0x3U << TIM_CHy_CNTRL1_NSELOE_Pos)     /*!< 0x00000300 */
/* output for non-inverted channel */
#define TIM_CHy_CNTRL1_NSELO_Pos        (10U)
#define TIM_CHy_CNTRL1_NSELO_Msk        (0x3U << TIM_CHy_CNTRL1_NSELO_Pos)      /*!< 0x00000C00 */
#define TIM_CHy_CNTRL1_NSELO_OE0        (0x0U << TIM_CHy_CNTRL1_NSELO_Pos)      /*!< 0x00000000 */
#define TIM_CHy_CNTRL1_NSELO_OE1        (0x1U << TIM_CHy_CNTRL1_NSELO_Pos)      /*!< 0x00000400 */
#define TIM_CHy_CNTRL1_NSELO_REF        (0x2U << TIM_CHy_CNTRL1_NSELO_Pos)      /*!< 0x00000800 */
#define TIM_CHy_CNTRL1_NSELO_DTG        (0x3U << TIM_CHy_CNTRL1_NSELO_Pos)      /*!< 0x00000C00 */
/* inversion of the non-inverted channel */
#define TIM_CHy_CNTRL1_NINV_Pos         (12U)
#define TIM_CHy_CNTRL1_NINV_Msk         (0x1U << TIM_CHy_CNTRL1_NINV_Pos)       /*!< 0x00001000 */
#define TIM_CHy_CNTRL1_NINV             TIM_CHy_CNTRL1_NINV_Msk

/*******************  Bit definition for TIM_CHy_CNTRL2 register  *************/
/* compare channel selection */
#define TIM_CHy_CNTRL2_CHSEL_Pos        (0U)
#define TIM_CHy_CNTRL2_CHSEL_Msk        (0x3U << TIM_CHy_CNTRL2_CHSEL_Pos)      /*!< 0x00000000 */
#define TIM_CHy_CNTRL2_CHSEL_CHxRISING  (0x0U << TIM_CHy_CNTRL2_CHSEL_Pos)      /*!< 0x00000000 */
#define TIM_CHy_CNTRL2_CHSEL_CHxFALLING (0x1U << TIM_CHy_CNTRL2_CHSEL_Pos)      /*!< 0x00000001 */
#define TIM_CHy_CNTRL2_CHSEL_Cp1FALLING (0x2U << TIM_CHy_CNTRL2_CHSEL_Pos)      /*!< 0x00000002 */
#define TIM_CHy_CNTRL2_CHSEL_Cp2FALLING (0x3U << TIM_CHy_CNTRL2_CHSEL_Pos)      /*!< 0x00000003 */
/* CCR1 enable (0 - disabled, 1 - enabled) */
#define TIM_CHy_CNTRL2_CCR1EN_Pos       (2U)
#define TIM_CHy_CNTRL2_CCR1EN_Msk       (0x1U << TIM_CHy_CNTRL2_CCR1EN_Pos)      /*!< 0x00000004 */
#define TIM_CHy_CNTRL2_CCR1EN           TIM_CHy_CNTRL2_CCR1EN_Msk
/* CCR reload (0 - in any time, 1 - only when CNT = 0) */
#define TIM_CHy_CNTRL2_CCRRLD_Pos       (3U)
#define TIM_CHy_CNTRL2_CCRRLD_Msk       (0x1U << TIM_CHy_CNTRL2_CCRRLD_Pos)     /*!< 0x00000008 */
#define TIM_CHy_CNTRL2_CCRRLD           TIM_CHy_CNTRL2_CCRRLD_Msk
/* event delay (0 - no delay, 1 - synchronyze with CCR update) */
#define TIM_CHy_CNTRL2_EVDELAY_Pos      (4U)
#define TIM_CHy_CNTRL2_EVDELAY_Msk      (0x1U << TIM_CHy_CNTRL2_EVDELAY_Pos)    /*!< 0x00000010 */
#define TIM_CHy_CNTRL2_EVDELAY_NODELAY  (0x0U << TIM_CHy_CNTRL2_EVDELAY_Pos)    /*!< 0x00000000 */
#define TIM_CHy_CNTRL2_EVDELAY_CCRSYNC  (0x1U << TIM_CHy_CNTRL2_EVDELAY_Pos)    /*!< 0x00000010 */

/*******************  Bit definition for TIM_CHy_DTG register  ****************/
/* predivisor for DTG (linear = 1,2,3,4,5, etc.) */
#define TIM_CHy_DTG_DTG_Pos             (0U)
#define TIM_CHy_DTG_DTG_Msk             (0xFU << TIM_CHy_DTG_DTG_Pos)           /*!< 0x0000000F */
/* clock source for DTG (0 - TIM_CLK, 1 - FDTS) */
#define TIM_CHy_DTG_EDTS_Pos            (4U)
#define TIM_CHy_DTG_EDTS_Msk            (0x1U << TIM_CHy_DTG_EDTS_Pos)          /*!< 0x00000010 */
#define TIM_CHy_DTG_EDTS_TIMCLK         (0x0U << TIM_CHy_DTG_EDTS_Pos)          /*!< 0x00000000 */
#define TIM_CHy_DTG_EDTS_FDTS           (0x1U << TIM_CHy_DTG_EDTS_Pos)          /*!< 0x00000010 */
/* divisor for DTG, DTGdel = DTGx * (DTG + 1) */
#define TIM_CHy_DTG_DTGx_Pos            (8U)
#define TIM_CHy_DTG_DTGx_Msk            (0xFFU << TIM_CHy_DTG_DTGx_Pos)         /*!< 0x0000FF00 */

/*******************  Bit definition for TIM_BRKETR_CNTRL register  ***********/
/* BRK input inversion (0 - not inverted, 1 - inverted) */
#define TIM_BRKETR_CNTRL_BRKINV_Pos     (0U)
#define TIM_BRKETR_CNTRL_BRKINV_Msk     (0x1U << TIM_BRKETR_CNTRL_BRKINV_Pos)   /*!< 0x00000001 */
#define TIM_BRKETR_CNTRL_BRKINV_NOTINV  (0x0U << TIM_BRKETR_CNTRL_BRKINV_Pos)   /*!< 0x00000000 */
#define TIM_BRKETR_CNTRL_BRKINV_INV     (0x1U << TIM_BRKETR_CNTRL_BRKINV_Pos)   /*!< 0x00000001 */
/* ETR input inversion (0 - not inverted, 1 - inverted) */
#define TIM_BRKETR_CNTRL_ETRINV_Pos     (0U)
#define TIM_BRKETR_CNTRL_ETRINV_Msk     (0x1U << TIM_BRKETR_CNTRL_ETRINV_Pos)   /*!< 0x00000002 */
#define TIM_BRKETR_CNTRL_ETRINV_NOTINV  (0x0U << TIM_BRKETR_CNTRL_ETRINV_Pos)   /*!< 0x00000000 */
#define TIM_BRKETR_CNTRL_ETRINV_INV     (0x1U << TIM_BRKETR_CNTRL_ETRINV_Pos)   /*!< 0x00000002 */
/* ETR prescaler (0b00 - 1, 0b01 - /2, 0b10 - /4, 0b11 - /8) */
#define TIM_BRKETR_CNTRL_ETRPSC_Pos     (0U)
#define TIM_BRKETR_CNTRL_ETRPSC_Msk     (0x3U << TIM_BRKETR_CNTRL_ETRPSC_Pos)   /*!< 0x0000000C */
#define TIM_BRKETR_CNTRL_ETRPSC_DIV1    (0x0U << TIM_BRKETR_CNTRL_ETRPSC_Pos)   /*!< 0x00000000 */
#define TIM_BRKETR_CNTRL_ETRPSC_DIV2    (0x1U << TIM_BRKETR_CNTRL_ETRPSC_Pos)   /*!< 0x00000004 */
#define TIM_BRKETR_CNTRL_ETRPSC_DIV4    (0x2U << TIM_BRKETR_CNTRL_ETRPSC_Pos)   /*!< 0x00000008 */
#define TIM_BRKETR_CNTRL_ETRPSC_DIV8    (0x3U << TIM_BRKETR_CNTRL_ETRPSC_Pos)   /*!< 0x0000000C */
/* channel ETR filter, should be used TIM_FLTR_xx bits */
#define TIM_BRKETR_CNTRL_ETRFLTR_Pos        (4U)
#define TIM_BRKETR_CNTRL_ETRFLTR_Msk        (0xFU << TIM_BRKETR_CNTRL_ETRFLTR_Pos) /*!< 0x000000F0 */

/*******************  Bit definition for TIM_STATUS register  *****************/
/*******************  Bit definition for TIM_IE register  *********************/
/*******************  Bit definition for TIM_DMA_RE register  *****************/
/* use common event bit mask */

/*
 * ==========================================================================
 * ---------------------- GPIO registers bits -------------------------------
 * ==========================================================================
 */

/*******************  GPIO PINs ***********************************************/
/* pin 0 */
#define PORT_Pin_0_Pos                  (0U)
#define PORT_Pin_0_Msk                  (0x1U << PORT_Pin_0_Pos)                /*!< 0x00000001 */
#define PORT_Pin_0                      PORT_Pin_0_Msk
/* pin 1 */
#define PORT_Pin_1_Pos                  (1U)
#define PORT_Pin_1_Msk                  (0x1U << PORT_Pin_1_Pos)                /*!< 0x00000002 */
#define PORT_Pin_1                      PORT_Pin_1_Msk
/* pin 2 */
#define PORT_Pin_2_Pos                  (2U)
#define PORT_Pin_2_Msk                  (0x1U << PORT_Pin_2_Pos)                /*!< 0x00000004 */
#define PORT_Pin_2                      PORT_Pin_2_Msk
/* pin 3 */
#define PORT_Pin_3_Pos                  (3U)
#define PORT_Pin_3_Msk                  (0x1U << PORT_Pin_3_Pos)                /*!< 0x00000008 */
#define PORT_Pin_3                      PORT_Pin_3_Msk

/* pin 4 */
#define PORT_Pin_4_Pos                  (4U)
#define PORT_Pin_4_Msk                  (0x1U << PORT_Pin_4_Pos)                /*!< 0x00000010 */
#define PORT_Pin_4                      PORT_Pin_4_Msk
/* pin 5 */
#define PORT_Pin_5_Pos                  (5U)
#define PORT_Pin_5_Msk                  (0x1U << PORT_Pin_5_Pos)                /*!< 0x00000020 */
#define PORT_Pin_5                      PORT_Pin_5_Msk
/* pin 6 */
#define PORT_Pin_6_Pos                  (6U)
#define PORT_Pin_6_Msk                  (0x1U << PORT_Pin_6_Pos)                /*!< 0x00000040 */
#define PORT_Pin_6                      PORT_Pin_6_Msk
/* pin 7 */
#define PORT_Pin_7_Pos                  (7U)
#define PORT_Pin_7_Msk                  (0x1U << PORT_Pin_7_Pos)                /*!< 0x00000080 */
#define PORT_Pin_7                      PORT_Pin_7_Msk

/* pin 8 */
#define PORT_Pin_8_Pos                  (8U)
#define PORT_Pin_8_Msk                  (0x1U << PORT_Pin_8_Pos)                /*!< 0x00000100 */
#define PORT_Pin_8                      PORT_Pin_8_Msk
/* pin 9 */
#define PORT_Pin_9_Pos                  (9U)
#define PORT_Pin_9_Msk                  (0x1U << PORT_Pin_9_Pos)                /*!< 0x00000200 */
#define PORT_Pin_9                      PORT_Pin_9_Msk
/* pin 10 */
#define PORT_Pin_10_Pos                 (10U)
#define PORT_Pin_10_Msk                 (0x1U << PORT_Pin_10_Pos)               /*!< 0x00000400 */
#define PORT_Pin_10                     PORT_Pin_10_Msk
/* pin 11 */
#define PORT_Pin_11_Pos                 (11U)
#define PORT_Pin_11_Msk                 (0x1U << PORT_Pin_11_Pos)               /*!< 0x00000800 */
#define PORT_Pin_11                     PORT_Pin_11_Msk

/* pin 12 */
#define PORT_Pin_12_Pos                 (12U)
#define PORT_Pin_12_Msk                 (0x1U << PORT_Pin_12_Pos)               /*!< 0x00001000 */
#define PORT_Pin_12                     PORT_Pin_12_Msk
/* pin 13 */
#define PORT_Pin_13_Pos                 (13U)
#define PORT_Pin_13_Msk                 (0x1U << PORT_Pin_13_Pos)               /*!< 0x00002000 */
#define PORT_Pin_13                     PORT_Pin_13_Msk
/* pin 14 */
#define PORT_Pin_14_Pos                 (14U)
#define PORT_Pin_14_Msk                 (0x1U << PORT_Pin_14_Pos)               /*!< 0x00004000 */
#define PORT_Pin_14                     PORT_Pin_14_Msk
/* pin 15 */
#define PORT_Pin_15_Pos                 (15U)
#define PORT_Pin_15_Msk                 (0x1U << PORT_Pin_15_Pos)               /*!< 0x00008000 */
#define PORT_Pin_15                     PORT_Pin_15_Msk

/*******************  Bit definition for PORTx_OE register  *******************/
/* use GPIO_PIN_x_Pos to specify PIN number */
#define GPIO_PORTx_OE_INPUT             (0U)
#define GPIO_PORTx_OE_OUTPUT            (1U)

/*******************  Bit definition for PORTx_FUNC register  *****************/
/* use GPIO_PORTx_FUNC_PIN_x_Pos to specify pin number */
#define GPIO_PORTx_FUNC_PORT            (0U)
#define GPIO_PORTx_FUNC_MAIN            (1U)
#define GPIO_PORTx_FUNC_ALT             (2U)
#define GPIO_PORTx_FUNC_REMAP           (3U)

/* pin 0 */
#define GPIO_PORTx_FUNC_PIN_0_Pos       (0U)
#define GPIO_PORTx_FUNC_PIN_0_Msk       (0x3U << GPIO_PORTx_FUNC_PIN_0_Pos)     /*!< 0x00000003 */
/* pin 1 */
#define GPIO_PORTx_FUNC_PIN_1_Pos       (2U)
#define GPIO_PORTx_FUNC_PIN_1_Msk       (0x3U << GPIO_PORTx_FUNC_PIN_1_Pos)     /*!< 0x0000000C */
/* pin 2 */
#define GPIO_PORTx_FUNC_PIN_2_Pos       (4U)
#define GPIO_PORTx_FUNC_PIN_2_Msk       (0x3U << GPIO_PORTx_FUNC_PIN_2_Pos)     /*!< 0x00000030 */
/* pin 3 */
#define GPIO_PORTx_FUNC_PIN_3_Pos       (6U)
#define GPIO_PORTx_FUNC_PIN_3_Msk       (0x3U << GPIO_PORTx_FUNC_PIN_3_Pos)     /*!< 0x000000C0 */

/* pin 4 */
#define GPIO_PORTx_FUNC_PIN_4_Pos       (8U)
#define GPIO_PORTx_FUNC_PIN_4_Msk       (0x3U << GPIO_PORTx_FUNC_PIN_4_Pos)     /*!< 0x00000300 */
/* pin 5 */
#define GPIO_PORTx_FUNC_PIN_5_Pos       (10U)
#define GPIO_PORTx_FUNC_PIN_5_Msk       (0x3U << GPIO_PORTx_FUNC_PIN_5_Pos)     /*!< 0x00000C00 */
/* pin 6 */
#define GPIO_PORTx_FUNC_PIN_6_Pos       (12U)
#define GPIO_PORTx_FUNC_PIN_6_Msk       (0x3U << GPIO_PORTx_FUNC_PIN_6_Pos)     /*!< 0x00003000 */
/* pin 7 */
#define GPIO_PORTx_FUNC_PIN_7_Pos       (14U)
#define GPIO_PORTx_FUNC_PIN_7_Msk       (0x3U << GPIO_PORTx_FUNC_PIN_7_Pos)     /*!< 0x0000C000 */

/* pin 8 */
#define GPIO_PORTx_FUNC_PIN_8_Pos       (16U)
#define GPIO_PORTx_FUNC_PIN_8_Msk       (0x3U << GPIO_PORTx_FUNC_PIN_8_Pos)     /*!< 0x00030000 */
/* pin 9 */
#define GPIO_PORTx_FUNC_PIN_9_Pos       (18U)
#define GPIO_PORTx_FUNC_PIN_9_Msk       (0x3U << GPIO_PORTx_FUNC_PIN_9_Pos)     /*!< 0x000C0000 */
/* pin 10 */
#define GPIO_PORTx_FUNC_PIN_10_Pos      (20U)
#define GPIO_PORTx_FUNC_PIN_10_Msk      (0x3U << GPIO_PORTx_FUNC_PIN_10_Pos)    /*!< 0x00300000 */
/* pin 11 */
#define GPIO_PORTx_FUNC_PIN_11_Pos      (22U)
#define GPIO_PORTx_FUNC_PIN_11_Msk      (0x3U << GPIO_PORTx_FUNC_PIN_11_Pos)    /*!< 0x00C00000 */

/* pin 12 */
#define GPIO_PORTx_FUNC_PIN_12_Pos      (24U)
#define GPIO_PORTx_FUNC_PIN_12_Msk      (0x3U << GPIO_PORTx_FUNC_PIN_12_Pos)    /*!< 0x03000000 */
/* pin 13 */
#define GPIO_PORTx_FUNC_PIN_13_Pos      (26U)
#define GPIO_PORTx_FUNC_PIN_13_Msk      (0x3U << GPIO_PORTx_FUNC_PIN_13_Pos)    /*!< 0x0C000000 */
/* pin 14 */
#define GPIO_PORTx_FUNC_PIN_14_Pos      (28U)
#define GPIO_PORTx_FUNC_PIN_14_Msk      (0x3U << GPIO_PORTx_FUNC_PIN_14_Pos)    /*!< 0x30000000 */
/* pin 15 */
#define GPIO_PORTx_FUNC_PIN_15_Pos      (30U)
#define GPIO_PORTx_FUNC_PIN_15_Msk      (0x3U << GPIO_PORTx_FUNC_PIN_15_Pos)    /*!< 0xC0000000 */

/*******************  Bit definition for PORTx_ANALOG register  ***************/
/* use GPIO_PIN_x_Pos to specify PIN number */
#define GPIO_PORTx_ANALOG_ANALOG        (0U)
#define GPIO_PORTx_ANALOG_DIGITAL       (1U)

/*******************  Bit definition for PORTx_PULL register  *****************/
/* use GPIO_PIN_x_Pos to specify PIN number */
#define GPIO_PORTx_PULL_NO              (0U)
#define GPIO_PORTx_PULL_DOWN            (1U)

/*******************  Bit definition for PORTx_PWR register  ******************/
/* use GPIO_PIN_x_Pos to specify PIN number */
#define GPIO_PORTx_PWR_2mA              (0U)
#define GPIO_PORTx_PWR_4mA              (1U)

/*******************  Bit definition for PORTx_SETTX register  ****************/
/* use GPIO_PIN_x to specify PIN number to be set */

/*******************  Bit definition for PORTx_CLRTX register  ****************/
/* use GPIO_PIN_x to specify PIN number to be cleared */

/*
 * ==========================================================================
 * ---------------------- CRC registers bits --------------------------------
 * ==========================================================================
 */

/*******************  Bit definition for CRC_CTRL register  *******************/
/* enable switch (0 - CRC module disabled, 1 - CRC module enabled) */
#define CRC_CTRL_CRCEN_Pos              (0U)
#define CRC_CTRL_CRCEN_Msk              (0x1U << CRC_CTRL_CRCEN_Pos)            /*!< 0x00000001 */
#define CRC_CTRL_CRCEN                  CRC_CTRL_CRCEN_Msk
/* calculation data inversion (0 - LSBF, 1 - MSBF) */
#define CRC_CTRL_DATAINV_Pos            (1U)
#define CRC_CTRL_DATAINV_Msk            (0x1U << CRC_CTRL_DATAINV_Pos)          /*!< 0x00000002 */
#define CRC_CTRL_DATAINV                CRC_CTRL_DATAINV_Msk
/* DMA request enable (0 - DMA disabled, 1 - DMA enabled) */
#define CRC_CTRL_DMAEN_Pos              (2U)
#define CRC_CTRL_DMAEN_Msk              (0x1U << CRC_CTRL_DMAEN_Pos)            /*!< 0x00000004 */
#define CRC_CTRL_DMAEN                  CRC_CTRL_DMAEN_Msk
/* Data loading size, always left aligned, 0b00 - 8 bit, 0b01 - 16 bit, 0b10 - 32 bit */
#define CRC_CTRL_DLSIZE_Pos             (3U)
#define CRC_CTRL_DLSIZE_Msk             (0x3U << CRC_CTRL_DLSIZE_Pos)           /*!< 0x00000018 */
#define CRC_CTRL_DLSIZE                 CRC_CTRL_DLSIZE_Msk
#define CRC_CTRL_DLSIZE_8BIT            (0x0U << CRC_CTRL_DLSIZE_Pos)           /*!< 0x00000000 */
#define CRC_CTRL_DLSIZE_16BIT           (0x1U << CRC_CTRL_DLSIZE_Pos)           /*!< 0x00000008 */
#define CRC_CTRL_DLSIZE_32BIT           (0x2U << CRC_CTRL_DLSIZE_Pos)           /*!< 0x00000010 */
/* Calculation step - should be less or equal to data loading size, coding the same */
#define CRC_CTRL_DCSIZE_Pos             (5U)
#define CRC_CTRL_DCSIZE_Msk             (0x3U << CRC_CTRL_DCSIZE_Pos)           /*!< 0x00000060 */
#define CRC_CTRL_DCSIZE                 CRC_CTRL_DCSIZE_Msk
#define CRC_CTRL_DCSIZE_8BIT            (0x0U << CRC_CTRL_DCSIZE_Pos)           /*!< 0x00000000 */
#define CRC_CTRL_DCSIZE_16BIT           (0x1U << CRC_CTRL_DCSIZE_Pos)           /*!< 0x00000020 */
#define CRC_CTRL_DCSIZE_32BIT           (0x2U << CRC_CTRL_DCSIZE_Pos)           /*!< 0x00000040 */

/*******************  Bit definition for CRC_CTRL register  *******************/
/* ready status, 0 - calculation ongoing, 1 - calculation complete or disabled */
#define CRC_STAT_CONVCOMP_Pos           (0U)
#define CRC_STAT_CONVCOMP_Msk           (0x1U << CRC_STAT_CONVCOMP_Pos)         /*!< 0x00000001 */
#define CRC_STAT_CONVCOMP               CRC_STAT_CONVCOMP_Msk
/* FIFO full status bit, 0 - FIFO is not full, 1 - FIFO is FULL */
#define CRC_STAT_FIFOFULL_Pos           (1U)
#define CRC_STAT_FIFOFULL_Msk           (0x1U << CRC_STAT_FIFOFULL_Pos)         /*!< 0x00000002 */
#define CRC_STAT_FIFOFULL               CRC_STAT_FIFOFULL_Msk
/* FIFO empty status bit, 0 - FIFO is not empty, 1 - FIFO is empty */
#define CRC_STAT_FIFOEMPTY_Pos          (2U)
#define CRC_STAT_FIFOEMPTY_Msk          (0x1U << CRC_STAT_FIFOEMPTY_Pos)        /*!< 0x00000004 */
#define CRC_STAT_FIFOEMPTY              CRC_STAT_FIFOEMPTY_Msk
/* FIFO overflow, 0 - no overflow, 1 - overflow detected (write 1 to clear this bit) */
#define CRC_STAT_FIFOOVER_Pos           (3U)
#define CRC_STAT_FIFOOVER_Msk           (0x1U << CRC_STAT_FIFOOVER_Pos)         /*!< 0x00000008 */
#define CRC_STAT_FIFOOVER               CRC_STAT_FIFOOVER_Msk

/*
 * ==========================================================================
 * ---------------------- L BLOCK registers bits ----------------------------
 * ==========================================================================
 */

/*******************  Bit definition for LBLOCK_SETUP register  ***************/
/* set number of R transformations */
#define LBLOCK_SETUP_SET_R_COUNT_Pos    (0U)
#define LBLOCK_SETUP_SET_R_COUNT_Msk    (0x1FU << LBLOCK_SETUP_SET_R_COUNT_Pos) /*!< 0x0000001F */
/* number of remaining R transformations */
#define LBLOCK_SETUP_GET_R_LEFT_Pos     (8U)
#define LBLOCK_SETUP_GET_R_LEFT_Msk     (0x1FU << LBLOCK_SETUP_GET_R_LEFT_Pos)  /*!< 0x00001F00 */
/* set direction */
#define LBLOCK_SETUP_SET_DIRECTION_Pos  (16U)
#define LBLOCK_SETUP_SET_DIRECTION_Msk  (0x1U << LBLOCK_SETUP_SET_DIRECTION_Pos) /*!< 0x00010000 */
#define LBLOCK_SETUP_DIRECT             (0U << LBLOCK_SETUP_SET_DIRECTION_Pos)
#define LBLOCK_SETUP_INVERSE            (1U << LBLOCK_SETUP_SET_DIRECTION_Pos)
/* read direction */
#define LBLOCK_SETUP_GET_DIRECTION_Pos  (17U)
#define LBLOCK_SETUP_GET_DIRECTION_Msk  (0x1U << LBLOCK_SETUP_GET_DIRECTION_Pos) /*!< 0x00020000 */

/*
 * ==========================================================================
 * ---------------------- P BYTE registers bits -----------------------------
 * ==========================================================================
 */

/*******************  Bit definition for PBYTE_MUX_SET register  **************/
/* IN_SEL */
#define PBYTE_MUX_SET_IN_SEL_Pos        (0U)
#define PBYTE_MUX_SET_IN_SEL_Msk        (0x3FU << PBYTE_MUX_SET_IN_SEL_Pos)     /*!< 0x0000003F */
/* OUT_SEL */
#define PBYTE_MUX_SET_OUT_SEL_Pos       (8U)
#define PBYTE_MUX_SET_OUT_SEL_Msk       (0x3FU << PBYTE_MUX_SET_OUT_SEL_Pos)    /*!< 0x00003F00 */

/*******************  Bit definition for PBYTE_MUX_VAL register  **************/
/* value */
#define PBYTE_MUX_VAL_VAL_Pos           (0U)
#define PBYTE_MUX_VAL_VAL_Msk           (0x3FU << PBYTE_MUX_VAL_VAL_Pos)        /*!< 0x0000003F */
/* sel */
#define PBYTE_MUX_VAL_SEL_Pos           (8U)
#define PBYTE_MUX_VAL_SEL_Msk           (0x3FU << PBYTE_MUX_VAL_SEL_Pos)        /*!< 0x00003F00 */

/*
 * ==========================================================================
 * ---------------------- P BIT registers bits ------------------------------
 * ==========================================================================
 */

/*******************  Bit definition for PBIT_MUX_SET register  ***************/
/* IN_SEL */
#define PBIT_MUX_SET_IN_SEL_Pos         (0U)
#define PBIT_MUX_SET_IN_SEL_Msk         (0x3FU << PBIT_MUX_SET_IN_SEL_Pos)      /*!< 0x0000003F */
/* OUT_SEL */
#define PBIT_MUX_SET_OUT_SEL_Pos        (8U)
#define PBIT_MUX_SET_OUT_SEL_Msk        (0x3FU << PBIT_MUX_SET_OUT_SEL_Pos)     /*!< 0x00003F00 */

/*******************  Bit definition for PBIT_MUX_VAL register  ***************/
/* value */
#define PBIT_MUX_VAL_VAL_Pos            (0U)
#define PBIT_MUX_VAL_VAL_Msk            (0x3FU << PBIT_MUX_VAL_VAL_Pos)         /*!< 0x0000003F */
/* sel */
#define PBIT_MUX_VAL_SEL_Pos            (8U)
#define PBIT_MUX_VAL_SEL_Msk            (0x3FU << PBIT_MUX_VAL_SEL_Pos)         /*!< 0x00003F00 */

/*
 * ==========================================================================
 * ---------------------- SENSORS registers bits ----------------------------
 * ==========================================================================
 */

/** Bit definition for SENSORS STATE, REALTIME, INTMSK, KRESMSK, ENABLE registers **/
/* light sensor */
#define SENSORS_LIGHT_Pos               (0U)
#define SENSORS_LIGHT_Msk               (0x1U << SENSORS_LIGHT_Pos)             /*!< 0x00000001 */
#define SENSORS_LIGHT                   SENSORS_LIGHT_Msk
/* EMFI 1 sensor */
#define SENSORS_EMFI1_Pos               (1U)
#define SENSORS_EMFI1_Msk               (0x1U << SENSORS_EMFI1_Pos)             /*!< 0x00000002 */
#define SENSORS_EMFI1                   SENSORS_EMFI1_Msk
/* EMFI 2 sensor */
#define SENSORS_EMFI2_Pos               (2U)
#define SENSORS_EMFI2_Msk               (0x1U << SENSORS_EMFI2_Pos)             /*!< 0x00000004 */
#define SENSORS_EMFI2                   SENSORS_EMFI2_Msk
/* EMFI 3 sensor */
#define SENSORS_EMFI3_Pos               (3U)
#define SENSORS_EMFI3_Msk               (0x1U << SENSORS_EMFI3_Pos)             /*!< 0x00000008 */
#define SENSORS_EMFI3                   SENSORS_EMFI3_Msk
/* Active mesh sensor */
#define SENSORS_MESH_Pos                (4U)
#define SENSORS_MESH_Msk                (0x1U << SENSORS_MESH_Pos)              /*!< 0x00000010 */
#define SENSORS_MESH                    SENSORS_MESH_Msk
/* all sensors mask */
#define SENSORS_MASK					(SENSORS_LIGHT | SENSORS_EMFI1 | SENSORS_EMFI2 | SENSORS_EMFI3 | SENSORS_MESH)

/*******************  Bit definition for SENSORS_MESHCNTR register  ***********/
/* mesh prescaler */
#define SENSORS_MESHCNTR_DIV_Pos        (0U)
#define SENSORS_MESHCNTR_DIV_Msk        (0x7U << SENSORS_MESHCNTR_DIV_Pos)      /*!< 0x00000007 */
#define SENSORS_MESHCNTR_DIV3           (0x0U << SENSORS_MESHCNTR_DIV_Pos)
#define SENSORS_MESHCNTR_DIV4           (0x1U << SENSORS_MESHCNTR_DIV_Pos)
#define SENSORS_MESHCNTR_DIV8           (0x2U << SENSORS_MESHCNTR_DIV_Pos)
#define SENSORS_MESHCNTR_DIV16          (0x3U << SENSORS_MESHCNTR_DIV_Pos)
#define SENSORS_MESHCNTR_DIV32          (0x4U << SENSORS_MESHCNTR_DIV_Pos)
#define SENSORS_MESHCNTR_DIV64          (0x5U << SENSORS_MESHCNTR_DIV_Pos)
#define SENSORS_MESHCNTR_DIV128         (0x6U << SENSORS_MESHCNTR_DIV_Pos)
#define SENSORS_MESHCNTR_DIV256         (0x7U << SENSORS_MESHCNTR_DIV_Pos)

/*
 * ==========================================================================
 * ---------------------- CLK_MEAUSRE registers bits ------------------------
 * ==========================================================================
 */

/*******************  Bit definition for CLK_MEASURE_CNTR_STAT register  ******/
/* enable switch (0 - disabled, 1 - enabled) */
#define CLK_MEASURE_CNTR_STAT_EN_Pos    (0U)
#define CLK_MEASURE_CNTR_STAT_EN_Msk    (0x1U << CLK_MEASURE_CNTR_STAT_EN_Pos)  /*!< 0x00000001 */
#define CLK_MEASURE_CNTR_STAT_EN        CLK_MEASURE_CNTR_STAT_EN_Msk
/* interrupt */
#define CLK_MEASURE_CNTR_STAT_INT_Pos   (4U)
#define CLK_MEASURE_CNTR_STAT_INT_Msk   (0x1U << CLK_MEASURE_CNTR_STAT_INT_Pos) /*!< 0x00000010 */
#define CLK_MEASURE_CNTR_STAT_INT       CLK_MEASURE_CNTR_STAT_INT_Msk
/* key reset */
#define CLK_MEASURE_CNTR_STAT_RST_Pos   (5U)
#define CLK_MEASURE_CNTR_STAT_RST_Msk   (0x1U << CLK_MEASURE_CNTR_STAT_RST_Pos) /*!< 0x00000020 */
#define CLK_MEASURE_CNTR_STAT_RST       CLK_MEASURE_CNTR_STAT_RST_Msk

/*******************  Bit definition for CLK_MEASURE_ALRM_RST register  *******/
/* maximum shift 1 before key reset */
#define CLK_MEASURE_ALRM_RST_REG0_Pos   (0U)
#define CLK_MEASURE_ALRM_RST_REG0_Msk   (0xFFFFU << CLK_MEASURE_ALRM_RST_REG0_Pos) /*!< 0x0000FFFF */
/* maximum shift 0 before key reset */
#define CLK_MEASURE_ALRM_RST_REG2_Pos   (16U)
#define CLK_MEASURE_ALRM_RST_REG2_Msk   (0xFFFFU << CLK_MEASURE_ALRM_RST_REG2_Pos) /*!< 0xFFFF0000 */

/*******************  Bit definition for CLK_MEASURE_ALRM_INT register  *******/
/* maximum shift 1 before interrupt */
#define CLK_MEASURE_ALRM_INT_REG1_Pos   (0U)
#define CLK_MEASURE_ALRM_INT_REG1_Msk   (0xFFFFU << CLK_MEASURE_ALRM_INT_REG1_Pos) /*!< 0x0000FFFF */
/* maximum shift 0 before interrupt */
#define CLK_MEASURE_ALRM_INT_REG3_Pos   (16U)
#define CLK_MEASURE_ALRM_INT_REG3_Msk   (0xFFFFU << CLK_MEASURE_ALRM_INT_REG3_Pos) /*!< 0xFFFF0000 */

/*******************  Bit definition for CLK_MEASURE_PREG0 register  **********/
/* counter for REG1 */
#define CLK_MEASURE_PREG0_PREG1_Pos     (0U)
#define CLK_MEASURE_PREG0_PREG1_Msk     (0xFFFFU << CLK_MEASURE_PREG0_PREG1_Pos) /*!< 0x0000FFFF */
/* counter for REG0 */
#define CLK_MEASURE_PREG0_PREG0_Pos     (16U)
#define CLK_MEASURE_PREG0_PREG0_Msk     (0xFFFFU << CLK_MEASURE_PREG0_PREG0_Pos) /*!< 0xFFFF0000 */

/*******************  Bit definition for CLK_MEASURE_PREG1 register  **********/
/* counter for REG3 */
#define CLK_MEASURE_PREG1_PREG3_Pos     (0U)
#define CLK_MEASURE_PREG1_PREG3_Msk     (0xFFFFU << CLK_MEASURE_PREG1_PREG3_Pos) /*!< 0x0000FFFF */
/* counter for REG2 */
#define CLK_MEASURE_PREG1_PREG2_Pos     (16U)
#define CLK_MEASURE_PREG1_PREG2_Msk     (0xFFFFU << CLK_MEASURE_PREG1_PREG2_Pos) /*!< 0xFFFF0000 */

/*******************  Bit definition for SENSORS_MESHCNTR register  ***********/

/*
 * ==========================================================================
 * ---------------------- RANDOM registers bits -----------------------------
 * ==========================================================================
 */

/*******************  Bit definition for RANDOM_STAT register  ****************/
/* force enable */
#define RANDOM_STAT_FORCEEN_Pos         (0U)
#define RANDOM_STAT_FORCEEN_Msk         (0x1U << RANDOM_STAT_FORCEEN_Pos)       /*!< 0x00000001 */
#define RANDOM_STAT_FORCEEN             RANDOM_STAT_FORCEEN_Msk
/* enable flag */
#define RANDOM_STAT_ENABLEF_Pos         (1U)
#define RANDOM_STAT_ENABLEF_Msk         (0x1U << RANDOM_STAT_ENABLEF_Pos)       /*!< 0x00000002 */
#define RANDOM_STAT_ENABLEF             RANDOM_STAT_ENABLEF_Msk
/* busy flag */
#define RANDOM_STAT_BUSYF_Pos           (2U)
#define RANDOM_STAT_BUSYF_Msk           (0x1U << RANDOM_STAT_BUSYF_Pos)         /*!< 0x00000004 */
#define RANDOM_STAT_BUSYF               RANDOM_STAT_BUSYF_Msk
/* unread data flag */
#define RANDOM_STAT_UNREADF_Pos         (3U)
#define RANDOM_STAT_UNREADF_Msk         (0x1U << RANDOM_STAT_UNREADF_Pos)       /*!< 0x00000008 */
#define RANDOM_STAT_UNREADF             RANDOM_STAT_UNREADF_Msk
/* generators activation mask */
#define RANDOM_STAT_MASK_Pos            (4U)
#define RANDOM_STAT_MASK_Msk            (0x3U << RANDOM_STAT_MASK_Pos)          /*!< 0x00000030 */
#define RANDOM_STAT_MASK_GEN0       	(0x1U << RANDOM_STAT_MASK_Pos)
#define RANDOM_STAT_MASK_GEN1   	    (0x2U << RANDOM_STAT_MASK_Pos)
#define RANDOM_STAT_MASK_BOTHGEN		RANDOM_STAT_MASK_Msk
/* generation mode */
#define RANDOM_STAT_WORK_MODE_Pos       (8U)
#define RANDOM_STAT_WORK_MODE_Msk       (0x3U << RANDOM_STAT_WORK_MODE_Pos)     /*!< 0x00000300 */
#define RANDOM_STAT_WORK_MODE_STOP      (0x0U << RANDOM_STAT_WORK_MODE_Pos)
#define RANDOM_STAT_WORK_MODE_ONCE      (0x1U << RANDOM_STAT_WORK_MODE_Pos)
#define RANDOM_STAT_WORK_MODE_SINGLE    (0x2U << RANDOM_STAT_WORK_MODE_Pos)
#define RANDOM_STAT_WORK_MODE_CONT      (0x3U << RANDOM_STAT_WORK_MODE_Pos)
/* remaining bits count */
#define RANDOM_STAT_BIT_CN_Pos          (12U)
#define RANDOM_STAT_BIT_CN_Msk          (0x3FU << RANDOM_STAT_BIT_CN_Pos)       /*!< 0x0003F000 */

/*******************  Bit definition for RANDOM_INT register  *****************/
/* interrupt enable */
#define RANDOM_INT_INT_EN_Pos           (0U)
#define RANDOM_INT_INT_EN_Msk           (0x1U << RANDOM_INT_INT_EN_Pos)         /*!< 0x00000001 */
#define RANDOM_INT_INT_EN               RANDOM_INT_INT_EN_Msk
/* unread data flag */
#define RANDOM_INT_UNREADF_Pos          (1U)
#define RANDOM_INT_UNREADF_Msk          (0x1U << RANDOM_INT_UNREADF_Pos)        /*!< 0x00000002 */
#define RANDOM_INT_UNREADF              RANDOM_INT_UNREADF_Msk

/*******************  Bit definition for RANDOM_CLKDIV register  **************/
/* clock divisor F = RANDOM_CLK / (2 * (DIV + 1)); F ~ 500 kHz */
#define RANDOM_CLKDIV_DIV_Pos           (0U)
#define RANDOM_CLKDIV_DIV_Msk           (0xFFFFU << RANDOM_CLKDIV_DIV_Pos)      /*!< 0x0000FFFF */

/*
 * ==========================================================================
 * ---------------------- ISO7816 registers bits ----------------------------
 * ==========================================================================
 */

/*******************  Bit definition for ISO7816_SR register  ****************/
/* parity error */
#define ISO7816_SR_PE_Pos               (0U)
#define ISO7816_SR_PE_Msk               (0x1U << ISO7816_SR_PE_Pos)             /*!< 0x00000001 */
#define ISO7816_SR_PE                   ISO7816_SR_PE_Msk
/* framing error */
#define ISO7816_SR_FE_Pos               (1U)
#define ISO7816_SR_FE_Msk               (0x1U << ISO7816_SR_FE_Pos)             /*!< 0x00000002 */
#define ISO7816_SR_FE                   ISO7816_SR_FE_Msk
/* noise detected flag */
#define ISO7816_SR_NE_Pos               (2U)
#define ISO7816_SR_NE_Msk               (0x1U << ISO7816_SR_NE_Pos)             /*!< 0x00000004 */
#define ISO7816_SR_NE                   ISO7816_SR_NE_Msk
/* overrun error */
#define ISO7816_SR_ORE_Pos              (3U)
#define ISO7816_SR_ORE_Msk              (0x1U << ISO7816_SR_ORE_Pos)            /*!< 0x00000008 */
#define ISO7816_SR_ORE                  ISO7816_SR_ORE_Msk
/* idle */
#define ISO7816_SR_IDLE_Pos             (4U)
#define ISO7816_SR_IDLE_Msk             (0x1U << ISO7816_SR_IDLE_Pos)           /*!< 0x00000010 */
#define ISO7816_SR_IDLE                 ISO7816_SR_IDLE_Msk
/* read data register is not empty */
#define ISO7816_SR_RXNE_Pos             (5U)
#define ISO7816_SR_RXNE_Msk             (0x1U << ISO7816_SR_RXNE_Pos)           /*!< 0x00000020 */
#define ISO7816_SR_RXNE                 ISO7816_SR_RXNE_Msk
/* transmission complete */
#define ISO7816_SR_TC_Pos               (6U)
#define ISO7816_SR_TC_Msk               (0x1U << ISO7816_SR_TC_Pos)             /*!< 0x00000040 */
#define ISO7816_SR_TC                   ISO7816_SR_TC_Msk
/* transmit data register empty */
#define ISO7816_SR_TXE_Pos              (7U)
#define ISO7816_SR_TXE_Msk              (0x1U << ISO7816_SR_TXE_Pos)            /*!< 0x00000080 */
#define ISO7816_SR_TXE                  ISO7816_SR_TXE_Msk
/* CTS flag */
#define ISO7816_SR_CTS_Pos              (9U)
#define ISO7816_SR_CTS_Msk              (0x1U << ISO7816_SR_CTS_Pos)            /*!< 0x00000200 */
#define ISO7816_SR_CTS                  ISO7816_SR_CTS_Msk

/*******************  Bit definition for ISO7816_DR register  ***************/
/* data mask */
#define ISO7816_DR_Msk					(0x1FFU)

/*******************  Bit definition for ISO7816_BRR register  ***************/
/* fraction */
#define ISO7816_BRR_FRAC_Pos            (0U)
#define ISO7816_BRR_FRAC_Msk            (0xFU << ISO7816_BRR_FRAC_Pos)          /*!< 0x0000000F */
/* mantissa */
#define ISO7816_BRR_MANT_Pos            (4U)
#define ISO7816_BRR_MANT_Msk            (0xFFFU << ISO7816_BRR_MANT_Pos)        /*!< 0x0000FFF0 */

/*******************  Bit definition for ISO7816_CR1 register  ***************/
/* send break */
#define ISO7816_CR1_SBK_Pos             (0U)
#define ISO7816_CR1_SBK_Msk             (0x1U << ISO7816_CR1_SBK_Pos)           /*!< 0x00000001 */
#define ISO7816_CR1_SBK                 ISO7816_CR1_SBK_Msk
/* receiver wakeup */
#define ISO7816_CR1_RWU_Pos             (1U)
#define ISO7816_CR1_RWU_Msk             (0x1U << ISO7816_CR1_RWU_Pos)           /*!< 0x00000002 */
#define ISO7816_CR1_RWU                 ISO7816_CR1_RWU_Msk
/* receiver enable */
#define ISO7816_CR1_RE_Pos              (2U)
#define ISO7816_CR1_RE_Msk              (0x1U << ISO7816_CR1_RE_Pos)            /*!< 0x00000004 */
#define ISO7816_CR1_RE                  ISO7816_CR1_RE_Msk
/* transmitter enable */
#define ISO7816_CR1_TE_Pos              (3U)
#define ISO7816_CR1_TE_Msk              (0x1U << ISO7816_CR1_TE_Pos)            /*!< 0x00000008 */
#define ISO7816_CR1_TE                  ISO7816_CR1_TE_Msk
/* IDLE interrupt enable */
#define ISO7816_CR1_IDLEIE_Pos          (4U)
#define ISO7816_CR1_IDLEIE_Msk          (0x1U << ISO7816_CR1_IDLEIE_Pos)        /*!< 0x00000010 */
#define ISO7816_CR1_IDLEIE              ISO7816_CR1_IDLEIE_Msk
/* RXNE interrupt enable */
#define ISO7816_CR1_RXNEIE_Pos          (5U)
#define ISO7816_CR1_RXNEIE_Msk          (0x1U << ISO7816_CR1_RXNEIE_Pos)        /*!< 0x00000020 */
#define ISO7816_CR1_RXNEIE              ISO7816_CR1_RXNEIE_Msk
/* TC interrupt enable */
#define ISO7816_CR1_TCIE_Pos            (6U)
#define ISO7816_CR1_TCIE_Msk            (0x1U << ISO7816_CR1_TCIE_Pos)          /*!< 0x00000040 */
#define ISO7816_CR1_TCIE                ISO7816_CR1_TCIE_Msk
/* TXE interrupt enable */
#define ISO7816_CR1_TXEIE_Pos           (7U)
#define ISO7816_CR1_TXEIE_Msk           (0x1U << ISO7816_CR1_TXEIE_Pos)         /*!< 0x00000080 */
#define ISO7816_CR1_TXEIE               ISO7816_CR1_TXEIE_Msk
/* PE interrupt enable */
#define ISO7816_CR1_PEIE_Pos            (8U)
#define ISO7816_CR1_PEIE_Msk            (0x1U << ISO7816_CR1_PEIE_Pos)          /*!< 0x00000100 */
#define ISO7816_CR1_PEIE                ISO7816_CR1_PEIE_Msk
/* parity selection */
#define ISO7816_CR1_PS_Pos              (9U)
#define ISO7816_CR1_PS_Msk              (0x1U << ISO7816_CR1_PS_Pos)            /*!< 0x00000200 */
#define ISO7816_CR1_PS_EVEN             (0x0U << ISO7816_CR1_PS_Pos)
#define ISO7816_CR1_PS_ODD              (0x1U << ISO7816_CR1_PS_Pos)
/* parity control */
#define ISO7816_CR1_PC_Pos              (10U)
#define ISO7816_CR1_PC_Msk              (0x1U << ISO7816_CR1_PC_Pos)            /*!< 0x00000400 */
#define ISO7816_CR1_PC_ENABLED          ISO7816_CR1_PC_Msk
/* wakeup method */
#define ISO7816_CR1_WAKE_Pos            (11U)
#define ISO7816_CR1_WAKE_Msk            (0x1U << ISO7816_CR1_WAKE_Pos)          /*!< 0x00000800 */
#define ISO7816_CR1_WAKE_IDLE           (0x0U << ISO7816_CR1_WAKE_Pos)
#define ISO7816_CR1_WAKE_ADDR           (0x1U << ISO7816_CR1_WAKE_Pos)
/* word length */
#define ISO7816_CR1_M_Pos               (12U)
#define ISO7816_CR1_M_Msk               (0x1U << ISO7816_CR1_M_Pos)             /*!< 0x00001000 */
#define ISO7816_CR1_M_8BITS             (0x0U << ISO7816_CR1_M_Pos)
#define ISO7816_CR1_M_9BITS             (0x1U << ISO7816_CR1_M_Pos)
/* USART enable */
#define ISO7816_CR1_UE_Pos              (13U)
#define ISO7816_CR1_UE_Msk              (0x1U << ISO7816_CR1_UE_Pos)            /*!< 0x00002000 */
#define ISO7816_CR1_UE                  ISO7816_CR1_UE_Msk
/* oversample 8 bit */
#define ISO7816_CR1_OVER8_Pos           (15U)
#define ISO7816_CR1_OVER8_Msk           (0x1U << ISO7816_CR1_OVER8_Pos)         /*!< 0x00008000 */
#define ISO7816_CR1_OVER8               ISO7816_CR1_OVER8_Msk

/*******************  Bit definition for ISO7816_CR2 register  ***************/
/* USART address for multiprocessor communication */
#define ISO7816_CR2_ADD_Pos             (0U)
#define ISO7816_CR2_ADD_Msk             (0xFU << ISO7816_CR2_ADD_Pos)           /*!< 0x0000000F */
/* last bit clock pulse */
#define ISO7816_CR2_LBCL_Pos            (8U)
#define ISO7816_CR2_LBCL_Msk            (0x1U << ISO7816_CR2_LBCL_Pos)          /*!< 0x00000100 */
#define ISO7816_CR2_LBCL                ISO7816_CR2_LBCL_Msk
/* clock phase */
#define ISO7816_CR2_CPHA_Pos            (9U)
#define ISO7816_CR2_CPHA_Msk            (0x1U << ISO7816_CR2_CPHA_Pos)          /*!< 0x00000200 */
#define ISO7816_CR2_CPHA                ISO7816_CR2_CPHA_Msk
/* clock polarity */
#define ISO7816_CR2_CPOL_Pos            (10U)
#define ISO7816_CR2_CPOL_Msk            (0x1U << ISO7816_CR2_CPOL_Pos)          /*!< 0x00000400 */
#define ISO7816_CR2_CPOL                ISO7816_CR2_CPOL_Msk
/* clock enable */
#define ISO7816_CR2_CLKEN_Pos           (11U)
#define ISO7816_CR2_CLKEN_Msk           (0x1U << ISO7816_CR2_CLKEN_Pos)         /*!< 0x00000800 */
#define ISO7816_CR2_CLKEN               ISO7816_CR2_CLKEN_Msk
/* stop bits count */
#define ISO7816_CR2_STOP_Pos            (12U)
#define ISO7816_CR2_STOP_Msk            (0x3U << ISO7816_CR2_STOP_Pos)          /*!< 0x00003000 */
#define ISO7816_CR2_STOP_1_STOPBIT      (0x0U << ISO7816_CR2_STOP_Pos)
#define ISO7816_CR2_STOP_0_5_STOPBIT    (0x1U << ISO7816_CR2_STOP_Pos)
#define ISO7816_CR2_STOP_2_STOPBIT      (0x2U << ISO7816_CR2_STOP_Pos)
#define ISO7816_CR2_STOP_1_5_STOPBIT    (0x3U << ISO7816_CR2_STOP_Pos)

/*******************  Bit definition for ISO7816_CR3 register  ***************/
/* error interrupt enable */
#define ISO7816_CR3_EIE_Pos             (0U)
#define ISO7816_CR3_EIE_Msk             (0x1U << ISO7816_CR3_EIE_Pos)           /*!< 0x00000001 */
#define ISO7816_CR3_EIE                 ISO7816_CR3_EIE_Msk
/* half-duplex selection */
#define ISO7816_CR3_HDSEL_Pos           (3U)
#define ISO7816_CR3_HDSEL_Msk           (0x1U << ISO7816_CR3_HDSEL_Pos)         /*!< 0x00000008 */
#define ISO7816_CR3_HDSEL               ISO7816_CR3_HDSEL_Msk
/* smart-card NACK */
#define ISO7816_CR3_NACK_Pos			(4U)
#define ISO7816_CR3_NACK_Msk			(0x1U << ISO7816_CR3_NACK_Pos)			/*!< 0x00000010 */
#define ISO7816_CR3_NACK				ISO7816_CR3_NACK_Msk
/* smart-card mode enable */
#define ISO7816_CR3_SCEN_Pos            (5U)
#define ISO7816_CR3_SCEN_Msk            (0x1U << ISO7816_CR3_SCEN_Pos)         /*!< 0x00000020 */
#define ISO7816_CR3_SCEN                ISO7816_CR3_SCEN_Msk
/* RTS enable */
#define ISO7816_CR3_RTSE_Pos            (8U)
#define ISO7816_CR3_RTSE_Msk            (0x1U << ISO7816_CR3_RTSE_Pos)          /*!< 0x00000100 */
#define ISO7816_CR3_RTSE                ISO7816_CR3_RTSE_Msk
/* CTS enable */
#define ISO7816_CR3_CTSE_Pos            (9U)
#define ISO7816_CR3_CTSE_Msk            (0x1U << ISO7816_CR3_CTSE_Pos)          /*!< 0x00000200 */
#define ISO7816_CR3_CTSE                ISO7816_CR3_CTSE_Msk
/* CTS interrupt enable */
#define ISO7816_CR3_CTSIE_Pos           (10U)
#define ISO7816_CR3_CTSIE_Msk           (0x1U << ISO7816_CR3_CTSIE_Pos)         /*!< 0x00000400 */
#define ISO7816_CR3_CTSIE               ISO7816_CR3_CTSIE_Msk
/* one sample bit method */
#define ISO7816_CR3_ONEBIT_Pos          (11U)
#define ISO7816_CR3_ONEBIT_Msk          (0x1U << ISO7816_CR3_ONEBIT_Pos)        /*!< 0x00000800 */
#define ISO7816_CR3_ONEBIT              ISO7816_CR3_ONEBIT_Msk

/*******************  Bit definition for ISO7816_GTPR register  **************/
/* prescaler */
#define ISO7816_GTPR_PSC_Pos            (0U)
#define ISO7816_GTPR_PSC_Msk            (0x1FU << ISO7816_GTPR_PSC_Pos)         /*!< 0x0000001F */
/* guard time */
#define ISO7816_GTPR_GT_Pos             (8U)
#define ISO7816_GTPR_GT_Msk             (0xFFU << ISO7816_GTPR_GT_Pos)          /*!< 0x0000FF00 */

/*
 * ==========================================================================
 * ---------------------- OTP registers bits --------------------------------
 * ==========================================================================
 */

/*******************  Bit definition for OTP_STAT_CTRL register  *************/
/* mode of the operation */
#define OTP_STAT_CTRL_FSM_STATE_Pos     (0U)
#define OTP_STAT_CTRL_FSM_STATE_Msk     (0x7U << OTP_STAT_CTRL_FSM_STATE_Pos)   /*!< 0x00000007 */
#define OTP_STAT_CTRL_FSM_STATE_IDLE    (0x0U << OTP_STAT_CTRL_FSM_STATE_Pos)
#define OTP_STAT_CTRL_FSM_STATE_INIT    (0x1U << OTP_STAT_CTRL_FSM_STATE_Pos)
#define OTP_STAT_CTRL_FSM_STATE_READY   (0x2U << OTP_STAT_CTRL_FSM_STATE_Pos)
#define OTP_STAT_CTRL_FSM_STATE_REGREAD (0x3U << OTP_STAT_CTRL_FSM_STATE_Pos)
#define OTP_STAT_CTRL_FSM_STATE_BUSREAD (0x4U << OTP_STAT_CTRL_FSM_STATE_Pos)
#define OTP_STAT_CTRL_FSM_STATE_WRITE   (0x5U << OTP_STAT_CTRL_FSM_STATE_Pos)
#define OTP_STAT_CTRL_FSM_STATE_DIRECT  (0x6U << OTP_STAT_CTRL_FSM_STATE_Pos)
/* busy flag */
#define OTP_STAT_CTRL_BUSYF_Pos         (3U)
#define OTP_STAT_CTRL_BUSYF_Msk         (0x1U << OTP_STAT_CTRL_BUSYF_Pos)       /*!< 0x00000008 */
#define OTP_STAT_CTRL_BUSYF             OTP_STAT_CTRL_BUSYF_Msk
/* OTP all lock */
#define OTP_STAT_CTRL_LOCKF_Pos         (4U)
#define OTP_STAT_CTRL_LOCKF_Msk         (0x1U << OTP_STAT_CTRL_LOCKF_Pos)       /*!< 0x00000010 */
#define OTP_STAT_CTRL_LOCKF             OTP_STAT_CTRL_LOCKF_Msk
/* OTP partial lock */
#define OTP_STAT_CTRL_PLOCKF_Pos        (5U)
#define OTP_STAT_CTRL_PLOCKF_Msk        (0x1U << OTP_STAT_CTRL_PLOCKF_Pos)      /*!< 0x00000020 */
#define OTP_STAT_CTRL_PLOCKF            OTP_STAT_CTRL_PLOCKF_Msk
/* RW error flag */
#define OTP_STAT_CTRL_RWERRORF_Pos      (6U)
#define OTP_STAT_CTRL_RWERRORF_Msk      (0x1U << OTP_STAT_CTRL_RWERRORF_Pos)    /*!< 0x00000040 */
#define OTP_STAT_CTRL_RWERRORF          OTP_STAT_CTRL_RWERRORF_Msk
/* test crc */
#define OTP_STAT_CTRL_TESTCRC_Pos       (7U)
#define OTP_STAT_CTRL_TESTCRC_Msk       (0x1U << OTP_STAT_CTRL_TESTCRC_Pos)     /*!< 0x00000080 */
#define OTP_STAT_CTRL_TESTCRC           OTP_STAT_CTRL_TESTCRC_Msk
/* write protection crc */
#define OTP_STAT_CTRL_WRITE_PCRC_Pos    (8U)
#define OTP_STAT_CTRL_WRITE_PCRC_Msk    (0x1U << OTP_STAT_CTRL_WRITE_PCRC_Pos)  /*!< 0x00000100 */
#define OTP_STAT_CTRL_WRITE_PCRC        OTP_STAT_CTRL_WRITE_PCRC_Msk
/* read protection crc */
#define OTP_STAT_CTRL_READ_PCRC_Pos     (9U)
#define OTP_STAT_CTRL_READ_PCRC_Msk     (0x1U << OTP_STAT_CTRL_READ_PCRC_Pos)   /*!< 0x00000200 */
#define OTP_STAT_CTRL_READ_PCRC         OTP_STAT_CTRL_READ_PCRC_Msk
/* direct control enable */
#define OTP_STAT_CTRL_DIR_EN_Pos        (10U)
#define OTP_STAT_CTRL_DIR_EN_Msk        (0x1U << OTP_STAT_CTRL_DIR_EN_Pos)      /*!< 0x00000400 */
#define OTP_STAT_CTRL_DIR_EN            OTP_STAT_CTRL_DIR_EN_Msk
/* ack of direct control enable */
#define OTP_STAT_CTRL_DIR_ACK_Pos       (11U)
#define OTP_STAT_CTRL_DIR_ACK_Msk       (0x1U << OTP_STAT_CTRL_DIR_ACK_Pos)     /*!< 0x00000800 */
#define OTP_STAT_CTRL_DIR_ACK           OTP_STAT_CTRL_DIR_ACK_Msk
/* direct control error */
#define OTP_STAT_CTRL_DIR_ERR_Pos       (12U)
#define OTP_STAT_CTRL_DIR_ERR_Msk       (0x1U << OTP_STAT_CTRL_DIR_ERR_Pos)     /*!< 0x00001000 */
#define OTP_STAT_CTRL_DIR_ERR           OTP_STAT_CTRL_DIR_ERR_Msk

/*******************  Bit definition for OTP_OTP_STAT register  *************/
/* OTP state */
#define OTP_OTP_STAT_FMS_STATE_Pos      (0U)
#define OTP_OTP_STAT_FMS_STATE_Msk      (0x1FU << OTP_OTP_STAT_FMS_STATE_Pos)   /*!< 0x0000001F */
#define OTP_OTP_STAT_FMS_STATE_IDLE     (0U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_SLEEP    (1U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_RSTPREP  (2U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_RST      (3U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_RSTDONE  (4U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_ACTIVE   (5U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_PAUSE    (6U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_RDPREP   (7U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_RD       (8U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_RDDONE   (9U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_WRPREP   (10U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_WRSAVE   (11U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_WRSAVED  (12U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_PROGPREP (13U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_PUMPPREP (14U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_PROG     (15U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_PUMPDACT (16U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_PROGDONE (17U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_WRDONE   (18U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_DIRPREP  (19U << OTP_OTP_STAT_FMS_STATE_Pos)
#define OTP_OTP_STAT_FMS_STATE_DIRMODE  (20U << OTP_OTP_STAT_FMS_STATE_Pos)
/* OTP lock */
#define OTP_OTP_STAT_LOCK_Pos           (6U)
#define OTP_OTP_STAT_LOCK_Msk           (0x1U << OTP_OTP_STAT_LOCK_Pos)         /*!< 0x00000040 */
#define OTP_OTP_STAT_LOCK               OTP_OTP_STAT_LOCK_Msk
/* OTP busy */
#define OTP_OTP_STAT_BUSY_Pos           (7U)
#define OTP_OTP_STAT_BUSY_Msk           (0x1U << OTP_OTP_STAT_BUSY_Pos)         /*!< 0x00000080 */
#define OTP_OTP_STAT_BUSY               OTP_OTP_STAT_BUSY_Msk

/*******************  Bit definition for OTP_DELAY0 register  ***************/
/* delay for 20 ns pause */
#define OTP_DELAY0_20NS_Pos             (0U)
#define OTP_DELAY0_20NS_Msk             (0xFU << OTP_DELAY0_20NS_Pos)           /*!< 0x0000000F */
/* delay for 70 ns pause */
#define OTP_DELAY0_70NS_Pos             (4U)
#define OTP_DELAY0_70NS_Msk             (0xFU << OTP_DELAY0_70NS_Pos)           /*!< 0x000000F0 */
/* delay for 50 ns pause */
#define OTP_DELAY0_50NS_Pos             (8U)
#define OTP_DELAY0_50NS_Msk             (0xFU << OTP_DELAY0_50NS_Pos)           /*!< 0x00000F00 */
/* delay for 1 us pause */
#define OTP_DELAY0_1US_Pos              (16U)
#define OTP_DELAY0_1US_Msk              (0xFFU << OTP_DELAY0_1US_Pos)           /*!< 0x00FF0000 */

/*******************  Bit definition for OTP_DELAY1 register  ***************/
/* delay for 16 us pause */
#define OTP_DELAY1_16US_Pos             (0U)
#define OTP_DELAY1_16US_Msk             (0xFFFFU << OTP_DELAY1_16US_Pos)        /*!< 0x0000FFFF */

/*******************  Bit definition for OTP_RW_CMD register  ****************/
/* address */
#define OTP_RW_CMD_ADDR_Pos             (0U)
#define OTP_RW_CMD_ADDR_Msk             (0xFFFFU << OTP_RW_CMD_ADDR_Pos)        /*!< 0x0000FFFF */
/* data to be write (1-s MASK) */
#define OTP_RW_CMD_DATA_Pos             (24U)
#define OTP_RW_CMD_DATA_Msk             (0x1U << OTP_RW_CMD_DATA_Pos)           /*!< 0x01000000 */
#define OTP_RW_CMD_DATA0				OTP_RW_CMD_DATA_Msk
/* read data */
#define OTP_RW_CMD_READ_Pos             (28U)
#define OTP_RW_CMD_READ_Msk             (0x1U << OTP_RW_CMD_READ_Pos)           /*!< 0x10000000 */
#define OTP_RW_CMD_READ                 OTP_RW_CMD_READ_Msk
/* write data */
#define OTP_RW_CMD_WRITE_Pos            (29U)
#define OTP_RW_CMD_WRITE_Msk            (0x1U << OTP_RW_CMD_WRITE_Pos)          /*!< 0x20000000 */
#define OTP_RW_CMD_WRITE                OTP_RW_CMD_WRITE_Msk
/* read-write error */
#define OTP_RW_CMD_RWERROR_Pos          (31U)
#define OTP_RW_CMD_RWERROR_Msk          (0x1U << OTP_RW_CMD_RWERROR_Pos)        /*!< 0x80000000 */
#define OTP_RW_CMD_RWERROR              OTP_RW_CMD_RWERROR_Msk

/*******************  Bit definition for OTP_DIR_CTRL register  **************/
/* web signal in direct mode */
#define OTP_DIR_CTRL_WEB_Pos            (0U)
#define OTP_DIR_CTRL_WEB_Msk            (0x1U << OTP_DIR_CTRL_WEB_Pos)          /*!< 0x00000001 */
#define OTP_DIR_CTRL_WEB                OTP_DIR_CTRL_WEB_Msk
/* rstb signal in direct mode */
#define OTP_DIR_CTRL_RSTB_Pos           (1U)
#define OTP_DIR_CTRL_RSTB_Msk           (0x1U << OTP_DIR_CTRL_RSTB_Pos)         /*!< 0x00000002 */
#define OTP_DIR_CTRL_RSTB               OTP_DIR_CTRL_RSTB_Msk
/* readen signal in direct mode */
#define OTP_DIR_CTRL_READEN_Pos         (2U)
#define OTP_DIR_CTRL_READEN_Msk         (0x1U << OTP_DIR_CTRL_READEN_Pos)       /*!< 0x00000004 */
#define OTP_DIR_CTRL_READEN             OTP_DIR_CTRL_READEN_Msk
/* pgmen signal in direct mode */
#define OTP_DIR_CTRL_PGMEN_Pos          (3U)
#define OTP_DIR_CTRL_PGMEN_Msk          (0x1U << OTP_DIR_CTRL_PGMEN_Pos)        /*!< 0x00000008 */
#define OTP_DIR_CTRL_PGMEN              OTP_DIR_CTRL_PGMEN_Msk
/* dle signal in direct mode */
#define OTP_DIR_CTRL_DLE_Pos            (4U)
#define OTP_DIR_CTRL_DLE_Msk            (0x1U << OTP_DIR_CTRL_DLE_Pos)          /*!< 0x00000010 */
#define OTP_DIR_CTRL_DLE                OTP_DIR_CTRL_DLE_Msk
/* DIN 0 signal in direct mode */
#define OTP_DIR_CTRL_DIN0_Pos           (5U)
#define OTP_DIR_CTRL_DIN0_Msk           (0x1U << OTP_DIR_CTRL_DIN0_Pos)         /*!< 0x00000020 */
#define OTP_DIR_CTRL_DIN0               OTP_DIR_CTRL_DIN0_Msk
/* CPUMPEN signal in direct mode */
#define OTP_DIR_CTRL_CPUMPEN_Pos        (6U)
#define OTP_DIR_CTRL_CPUMPEN_Msk        (0x1U << OTP_DIR_CTRL_CPUMPEN_Pos)      /*!< 0x00000040 */
#define OTP_DIR_CTRL_CPUMPEN            OTP_DIR_CTRL_CPUMPEN_Msk
/* CLE signal in direct mode */
#define OTP_DIR_CTRL_CLE_Pos            (7U)
#define OTP_DIR_CTRL_CLE_Msk            (0x1U << OTP_DIR_CTRL_CLE_Pos)          /*!< 0x00000080 */
#define OTP_DIR_CTRL_CLE                OTP_DIR_CTRL_CLE_Msk
/* CEB signal in direct mode */
#define OTP_DIR_CTRL_CEB_Pos            (8U)
#define OTP_DIR_CTRL_CLE_Msk            (0x1U << OTP_DIR_CTRL_CLE_Pos)          /*!< 0x00000100 */
#define OTP_DIR_CTRL_CLE                OTP_DIR_CTRL_CLE_Msk
/* A signal in direct mode */
#define OTP_DIR_CTRL_A_Pos              (9U)
#define OTP_DIR_CTRL_A_Msk              (0x1U << OTP_DIR_CTRL_A_Pos)            /*!< 0x00000200 */
#define OTP_DIR_CTRL_A                  OTP_DIR_CTRL_A_Msk

/*******************  Bit definition for OTP_DIR_DATA register  **************/
/* read out data */
#define OTP_DIR_DATA_Pos                (0U)
#define OTP_DIR_DATA_Msk                (0x1U << OTP_DIR_DATA_Pos)              /*!< 0x000000FF */

/*******************  Bit definition for OTP_TEST register  ******************/
/* degug */
#define OTP_TEST_DEBUG_Pos              (0U)
#define OTP_TEST_DEBUG_Msk              (0xFFU << OTP_TEST_Pos)                 /*!< 0x000000FF */
/* ATPG */
#define OTP_TEST_ATPG_Pos               (8U)
#define OTP_TEST_ATPG_Msk               (0xFFFFFFU << OTP_TEST_ATPG_Pos)        /*!< 0xFFFFFF00 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MLDR187_H */

