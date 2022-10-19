/**
  ******************************************************************************
  * @file    MDR1986VK01_it.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    07/04/2022
  * @brief   Main Interrupt Service Routines.
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

#include "MDR1986VK01_it.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern DMA_ChannelInitTypeDef DMA_InitStr;
extern DMA_CtrlDataInitTypeDef DMA_PriCtrlStr;
extern DMA_CtrlDataInitTypeDef DMA_AltCtrlStr;

void DMA_DONE0_IRQHandler(void)
{
  if((MDR_DMA->CHNL_PRI_ALT_SET &(1<<0)) == (0<<0))
  {
   DMA_CtrlInit(0, DMA_CTRL_DATA_ALTERNATE,  &DMA_AltCtrlStr);
  }
  else if((MDR_DMA->CHNL_PRI_ALT_SET & (1<<0)) == (1<<0))
  {
   DMA_CtrlInit(0, DMA_CTRL_DATA_PRIMARY, &DMA_PriCtrlStr);
  }
}

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE MDR1986VK01_it.c */


