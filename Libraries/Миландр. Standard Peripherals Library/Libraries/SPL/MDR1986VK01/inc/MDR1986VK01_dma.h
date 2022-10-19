/**
  ******************************************************************************
  * @file    MDR1986VK01_dma.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   This file contains all the functions prototypes for the DMA
  *          firmware library.
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
  ******************************************************************************
  * FILE MDR1986VK01_dma.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR1986VK01_DMA_H
#define __MDR1986VK01_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_config.h"	

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @addtogroup DMA DMA
  * @{
  */

/** @defgroup DMA_Exported_Types DMA Exported Types
  * @{
  */

/**
  * @brief  DMA Channel Primary / Alternate Control Data initialization structure definition
  */

typedef struct
{
  uint32_t DMA_SourceBaseAddr;                                                          /*!< Specifies the source base address for DMA Channelx. */
                                                                                        
  uint32_t DMA_DestBaseAddr;                                                            /*!< Specifies the destination base address for DMA Channelx. */
                                                                                        
  uint32_t DMA_SourceIncSize;                                                           /*!< Specifies the source address register increment value.
                                                                                          This parameter can be a value of @ref DMA_source_incremented_mode */
                                                                                        
  uint32_t DMA_DestIncSize;                                                             /*!< Specifies the destination address register increment value.
                                                                                          This parameter can be a value of @ref DMA_dest_incremented_mode */
                                                                                        
  uint32_t DMA_MemoryDataSize;                                                          /*!< Specifies the Memory data width.
                                                                                          This parameter can be a value of @ref DMA_memory_data_size */
                                                                                        
  uint32_t DMA_Mode;                                                                    /*!< Specifies the operation mode of the DMA Channelx.
                                                                                          This parameter can be a value of @ref DMA_operating_mode. */
                                                                                        
  uint32_t DMA_CycleSize;                                                               /*!< Specifies the  total number of DMA transfers that the DMA cycle contains.
                                                                                          This parameter can be a value of @ref DMA_cycle_size. */
                                                                                        
  uint32_t DMA_NumContinuous;                                                           /*!< Specifies how many DMA transfers can occur before the DMA controller rearbitrates.
                                                                                          This parameter can be a value of @ref DMA_number_continuous_transfers. */
                                                                                        
  uint32_t DMA_SourceProtCtrl;                                                          /*!< Specifies the DMA Source protection control.
                                                                                          This parameter can be a value of @ref DMA_source_protection_control. */
                                                                                        
  uint32_t DMA_DestProtCtrl;                                                            /*!< Specifies the DMA Destination protection control.
                                                                                          This parameter can be a value of @ref DMA_dest_protection_control. */
} DMA_CtrlDataInitTypeDef;

/**
  * @brief  DMA Channel Control Data structure definition
  */

typedef struct
{
  uint32_t DMA_SourceEndAddr;                                                           /*!< Specifies the DMA channel source end address */
                                            
  uint32_t DMA_DestEndAddr;                                                             /*!< Specifies the DMA channel destination end address. */
                                            
  uint32_t DMA_Control;                                                                 /*!< Specifies the DMA channel control data configuration. */
                                            
  uint32_t DMA_Unused;                                                                  /*!< Specifies the DMA channel unused memory. */
                                            
}DMA_CtrlDataTypeDef;

/**
  * @brief  DMA Channel Init structure definition
  */

typedef struct
{
  DMA_CtrlDataInitTypeDef *DMA_PriCtrlData;                                             /*!< Specifies the pointer to the primary control data structure.
                                                                                            This parameter should be NULL if primary data structure is not used */
                                            
  DMA_CtrlDataInitTypeDef *DMA_AltCtrlData;                                             /*!< Specifies the pointer to the alternate control data structure.
                                                                                            This parameter should be NULL if alternate data structure is not used */
                                            
  uint32_t DMA_ProtCtrl;                                                                /*!< Specifies the AHB-Lite protection control.
                                                                                            This parameter can be a value of @ref DMA_AHB_protection_control. */
                                            
  uint8_t DMA_Priority;                                                                 /*!< Specifies the software priority for the DMA Channelx.
                                                                                            This parameter can be a value of @ref DMA_priority_level */
                                            
  uint8_t DMA_UseBurst;                                                                 /*!< Disables single request to generate DMA requests for the DMA Channelx.
                                                                                            This parameter can be a value of @ref DMA_burst_mode */
                                            
  uint8_t DMA_SelectDataStructure;                                                      /*!< Specifies the primary /alternate data structure to use by the DMA channel.
                                                                                            This parameter can be a value of @ref DMA_data_structure_selection. */

} DMA_ChannelInitTypeDef;

