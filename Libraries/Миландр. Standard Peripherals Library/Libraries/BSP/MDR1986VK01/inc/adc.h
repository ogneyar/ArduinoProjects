/**
  ******************************************************************************
  * @file    adc.h
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    11/11/2020
  * @brief   ADC header file for demo board.
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
  * FILE adc.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H
#define __ADC_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"
#include <stdint.h>

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_ADC BSP_ADC
  * @{
  */

/** @defgroup BSP_ADC_Exported_Types BSP ADC Exported Types
  * @{
  */

/* ADC_CTRL */
enum
{
    ADC_CNV_NUM_1 = 0,
    ADC_CNV_NUM_2,
    ADC_CNV_NUM_3,
    ADC_CNV_NUM_4,
    ADC_CNV_NUM_5,
    ADC_CNV_NUM_6,
    ADC_CNV_NUM_7,
    ADC_CNV_NUM_8,
    ADC_CNV_NUM_9,
    ADC_CNV_NUM_10,
    ADC_CNV_NUM_11,
    ADC_CNV_NUM_12,
    ADC_CNV_NUM_13,
    ADC_CNV_NUM_14,
    ADC_CNV_NUM_15,
    ADC_CNV_NUM_16,
    ADC_CNV_NUM_17,
    ADC_CNV_NUM_18,
    ADC_CNV_NUM_19,
    ADC_CNV_NUM_20,
    ADC_CNV_NUM_21,
    ADC_CNV_NUM_22,
    ADC_CNV_NUM_23,
    ADC_CNV_NUM_24,
    ADC_CNV_NUM_25,
    ADC_CNV_NUM_26,
    ADC_CNV_NUM_27,
    ADC_CNV_NUM_28,
    ADC_CNV_NUM_29,
    ADC_CNV_NUM_30,
    ADC_CNV_NUM_31,
    ADC_CNV_NUM_32,
    ADC_CNV_NUM_MAX
};

enum
{
    ADC_CH0 = 0,
    ADC_CH1,
    ADC_CH2,
    ADC_CH3,
    ADC_CH4,
    ADC_CH5,
    ADC_CH6,
    ADC_CH7,
    ADC_CH8
};

/* 
    Conversion start signal source for ADC_CTRL_CONV_TRIG(x)
    ADC20 - 2 - ADC block number (0, 1, 2), 0 - ADC number in the block (0, 1)
 */
#define ADC00_ADC_ESOC_00               0x01
#define ADC00_EPWMxSOCA_7               0x02
#define ADC00_EPWMxSOCB_0               0x04
#define ADC00_EPWMxSOCA_0               0x08
#define ADC00_EPWMxSOCB_1               0x10
#define ADC00_EPWMxSOCA_1               0x20
#define ADC00_EPWMxSOCB_2               0x40
#define ADC00_EPWMxSOCA_2               0x80

#define ADC01_ADC_ESOC_01               0x01
#define ADC01_EPWMxSOCA_7               0x02
#define ADC01_EPWMxSOCB_3               0x04
#define ADC01_EPWMxSOCA_3               0x08
#define ADC01_EPWMxSOCB_4               0x10
#define ADC01_EPWMxSOCA_4               0x20
#define ADC01_EPWMxSOCB_5               0x40
#define ADC01_EPWMxSOCA_5               0x80

#define ADC10_ADC_ESOC_10               0x01
#define ADC10_EPWMxSOCA_8               0x02
#define ADC10_EPWMxSOCA_0               0x04
#define ADC10_EPWMxSOCA_1               0x08
#define ADC10_EPWMxSOCA_2               0x10
#define ADC10_EPWMxSOCA_3               0x20
#define ADC10_EPWMxSOCA_4               0x40
#define ADC10_EPWMxSOCA_5               0x80

#define ADC11_ADC_ESOC_11               0x01
#define ADC11_EPWMxSOCB_8               0x02
#define ADC11_EPWMxSOCB_0               0x04
#define ADC11_EPWMxSOCB_1               0x08
#define ADC11_EPWMxSOCB_2               0x10
#define ADC11_EPWMxSOCB_3               0x20
#define ADC11_EPWMxSOCB_4               0x40
#define ADC11_EPWMxSOCB_5               0x80
                                            
#define ADC20_ADC_ESOC_20               0x01
#define ADC20_EPWMxSOCA_1               0x02
#define ADC20_EPWMxSOCB_6               0x04
#define ADC20_EPWMxSOCB_7               0x08
#define ADC20_EPWMxSOCB_8               0x10
#define ADC20_EPWMxSOCA_6               0x20
#define ADC20_EPWMxSOCA_7               0x40
#define ADC20_EPWMxSOCA_8               0x80
                                            
#define ADC21_ADC_ESOC_21               0x01
#define ADC21_EPWMxSOCB_1               0x02
#define ADC21_EPWMxSOCB_6               0x04
#define ADC21_EPWMxSOCB_7               0x08
#define ADC21_EPWMxSOCB_8               0x10
#define ADC21_EPWMxSOCA_6               0x20
#define ADC21_EPWMxSOCA_7               0x40
#define ADC21_EPWMxSOCA_8               0x80

