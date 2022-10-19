/**
  * FILE MLDR187_eeprom.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_EEPROM_H
#define __MLDR187_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"

#include <stdint.h>

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup EEPROM
  * @{
  */

/** @defgroup EEPROM_Exported_Types
  * @{
  */

/* maximum speed for FLASH module is 30 MHz, user should use lattency delay if core speed is greater */
typedef enum
{
    flashCoreSpeedUpTo30MHz,
    flashCoreSpeedUpTo60MHz
} flashCoreSpeed;

/* flash memory bank selector: Main memory (256K), Info memory (8K) or both */
typedef enum
{
	flashMainBank,
	flashInfoBank,
	flashBothBanks
} flashMemBank;

/** @} */ /* End of group EEPROM_Exported_Types */

/** @defgroup EEPROM_Exported_Constants
  * @{
  */

/** @} */ /* End of group EEPROM_Exported_Constants */

/** @defgroup EEPROM_Exported_Macros
  * @{
  */

/** @} */ /* End of group EEPROM_Exported_Macros */

/** @defgroup EEPROM_Exported_Functions
  * @{
  */

/** @defgroup EEPROM_Functions_allowed_to_be_located_in_Flash
  * @{
  */

/**
 *  @brief  maximum core speed to setup flash lattency
 *  @param  coreSpeed - @flashCoreSpeed maximum core speed (less or equal to 30MHz OR more)
 */
void EEPROM_SetLatency(flashCoreSpeed coreSpeed);

/** @} */ /* End of group EEPROM_Functions_allowed_to_be_located_in_Flash */

/** @defgroup EEPROM_Functions_not_allowed_to_be_located_in_Flash Functions not allowed to be located in Flash
  * @{
  */

#define __RAMFUNC __attribute__((section("EXECUTABLE_MEMORY_SECTION")))

/**
 *  @brief  read out byte from the flash memory
 *  @param  address - address of the byte to be read
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @return byte from the memory within specified address
 */
__RAMFUNC uint8_t EEPROM_ReadByte (uint32_t Address, flashMemBank BankSelector) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/**
 *  @brief  read 2 bytes from the flash memory
 *  @param  address - address of the byte to be read
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @return bytes from the memory within specified address
 */
__RAMFUNC uint16_t EEPROM_ReadHalfWord(uint32_t Address, flashMemBank BankSelector) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/**
 *  @brief  read 4 bytes from the flash memory
 *  @param  address - address of the byte to be read
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @return bytes from the memory within specified address
 */
__RAMFUNC uint32_t EEPROM_ReadWord(uint32_t Address, flashMemBank BankSelector) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/**
 *  @brief  erase signle page from the flash memory
 *  @param  address - address of the page start
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 */
__RAMFUNC void EEPROM_ErasePage(uint32_t Address, flashMemBank BankSelector) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/**
 *  @brief  erase all pages from the flash memory
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 */
__RAMFUNC void EEPROM_EraseAllPages(flashMemBank BankSelector) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/**
 *  @brief  program single byte to the flash memory
 *  @param  address - address of the page start
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @param  data - value to be written
 */
__RAMFUNC void EEPROM_ProgramByte(uint32_t Address, flashMemBank BankSelector, uint8_t Data) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/**
 *  @brief  program 2 bytes to the flash memory
 *  @param  address - address of the page start
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @param  data - value to be written
 */
__RAMFUNC void EEPROM_ProgramHalfWord(uint32_t Address, flashMemBank BankSelector, uint16_t Data) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/**
 *  @brief  program 4 bytes to the flash memory
 *  @param  address - address of the page start
 *  @param  bankSelector - @ref flashMemBank - selection of the main or info memory
 *  @param  data - value to be written
 */
__RAMFUNC void EEPROM_ProgramWord(uint32_t Address, flashMemBank BankSelector, uint32_t Data) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

/** @} */ /* End of group EEPROM_Functions_not_allowed_to_be_located_in_Flash */

/** @} */ /* End of group EEPROM_Exported_Functions */

/** @} */ /* End of group EEPROM */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_EEPROM_H */

/**
 * END OF FILE MLDR187_eeprom.h
 */

