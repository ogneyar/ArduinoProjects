/**
  * FILE MLDR187_crypto.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_CRYPTO_H
#define __MLDR187_CRYPTO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>

/** @addtogroup __MLDR187_StdPeriph_Driver MLDR187 Standard Peripherial Driver
  * @{
  */

/** @addtogroup CRYPTO
  * @{
  */

/**
  * implementation selection: ASM or C
  *
  * By default, ASM implementation is recommended. Use C implementation if there is any
  * problems with ASM usage within your compiler
  *
  * ASM implementation of the cryptography 3-5 times faster than C implementation
  * and produce 1.5-2 times less code (depends on compiler)
  *
  * ASM implementation is compiled, linked and tested with GNU GCC compiler
  */
#define CRYPTO_KUZNECHIK_ASM
#ifndef CRYPTO_KUZNECHIK_ASM
#define CRYPTO_KUZNECHIK_C
#endif
#define CRYPTO_AES_ASM
#ifndef CRYPTO_AES_ASM
#define CRYPTO_AES_C
#endif

/** @defgroup CRYPTO_Exported_Types CRYPTO Exported Types
  * @{
  */

/* possible types of AES cipher - bit length of the key */
typedef enum
{
    AES128 = 128,
    AES192 = 192,
    AES256 = 256
} AesType;

/** @} */ /* End of group CRYPTO_Exported_Types */

/** @defgroup CRYPTO_Exported_Constants
  * @{
  */

/** @} */ /* End of group CRYPTO_Exported_Constants */

/** @defgroup CRYPTO_Exported_Macros
  * @{
  */

/** @} */ /* End of group CRYPTO_Exported_Macros */

/** @defgroup CRYPTO_Exported_Functions
  * @{
  */

/**************************************************************************************************/
/*                                       AES-128,192,256                                          */
/**************************************************************************************************/

/**
 *  @brief  initialize AES processing
 *          should be called only once before any number of AES operations
 *          if any user code re-init crypto processors (for example,
 *          other cipher initialization is called), update could be required
 */
void aesInitCCPU(void);

/**
 *  @brief  key expansion for AES processing
 *          approximate performance (depends on compiler):
 *          AES-128:
 *          1950  CPU clock cycles - ASM implementation
 *          4800  CPU clock cycles - C implementation
 *          AES-192:
 *          2200  CPU clock cycles - ASM implementation
 *          5500  CPU clock cycles - C implementation
 *          AES-256:
 *          2800  CPU clock cycles - ASM implementation
 *          6700  CPU clock cycles - C implementation
 *  @param  key [in] - pointer to compressed key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256 or 128, 192, 256
 *  @param  expKey [out] - pointer to store expanded key
 */
void aesExpandKey(uint8_t* key, uint32_t type, uint32_t* expKey);

/**
 *  @brief  block encryption with AES
 *          approximate performance (depends on compiler):
 *          AES-128:
 *          1650  CPU clock cycles - ASM implementation
 *          5400  CPU clock cycles - C implementation
 *          AES-192:
 *          2000  CPU clock cycles - ASM implementation
 *          6500  CPU clock cycles - C implementation
 *          AES-256:
 *          2300  CPU clock cycles - ASM implementation
 *          7500  CPU clock cycles - C implementation
 *  @param  data [in/out] - data block to be encrypted, 16 bytes
 *  @param  expKey [in] - expanded key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 */
void aesEncBlock(uint8_t* data, uint32_t* expKey, uint32_t type);

/**
 *  @brief  block decryption with AES
 *          approximate performance (depends on compiler):
 *          AES-128:
 *          2300  CPU clock cycles - ASM implementation
 *          6300  CPU clock cycles - C implementation
 *          AES-192:
 *          2750  CPU clock cycles - ASM implementation
 *          7500  CPU clock cycles - C implementation
 *          AES-256:
 *          3200  CPU clock cycles - ASM implementation
 *          8800  CPU clock cycles - C implementation
 *  @param  data [in/out] - data block to be decrypted, 16 bytes
 *  @param  expKey [in] - expanded key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 */
void aesDecBlock(uint8_t* data, uint32_t* expKey, uint32_t type);

/**************************************************************************************************/
/*                               GOST R34.12-2015 Kuznechik                                       */
/**************************************************************************************************/

/**
 *  @brief  initialize GOST R34.12-2015 (Kuznechik) processing
 *          should be called only once before any number of Kuznechik operations
 *          if any user code re-init L-block, S-block#1/2 or P-byte co-processors (for example,
 *          other cipher initialization is called), update could be required
 */
void kuzInitCCPU(void);

/**
 *  @brief  key expansion for Kuznechik processing
 *          approximate performance (depends on compiler):
 *          5600  CPU clock cycles - ASM implementation
 *          24140 CPU clock cycles - C implementation
 *          to select implementation use definitions above
 *  @param  key [in] - pointer to compressed key
 *  @param  expKey [out] - pointer to store expanded key in system little-endian format
 */
void kuzExpandKey(uint8_t* key, uint32_t* expKey);

/**
 *  @brief  block encryption with Kuznechik
 *          approximate performance (depends on compiler):
 *          920  CPU clock cycles - ASM implementation
 *          2700 CPU clock cycles - C implementation
 *          to select implementation use definitions above
 *  @param  data [in/out] - data block to be encrypted, 16 bytes
 *  @param  expKey [in] - expanded key in system little-endian format
 */
void kuzEncBlock(uint8_t* data, uint32_t* expKey);

/**
 *  @brief  block decryption with Kuznechik
 *          approximate performance (depends on compiler):
 *          920  CPU clock cycles - ASM implementation
 *          2700 CPU clock cycles - C implementation
 *          to select implementation use definitions above
 *  @param  data [in/out] - data block to be decrypted, 16 bytes
 *  @param  expKey [in] - expanded key in system little-endian format
 */
void kuzDecBlock(uint8_t* data, uint32_t* expKey);

/** @} */ /* End of group CRYPTO_Exported_Functions */

/** @} */ /* End of group CRYPTO */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_CRYPTO_H */

/**
 * END OF FILE MLDR187_crypto.h
 */

