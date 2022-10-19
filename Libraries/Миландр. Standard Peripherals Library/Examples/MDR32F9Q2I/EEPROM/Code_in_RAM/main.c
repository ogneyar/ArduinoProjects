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
#include "MDR32FxQI_eeprom.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F9Q2I_EVAL MDR32F9Q2I Evaluation Board
  * @{
  */

/** @addtogroup EEPROM_Code_in_RAM_MDR32F9Q2I EEPROM_Code_in_RAM
  * @{
  */

/* Private variables ---------------------------------------------------------*/
static PORT_InitTypeDef PORT_InitStructure;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Pseudo random function.
  * @param  addr: 32-bit encoded value.
  * @retval 32-bit encoder result.
  */
uint32_t Pseudo_Rand(uint32_t addr)
{
    uint32_t hash = 0;
    uint32_t i;
    uint8_t* key = (uint8_t *)&addr;

    for (i = 0; i < 4; i++)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    for (i = 0; i < 256; i++)
    {
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t Address;
    uint32_t BankSelector;
    uint32_t Data;
    int i;
    uint8_t EraseErrMM=0;
    uint8_t WriteErrMM=0;
    uint8_t EraseErrIM=0;
    uint8_t WriteErrIM=0;

    /* Enables the clock on PORTC */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);

    /* Enables the  clock on EEPROM */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);

    /* Configure PORTC pin 0,1 for output to switch LEDs on/off */
    PORT_InitStructure.PORT_Pin   = PORT_Pin_0 | PORT_Pin_1;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTC, &PORT_InitStructure);

    /* Erase main memory page 0 */
    Address = 0x08000000;
    BankSelector = 0;
    EEPROM_ErasePage (Address,BankSelector);

    /* Check main memory page 0 */
    Data = 0xFFFFFFFF;
    for (i=0;i<1024;i++)
    {
        if(EEPROM_ReadWord (Address+i*4,BankSelector) != Data)
        {
            EraseErrMM = 1;
        }
    }

    /* Indicate status of erasing main memory page 0*/
    if (EraseErrMM == 0)
    {
        PORT_SetBits(MDR_PORTC, PORT_Pin_0);
    }

    /* Fill main memory page 0 */
    Address = 0x08000000;
    BankSelector = 0;
    for (i=0;i<1024;i++)
    {
        Data = Pseudo_Rand (Address+i*4);
        EEPROM_ProgramWord (Address+i*4,BankSelector,Data);
    }

    /* Check main memory page 0 */
    Address = 0x08000000;
    BankSelector = 0;
    for (i=0;i<1024;i++)
    {
        Data = Pseudo_Rand (Address+i*4);
        if (EEPROM_ReadWord (Address+i*4,BankSelector) != Data)
        {
            WriteErrMM = 1;
        }
    }

    /* Indicate status of writing main memory page 0*/
    if (WriteErrMM == 0)
    {
        PORT_SetBits(MDR_PORTC, PORT_Pin_1);
    }
    PORT_ResetBits(MDR_PORTC, PORT_Pin_0);

    /* Full Erase information memory */
    Address = 0x08000000;
    BankSelector = 1;
    EEPROM_EraseAllPages (BankSelector);

    /* Check information memory */
    Data = 0xFFFFFFFF;
    for (i=0;i<1024;i++)
    {
        if (EEPROM_ReadWord (Address+i*4,BankSelector) != Data)
        {
            EraseErrIM = 1;
        }
    }

    /* Indicate status of erasing information memory */
    if (EraseErrIM == 0)
    {
        PORT_SetBits(MDR_PORTC, PORT_Pin_0);
    }
    PORT_ResetBits(MDR_PORTC, PORT_Pin_1);

    /* fill information memory */
    Address = 0x08000000;
    BankSelector = 1;
    for (i=0;i<1024;i++)
    {
        Data = Pseudo_Rand (Address+i*4);
        EEPROM_ProgramWord (Address+i*4,BankSelector,Data);
    }

    /* Check information memory */
    Address = 0x08000000;
    BankSelector = 1;
    for (i=0;i<1024;i++)
    {
        Data = Pseudo_Rand (Address+i*4);
        if (EEPROM_ReadWord (Address+i*4,BankSelector) != Data)
        {
            WriteErrIM = 1;
        }
    }

    /* Indicate status of writing information memory */
    if (WriteErrIM == 0)
    {
        PORT_SetBits(MDR_PORTC, PORT_Pin_1);
    }
    PORT_ResetBits(MDR_PORTC, PORT_Pin_0);

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

/** @} */ /* End of group EEPROM_Code_in_RAM_MDR32F9Q2I */

/** @} */ /* End of group __MDR32F9Q2I_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE main.c */


