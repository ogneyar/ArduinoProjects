/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    22/09/2021
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
#include "MDR32FxQI_config.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2I_EVAL MDR32F9Q2I Evaluation Board
  * @{
  */

/** @addtogroup PORT_Joystick_LEDs_MDR32F9Q2I PORT_Joystick_LEDs
  * @{
  */

/* Private define ------------------------------------------------------------*/
#define ALL_PORTS_CLK (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | \
                       RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD | \
                       RST_CLK_PCLK_PORTE | RST_CLK_PCLK_PORTF)

/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;

/* Private functions ---------------------------------------------------------*/

void Init_All_Ports(void)
{
    /* Enable the RTCHSE clock on all ports */
    RST_CLK_PCLKcmd(ALL_PORTS_CLK, ENABLE);

    /* Configure all ports to the state as after reset, i.e. low power consumption */
    PORT_StructInit(&PORT_InitStructure);
    PORT_Init(MDR_PORTA, &PORT_InitStructure);
    PORT_Init(MDR_PORTB, &PORT_InitStructure);
    PORT_Init(MDR_PORTC, &PORT_InitStructure);
    PORT_Init(MDR_PORTD, &PORT_InitStructure);
    PORT_Init(MDR_PORTE, &PORT_InitStructure);
    PORT_Init(MDR_PORTF, &PORT_InitStructure);

    /* Disable the RTCHSE clock on all ports */
    RST_CLK_PCLKcmd(ALL_PORTS_CLK, DISABLE);
}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /*!< Usually, reset is done before the program is to be loaded into microcontroller,
         and there is no need to perform any special operations to switch the ports
         to low power consumption mode explicitly. So, the function Init_All_Ports
         is used here for demonstration purpose only.
    */
    Init_All_Ports();

    /* Enables the RTCHSE clock on PORTB, PORTC and PORTE */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTE, ENABLE);

    /* Configure PORTC pins 0,1 for output to switch LEDs on/off */

    PORT_InitStructure.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_1);
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTC, &PORT_InitStructure);

    /* Configure PORTB pin 6 for input to handle joystick events */

    PORT_InitStructure.PORT_Pin   = (PORT_Pin_6);
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTB, &PORT_InitStructure);

    /* Configure PORTE pin 3 for input to handle joystick events */

    PORT_InitStructure.PORT_Pin   = (PORT_Pin_3);
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTE, &PORT_InitStructure);


    /* In this infinite loop, PORTE pin3 and PORTB pin6 (joystick) are iteratively scanned and
       PORTC output pins (LED indicators) are appropriately set/cleared.
       Note: in this example, the following fact about MDR32F9Q2 eval board is used: the
       joystic input pin numbers exactly match LED output pins, i.e:
           LEFT   => VD4
           RIGHT  => VD3
    */
    while(1)
    {
        if (PORT_ReadInputDataBit(MDR_PORTB, PORT_Pin_6) == RESET)
        {
            PORT_SetBits(MDR_PORTC, PORT_Pin_0);
        }
        else
        {
            PORT_ResetBits(MDR_PORTC, PORT_Pin_0);
        }
    
        if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_3) == RESET)
        {
            PORT_SetBits(MDR_PORTC, PORT_Pin_1);
        }
        else
        {
            PORT_ResetBits(MDR_PORTC, PORT_Pin_1);
        }
    }
}

/**
  * @brief  Reports the source file name, the source line number
  *         and expression text (if USE_ASSERT_INFO == 2) where
  *         the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @param  expr:
  * @retval None
  */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the source file name and line number.
       Ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    /* User can add his own implementation to report the source file name, line number and
       expression text.
       Ex: printf("Wrong parameters value (%s): file %s on line %d\r\n", expr, file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group PORT_Joystick_LEDs_MDR32F9Q2I */

/** @} */ /* End of group __MDR32F9Q2I_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE main.c */


