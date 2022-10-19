
/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"
#include "MDR1986VK01_uart.h"

void UartSendBuff( MDR_UART_TypeDef* UARTx, uint8_t* pucData, uint16_t usLenght );
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
