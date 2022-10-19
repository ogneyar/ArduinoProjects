/**
  * FILE MLDR187_eeprom.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_eeprom.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_EEPROM_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup EEPROM
  * @{
  */

/** @defgroup EEPROM_Private_Defines
  * @{
  */

/** @} */ /* End of group EEPROM_Private_Defines */

/** @defgroup EEPROM_Private_Macros EEPROM Private Macros
  * @{
  */

/* assert for flash core speed (for lattency selection) */
#define IS_FLASH_CORE_SPEED(SPEED)	    (((SPEED) == flashCoreSpeedUpTo30MHz) || \
									     ((SPEED) == flashCoreSpeedUpTo60MHz))

/* assert for memory bank selection for write */
#define IS_FLASH_MEMORY_BANK_RW(BANK)   ((BANK) == flashMainBank || (BANK) == flashInfoBank)

/* assert for memory bank selection for erase */
#define IS_FLASH_MEMORY_BANK_ERASE(BANK) ((BANK) == flashMainBank || (BANK) == flashBothBanks)

/* assert for 2 bytes alignment */
#define IS_TWO_BYTE_ALLIGNED(ADDR)      ((ADDR & 1) == 0)

/* assert for 4 bytes alignment */
#define IS_FOUR_BYTE_ALLIGNED(ADDR)     ((ADDR & 3) == 0)

/* number of delays within one loop */
#define DELAY_LOOP_CYCLES               (8UL)

/* calculation of delay loops count */
#define GET_US_LOOPS(N)                 ((uint32_t)((float)(N) * FLASH_PROG_FREQ_MHZ / DELAY_LOOP_CYCLES))

/** @} */ /* End of group EEPROM_Private_Macros */

/** @defgroup EEPROM_Private_Functions_Declarations
  * @{
  */

__RAMFUNC static void ProgramDelay(uint32_t Loops) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/** @} */ /* End of group EEPROM_Private_Functions_Declarations */

/** @defgroup EEPROM_Exported_Functions
  * @{
  */

/**
 *  @brief  maximum core speed to setup flash lattency
 *  @param  coreSpeed - @flashCoreSpeed maximum core speed (less or equal to 30MHz OR more)
 */
void EEPROM_SetLatency (flashCoreSpeed coreSpeed)
{
	uint32_t tempReg;

	/* Check the parameters */
	assert_param(IS_FLASH_CORE_SPEED(coreSpeed));

	/* update flash latency */
	tempReg = MDR_EEPROM->CMD;
	tempReg &= ~EEPROM_CMD_DELAY_Msk;
	/* due to spec it is recommended to setup TMR every time */
	tempReg |= EEPROM_CMD_TMR;
	if (coreSpeed == flashCoreSpeedUpTo30MHz) {
		tempReg |= EEPROM_CMD_DELAY_0_CYCLE;
	} else {
		tempReg |= EEPROM_CMD_DELAY_1_CYCLE;
	}
	MDR_EEPROM->CMD = tempReg;
}

/**
 *  @brief  read out byte from the flash memory
 *  @param  address - address of the byte to be read
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @return byte from the memory within specified address
 */
__RAMFUNC uint8_t EEPROM_ReadByte (uint32_t Address, flashMemBank BankSelector)
{
	uint32_t Data;
	uint32_t Command;
	uint32_t Shift;

	/* test input parameters */
	assert_param(IS_FLASH_MEMORY_BANK_RW(BankSelector));

	/* disable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_UNLOCK_KEY;

	/* read data */
	Command = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON_PROGRAMMING;
	/* due to spec it is recommended to setup TMR every time */
	Command |= EEPROM_CMD_TMR;
	Command |= (BankSelector == flashInfoBank) ? EEPROM_CMD_IFREN : 0;
	MDR_EEPROM->CMD = Command;
	MDR_EEPROM->ADR = Address;
	MDR_EEPROM->CMD = Command | EEPROM_CMD_XE | EEPROM_CMD_YE | EEPROM_CMD_SE;
	Data = MDR_EEPROM->DO;   /* Idle Reading for Delay */
	Data = MDR_EEPROM->DO;   /* Idle Reading for Delay */
	Data = MDR_EEPROM->DO;   /* Idle Reading for Delay */
	Data = MDR_EEPROM->DO;
    /* clear all bits except latency and TMR */
    Command &= (uint32_t)(EEPROM_CMD_DELAY_Msk | EEPROM_CMD_TMR);
	MDR_EEPROM->CMD = Command;

	/* enable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_LOCK_KEY;

	/* return data */
	Shift = (Address & 3) * 8;
	Data >>= Shift;
	return Data;
}

/**
 *  @brief  read 2 bytes from the flash memory
 *  @param  address - address of the byte to be read
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @return bytes from the memory within specified address
 */
__RAMFUNC uint16_t EEPROM_ReadHalfWord(uint32_t Address, flashMemBank BankSelector)
{
	uint32_t Data;
	uint32_t Command;
	uint32_t Shift;

	/* test input parameters */
	assert_param(IS_FLASH_MEMORY_BANK_RW(BankSelector));
	assert_param(IS_TWO_BYTE_ALLIGNED(Address));

	/* disable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_UNLOCK_KEY;

	/* read data */
	Command = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON_PROGRAMMING;
    /* due to spec it is recommended to setup TMR every time */
	Command |= EEPROM_CMD_TMR;
	Command |= (BankSelector == flashInfoBank) ? EEPROM_CMD_IFREN : 0;
	MDR_EEPROM->CMD = Command;
	MDR_EEPROM->ADR = Address;
	MDR_EEPROM->CMD = Command | EEPROM_CMD_XE | EEPROM_CMD_YE | EEPROM_CMD_SE;
	Data = MDR_EEPROM->DO;   /* Idle Reading for Delay */
	Data = MDR_EEPROM->DO;   /* Idle Reading for Delay */
	Data = MDR_EEPROM->DO;   /* Idle Reading for Delay */
	Data = MDR_EEPROM->DO;
	/* clear all bits except latency and TMR */
	Command &= (uint32_t)(EEPROM_CMD_DELAY_Msk | EEPROM_CMD_TMR);
	MDR_EEPROM->CMD = Command;

	/* enable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_LOCK_KEY;

	Shift = (Address & 2) * 8;
	Data >>= Shift;
	return Data;
}

/**
 *  @brief  read 4 bytes from the flash memory
 *  @param  address - address of the byte to be read
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @return bytes from the memory within specified address
 */
__RAMFUNC uint32_t EEPROM_ReadWord(uint32_t Address, flashMemBank BankSelector)
{
	uint32_t Command;
	uint32_t Data;

	/* test input parameters */
	assert_param(IS_FLASH_MEMORY_BANK_RW(BankSelector));
	assert_param(IS_FOUR_BYTE_ALLIGNED(Address));

	/* disable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_UNLOCK_KEY;

	/* read data */
	Command = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON_PROGRAMMING;
    /* due to spec it is recommended to setup TMR every time */
	Command |= EEPROM_CMD_TMR;
	Command |= (BankSelector == flashInfoBank) ? EEPROM_CMD_IFREN : 0;
	MDR_EEPROM->CMD = Command;
	MDR_EEPROM->ADR = Address;
	MDR_EEPROM->CMD = Command | EEPROM_CMD_XE | EEPROM_CMD_YE | EEPROM_CMD_SE;
	Data = MDR_EEPROM->DO;   /* Idle Reading for Delay */
	Data = MDR_EEPROM->DO;   /* Idle Reading for Delay */
	Data = MDR_EEPROM->DO;   /* Idle Reading for Delay */
	Data = MDR_EEPROM->DO;
    /* clear all bits except latency and TMR */
    Command &= (uint32_t)(EEPROM_CMD_DELAY_Msk | EEPROM_CMD_TMR);
	MDR_EEPROM->CMD = Command;

	/* enable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_LOCK_KEY;

	return Data;
}

/**
 *  @brief  erase signle page from the flash memory
 *  @param  address - address of the page start
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 */
__RAMFUNC void EEPROM_ErasePage(uint32_t Address, flashMemBank BankSelector)
{
	uint32_t Command;
	uint32_t Offset;

	/* test input parameters */
	assert_param(IS_FLASH_MEMORY_BANK_ERASE(BankSelector));

	/* disable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_UNLOCK_KEY;

	/* prepare command */
	Command = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON_PROGRAMMING;
    /* due to spec it is recommended to setup TMR every time */
	Command |= EEPROM_CMD_TMR;
	Command |= (BankSelector == flashInfoBank) ? EEPROM_CMD_IFREN : 0;
	MDR_EEPROM->CMD = Command;

	for (Offset = 0; Offset < (4 << 2); Offset += 4)
	{
		MDR_EEPROM->ADR = Address + Offset;             /* Page Address */
		MDR_EEPROM->DI = 0;
		Command |= EEPROM_CMD_XE | EEPROM_CMD_ERASE;
		MDR_EEPROM->CMD = Command;
		ProgramDelay(GET_US_LOOPS(5));              /* Wait for 5 us */
		Command |= EEPROM_CMD_NVSTR;
		MDR_EEPROM->CMD = Command;
		ProgramDelay(GET_US_LOOPS(40000));          /* Wait for 40 ms */
		Command &= ~EEPROM_CMD_ERASE;
		MDR_EEPROM->CMD = Command;
		ProgramDelay(GET_US_LOOPS(5));              /* Wait for 5 us */
		Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_NVSTR);
		MDR_EEPROM->CMD = Command;
		ProgramDelay(GET_US_LOOPS(1));              /* Wait for 1 us */
	}
    /* clear all bits except latency and TMR */
    Command &= (uint32_t)(EEPROM_CMD_DELAY_Msk | EEPROM_CMD_TMR);
	MDR_EEPROM->CMD = Command;

	/* enable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_LOCK_KEY;
}

/**
 *  @brief  erase all pages from the flash memory
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 */
__RAMFUNC void EEPROM_EraseAllPages(flashMemBank BankSelector)
{
	uint32_t Command;
	uint32_t Offset;

	/* test input parameters */
	assert_param(IS_FLASH_MEMORY_BANK_ERASE(BankSelector));

	/* disable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_UNLOCK_KEY;

	/* prepare command */
	Command = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON_PROGRAMMING;
    /* due to spec it is recommended to setup TMR every time */
	Command |= EEPROM_CMD_TMR;
	Command |= (BankSelector == flashInfoBank) ? EEPROM_CMD_IFREN : 0;
	MDR_EEPROM->CMD = Command;

	/* erase pages */
	for (Offset = 0; Offset < (4 << 2); Offset += 4)
	{
		MDR_EEPROM->ADR = Offset;
		MDR_EEPROM->DI = 0;
		Command |= EEPROM_CMD_XE | EEPROM_CMD_MAS1 | EEPROM_CMD_ERASE;
		MDR_EEPROM->CMD = Command;
		ProgramDelay(GET_US_LOOPS(5));                /* Wait for 5 us */
		Command |= EEPROM_CMD_NVSTR;
		MDR_EEPROM->CMD = Command;
		ProgramDelay(GET_US_LOOPS(40000));            /* Wait for 40 ms */
		Command &= ~EEPROM_CMD_ERASE;
		MDR_EEPROM->CMD = Command;
		ProgramDelay(GET_US_LOOPS(100));              /* Wait for 100 us */
		Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_MAS1 | EEPROM_CMD_NVSTR);
		MDR_EEPROM->CMD = Command;
		ProgramDelay(GET_US_LOOPS(1));                /* Wait for 1 us */
	}
    /* clear all bits except latency and TMR */
    Command &= (uint32_t)(EEPROM_CMD_DELAY_Msk | EEPROM_CMD_TMR);
	MDR_EEPROM->CMD = Command;

	/* enable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_LOCK_KEY;
}

/**
 *  @brief  program single byte to the flash memory
 *  @param  address - address of the page start
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @param  data - value to be written
 */
__RAMFUNC void EEPROM_ProgramByte(uint32_t Address, flashMemBank BankSelector, uint8_t Data)
{
	uint32_t Mask, Tmp, Shift, d;

	/* test input parameters */
	assert_param(IS_FLASH_MEMORY_BANK_RW(BankSelector));

	/* prepare data and mask */
	Shift = (Address & 3) * 8;
	d = (uint32_t)Data << Shift;
	Mask = 0xFF << Shift;

	/* read data and prepare update word */
	Tmp = EEPROM_ReadWord(Address, BankSelector);
	Tmp = (Tmp & ~Mask) | (d & Mask);

	/* write data back */
	EEPROM_ProgramWord(Address, BankSelector, Tmp);
}

/**
 *  @brief  program 2 bytes to the flash memory
 *  @param  address - address of the page start
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @param  data - value to be written
 */
__RAMFUNC void EEPROM_ProgramHalfWord(uint32_t Address, flashMemBank BankSelector, uint16_t Data)
{
	uint32_t Mask;
	uint32_t Tmp;
	uint32_t Shift;

	/* test input parameters */
	assert_param(IS_FLASH_MEMORY_BANK_RW(BankSelector));
	assert_param(IS_TWO_BYTE_ALLIGNED(Address));

	/* prepare data and mask */
	Shift = (Address & 2) * 8;
	Data = Data << Shift;
	Mask = 0xFFFF << Shift;

	/* read data and prepare update word */
	Tmp = EEPROM_ReadWord(Address, BankSelector);
	Tmp = (Tmp & ~Mask) | (Data & Mask);

	/* write data back */
	EEPROM_ProgramWord(Address, BankSelector, Tmp);
}

/**
 *  @brief  program 4 bytes to the flash memory
 *  @param  address - address of the page start
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @param  data - value to be written
 */
__RAMFUNC void EEPROM_ProgramWord(uint32_t Address, flashMemBank BankSelector, uint32_t Data)
{
	uint32_t Command;

	/* test input parameters */
	assert_param(IS_FLASH_MEMORY_BANK_RW(BankSelector));
	assert_param(IS_FOUR_BYTE_ALLIGNED(Address));

	/* disable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_UNLOCK_KEY;

	/* prepare command */
	Command = (MDR_EEPROM->CMD & EEPROM_CMD_DELAY_Msk) | EEPROM_CMD_CON_PROGRAMMING;
    /* due to spec it is recommended to setup TMR every time */
	Command |= EEPROM_CMD_TMR;
	Command |= ((BankSelector == flashInfoBank) ? EEPROM_CMD_IFREN : 0);

	/* proceed memory programming */
	MDR_EEPROM->CMD = Command;
	MDR_EEPROM->ADR = Address;
	MDR_EEPROM->DI  = Data;
	Command |= EEPROM_CMD_XE | EEPROM_CMD_PROG;
	MDR_EEPROM->CMD = Command;
	ProgramDelay(GET_US_LOOPS(5));                /* Wait for 5 us */
	Command |= EEPROM_CMD_NVSTR;
	MDR_EEPROM->CMD = Command;
	ProgramDelay(GET_US_LOOPS(10));               /* Wait for 10 us */
	Command |= EEPROM_CMD_YE;
	MDR_EEPROM->CMD = Command;
	ProgramDelay(GET_US_LOOPS(40));               /* Wait for 40 us */
	Command &= ~EEPROM_CMD_YE;
	MDR_EEPROM->CMD = Command;
	Command &= ~EEPROM_CMD_PROG;
	MDR_EEPROM->CMD = Command;
	ProgramDelay(GET_US_LOOPS(5));                /* Wait for 5 us */
	Command &= ~(EEPROM_CMD_XE | EEPROM_CMD_NVSTR);
	MDR_EEPROM->CMD = Command;
	ProgramDelay(GET_US_LOOPS(1));                /* Wait for 1 us */

    /* clear all bits except latency and TMR */
    Command &= (uint32_t)(EEPROM_CMD_DELAY_Msk | EEPROM_CMD_TMR);
	MDR_EEPROM->CMD = Command;

	/* enable protection */
	MDR_EEPROM->KEY = EEPROM_KEY_LOCK_KEY;
}

/** @} */ /* End of group EEPROM_Exported_Functions */

/** @defgroup EEPROM_Private_Functions
  * @{
  */

/**
  * @brief  Program delay.
  * @param  Loops: Number of the loops.
  * @retval None.
  */
__RAMFUNC static void ProgramDelay(uint32_t Loops)
{
	volatile uint32_t i = Loops;
	for (; i > 0; i--)
	{
		asm("nop");
	}
}

/** @} */ /* End of group EEPROM_Private_Functions */

/** @} */ /* End of group EEPROM */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/*
*
* END OF FILE MLDR187_eeprom.c */


