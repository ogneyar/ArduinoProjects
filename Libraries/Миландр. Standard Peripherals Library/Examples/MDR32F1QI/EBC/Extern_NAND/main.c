/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    21/09/2021
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
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_ebc.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup EXT_BUS_Extern_NAND_MDR32F1QI EXT_BUS_Extern_NAND
  * @{
  */


/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
EBC_InitTypeDef EBC_InitStruct;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Enables the HSI clock for EBC control */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_EBC,ENABLE);

    /* Initializes EBC_InitStruct by default values */
    EBC_StructInit(&EBC_InitStruct);

    /* Specifies external bus mode NAND */
    EBC_InitStruct.EBC_Mode = EBC_MODE_NAND;

    /* Calculates the t_rc number for 8 MHz frequency and time interval = 500 ns */
    EBC_InitStruct.EBC_NandTrc   = EBC_CalcNandCycles(8000,500);

    /* Calculates the t_wc number for 8 MHz frequency and time interval = 250 ns */
    EBC_InitStruct.EBC_NandTwc   = EBC_CalcNandCycles(8000,250);

    /* Calculates the t_rea number for 8 MHz frequency and time interval = 500 ns */
    EBC_InitStruct.EBC_NandTrea  = EBC_CalcNandCycles(8000,500);

    /* Calculates the t_wp number for 8 MHz frequency and time interval = 250 ns */
    EBC_InitStruct.EBC_NandTwp   = EBC_CalcNandCycles(8000,250);

    /* Calculates the t_whr number for 8 MHz frequency and time interval = 1200 ns */
    EBC_InitStruct.EBC_NandTwhr  = EBC_CalcNandCycles(8000,1200);

    /* Calculates the t_alea number for 8 MHz frequency and time interval = 800 ns */
    EBC_InitStruct.EBC_NandTalea = EBC_CalcNandCycles(8000,800);

    /* Calculates the t_rr number for 8 MHz frequency and time interval = 750 ns */
    EBC_InitStruct.EBC_NandTrr   = EBC_CalcNandCycles(8000,750);

    /* Initializes the EBC peripheral registers */
    EBC_Init(&EBC_InitStruct);

    /* Infinite loop */
    while (1)
    {
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

/** @} */ /* End of group EXT_BUS_Extern_NAND_MDR32F1QI */

/** @} */ /* End of group __MDR32F1QI */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE main.c */



