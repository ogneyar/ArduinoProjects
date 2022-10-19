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
#include "rtc.h"

#include <string.h>
#include <stdlib.h>

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup rtc rtc
 *  @{
 */

uint32_t tmp;
tTime time;
tDate date;

void ClockInit()
{
    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK =  0xFFFFFFFF;
    MDR_CLK->PER1_CLK =  0xFFFFFFFF;

//    MDR_COMP0->ANABG_CTRL = ANABG_IREFEN | ANABG_BGEN |
//                      ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );
    
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
    
    InitRtc();
    
    time.sec = 0;
    time.min = 0;
    time.hour = 0;
    tDate date;
    date.day = 1;
    date.month = 1;
    date.year = 2020;
    
    if(MDR_BKP->REG_xx[0] == 0)
    {
        date.year=2050;
        date.month=11;
        date.day=3;
        
        setDate(date);
        
        time.hour=14;
        time.min=13;
        time.sec=11;
        
        setTime(time);

        MDR_BKP->REG_xx[0] = 1;
    }
    
    
    tmp = MDR_BKP->RTC_CNT_TMR0;
    
    while(1)
    {
        if(tmp != MDR_BKP->RTC_CNT_TMR0)
        {
            tmp = MDR_BKP->RTC_CNT_TMR0;
            time = getTime();
            date = getDate();
        }
    }
}

/** @} */ /* End of group rtc */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */


