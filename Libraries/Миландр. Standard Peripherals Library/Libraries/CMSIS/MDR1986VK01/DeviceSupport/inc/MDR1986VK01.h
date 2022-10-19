/**
  ******************************************************************************
  * @file    MDR1986VK01.h
  * @author  Milandr Application Team
  * @version V1.3.0
  * @date    21/04/2022
  * @brief   MDR1986VK01 header file
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR1986VK01_H__
#define __MDR1986VK01_H__

/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @defgroup MDR1986VK01 MDR1986VK01
  * @{
  */

/** @defgroup MDR1986VK01_Peripheral MDR1986VK01 Peripheral
  * @{
  */

/**
  * @brief MDR1986VK01 Interrupt Number Definition
  */

typedef enum IRQn
{
/******* Cortex-M4 Processor Exceptions Numbers *******************************/
  NonMaskableInt_IRQn= -14,    ///< 2 Non Maskable Interrupt
  HardFault_IRQn     = -13,    ///< 3 Cortex-M4 Hard Fault Interrupt
  SVCall_IRQn        = -5,     ///< 11 Cortex-M4 SV Call Interrupt
  PendSV_IRQn        = -2,     ///< 14 Cortex-M4 Pend SV Interrupt
  SysTick_IRQn       = -1,     ///< 15 Cortex-M4 System Tick Interrupt

/******* Cortex-M4 specific Interrupt Numbers *********************************/
  FT_IF0_IRQn         = 32,
  FT_IF1_IRQn         = 33,
  FT_IF2_IRQn         = 34,
  FT_IF3_IRQn         = 35,
  CLK_IF_IRQn         = 36,
  RTC_IF_IRQn         = 38,
  BKP_IF_IRQn         = 39,
  EXT_INTERROR0_IRQn  = 40,
  EXT_INTERROR1_IRQn  = 41,
  EXT_INTERROR2_IRQn  = 42,
  EXT_INTERROR3_IRQn  = 43,
  EXT_INTERROR4_IRQn  = 44,
  EXT_INTERROR5_IRQn  = 45,
  EXT_INTERROR6_IRQn  = 46,
  EXT_INTERROR7_IRQn  = 47,
  IF_ERR_SCR_IRQn     = 48,
  IF_FIN_SCR_IRQn     = 49,
  DMA_ERR_IRQn        = 50,
  DMA_DONE0_IRQn      = 51,
  DMA_DONE1_IRQn      = 52,
  DMA_DONE2_IRQn      = 53,
  DMA_DONE3_IRQn      = 54,
  DMA_DONE4_IRQn      = 55,
  DMA_DONE5_IRQn      = 56,
  DMA_DONE6_IRQn      = 57,
  DMA_DONE7_IRQn      = 58,
  DMA_DONE8_IRQn      = 59,
  DMA_DONE9_IRQn      = 60,
  DMA_DONE10_IRQn     = 61,
  DMA_DONE11_IRQn     = 62,
  DMA_DONE12_IRQn     = 63,
  DMA_DONE13_IRQn     = 64,
  DMA_DONE14_IRQn     = 65,
  DMA_DONE15_IRQn     = 66,
  DMA_DONE16_IRQn     = 67,
  DMA_DONE17_IRQn     = 68,
  DMA_DONE18_IRQn     = 69,
  DMA_DONE19_IRQn     = 70,
  DMA_DONE20_IRQn     = 71,
  DMA_DONE21_IRQn     = 72,
  DMA_DONE22_IRQn     = 73,
  DMA_DONE23_IRQn     = 74,
  DMA_DONE24_IRQn     = 75,
  DMA_DONE25_IRQn     = 76,
  DMA_DONE26_IRQn     = 77,
  DMA_DONE27_IRQn     = 78,
  DMA_DONE28_IRQn     = 79,
  DMA_DONE29_IRQn     = 80,
  DMA_DONE30_IRQn     = 81,
  DMA_DONE31_IRQn     = 82,
  IRQ_PORTA_IRQn      = 83,
  IRQ_PORTB_IRQn      = 84,
  IRQ_PORTC_IRQn      = 85,
  IRQ_PORTD_IRQn      = 86,
  ETH_IRQn            = 89,
  CAN0_IRQn           = 90,
  CAN1_IRQn           = 91,
  SSP0_IRQn           = 92,
  SSP0_RXINTR_IRQn    = 93,
  SSP0_TXINTR_IRQn    = 94,
  SSP0_RORINTR_IRQn   = 95,
  SSP0_RTINTR_IRQn    = 96,
  SSP0_RNEINTR_IRQn   = 97,
  SSP0_TFEINTR_IRQn   = 98,
  SSP0_TNBSYINTR_IRQn = 99,
  SSP1_IRQn           = 100,
  SSP1_RXINTR_IRQn    = 101,
  SSP1_TXINTR_IRQn    = 102,
  SSP1_RORINTR_IRQn   = 103,
  SSP1_RTINTR_IRQn    = 104,
  SSP1_RNEINTR_IRQn   = 105,
  SSP1_TFEINTR_IRQn   = 106,
  SSP1_TNBSYINTR_IRQn = 107,
  UART0_IRQn          = 108,
  UART0_TNBSYINTR_IRQn= 109,
  UART0_TFEINTR_IRQn  = 110,
  UART0_RNEINTR_IRQn  = 111,
  UART0_EINTR_IRQn    = 112,
  UART0_RTINTR_IRQn   = 113,
  UART0_TXINTR_IRQn   = 114,
  UART0_RXINTR_IRQn   = 115,
  UART0_MSINTR_IRQn   = 116,
  UART1_IRQn          = 117,
  UART1_TNBSYINTR_IRQn= 118,
  UART1_TFEINTR_IRQn  = 119,
  UART1_RNEINTR_IRQn  = 120,
  UART1_EINTR_IRQn    = 121,
  UART1_RTINTR_IRQn   = 122,
  UART1_TXINTR_IRQn   = 123,
  UART1_RXINTR_IRQn   = 149,
  UART1_MSINTR_IRQn   = 125,
  UART2_IRQn          = 126,
  UART2_TNBSYINTR_IRQn= 127,
  UART2_TFEINTR_IRQn  = 128,
  UART2_RNEINTR_IRQn  = 129,
  UART2_EINTR_IRQn    = 130,
  UART2_RTINTR_IRQn   = 131,
  UART2_TXINTR_IRQn   = 132,
  UART2_RXINTR_IRQn   = 133,
  UART2_MSINTR_IRQn   = 134,
  UART3_IRQn          = 135,
  UART3_TNBSYINTR_IRQn= 136,
  UART3_TFEINTR_IRQn  = 137,
  UART3_RNEINTR_IRQn  = 138,
  UART3_EINTR_IRQn    = 139,
  UART3_RTINTR_IRQn   = 140,
  UART3_TXINTR_IRQn   = 141,
  UART3_RXINTR_IRQn   = 142,
  UART3_MSINTR_IRQn   = 143,
  USB_IRQn            = 144,
  MIL0_IRQn           = 145,
  DAC0_IRQn           = 146,
  DAC1_IRQn           = 147,
  DAC2_IRQn           = 148,
  DAC3_IRQn           = 149,
  DAC0_FIFO_IRQn      = 150,
  DAC1_FIFO_IRQn      = 151,
  DAC2_FIFO_IRQn      = 152,
  DAC3_FIFO_IRQn      = 153,
  TIMER0_IRQn         = 154,
  TIMER1_IRQn         = 155,
  TIMER2_IRQn         = 156,
  TIMER3_IRQn         = 157,
  QEP0_IRQn           = 158,
  QEP1_IRQn           = 159,
  CAP0_IRQn           = 162,
  CAP1_IRQn           = 163,
  CAP2_IRQn           = 164,
  CAP3_IRQn           = 165,
  EPWM8_IRQn          = 166,
  EPWM7_IRQn          = 167,
  EPWM6_IRQn          = 168,
  EPWM5_IRQn          = 169,
  EPWM4_IRQn          = 170,
  EPWM3_IRQn          = 171,
  EPWM2_IRQn          = 172,
  EPWM1_IRQn          = 173,
  EPWM0_IRQn          = 174,
  EPWM_TZ8_IRQn       = 175,
  EPWM_TZ7_IRQn       = 176,
  EPWM_TZ6_IRQn       = 177,
  EPWM_TZ5_IRQn       = 178,
  EPWM_TZ4_IRQn       = 179,
  EPWM_TZ3_IRQn       = 180,
  EPWM_TZ2_IRQn       = 181,
  EPWM_TZ1_IRQn       = 182,
  EPWM_TZ0_IRQn       = 183,
  EPWM_FIFO8_IRQn     = 184,
  EPWM_FIFO7_IRQn     = 185,
  EPWM_FIFO6_IRQn     = 186,
  EPWM_FIFO5_IRQn     = 187,
  EPWM_FIFO4_IRQn     = 188,
  EPWM_FIFO3_IRQn     = 189,
  EPWM_FIFO2_IRQn     = 190,
  EPWM_FIFO1_IRQn     = 191,
  EPWM_FIFO0_IRQn     = 192,
  CMP0_IRQn           = 193,
  CMP1_IRQn           = 194,
  CMP2_IRQn           = 195,
  CMP3_IRQn           = 196,
  ADC00_IRQn          = 197,
  ADC_FIFO00_IRQn     = 198,
  ADC01_IRQn          = 199,
  ADC_FIFO01_IRQn     = 200,
  ADC02_IRQn          = 201,
  ADC_FIFO02_IRQn     = 202,
  ADC10_IRQn          = 203,
  ADC_FIFO10_IRQn     = 204,
  ADC11_IRQn          = 205,
  ADC_FIFO11_IRQn     = 206,
  ADC12_IRQn          = 207,
  ADC_FIFO12_IRQn     = 208,
  CRDC_IRQn           = 209,
  CANFD_IRQn          = 210,
  MIL1_IRQn           = 211,
  CRPT_FIFO0_IRQn     = 212,
  CRPT_REG0_IRQn      = 213,
  CRPT_FIFO1_IRQn     = 214,
  CRPT_REG1_IRQn      = 215,
  SDIO_IRQn           = 216,
  CRPT_LOADDONE_IRQn  = 217,
  CRPT_LOCKEDUP_IRQn  = 219
} IRQn_Type;


/** @addtogroup __MDR1986VK01___Configuration_of_CMSIS Configuration of CMSIS
  * @{
  */

/* Configuration of the Cortex-M4 Processor and Core Peripherals */
#define __MPU_PRESENT           1       /*!< MPU present                                  */
#define __FPU_PRESENT           1       /*!< FPU present */
#define __NVIC_PRIO_BITS        3       /*!< Supports 3 Bits for the Priority Levels      */
#define __Vendor_SysTickConfig  0       /*!< Set to 1 if different SysTick Config is used */

/** @} */ /* __MDR1986VK01___Configuration_of_CMSIS */

/* Includes ------------------------------------------------------------------*/
#include "core_cm4.h"                   /* Cortex-M4 processor and core peripherals       */
#include "system_MDR1986VK01.h"         /* MDR1986VK01 System                             */

/** @defgroup __MDR1986VK01___Exported_types Exported types
  * @{
  */
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus;

#define IS_BIT_STATUS(STATUS)       (((STATUS) == RESET) || ((STATUS) == SET))

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE)  (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/** @} */ /* End of group __MDR1986VK01___Exported_types */

/** @addtogroup __MDR1986VK01_Memory_map Memory map
  * @{
  */

/**
  * @brief MDR1986VK01 Peripheral and SRAM base address
  */

#define SRAM_BASE                 ((uint32_t)0x20000000)
#define PERIPH_BASE               ((uint32_t)0x40000000)
#define CORE_BASE                 ((uint32_t)0xe0000000)

#define SMPID                     ((volatile uint32_t) *((uint32_t *)0xe00fe000))
#define SMPID_BASE                ((uint32_t) 0xe00fe000)

/** @} */ /* End of group __MDR1986VK01_Memory_map */

/**************************************************************************************************/
/*                Device Specific Peripheral registers structures                                 */
/**************************************************************************************************/

/** @addtogroup __MDR1986VK01_MDR_DMA MDR_DMA
  * @{
  */

/**
  * @brief MDR1986VK01 DMA control
  */

typedef struct
{
  __IO  uint32_t STATUS;
  __IO  uint32_t CONFIG;
  __IO  uint32_t CTRL_BASE_PTR;
  __IO  uint32_t ALT_CTRL_BASE_PTR;
  __IO  uint32_t WAITONREG_STATUS;
  __IO  uint32_t CHNL_SW_REQUEST;
  __IO  uint32_t CHNL_USEBURST_SET;
  __IO  uint32_t CHNL_USEBURST_CLR;
  __IO  uint32_t CHNL_REQ_MASK_SET;
  __IO  uint32_t CHNL_REQ_MASK_CLR;
  __IO  uint32_t CHNL_ENABLE_SET;
  __IO  uint32_t CHNL_ENABLE_CLR;
  __IO  uint32_t CHNL_PRI_ALT_SET;
  __IO  uint32_t CHNL_PRI_ALT_CLR;
  __IO  uint32_t CHNL_PRIORITY_SET;
  __IO  uint32_t CHNL_PRIORITY_CLR;
        uint32_t RESERVED[3];
  __IO  uint32_t ERR_CLR;
  __IO  uint32_t CHMUX[8];
} DMAControl;

#define MDR_DMA_BASE              (( uint32_t) 0xe0042000)

#define MDR_DMA                   ((DMAControl *) MDR_DMA_BASE)

/**
  * @brief MDR1986VK01 DMA Primary data structure
  */

typedef struct
{
  __IO  uint32_t PRIMARY_CH0_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH0_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH0_CONTROL;
  __IO  uint32_t PRIMARY_CH0_UNUSED;

  __IO  uint32_t PRIMARY_CH1_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH1_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH1_CONTROL;
  __IO  uint32_t PRIMARY_CH1_UNUSED;

  __IO  uint32_t PRIMARY_CH2_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH2_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH2_CONTROL;
  __IO  uint32_t PRIMARY_CH2_UNUSED;

  __IO  uint32_t PRIMARY_CH3_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH3_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH3_CONTROL;
  __IO  uint32_t PRIMARY_CH3_UNUSED;

  __IO  uint32_t PRIMARY_CH4_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH4_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH4_CONTROL;
  __IO  uint32_t PRIMARY_CH4_UNUSED;

  __IO  uint32_t PRIMARY_CH5_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH5_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH5_CONTROL;
  __IO  uint32_t PRIMARY_CH5_UNUSED;

  __IO  uint32_t PRIMARY_CH6_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH6_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH6_CONTROL;
  __IO  uint32_t PRIMARY_CH6_UNUSED;

  __IO  uint32_t PRIMARY_CH7_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH7_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH7_CONTROL;
  __IO  uint32_t PRIMARY_CH7_UNUSED;

  __IO  uint32_t PRIMARY_CH8_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH8_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH8_CONTROL;
  __IO  uint32_t PRIMARY_CH8_UNUSED;

  __IO  uint32_t PRIMARY_CH9_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH9_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH9_CONTROL;
  __IO  uint32_t PRIMARY_CH9_UNUSED;

  __IO  uint32_t PRIMARY_CH10_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH10_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH10_CONTROL;
  __IO  uint32_t PRIMARY_CH10_UNUSED;

  __IO  uint32_t PRIMARY_CH11_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH11_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH11_CONTROL;
  __IO  uint32_t PRIMARY_CH11_UNUSED;

  __IO  uint32_t PRIMARY_CH12_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH12_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH12_CONTROL;
  __IO  uint32_t PRIMARY_CH12_UNUSED;

  __IO  uint32_t PRIMARY_CH13_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH13_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH13_CONTROL;
  __IO  uint32_t PRIMARY_CH13_UNUSED;

  __IO  uint32_t PRIMARY_CH14_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH14_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH14_CONTROL;
  __IO  uint32_t PRIMARY_CH14_UNUSED;

  __IO  uint32_t PRIMARY_CH15_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH15_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH15_CONTROL;
  __IO  uint32_t PRIMARY_CH15_UNUSED;

  __IO  uint32_t PRIMARY_CH16_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH16_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH16_CONTROL;
  __IO  uint32_t PRIMARY_CH16_UNUSED;

  __IO  uint32_t PRIMARY_CH17_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH17_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH17_CONTROL;
  __IO  uint32_t PRIMARY_CH17_UNUSED;

  __IO  uint32_t PRIMARY_CH18_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH18_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH18_CONTROL;
  __IO  uint32_t PRIMARY_CH18_UNUSED;

  __IO  uint32_t PRIMARY_CH19_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH19_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH19_CONTROL;
  __IO  uint32_t PRIMARY_CH19_UNUSED;

  __IO  uint32_t PRIMARY_CH20_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH20_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH20_CONTROL;
  __IO  uint32_t PRIMARY_CH20_UNUSED;

  __IO  uint32_t PRIMARY_CH21_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH21_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH21_CONTROL;
  __IO  uint32_t PRIMARY_CH21_UNUSED;

  __IO  uint32_t PRIMARY_CH22_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH22_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH22_CONTROL;
  __IO  uint32_t PRIMARY_CH22_UNUSED;

  __IO  uint32_t PRIMARY_CH23_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH23_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH23_CONTROL;
  __IO  uint32_t PRIMARY_CH23_UNUSED;

  __IO  uint32_t PRIMARY_CH24_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH24_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH24_CONTROL;
  __IO  uint32_t PRIMARY_CH24_UNUSED;

  __IO  uint32_t PRIMARY_CH25_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH25_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH25_CONTROL;
  __IO  uint32_t PRIMARY_CH25_UNUSED;

  __IO  uint32_t PRIMARY_CH26_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH26_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH26_CONTROL;
  __IO  uint32_t PRIMARY_CH26_UNUSED;

  __IO  uint32_t PRIMARY_CH27_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH27_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH27_CONTROL;
  __IO  uint32_t PRIMARY_CH27_UNUSED;

  __IO  uint32_t PRIMARY_CH28_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH28_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH28_CONTROL;
  __IO  uint32_t PRIMARY_CH28_UNUSED;

  __IO  uint32_t PRIMARY_CH29_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH29_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH29_CONTROL;
  __IO  uint32_t PRIMARY_CH29_UNUSED;

  __IO  uint32_t PRIMARY_CH30_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH30_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH30_CONTROL;
  __IO  uint32_t PRIMARY_CH30_UNUSED;

  __IO  uint32_t PRIMARY_CH31_SOURCE_END_POINTER;
  __IO  uint32_t PRIMARY_CH31_DEST_END_POINTER;
  __IO  uint32_t PRIMARY_CH31_CONTROL;
  __IO  uint32_t PRIMARY_CH31_UNUSED;
} DMA_PrimaryData_TypeDef;

/**
  * @brief MDR1986VK01 DMA Alternate data structure
  */
typedef struct
{
  __IO  uint32_t ALTER_CH0_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH0_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH0_CONTROL;
  __IO  uint32_t ALTER_CH0_UNUSED;

  __IO  uint32_t ALTER_CH1_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH1_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH1_CONTROL;
  __IO  uint32_t ALTER_CH1_UNUSED;

  __IO  uint32_t ALTER_CH2_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH2_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH2_CONTROL;
  __IO  uint32_t ALTER_CH2_UNUSED;

  __IO  uint32_t ALTER_CH3_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH3_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH3_CONTROL;
  __IO  uint32_t ALTER_CH3_UNUSED;

  __IO  uint32_t ALTER_CH4_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH4_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH4_CONTROL;
  __IO  uint32_t ALTER_CH4_UNUSED;

  __IO  uint32_t ALTER_CH5_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH5_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH5_CONTROL;
  __IO  uint32_t ALTER_CH5_UNUSED;

  __IO  uint32_t ALTER_CH6_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH6_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH6_CONTROL;
  __IO  uint32_t ALTER_CH6_UNUSED;

  __IO  uint32_t ALTER_CH7_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH7_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH7_CONTROL;
  __IO  uint32_t ALTER_CH7_UNUSED;

  __IO  uint32_t ALTER_CH8_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH8_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH8_CONTROL;
  __IO  uint32_t ALTER_CH8_UNUSED;

  __IO  uint32_t ALTER_CH9_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH9_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH9_CONTROL;
  __IO  uint32_t ALTER_CH9_UNUSED;

  __IO  uint32_t ALTER_CH10_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH10_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH10_CONTROL;
  __IO  uint32_t ALTER_CH10_UNUSED;

  __IO  uint32_t ALTER_CH11_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH11_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH11_CONTROL;
  __IO  uint32_t ALTER_CH11_UNUSED;

  __IO  uint32_t ALTER_CH12_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH12_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH12_CONTROL;
  __IO  uint32_t ALTER_CH12_UNUSED;

  __IO  uint32_t ALTER_CH13_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH13_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH13_CONTROL;
  __IO  uint32_t ALTER_CH13_UNUSED;

  __IO  uint32_t ALTER_CH14_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH14_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH14_CONTROL;
  __IO  uint32_t ALTER_CH14_UNUSED;

  __IO  uint32_t ALTER_CH15_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH15_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH15_CONTROL;
  __IO  uint32_t ALTER_CH15_UNUSED;

  __IO  uint32_t ALTER_CH16_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH16_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH16_CONTROL;
  __IO  uint32_t ALTER_CH16_UNUSED;

  __IO  uint32_t ALTER_CH17_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH17_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH17_CONTROL;
  __IO  uint32_t ALTER_CH17_UNUSED;

  __IO  uint32_t ALTER_CH18_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH18_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH18_CONTROL;
  __IO  uint32_t ALTER_CH18_UNUSED;

  __IO  uint32_t ALTER_CH19_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH19_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH19_CONTROL;
  __IO  uint32_t ALTER_CH19_UNUSED;

  __IO  uint32_t ALTER_CH20_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH20_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH20_CONTROL;
  __IO  uint32_t ALTER_CH20_UNUSED;

  __IO  uint32_t ALTER_CH21_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH21_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH21_CONTROL;
  __IO  uint32_t ALTER_CH21_UNUSED;

  __IO  uint32_t ALTER_CH22_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH22_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH22_CONTROL;
  __IO  uint32_t ALTER_CH22_UNUSED;

  __IO  uint32_t ALTER_CH23_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH23_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH23_CONTROL;
  __IO  uint32_t ALTER_CH23_UNUSED;

  __IO  uint32_t ALTER_CH24_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH24_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH24_CONTROL;
  __IO  uint32_t ALTER_CH24_UNUSED;

  __IO  uint32_t ALTER_CH25_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH25_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH25_CONTROL;
  __IO  uint32_t ALTER_CH25_UNUSED;

  __IO  uint32_t ALTER_CH26_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH26_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH26_CONTROL;
  __IO  uint32_t ALTER_CH26_UNUSED;

  __IO  uint32_t ALTER_CH27_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH27_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH27_CONTROL;
  __IO  uint32_t ALTER_CH27_UNUSED;

  __IO  uint32_t ALTER_CH28_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH28_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH28_CONTROL;
  __IO  uint32_t ALTER_CH28_UNUSED;

  __IO  uint32_t ALTER_CH29_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH29_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH29_CONTROL;
  __IO  uint32_t ALTER_CH29_UNUSED;

  __IO  uint32_t ALTER_CH30_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH30_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH30_CONTROL;
  __IO  uint32_t ALTER_CH30_UNUSED;

  __IO  uint32_t ALTER_CH31_SOURCE_END_POINTER;
  __IO  uint32_t ALTER_CH31_DEST_END_POINTER;
  __IO  uint32_t ALTER_CH31_CONTROL;
  __IO  uint32_t ALTER_CH31_UNUSED;
} DMA_AlterData_TypeDef;

/** @} */ /* End of group __MDR1986VK01_MDR_DMA */


/** @addtogroup __MDR1986VK01_Cache Cache
  * @{
  */

/**
  * @brief MDR1986VK01 Cache control
  */

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t CNTL;
  __I   uint32_t HIT_CNT;
  __I   uint32_t MISS_CNT;
        uint32_t RESERVED[4];
  __IO  uint32_t ECC_CNTL;
  __IO  uint32_t ECC_ADDR;
  __IO  uint32_t ECC_DATA;
  __IO  uint32_t ECC_ECC;
} CacheControl;

#define MDR_ICACHE_BASE           (( uint32_t) 0xe0044000)
#define MDR_DCACHE_BASE           (( uint32_t) 0xe0045000)

#define MDR_ICACHE                ((CacheControl *) MDR_ICACHE_BASE)
#define MDR_DCACHE                ((CacheControl *) MDR_DCACHE_BASE)

#define CC_CACHE_ENABLE ((uint32_t)   0x1 )
#define CC_CACHE_CLR    ((uint32_t) (1<<1))
#define CC_OTP_ENABLE   ((uint32_t) (1<<2))
#define CC_EXTB_ENABLE  ((uint32_t) (1<<3))
#define CC_HIT_CLR      ((uint32_t) (1<<4))
#define CC_MISS_CLR     ((uint32_t) (1<<5))
#define CC_KEY          ((uint32_t) 0x8555aaa1)

/** @} */ /* End of group __MDR1986VK01_Cache */

/** @addtogroup __MDR1986VK01_SCRABER SCRABER
  * @{
  */

/**
  * @brief MDR1986VK01 SCRABER control
  */

typedef struct
{
  __IO  uint32_t CNTRL;
  __IO  uint32_t S_ADDR;
  __IO  uint32_t F_ADDR;
  __IO  uint32_t DATA;
  __IO  uint32_t SECC;
} SCRControl;

#define MDR_SCR_BASE      (( uint32_t) 0xe0043000)

#define MDR_SCR           ((SCRControl *) MDR_SCR_BASE)

/** @} */ /* End of group __MDR1986VK01_SCRABER */

/** @defgroup __MDR1986VK01_Periph_ETH	ETH
  * @{
  */

/**
  * @brief MDR1986VK01 MDR_ETH control
  */

typedef struct
{
  __IO  uint16_t DILIMETR;
  __IO  uint16_t MAC_T;
  __IO  uint16_t MAC_M;
  __IO  uint16_t MAC_H;
  __IO  uint16_t HASH0;
  __IO  uint16_t HASH1;
  __IO  uint16_t HASH2;
  __IO  uint16_t HASH3;
  __IO  uint16_t IPG;
  __IO  uint16_t PSC;
  __IO  uint16_t BAG;
  __IO  uint16_t JITTERWND;
  __IO  uint16_t R_CFG;
  __IO  uint16_t X_CFG;
  __IO  uint32_t G_CFG;//__IO uint16_t G_CFGl;__IO  uint16_t G_CFGh;
  __IO  uint16_t IMR;
  __IO  uint16_t IFR;
  __IO  uint16_t MDIO_CTRL;
  __IO  uint16_t MDIO_DATA;
  __IO  uint16_t R_HEAD;
  __IO  uint16_t X_TAIL;
  __IO  uint16_t R_TAIL;
  __IO  uint16_t X_HEAD;
  __IO  uint16_t STAT;
  __IO  uint16_t RCOUNTER;
  __IO  uint16_t PHY_CONTROL;
  __IO  uint16_t PHY_STATUS;
  __IO  uint16_t PHY_CNTR_A;
}MDR_ETH_TypeDef;

#define MDR_ETH_BASE              (SRAM_BASE + 0x1000000)

#define MDR_ETH0_BASE             (MDR_ETH_BASE + 0x00000)

#define MDR_ETH0                  ((MDR_ETH_TypeDef *) MDR_ETH0_BASE)

/** @defgroup __MDR1986VK01_ETH_G_CFG	ETH_G_CFG
  * @{
  */

/* Bit field positions: */
#define ETH_G_CFG_ColWnd_Pos          		0
#define ETH_G_CFG_PAUSE_EN_Pos       		8
#define ETH_G_CFG_DTRM_EN_Pos         		9
#define ETH_G_CFG_HD_EN_Pos          		10
#define ETH_G_CFG_EXT_EN_Pos          		11
#define ETH_G_CFG_BUFF_MODE_Pos       		12
#define ETH_G_CFG_RCLR_EN_Pos         		14
#define ETH_G_CFG_XRST_Pos					16
#define ETH_G_CFG_RRST_Pos            	 	17
#define ETH_G_CFG_DLB_Pos					18
#define ETH_G_CFG_RMIInMII_Pos				19
#define ETH_G_CFG_RMII_SPEED_Pos			20
#define ETH_G_CFG_DBG_RF_EN_Pos			    28
#define ETH_G_CFG_DBG_XF_EN_Pos			    29
#define ETH_G_CFG_DBG_MODE_Pos				30

/* Bit field masks: */
#define ETH_G_CFG_XRST               		((uint32_t)0x00010000)
#define ETH_G_CFG_RRST         		        ((uint32_t)0x00020000)
#define ETH_G_CFG_BUFF_MODE_Msk             ((uint32_t)0x00003000)

/** @} */ /* End of group __MDR1986VK01_ETH_G_CFG */

/** @defgroup __MDR1986VK01_Periph_ETH_X_CFG	ETH X CFG
  * @{
  */

/*-- ETH_X_CFG: ETH X_CFG Register -----*/
/* Bit field positions: */
#define ETH_X_CFG_RtryCnt_Pos         		0
#define ETH_X_CFG_IPG_EN_Pos          		4
#define ETH_X_CFG_CRC_EN_Pos          		5
#define ETH_X_CFG_PRE_EN_Pos          		6
#define ETH_X_CFG_PAD_EN_Pos          		7
#define ETH_X_CFG_EVNT_MODE_Pos       		8
#define ETH_X_CFG_MSB1st_Pos          		12
#define ETH_X_CFG_BE_Pos              		13
#define ETH_X_CFG_EN_Pos             		15

/* Bit field masks: */
#define ETH_X_CFG_RtryCnt_Msk         		((uint32_t)0x0000000F)
#define ETH_X_CFG_IPG_EN               		((uint32_t)0x00000010)
#define ETH_X_CFG_CRC_EN               		((uint32_t)0x00000020)
#define ETH_X_CFG_PRE_EN               		((uint32_t)0x00000040)
#define ETH_X_CFG_PAD_EN               		((uint32_t)0x00000080)
#define ETH_X_CFG_EVNT_MODE_Msk       		((uint32_t)0x00000700)
#define ETH_X_CFG_MSB1st               		((uint32_t)0x00001000)
#define ETH_X_CFG_BE                   		((uint32_t)0x00002000)
#define ETH_X_CFG_EN                  		((uint32_t)0x00008000)

/** @} */ /* End of group __MDR1986VK01_Periph_ETH_X_CFG */

/** @defgroup __MDR1986VK01_Periph_ETH_R_CFG	ETH R CFG
  * @{
  */

/*-- ETH_R_CFG: ETH R_CFG Register -----*/
/* Bit field positions: */
#define ETH_R_CFG_MCA_EN_Pos          0
#define ETH_R_CFG_BCA_EN_Pos          1
#define ETH_R_CFG_UCA_EN_Pos          2
#define ETH_R_CFG_AC_EN_Pos           3
#define ETH_R_CFG_EF_EN_Pos           4
#define ETH_R_CFG_CF_EN_Pos           5
#define ETH_R_CFG_LF_EN_Pos           6
#define ETH_R_CFG_SF_EN_Pos           7
#define ETH_R_CFG_EVNT_MODE_Pos       8
#define ETH_R_CFG_MSB1st_Pos          12
#define ETH_R_CFG_BE_Pos              13
#define ETH_R_CFG_EN_Pos              15

/* Bit field masks: */
#define ETH_R_CFG_MCA_EN               ((uint32_t)0x00000001)
#define ETH_R_CFG_BCA_EN               ((uint32_t)0x00000002)
#define ETH_R_CFG_UCA_EN               ((uint32_t)0x00000004)
#define ETH_R_CFG_AC_EN                ((uint32_t)0x00000008)
#define ETH_R_CFG_EF_EN                ((uint32_t)0x00000010)
#define ETH_R_CFG_CF_EN                ((uint32_t)0x00000020)
#define ETH_R_CFG_LF_EN                ((uint32_t)0x00000040)
#define ETH_R_CFG_SF_EN                ((uint32_t)0x00000080)
#define ETH_R_CFG_EVNT_MODE_Msk        ((uint32_t)0x00000700)
#define ETH_R_CFG_MSB1st               ((uint32_t)0x00001000)
#define ETH_R_CFG_BE                   ((uint32_t)0x00002000)
#define ETH_R_CFG_EN                   ((uint32_t)0x00008000)

/** @} */ /* End of group __MDR1986VK01_Periph_ETH_R_CFG */

/** @defgroup __MDR1986VK01_Periph_ETH_IMR	ETH IMR
  * @{
  */

/*-- ETH_IMR: ETH IMR Register -----*/
/* Bit field positions: */
#define ETH_IMR_RF_OK_Pos             0
#define ETH_IMR_MISSED_F_Pos          1
#define ETH_IMR_OVF_Pos               2
#define ETH_IMR_SMB_ERR_Pos           3
#define ETH_IMR_CRC_ERR_Pos           4
#define ETH_IMR_CF_Pos                5
#define ETH_IMR_LF_Pos                6
#define ETH_IMR_SF_Pos                7
#define ETH_IMR_XF_OK_Pos             8
#define ETH_IMR_XF_ERR_Pos            9
#define ETH_IMR_UNDF_Pos              10
#define ETH_IMR_LC_Pos                11
#define ETH_IMR_CRS_LOST_Pos          12
#define ETH_IMR_MDIO_INT_Pos          14
#define ETH_IMR_MII_RDY_Pos           15

/* Bit field masks: */
#define ETH_IMR_RF_OK                  ((uint32_t)0x00000001)
#define ETH_IMR_MISSED_F               ((uint32_t)0x00000002)
#define ETH_IMR_OVF                    ((uint32_t)0x00000004)
#define ETH_IMR_SMB_ERR                ((uint32_t)0x00000008)
#define ETH_IMR_CRC_ERR                ((uint32_t)0x00000010)
#define ETH_IMR_CF                     ((uint32_t)0x00000020)
#define ETH_IMR_LF                     ((uint32_t)0x00000040)
#define ETH_IMR_SF                     ((uint32_t)0x00000080)
#define ETH_IMR_XF_OK                  ((uint32_t)0x00000100)
#define ETH_IMR_XF_ERR                 ((uint32_t)0x00000200)
#define ETH_IMR_UNDF                   ((uint32_t)0x00000400)
#define ETH_IMR_LC                     ((uint32_t)0x00000800)
#define ETH_IMR_CRS_LOST               ((uint32_t)0x00001000)
#define ETH_IMR_MDIO_INT			   ((uint32_t)0x00004000)
#define ETH_IMR_MII_RDY                ((uint32_t)0x00008000)

/** @} */ /* End of group ETH_IMR */

/** @defgroup __MDR1986VK01_Periph_ETH_IFR	ETH IFR
  * @{
  */

/*-- ETH_IFR: ETH IFR Register -----*/
/* Bit field positions: */
#define ETH_IFR_RF_OK_Pos             0
#define ETH_IFR_MISSED_F_Pos          1
#define ETH_IFR_OVF_Pos               2
#define ETH_IFR_SMB_ERR_Pos           3
#define ETH_IFR_CRC_ERR_Pos           4
#define ETH_IFR_CF_Pos                5
#define ETH_IFR_LF_Pos                6
#define ETH_IFR_SF_Pos                7
#define ETH_IFR_XF_OK_Pos             8
#define ETH_IFR_XF_ERR_Pos            9
#define ETH_IFR_UNDF_Pos              10
#define ETH_IFR_LC_Pos                11
#define ETH_IFR_CRS_LOST_Pos          12
#define ETH_IFR_MDIO_INT_Pos          14
#define ETH_IFR_MII_RDY_Pos           15

/* Bit field masks: */
#define ETH_IFR_RF_OK                  ((uint32_t)0x00000001)
#define ETH_IFR_MISSED_F               ((uint32_t)0x00000002)
#define ETH_IFR_OVF                    ((uint32_t)0x00000004)
#define ETH_IFR_SMB_ERR                ((uint32_t)0x00000008)
#define ETH_IFR_CRC_ERR                ((uint32_t)0x00000010)
#define ETH_IFR_CF                     ((uint32_t)0x00000020)
#define ETH_IFR_LF                     ((uint32_t)0x00000040)
#define ETH_IFR_SF                     ((uint32_t)0x00000080)
#define ETH_IFR_XF_OK                  ((uint32_t)0x00000100)
#define ETH_IFR_XF_ERR                 ((uint32_t)0x00000200)
#define ETH_IFR_UNDF                   ((uint32_t)0x00000400)
#define ETH_IFR_LC                     ((uint32_t)0x00000800)
#define ETH_IFR_CRS_LOST               ((uint32_t)0x00001000)
#define ETH_IFR_MDIO_INT			   ((uint32_t)0x00004000)
#define ETH_IFR_MII_RDY                ((uint32_t)0x00008000)

/** @} */ /* End of group ETH_IFR */

/** @defgroup __MDR1986VK01_Periph_ETH_STAT	ETH STAT
  * @{
  */

/*-- ETH_STAT: ETH STAT Register -----*/
/* Bit field positions: */
#define ETH_STAT_R_EMPTY_Pos			0
#define ETH_STAT_R_AEMPTY_Pos			1
#define ETH_STAT_R_HALF_Pos				2
#define ETH_STAT_R_AFULL_Pos			3
#define ETH_STAT_R_FULL_Pos				4
#define ETH_STAT_R_COUNT_Pos			5
#define ETH_STAT_X_EMPTY_Pos			8
#define ETH_STAT_X_AEMPTY_Pos			9
#define ETH_STAT_X_HALF_Pos				10
#define ETH_STAT_X_AFULL_Pos			11
#define ETH_STAT_X_FULL_Pos				12

/* Bit field masks: */
#define ETH_STAT_R_EMPTY				((uint32_t)0x00000001)
#define ETH_STAT_R_AEMPTY				((uint32_t)0x00000002)
#define ETH_STAT_R_HALF					((uint32_t)0x00000004)
#define ETH_STAT_R_AFULL				((uint32_t)0x00000008)
#define ETH_STAT_R_FULL					((uint32_t)0x00000010)
#define ETH_STAT_R_COUNT_Msk			((uint32_t)0x000000E0)
#define ETH_STAT_X_EMPTY				((uint32_t)0x00000100)
#define ETH_STAT_X_AEMPTY				((uint32_t)0x00000200)
#define ETH_STAT_X_HALF					((uint32_t)0x00000400)
#define ETH_STAT_X_AFULL				((uint32_t)0x00000800)
#define ETH_STAT_X_FULL					((uint32_t)0x00001000)

/** @} */ /* End of group ETH_STAT */

/** @defgroup __MDR1986VK01_Periph_ETH_MDIO_CTRL	ETH MDIO CTRL
  * @{
  */

/*-- ETH_MDIO_CTRL: ETH MDIO_CTRL Register -----*/
/* Bit field positions: */
#define ETH_MDIO_CTRL_RG_A_Pos			0
#define ETH_MDIO_CTRL_DIV_Pos			5
#define ETH_MDIO_CTRL_PHY_A_Pos			8
#define ETH_MDIO_CTRL_OP_Pos			13
#define ETH_MDIO_CTRL_PRE_EN_Pos		14
#define ETH_MDIO_CTRL_RDY_Pos			15

/* Bit field masks: */
#define ETH_MDIO_CTRL_RG_A_Msk			((uint32_t)0x0000001F)
#define ETH_MDIO_CTRL_DIV_Msk			((uint32_t)0x000000E0)
#define ETH_MDIO_CTRL_PHY_A_Msk			((uint32_t)0x00001F00)
#define ETH_MDIO_CTRL_OP				((uint32_t)0x00002000)
#define ETH_MDIO_CTRL_PRE_EN			((uint32_t)0x00004000)
#define ETH_MDIO_CTRL_RDY				((uint32_t)0x00008000)

/** @} */ /* End of group ETH_MDIO_CTRL */

/** @} */ /* End of group __MDR1986VK01_Periph_ETH */


/** @defgroup __MDR1986VK01_Periph_USB USB
  * @{
  */

/**
  * @brief MDR1986VK01 USB controller interface
  */

typedef struct
{
   __IO uint8_t  TxFuncAddr;
        uint8_t  UNUSED1;
   __IO uint8_t  TxHudAddr;
   __IO uint8_t  TxHudPort;
        uint32_t UNUSED2;
} USB_TAR0_struct;

typedef struct
{
   __IO uint8_t TxFuncAddr;
        uint8_t UNUSED1;
   __IO uint8_t TxHudAddr;
   __IO uint8_t TxHudPort;
   __IO uint8_t RxFuncAddr;
        uint8_t UNUSED2;
   __IO uint8_t RxHudAddr;
   __IO uint8_t RxHudPort;
} USB_TAR_struct;

typedef struct
{
  /* Common USB registers */
  __IO uint8_t  FADDR;
  __IO uint8_t  POWER;
  __I  uint16_t INTRTX;
  __I  uint16_t INTRRX;
  __IO uint16_t INTRTXE;
  __IO uint16_t INTRRXE;
  __I  uint8_t  INTRUSB;
  __IO uint8_t  INTRUSBE;
  __I  uint16_t FRAME;
  __IO uint8_t  INDEX;
  __IO uint8_t  TESTMODE;
  /* Indexed registers */
  __IO uint16_t TXMAXP;
  __IO uint16_t CSR0_TXCSR;
  __IO uint16_t RXMAXP;
  __IO uint16_t RXCSR;
  __I  uint16_t COUNT0_RXCOUNT;
  __IO uint8_t  TYPE0_TXTYPE;
  __IO uint8_t  NAKLIMIT0_TXINTERVAL;
  __IO uint8_t  RXTYPE;
  __IO uint8_t  RXINTERVAL;
       uint8_t  UNUSED1;
  __I  uint8_t  CONFIGDATA_FIFOSIZE;
  /* FIFOs */
  __IO uint32_t FIFO[4];
       uint32_t UNUSED2[12];
  /* OTG, Dynamic FIFO, Version & Vendor registers */
  __IO uint8_t  DEVCTL;
       uint8_t  UNUSED3;
  __IO uint8_t  TXFIFOSZ;
  __IO uint8_t  RXFIFOSZ;
  __IO uint16_t TXFIFOADD;
  __IO uint16_t RXFIFOADD;
       uint32_t UNUSED4;
  __I  uint16_t HWVERS;
       uint16_t UNUSED5;
       uint32_t UNUSED6[4];
  /* */
USB_TAR0_struct TAR0;
USB_TAR_struct  TAR[3];
} USB_Typedef;

#define MDR_USB_BASE              (SRAM_BASE + 0x1000000)

#define MDR_USB0_BASE             (MDR_USB_BASE + 0x10000)

#define MDR_USB0                  ((USB_Typedef *) MDR_USB0_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_USB */

/**************************************************************************************************/
/*                         Peripheral declaration                                                 */
/**************************************************************************************************/

/** @defgroup __MDR1986VK01_Periph_CLK CLK
  * @{
  */

/**
  * @brief MDR1986VK01 CLOCK Control
  */

typedef struct
{
  __IO  uint32_t CLK;
  __IO  uint32_t CHK0;
  __IO  uint32_t CHK1;
  __IO  uint32_t CHK2;
  __IO  uint32_t STAT;
}MDR_CLK_TypeDef;

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t MAX_CLK;
  __IO  uint32_t CPU_CLK;
  __IO  uint32_t PER0_CLK;
  __IO  uint32_t PER1_CLK;

  __IO  uint32_t CPU_CHK0;
  __IO  uint32_t CPU_CHK1;
  __IO  uint32_t CPU_CHK2;
  __IO  uint32_t CPU_STAT;

  MDR_CLK_TypeDef LSI;

  __IO  uint32_t HSI_STAT;

  MDR_CLK_TypeDef LSE;

  MDR_CLK_TypeDef HSE[2];

  MDR_CLK_TypeDef PLL[4];

  __IO  uint32_t EMAC0_CLK;
  __IO  uint32_t USB0_CLK;
  __IO  uint32_t USBMAC_CLK;
  __IO  uint32_t RTC0_CLK;

  __IO  uint32_t SSP0_CLK;
  __IO  uint32_t SSP1_CLK;

  __IO  uint32_t CAN0_CLK;
  __IO  uint32_t CAN1_CLK;

  __IO  uint32_t UART0_CLK;
  __IO  uint32_t UART1_CLK;
  __IO  uint32_t UART2_CLK;
  __IO  uint32_t UART3_CLK;

  __IO  uint32_t MIL0_CLK;

  __IO  uint32_t TIM0_CLK;
  __IO  uint32_t TIM1_CLK;
  __IO  uint32_t TIM2_CLK;
  __IO  uint32_t RESERVED0;
  __IO  uint32_t TIM3_CLK;

  __IO  uint32_t CAP0_CLK;
  __IO  uint32_t CAP1_CLK;
  __IO  uint32_t CAP2_CLK;
  __IO  uint32_t CAP3_CLK;

  __IO  uint32_t QEP0_CLK;
  __IO  uint32_t QEP1_CLK;

  __IO  uint32_t PWM0_CLK;
  __IO  uint32_t PWM1_CLK;
  __IO  uint32_t PWM2_CLK;
  __IO  uint32_t PWM3_CLK;
  __IO  uint32_t PWM4_CLK;
  __IO  uint32_t PWM5_CLK;
  __IO  uint32_t PWM6_CLK;
  __IO  uint32_t PWM7_CLK;
  __IO  uint32_t PWM8_CLK;

  __IO  uint32_t ADC0_CLK;
  __IO  uint32_t RESERVED1[32];
  __IO  uint32_t ADC1_CLK;
  __IO  uint32_t ADC2_CLK;
  __IO  uint32_t CRDC_CLK;
  __IO  uint32_t CANFD_CLK;
  __IO  uint32_t CRPT_CLK;
  __IO  uint32_t SDIO_CLK;
} CLKControl;

