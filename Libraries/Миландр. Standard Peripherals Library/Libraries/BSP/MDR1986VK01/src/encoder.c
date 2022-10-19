/**
  ******************************************************************************
  * @file    encoder.c
  * @author  Milandr Application Team
  * @version V1.2.0
  * @date    06/09/2021
  * @brief   Encoder source file for demo board.
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
  * FILE encoder.c
  */

/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_ENC BSP_ENC
  * @{
  */

/** @defgroup BSP_ENC_Private_Variables BSP_ENC Private Variables
  * @{
  */

uint8_t ucEncWasPressed = 0;

/** @} */ /* End of group BSP_ENC_Private_Variables */

/** @defgroup BSP_ENC_Exported_Functions BSP_ENC Exported Functions
  * @{
  */

/** Encoder pins initialization */
void EncInit( void )
{
    PORT_InitTypeDef encPort;

    PORT_StructInit( &encPort );

    ENC_PORT->KEY = 0x8555AAA1;

    encPort.PORT_SOE     = PORT_SOE_IN;
    encPort.PORT_SFUNC   = PORT_SFUNC_15;
    encPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    encPort.PORT_SPWR    = PORT_SPWR_10;
    //encPort.PORT_SIE     = PORT_SIE_ON;

    encPort.PORT_Pin     = ENC_PIN_A | ENC_PIN_B;
    PORT_Init( ENC_PORT, &encPort );

    encPort.PORT_Pin     = ENC_PIN_SW;
    encPort.PORT_SFUNC   = PORT_SFUNC_PORT;
    PORT_Init( ENC_PORT, &encPort );

    MDR_CLK->QEP1_CLK = CLK_ENABLE;

    MDR_QEP1->QDECCTL = 0x00000800;

    MDR_QEP1->QEPCTL  = 0x0000F028;//0x0000F208;
    MDR_QEP1->QPOSCTL = 0x00000004;//0x00001004;
    MDR_QEP1->QCAPCTL = 0x00000800;
    MDR_QEP1->QEINT   = 0x00000400;

    MDR_QEP1->QPOSMAX = 0xFFFFFFFF;
    MDR_QEP1->QPOSCNT = 0x00000000;
    MDR_QEP1->QCLR   |= 0x00000400;

    NVIC_EnableIRQ( QEP1_IRQn );
    ucEncWasPressed = 0;
    //NVIC_EnableIRQ( IRQ_PORTC_IRQn );
}

int32_t getEncCount()
{
    return MDR_QEP1->QPOSCNT;
}

void QEP1_IRQHandler( void )
{
    //ucEncWasPressed = 1;
    MDR_QEP1->QCLR |= 0x00000400;
}

/** @} */ /* End of group BSP_ENC_Exported_Functions */

/** @} */ /* End of group BSP_ENC */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE encoder.c */



