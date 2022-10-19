/**
  ******************************************************************************
  * @file    milstd.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   MILSTD source file for demo board.
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
  * FILE milstd.c
  */

/* Includes ------------------------------------------------------------------*/
#include "milstd.h"

#include "MDR1986VK01_port.h"
#include "MDR1986VK01_milstd.h"
#include "MDR1986VK01_clk.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_MILSTD BSP_MILSTD
  * @{
  */

/** @defgroup BSP_MILSTD_Private_Variables BSP_MILSTD Private Variables
  * @{
  */

static MIL_STD_1553_CommandWordTypeDef CommandWord = {0};
static uint32_t i;
static uint32_t TestData[32];

/** @} */ /* End of group BSP_MILSTD_Private_Variables */

/** @defgroup BSP_MILSTD_Exported_Functions BSP_MILSTD Exported Functions
  * @{
  */

void InitMilStd( uint32_t speed )
{
    PORT_InitTypeDef milstdPort;
    MIL_STD_1553_InitTypeDef MIL_STD_1553InitStructure;

    PORT_StructInit( &milstdPort );

    //MILSTD0
    milstdPort.PORT_Pin     = PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10 | PORT_Pin_11 |
                              PORT_Pin_12 | PORT_Pin_13 | PORT_Pin_14 | PORT_Pin_15 | PORT_Pin_16;
    milstdPort.PORT_SOE     = PORT_SOE_OUT;
    milstdPort.PORT_SFUNC   = PORT_SFUNC_7;
    milstdPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    milstdPort.PORT_SPWR    = PORT_SPWR_300;

    MDR_PORTA->KEY = 0x8555AAA1;
    PORT_Init( MDR_PORTA, &milstdPort );

    //MILSTD1
    milstdPort.PORT_Pin     = PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 |
                              PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9;
    milstdPort.PORT_SOE     = PORT_SOE_OUT;
    milstdPort.PORT_SFUNC   = PORT_SFUNC_7;
    milstdPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    milstdPort.PORT_SPWR    = PORT_SPWR_300;
    MDR_PORTC->KEY = 0x8555AAA1;
    PORT_Init( MDR_PORTC, &milstdPort );

    MIL_STD_1553_CLK_en( 0 );

    MIL_STD_1553_DeInit( MDR_MIL0_STD_1553 );
    MIL_STD_1553_DeInit( MDR_MIL1_STD_1553 );

    MIL_STD_1553xStructInit(&MIL_STD_1553InitStructure);

    /* Terminal */
    /* Initialize MIL_STD_1553_InitStructure */
    MIL_STD_1553InitStructure.MIL_STD_1553_Mode = MIL_STD_1553_ModeTerminal;
    MIL_STD_1553InitStructure.MIL_STD_1553_RERR = ENABLE;
    MIL_STD_1553InitStructure.MIL_STD_1553_DIV = 80;
    MIL_STD_1553InitStructure.MIL_STD_1553_RTA = 10;
    MIL_STD_1553InitStructure.MIL_STD_1553_TRA = ENABLE;
    MIL_STD_1553InitStructure.MIL_STD_1553_TRB = ENABLE;
    MIL_STD_1553InitStructure.MIL_STD_1553_Inversion_Signals = ENABLE;                  // Для модуля МКИО

	/* Configure MIL_STD_1553 parameters*/
	MIL_STD_1553_Init(MDR_MIL0_STD_1553, &MIL_STD_1553InitStructure);

//	MIL_STD_1553_ITConfig( MDR_MIL0_STD_1553,
//						  (MIL_STD_1553_IT_ERRIE |
//						   MIL_STD_1553_IT_VALMESSIE |
//						   MIL_STD_1553_IT_RFLAGNIE), ENABLE);

//    NVIC_EnableIRQ(MIL0_IRQn);
    MIL_STD_1553_Cmd(MDR_MIL0_STD_1553, ENABLE);

    /* Контроллер шины */
	MIL_STD_1553InitStructure.MIL_STD_1553_Mode = MIL_STD_1553_ModeBusController;
	MIL_STD_1553InitStructure.MIL_STD_1553_RERR = ENABLE;
	MIL_STD_1553InitStructure.MIL_STD_1553_DIV = 80;//SystemCoreClock/speed;//80;
	MIL_STD_1553InitStructure.MIL_STD_1553_RTA = 0;
	MIL_STD_1553InitStructure.MIL_STD_1553_TRA = ENABLE;
	MIL_STD_1553InitStructure.MIL_STD_1553_TRB = DISABLE;
    MIL_STD_1553InitStructure.MIL_STD_1553_Inversion_Signals = ENABLE;                  // Для модуля МКИО

    /* Configure MIL_STD_1553 parameters*/
	MIL_STD_1553_Init(MDR_MIL1_STD_1553, &MIL_STD_1553InitStructure);
    MIL_STD_1553_Cmd(MDR_MIL1_STD_1553, ENABLE);
}

uint8_t MilStdTest( void )
{
    CommandWord.Fields.ReadWriteBit = MIL_STD_1553_BC_TO_TD;
    CommandWord.Fields.Data = 31;
    CommandWord.Fields.Subaddress = 1;
    /* Fill the data */
    for(i = 0; i < 31; i++)
        TestData[i] = i;
    /* Write data to transmiter buffer */
    MIL_STD_1553_WiteDataToSendBuffer(MDR_MIL1_STD_1553, 1, 31, &TestData[0]);

    CommandWord.Fields.TerminalDeviceAddress = 10;
    /* Set Command Word */
    MIL_STD_1553_SetCommandWord(MDR_MIL1_STD_1553, MIL_STD_1553_COMMAND_WORD1, &CommandWord);
    /* Start transmision */
    MIL_STD_1553_StartTransmision(MDR_MIL1_STD_1553);
    /* Enable interrups */
    MIL_STD_1553_ITConfig( MDR_MIL1_STD_1553, (MIL_STD_1553_IT_ERRIE |
                                           MIL_STD_1553_IT_VALMESSIE), ENABLE);

    while(MIL_STD_1553_GetFlagStatus(MDR_MIL1_STD_1553, MIL_STD_1553_FLAG_IDLE) != SET);

//    while(MIL_STD_1553_GetFlagStatus(MIL0_STD_1553, MIL_STD_1553_FLAG_RCVA) != SET);

    for(i = 0; i < 31; i++)
        TestData[i] = 0;

    if( MDR_MIL0_STD_1553->STATUS & 0x200 )
    {
        MDR_MIL0_STD_1553->STATUS &= ~0x200;
        MIL_STD_1553_ReceiveData( MDR_MIL0_STD_1553, 1, 31, &TestData[0] );
    }
    else
        return 0;

    for(i = 0; i < 31; i++)
    {
        if( TestData[i] != i )
            return 0;
    }

    return 1;
}

void MIL0_IRQHandler( void )
{

}

/** @} */ /* End of group BSP_MILSTD_Exported_Functions */

/** @} */ /* End of group BSP_MILSTD */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE milstd.c */



