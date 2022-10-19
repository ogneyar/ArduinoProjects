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
#include "MDR32FxQI_can.h"

/* Private variables ---------------------------------------------------------*/
extern __IO uint32_t ret;
extern __IO uint32_t rx_buf;

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : CAN1_IRQHandler
* Description    : This function handles CAN1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN1_IRQHandler(void)
{
    CAN_RxMsgTypeDef RxMessage;

    CAN_GetRawReceivedData(MDR_CAN1, rx_buf, &RxMessage);

    if((RxMessage.Rx_Header.ID==0x15555555) && (RxMessage.Rx_Header.IDE==CAN_ID_EXT)
    && (RxMessage.Rx_Header.DLC==4) && (RxMessage.Data[0]==0x12345678))
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    CAN_ITClearRxTxPendingBit(MDR_CAN1, rx_buf, CAN_STATUS_RX_READY);
}

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE MDR32F9Q2I_IT.c */


