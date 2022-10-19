/**
  ******************************************************************************
  * @file    pwm.h
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    11/11/2020
  * @brief   PWM header file for demo board.
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
  * FILE pwm.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PWM_H
#define __PWM_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_PWM BSP_PWM
  * @{
  */

/** @defgroup BSP_PWM_Private_Defines BSP_PWM Private Defines
  * @{
  */

#define EVENT_EQ_CMPB           0    
#define EVENT_EQ_CMPA           1
#define EVENT_CTR_ZERO          2  
#define EVENT_CTR_PRD           3      
        
#define EVENT_ACT_NONE          0
#define EVENT_ACT_RESET         1
#define EVENT_ACT_SET           2    
#define EVENT_ACT_I_MODE        3 
    
#define CTR_CNT_UP              0    
#define CTR_CNT_DOWN            1
#define CTR_CNT_UP_DOWN         2
#define CTR_CNT_STOP            3 
    
#define SYNCOSEL_DIRECT         0
#define SYNCOSEL_CTR_ZERO       1
#define SYNCOSEL_CTR_CMP        2
#define SYNCOSEL_OFF            3

/* EVENTS */
#define ETSEL_EVENT_NONE               0
#define ETSEL_EVENT_CTR_ZERO           1
#define ETSEL_EVENT_CTR_EQ_PRD         2
#define ETSEL_EVENT_CTR_EQ_CMPA_INC    4
#define ETSEL_EVENT_CTR_EQ_CMPA_DEC    5
#define ETSEL_EVENT_CTR_EQ_CMPB_INC    6
#define ETSEL_EVENT_CTR_EQ_CMPB_DEC    7

/** @} */ /* End of group BSP_PWM_Private_Defines */

/** @defgroup BSP_PWM_Exported_Types BSP_PWM Exported Types
  * @{
  */

typedef struct
{
    uint8_t ucEventSel;                                                                 /*!< Event source selection */
    uint8_t ucActionInc;                                                                /*!< Main counter increment action */
    uint8_t ucActionDec;                                                                /*!< Main counter decrement action */
}PWM_Event_TypeDef;

typedef struct
{
    uint32_t ulPeriod;
    uint32_t ulPhase;
    uint32_t ulCmpA;
    uint32_t ulCmpB;
    uint8_t ucCountMode;
    
    uint8_t ucSyncOutSelect;
    uint8_t ucSocAEvent;
    uint8_t ucSocBEvent;
    uint8_t ucIrqEvent;
    
    FunctionalState eEnableSyncPhase;
    FunctionalState eDirectPeriodWrite;
    FunctionalState eEnableSocA;
    FunctionalState eEnableSocB;
    FunctionalState eEnableIrq;
    
    PWM_Event_TypeDef xEventA[4];
    PWM_Event_TypeDef xEventB[4];
}PWM_Conf_TypeDef;

/** @} */ /* End of group BSP_PWM_Exported_Types */

/** @defgroup BSP_PWM_Exported_Functions BSP_PWM Exported Functions
  * @{
  */

void PwmInitConfStruct( PWM_Conf_TypeDef *pwmConf );
void PwmInit( PWMControl *pwm, PWM_Conf_TypeDef *conf );
void PwmInitClk( PWMControl *pwm, uint16_t div );

/** @} */ /* End of group BSP_PWM_Exported_Functions */

/** @} */ /* End of group BSP_PWM */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __PWM_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE pwm.h */