#define MDR_CLK_BASE             (PERIPH_BASE + 0x00000)

#define MDR_CLK                  ((CLKControl *) MDR_CLK_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_CLK */


/** @defgroup __MDR1986VK01_Periph_BKP BKP
  * @{
  */

/**
  * @brief MDR1986VK01 BKP control
  */

typedef struct
{
  __IO  uint32_t REG_xx[60];
  __IO  uint32_t KEY;
  __IO  uint32_t REG_64_TMR0;
  __IO  uint32_t REG_64_TMR1;
  __IO  uint32_t REG_64_TMR2;

  __IO  uint32_t REG_60_SYS0;
  __IO  uint32_t REG_61_PWR0;
  __IO  uint32_t REG_62_PWR0;
  __IO  uint32_t REG_63_CLK0;

  __IO  uint32_t REG_60_SYS1;
  __IO  uint32_t REG_61_PWR1;
  __IO  uint32_t REG_62_PWR1;
  __IO  uint32_t REG_63_CLK1;

  __IO  uint32_t REG_60_SYS2;
  __IO  uint32_t REG_61_PWR2;
  __IO  uint32_t REG_62_PWR2;
  __IO  uint32_t REG_63_CLK2;

  __IO  uint32_t RTC_CNT_TMR0;
  __IO  uint32_t RTC_DIV_TMR0;
  __IO  uint32_t RTC_PRL_TMR0;
  __IO  uint32_t RTC_ALRM_TMR0;
  __IO  uint32_t RTC_CS_TMR0;

  __IO  uint32_t RESERV_1[3];

  __IO  uint32_t RTC_CNT_TMR1;
  __IO  uint32_t RTC_DIV_TMR1;
  __IO  uint32_t RTC_PRL_TMR1;
  __IO  uint32_t RTC_ALRM_TMR1;
  __IO  uint32_t RTC_CS_TMR1;

  __IO  uint32_t RESERV_2[3];

  __IO  uint32_t RTC_CNT_TMR2;
  __IO  uint32_t RTC_DIV_TMR2;
  __IO  uint32_t RTC_PRL_TMR2;
  __IO  uint32_t RTC_ALRM_TMR2;
  __IO  uint32_t RTC_CS_TMR2;

  __IO  uint32_t RESERV_3[3];
  __IO  uint32_t BKP_PWR_CNTR0;
  __IO  uint32_t BKP_PWR_CNTR1;
  __IO  uint32_t RESERV_4;
  __IO  uint32_t BKP_PWR_CNTR2;
} BKPControl;

#define BKP_KEY                   ((uint32_t) 0x8555aaa1)

#define MDR_BKP_BASE              (PERIPH_BASE + 0x01000)

#define MDR_BKP                   ((BKPControl *) MDR_BKP_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_BKP */


// /** @defgroup __MDR1986VK01_Periph_PWR PWR
  // * @{
  // */

// /**
  // * @brief MDR1986VK01 PWR control
  // */

// typedef struct
// {
  // __IO  uint32_t KEY;

  // __IO  uint32_t CNTR0;
  // __IO  uint32_t CNTR1;
  // __IO  uint32_t CNTR2;

  // __IO  uint32_t STAT;

  // __IO  uint32_t ULIMIT;
  // __IO  uint32_t CLIMIT;
// } PWRControl;

// #define PWR_BASE                  (PERIPH_BASE + 0x02000)

// #define PWR                       ((PWRControl *) PWR_BASE)

// /** @} */ /* End of group __MDR1986VK01_Periph_PWR */


/** @defgroup __MDR1986VK01_Periph_FT FT
  * @{
  */

/**
  * @brief MDR1986VK01 FT control
  */

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t CONTROL;
  __IO  uint32_t STATUS;
  __IO  uint32_t TIMEOUT;
  __IO  uint32_t TICKCNT;
  __IO  uint32_t FIRSTEVENT;
  __IO  uint32_t LASTEVENT;
  __IO  uint32_t TIMEOUTCNT;
  __IO  uint32_t EVENT[13];
  __IO  uint32_t RESET_EVENT0;
  __IO  uint32_t RESET_EVENT1;
  __IO  uint32_t RESET_EVENT2;
  __IO  uint32_t RESET_EVENT3;
  __IO  uint32_t RESET_EVENT4;
  __IO  uint32_t IE_EVENT5;
  __IO  uint32_t IE_EVENT6;
  __IO  uint32_t IE_EVENT7;
  __IO  uint32_t IE_EVENT8;
  __IO  uint32_t IE_EVENT9;
  __IO  uint32_t IE_EVENT10;
  __IO  uint32_t IE_EVENT11;
  __IO  uint32_t IE_EVENT12;
  __IO  uint32_t FT_STAT0;
  __IO  uint32_t FT_STAT1;
} FTControl;

#define MDR_FTMODE_BASE              (PERIPH_BASE + 0x03000)

#define MDR_FTMODE                   ((FTControl *) MDR_FTMODE_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_FT */


/** @defgroup __MDR1986VK01_Periph_WDT WDT
  * @{
  */

/**
  * @brief MDR1986VK01 WDT control
  */

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t PRL;
  __IO  uint32_t EN;
  __IO  uint32_t CNT;
} WDTControl;

#define MDR_WDT_BASE              (PERIPH_BASE + 0x04000)

#define MDR_WDT                   ((WDTControl *) MDR_WDT_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_WDT */


/** @defgroup __MDR1986VK01_Periph_FLASH FLASH
  * @{
  */

/**
  * @brief MDR1986VK01 FLASH control
  */

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t CNTR;
  __IO  uint32_t ADR;
  __IO  uint32_t WDATA3;
  __IO  uint32_t WDATA2;
  __IO  uint32_t WDATA1;
  __IO  uint32_t WDATA0;
  __IO  uint32_t WECC0;
  __IO  uint32_t WECC1;
  __IO  uint32_t RDATA3;
  __IO  uint32_t RDATA2;
  __IO  uint32_t RDATA1;
  __IO  uint32_t RDATA0;
  __IO  uint32_t RECC0;
  __IO  uint32_t RECC1;
  __IO  uint32_t ECCCS;
  __IO  uint32_t ECCADR;
  __IO  uint32_t ECCDATA;
  __IO  uint32_t ECCECC;
  __IO  uint32_t BLOCK;
} FLASHControl;

#define MDR_FLASH_BASE                (PERIPH_BASE + 0x06000)

#define MDR_FLASH                     ((FLASHControl *) MDR_FLASH_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_FLASH */


/** @defgroup __MDR1986VK01_Periph_ROM_RAMC_RAMD ROM,RAMC,RAMD
  * @{
  */

/**
  * @brief MDR1986VK01 ROM,RAMC,RAMD control
  */

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t ECCCS;
  __IO  uint32_t ECCADR;
  __IO  uint32_t ECCDATA;
  __IO  uint32_t ECCECC;
  __IO  uint32_t TEST_TUNING;
} MEMControl;

#define MDR_ROM_BASE              (PERIPH_BASE + 0x05000)
#define MDR_RAM_BASE              (PERIPH_BASE + 0x08000)

#define MDR_RAMC0_BASE            (MDR_RAM_BASE + 0x0000)
#define MDR_RAMC1_BASE            (MDR_RAM_BASE + 0x1000)
#define MDR_RAMD0_BASE            (MDR_RAM_BASE + 0x2000)
#define MDR_RAMD1_BASE            (MDR_RAM_BASE + 0x3000)

#define MDR_ROM                   ((MEMControl *) MDR_ROM_BASE)
#define MDR_RAMC0                 ((MEMControl *) MDR_RAMC0_BASE)
#define MDR_RAMC1                 ((MEMControl *) MDR_RAMC1_BASE)
#define MDR_RAMD0                 ((MEMControl *) MDR_RAMD0_BASE)
#define MDR_RAMD1                 ((MEMControl *) MDR_RAMD1_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_ROM_RAMC_RAMD */


/** @defgroup __MDR1986VK01_Periph_EBC MDR_EBC
  * @{
  */

/**
  * @brief MDR1986VK01 MDR_EBC control
  */

typedef struct
{
  __IO  uint32_t RGN0_CNTRL;
  __IO  uint32_t RGN0_ECCBASE;
  __IO  uint32_t RGN0_ECCS;
  __IO  uint32_t RGN0_STATE;

  __IO  uint32_t RGN1_CNTRL;
  __IO  uint32_t RGN1_ECCBASE;
  __IO  uint32_t RGN1_ECCS;
  __IO  uint32_t RGN1_STATE;

  __IO  uint32_t RGN2_CNTRL;
  __IO  uint32_t RGN2_ECCBASE;
  __IO  uint32_t RGN2_ECCS;
  __IO  uint32_t RGN2_STATE;

  __IO  uint32_t RGN3_CNTRL;
  __IO  uint32_t RGN3_ECCBASE;
  __IO  uint32_t RGN3_ECCS;
  __IO  uint32_t RGN3_STATE;

  __IO  uint32_t RGN4_CNTRL;
  __IO  uint32_t RGN4_ECCBASE;
  __IO  uint32_t RGN4_ECCS;
  __IO  uint32_t RGN4_STATE;

  __IO  uint32_t RGN5_CNTRL;
  __IO  uint32_t RGN5_ECCBASE;
  __IO  uint32_t RGN5_ECCS;
  __IO  uint32_t RGN5_STATE;

  __IO  uint32_t RGN6_CNTRL;
  __IO  uint32_t RGN6_ECCBASE;
  __IO  uint32_t RGN6_ECCS;
  __IO  uint32_t RGN6_STATE;

  __IO  uint32_t RGN7_CNTRL;
  __IO  uint32_t RGN7_ECCBASE;
  __IO  uint32_t RGN7_ECCS;
  __IO  uint32_t RGN7_STATE;

  __IO  uint32_t KEY;
  __IO  uint32_t ECC_ADDR;
  __IO  uint32_t ECC_DATA;
  __IO  uint32_t ECC_ECC;
  __IO  uint32_t OCLK;
} EXTBUSControl;

#define MDR_EBC_BASE              (PERIPH_BASE + 0x0C000)

#define MDR_EBC                   ((EXTBUSControl *) MDR_EBC_BASE)

#define EB_CNTR_MODE(mode)        ((mode & 3) << 4)
#define EB_CNTR_ECCMODE           4
#define EB_CNTR_ECCEN             2
#define EB_CNTR_EN                1
#define EB_CNTR_WS_HOLD(hold)     ((hold & 0xf) << 20)
#define EB_CNTR_WS_ACTIVE(act)    ((act & 0xf) << 16)
#define EB_CNTR_WS_SETUP(setup)   ((setup & 0xff) << 8)

#define EBC_EN_pos			      0
#define EBC_ECCEN_pos			  1
#define EBC_ECCMODE_pos			  2
#define EBC_RDYWAIT_pos			  3
#define EBC_MODE_pos			  4
#define EBC_ROM_pos				  6
#define EBC_CPOL_pos			  7
#define EBC_WS_ACTIVE_pos		  8
#define EBC_WS_SETUP_pos		  16
#define EBC_WS_HOLD_pos			  20
#define EBC_ECC8BIT_pos		      24
#define EBC_ENOCLK_pos			  27
#define EBC_DIVOCLK_pos			  28

#define EBC_EN_MSK			      ((uint32_t) 0x00000001)
#define EBC_ECCEN_MSK			  ((uint32_t) 0x00000002)
#define EBC_ECCMODE_MSK			  ((uint32_t) 0x00000004)
#define EBC_RDYWAIT_MSK			  ((uint32_t) 0x00000008)
#define EBC_MODE_MSK			  ((uint32_t) 0x00000030)
#define EBC_ROM_MSK				  ((uint32_t) 0x00000040)
#define EBC_CPOL_MSK			  ((uint32_t) 0x00000080)
#define EBC_WS_ACTIVE_MSK		  ((uint32_t) 0x0000FF00)
#define EBC_WS_SETUP_MSK		  ((uint32_t) 0x000F0000)
#define EBC_WS_HOLD_MSK			  ((uint32_t) 0x00F00000)
#define EBC_USESEPAR_MSK		  ((uint32_t) 0x01000000)
#define EBC_CACHEBLE_MSK		  ((uint32_t) 0x02000000)
#define EBC_READ32_MSK			  ((uint32_t) 0x04000000)
#define EBC_ENOCLK_MSK			  ((uint32_t) 0x08000000)
#define EBC_DIVOCLK_MSK			  ((uint32_t) 0xF0000000)

/** @} */ /* End of group __MDR1986VK01_Periph_EBC */


/** @defgroup __MDR1986VK01_Periph_PORT MDR_PORT
  * @{
  */

/**
  * @brief MDR1986VK01 PORT control
  */

typedef struct
{
  __IO  uint32_t KEY;
  __IO  uint32_t RXTX;
  __IO  uint32_t SRXTX;
  __IO  uint32_t CRXTX;

  __IO  uint32_t SOE;
  __IO  uint32_t COE;

  __IO  uint32_t SFUNC[4];

  __IO  uint32_t CFUNC[4];

  __IO  uint32_t SANALOG;
  __IO  uint32_t CANALOG;

  __IO  uint32_t SPULLUP;
  __IO  uint32_t CPULLUP;

  __IO  uint32_t SPULLDOWN;
  __IO  uint32_t CPULLDOWN;

  __IO  uint32_t SPD;
  __IO  uint32_t CPD;

  __IO  uint32_t SPWR[2];
  __IO  uint32_t CPWR[2];

  __IO  uint32_t SCL;
  __IO  uint32_t CCL;

  __IO  uint32_t SIE;
  __IO  uint32_t CIE;

  __IO  uint32_t SIT;
  __IO  uint32_t CIT;

  __IO  uint32_t SIR;
  __IO  uint32_t CIR;

  __IO  uint32_t HCUR;
} PortControl;

#define MDR_PORT_BASE             (PERIPH_BASE + 0x80000)

#define MDR_PORTA_BASE                (MDR_PORT_BASE + 0x0000)
#define MDR_PORTB_BASE                (MDR_PORT_BASE + 0x1000)
#define MDR_PORTC_BASE                (MDR_PORT_BASE + 0x2000)
#define MDR_PORTD_BASE                (MDR_PORT_BASE + 0x3000)

#define MDR_PORTA                     ((PortControl *) MDR_PORTA_BASE)
#define MDR_PORTB                     ((PortControl *) MDR_PORTB_BASE)
#define MDR_PORTC                     ((PortControl *) MDR_PORTC_BASE)
#define MDR_PORTD                     ((PortControl *) MDR_PORTD_BASE)

#define FUNC_MASK 0x0f
#define FUNCREGNUM(pin) (pin >> 3)
#define _FUNCPIN(TYPE) TYPE ## FUNC
#define FUNCPIN(pin,TYPE) _FUNCPIN(TYPE)[FUNCREGNUM(pin)]
#define SFUNCPIN(pin) FUNCPIN(pin,S)
#define CFUNCPIN(pin) FUNCPIN(pin,C)
#define FUNCVAL(pin,func) ((func & FUNC_MASK) << ((pin % 8)<<2))

