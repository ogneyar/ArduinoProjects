/**
  ******************************************************************************
  * @file    dac.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   DAC source file for demo board.
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
  * FILE dac.c
  */

/* Includes ------------------------------------------------------------------*/
#include "dac.h"
#include <math.h>

#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_DAC BSP_DAC
  * @{
  */

/** @defgroup BSP_DAC_Private_Defines BSP_DAC Private Defines
  * @{
  */

#define DAC_EN_A                    (1 << 0)
#define DAC_EN_D                    (1 << 1)

#define DAC_REF_VDD                 (0 << 2)
#define DAC_REF_VREF0               (1 << 2)
#define DAC_REF_VREF1               (2 << 2)
#define DAC_REF_VREF                (3 << 2)

#define DAC_MODE_SINGLE             (0 << 4)
#define DAC_MODE_FIFO               (1 << 4)
#define DAC_MODE_FIFO_EX_SYNC       (2 << 4)

#define DAC_RST                     (1 << 8)

#define DAC_OUT_2V5                 3100                                                // This code corresponds to 2.5 V at the DAC output

#define DAC_DATA_SIZE               32000
#define DAC_TEST_FREQ               1000.0F

#define M_PI                        3.1415926535897932384626433832795F

/** @} */ /* End of group BSP_DAC_Private_Defines */

uint16_t usDacData[ DAC_DATA_SIZE ];

/** @defgroup BSP_DAC_Exported_Functions BSP_DAC Exported Functions
  * @{
  */

void InitDac( uint32_t freq )
{
    uint16_t i;
    uint32_t per;

    for( i = 0; i < DAC_DATA_SIZE; i++ )
    {
        //usDacData[ i ] = 4095 * ( ( sin( M_PI * 2 * i / DAC_DATA_SIZE ) + 1 ) / 2 );
        usDacData[ i ] = DAC_OUT_2V5 * ( ( sin( DAC_TEST_FREQ * 2 * M_PI * i / DAC_DATA_SIZE ) + 1 ) / 2 );
        //usDacData[ i ] = i;
    }

    per = SystemCoreClock / freq;                                                       // DAC runs at core frequency

    MDR_DAC1->DATA = 0;
    MDR_DAC1->PRD = per;
    MDR_DAC1->CTRL = DAC_EN_A | DAC_EN_D | DAC_REF_VREF | DAC_MODE_FIFO;

    MDR_DAC2->DATA = 0;
    MDR_DAC2->PRD = per;
    MDR_DAC2->CTRL = DAC_EN_A | DAC_EN_D | DAC_REF_VREF | DAC_MODE_FIFO;
}

void SetDac( uint16_t usData )
{
    usData &= 0xFFF;

    if( usData > DAC_OUT_2V5 )
        usData = DAC_OUT_2V5;

    MDR_DAC1->DATA = usData;
}

void DacLoop( void )
{
    static uint16_t i = 0;
    static uint16_t j = 100;

    while( ! ( MDR_DAC1->STS & ( 1 << 3 ) ) )
    {
        MDR_DAC1->DATA = usDacData[ i++ ];

        if( i == DAC_DATA_SIZE )
            i = 0;
    }

    while( ! ( MDR_DAC2->STS & ( 1 << 3 ) ) )
    {
        MDR_DAC2->DATA = usDacData[ j++ ];

        if( j == DAC_DATA_SIZE )
            j = 0;
    }
}

void DeinitDac( void )
{
    MDR_DAC1->CTRL = DAC_RST;
    MDR_DAC2->CTRL = DAC_RST;
}

/** @} */ /* End of group BSP_DAC_Exported_Functions */

/** @} */ /* End of group BSP_DAC */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE dac.c */



