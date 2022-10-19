/**
  * FILE MLDR187_crc.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_CRC_H
#define __MLDR187_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup CRC
  * @{
  */

/** @defgroup CRC_Exported_Types
  * @{
  */

/* data inversion during CRC calculation */
typedef enum
{
    crcCalcOrderMSBF,
    crcCalcOrderLSBF
} crcCalcOrder;

/** @} */ /* End of group CRC_Exported_Types */

/** @defgroup CRC_Exported_Constants
  * @{
  */

/** @} */ /* End of group CRC_Exported_Constants */

/** @defgroup CRC_Exported_Macros
  * @{
  */

/** @} */ /* End of group CRC_Exported_Macros */

/** @defgroup CRC_Exported_Functions
  * @{
  */

/**
 *  @brief  initialize CRC processing unit with specified polynomial, enable peripheral clock
 *  @param  polynomial - calculation polynomial definition
 *  @param  order - data inversion during calculation (MSBF / LSBF)
 */
void CRC_Init(uint16_t polynomial, crcCalcOrder order);

/**
 * 	@brief	deinitialize CRC module, write default values to all registers and disable peripheral clock
 */
void CRC_DeInit(void);

/**
 *  @param  start CRC processing with initial value
 *  @param  initial - initial value
 */
void CRC_Start(uint16_t initial);

/**
 *  @brief  add byte to processing
 *  @param  value - next 8 bits to be proceeded
 */
void CRC_ProceedByte(uint8_t value);

/**
 *  @brief  add half word to processing
 *  @param  value - next 16 bits to be proceeded
 */
void CRC_ProceedHalfWord(uint32_t value);

/**
 *  @brief  add word to processing
 *  @param  value - next 32 bits to be proceeded
 */
void CRC_ProceedWord(uint32_t value);

/**
 *  @brief  finalize CRC calculation and return result
 *  @return CRC calculation result
 */
uint16_t CRC_Finalize(void);

/**
 *  @brief  calculate CRC for specified memory window
 *  		includes: module power-on, initialization, all bytes processing, finalization and module power-off
 *  @param  start - start address
 *  @param  len - number of bytes to be proceeded
 *  @param  polynomial - calculation polynomial definition
 *  @param  initial - initial value
 *  @param  order - data inversion during calculation (MSBF / LSBF)
 *  @return CRC calculation result
 */
uint16_t CRC_Mem(uint8_t* start, uint32_t len, uint16_t polynomial, uint16_t initial, crcCalcOrder order);

/** @} */ /* End of group CRC_Exported_Functions */

/** @} */ /* End of group CRC */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_CRC_H */

/**
 * END OF FILE MLDR187_crc.h
 */

