/**
  * FILE MLDR187_lib.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_LIB_H
#define __MLDR187_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

/* hardware definition */
#include "MLDR187.h"

/* flag status enumeration */
typedef enum
{
	RESET = 0,
	SET = !RESET
} FlagStatus, ITStatus, BitStatus;
/* assert flag status */
#define IS_FLAG_STATUS(FLAG) (((FLAG) == RESET) || ((FLAG) == SET))

/* functional state enumeration */
typedef enum
{
	DISABLE = 0,
	ENABLE = !DISABLE
} FunctionalState;
/* assert function state */
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

/* operation result enumeration */
typedef enum
{
	ERROR = 0,
	SUCCESS = !ERROR
} ErrorStatus;

/* common assert for the RAM memory */
#define IS_MEMORY_IN_COMMON_RAM(START, LEN) (((uint32_t)(START) >= MDR_SYSTEM_RAM_TCMA) && ((uint32_t)(START) + (LEN) <= MDR_SYSTEM_RAM_TCMA + (112 * 1024)))

/* maximum flash programming frequency (for delays) */
#define FLASH_PROG_FREQ_MHZ     (60.0)

#define USE_ASSERT_INFO    0
/* #define USE_ASSERT_INFO    1 */
/* #define USE_ASSERT_INFO    2 */

/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param  expr: If expr is false, it calls assert_failed user's function
 *   which gets the source file ID (see MDR32F9Qx_lib.h), line number and
 *   expression text (if USE_ASSERT_INFO == 2) of the call that failed. That
 *   function should not return. If expr is true, nothing is done.
 * @retval None
 */
#if (USE_ASSERT_INFO == 0)
 #define assert_param(expr) ((void)0)
#elif (USE_ASSERT_INFO == 1)
 #define assert_param(expr) ((expr) ? (void)0 : assert_failed(ASSERT_INFO_FILE_ID, __LINE__))
 void assert_failed(uint32_t file_id, uint32_t line);
#elif (USE_ASSERT_INFO == 2)
 #define assert_param(expr) ((expr) ? (void)0 : assert_failed(ASSERT_INFO_FILE_ID, __LINE__, #expr))
 void assert_failed(uint32_t file_id, uint32_t line, const uint8_t* expr);
#else
 #error "Unsupported USE_ASSERT_INFO level"
#endif /* USE_ASSERT_INFO */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_LIB_H */

/**
 * END OF FILE MLDR187_lib.h
 */

