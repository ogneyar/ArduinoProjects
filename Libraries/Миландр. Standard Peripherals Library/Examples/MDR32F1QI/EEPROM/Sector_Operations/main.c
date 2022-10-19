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
#include "MDR32FxQI_eeprom.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup EEPROM_Sector_Operations EEPROM_Sector_Operations
  * @{
  */

/* Private define ------------------------------------------------------------*/
#define EEPROM_PAGE_SIZE             (4*1024)
#define MAIN_EEPAGE                  5
#define LED_MASK                     (PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9)
#define LED0_MASK                    PORT_Pin_7

/* Private macro -------------------------------------------------------------*/
#define LED_TST_NUM(num)             (((num) * LED0_MASK) & LED_MASK)

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
int main(void)
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

    /* Enables the clock on PORTD */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);
    /* Enables the clock on EEPROM */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);

    /* Configure PORTD pins 10..14 for output to switch LEDs on/off */
    PORT_InitStructure.PORT_Pin   = LED_MASK;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    /* Erase main memory page MAIN_EEPAGE */
    Address = 0x00010000 + MAIN_EEPAGE * EEPROM_PAGE_SIZE;
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
    Leds = LED_TST_NUM(0x1);
    if (EraseErrMM == 0)
    {
        PORT_Write(MDR_PORTD, Leds);
    }
    else
    {
        while (1)
        {
            Leds ^= LED_TST_NUM(0x1);
            PORT_Write(MDR_PORTD, Leds);
            Delay();
        }
    }

    /* Fill main memory page MAIN_EEPAGE */
    Address = 0x00010000 + MAIN_EEPAGE * EEPROM_PAGE_SIZE;
    BankSelector = EEPROM_Main_Bank_Select;
    for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
    {
        Data = Pseudo_Rand (Address + i);
        EEPROM_ProgramWord (Address + i, BankSelector, Data);
    }

    /* Check main memory page MAIN_EEPAGE */
    Address = 0x00010000 + MAIN_EEPAGE * EEPROM_PAGE_SIZE;
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
    Leds = LED_TST_NUM(0x2);
    if (EraseErrMM == 0)
    {
        PORT_Write(MDR_PORTD, Leds);
    }
    else
    {
        while (1)
        {
            Leds ^= LED_TST_NUM(0x2);
            PORT_Write(MDR_PORTD, Leds);
            Delay();
        }
    }

    /* Erase main memory page MAIN_EEPAGE */
    Address = 0x00010000 + MAIN_EEPAGE * EEPROM_PAGE_SIZE;
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
    Leds = LED_TST_NUM(0x3);
    if (EraseErrMM == 0)
    {
        PORT_Write(MDR_PORTD, Leds);
    }
    else
    {
        while (1)
        {
            Leds ^= LED_TST_NUM(0x3);
            PORT_Write(MDR_PORTD, Leds);
            Delay();
        }
    }

    /* Full Erase information memory */
    Address = 0x00000000;
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
    Leds = LED_TST_NUM(0x4);
    if (EraseErrMM == 0)
    {
        PORT_Write(MDR_PORTD, Leds);
    }
    else
    {
        while (1)
        {
            Leds ^= LED_TST_NUM(0x4);
            PORT_Write(MDR_PORTD, Leds);
            Delay();
        }
    }

    /* fill information memory */
    Address = 0x00000000;
    BankSelector = EEPROM_Info_Bank_Select;
    for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
    {
        Data = Pseudo_Rand (Address + i);
        EEPROM_ProgramWord (Address + i, BankSelector, Data);
    }

    /* Check information memory */
    Address = 0x00000000;
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
    Leds = LED_TST_NUM(0x5);
    if (EraseErrMM == 0)
    {
        PORT_Write(MDR_PORTD, Leds);
    }
    else
    {
        while (1)
        {
            Leds ^= LED_TST_NUM(0x5);
            PORT_Write(MDR_PORTD, Leds);
            Delay();
        }
    }

    /* Full Erase information memory */
    Address = 0x00000000;
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

    /* Indicate status of writing information memory */
    Leds = LED_TST_NUM(0x6);
    if (EraseErrMM == 0)
    {
        PORT_Write(MDR_PORTD, Leds);
    }
    else
    {
        while (1)
        {
            Leds ^= LED_TST_NUM(0x6);
            PORT_Write(MDR_PORTD, Leds);
            Delay();
        }
    }

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

/** @} */ /* End of group EEPROM_Sector_Operations */

/** @} */ /* End of group __MDR32F1QI */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE main.c */



