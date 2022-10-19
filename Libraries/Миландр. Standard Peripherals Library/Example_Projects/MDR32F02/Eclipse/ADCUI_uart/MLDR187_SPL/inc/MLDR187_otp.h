/**
  * FILE MLDR187_otp.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_OTP_H
#define __MLDR187_OTP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#include "MLDR187.h"
#include "MLDR187_lib.h"

/** @addtogroup __MLDR187_StdPeriph_Driver MLDR187 Standard Peripherial Driver
  * @{
  */

/** @addtogroup OTP
  * @{
  */

/** @defgroup OTP_Exported_Types
  * @{
  */
  
/**
 *  state of the OTP write operation:
 *      - success - bit was writted successfully 
 *      - invalid - bit cannot be writen (value 1 cannot be switched to 0 OR write-protection)
 *      - HWFatalError - process caused HW error or requested bit doesn't change it's state
 */
typedef enum 
{
    otpSuccess,
    otpInvalid,
    otpHWFatalError
} otpStatus;

/** @} */ /* End of group OTP_Exported_Types */

/** @defgroup OTP_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize OTP module
 */
void OTP_Init(void);
  
/**
 *  @brief  write signle bit to OTP memory 
 *  @param  addr - bit-address of the specified bit
 *  @param  value - value to be written, 7 MSbits are ignored
 *  @retval @otpStatus of the operation
 */
otpStatus OTP_WriteBit(uint32_t addr, uint8_t value);

/**
 *  @brief  write signle byte to OTP memory 
 *  @param  addr - bit-address of the specified byte, 3 LSbits are ignored
 *  @param  value - value to be written
 *  @retval @otpStatus of the operation
 */
otpStatus OTP_WriteByte(uint32_t addr, uint8_t value);
  
/**
 *  @brief  read signle byte from the OTP memory
 *  @param  addr - bit-address of the specified byte, 3 LSbits are ignored
 *  @return OTP value at specified address
 */
uint8_t OTP_Read(uint32_t addr);

/**
 * 	@brief	read read-protection state
 * 	@return	bit-mask of protection, every bit protects 2048 bytes of OTP
 */
uint8_t OTP_ReadReadProtection(void);

/**
 *  @brief  set OTP read-protection 
 *  @param  mask - bit-mask of protection, every bit protects 2048 bytes of OTP
 */
void OTP_SetReadProtection(uint8_t mask);

/**
 * 	@brief	read write-protection state
 * 	@return	bit-mask of protection, every bit protects 2048 bytes of OTP
 */
uint8_t OTP_ReadWriteProtection(void);

/**
 *  @brief  set OTP write-protection
 *  @param  mask - bit-mask of protection, every bit protects 2048 bytes of OTP
 */
void OTP_SetWriteProtection(uint8_t mask);

/** @} */ /* End of group OTP_Exported_Functions */

/** @} */ /* End of group OTP */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_OTP_H */

/**
 * END OF FILE MLDR187_otp.h
 */

