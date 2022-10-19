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

/** @addtogroup EEPROM_Sector_Operations_MDR32F9Q2I EEPROM_Sector_Operations
  * @{
  */

/* Private define ------------------------------------------------------------*/
#define EEPROM_PAGE_SIZE             (4*1024)
#define MAIN_EEPAGE                  5
#define LED_MASK                     (PORT_Pin_0 | PORT_Pin_1)
#define LED0_MASK                    PORT_Pin_0

/* Private macro -------------------------------------------------------------*/
#define LED_TST_NUM(num)             ((LED0_MASK << ((num) & 1)) & LED_MASK)

/* Private variables ---------------------------------------------------------*/
static PORT_InitTypeDef PORT_InitStructure;

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Pseudo random function
  * @param  addr: 32-bit encoded value
  * @retval 32-bit encoder result
  */
uint32_t Pseudo_Rand(uint32_t addr)
{
    uint32_t hash = 0;
    uint32_t i = 0;
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
  * @brief  Delay function
  * @param  None
  * @retval None
  */
void Delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 100000; i++)
    {
    }
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int32_t main (void)
{
    uint32_t Address = 0;
    uint32_t BankSelector = 0;
    uint32_t Data = 0;
    uint32_t i = 0;
    uint32_t Leds = 0;
    uint8_t EraseErrMM = 0;
    uint8_t WriteErrMM = 0;
    uint8_t EraseErrIM = 0;
    uint8_t WriteErrIM = 0;

    /* Enables the clock on PORTC */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
    /* Enables the clock on EEPROM */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);

    /* Configure PORTC pins 0..1 for output to switch LEDs on/off */
    PORT_InitStructure.PORT_Pin   = LED_MASK;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTC, &PORT_InitStructure);

    /* Erase main memory page MAIN_EEPAGE */
    Address = 0x08000000 + MAIN_EEPAGE * EEPROM_PAGE_SIZE;
    BankSelector = EEPROM_Main_Bank_Select;
    EEPROM_ErasePage (Address, BankSelector);

    /* Check main memory page MAIN_EEPAGE */
    Data = 0xFFFFFFFF;
    for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
    {
        if (EEPROM_ReadWord (Address + i, BankSelector) != Data)
        {
            EraseErrMM = 1;
        }
    }

    /* Indicate status of erasing main memory page MAIN_EEPAGE */
    if (EraseErrMM == 0)
    {
        PORT_Write(MDR_PORTC, LED_TST_NUM(0x0));
    }
    else
    {
        while (1)
        {
            Leds ^= LED_MASK;
            PORT_Write(MDR_PORTC, Leds);
            Delay();
        }
    }

    /* Fill main memory page MAIN_EEPAGE */
    Address = 0x08000000 + MAIN_EEPAGE * EEPROM_PAGE_SIZE;
    BankSelector = EEPROM_Main_Bank_Select;
    for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
    {
        Data = Pseudo_Rand (Address + i);
        EEPROM_ProgramWord (Address + i, BankSelector, Data);
    }

    /* Check main memory page MAIN_EEPAGE */
    Address = 0x08000000 + MAIN_EEPAGE * EEPROM_PAGE_SIZE;
    BankSelector = EEPROM_Main_Bank_Select;
    for (i = 0; i < EEPROM_PAGE_SIZE; i +=4 )
    {
        Data = Pseudo_Rand (Address + i);
        if (EEPROM_ReadWord (Address + i, BankSelector) != Data)
        {
            WriteErrMM = 1;
        }
    }

    /* Indicate status of writing main memory page MAIN_EEPAGE */
    if (WriteErrMM == 0)
    {
        PORT_Write(MDR_PORTC, LED_TST_NUM(0x1));
    }
    else
    {
        while (1)
        {
            Leds ^= LED_MASK;
            PORT_Write(MDR_PORTC, Leds);
            Delay();
        }
    }

    /* Erase main memory page MAIN_EEPAGE */
    Address = 0x08000000 + MAIN_EEPAGE * EEPROM_PAGE_SIZE;
    BankSelector = EEPROM_Main_Bank_Select;
    EEPROM_ErasePage (Address, BankSelector);

    /* Check main memory page MAIN_EEPAGE */
    Data = 0xFFFFFFFF;
    for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
    {
        if (EEPROM_ReadWord (Address + i, BankSelector) != Data)
        {
            EraseErrMM = 1;
        }
    }

    /* Indicate status of erasing main memory page MAIN_EEPAGE */
    if (EraseErrMM == 0)
    {
        PORT_Write(MDR_PORTC, LED_TST_NUM(0x2));
    }
    else
    {
        while (1)
        {
            Leds ^= LED_MASK;
            PORT_Write(MDR_PORTC, Leds);
            Delay();
        }
    }

    /* Full Erase information memory */
    Address = 0x08000000;
    BankSelector = EEPROM_Info_Bank_Select;
    EEPROM_ErasePage (Address, BankSelector);

    /* Check information memory */
    Data = 0xFFFFFFFF;
    for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
    {
        if (EEPROM_ReadWord (Address + i, BankSelector) != Data)
        {
            EraseErrIM = 1;
        }
    }

    /* Indicate status of erasing information memory */
    if (EraseErrIM == 0)
    {
        PORT_Write(MDR_PORTC, LED_TST_NUM(0x3));
    }
    else
    {
        while (1)
        {
            Leds ^= LED_MASK;
            PORT_Write(MDR_PORTC, Leds);
            Delay();
        }
    }

    /* fill information memory */
    Address = 0x08000000;
    BankSelector = EEPROM_Info_Bank_Select;
    for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
    {
        Data = Pseudo_Rand (Address + i);
        EEPROM_ProgramWord (Address + i, BankSelector, Data);
    }

    /* Check information memory */
    Address = 0x08000000;
    BankSelector = EEPROM_Info_Bank_Select;
    for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
    {
        Data = Pseudo_Rand (Address + i);
        if (EEPROM_ReadWord (Address + i, BankSelector) != Data)
        {
            WriteErrIM = 1;
        }
    }

    /* Indicate status of writing information memory */
    if (WriteErrIM == 0)
    {
        PORT_Write(MDR_PORTC, LED_TST_NUM(0x4));
    }
    else
    {
        while (1)
        {
            Leds ^= LED_MASK;
            PORT_Write(MDR_PORTC, Leds);
            Delay();
        }
    }

    /* Full Erase information memory */
    Address = 0x08000000;
    BankSelector = EEPROM_Info_Bank_Select;
    EEPROM_ErasePage (Address, BankSelector);

    /* Check information memory */
    Data = 0xFFFFFFFF;
    for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
    {
        if (EEPROM_ReadWord (Address + i, BankSelector) != Data)
        {
            EraseErrIM = 1;
        }
    }

    if (WriteErrIM == 0)
    {
        PORT_Write(MDR_PORTC, LED_TST_NUM(0x5));
        Delay();
    }
    else
    {
        while (1)
        {
            Leds ^= LED_MASK;
            PORT_Write(MDR_PORTC, Leds);
            Delay();
        }
    }

    PORT_Write(MDR_PORTC, LED_MASK);
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

/** @} */ /* End of group EEPROM_Sector_Operations_MDR32F9Q2I */

/** @} */ /* End of group __MDR32F9Q2I_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE main.c */



