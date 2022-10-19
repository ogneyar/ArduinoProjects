/**
  ******************************************************************************
  * @file    leds.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   Leds source file for demo board.
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
  * FILE leds.c
  */

/* Includes ------------------------------------------------------------------*/
#include "leds.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_LEDS BSP_LEDS
  * @{
  */

/** @defgroup BSP_LEDS_Private_Variables BSP_LEDS Private Variables
  * @{
  */

static MDR_TIMER_TypeDef* LedTMR[3] = { LED_GREEN_TMR, LED_RED_TMR, LED_BLUE_TMR};
static uint32_t LedChns[3] = { LED_GREEN_CHN, LED_RED_CHN, LED_BLUE_CHN };
static uint32_t LedMBrs[3] = { LED_GREEN_MAX_BRIGHT, LED_RED_MAX_BRIGHT, LED_BLUE_MAX_BRIGHT };

/** @} */ /* End of group BSP_LEDS_Private_Variables */

/** @defgroup BSP_LEDS_Exported_Functions BSP_LEDS Exported Functions
  * @{
  */

/* Initialize RGB LED pins */
void LedInit( void )
{
    PORT_InitTypeDef ledPort;
    TIMER_CntInitTypeDef ledTimerCnt;
    TIMER_ChnInitTypeDef ledTimerCh;
    TIMER_ChnOutInitTypeDef ledTimerChOut;

    PORT_StructInit( &ledPort );
    TIMER_CntStructInit( &ledTimerCnt );
    TIMER_ChnStructInit( &ledTimerCh );
    TIMER_ChnOutStructInit( &ledTimerChOut );

    LED_GREEN_PORT->KEY = 0x8555AAA1;
    
    ledPort.PORT_Pin     = LED_GREEN_PIN;
    ledPort.PORT_SOE     = PORT_SOE_OUT;
    ledPort.PORT_SFUNC   = PORT_SFUNC_10;
    ledPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    ledPort.PORT_SPWR    = PORT_SPWR_10;
    PORT_Init( LED_GREEN_PORT, &ledPort );
    
    TIMER_BRGInit( LED_GREEN_TMR, 0 );

    ledTimerCnt.TIMER_Period = LED_MAX_BRIGHT;
    TIMER_CntInit( LED_GREEN_TMR, &ledTimerCnt );

    ledTimerCh.TIMER_CH_REF_Format = TIMER_CH_REF_Format6;
    ledTimerCh.TIMER_CH_Number = LED_GREEN_CHN;
    TIMER_ChnInit( LED_GREEN_TMR, &ledTimerCh );
  
    ledTimerChOut.TIMER_CH_DirOut_Polarity = TIMER_CHOPolarity_NonInverted;
    ledTimerChOut.TIMER_CH_DirOut_Mode = TIMER_CH_OutMode_Output;
    ledTimerChOut.TIMER_CH_DirOut_Source = TIMER_CH_OutSrc_REF; 
    ledTimerChOut.TIMER_CH_Number = LED_GREEN_CHN;
    TIMER_ChnOutInit( LED_GREEN_TMR, &ledTimerChOut );

    TIMER_Cmd( LED_GREEN_TMR, ENABLE );
    
    LED_RED_PORT->KEY = 0x8555AAA1;
    
    ledPort.PORT_Pin     = LED_RED_PIN;
    ledPort.PORT_SOE     = PORT_SOE_OUT;
    ledPort.PORT_SFUNC   = PORT_SFUNC_10;
    ledPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    ledPort.PORT_SPWR    = PORT_SPWR_10;

    PORT_Init( LED_RED_PORT, &ledPort );
    
    TIMER_BRGInit( LED_RED_TMR, 0 );

    ledTimerCnt.TIMER_Period = LED_MAX_BRIGHT;
    TIMER_CntInit( LED_RED_TMR, &ledTimerCnt );

    ledTimerCh.TIMER_CH_REF_Format = TIMER_CH_REF_Format6;
    ledTimerCh.TIMER_CH_Number = LED_RED_CHN;
    TIMER_ChnInit( LED_RED_TMR, &ledTimerCh );
  
    ledTimerChOut.TIMER_CH_NegOut_Polarity = TIMER_CHOPolarity_Inverted;
    ledTimerChOut.TIMER_CH_NegOut_Mode = TIMER_CH_OutMode_Output;
    ledTimerChOut.TIMER_CH_NegOut_Source = TIMER_CH_OutSrc_REF; 
    ledTimerChOut.TIMER_CH_Number = LED_RED_CHN;
    TIMER_ChnOutInit( LED_RED_TMR, &ledTimerChOut );
    
    TIMER_Cmd( LED_RED_TMR, ENABLE );

    LED_BLUE_PORT->KEY = 0x8555AAA1;
    
    ledPort.PORT_Pin     = LED_BLUE_PIN;
    ledPort.PORT_SOE     = PORT_SOE_OUT;
    ledPort.PORT_SFUNC   = PORT_SFUNC_10;
    ledPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    ledPort.PORT_SPWR    = PORT_SPWR_10;

    PORT_Init( LED_BLUE_PORT, &ledPort );

    TIMER_BRGInit( LED_BLUE_TMR, 0 );

    ledTimerCnt.TIMER_Period = LED_MAX_BRIGHT;
    TIMER_CntInit( LED_BLUE_TMR, &ledTimerCnt );

    ledTimerCh.TIMER_CH_REF_Format = TIMER_CH_REF_Format6;
    ledTimerCh.TIMER_CH_Number = LED_BLUE_CHN;
    TIMER_ChnInit( LED_BLUE_TMR, &ledTimerCh );
  
    ledTimerChOut.TIMER_CH_NegOut_Polarity = TIMER_CHOPolarity_Inverted;
    ledTimerChOut.TIMER_CH_NegOut_Mode = TIMER_CH_OutMode_Output;
    ledTimerChOut.TIMER_CH_NegOut_Source = TIMER_CH_OutSrc_REF; 
    ledTimerChOut.TIMER_CH_Number = LED_BLUE_CHN;
    TIMER_ChnOutInit( LED_BLUE_TMR, &ledTimerChOut );

    TIMER_Cmd( LED_BLUE_TMR, ENABLE );
}

void Led_Set(uint8_t LedNum)
{
    TIMER_SetChnCompare( LedTMR[LedNum], LedChns[LedNum], LedMBrs[LedNum] );
}

void Led_Reset(uint8_t LedNum)
{
  TIMER_SetChnCompare( LedTMR[LedNum], LedChns[LedNum], 0 );
}

/** @} */ /* End of group BSP_LEDS_Exported_Functions */

/** @} */ /* End of group BSP_LEDS */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE leds.ñ */


