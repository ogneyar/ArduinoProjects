/**
  ******************************************************************************
  * @file    eth.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    07/04/2022
  * @brief   ETH source file for demo board.
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
  * FILE eth.c
  */

/* Includes ------------------------------------------------------------------*/
#include "eth.h"
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"
#include "MDR1986VK01_delay.h"
#include "MDR1986VK01.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_ETH BSP_ETH
  * @{
  */

/** @defgroup BSP_ETH_Private_Variables BSP_ETH Private Variables
  * @{
  */

static uint8_t EthReady;
uint32_t ulOurIp;
uint8_t ucSpeed;

/** @} */ /* End of group BSP_ETH_Private_Variables */

/** @defgroup BSP_ETH_Exported_Functions BSP_ETH Exported Functions
  * @{
  */

void InitEth(uint32_t speed)
{
    uint32_t *ethMem = ( uint32_t* )ETH_BUFF_BASE_ADDR;
    uint32_t i, dv;
    PORT_InitTypeDef ethPort;
    ETH_InitTypeDef ethInit;

    MDR_PORTC->KEY = 0x8555AAA1;

    PORT_StructInit( &ethPort );

                        /* TX_EN         TXD_0         TXD_1         RXD_0 */
    ethPort.PORT_Pin     = PORT_Pin_8  | PORT_Pin_24 | PORT_Pin_25 | PORT_Pin_28
                        /* RXD_1         RX_ERR        RX_DV        MDC  */
                         | PORT_Pin_29 | PORT_Pin_14 | PORT_Pin_9 | PORT_Pin_17
                        /* MDIO          RMII_CLK*/
                         | PORT_Pin_16 | PORT_Pin_15;
    ethPort.PORT_SOE     = PORT_SOE_OUT;
    ethPort.PORT_SFUNC   = PORT_SFUNC_8;
    ethPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    ethPort.PORT_SPWR    = PORT_SPWR_10;
    PORT_Init( MDR_PORTC, &ethPort );
                        /* RESET */
    ethPort.PORT_Pin     = PORT_Pin_12;
    ethPort.PORT_SFUNC   = PORT_SFUNC_PORT;
    PORT_Init( MDR_PORTC, &ethPort );

    MDR_PORTC->CRXTX = 1<<12;
    DELAY_ms( 100 );
    MDR_PORTC->SRXTX = 1<<12;

    dv = SystemCoreClock / speed;
    if( dv > 0 )
    {
        dv--;
    }

    ETH_BRGInit(dv);
    ETH_ClockCMD(CLK_SOURCE_MAX_CLK, ENABLE );

    ETH_DeInit();

    for( i = 0; i < 0x8000; i++ )
    {
        *ethMem = 0;
    }

    ETH_StructInit( &ethInit );
    ethInit.ETH_RMII_nMII = SET;
    ethInit.ETH_Transmitter_State = ENABLE;
    ethInit.ETH_Receiver_State = ENABLE;
    ethInit.ETH_Dilimiter = 0x4000;
    ethInit.ETH_Buffer_Mode = ETH_BUFFER_MODE_FIFO;
    ethInit.ETH_DBG_XF = ENABLE;
    ethInit.ETH_DBG_RF = ENABLE;

    ETH_Init( &ethInit );
}

void EthLoop( void )
{
    static uint16_t oldreg, reg;

    reg = ETH_ReadPHYRegister( 0, 1 );

    if( reg & ( 1 << 2 ) )
    {
        reg = ETH_ReadPHYRegister( 0, 31 ) & 0x101C;

        if( oldreg != reg )
        {
            EthReady = 0;

            if( reg & ( 1 << 12 ) )
            {
                EthReady = 1;
                MDR_ETH0->G_CFG &= 0xFFEFFBFF;              // 10M Full
                ucSpeed = 10;
                if( ( reg & 0x1C ) == ( 0x1 << 2 ) )        // 10M Half
                {
                    ucSpeed = 11;
                    MDR_ETH0->G_CFG |= 1 << 10;
                }
                else if( ( reg & 0x1C ) == ( 0x2 << 2 ) )   // 100M Half
                {
                    ucSpeed = 100;
                    MDR_ETH0->G_CFG |= ( 1 << 20 ) | ( 1 << 10 );
                }
                else if( ( reg & 0x1C ) == ( 0x6 << 2 ) )   // 100M Full
                {
                    ucSpeed = 101;
                    MDR_ETH0->G_CFG |= 1 << 20;
                }
            }
            oldreg = reg;
        }
    }
    else
    {
        EthReady = 0;
        ucSpeed = 0;
        ulOurIp = 0;
    }

    if( EthReady )
    {
        ETH_MACITConfig( ETH_MAC_IT_RF_OK, ENABLE );
    }
}

void DeinitEth( void )
{
    PORT_InitTypeDef ethPort;

    MDR_PORTA->KEY = 0x8555AAA1;
    MDR_PORTB->KEY = 0x8555AAA1;

    PORT_StructInit( &ethPort );

    /* RX_DV, MDIO, MDC */
    ethPort.PORT_Pin     = PORT_Pin_9 | PORT_Pin_16 | PORT_Pin_17;
    ethPort.PORT_COE     = PORT_COE_OUT;
	ethPort.PORT_SFUNC   = PORT_SFUNC_PORT;
	ethPort.PORT_CFUNC   = PORT_CFUNC_8;
	ethPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    ethPort.PORT_SPWR    = PORT_SPWR_10;
    PORT_Init( MDR_PORTA, &ethPort );

    ethPort.PORT_Pin     = PORT_Pin_7  | PORT_Pin_8  | PORT_Pin_9  | PORT_Pin_12
                         | PORT_Pin_13 | PORT_Pin_16 | PORT_Pin_17 | PORT_Pin_18;
    PORT_Init( MDR_PORTB, &ethPort );

    ETH_DeInit();
    ETH_ClockDeInit();
}

/** @} */ /* End of group BSP_ETH_Exported_Functions */

/** @} */ /* End of group BSP_ETH */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE eth.с */


