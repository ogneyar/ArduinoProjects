/**
  ******************************************************************************
  * @file    rs485.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   RS485 source file for demo board.
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
  * FILE rs485.c
  */

/* Includes ------------------------------------------------------------------*/
#include "rs485.h"

#include "MDR1986VK01_port.h"
#include "MDR1986VK01_uart.h"
#include "MDR1986VK01_clk.h"
#include "MDR1986VK01_it.h"

#include <string.h>
#include <stdlib.h>

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_RS485 BSP_RS485
  * @{
  */

/** @defgroup BSP_RS485_Private_Defines BSP_RS485 Private Defines
  * @{
  */

#define MAX_INPUT_BUFF						24

/** @} */ /* End of group BSP_RS485_Private_Defines */

/** @defgroup BSP_RS485_Private_Variables BSP_RS485 Private Variables
  * @{
  */

uint8_t ucUartData[ MAX_INPUT_BUFF ];
volatile uint16_t usUartRxLenght;                                                       
volatile uint8_t ucRxDone;

volatile uint16_t usRemainingDataSize;
uint8_t *pucTxData;
uint8_t ucText[ 32 ];

/** @} */ /* End of group BSP_RS485_Private_Variables */

/** @defgroup BSP_RS485_Exported_Functions BSP_RS485 Exported Functions
  * @{
  */

void InitRs485( uint32_t speed )
{
    PORT_InitTypeDef uartPort;
    UART_InitTypeDef uartInit;

    PORT_StructInit( &uartPort );
    UART_StructInit( &uartInit );

    MDR_PORTB->KEY = 0x8555AAA1;

    uartPort.PORT_Pin     = PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3;
    uartPort.PORT_SOE     = PORT_SOE_OUT;
	uartPort.PORT_SFUNC   = PORT_SFUNC_5;
	uartPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    uartPort.PORT_SPWR    = PORT_SPWR_300;

    PORT_Init( MDR_PORTB, &uartPort );

    MDR_PORTA->KEY = 0x8555AAA1;
    uartPort.PORT_Pin     = PORT_Pin_25 | PORT_Pin_26;
    uartPort.PORT_SOE     = PORT_SOE_OUT;
	uartPort.PORT_SFUNC   = PORT_SFUNC_PORT;
	uartPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    uartPort.PORT_SPWR    = PORT_SPWR_300;

    PORT_Init( MDR_PORTA, &uartPort );

    UART_BRGInit( RS485_UART0, 0, CLK_SOURCE_MAX_CLK );
    UART_BRGInit( RS485_UART1, 0, CLK_SOURCE_MAX_CLK );

    uartInit.UART_BaudRate = speed;
    uartInit.UART_FIFOMode = UART_FIFO_ON;
    UART_Init( RS485_UART0, &uartInit );
    UART_Init( RS485_UART1, &uartInit );

    UART_Cmd( RS485_UART0, ENABLE );
    UART_Cmd( RS485_UART1, ENABLE );

    UART_DMAConfig( RS485_UART0, UART_IT_FIFO_LVL_12words, UART_IT_FIFO_LVL_2words );
    UART_DMAConfig( RS485_UART1, UART_IT_FIFO_LVL_12words, UART_IT_FIFO_LVL_2words );
    UART_ITConfig( RS485_UART0, UART_IT_RT | UART_IT_RX, ENABLE );
    UART_ITConfig( RS485_UART1, UART_IT_RT | UART_IT_RX, ENABLE );
    UART_Cmd( RS485_UART0, ENABLE );
    UART_Cmd( RS485_UART1, ENABLE );

    NVIC_SetPriority( UART0_IRQn, 5 );
    NVIC_SetPriority( UART1_IRQn, 5 );
    NVIC_EnableIRQ( UART0_IRQn );
    NVIC_EnableIRQ( UART1_IRQn );
}

void SetOutput0( void )
{
    PORT_SetBits(MDR_PORTA, PORT_Pin_26);
    PORT_ResetBits(MDR_PORTA, PORT_Pin_25);
}

void SetOutput1( void )
{
    PORT_ResetBits(MDR_PORTA, PORT_Pin_26);
    PORT_SetBits(MDR_PORTA, PORT_Pin_25);
}

void DeinitRs485( void )
{
    PORT_InitTypeDef uartPort;

    UART_Cmd( MDR_UART0, DISABLE );
    UART_Cmd( MDR_UART1, DISABLE );

    UART_DeInit( MDR_UART0 );
    UART_DeInit( MDR_UART1 );

    MDR_CLK->UART0_CLK = 0;
    MDR_CLK->UART1_CLK = 0;

    PORT_StructInit( &uartPort );

    MDR_PORTB->KEY = 0x8555AAA1;

    uartPort.PORT_Pin     = PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3;
    uartPort.PORT_SOE     = PORT_SOE_IN;
	uartPort.PORT_SFUNC   = PORT_SFUNC_PORT;
	uartPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    uartPort.PORT_SPWR    = PORT_SPWR_300;

    PORT_Init( MDR_PORTB, &uartPort );
}

void UartSendBuff( MDR_UART_TypeDef* UARTx, uint8_t* pucData, uint16_t usLenght )
{
    usRemainingDataSize = usLenght;
    pucTxData = pucData;

    while( usRemainingDataSize && !( UARTx->FR & UART_FLAG_TXFF ) )
    {
        UARTx->DR = *pucTxData++;
        usRemainingDataSize--;
    }

    MDR_PORTA->SRXTX = 1;
    UART_ITConfig( UARTx, UART_IT_TX | UART_IT_TNBSY, ENABLE );
    UARTx->CR |= 1 << UART_CR_TXE_Pos;
}

/* ------------------------------ UART0 ------------------------------- */
void UART0_IRQHandler( void )
{
    uint8_t ucMaxBytesToRead = 11;

    if ( UART_GetITStatusMasked( MDR_UART0, UART_IT_RX ) == SET )
    {
        while ( ucMaxBytesToRead )
        {
            if( ( usUartRxLenght < MAX_INPUT_BUFF ) && !ucRxDone )
                ucUartData[ usUartRxLenght++ ] = UART_ReceiveData( MDR_UART0 );
            else
                UART_ReceiveData( MDR_UART0 );

            ucMaxBytesToRead--;
        }
    }

    if ( UART_GetITStatusMasked( MDR_UART0, UART_IT_RT ) == SET )
    {
        while ( !( MDR_UART0->FR & UART_FLAG_RXFE ) )
        {
            if( ( usUartRxLenght < MAX_INPUT_BUFF ) && !ucRxDone )
                ucUartData[ usUartRxLenght++ ] = UART_ReceiveData( MDR_UART0 );
            else
                UART_ReceiveData( MDR_UART0 );
        }
        ucRxDone = 1;
    }

    if ( UART_GetITStatusMasked( MDR_UART0, UART_IT_TX ) == SET )
    {
        if( usRemainingDataSize )
        {
            while( usRemainingDataSize && !( MDR_UART0->FR & UART_FLAG_TXFF ) )
            {
                MDR_UART0->DR = *pucTxData++;
                usRemainingDataSize--;
            }
        }
        else
        {
            UART_ITConfig( MDR_UART0, UART_IT_TX, DISABLE );
            UART_ClearITPendingBit( MDR_UART0, UART_IT_TX );
        }
    }

    if ( UART_GetITStatusMasked( MDR_UART0, UART_IT_TNBSY ) == SET )
    {
        MDR_PORTA->CRXTX = 1;
        UART_ITConfig( MDR_UART0, UART_IT_TNBSY, DISABLE );
        UART_ClearITPendingBit( MDR_UART0, UART_IT_TNBSY );
    }
}

/* ------------------------------ UART1 ------------------------------- */
void UART1_IRQHandler( void )
{
    uint8_t ucMaxBytesToRead = 11;

    if ( UART_GetITStatusMasked( MDR_UART1, UART_IT_RX ) == SET )                       
    {
        while ( ucMaxBytesToRead )                                                      
        {
            if( ( usUartRxLenght < MAX_INPUT_BUFF ) && !ucRxDone )
                ucUartData[ usUartRxLenght++ ] = UART_ReceiveData( MDR_UART1 );
            else
                UART_ReceiveData( MDR_UART1 );

            ucMaxBytesToRead--;
        }
    }

    if ( UART_GetITStatusMasked( MDR_UART1, UART_IT_RT ) == SET )                       
    {
        while ( !( MDR_UART1->FR & UART_FLAG_RXFE ) )
        {
            if( ( usUartRxLenght < MAX_INPUT_BUFF ) && !ucRxDone )
                ucUartData[ usUartRxLenght++ ] = UART_ReceiveData( MDR_UART1 );
            else
                UART_ReceiveData( MDR_UART1 );
        }
        ucRxDone = 1;
    }

    if ( UART_GetITStatusMasked( MDR_UART1, UART_IT_TX ) == SET )                        
    {
        if( usRemainingDataSize )
        {
            while( usRemainingDataSize && !( MDR_UART1->FR & UART_FLAG_TXFF ) )
            {
                MDR_UART1->DR = *pucTxData++;
                usRemainingDataSize--;
            }
        }
        else
        {
            UART_ITConfig( MDR_UART1, UART_IT_TX, DISABLE );
            UART_ClearITPendingBit( MDR_UART1, UART_IT_TX );
        }
    }

    if ( UART_GetITStatusMasked( MDR_UART1, UART_IT_TNBSY ) == SET )                      
    {
        MDR_PORTA->CRXTX = 1;
        UART_ITConfig( MDR_UART1, UART_IT_TNBSY, DISABLE );
        UART_ClearITPendingBit( MDR_UART1, UART_IT_TNBSY );
    }
}

void RS485Func( void )
{

    uint8_t ucData0[] = "abcd";
    uint8_t ucData1[] = "efgh";

    uint8_t output = 0;
		uint32_t q;
	
    while(1)
    {
        if(output == 0)
        {
            SetOutput1();
            UartSendBuff( RS485_UART1, ucData1, sizeof(ucData1) );
            output = 1;
        } else {
            SetOutput0();
            UartSendBuff( RS485_UART0, ucData0, sizeof(ucData0) );
            output = 0;
        }
				
		for(q=0;q<500000;q++){}
				
        if( ucRxDone )
        {
            memcpy( ucText, ucUartData, usUartRxLenght );
            ucText[ usUartRxLenght ] = 0;

            usUartRxLenght = 0;
            ucRxDone = 0;
        }
    }

    DeinitRs485();
}

/** @} */ /* End of group BSP_RS485_Exported_Functions */

/** @} */ /* End of group BSP_RS485 */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE rs485.c */


