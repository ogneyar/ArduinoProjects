/**
  ******************************************************************************
  * @file    MDR32F9Q2I_IT.c
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    27/07/2021
  * @brief   Main Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Q2I_IT.h"
#include "MDR32FxQI_dma.h"

/* Private variables ---------------------------------------------------------*/
extern DMA_ChannelInitTypeDef DMA_InitStr;
extern DMA_CtrlDataInitTypeDef DMA_PriCtrlStr;
extern DMA_CtrlDataInitTypeDef DMA_AltCtrlStr;

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : DMA_IRQHandler
* Description    : This function handles DMA global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_IRQHandler(void)
{
    /* Reconfigure the inactive DMA data structure*/
    if((MDR_DMA->CHNL_PRI_ALT_SET &(1<<DMA_Channel_TIM1)) == (0<<DMA_Channel_TIM1))
    {
        DMA_AltCtrlStr.DMA_CycleSize = 32;
        DMA_Init(DMA_Channel_TIM1, &DMA_InitStr);
    }
    else if((MDR_DMA->CHNL_PRI_ALT_SET & (1<<DMA_Channel_TIM1)) == (1<<DMA_Channel_TIM1))
    {
        DMA_PriCtrlStr.DMA_CycleSize = 32;
        DMA_Init(DMA_Channel_TIM1, &DMA_InitStr);
    }
}

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE MDR32F9Q2I_IT.c */