/**
  * @brief  DMA Channel Scatter-Gather Init structure definition
  */

typedef struct
{
  DMA_CtrlDataTypeDef *DMA_SG_TaskArray;                                                /*!< Specifies the pointer to the Scatter-Gather task structures array. The size
                                                                                            of the array should be equal to DMA_SG_TaskNumber.
                                                                                            Every structure of the array should contain the copy of the alternate control
                                                                                            data for the related task. It will be used by DMA to configure
                                                                                            the alternate control data while operating in the
                                                                                            scatter-gather mode */
                                            
  uint32_t DMA_SG_TaskNumber;                                                           /*!< Specifies the number of scatter-gather tasks to be executed by DMA */
                                            
                                            
  uint32_t DMA_SourceProtCtrl;                                                          /*!< Specifies the Primary Control Data DMA Source protection control.
                                                                                            This parameter can be a value of @ref DMA_source_protection_control. */
                                            
  uint32_t DMA_DestProtCtrl;                                                            /*!< Specifies the Primary Control Data DMA Destination protection control.
                                                                                            This parameter can be a value of @ref DMA_dest_protection_control. */
                                            
  uint32_t DMA_ProtCtrl;                                                                /*!< Specifies the AHB-Lite protection control.
                                                                                            This parameter can be a value of @ref DMA_AHB_protection_control. */
                                            
  uint8_t DMA_Priority;                                                                 /*!< Specifies the software priority for the DMA Channelx.
                                                                                            This parameter can be a value of @ref DMA_priority_level */
                                            
  uint8_t DMA_UseBurst;                                                                 /*!< Disables single request to generate DMA requests for the DMA Channelx.
                                                                                            This parameter can be a value of @ref DMA_burst_mode */

} DMA_Channel_SG_InitTypeDef;


/** @} */ /* End of group DMA_Exported_Types */

/** @defgroup DMA_Exported_Constants DMA Exported Constants
  * @{
  */

/** @defgroup DMA_channels_number DMA channels number
  * @{
  */

#define IS_DMA_CHANNELS(NUMBER) ((NUMBER >= 1) && (NUMBER <= 32))

/** @} */ /* End of group DMA_channels_number */

/** @defgroup DMA_alternate_data_usage DMA alternate data usage
  * @{
  */

#define DMA_ALternateDataDisabled           ((uint16_t)(0x00))
#define DMA_ALternateDataEnabled            ((uint16_t)(0x01))

#define IS_DMA_ALTERNATE_DATA(STATE)        (((STATE) == DMA_ALternateDataDisabled) || \
                                            ((STATE)  == DMA_ALternateDataEnabled))

/** @} */ /* End of group DMA_alternate_data_usage */

/** @defgroup DMA_valid_channels DMA valid channels
  * @{
  */