#define PWR_MASK 0x3
#define PWRREGNUM(pin) (pin >> 4)
#define _PWRPIN(type) type ## PWR
#define PWRPIN(pin, type) _PWRPIN(type)[PWRREGNUM(pin)]
#define SPWRPIN(pin) PWRPIN(pin, S)
#define CPWRPIN(pin) PWRPIN(pin, C)
#define PWRVAL(pin, pwr) ((pwr & PWR_MASK) << ((pin % 16) << 1))

/** @} */ /* End of group __MDR1986VK01_Periph_PORT */


/** @defgroup __MDR1986VK01_Periph_CANFD CANFD
  * @{
  */

/**
  * @brief MDR1986VK01 MDR_CANFD control
  */

typedef struct
{
  __IO    uint32_t CTRL[3];
}MDR_CANFD_TXCTRL_TypeDef;

typedef struct
{
  /* Control registers */
  __IO  uint32_t CONTROL;
  __IO  uint32_t CFG0;
  __IO  uint32_t CFG1;
  __IO  uint32_t CFG2;
  __IO  uint32_t CFG3;
  /* Filter config register */
  __IO  uint32_t RXFCFG;
  /* Prescalers */
  __IO  uint32_t PRSC;
  __IO  uint32_t FPRSC;
  /* IRQ resiters */
  __I   uint32_t ST;
  __IO  uint32_t MSK;
  /* Rx queue Base Addr */
  __IO  uint32_t RXBADDR;
  /* Tx queue Base Addr */
  __IO  uint32_t TXBADDR[4];
  /* Timer register */
  __I   uint32_t CURTIMEHi;
  __I   uint32_t CURTIMELo;
        uint32_t Reserved1[3];

  /* Rx Queue Control register */
  __IO  uint32_t RXQCTRL[2];
  /* Tx Queue Control register (Set) */
  MDR_CANFD_TXCTRL_TypeDef TXQCTRL[4];
  /* Tx Queue Control register (Clear) */
  MDR_CANFD_TXCTRL_TypeDef TXRCTRL[4];
        uint32_t Reserved2[2];

  /* Filtration pattern */
  __IO  uint32_t RXF[16];
  /* Filtration mask */
  __IO  uint32_t RXFMSK[16];

  /* Error Counter registers */
  __I   uint32_t TECE;
  __I   uint32_t RECE;
  __I   uint32_t TEC;
  __I   uint32_t REC;
  __I   uint32_t EOVLC;
  __I   uint32_t EPSC;
  __I   uint32_t BOSC;
  __I   uint32_t LMSGLC;
}MDR_CANFD_TypeDef;

#define MDR_CANFD_BASE            (PERIPH_BASE + 0x80000)

#define MDR_CANFD0_BASE           (MDR_CANFD_BASE + 0x6000)

#define MDR_CANFD0                ((MDR_CANFD_TypeDef *) MDR_CANFD0_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_CANFD */


/** @defgroup __MDR1986VK01_Periph_SSP SSP
  * @{
  */

/**
  * @brief MDR1986VK01 MDR_SSP control
  */

typedef struct
{
  __IO  uint32_t CR0;
  __IO  uint32_t CR1;
  __IO  uint32_t DR;
  __IO  uint32_t SR;
  __IO  uint32_t CPSR;
  __IO  uint32_t IMSC;
  __IO  uint32_t RIS;
  __IO  uint32_t MIS;
  __IO  uint32_t ICR;
  __IO  uint32_t DMACR;
}MDR_SSP_TypeDef;

#define MDR_SSP_BASE              (PERIPH_BASE + 0x80000)

#define MDR_SSP0_BASE             (MDR_SSP_BASE + 0x9000)
#define MDR_SSP1_BASE             (MDR_SSP_BASE + 0xA000)

#define MDR_SSP0                  ((MDR_SSP_TypeDef *) MDR_SSP0_BASE)
#define MDR_SSP1                  ((MDR_SSP_TypeDef *) MDR_SSP1_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_SSP */


/** @defgroup __MDR1986VK01_Periph_CAN CAN
  * @{
  */

/**
  * @brief MDR1986VK01 MDR_CAN control
  */

typedef struct
{
  __IO  uint32_t ID;
  __IO  uint32_t DLC;
  __IO  uint32_t DATAL;
  __IO  uint32_t DATAH;
}MDR_CAN_BUF_TypeDef;

typedef struct
{
  __IO  uint32_t MASK;
  __IO  uint32_t FILTER;
}MDR_CAN_BUF_FILTER_TypeDef;

typedef struct
{
  __IO  uint32_t CONTROL;
  __IO  uint32_t STATUS;
  __IO  uint32_t BITTMNG;
  __IO  uint32_t Reserved0;
  __IO  uint32_t INT_EN;
  __IO  uint32_t Reserved1[2];
  __IO  uint32_t OVER;
  __IO  uint32_t RXID;
  __IO  uint32_t RXDLC;
  __IO  uint32_t RXDATAL;
  __IO  uint32_t RXDATAH;
  __IO  uint32_t TXID;
  __IO  uint32_t TXDLC;
  __IO  uint32_t DATAL;
  __IO  uint32_t DATAH;
  __IO  uint32_t BUF_CON[32];
  __IO  uint32_t INT_RX;
  __IO  uint32_t RX;
  __IO  uint32_t INT_TX;
  __IO  uint32_t TX;
  __IO  uint32_t Reserved2[76];
  MDR_CAN_BUF_TypeDef BUF[32];
  __IO  uint32_t Reserved3[64];
  MDR_CAN_BUF_FILTER_TypeDef FILTER[32];
}MDR_CAN_TypeDef;

#define MDR_CAN_BASE              (PERIPH_BASE + 0x80000)

#define MDR_CAN0_BASE             (MDR_CAN_BASE + 0xB000)
#define MDR_CAN1_BASE             (MDR_CAN_BASE + 0xC000)

#define MDR_CAN0                  ((MDR_CAN_TypeDef *) MDR_CAN0_BASE)
#define MDR_CAN1                  ((MDR_CAN_TypeDef *) MDR_CAN1_BASE)

/*-- CAN_CONTROL: CAN Control Register -----------------------------*/
/* Bit field positions: */
#define CAN_CONTROL_CAN_EN_Pos                  0
#define CAN_CONTROL_ROM_Pos                     1
#define CAN_CONTROL_STM_Pos                     2
#define CAN_CONTROL_SAP_Pos                     3
#define CAN_CONTROL_ROP_Pos                     4

/* Bit field masks: */
#define CAN_CONTROL_CAN_EN                      ((uint32_t)0x00000001)
#define CAN_CONTROL_ROM                         ((uint32_t)0x00000002)
#define CAN_CONTROL_STM                         ((uint32_t)0x00000004)
#define CAN_CONTROL_SAP                         ((uint32_t)0x00000008)
#define CAN_CONTROL_ROP                         ((uint32_t)0x00000010)

/*-- CAN_STATUS: CAN Status Register -------------------------------*/
/* Bit field positions: */
#define CAN_STATUS_RX_READY_Pos                 0
#define CAN_STATUS_TX_READY_Pos                 1
#define CAN_STATUS_ERROR_OVER_Pos               2
#define CAN_STATUS_BIT_ERR_Pos                  3
#define CAN_STATUS_BIT_STUFF_ERR_Pos            4
#define CAN_STATUS_CRC_ERR_Pos                  5
#define CAN_STATUS_FRAME_ERR_Pos                6
#define CAN_STATUS_ACK_ERR_Pos                  7
#define CAN_STATUS_IDLOWER_Pos                  8
#define CAN_STATUS_ERR_STATUS_Pos               9
#define CAN_STATUS_RX_ERR_CNT8_Pos              11
#define CAN_STATUS_TX_ERR_CNT8_Pos              12
#define CAN_STATUS_RX_ERR_CNT_Pos               16
#define CAN_STATUS_TX_ERR_CNT_Pos               24

/* Bit field masks: */
#define CAN_STATUS_RX_READY                     ((uint32_t)0x00000001)
#define CAN_STATUS_TX_READY                     ((uint32_t)0x00000002)
#define CAN_STATUS_ERROR_OVER                   ((uint32_t)0x00000004)
#define CAN_STATUS_BIT_ERR                      ((uint32_t)0x00000008)
#define CAN_STATUS_BIT_STUFF_ERR                ((uint32_t)0x00000010)
#define CAN_STATUS_CRC_ERR                      ((uint32_t)0x00000020)
#define CAN_STATUS_FRAME_ERR                    ((uint32_t)0x00000040)
#define CAN_STATUS_ACK_ERR                      ((uint32_t)0x00000080)
#define CAN_STATUS_IDLOWER                      ((uint32_t)0x00000100)
#define CAN_STATUS_ERR_STATUS_Msk               ((uint32_t)0x00000600)
#define CAN_STATUS_RX_ERR_CNT8                  ((uint32_t)0x00000800)
#define CAN_STATUS_TX_ERR_CNT8                  ((uint32_t)0x00001000)
#define CAN_STATUS_RX_ERR_CNT_Msk               ((uint32_t)0x00FF0000)
#define CAN_STATUS_TX_ERR_CNT_Msk               ((uint32_t)0xFF000000)

/*-- CAN_BITTMNG: CAN Bittiming Register ---------------------------*/
/* Bit field positions: */
#define CAN_BITTMNG_BRP_Pos                     0
#define CAN_BITTMNG_PSEG_Pos                    16
#define CAN_BITTMNG_SEG1_Pos                    19
#define CAN_BITTMNG_SEG2_Pos                    22
#define CAN_BITTMNG_SJW_Pos                     25
#define CAN_BITTMNG_SB_Pos                      27

/* Bit field masks: */
#define CAN_BITTMNG_BRP_Msk                     ((uint32_t)0x0000FFFF)
#define CAN_BITTMNG_PSEG_Msk                    ((uint32_t)0x00070000)
#define CAN_BITTMNG_SEG1_Msk                    ((uint32_t)0x00380000)
#define CAN_BITTMNG_SEG2_Msk                    ((uint32_t)0x01C00000)
#define CAN_BITTMNG_SJW_Msk                     ((uint32_t)0x06000000)
#define CAN_BITTMNG_SB                          ((uint32_t)0x08000000)

/*-- CAN_INT_EN: CAN Interrupt enable Register ---------------------*/
/* Bit field positions: */
#define CAN_INT_EN_GLB_INT_EN_Pos               0
#define CAN_INT_EN_RX_INT_EN_Pos                1
#define CAN_INT_EN_TX_INT_EN_Pos                2
#define CAN_INT_EN_ERR_INT_EN_Pos               3
#define CAN_INT_EN_ERR_OVER_INT_EN_Pos          4

/* Bit field masks: */
#define CAN_INT_EN_GLB_INT_EN                   ((uint32_t)0x00000001)
#define CAN_INT_EN_RX_INT_EN                    ((uint32_t)0x00000002)
#define CAN_INT_EN_TX_INT_EN                    ((uint32_t)0x00000004)
#define CAN_INT_EN_ERR_INT_EN                   ((uint32_t)0x00000008)
#define CAN_INT_EN_ERR_OVER_INT_EN              ((uint32_t)0x00000010)

/*-- CAN_RXID:   CAN Receive ID Register ---------------------------*/
/*-- CAN_TXID:   CAN Transmit ID Register --------------------------*/
/*-- CAN_BUF_ID: CAN Buffer ID Register ----------------------------*/
/* Bit field positions: */
#define CAN_ID_EID_Pos                          0
#define CAN_ID_SID_Pos                          18

/* Bit field masks: */
#define CAN_ID_EID_Msk                          ((uint32_t)0x0003FFFF)
#define CAN_ID_SID_Msk                          ((uint32_t)0x1FFC0000)

/*-- CAN_RXDLC:   CAN Receive DLC Register -------------------------*/
/*-- CAN_TXDLC:   CAN Transmit DLC Register ------------------------*/
/*-- CAN_BUF_DLC: CAN Buffer DLC Register --------------------------*/
/* Bit field positions: */
#define CAN_DLC_Pos                             0
#define CAN_DLC_RTR_Pos                         8
#define CAN_DLC_R1_Pos                          9
#define CAN_DLC_R0_Pos                          10
#define CAN_DLC_SSR_Pos                         11
#define CAN_DLC_IDE_Pos                         12

/* Bit field masks: */
#define CAN_DLC_Msk                             ((uint32_t)0x0000000F)
#define CAN_DLC_RTR                             ((uint32_t)0x00000100)
#define CAN_DLC_R1                              ((uint32_t)0x00000200)
#define CAN_DLC_R0                              ((uint32_t)0x00000400)
#define CAN_DLC_SSR                             ((uint32_t)0x00000800)
#define CAN_DLC_IDE                             ((uint32_t)0x00001000)

/*-- CAN_RXDATAL:   CAN Receive Data low Register ------------------*/
/*-- CAN_DATAL:     CAN Transmit Data low Register -----------------*/
/*-- CAN_BUF_DATAL: CAN Buffer Data low Register -------------------*/
/* Bit field positions: */
#define CAN_DATAL_DB0_Pos                       0
#define CAN_DATAL_DB1_Pos                       8
#define CAN_DATAL_DB2_Pos                       16
#define CAN_DATAL_DB3_Pos                       24

/* Bit field masks: */
#define CAN_DATAL_DB0_Msk                       ((uint32_t)0x000000FF)
#define CAN_DATAL_DB1_Msk                       ((uint32_t)0x0000FF00)
#define CAN_DATAL_DB2_Msk                       ((uint32_t)0x00FF0000)
#define CAN_DATAL_DB3_Msk                       ((uint32_t)0xFF000000)

/*-- CAN_RXDATAH:   CAN Receive Data high Register -----------------*/
/*-- CAN_DATAH:     CAN Transmit Data high Register ----------------*/
/*-- CAN_BUF_DATAH: CAN Buffer Data high Register ------------------*/
/* Bit field positions: */
#define CAN_DATAH_DB4_Pos                       0
#define CAN_DATAH_DB5_Pos                       8
#define CAN_DATAH_DB6_Pos                       16
#define CAN_DATAH_DB7_Pos                       24

/* Bit field masks: */
#define CAN_DATAH_DB4_Msk                       ((uint32_t)0x000000FF)
#define CAN_DATAH_DB5_Msk                       ((uint32_t)0x0000FF00)
#define CAN_DATAH_DB6_Msk                       ((uint32_t)0x00FF0000)
#define CAN_DATAH_DB7_Msk                       ((uint32_t)0xFF000000)

/*-- CAN_BUF_CON: CAN Buffer Connection Register -------------------*/
/* Bit field positions: */
#define CAN_BUF_CON_EN_Pos                      0
#define CAN_BUF_CON_RX_TXN_Pos                  1
#define CAN_BUF_CON_OVER_EN_Pos                 2
#define CAN_BUF_CON_RTR_EN_Pos                  3
#define CAN_BUF_CON_PRIOR_0_Pos                 4
#define CAN_BUF_CON_TX_REQ_Pos                  5
#define CAN_BUF_CON_RX_FULL_Pos                 6
#define CAN_BUF_CON_OVER_WR_Pos                 7

