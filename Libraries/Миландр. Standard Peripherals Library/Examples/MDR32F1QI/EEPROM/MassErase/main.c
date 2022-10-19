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
#include "MDR32FxQI_config.h"
#include "MDR32FxQI_eeprom.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
 * @{
 */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
 * @{
 */

/** @addtogroup EEPROM_Mass_Erase EEPROM_Mass_Erase
 * @{
 */

/* Private define ------------------------------------------------------------*/
#define EEPROM_MAIN_BANK_SIZE       (1024)
#define EEPROM_INFO_BANK_SIZE       (1024)

#define LED_MASK                    (PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10)
#define LED0_MASK                   PORT_Pin_7

#define RESULT_OK                   0
#define RESULT_ERR                  1

/* Private macro -------------------------------------------------------------*/
#define LED_TST_NUM(num)            (((num) * LED0_MASK) & LED_MASK)

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
    uint8_t* key = (uint8_t *) &addr;

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
  * @brief  Check main block is empty
  * @param  None
  * @retval Result: RESULT_OK or RESULT_ERR
  */
uint32_t BlankCheckMainMemory(void)
{
    uint32_t Address = 0;
    uint32_t BankSelector = 0;
    uint32_t Data = 0;
    uint32_t i = 0;
    uint32_t Errs = RESULT_OK;

    /* Check main memory bank */
    Address = 0x00010000;
    BankSelector = EEPROM_Main_Bank_Select;
    Data = 0xFFFFFFFF;
    for (i = 0; i < EEPROM_MAIN_BANK_SIZE; i += 4)
    {
        if (EEPROM_ReadWord(Address + i, BankSelector) != Data)
        {
            Errs = RESULT_ERR;
        }
    }
    return Errs;
}

/**
  * @brief  Check info block is empty
  * @param  None
  * @retval Result: RESULT_OK or RESULT_ERR
  */
uint32_t BlankCheckInfoMemory(void)
{
    uint32_t Address = 0;
    uint32_t BankSelector = 0;
    uint32_t Data = 0;
    uint32_t i = 0;
    uint32_t Errs = RESULT_OK;

    /* Check information memory bank */
    Address = 0x00000000;
    BankSelector = EEPROM_Info_Bank_Select;
    Data = 0xFFFFFFFF;
    for (i = 0; i < EEPROM_INFO_BANK_SIZE; i += 4)
    {
        if (EEPROM_ReadWord(Address + i, BankSelector) != Data)
        {
            Errs = RESULT_ERR;
        }
    }
    return Errs;
}

/**
  * @brief  Fill main memory bank with pseudo-random values
  * @param  None
  * @retval None
  */
void FillMainMemory(void)
{
    uint32_t Address = 0;
    uint32_t BankSelector = 0;
    uint32_t Data = 0;
    uint32_t i = 0;

    /* Fill main memory bank */
    Address = 0x00010000;
    BankSelector = EEPROM_Main_Bank_Select;
    for (i = 0; i < EEPROM_MAIN_BANK_SIZE; i += 11 * 4)
    {
        Data = Pseudo_Rand(Address + i);
        EEPROM_ProgramWord(Address + i, BankSelector, Data);
    }
}

/**
  * @brief  Verify main memory bank
  * @param  None
  * @retval Result: RESULT_OK or RESULT_ERR
  */
uint32_t VerifyMainMemory(void)
{
    uint32_t Address = 0;
    uint32_t BankSelector = 0;
    uint32_t Data = 0;
    uint32_t i = 0;
    uint32_t Errs = RESULT_OK;

    /* Check main memory bank */
    Address = 0x00010000;
    BankSelector = EEPROM_Main_Bank_Select;
    for (i = 0; i < EEPROM_MAIN_BANK_SIZE; i += 11 * 4)
    {
        Data = Pseudo_Rand(Address + i);
        if (EEPROM_ReadWord(Address + i, BankSelector) != Data)
        {
            Errs = RESULT_ERR;
        }
    }
    return Errs;
}

/**
  * @brief  Fill info memory bank with pseudo-random values
  * @param  None
  * @retval None
  */
void FillInfoMemory(void)
{
    uint32_t Address = 0;
    uint32_t BankSelector = 0;
    uint32_t Data = 0;
    uint32_t i = 0;

    /* Fill information memory bank */
    Address = 0x00000000;
    BankSelector = EEPROM_Info_Bank_Select;
    for (i = 0; i < EEPROM_INFO_BANK_SIZE; i += 4)
    {
        Data = Pseudo_Rand(Address + i + 1);
        EEPROM_ProgramWord(Address + i, BankSelector, Data);
    }
}

/**
  * @brief  Verify info memory bank
  * @param  None
  * @retval Result: RESULT_OK or RESULT_ERR
  */
uint32_t VerifyInfoMemory(void)
{
    uint32_t Address = 0;
    uint32_t BankSelector = 0;
    uint32_t Data = 0;
    uint32_t i = 0;
    uint32_t Errs = RESULT_OK;

    /* Check information memory bank */
    Address = 0x00000000;
    BankSelector = EEPROM_Info_Bank_Select;
    for (i = 0; i < EEPROM_INFO_BANK_SIZE; i += 4)
    {
        Data = Pseudo_Rand(Address + i + 1);
        if (EEPROM_ReadWord(Address + i, BankSelector) != Data)
        {
            Errs = RESULT_ERR;
        }
    }
    return Errs;
}

/**
  * @brief  Indicates status of selected test
  * @param  TestStatus - test result
  * @param  TestNum - test number
  * @retval None
  */
void ShowTestStatus(uint32_t TestStatus, uint32_t TestNum)
{
    uint32_t Leds = LED_TST_NUM(TestNum);
    if (TestStatus == RESULT_OK)
    {
        PORT_Write(MDR_PORTD, Leds);
        Delay();
    }
    else {
        while (1)
        {
            Leds ^= LED_TST_NUM(TestNum);
            PORT_Write(MDR_PORTD, Leds);
            Delay();
        }
    }
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t address = 0x00010000;

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

    /* Erase main and information memory banks */
    EEPROM_ErasePage(address, EEPROM_Main_Bank_Select );
    EEPROM_ErasePage(0x00000000, EEPROM_Info_Bank_Select);

    /* Indicate status of erasing main memory bank */
    ShowTestStatus(BlankCheckMainMemory(), 0x1);

    /* Indicate status of erasing information memory bank */
    ShowTestStatus(BlankCheckInfoMemory(), 0x2);

    /* Fill main memory bank */
    FillMainMemory();

    /* Verify main memory bank */
    ShowTestStatus(VerifyMainMemory(), 0x3);

    /* Fill information memory bank */
    FillInfoMemory();

    /* Verify information memory bank */
    ShowTestStatus(VerifyInfoMemory(), 0x4);

    /* Erase main memory bank only */
    EEPROM_ErasePage(address, EEPROM_Main_Bank_Select );

    /* Indicate status of erasing main memory bank */
    ShowTestStatus(BlankCheckMainMemory(), 0x5);

    /* Verify information memory bank */
    ShowTestStatus(VerifyInfoMemory(), 0x6);

    /* Fill main memory bank */
    FillMainMemory();

    /* Verify main memory bank */
    ShowTestStatus(VerifyMainMemory(), 0x7);

    /* Erase main and information memory banks */
    EEPROM_ErasePage(address, EEPROM_Main_Bank_Select );
    EEPROM_ErasePage(0x00000000, EEPROM_Info_Bank_Select);


    /* Indicate status of erasing main memory bank */
    ShowTestStatus(BlankCheckMainMemory(), 0x8);

    /* Indicate status of erasing information memory bank */
    ShowTestStatus(BlankCheckInfoMemory(), 0x9);

    while(1);
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

/** @} *//* End of group EEPROM_Mass_Erase */

/** @} *//* End of group __MDR32F1QI */

/** @} *//* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
 *
 * END OF FILE main.c */