/*-- req DMA request ---------------------------------------------------------*/
#define DMA_Channel_REQ_ETH0                ((uint8_t)(7))
#define DMA_Channel_REQ_ETH1                ((uint8_t)(8))
#define DMA_Channel_REQ_TIM0_0              ((uint8_t)(9))
#define DMA_Channel_REQ_TIM1_0              ((uint8_t)(10))
#define DMA_Channel_REQ_TIM2_0              ((uint8_t)(11))
#define DMA_Channel_REQ_TIM3_0              ((uint8_t)(12))
#define DMA_Channel_REQ_TIM0_1              ((uint8_t)(13))
#define DMA_Channel_REQ_TIM1_1              ((uint8_t)(14))
#define DMA_Channel_REQ_TIM2_1              ((uint8_t)(15))
#define DMA_Channel_REQ_TIM3_1              ((uint8_t)(16))
#define DMA_Channel_REQ_TIM0_2              ((uint8_t)(17))
#define DMA_Channel_REQ_TIM1_2              ((uint8_t)(18))
#define DMA_Channel_REQ_TIM2_2              ((uint8_t)(19))
#define DMA_Channel_REQ_TIM3_2              ((uint8_t)(20))
#define DMA_Channel_REQ_TIM0_3              ((uint8_t)(21))
#define DMA_Channel_REQ_TIM1_3              ((uint8_t)(22))
#define DMA_Channel_REQ_TIM2_3              ((uint8_t)(23))
#define DMA_Channel_REQ_TIM3_3              ((uint8_t)(24))
#define DMA_Channel_REQ_TIM0_4              ((uint8_t)(25))
#define DMA_Channel_REQ_TIM1_4              ((uint8_t)(26))
#define DMA_Channel_REQ_CRDC_DRQ0           ((uint8_t)(27))
#define DMA_Channel_REQ_CRDC_DRQ1           ((uint8_t)(28))
#define DMA_Channel_REQ_SSP0_TX             ((uint8_t)(29))
#define DMA_Channel_REQ_SSP1_TX             ((uint8_t)(30))
#define DMA_Channel_REQ_SSP0_RX             ((uint8_t)(31))
#define DMA_Channel_REQ_SSP1_RX             ((uint8_t)(32))
#define DMA_Channel_REQ_UART0_TX            ((uint8_t)(33))
#define DMA_Channel_REQ_UART1_TX            ((uint8_t)(34))
#define DMA_Channel_REQ_UART2_TX            ((uint8_t)(35))
#define DMA_Channel_REQ_UART3_TX            ((uint8_t)(36))
#define DMA_Channel_REQ_UART0_RX            ((uint8_t)(37))
#define DMA_Channel_REQ_UART1_RX            ((uint8_t)(38))
#define DMA_Channel_REQ_UART2_RX            ((uint8_t)(39))
#define DMA_Channel_REQ_UART3_RX            ((uint8_t)(40))
#define DMA_Channel_REQ_DAC0                ((uint8_t)(41))
#define DMA_Channel_REQ_DAC1                ((uint8_t)(42))
#define DMA_Channel_REQ_DAC2                ((uint8_t)(43))
#define DMA_Channel_REQ_DAC3                ((uint8_t)(44))
#define DMA_Channel_REQ_SHDWP_PWM9          ((uint8_t)(45))
#define DMA_Channel_REQ_SHDWP_PWM8          ((uint8_t)(46))
#define DMA_Channel_REQ_SHDWP_PWM7          ((uint8_t)(47))
#define DMA_Channel_REQ_SHDWP_PWM6          ((uint8_t)(48))
#define DMA_Channel_REQ_SHDWP_PWM5          ((uint8_t)(49))
#define DMA_Channel_REQ_SHDWP_PWM4          ((uint8_t)(50))
#define DMA_Channel_REQ_SHDWP_PWM3          ((uint8_t)(51))
#define DMA_Channel_REQ_SHDWP_PWM2          ((uint8_t)(52))
#define DMA_Channel_REQ_SHDWP_PWM1          ((uint8_t)(53))
#define DMA_Channel_REQ_SHDWB_PWM9          ((uint8_t)(54))
#define DMA_Channel_REQ_SHDWB_PWM8          ((uint8_t)(55))
#define DMA_Channel_REQ_SHDWB_PWM7          ((uint8_t)(56))
#define DMA_Channel_REQ_SHDWB_PWM6          ((uint8_t)(57))
#define DMA_Channel_REQ_SHDWB_PWM5          ((uint8_t)(58))
#define DMA_Channel_REQ_SHDWB_PWM4          ((uint8_t)(59))
#define DMA_Channel_REQ_SHDWB_PWM3          ((uint8_t)(60))
#define DMA_Channel_REQ_SHDWB_PWM2          ((uint8_t)(61))
#define DMA_Channel_REQ_SHDWB_PWM1          ((uint8_t)(62))
#define DMA_Channel_REQ_SHDWA_PWM9          ((uint8_t)(63))
#define DMA_Channel_REQ_SHDWA_PWM8          ((uint8_t)(64))
#define DMA_Channel_REQ_SHDWA_PWM7          ((uint8_t)(65))
#define DMA_Channel_REQ_SHDWA_PWM6          ((uint8_t)(66))
#define DMA_Channel_REQ_SHDWA_PWM5          ((uint8_t)(67))
#define DMA_Channel_REQ_SHDWA_PWM4          ((uint8_t)(68))
#define DMA_Channel_REQ_SHDWA_PWM3          ((uint8_t)(69))
#define DMA_Channel_REQ_SHDWA_PWM2          ((uint8_t)(70))
#define DMA_Channel_REQ_SHDWA_PWM1          ((uint8_t)(71))
#define DMA_Channel_REQ_END_CONV_ADC12      ((uint8_t)(72))
#define DMA_Channel_REQ_END_CONV_ADC11      ((uint8_t)(73))
#define DMA_Channel_REQ_END_CONV_ADC10      ((uint8_t)(74))
#define DMA_Channel_REQ_FIFO_LIM_ADC12      ((uint8_t)(75))
#define DMA_Channel_REQ_FIFO_LIM_ADC11      ((uint8_t)(76))
#define DMA_Channel_REQ_FIFO_LIM_ADC10      ((uint8_t)(77))
#define DMA_Channel_REQ_FIFO_NEMPTY_ADC12   ((uint8_t)(78))
#define DMA_Channel_REQ_FIFO_NEMPTY_ADC11   ((uint8_t)(79))
#define DMA_Channel_REQ_FIFO_NEMPTY_ADC10   ((uint8_t)(80))
#define DMA_Channel_REQ_FIFO_FULL_ADC12     ((uint8_t)(81))
#define DMA_Channel_REQ_FIFO_FULL_ADC11     ((uint8_t)(82))
#define DMA_Channel_REQ_FIFO_FULL_ADC10     ((uint8_t)(83))
#define DMA_Channel_REQ_END_CONV_ADC02      ((uint8_t)(84))
#define DMA_Channel_REQ_END_CONV_ADC01      ((uint8_t)(85))
#define DMA_Channel_REQ_END_CONV_ADC00      ((uint8_t)(86))
#define DMA_Channel_REQ_FIFO_LIM_ADC02      ((uint8_t)(87))
#define DMA_Channel_REQ_FIFO_LIM_ADC01      ((uint8_t)(88))
#define DMA_Channel_REQ_FIFO_LIM_ADC00      ((uint8_t)(89))
#define DMA_Channel_REQ_FIFO_NEMPTY_ADC02   ((uint8_t)(90))
#define DMA_Channel_REQ_FIFO_NEMPTY_ADC01   ((uint8_t)(91))
#define DMA_Channel_REQ_FIFO_NEMPTY_ADC00   ((uint8_t)(92))
#define DMA_Channel_REQ_FIFO_FULL_ADC02     ((uint8_t)(93))
#define DMA_Channel_REQ_FIFO_FULL_ADC01     ((uint8_t)(94))
#define DMA_Channel_REQ_FIFO_FULL_ADC00     ((uint8_t)(95))

/*-- sreq DMA request --------------------------------------------------------*/


#define IS_DMA_CHANNEL(CHANNEL) (CHANNEL <= (DMA_Channels_Number - 1))

/** @} */ /* End of group DMA_valid_channels */

/** @defgroup DMA_source_incremented_mode DMA source incremented mode
  * @{
  */

#define DMA_SourceIncByte                   ((uint32_t)(0 << 26))
#define DMA_SourceIncHalfword               ((uint32_t)(1 << 26))
#define DMA_SourceIncWord                   ((uint32_t)(2 << 26))
#define DMA_SourceIncNo                     ((uint32_t)(3 << 26))
#define IS_DMA_SOURCE_INC_STATE(STATE)      (((STATE) == DMA_SourceIncByte)     || \
                                            ((STATE)  == DMA_SourceIncHalfword) || \
                                            ((STATE)  == DMA_SourceIncWord)     || \
                                            ((STATE)  == DMA_SourceIncNo))

/** @} */ /* End of group DMA_source_incremented_mode */

/** @defgroup DMA_dest_incremented_mode DMA dest incremented mode
  * @{
  */

#define DMA_DestIncByte                     ((uint32_t)(0x0UL << 30))
#define DMA_DestIncHalfword                 ((uint32_t)(0x1UL << 30))
#define DMA_DestIncWord                     ((uint32_t)(0x2UL << 30))
#define DMA_DestIncNo                       ((uint32_t)(0x3UL << 30))
#define IS_DMA_DEST_INC_STATE(STATE)        (((STATE) == DMA_DestIncByte)       || \
                                            ((STATE)  == DMA_DestIncHalfword)   || \
                                            ((STATE)  == DMA_DestIncWord)       || \
                                            ((STATE)  == DMA_DestIncNo))