/* Bit field masks: */
#define CAN_BUF_CON_EN                          ((uint32_t)0x00000001)
#define CAN_BUF_CON_RX_TXN                      ((uint32_t)0x00000002)
#define CAN_BUF_CON_OVER_EN                     ((uint32_t)0x00000004)
#define CAN_BUF_CON_RTR_EN                      ((uint32_t)0x00000008)
#define CAN_BUF_CON_PRIOR_0                     ((uint32_t)0x00000010)
#define CAN_BUF_CON_TX_REQ                      ((uint32_t)0x00000020)
#define CAN_BUF_CON_RX_FULL                     ((uint32_t)0x00000040)
#define CAN_BUF_CON_OVER_WR                     ((uint32_t)0x00000080)


/** @} */ /* End of group __MDR1986VK01_Periph_CAN */


/** @defgroup __MDR1986VK01_Periph_UART	UART
  * @{
  */

typedef struct
{
  __IO  uint32_t DR;
  __IO  uint32_t RSR_ECR;
  __IO  uint32_t Reserved1[4];
  __IO  uint32_t FR;
  __IO  uint32_t Reserved2;
  __IO  uint32_t ILPR;
  __IO  uint32_t IBRD;
  __IO  uint32_t FBRD;
  __IO  uint32_t LCR_H;
  __IO  uint32_t CR;
  __IO  uint32_t IFLS;
  __IO  uint32_t IMSC;
  __IO  uint32_t RIS;
  __IO  uint32_t MIS;
  __IO  uint32_t ICR;
  __IO  uint32_t DMACR;
}MDR_UART_TypeDef;

#define MDR_UART_BASE             (PERIPH_BASE   + 0x80000)

#define MDR_UART0_BASE            (MDR_UART_BASE + 0x0D000)
#define MDR_UART1_BASE            (MDR_UART_BASE + 0x0E000)
#define MDR_UART2_BASE            (MDR_UART_BASE + 0x0F000)
#define MDR_UART3_BASE            (MDR_UART_BASE + 0x10000)

#define MDR_UART0                 ((MDR_UART_TypeDef *) MDR_UART0_BASE)
#define MDR_UART1                 ((MDR_UART_TypeDef *) MDR_UART1_BASE)
#define MDR_UART2                 ((MDR_UART_TypeDef *) MDR_UART2_BASE)
#define MDR_UART3                 ((MDR_UART_TypeDef *) MDR_UART3_BASE)

/** @defgroup __MDR1986VK01_Periph_UART_DR	UART_DR
  * @{
  */

/* Bit field positions: */
#define UART_DR_DATA_Pos                        0
#define UART_DR_FE_Pos                          8
#define UART_DR_PE_Pos                          9
#define UART_DR_BE_Pos                          10
#define UART_DR_OE_Pos                          11

/* Bit field masks: */
#define UART_DR_DATA_Msk                        ((uint32_t)0x000000FF)
#define UART_DR_FE                              ((uint32_t)0x00000100)
#define UART_DR_PE                              ((uint32_t)0x00000200)
#define UART_DR_BE                              ((uint32_t)0x00000400)
#define UART_DR_OE                              ((uint32_t)0x00000800)

/** @} */ /* End of group __MDR1986VK01_Periph_UART_DR */

/** @defgroup Periph_UART_RSR_ECR	UART RSR ECR
  * @{
  */

/* Bit field positions: */
#define UART_RSR_ECR_FE_Pos                     0
#define UART_RSR_ECR_PE_Pos                     1
#define UART_RSR_ECR_BE_Pos                     2
#define UART_RSR_ECR_OE_Pos                     3

/* Bit field masks: */
#define UART_RSR_ECR_FE                         ((uint32_t)0x00000001)
#define UART_RSR_ECR_PE                         ((uint32_t)0x00000002)
#define UART_RSR_ECR_BE                         ((uint32_t)0x00000004)
#define UART_RSR_ECR_OE                         ((uint32_t)0x00000008)

/** @} */ /* End of group Periph_UART_RSR_ECR */

/** @defgroup Periph_UART_FR	UART FR
  * @{
  */

/* Bit field positions: */
#define UART_FR_CTS_Pos                         0
#define UART_FR_DSR_Pos                         1
#define UART_FR_DCD_Pos                         2
#define UART_FR_BUSY_Pos                        3
#define UART_FR_RXFE_Pos                        4
#define UART_FR_TXFF_Pos                        5
#define UART_FR_RXFF_Pos                        6
#define UART_FR_TXFE_Pos                        7
#define UART_FR_RI_Pos                          8

/* Bit field masks: */
#define UART_FR_CTS                             ((uint32_t)0x00000001)
#define UART_FR_DSR                             ((uint32_t)0x00000002)
#define UART_FR_DCD                             ((uint32_t)0x00000004)
#define UART_FR_BUSY                            ((uint32_t)0x00000008)
#define UART_FR_RXFE                            ((uint32_t)0x00000010)
#define UART_FR_TXFF                            ((uint32_t)0x00000020)
#define UART_FR_RXFF                            ((uint32_t)0x00000040)
#define UART_FR_TXFE                            ((uint32_t)0x00000080)
#define UART_FR_RI                              ((uint32_t)0x00000100)

/** @} */ /* End of group Periph_UART_FR */

/** @defgroup Periph_UART_LCR_H	UART LCR H
  * @{
  */

/* Bit field positions: */
#define UART_LCR_H_BRK_Pos                      0
#define UART_LCR_H_PEN_Pos                      1
#define UART_LCR_H_EPS_Pos                      2
#define UART_LCR_H_STP2_Pos                     3
#define UART_LCR_H_FEN_Pos                      4
#define UART_LCR_H_WLEN_Pos                     5
#define UART_LCR_H_SPS_Pos                      7

/* Bit field masks: */
#define UART_LCR_H_BRK                          ((uint32_t)0x00000001)
#define UART_LCR_H_PEN                          ((uint32_t)0x00000002)
#define UART_LCR_H_EPS                          ((uint32_t)0x00000004)
#define UART_LCR_H_STP2                         ((uint32_t)0x00000008)
#define UART_LCR_H_FEN                          ((uint32_t)0x00000010)
#define UART_LCR_H_WLEN_Msk                     ((uint32_t)0x00000060)
#define UART_LCR_H_SPS                          ((uint32_t)0x00000080)

/** @} */ /* End of group Periph_UART_LCR_H */

/** @defgroup Periph_UART_CR	UART CR
  * @{
  */

/* Bit field positions: */
#define UART_CR_UARTEN_Pos                      0
#define UART_CR_SIREN_Pos                       1
#define UART_CR_SIRLP_Pos                       2
#define UART_CR_LBE_Pos                         7
#define UART_CR_TXE_Pos                         8
#define UART_CR_RXE_Pos                         9
#define UART_CR_DTR_Pos                         10
#define UART_CR_RTS_Pos                         11
#define UART_CR_OUT1_Pos                        12
#define UART_CR_OUT2_Pos                        13
#define UART_CR_RTSEN_Pos                       14
#define UART_CR_CTSEN_Pos                       15

/* Bit field masks: */
#define UART_CR_UARTEN                          ((uint32_t)0x00000001)
#define UART_CR_SIREN                           ((uint32_t)0x00000002)
#define UART_CR_SIRLP                           ((uint32_t)0x00000004)
#define UART_CR_LBE                             ((uint32_t)0x00000080)
#define UART_CR_TXE                             ((uint32_t)0x00000100)
#define UART_CR_RXE                             ((uint32_t)0x00000200)
#define UART_CR_DTR                             ((uint32_t)0x00000400)
#define UART_CR_RTS                             ((uint32_t)0x00000800)
#define UART_CR_OUT1                            ((uint32_t)0x00001000)
#define UART_CR_OUT2                            ((uint32_t)0x00002000)
#define UART_CR_RTSEN                           ((uint32_t)0x00004000)
#define UART_CR_CTSEN                           ((uint32_t)0x00008000)

/** @} */ /* End of group Periph_UART_CR */

/** @defgroup Periph_UART_IFLS	UART IFLS
  * @{
  */

/*-- UART_IFLS: UART IFLS Register ---------------------------------*/
/* Bit field positions: */
#define UART_IFLS_TXIFLSEL_Pos                  0
#define UART_IFLS_RXIFLSEL_Pos                  3

/* Bit field masks: */
#define UART_IFLS_TXIFLSEL_Msk                  ((uint32_t)0x00000007)
#define UART_IFLS_RXIFLSEL_Msk                  ((uint32_t)0x00000038)

/** @} */ /* End of group Periph_UART_IFLS */

/** @defgroup Periph_UART_IMSC	UART IMSC
  * @{
  */

/**
  * @brief UART Interrupt Mask Register
  */

/* Bit field positions: */
#define UART_IMSC_RIMIM_Pos                     0
#define UART_IMSC_CTSMIM_Pos                    1
#define UART_IMSC_DCDMIM_Pos                    2
#define UART_IMSC_DSRMIM_Pos                    3
#define UART_IMSC_RXIM_Pos                      4
#define UART_IMSC_TXIM_Pos                      5
#define UART_IMSC_RTIM_Pos                      6
#define UART_IMSC_FEIM_Pos                      7
#define UART_IMSC_PEIM_Pos                      8
#define UART_IMSC_BEIM_Pos                      9
#define UART_IMSC_OEIM_Pos                      10

/* Bit field masks: */
#define UART_IMSC_RIMIM                         ((uint32_t)0x00000001)
#define UART_IMSC_CTSMIM                        ((uint32_t)0x00000002)
#define UART_IMSC_DCDMIM                        ((uint32_t)0x00000004)
#define UART_IMSC_DSRMIM                        ((uint32_t)0x00000008)
#define UART_IMSC_RXIM                          ((uint32_t)0x00000010)
#define UART_IMSC_TXIM                          ((uint32_t)0x00000020)
#define UART_IMSC_RTIM                          ((uint32_t)0x00000040)
#define UART_IMSC_FEIM                          ((uint32_t)0x00000080)
#define UART_IMSC_PEIM                          ((uint32_t)0x00000100)
#define UART_IMSC_BEIM                          ((uint32_t)0x00000200)
#define UART_IMSC_OEIM                          ((uint32_t)0x00000400)

/** @} */ /* End of group UART_IMSC */

/** @defgroup Periph_UART_RIS	UART RIS
  * @{
  */

/**
  * @brief UART Interrupt Pending Register
  */

/* Bit field positions: */
#define UART_RIS_RIRMIS_Pos                     0
#define UART_RIS_CTSRMIS_Pos                    1
#define UART_RIS_DCDRMIS_Pos                    2
#define UART_RIS_DSRRMIS_Pos                    3
#define UART_RIS_RXRIS_Pos                      4
#define UART_RIS_TXRIS_Pos                      5
#define UART_RIS_RTRIS_Pos                      6
#define UART_RIS_FERIS_Pos                      7
#define UART_RIS_PERIS_Pos                      8
#define UART_RIS_BERIS_Pos                      9
#define UART_RIS_OERIS_Pos                      10

/* Bit field masks: */
#define UART_RIS_RIRMIS                         ((uint32_t)0x00000001)
#define UART_RIS_CTSRMIS                        ((uint32_t)0x00000002)
#define UART_RIS_DCDRMIS                        ((uint32_t)0x00000004)
#define UART_RIS_DSRRMIS                        ((uint32_t)0x00000008)
#define UART_RIS_RXRIS                          ((uint32_t)0x00000010)
#define UART_RIS_TXRIS                          ((uint32_t)0x00000020)
#define UART_RIS_RTRIS                          ((uint32_t)0x00000040)
#define UART_RIS_FERIS                          ((uint32_t)0x00000080)
#define UART_RIS_PERIS                          ((uint32_t)0x00000100)
#define UART_RIS_BERIS                          ((uint32_t)0x00000200)
#define UART_RIS_OERIS                          ((uint32_t)0x00000400)

/** @} */ /* End of group Periph_UART_RIS */

/** @defgroup Periph_UART_MIS	UART MIS
  * @{
  */

/**
  * @brief UART Masked Interrupt Pending Register
  */

/* Bit field positions: */
#define UART_MIS_RIMMIS_Pos                     0
#define UART_MIS_CTSMMIS_Pos                    1
#define UART_MIS_DCDMMIS_Pos                    2
#define UART_MIS_DSRMMIS_Pos                    3
#define UART_MIS_RXMIS_Pos                      4
#define UART_MIS_TXMIS_Pos                      5
#define UART_MIS_RTMIS_Pos                      6
#define UART_MIS_FEMIS_Pos                      7
#define UART_MIS_PEMIS_Pos                      8
#define UART_MIS_BEMIS_Pos                      9
#define UART_MIS_OEMIS_Pos                      10

/* Bit field masks: */
#define UART_MIS_RIMMIS                         ((uint32_t)0x00000001)
#define UART_MIS_CTSMMIS                        ((uint32_t)0x00000002)
#define UART_MIS_DCDMMIS                        ((uint32_t)0x00000004)
#define UART_MIS_DSRMMIS                        ((uint32_t)0x00000008)
#define UART_MIS_RXMIS                          ((uint32_t)0x00000010)
#define UART_MIS_TXMIS                          ((uint32_t)0x00000020)
#define UART_MIS_RTMIS                          ((uint32_t)0x00000040)
#define UART_MIS_FEMIS                          ((uint32_t)0x00000080)
#define UART_MIS_PEMIS                          ((uint32_t)0x00000100)
#define UART_MIS_BEMIS                          ((uint32_t)0x00000200)
#define UART_MIS_OEMIS                          ((uint32_t)0x00000400)

/** @} */ /* End of group Periph_UART_MIS */

/** @defgroup Periph_UART_ICR	UART ICR
  * @{
  */

/**
  * @brief UART Interrupt Clear Register
  */

/* Bit field positions: */
#define UART_ICR_RIMIC_Pos                      0
#define UART_ICR_CTSMIC_Pos                     1
#define UART_ICR_DCDMIC_Pos                     2
#define UART_ICR_DSRMIC_Pos                     3
#define UART_ICR_RXIC_Pos                       4
#define UART_ICR_TXIC_Pos                       5
#define UART_ICR_RTIC_Pos                       6
#define UART_ICR_FEIC_Pos                       7
#define UART_ICR_PEIC_Pos                       8
#define UART_ICR_BEIC_Pos                       9
#define UART_ICR_OEIC_Pos                       10

/* Bit field masks: */
#define UART_ICR_RIMIC                          ((uint32_t)0x00000001)
#define UART_ICR_CTSMIC                         ((uint32_t)0x00000002)
#define UART_ICR_DCDMIC                         ((uint32_t)0x00000004)
#define UART_ICR_DSRMIC                         ((uint32_t)0x00000008)
#define UART_ICR_RXIC                           ((uint32_t)0x00000010)
#define UART_ICR_TXIC                           ((uint32_t)0x00000020)
#define UART_ICR_RTIC                           ((uint32_t)0x00000040)
#define UART_ICR_FEIC                           ((uint32_t)0x00000080)
#define UART_ICR_PEIC                           ((uint32_t)0x00000100)
#define UART_ICR_BEIC                           ((uint32_t)0x00000200)
#define UART_ICR_OEIC                           ((uint32_t)0x00000400)

/** @} */ /* End of group Periph_UART_ICR */

/** @defgroup Periph_UART_DMACR	UART DMACR
  * @{
  */

/**
  * @brief UART DMA Control Register
  */

/* Bit field positions: */
#define UART_DMACR_RXDMAE_Pos                   0
#define UART_DMACR_TXDMAE_Pos                   1
#define UART_DMACR_DMAONERR_Pos                 2

