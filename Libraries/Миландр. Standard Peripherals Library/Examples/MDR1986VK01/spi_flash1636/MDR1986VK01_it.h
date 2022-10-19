/**
  ******************************************************************************
  * @file    MDR1986VK01_it.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    14/04/2022
  * @brief   Functions prototypes for the interrupt.
  *
  ******************************************************************************
  * <br><br>
  *
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  */

#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"
#include "MDR1986VK01_uart.h"

void UartSendBuff( MDR_UART_TypeDef* UARTx, uint8_t* pucData, uint16_t usLenght );
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE MDR1986VK01_it.h */