#define ADC_CTRL_ENABLE                 0x01
#define ADC_CTRL_RESET                  0x02
#define ADC_CTRL_BUFEN                  0x04
#define ADC_CTRL_START_CONV             0x08
#define ADC_CTRL_CONT_CONV              0x10
#define ADC_CTRL_CONV_TRIG(x)           ( ( x & 0xFF ) << 6 )
#define ADC_CTRL_MAX_CNV(x)             ( ( x & 0x1F ) << 14 )
#define ADC_CTRL_DELAY_TIME(x)          ( ( x & 0xFF ) << 24 )

/* ADC_SYNC_CTRL */
#define ADC_SYNC_OFF                    0x00
#define ADC_SYNC_ADCX                   0x01
#define ADC_SYNC_EXT                    0x02
#define ADC_SYNC_SYNCHRO                0x03
#define ADC_SYNC_INTRLV                 0x04

#define ADC_SYNC_CTRL_MODE_ADC0(x)      ( x & 0x07 )
#define ADC_SYNC_CTRL_OUT_DLY_ADC0(x)   ( ( x & 0xFF ) << 4 )
#define ADC_SYNC_CTRL_MODE_ADC1(x)      ( ( x & 0x07 ) << 16 )
#define ADC_SYNC_CTRL_OUT_DLY_ADC1(x)   ( ( x & 0xFF ) << 20 )

/* ADC_BUF_MODE */
#define ADC_BUF_LIM_ADC0(x)             ( x & 0xF )
#define ADC_BUF_MODE_ADC0               0x00000100
#define ADC_BUF_LIM_ADC1(x)             ( ( x & 0xF ) << 12 )
#define ADC_BUF_MODE_ADC1               0x00100000

/* ADC_INT_CNTRL */
#define ADC_INT_FIFO_FULL_ADC0          0x0001
#define ADC_INT_FIFO_NEMPTY_ADC0        0x0002
#define ADC_INT_FIFO_LIM_ADC0           0x0004
#define ADC_INT_END_CONV_ADC0           0x0008
#define ADC_INT_FIFO_FULL_ADC1          0x0010
#define ADC_INT_FIFO_NEMPTY_ADC1        0x0020
#define ADC_INT_FIFO_LIM_ADC1           0x0040
#define ADC_INT_END_CONV_ADC1           0x0080
#define ADC_INT_SCOPE_ERR_ADC0          0x0100
#define ADC_INT_SCOPE_ERR_ADC1          0x0200

/* ADC_DMA_CNTRL */
#define ADC_DMA_FIFO_FULL_ADC0          0x01
#define ADC_DMA_FIFO_NEMPTY_ADC0        0x02
#define ADC_DMA_FIFO_LIM_ADC0           0x04
#define ADC_DMA_END_CONV_ADC0           0x08
#define ADC_DMA_FIFO_FULL_ADC1          0x10
#define ADC_DMA_FIFO_NEMPTY_ADC1        0x20
#define ADC_DMA_FIFO_LIM_ADC1           0x40
#define ADC_DMA_END_CONV_ADC1           0x80

/* BNGP_CTRL register bits */
#define ANABG_IREFEN                (1 << 0)
#define ANABG_BFEN(x)               ((x & 0x3F) << 1)
#define ANABG_BGEN                  (1 << 7)
#define ANABG_BFEXT(x)              ((x & 0xF) << 8)
#define ANABG_SWMODE(x)             ((x & 0x3F) << 12)
#define ANABG_EXTMODE               (1 << 18)
#define ANABG_IRECMODE              (1 << 19)
#define ANABG_VRECMODE              (1 << 20)
#define ANABG_ZMODE                 (1 << 21)

/* ANALOG_CTRL register bits */
#define OFFSET_ADC0(x)              (x & 0xFF)
#define MODE_ADC0                   (1 << 9)
#define OFFSET_ADC1(x)              ((x & 0xFF) << 12)
#define MODE_ADC1                   (1 << 21)

#define TEST_ADC            MDR_ADC1
#define ADC_PORT            MDR_PORTC
#define ADC_PIN             PORT_Pin_13

typedef struct
{
    uint8_t ucAdc0ConvChP[ ADC_CNV_NUM_MAX ];
    uint8_t ucAdc0ConvChN[ ADC_CNV_NUM_MAX ];
    uint8_t ucAdc1ConvChP[ ADC_CNV_NUM_MAX ];
    uint8_t ucAdc1ConvChN[ ADC_CNV_NUM_MAX ];
    uint8_t ucAdc0ConvCnt;
    uint8_t ucAdc1ConvCnt;
}ADC_CH_TypeDef;

/** @} */ /* End of group BSP_ADC_Exported_Types */

/** @defgroup BSP_ADC_Exported_Functions BSP ADC Exported Functions
  * @{
  */

void AdcInitChStruct( ADC_CH_TypeDef *adcCh );
void AdcInitBg( ADCxControl *adc );
void AdcInit( ADCxControl *adc, ADC_CH_TypeDef *convCh, uint32_t freq );
void InitAdcTest( void );
void AdcStartConv( ADCxControl *adc );

//uint32_t AdcLoop( void );
void DeinitAdc( ADCxControl *adc );

/** @} */ /* End of group BSP_ADC_Exported_Functions */

/** @} */ /* End of group BSP_ADC */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __ADC_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE adc.h */