/* Bit field masks: */
#define UART_DMACR_RXDMAE                       ((uint32_t)0x00000001)
#define UART_DMACR_TXDMAE                       ((uint32_t)0x00000002)
#define UART_DMACR_DMAONERR                     ((uint32_t)0x00000004)

/** @} */ /* End of group Periph_UART_DMACR */

/** @} */ /* End of group __MDR1986VK01_Periph_UART */


/** @defgroup __MDR1986VK01_Periph_MIL_STD_1553	MIL_STD_1553
  * @{
  */

/**
  * @brief MDR1986VK01 MIL_STD_1553 Control
  */

typedef struct
{
  __IO  uint32_t CONTROL;
  __IO  uint32_t STATUS;
  __IO  uint32_t ERROR;
  __IO  uint32_t CommandWord1;
  __IO  uint32_t CommandWord2;
  __IO  uint32_t ModeData;
  __IO  uint32_t StatusWord1;
  __IO  uint32_t StatusWord2;
  __IO  uint32_t INTEN;
  __IO  uint32_t MSG;
  __IO  uint32_t RESERVED[1014];
  __IO  uint32_t DATA[1024];
} MIL1553Control;

#define MDR_MIL0_1553_BASE             (PERIPH_BASE + 0x90000 + 0x1000)
#define MDR_MIL1_1553_BASE             (PERIPH_BASE + 0x80000 + 0x7000)

#define MDR_MIL0_STD_1553             ((MIL1553Control *) MDR_MIL0_1553_BASE)
#define MDR_MIL1_STD_1553             ((MIL1553Control *) MDR_MIL1_1553_BASE)

/*-- MIL_STD_1553_CONTROL: MIL_STD_1553 Control Register -----*/
/* Bit field positions: */
#define MIL_STD_1553_CONTROL_MR_Pos            0
#define MIL_STD_1553_CONTROL_BCSTART_Pos       1
#define MIL_STD_1553_CONTROL_BCMODE_Pos        2
#define MIL_STD_1553_CONTROL_RTMODE_Pos        3
#define MIL_STD_1553_CONTROL_TRA_Pos           4
#define MIL_STD_1553_CONTROL_TRB_Pos           5
#define MIL_STD_1553_CONTROL_RTA_Pos           6
#define MIL_STD_1553_CONTROL_DIV_Pos           11
#define MIL_STD_1553_CONTROL_RERR_Pos          18
#define MIL_STD_1553_CONTROL_INVTR_Pos		   19
#define MIL_STD_1553_CONTROL_ENFILTER_Pos	   20
#define MIL_STD_1553_CONTROL_AUTOTUNE_Pos	   21

/* Bit field masks: */
#define MIL_STD_1553_CONTROL_MR                 ((uint32_t)0x00000001)
#define MIL_STD_1553_CONTROL_BCSTART            ((uint32_t)0x00000002)
#define MIL_STD_1553_CONTROL_BCMODE			    ((uint32_t)0x00000004)
#define MIL_STD_1553_CONTROL_RTMODE             ((uint32_t)0x00000008)
#define MIL_STD_1553_CONTROL_TRA                ((uint32_t)0x00000010)
#define MIL_STD_1553_CONTROL_TRB                ((uint32_t)0x00000020)
#define MIL_STD_1553_CONTROL_RTA_Msk            ((uint32_t)0x000007C0)
#define MIL_STD_1553_CONTROL_DIV_Msk            ((uint32_t)0x0003F800)
#define MIL_STD_1553_CONTROL_RERR               ((uint32_t)0x00040000)
#define MIL_STD_1553_CONTROL_INVTR				((uint32_t)0x00080000)
#define MIL_STD_1553_CONTROL_ENFILTER		    ((uint32_t)0x00100000)
#define MIL_STD_1553_CONTROL_AUTOTUNE		    ((uint32_t)0x00200000)

/*-- MIL_STD_1553_STATUS: MIL_STD_1553 Status Register -----*/
/* Bit field positions: */
#define MIL_STD_1553_STATUS_IDLE_Pos            	 0
#define MIL_STD_1553_STATUS_RFLAGN_Pos            	 1
#define MIL_STD_1553_STATUS_VALMESS_Pos            	 2
#define MIL_STD_1553_STATUS_ERR_Pos	            	 3
#define MIL_STD_1553_STATUS_RCVA_Pos            	 4
#define MIL_STD_1553_STATUS_RCVB_Pos            	 5

/* Bit field masks: */
#define MIL_STD_1553_STATUS_IDLE            		 ((uint32_t)0x00000001)
#define MIL_STD_1553_STATUS_RFLAGN          	  	 ((uint32_t)0x00000002)
#define MIL_STD_1553_STATUS_VALMESS     	       	 ((uint32_t)0x00000004)
#define MIL_STD_1553_STATUS_ERR	     	   	    	 ((uint32_t)0x00000008)
#define MIL_STD_1553_STATUS_RCVA	            	 ((uint32_t)0x00000010)
#define MIL_STD_1553_STATUS_RCVB 	  	         	 ((uint32_t)0x00000020)

/*-- MIL_STD_1553_ERROR: MIL_STD_1553 ERROR Register -----*/
/* Bit field positions: */
#define MIL_STD_1553_ERROR_NORCV_Pos           0
#define MIL_STD_1553_ERROR_MANERR_Pos          1
#define MIL_STD_1553_ERROR_SYNCERR_Pos         2
#define MIL_STD_1553_ERROR_SEQERR_Pos          3
#define MIL_STD_1553_ERROR_GAPERR_Pos          4
#define MIL_STD_1553_ERROR_CONERR_Pos          5
#define MIL_STD_1553_ERROR_PROERR_Pos          6

/* Bit field masks: */
#define MIL_STD_1553_ERROR_NORCV                ((uint32_t)0x00000001)
#define MIL_STD_1553_ERROR_MANERR               ((uint32_t)0x00000002)
#define MIL_STD_1553_ERROR_SYNCERR              ((uint32_t)0x00000004)
#define MIL_STD_1553_ERROR_SEQERR               ((uint32_t)0x00000008)
#define MIL_STD_1553_ERROR_GAPERR               ((uint32_t)0x00000010)
#define MIL_STD_1553_ERROR_CONERR               ((uint32_t)0x00000020)
#define MIL_STD_1553_ERROR_PROERR               ((uint32_t)0x00000040)

/*-- MIL_STD_1553_ITEEN: MIL_STD_1553 ITEEN Register -----*/
/* Bit field positions: */
#define MIL_STD_1553_INTEN_IDLEIE_Pos          0
#define MIL_STD_1553_INTEN_RFLAGNIE_Pos        1
#define MIL_STD_1553_INTEN_VALMESSIE_Pos       2
#define MIL_STD_1553_INTEN_ERRIE_Pos           3

/* Bit field masks: */
#define MIL_STD_1553_INTEN_IDLEIE               ((uint32_t)0x00000001)
#define MIL_STD_1553_INTEN_RFLAGNIE             ((uint32_t)0x00000002)
#define MIL_STD_1553_INTEN_VALMESSIE            ((uint32_t)0x00000004)
#define MIL_STD_1553_INTEN_ERRIE                ((uint32_t)0x00000008)

/** @} */ /* End of group __MDR1986VK01_Periph_MIL_STD_1553 */


/** @defgroup __MDR1986VK01_Periph_USB_RAM	USB_RAM
  * @{
  */

/**
  * @brief MDR1986VK01 USB_RAM interface
  */

typedef struct
{
  /* Common USB registers */
  __IO uint32_t  USB_RAM_CNTR;
  __IO uint32_t  USB_M31_CNTR;
}
USBRAM_Typedef;

#define MDR_USB_RAM_BASE          (PERIPH_BASE      + 0x90000)

#define MDR_USB_RAM0_BASE         (MDR_USB_RAM_BASE + 0x03000)

#define MDR_USB_RAM0              ((USBRAM_Typedef *) MDR_USB_RAM0_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_USB_RAM */


/** @defgroup __MDR1986VK01_Periph_TIMER MDR_TIMERx
  * @{
  */

/**
  * @brief MDR1986VK01 TIMER32 control
  */

typedef struct
{
  __IO  uint32_t CNT;
  __IO  uint32_t PSG;
  __IO  uint32_t ARR;
  __IO  uint32_t CNTRL;
  __IO  uint32_t CCR1;
  __IO  uint32_t CCR2;
  __IO  uint32_t CCR3;
  __IO  uint32_t CCR4;
  __IO  uint32_t CH1_CNTRL;
  __IO  uint32_t CH2_CNTRL;
  __IO  uint32_t CH3_CNTRL;
  __IO  uint32_t CH4_CNTRL;
  __IO  uint32_t CH1_CNTRL1;
  __IO  uint32_t CH2_CNTRL1;
  __IO  uint32_t CH3_CNTRL1;
  __IO  uint32_t CH4_CNTRL1;
  __IO  uint32_t CH1_DTG;
  __IO  uint32_t CH2_DTG;
  __IO  uint32_t CH3_DTG;
  __IO  uint32_t CH4_DTG;
  __IO  uint32_t BRKETR_CNTRL;
  __IO  uint32_t STATUS;
  __IO  uint32_t IE;
  __IO  uint32_t DMA_RE;
  __IO  uint32_t CH1_CNTRL2;
  __IO  uint32_t CH2_CNTRL2;
  __IO  uint32_t CH3_CNTRL2;
  __IO  uint32_t CH4_CNTRL2;
  __IO  uint32_t CCR11;
  __IO  uint32_t CCR21;
  __IO  uint32_t CCR31;
  __IO  uint32_t CCR41;
  __IO  uint32_t DMA_REChx[4];
}MDR_TIMER_TypeDef;

#define MDR_TIMER_BASE            (PERIPH_BASE + 0x90000)

#define MDR_TIMER0_BASE           (MDR_TIMER_BASE + 0x4000)
#define MDR_TIMER1_BASE           (MDR_TIMER_BASE + 0x5000)
#define MDR_TIMER2_BASE           (MDR_TIMER_BASE + 0x6000)
#define MDR_TIMER3_BASE           (MDR_TIMER_BASE + 0x7000)

#define MDR_TIMER0                ((MDR_TIMER_TypeDef *) MDR_TIMER0_BASE)
#define MDR_TIMER1                ((MDR_TIMER_TypeDef *) MDR_TIMER1_BASE)
#define MDR_TIMER2                ((MDR_TIMER_TypeDef *) MDR_TIMER2_BASE)
#define MDR_TIMER3                ((MDR_TIMER_TypeDef *) MDR_TIMER3_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_TIMER */


/** @defgroup __MDR1986VK01_Periph_CAP	MDR_CAP
  * @{
  */

/**
  * @brief MDR1986VK01 CAPx control
  */

typedef struct
{
  __IO  uint32_t TSCTR;
  __IO  uint32_t CTRPHS;
  __IO  uint32_t CAP1;
  __IO  uint32_t CAP2;
  __IO  uint32_t CAP3;
  __IO  uint32_t CAP4;
  __IO  uint32_t ECCTL1;
  __IO  uint32_t ECCTL2;
  __IO  uint32_t ECEINT;
  __IO  uint32_t ECFLG;
  __IO  uint32_t ECCLR;
  __IO  uint32_t ECFRC;
} CAPControl;

#define MDR_CAP_BASE              (PERIPH_BASE + 0x90000)

#define MDR_CAP0_BASE                 (MDR_CAP_BASE + 0x8000)
#define MDR_CAP1_BASE                 (MDR_CAP_BASE + 0x9000)
#define MDR_CAP2_BASE                 (MDR_CAP_BASE + 0xA000)
#define MDR_CAP3_BASE                 (MDR_CAP_BASE + 0xB000)

#define MDR_CAP0                  ((CAPControl  *) MDR_CAP0_BASE)
#define MDR_CAP1                  ((CAPControl  *) MDR_CAP1_BASE)
#define MDR_CAP2                  ((CAPControl  *) MDR_CAP2_BASE)
#define MDR_CAP3                  ((CAPControl  *) MDR_CAP3_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_CAP */


/** @defgroup __MDR1986VK01_Periph_QEP	MDR_QEP
  * @{
  */

/**
  * @brief MDR1986VK01 QEPx control
  */

typedef struct
{
  __IO  uint32_t QDECCTL;
  __IO  uint32_t QEPCTL;
  __IO  uint32_t QPOSCTL;
  __IO  uint32_t QCAPCTL;
  __IO  uint32_t QPOSCNT;
  __IO  uint32_t QPOSINIT;
  __IO  uint32_t QPOSMAX;
  __IO  uint32_t QPOSCMP;
  __IO  uint32_t QPOSILAT;
  __IO  uint32_t QPOSSLAT;
  __IO  uint32_t QPOSLAT;
  __IO  uint32_t QUTMR;
  __IO  uint32_t QUPRD;
  __IO  uint32_t QWDTMR;
  __IO  uint32_t QEINT;
  __IO  uint32_t QFLG;
  __IO  uint32_t QCLR;
  __IO  uint32_t QFRC;
  __IO  uint32_t QEPSTS;
  __IO  uint32_t QWDPRD;
  __IO  uint32_t QCTMR;
  __IO  uint32_t QCTMR1;
  __IO  uint32_t QCTMR2;
  __IO  uint32_t QCTMR3;
  __IO  uint32_t QCTMR4;
  __IO  uint32_t QCPRD;
  __IO  uint32_t QCTMRLAT;
  __IO  uint32_t QCPRDLAT;
} QEPControl;

#define MDR_QEP_BASE              (PERIPH_BASE + 0x90000)

#define MDR_QEP0_BASE                 (MDR_QEP_BASE + 0xC000)
#define MDR_QEP1_BASE                 (MDR_QEP_BASE + 0xD000)

#define MDR_QEP0                      ((QEPControl  *) MDR_QEP0_BASE)
#define MDR_QEP1                      ((QEPControl  *) MDR_QEP1_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_QEP */


/** @defgroup __MDR1986VK01_Periph_PWM	MDR_PWMx
  * @{
  */

/**
  * @brief MDR1986VK01 PWMx control
  */

typedef struct
{
  __IO  uint32_t TBPRD;
  uint32_t RESERVED0;
  __IO  uint32_t TBPHS;
  __IO  uint32_t TBCTR;
  __IO  uint32_t TBCTL;
  __IO  uint32_t TBSTS;
  __IO  uint32_t CMPA;
  __IO  uint32_t CMPB;
  __IO  uint32_t CMPCTL;
  uint32_t RESERVED1;
  __IO  uint32_t AQCTLA;
  __IO  uint32_t AQCTLB;
  __IO  uint32_t AQSFRC;
  __IO  uint32_t AQCSFRC;
  __IO  uint32_t DBCTL;
  __IO  uint32_t DBRED;
  __IO  uint32_t DBFED;
  __IO  uint32_t PCCTL;
  __IO  uint32_t TZSEL;
  __IO  uint32_t TZCTL;
  __IO  uint32_t TZEINT;
  __IO  uint32_t TZFLG;
  __IO  uint32_t TZCLR;
  __IO  uint32_t TZFRC;
  __IO  uint32_t ETSEL;
  __IO  uint32_t ETPS;
  __IO  uint32_t ETFLG;
  __IO  uint32_t ETCLR;
  __IO  uint32_t ETFRC;
  uint32_t RESERVED2;
  uint32_t RESERVED3;
  __IO  uint32_t HRPWM_CTRL;

} PWMControl;

