/**
  ******************************************************************************
  * @file    retarget_uart.c
  * @author  Milandr Application Team
  * @version V2.0.1
  * @date    04/04/2022
  * @brief   Retarget the C library printf and scanf function to the UART.
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
#include <MDR32FxQI_port.h>
#include <MDR32FxQI_rst_clk.h>
#include <MDR32FxQI_uart.h>
#include "stdio.h"

#if defined ( _USE_DEBUG_UART_ )
/* Private macro -------------------------------------------------------------*/
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
    
/* Private variables ---------------------------------------------------------*/
#if defined ( __ARMCC_VERSION ) /* ARM Compiler */
#if defined ( __CC_ARM )
struct __FILE { int handle; /* Add whatever you need here */ };
#endif /* #if defined __CC_ARM (ARM Compiler 5) */
FILE __stdout;
FILE __stdin;
#endif /* #if defined __ARMCC_VERSION */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief	Configure UART
  * @param	None
  * @retval None
  */
void DebugUARTInit(void)
{
    UART_InitTypeDef UART_InitStructure;
    PORT_InitTypeDef PORT_InitStructure;
    uint32_t BaudRateStatus;

    /* Enable peripheral clocks */
    RST_CLK_PCLKcmd((RST_CLK_PCLK_PORTF | RST_CLK_PCLK_UART2), ENABLE);

    /* Fill PORT_InitStructure */
    PORT_StructInit(&PORT_InitStructure);
    
    PORT_InitStructure.PORT_Pin = DEBUG_UART_PINS;
    PORT_InitStructure.PORT_FUNC = DEBUG_UART_PINS_FUNCTION;
    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;

    /* Configure DEBUG_UART_PORT pins */
    PORT_Init(DEBUG_UART_PORT, &PORT_InitStructure);

    /* Reset DEBUG_UART settings */
    UART_DeInit(DEBUG_UART);

    /*  Initialize UART_InitStructure */
    UART_InitStructure.UART_BaudRate            = DEBUG_BAUD_RATE;
    UART_InitStructure.UART_WordLength          = UART_WordLength8b;
    UART_InitStructure.UART_StopBits            = UART_StopBits1;
    UART_InitStructure.UART_Parity              = UART_Parity_No;
    UART_InitStructure.UART_FIFOMode            = UART_FIFO_ON;
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE | UART_HardwareFlowControl_TXE;

    /* Configure DEBUG_UART parameters */
    UART_BRGInit(DEBUG_UART, UART_HCLKdiv1);
    BaudRateStatus = UART_Init(DEBUG_UART, &UART_InitStructure);

    if(BaudRateStatus == SUCCESS)
    {
        UART_Cmd(DEBUG_UART, ENABLE);
    }
    else
    {
        while(1);
    }

    printf("\n\r======== System startup ========\n\r");
    printf("Init Debug UART ... Ok\r\n");
}

PUTCHAR_PROTOTYPE
{
    // Wait until there is enough space in TX buffer
    while (UART_GetFlagStatus(DEBUG_UART, UART_FLAG_TXFF) == SET);
    UART_SendData(DEBUG_UART, (uint8_t) ch);
    
    return (ch);
}

GETCHAR_PROTOTYPE
{
    // Wait until a character is received
    while (UART_GetFlagStatus(DEBUG_UART, UART_FLAG_RXFE) == SET);
    
    return (UART_ReceiveData(DEBUG_UART));
}
#endif /* #if defined _USE_DEBUG_UART_ */


