/**
  ******************************************************************************
  * @file    pwm.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   PWM source file for demo board.
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
  * FILE pwm.c
  */

/* Includes ------------------------------------------------------------------*/
#include "pwm.h"

#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MLDR149 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_PWM BSP_PWM
  * @{
  */

/** @defgroup BSP_PWM_Exported_Functions BSP_PWM Exported Functions
  * @{
  */

void PwmInitConfStruct( PWM_Conf_TypeDef *pwmConf )
{
    pwmConf->ulPeriod = 0;
    pwmConf->ulPhase = 0;
    pwmConf->ulCmpA = 0;
    pwmConf->ulCmpB = 0;
    pwmConf->ucCountMode = CTR_CNT_STOP;
    
    pwmConf->ucSyncOutSelect = SYNCOSEL_DIRECT;
    
    pwmConf->eEnableSyncPhase = DISABLE;
    pwmConf->eDirectPeriodWrite = DISABLE;
    
    pwmConf->eEnableSocA = DISABLE;
    pwmConf->ucSocAEvent = ETSEL_EVENT_NONE;
    pwmConf->eEnableSocB = DISABLE;
    pwmConf->ucSocBEvent = ETSEL_EVENT_NONE;    
    pwmConf->eEnableIrq = DISABLE;
    pwmConf->ucIrqEvent = ETSEL_EVENT_NONE;
    
    for( uint8_t i = 0; i < 4; i++ )
    {
        pwmConf->xEventA[ i ].ucEventSel = EVENT_CTR_ZERO;
        pwmConf->xEventA[ i ].ucActionDec = EVENT_ACT_NONE;
        pwmConf->xEventA[ i ].ucActionInc = EVENT_ACT_NONE;
        
        pwmConf->xEventB[ i ].ucEventSel = EVENT_CTR_ZERO;
        pwmConf->xEventB[ i ].ucActionDec = EVENT_ACT_NONE;
        pwmConf->xEventB[ i ].ucActionInc = EVENT_ACT_NONE;
    }
}

void PwmInit( PWMControl *pwm, PWM_Conf_TypeDef *pwmConf )
{
    pwm->TBPRD = pwmConf->ulPeriod;
    pwm->TBPHS = pwmConf->ulPhase;
    pwm->CMPA  = pwmConf->ulCmpA; 
    pwm->CMPB  = pwmConf->ulCmpB; 
    
    pwm->AQCTLA = ( uint32_t )pwmConf->xEventA[0].ucEventSel << 22 |
                  pwmConf->xEventA[1].ucEventSel << 20 |
                  pwmConf->xEventA[2].ucEventSel << 18 |
                  pwmConf->xEventA[3].ucEventSel << 16 |
                  pwmConf->xEventA[0].ucActionInc << 14 |    
                  pwmConf->xEventA[0].ucActionDec << 12 | 
                  pwmConf->xEventA[1].ucActionInc << 10 |    
                  pwmConf->xEventA[1].ucActionDec << 8 | 
                  pwmConf->xEventA[2].ucActionInc << 6 |    
                  pwmConf->xEventA[2].ucActionDec << 4 | 
                  pwmConf->xEventA[3].ucActionInc << 2 |    
                  pwmConf->xEventA[3].ucActionDec;
    
    pwm->AQCTLB = ( uint32_t )pwmConf->xEventB[0].ucEventSel << 22 |
                  pwmConf->xEventB[1].ucEventSel << 20 |
                  pwmConf->xEventB[2].ucEventSel << 18 |
                  pwmConf->xEventB[3].ucEventSel << 16 |
                  pwmConf->xEventB[0].ucActionInc << 14 |    
                  pwmConf->xEventB[0].ucActionDec << 12 | 
                  pwmConf->xEventB[1].ucActionInc << 10 |    
                  pwmConf->xEventB[1].ucActionDec << 8 | 
                  pwmConf->xEventB[2].ucActionInc << 6 |    
                  pwmConf->xEventB[2].ucActionDec << 4 | 
                  pwmConf->xEventB[3].ucActionInc << 2 |    
                  pwmConf->xEventB[3].ucActionDec; 
    
    pwm->TBCTL =  pwmConf->ucSyncOutSelect << 4 |
                  pwmConf->eDirectPeriodWrite << 3 | 
                  pwmConf->eEnableSyncPhase << 2 |  
                  pwmConf->ucCountMode;
    
    pwm->ETSEL  = pwmConf->eEnableSocB << 15 |
                  pwmConf->ucSocBEvent << 12 |
                  pwmConf->eEnableSocA << 11 |
                  pwmConf->ucSocAEvent << 8 |    
                  pwmConf->eEnableIrq << 3 | 
                  pwmConf->ucIrqEvent;
}

void PwmInitClk( PWMControl *pwm, uint16_t div )
{
    switch( ( uint32_t )pwm )
    {
    case ( uint32_t )MDR_PWM0:
        MDR_CLK->PWM0_CLK = CLK_ENABLE | div;
        break;
    case ( uint32_t )MDR_PWM1:
        MDR_CLK->PWM1_CLK = CLK_ENABLE | div;
        break;
    case ( uint32_t )MDR_PWM2:
        MDR_CLK->PWM2_CLK = CLK_ENABLE | div;
        break;
    case ( uint32_t )MDR_PWM3:
        MDR_CLK->PWM3_CLK = CLK_ENABLE | div;
        break;
    case ( uint32_t )MDR_PWM4:
        MDR_CLK->PWM4_CLK = CLK_ENABLE | div;
        break;
    case ( uint32_t )MDR_PWM5:
        MDR_CLK->PWM5_CLK = CLK_ENABLE | div;
        break;
    case ( uint32_t )MDR_PWM6:
        MDR_CLK->PWM6_CLK = CLK_ENABLE | div;
        break;
    case ( uint32_t )MDR_PWM7:
        MDR_CLK->PWM7_CLK = CLK_ENABLE | div;
        break;
    case ( uint32_t )MDR_PWM8:
        MDR_CLK->PWM8_CLK = CLK_ENABLE | div;
        break;
    }
}

/** @} */ /* End of group BSP_PWM_Exported_Functions */

/** @} */ /* End of group BSP_PWM */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE pwm.c */