#define MDR_PWM_BASE              (PERIPH_BASE +  0x9E000)

#define MDR_PWM0_BASE                 (MDR_PWM_BASE + 0x00000)
#define MDR_PWM1_BASE                 (MDR_PWM_BASE + 0x01000)
#define MDR_PWM2_BASE                 (MDR_PWM_BASE + 0x02000)
#define MDR_PWM3_BASE                 (MDR_PWM_BASE + 0x03000)
#define MDR_PWM4_BASE                 (MDR_PWM_BASE + 0x04000)
#define MDR_PWM5_BASE                 (MDR_PWM_BASE + 0x05000)
#define MDR_PWM6_BASE                 (MDR_PWM_BASE + 0x06000)
#define MDR_PWM7_BASE                 (MDR_PWM_BASE + 0x07000)
#define MDR_PWM8_BASE                 (MDR_PWM_BASE + 0x08000)

#define MDR_PWM0                      ((PWMControl  *) MDR_PWM0_BASE)
#define MDR_PWM1                      ((PWMControl  *) MDR_PWM1_BASE)
#define MDR_PWM2                      ((PWMControl  *) MDR_PWM2_BASE)
#define MDR_PWM3                      ((PWMControl  *) MDR_PWM3_BASE)
#define MDR_PWM4                      ((PWMControl  *) MDR_PWM4_BASE)
#define MDR_PWM5                      ((PWMControl  *) MDR_PWM5_BASE)
#define MDR_PWM6                      ((PWMControl  *) MDR_PWM6_BASE)
#define MDR_PWM7                      ((PWMControl  *) MDR_PWM7_BASE)
#define MDR_PWM8                      ((PWMControl  *) MDR_PWM8_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_PWM */


/** @defgroup __MDR1986VK01_Periph_ADC	MDR_ADC
  * @{
  */

/**
  * @brief MDR1986VK01 ADCx control
  */

typedef struct
{
  __IO  uint32_t ADC0CTRL;
  __IO  uint32_t ADC1CTRL;
  __IO  uint32_t ADC0SCOPECTRL;
  __IO  uint32_t ADC1SCOPECTRL;
  __IO  uint32_t ADCSYNCCTRL;
  __IO  uint32_t BUF_MODE_ADC;
  __IO  uint32_t BUF_STATE;
  __IO  uint32_t INT_CTRL_ADC;
  __IO  uint32_t DMARQ_CTRL_ADC;
    uint32_t Reserved0;
  __IO  uint32_t ANALOG_CTRL;
  __IO  uint32_t BNGP_CTRL;
  uint32_t Reserved1[4];
  __IO  uint32_t ADC0_CHNL_SEL[8];
  __IO  uint32_t ADC1_CHNL_SEL[8];
  __IO  uint32_t ADC0_RESULT[32];
  __IO  uint32_t ADC1_RESULT[32];
} ADCxControl;

#define MDR_ADC_BASE              (PERIPH_BASE + 0xA0000)

#define MDR_ADC0_BASE                 (MDR_ADC_BASE + 0x7000)
#define MDR_ADC1_BASE                 (MDR_ADC_BASE + 0x8000)
#define MDR_ADC2_BASE                 (MDR_ADC_BASE + 0x9000)

#define MDR_ADC0                      ((ADCxControl *) MDR_ADC0_BASE)
#define MDR_ADC1                      ((ADCxControl *) MDR_ADC1_BASE)
#define MDR_ADC2                      ((ADCxControl *) MDR_ADC2_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_ADC */


/** @defgroup __MDR1986VK01_Periph_DAC	DAC
  * @{
  */

/**
  * @brief MDR1986VK01 DACx control
  */

typedef struct
{
  __IO  uint32_t CTRL;
  __IO  uint32_t FIFO_CTRL;
  __IO  uint32_t PRD;
  __IO  uint32_t CNT;

  __IO  uint32_t IE;
  __IO  uint32_t RE;
  __IO  uint32_t STS;
  __IO  uint32_t DATA;
} DACxControl;

#define MDR_DAC_BASE              (PERIPH_BASE + 0xA0000)

#define MDR_DAC0_BASE             (MDR_DAC_BASE + 0xA000)
#define MDR_DAC1_BASE             (MDR_DAC_BASE + 0xB000)
#define MDR_DAC2_BASE             (MDR_DAC_BASE + 0xC000)
#define MDR_DAC3_BASE             (MDR_DAC_BASE + 0xD000)

#define MDR_DAC0                  ((DACxControl *) MDR_DAC0_BASE)
#define MDR_DAC1                  ((DACxControl *) MDR_DAC1_BASE)
#define MDR_DAC2                  ((DACxControl *) MDR_DAC2_BASE)
#define MDR_DAC3                  ((DACxControl *) MDR_DAC3_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_DAC */


/** @defgroup __MDR1986VK01_Periph_COMP	COMP
  * @{
  */

/**
  * @brief MDR1986VK01 COMP control
  */

typedef struct
{
  __IO  uint32_t COMP_CNTR;
  __IO  uint32_t COMP_EVNT;
  __IO  uint32_t ANABG_CTRL;
} CompControl;

#define MDR_COMP_BASE             (PERIPH_BASE + 0xA0000)

#define MDR_COMP0_BASE            (MDR_COMP_BASE + 0x0E000)
#define MDR_COMP1_BASE            (MDR_COMP_BASE + 0x0F000)
#define MDR_COMP2_BASE            (MDR_COMP_BASE + 0x10000)
#define MDR_COMP3_BASE            (MDR_COMP_BASE + 0x11000)

#define MDR_COMP0                 ((CompControl *) MDR_COMP0_BASE)
#define MDR_COMP1                 ((CompControl *) MDR_COMP1_BASE)
#define MDR_COMP2                 ((CompControl *) MDR_COMP2_BASE)
#define MDR_COMP3                 ((CompControl *) MDR_COMP3_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_COMP */


/** @defgroup __MDR1986VK01_Periph_I2C	I2C
  * @{
  */

/**
  * @brief MDR1986VK01 MDR_I2C control
  */

typedef struct
{
  __IO  uint32_t PRL;
  __IO  uint32_t PRH;
  __IO  uint32_t CTR;
  __IO  uint32_t RXD;
  __IO  uint32_t STA;
  __IO  uint32_t TXD;
  __IO  uint32_t CMD;
}MDR_I2C_TypeDef;

#define MDR_I2C_BASE              (PERIPH_BASE   + 0xB2000)

#define MDR_I2C                   ((MDR_I2C_TypeDef *) MDR_I2C_BASE)

/** @defgroup Periph_I2C_CTR	I2C_CTR
  * @{
  */

/**
  * @brief I2C Control Register
  */

/* Bit field positions: */
#define I2C_CTR_S_I2C_Pos                       5
#define I2C_CTR_EN_INT_Pos                      6
#define I2C_CTR_EN_I2C_Pos                      7

/* Bit field masks: */
#define I2C_CTR_S_I2C                           ((uint32_t)0x00000020)
#define I2C_CTR_EN_INT                          ((uint32_t)0x00000040)
#define I2C_CTR_EN_I2C                          ((uint32_t)0x00000080)

/** @} */ /* End of group Periph_I2C_CTR */

/** @defgroup Periph_I2C_STA	I2C STA
  * @{
  */

/**
  * @brief I2C Status Register
  */

/* Bit field positions: */
#define I2C_STA_INT_Pos                         0
#define I2C_STA_TR_PROG_Pos                     1
#define I2C_STA_LOST_ARB_Pos                    5
#define I2C_STA_BUSY_Pos                        6
#define I2C_STA_RX_ACK_Pos                      7

/* Bit field masks: */
#define I2C_STA_INT                             ((uint32_t)0x00000001)
#define I2C_STA_TR_PROG                         ((uint32_t)0x00000002)
#define I2C_STA_LOST_ARB                        ((uint32_t)0x00000020)
#define I2C_STA_BUSY                            ((uint32_t)0x00000040)
#define I2C_STA_RX_ACK                          ((uint32_t)0x00000080)

/** @} */ /* End of group Periph_I2C_STA */

/** @defgroup Periph_I2C_CMD	I2C CMD
  * @{
  */

/**
  * @brief I2C Command Register
  */

/* Bit field positions: */
#define I2C_CMD_CLRINT_Pos                      0
#define I2C_CMD_ACK_Pos                         3
#define I2C_CMD_WR_Pos                          4
#define I2C_CMD_RD_Pos                          5
#define I2C_CMD_STOP_Pos                        6
#define I2C_CMD_START_Pos                       7

/* Bit field masks: */
#define I2C_CMD_CLRINT                          ((uint32_t)0x00000001)
#define I2C_CMD_ACK                             ((uint32_t)0x00000008)
#define I2C_CMD_WR                              ((uint32_t)0x00000010)
#define I2C_CMD_RD                              ((uint32_t)0x00000020)
#define I2C_CMD_STOP                            ((uint32_t)0x00000040)
#define I2C_CMD_START                           ((uint32_t)0x00000080)

/** @} */ /* End of group Periph_I2C_CMD */

/** @} */ /* End of group __MDR1986VK01_Periph_I2C */


/** @defgroup __MDR1986VK01_Periph_CORDIC	CORDIC
  * @{
  */

/**
  * @brief MDR1986VK01 CORDICx control
  */

typedef struct
{
  __IO  uint32_t CTRL;
  __IO  uint32_t STATUS;
  __IO  uint32_t INTF;
  __IO  uint32_t INTE;
  __IO  uint32_t IN_X;
  __IO  uint32_t IN_Y;
  __IO  uint32_t IN_A;
  __IO  uint32_t IN_SEQ;
  __IO  uint32_t OUT_X;
  __IO  uint32_t OUT_Y;
  __IO  uint32_t OUT_A;
  __IO  uint32_t OUT_SEQ;
  __IO  uint32_t IN_ADDR;
  __IO  uint32_t OUT_ADDR;
} CRDControl;

#define MDR_CORDIC_BASE           (PERIPH_BASE + 0xB0000)

#define MDR_CORDIC0_BASE          (MDR_CORDIC_BASE + 0x3000)

#define MDR_CORDIC                ((CRDControl  *) MDR_CORDIC0_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_CORDIC */


/** @defgroup __MDR1986VK01_Periph_CRC	CRC
  * @{
  */

typedef struct
{
  __IO  uint32_t DR;          ///< CRC Data register,             Address offset: 0x00
  __IO  uint8_t  IDR;         ///< CRC Independent data register, Address offset: 0x04
        uint8_t  RESERVED0;   ///< Reserved,                                      0x05
        uint16_t RESERVED1;   ///< Reserved,                                      0x06
  __IO  uint32_t CR;          ///< CRC Control register,          Address offset: 0x08
        uint32_t RESERVED2;   ///< Reserved,                                      0x0C
  __IO  uint32_t INIT;        ///< Initial CRC value register,    Address offset: 0x10
  __IO  uint32_t POL;         ///< CRC polynomial register,       Address offset: 0x14
} CRC_TypeDef;


#define MDR_CRC_BASE                (PERIPH_BASE + 0xB6000)

#define MDR_CRC                     ((CRC_TypeDef *) MDR_CRC_BASE)

/** @} */ /* End of group __MDR1986VK01_Periph_CRC */


/** @defgroup __MDR1986VK01_Periph_GATE	Gate
  * @{
  */

typedef struct
{
    __IO uint32_t OP_FIFO_OP_TO_SF;
    __IO uint32_t OP_FIFO_SF_TO_OP;
    __IO uint32_t OP_FIFO_LEVELS;
    __IO uint32_t OP_FIFO_INT_MASK;
    __IO uint32_t OP_FIFO_INT_SOURCE;
    __IO uint32_t OP_REG[16];
    __IO uint32_t OP_REGS_BUSY;
    __IO uint32_t OP_REGS_INT_MASK;
    __IO uint32_t OP_REGS_INT_SOURCE;
} GateRegs;

#define GATE_BASE               ((uint32_t)0x21030000)
#define GATE_REGS               ((GateRegs *)GATE_BASE)


#define GATE0_REGS_BASE         GATE_BASE // backward compability alias
#define GATE1_REGS_BASE         ((uint32_t)0x21030080)

#define GATE0_REGS              ((GateRegs *)GATE0_REGS_BASE)
#define GATE1_REGS              ((GateRegs *)GATE1_REGS_BASE)


/** @} */ /* End of group __MDR1986VK01_Periph_GATE */

/************************* Alias definitions **********************************/

#if defined (MDR_LEGACY_SUPPORT)
    #warning "Legacy 1.1.1+: REG_60-63_TMRx in MDR_BKP replaced with REG_60_SYSx, REG_61-62_PWRx, REG_63_CLKx according to spec. These alias definitions will be removed in 2.0 version"
    #define REG_60_TMR0 REG_60_SYS0
    #define REG_60_TMR1 REG_60_SYS1
    #define REG_60_TMR2 REG_60_SYS2
    #define REG_61_TMR0 REG_61_PWR0
    #define REG_61_TMR1 REG_61_PWR1
    #define REG_61_TMR2 REG_61_PWR2
    #define REG_62_TMR0 REG_62_PWR0
    #define REG_62_TMR1 REG_62_PWR1
    #define REG_62_TMR2 REG_62_PWR2
    #define REG_63_TMR0 REG_63_CLK0
    #define REG_63_TMR1 REG_63_CLK1
    #define REG_63_TMR2 REG_63_CLK2
#endif

#if defined (MDR_LEGACY_SUPPORT)
    #warning "Legacy 1.3.0+: Changed "TBSY" to "TNBSY" in UART_IT_TBSY (MDR_UART), SSPx/UARTx_TBSYINTR_IRQn (MDR1986VK01) and SSPx/UARTx_TBSYINTR_IRQHandler (startup) according to spec. These alias definitions will be removed in 2.0 version"
    #define UART_IT_TBSY UART_IT_TNBSY
    #define SSP0_TBSYINTR_IRQn SSP0_TNBSYINTR_IRQn
    #define SSP1_TBSYINTR_IRQn SSP1_TNBSYINTR_IRQn
    #define UART0_TBSYINTR_IRQn UART0_TNBSYINTR_IRQn
    #define UART1_TBSYINTR_IRQn UART1_TNBSYINTR_IRQn
    #define UART2_TBSYINTR_IRQn UART2_TNBSYINTR_IRQn
    #define UART3_TBSYINTR_IRQn UART3_TNBSYINTR_IRQn
    #define SSP0_TBSYINTR_IRQHandler SSP0_TNBSYINTR_IRQHandler
    #define SSP1_TBSYINTR_IRQHandler SSP1_TNBSYINTR_IRQHandler
    #define UART0_TBSYINTR_IRQHandler UART0_TNBSYINTR_IRQHandler
    #define UART1_TBSYINTR_IRQHandler UART1_TNBSYINTR_IRQHandler
    #define UART2_TBSYINTR_IRQHandler UART2_TNBSYINTR_IRQHandler
    #define UART3_TBSYINTR_IRQHandler UART3_TNBSYINTR_IRQHandler
#endif

#endif /* __MDR1986VK01_H__ */

/*********************** (C) COPYRIGHT 2022 Milandr ****************************
*
* END OF FILE MDR1986VK01.h */