/** @} */ /* End of group DMA_dest_incremented_mode */

/** @defgroup DMA_memory_data_size DMA memory data size
  * @{
  */

#define DMA_MemoryDataSize_Byte             ((uint32_t)(0x00 << 24))
#define DMA_MemoryDataSize_HalfWord         ((uint32_t)(0x11 << 24))
#define DMA_MemoryDataSize_Word             ((uint32_t)(0x22 << 24))
#define IS_DMA_MEMORY_DATA_SIZE(SIZE)       (((SIZE) == DMA_MemoryDataSize_Byte)      || \
                                            ((SIZE) == DMA_MemoryDataSize_HalfWord)  || \
                                            ((SIZE) == DMA_MemoryDataSize_Word))

/** @} */ /* End of group DMA_memory_data_size */

/** @defgroup DMA_operating_mode DMA operating mode
  * @{
  */

#define DMA_Mode_Stop                       ((uint32_t)0x0)
#define DMA_Mode_Basic                      ((uint32_t)0x1)
#define DMA_Mode_AutoRequest                ((uint32_t)0x2)
#define DMA_Mode_PingPong                   ((uint32_t)0x3)
#define DMA_Mode_MemScatterPri              ((uint32_t)0x4)
#define DMA_Mode_MemScatterAlt              ((uint32_t)0x5)
#define DMA_Mode_PerScatterPri              ((uint32_t)0x6)
#define DMA_Mode_PerScatterAlt              ((uint32_t)0x7)
#define DMA_Mode_PerScatterAltBurst         ((uint32_t)0xF)

#define IS_DMA_MODE(MODE)                   (((MODE) == DMA_Mode_Stop)           || \
                                            ((MODE) == DMA_Mode_Basic)          || \
                                            ((MODE) == DMA_Mode_AutoRequest)    || \
                                            ((MODE) == DMA_Mode_PingPong)       || \
                                            ((MODE) == DMA_Mode_MemScatterPri)  || \
                                            ((MODE) == DMA_Mode_MemScatterAlt)  || \
                                            ((MODE) == DMA_Mode_PerScatterPri)  || \
                                            ((MODE) == DMA_Mode_PerScatterAlt)  || \
                                            ((MODE) == DMA_Mode_PerScatterAltBurst))

/** @} */ /* End of group DMA_operating_mode */

/** @defgroup DMA_cycle_size DMA cycle size
  * @{
  */

#define IS_DMA_CYCLE_SIZE(SIZE)             ((SIZE >= 1) && (SIZE <= 1024))

/** @} */ /* End of group DMA_cycle_size */

/** @defgroup DMA_priority_level DMA priority level
  * @{
  */

#define DMA_Priority_Default                ((uint8_t)0x00)
#define DMA_Priority_High                   ((uint8_t)0x01)
#define IS_DMA_PRIORITY(PRIORITY)           (((PRIORITY) == DMA_Priority_Default) || \
                                            ((PRIORITY)  == DMA_Priority_High))

/** @} */ /* End of group DMA_priority_level */

/** @defgroup DMA_burst_mode DMA burst mode
  * @{
  */

#define DMA_BurstClear                      ((uint8_t)0x00)
#define DMA_BurstSet                        ((uint8_t)0x01)
#define IS_DMA_BURST(STATE)                 (((STATE) == DMA_BurstClear) || \
                                            ((STATE)  == DMA_BurstSet))

/** @} */ /* End of group DMA_burst_mode */


/** @defgroup DMA_source_protection_control DMA source protection control
  * @{
  */

#define DMA_SourceCacheable                 ((uint32_t)(0x01 << 20))
#define DMA_SourceBufferable                ((uint32_t)(0x01 << 19))
#define DMA_SourcePrivileged                ((uint32_t)(0x01 << 18))

#define IS_DMA_SOURCE_PROT(STATE)           ((STATE & (~(0x7 << 18))) == 0)

/** @} */ /* End of group DMA_source_protection_control */

/** @defgroup DMA_dest_protection_control DMA dest protection control
  * @{
  */

#define DMA_DestCacheable                   ((uint32_t)(0x01 << 23))
#define DMA_DestBufferable                  ((uint32_t)(0x01 << 22))
#define DMA_DestPrivileged                  ((uint32_t)(0x01 << 21))

#define IS_DMA_DEST_PROT(STATE)             ((STATE & (~(0x7 << 21))) == 0)

/** @} */ /* End of group DMA_dest_protection_control */

/** @defgroup DMA_AHB_protection_control DMA AHB-Lite protection control
  * @{
  */

#define DMA_AHB_Cacheable                   ((uint32_t)(0x01 << 7))
#define DMA_AHB_Bufferable                  ((uint32_t)(0x01 << 6))
#define DMA_AHB_Privileged                  ((uint32_t)(0x01 << 5))
    
#define IS_DMA_AHB_PROT(STATE)              ((STATE & (~(0x7 << 5))) == 0)

/** @} */ /* End of group DMA_source_protection_control */

/** @defgroup DMA_number_continuous_transfers DMA number continuous transfers
  * @{
  */

#define DMA_Transfers_1                     ((uint32_t)(0x00 << 14))
#define DMA_Transfers_2                     ((uint32_t)(0x01 << 14))
#define DMA_Transfers_4                     ((uint32_t)(0x02 << 14))
#define DMA_Transfers_8                     ((uint32_t)(0x03 << 14))
#define DMA_Transfers_16                    ((uint32_t)(0x04 << 14))
#define DMA_Transfers_32                    ((uint32_t)(0x05 << 14))
#define DMA_Transfers_64                    ((uint32_t)(0x06 << 14))
#define DMA_Transfers_128                   ((uint32_t)(0x07 << 14))
#define DMA_Transfers_256                   ((uint32_t)(0x08 << 14))
#define DMA_Transfers_512                   ((uint32_t)(0x09 << 14))
#define DMA_Transfers_1024                  ((uint32_t)(0x0A << 14))

#define IS_DMA_CONTINUOUS_NUMBER(NUMBER)    (((NUMBER)  == DMA_Transfers_1)      || \
                                            ((NUMBER)  == DMA_Transfers_2)      || \
                                            ((NUMBER)  == DMA_Transfers_4)      || \
                                            ((NUMBER)  == DMA_Transfers_8)      || \
                                            ((NUMBER)  == DMA_Transfers_16)     || \
                                            ((NUMBER)  == DMA_Transfers_32)     || \
                                            ((NUMBER)  == DMA_Transfers_64)     || \
                                            ((NUMBER)  == DMA_Transfers_128)    || \
                                            ((NUMBER)  == DMA_Transfers_256)    || \
                                            ((NUMBER)  == DMA_Transfers_512)    || \
                                            ((NUMBER)  == DMA_Transfers_1024))

/** @} */ /* End of group DMA_number_continuous_transfers */

/** @defgroup DMA_data_structure_selection DMA data structure selection
  * @{
  */

#define DMA_CTRL_DATA_PRIMARY               ((uint8_t)0x00)

#if (DMA_AlternateData == 1)

  #define DMA_CTRL_DATA_ALTERNATE           ((uint8_t)0x01)

  #define IS_DMA_SELECT_DATA_STRUCTURE(TYPE) (((TYPE)  == DMA_CTRL_DATA_PRIMARY)      || \
                                              ((TYPE)  == DMA_CTRL_DATA_ALTERNATE))
#else
  #define IS_DMA_SELECT_DATA_STRUCTURE(TYPE) (((TYPE)  == DMA_CTRL_DATA_PRIMARY))
#endif

/** @} */ /* End of group DMA_data_structure_selection */

/** @defgroup DMA_flags_definition DMA flags definition
  * @{
  */

#define DMA_FLAG_DMA_ENA                    ((uint8_t)0x01)
#define DMA_FLAG_DMA_ERR                    ((uint8_t)0x02)
#define DMA_FLAG_CHNL_ENA                   ((uint8_t)0x03)
#define DMA_FLAG_CHNL_MASK                  ((uint8_t)0x04)
#define DMA_FLAG_CHNL_WAIT                  ((uint8_t)0x05)
#define DMA_FLAG_CHNL_BURST                 ((uint8_t)0x06)
#define DMA_FLAG_CHNL_ALT                   ((uint8_t)0x07)
#define DMA_FLAG_CHNL_PRIORITY              ((uint8_t)0x08)

#define IS_DMA_FLAG(FLAG)                   (((FLAG)  == DMA_FLAG_DMA_ENA)      || \
                                            ((FLAG)  == DMA_FLAG_DMA_ERR)      || \
                                            ((FLAG)  == DMA_FLAG_CHNL_ENA)     || \
                                            ((FLAG)  == DMA_FLAG_CHNL_MASK)    || \
                                            ((FLAG)  == DMA_FLAG_CHNL_WAIT)    || \
                                            ((FLAG)  == DMA_FLAG_CHNL_BURST)   || \
                                            ((FLAG)  == DMA_FLAG_CHNL_ALT)     || \
                                            ((FLAG)  == DMA_FLAG_CHNL_PRIORITY))

#define DMA_CFG_MASTER_ENABLE               ((uint8_t)0x01)
#define DMA_STATUS_MASTER_ENABLE            ((uint8_t)0x01)

/** @} */ /* End of group DMA_flags_definition */

/** @} */ /* End of group DMA_Exported_Constants */

/** @defgroup DMA_Exported_Macros DMA Exported Macros
  * @{
  */

/** @} */ /* End of group DMA_Exported_Macros */

/** @defgroup DMA_Exported_Functions DMA Exported Functions
  * @{
  */

void DMA_CtrlDataInit(DMA_CtrlDataInitTypeDef *DMA_ctrl_data_ptr, DMA_CtrlDataTypeDef *DMA_ctrl_table_ptr);

void DMA_DeInit(void);
void DMA_CtrlInit(uint8_t DMA_Channel, uint8_t DMA_CtrlDataType,  DMA_CtrlDataInitTypeDef* DMA_CtrlStruct);
void DMA_SG_CtrlInit(uint32_t DMA_Task, DMA_CtrlDataTypeDef *DMA_SG_TaskArray,  DMA_CtrlDataInitTypeDef* DMA_CtrlStruct);
void DMA_SG_Init( uint8_t DMA_Channel, DMA_Channel_SG_InitTypeDef *DMA_SG_InitStruct);
void DMA_Init(uint8_t DMA_Channel, DMA_ChannelInitTypeDef* DMA_InitStruct);
void DMA_SetChannelRequest(uint8_t DMA_Channel, uint8_t DMA_Req);

void DMA_StructInit(DMA_ChannelInitTypeDef* DMA_InitStruct);
void DMA_SG_StructInit(DMA_Channel_SG_InitTypeDef* DMA_InitStruct);

void DMA_Cmd(uint8_t DMA_Channel, FunctionalState NewState);
void DMA_Request(uint8_t DMA_Channel);
void DMA_ClearError(void);

uint32_t DMA_GetCurrTransferCounter(uint8_t DMA_Channel, uint8_t DMA_CtrlData);
FlagStatus DMA_GetFlagStatus(uint8_t DMA_Channel, uint8_t DMA_Flag);


/** @} */ /* End of group DMA_Exported_Functions */

/** @} */ /* End of group DMA */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR1986VK01_DMA_H */

/******************* (C) COPYRIGHT 2022 Milandr *********
*
* END OF FILE MDR1986VK01_dma.h */


