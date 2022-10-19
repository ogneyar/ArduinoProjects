/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    07/04/2022
  * @brief   Main program body.
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
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"
#include "MDR1986VK01_uart.h"
#include "MDR1986VK01_it.h"

#include <string.h>
#include <stdlib.h>

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup uart_echo uart_echo
 *  @{
 */

PORT_InitTypeDef uartPort;
UART_InitTypeDef uartInit;

void ClockInit()
{
    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK =  0xFFFFFFFF;
    MDR_CLK->PER1_CLK =  0xFFFFFFFF;

    MDR_BKP->KEY = 0x8555AAA1;

    CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
    if( !CLK_XSEWaitReady( CLK_HSE0 ) )
        while(1){}

//    CLK_SetPllClk( &MDR_CLK->PLL[0], PLL_CLK_HSE0, CPU_CLK );
//    CLK_PllState( &MDR_CLK->PLL[0], ENABLE );
//    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[0] ) )
//        while(1){}

//    CLK_SetPllClk( &MDR_CLK->PLL[2], PLL_CLK_HSE0, 50000000 );
//    CLK_PllState( &MDR_CLK->PLL[2], ENABLE );
//    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[2] ) )
//        while(1){}

    CLK_SetSystemClock( MAX_CLK_HSE0 );
}

int main()
{
    ClockInit();
    
    PORT_StructInit( &uartPort );
    UART_StructInit( &uartInit );

    MDR_PORTB->KEY = 0x8555AAA1;

    uartPort.PORT_Pin     = PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3;
    uartPort.PORT_SOE     = PORT_SOE_OUT;
    uartPort.PORT_SFUNC   = PORT_SFUNC_5;
    uartPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    uartPort.PORT_SPWR    = PORT_SPWR_300;

    PORT_Init( MDR_PORTB, &uartPort );

    UART_BRGInit( MDR_UART0, 0, CLK_SOURCE_MAX_CLK );
    UART_BRGInit( MDR_UART1, 0, CLK_SOURCE_MAX_CLK );

    uartInit.UART_BaudRate = 115200;
    uartInit.UART_FIFOMode = UART_FIFO_OFF;
    UART_Init( MDR_UART0, &uartInit );
    UART_Init( MDR_UART1, &uartInit );

    UART_Cmd( MDR_UART0, ENABLE );
    UART_Cmd( MDR_UART1, ENABLE );
    
    UART_ITConfig( MDR_UART0, UART_IT_RX, ENABLE );
    //UART_ITConfig( MDR_UART1, UART_IT_RX, ENABLE );
    
    NVIC_EnableIRQ( UART0_IRQn );
    NVIC_EnableIRQ( UART1_IRQn );
    
    while(1)
    {
    
    }
    
}

/** @} */ /* End of group uart_echo */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */


