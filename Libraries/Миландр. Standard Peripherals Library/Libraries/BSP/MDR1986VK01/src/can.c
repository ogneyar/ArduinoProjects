/**
  ******************************************************************************
  * @file    can.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   CAN source file for demo board.
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
  * FILE can.c
  */

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_can.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_CAN BSP_CAN
  * @{
  */

/** @defgroup BSP_CAN_Private_Variables BSP_CAN Private Variables
  * @{
  */

static volatile uint32_t rx_buf = 0;
static volatile uint32_t tx_buf = 1;
static uint32_t i;

/** @} */ /* End of group BSP_CAN_Private_Variables */

/** @defgroup BSP_CAN_Exported_Functions BSP CAN Exported Functions
  * @{
  */

void InitCan( uint32_t speed )
{
    CAN_InitTypeDef  sCAN;
    PORT_InitTypeDef canPort;

    MDR_PORTA->KEY = 0x8555AAA1;
    MDR_PORTB->KEY = 0x8555AAA1;

    PORT_StructInit( &canPort );
    //CAN 0
    //                     RX_0         TX_0
    canPort.PORT_Pin     = PORT_Pin_8 | PORT_Pin_9;
    canPort.PORT_SOE     = PORT_SOE_OUT;
	canPort.PORT_SFUNC   = PORT_SFUNC_4;
	canPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    canPort.PORT_SPWR    = PORT_SPWR_300;

    PORT_Init( MDR_PORTA, &canPort );

    // CAN 1
    //                     RX_1         TX_1
    canPort.PORT_Pin     = PORT_Pin_2 | PORT_Pin_3;
    PORT_Init( MDR_PORTB, &canPort );

    CAN_BRGInit( MDR_CAN0, SystemCoreClock/speed );
    CAN_BRGInit( MDR_CAN1, SystemCoreClock/speed );

    /* CAN register init */
    CAN_DeInit( MDR_CAN0 );
    CAN_DeInit( MDR_CAN1 );

    /* CAN cell init */
    CAN_StructInit (&sCAN);

    sCAN.CAN_ROP  = ENABLE;
    sCAN.CAN_SAP  = ENABLE;
    sCAN.CAN_STM  = DISABLE;
    sCAN.CAN_ROM  = DISABLE;
    sCAN.CAN_PSEG = CAN_PSEG_Mul_2TQ;
    sCAN.CAN_SEG1 = CAN_SEG1_Mul_5TQ;
    sCAN.CAN_SEG2 = CAN_SEG2_Mul_5TQ;
    sCAN.CAN_SJW  = CAN_SJW_Mul_4TQ;
    sCAN.CAN_SB   = CAN_SB_3_SAMPLE;
    sCAN.CAN_BRP  = 4;

    CAN_Init( MDR_CAN0, &sCAN );
    CAN_Init( MDR_CAN1, &sCAN );

    CAN_Cmd( MDR_CAN0, ENABLE );
    CAN_Cmd( MDR_CAN1, ENABLE );

    /* Disable all CAN interrupt */
    CAN_ITConfig( MDR_CAN0, CAN_IT_GLBINTEN | CAN_IT_RXINTEN | CAN_IT_TXINTEN |
                 CAN_IT_ERRINTEN | CAN_IT_ERROVERINTEN, DISABLE);

    CAN_ITConfig( MDR_CAN1, CAN_IT_GLBINTEN | CAN_IT_RXINTEN | CAN_IT_TXINTEN |
                 CAN_IT_ERRINTEN | CAN_IT_ERROVERINTEN, DISABLE);

    /* Enable CAN0 interrupt from receive buffer */
    CAN_RxITConfig( MDR_CAN0 ,(1<<rx_buf), ENABLE);

    /* Enable CAN1 interrupt from transmit buffer */
    CAN_TxITConfig( MDR_CAN1 ,(1<<tx_buf), ENABLE);
}

void DeinitCan( void )
{
    PORT_InitTypeDef canPort;

    CAN_RxITConfig( MDR_CAN0 ,(1<<rx_buf), DISABLE);
    CAN_TxITConfig( MDR_CAN1 ,(1<<tx_buf), DISABLE);
    CAN_Cmd( MDR_CAN0, DISABLE );
    CAN_Cmd( MDR_CAN1, DISABLE );
    CAN_DeInit(MDR_CAN0);
    CAN_DeInit(MDR_CAN1);
    MDR_CLK->CAN0_CLK = 0;
    MDR_CLK->CAN1_CLK = 0;


    //CAN 0
    PORT_StructInit( &canPort );
    canPort.PORT_Pin     = PORT_Pin_8 | PORT_Pin_9;
    canPort.PORT_SOE     = PORT_SOE_OUT;
    canPort.PORT_SFUNC   = PORT_SFUNC_PORT;
    canPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    canPort.PORT_SPWR    = PORT_SPWR_300;

    PORT_Init( MDR_PORTA, &canPort );

    // CAN 1
    canPort.PORT_Pin = PORT_Pin_2 | PORT_Pin_3;
    PORT_Init( MDR_PORTB, &canPort );
}

uint32_t CanTest( uint32_t TData0, uint32_t TData1,
                 uint32_t * RData0, uint32_t * RData1  )
{
    CAN_TxMsgTypeDef TxMsg;
    CAN_RxMsgTypeDef RxMsg = { 0 };
		uint16_t j = 0;

    /* receive buffer enable */
    CAN_Receive( MDR_CAN0, rx_buf, DISABLE ) ;

    /* transmit */
    TxMsg.IDE     = CAN_ID_EXT;
    TxMsg.DLC     = 0x08;
    TxMsg.PRIOR_0 = DISABLE;
    TxMsg.ID      = 0x12345678;
    TxMsg.Data[1] = TData1;//0x01234567;
    TxMsg.Data[0] = TData0;//0x89ABCDEF;

    CAN_Transmit( MDR_CAN1, tx_buf, &TxMsg );

    i = 0;
    while(((CAN_GetStatus(MDR_CAN1) & CAN_STATUS_TX_READY) == RESET) && (i != 0xFFFF))
    {
        i++;
    }
    CAN_ITClearRxTxPendingBit(MDR_CAN1, tx_buf, CAN_STATUS_TX_READY);

    while(((CAN_GetStatus(MDR_CAN0) & CAN_STATUS_RX_READY) == RESET) && (j != 0xFFFF))
    {
        j++;
    }
    j += i;

    /* receive */
    if( i > 0xFF00 || j > 0xFF00 )
    {
        *RData0 = 0;
        *RData1 = 0;
    }
    else
    {
        CAN_GetRawReceivedData(MDR_CAN0, rx_buf, &RxMsg);

        CAN_ITClearRxTxPendingBit(MDR_CAN0, rx_buf, CAN_STATUS_RX_READY);

        *RData0 = RxMsg.Data[0];
        *RData1 = RxMsg.Data[1];
    }

    CAN_Cmd(MDR_CAN0, DISABLE);
    return (i << 16) | j;
}

/** @} */ /* End of group BSP_CAN_Exported_Functions */

/** @} */ /* End of group BSP_CAN */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE can.c */


