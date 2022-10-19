/**
  ******************************************************************************
  * @file    MDR32F1QI_IT.h
  * @author  Milandr Application Team
  * @version V2.0.2i
  * @date    10/03/2022
  * @brief   This file contains all the functions prototypes
  *          for the interrupt handlers for MPU MDR32F1QI.
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
#ifndef __MDR32F1QI_IT_H
#define __MDR32F1QI_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32FxQI_config.h"

#if defined (USE_MDR32F1QI)

/* Function prototypes -------------------------------------------------------*/
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void MIL_STD_1553B2_IRQHandler(void);
void MIL_STD_1553B1_IRQHandler(void);
void USB_IRQHandler(void);
void CAN1_IRQHandler(void);
void CAN2_IRQHandler(void);
void DMA_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);
void SSP1_IRQHandler(void);
void BUSY_IRQHandler(void);
void ARINC429R_IRQHandler(void);
void POWER_IRQHandler(void);
void WWDG_IRQHandler(void);
void TIMER4_IRQHandler(void);
void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);
void TIMER3_IRQHandler(void);
void ADC_IRQHandler(void);
void ETHERNET_IRQHandler(void);
void SSP3_IRQHandler(void);
void SSP2_IRQHandler(void);
void ARINC429T1_IRQHandler(void);
void ARINC429T2_IRQHandler(void);
void ARINC429T3_IRQHandler(void);
void ARINC429T4_IRQHandler(void);
void BKP_IRQHandler(void);
void EXT_INT1_IRQHandler(void);
void EXT_INT2_IRQHandler(void);
void EXT_INT3_IRQHandler(void);
void EXT_INT4_IRQHandler(void);

#endif /* #if defined (USE_MDR32F1QI) */

#ifdef __cplusplus
}
#endif

#endif /* __MDR32F1QI_IT_H */

/*********************** (C) COPYRIGHT 2022 Milandr ****************************
*
* END OF FILE MDR32F1QI_IT.h */


