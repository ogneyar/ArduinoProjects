/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    07/04/2022
  * @brief   Main program body.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"
#include "demoboard.h"
#include "dac.h"
#include "adc.h"


#include <string.h>
#include <stdlib.h>
#include <math.h>

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup dac_sin dac_sin
 *  @{
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

#define DAC_OUT_2V5                 3100

#define DAC_DATA_SIZE               32000
#define DAC_TEST_FREQ               1000.0F

#define M_PI                        3.1415926535897932384626433832795F


void ClockInit()
{
    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK =  0xFFFFFFFF;
    MDR_CLK->PER1_CLK =  0xFFFFFFFF;

    MDR_COMP0->ANABG_CTRL= ANABG_IREFEN | ANABG_BGEN | 
                     ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );
    
    MDR_BKP->KEY = 0x8555AAA1;

    CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
    if( !CLK_XSEWaitReady( CLK_HSE0 ) )
        while(1){}

//    CLK_SetPllClk( &MDR_CLK->PLL[0], PLL_CLK_HSE0, CPU_CLK );
//    CLK_PllState( &MDR_CLK->PLL[0], ENABLE );
//    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[0] ) )
//        while(1){}

//    CLK_SetPllClk( &MDR_CLK->PLL[2], PLL_CLK_HSE0, 50000000 );
//    CLK_PllState( &MDR_CLK->PLL[2], ENABLE );
//    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[2] ) )
//        while(1){}

    CLK_SetSystemClock( MAX_CLK_HSE0 );
}

static void vShifterInit( void )
{
    PORT_InitTypeDef ShifterPort;
    PORT_StructInit( &ShifterPort );
    MDR_PORTA->KEY = 0x8555AAA1;
    ShifterPort.PORT_Pin     = PORT_Pin_31;
    ShifterPort.PORT_SOE     = PORT_SOE_OUT;
    ShifterPort.PORT_SFUNC   = PORT_SFUNC_PORT;
    ShifterPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    ShifterPort.PORT_SPWR    = PORT_SPWR_10;
    PORT_Init( MDR_PORTA, &ShifterPort );
    BUF_OE_OFF;
}

int main()
{
    ClockInit();
    
    vShifterInit();
    
    InitDac( 32000 );
    
    while(1)
    {
        DacLoop();
    }
    
}

/** @} */ /* End of group dac_sin */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */


