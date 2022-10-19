/**
  ******************************************************************************
  * @file    MDR1986VK01_it.c
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    11/11/2020
  * @brief   Main Interrupt Service Routines.
  *
  ******************************************************************************
  * <br><br>
  *
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


void UART0_IRQHandler(void)
{
	uint32_t temp_1;

	if (UART_GetITStatusMasked(MDR_UART0, UART_IT_RX) == SET)
	{
		temp_1 = UART_ReceiveData(MDR_UART0);	
		
		UART_ClearITPendingBit(MDR_UART0, UART_IT_RX);

		while (UART_GetFlagStatus (MDR_UART0, UART_FLAG_TXFE)!= SET)
		{
		}
		UART_SendData (MDR_UART0,temp_1);
  }
}

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE MDR1986VK01_it.c */


