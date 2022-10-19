#include "otp_functions.h"

#include <stdlib.h>
#include <MLDR187_eeprom.h>

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


__attribute__((always_inline)) static inline void ProgramDelay(uint32_t Loops)
{
    volatile uint32_t i = Loops;
    for (; i > 0; i--)
    {
        asm("nop");
    }
}


void EEPROM_ProgramWord_from_OTP(uint32_t Address, flashMemBank BankSelector, uint32_t Data)
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


void EEPROM_ErasePage_from_OTP(uint32_t Address, flashMemBank BankSelector)
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

