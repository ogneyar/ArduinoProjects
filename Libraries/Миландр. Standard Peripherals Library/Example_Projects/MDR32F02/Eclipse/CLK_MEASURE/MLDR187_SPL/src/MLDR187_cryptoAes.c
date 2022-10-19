/**
  * FILE MLDR187_cryptoAes.c
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_crypto.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_CRYPTOAES_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup CRYPTOAES
  * @{
  */

/** @defgroup CRYPTOAES_Private_Constants
  * @{
  */

/* round constants */
uint8_t g_AesRcon[16] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A };

/* S-box values */
uint8_t g_AesSBox[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16 };

/* inversed S-box values */
uint8_t g_AesSboxM1[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

/* Table multiplication constants */
uint8_t g_AesE[256] = {
    0x01, 0x03, 0x05, 0x0F, 0x11, 0x33, 0x55, 0xFF, 0x1A, 0x2E, 0x72, 0x96, 0xA1, 0xF8, 0x13, 0x35,
    0x5F, 0xE1, 0x38, 0x48, 0xD8, 0x73, 0x95, 0xA4, 0xF7, 0x02, 0x06, 0x0A, 0x1E, 0x22, 0x66, 0xAA,
    0xE5, 0x34, 0x5C, 0xE4, 0x37, 0x59, 0xEB, 0x26, 0x6A, 0xBE, 0xD9, 0x70, 0x90, 0xAB, 0xE6, 0x31,
    0x53, 0xF5, 0x04, 0x0C, 0x14, 0x3C, 0x44, 0xCC, 0x4F, 0xD1, 0x68, 0xB8, 0xD3, 0x6E, 0xB2, 0xCD,
    0x4C, 0xD4, 0x67, 0xA9, 0xE0, 0x3B, 0x4D, 0xD7, 0x62, 0xA6, 0xF1, 0x08, 0x18, 0x28, 0x78, 0x88,
    0x83, 0x9E, 0xB9, 0xD0, 0x6B, 0xBD, 0xDC, 0x7F, 0x81, 0x98, 0xB3, 0xCE, 0x49, 0xDB, 0x76, 0x9A,
    0xB5, 0xC4, 0x57, 0xF9, 0x10, 0x30, 0x50, 0xF0, 0x0B, 0x1D, 0x27, 0x69, 0xBB, 0xD6, 0x61, 0xA3,
    0xFE, 0x19, 0x2B, 0x7D, 0x87, 0x92, 0xAD, 0xEC, 0x2F, 0x71, 0x93, 0xAE, 0xE9, 0x20, 0x60, 0xA0,
    0xFB, 0x16, 0x3A, 0x4E, 0xD2, 0x6D, 0xB7, 0xC2, 0x5D, 0xE7, 0x32, 0x56, 0xFA, 0x15, 0x3F, 0x41,
    0xC3, 0x5E, 0xE2, 0x3D, 0x47, 0xC9, 0x40, 0xC0, 0x5B, 0xED, 0x2C, 0x74, 0x9C, 0xBF, 0xDA, 0x75,
    0x9F, 0xBA, 0xD5, 0x64, 0xAC, 0xEF, 0x2A, 0x7E, 0x82, 0x9D, 0xBC, 0xDF, 0x7A, 0x8E, 0x89, 0x80,
    0x9B, 0xB6, 0xC1, 0x58, 0xE8, 0x23, 0x65, 0xAF, 0xEA, 0x25, 0x6F, 0xB1, 0xC8, 0x43, 0xC5, 0x54,
    0xFC, 0x1F, 0x21, 0x63, 0xA5, 0xF4, 0x07, 0x09, 0x1B, 0x2D, 0x77, 0x99, 0xB0, 0xCB, 0x46, 0xCA,
    0x45, 0xCF, 0x4A, 0xDE, 0x79, 0x8B, 0x86, 0x91, 0xA8, 0xE3, 0x3E, 0x42, 0xC6, 0x51, 0xF3, 0x0E,
    0x12, 0x36, 0x5A, 0xEE, 0x29, 0x7B, 0x8D, 0x8C, 0x8F, 0x8A, 0x85, 0x94, 0xA7, 0xF2, 0x0D, 0x17,
    0x39, 0x4B, 0xDD, 0x7C, 0x84, 0x97, 0xA2, 0xFD, 0x1C, 0x24, 0x6C, 0xB4, 0xC7, 0x52, 0xF6, 0x01 };

uint8_t g_AesL[256] = {
    0x00, 0x00, 0x19, 0x01, 0x32, 0x02, 0x1A, 0xC6, 0x4B, 0xC7, 0x1B, 0x68, 0x33, 0xEE, 0xDF, 0x03,
    0x64, 0x04, 0xE0, 0x0E, 0x34, 0x8D, 0x81, 0xEF, 0x4C, 0x71, 0x08, 0xC8, 0xF8, 0x69, 0x1C, 0xC1,
    0x7D, 0xC2, 0x1D, 0xB5, 0xF9, 0xB9, 0x27, 0x6A, 0x4D, 0xE4, 0xA6, 0x72, 0x9A, 0xC9, 0x09, 0x78,
    0x65, 0x2F, 0x8A, 0x05, 0x21, 0x0F, 0xE1, 0x24, 0x12, 0xF0, 0x82, 0x45, 0x35, 0x93, 0xDA, 0x8E,
    0x96, 0x8F, 0xDB, 0xBD, 0x36, 0xD0, 0xCE, 0x94, 0x13, 0x5C, 0xD2, 0xF1, 0x40, 0x46, 0x83, 0x38,
    0x66, 0xDD, 0xFD, 0x30, 0xBF, 0x06, 0x8B, 0x62, 0xB3, 0x25, 0xE2, 0x98, 0x22, 0x88, 0x91, 0x10,
    0x7E, 0x6E, 0x48, 0xC3, 0xA3, 0xB6, 0x1E, 0x42, 0x3A, 0x6B, 0x28, 0x54, 0xFA, 0x85, 0x3D, 0xBA,
    0x2B, 0x79, 0x0A, 0x15, 0x9B, 0x9F, 0x5E, 0xCA, 0x4E, 0xD4, 0xAC, 0xE5, 0xF3, 0x73, 0xA7, 0x57,
    0xAF, 0x58, 0xA8, 0x50, 0xF4, 0xEA, 0xD6, 0x74, 0x4F, 0xAE, 0xE9, 0xD5, 0xE7, 0xE6, 0xAD, 0xE8,
    0x2C, 0xD7, 0x75, 0x7A, 0xEB, 0x16, 0x0B, 0xF5, 0x59, 0xCB, 0x5F, 0xB0, 0x9C, 0xA9, 0x51, 0xA0,
    0x7F, 0x0C, 0xF6, 0x6F, 0x17, 0xC4, 0x49, 0xEC, 0xD8, 0x43, 0x1F, 0x2D, 0xA4, 0x76, 0x7B, 0xB7,
    0xCC, 0xBB, 0x3E, 0x5A, 0xFB, 0x60, 0xB1, 0x86, 0x3B, 0x52, 0xA1, 0x6C, 0xAA, 0x55, 0x29, 0x9D,
    0x97, 0xB2, 0x87, 0x90, 0x61, 0xBE, 0xDC, 0xFC, 0xBC, 0x95, 0xCF, 0xCD, 0x37, 0x3F, 0x5B, 0xD1,
    0x53, 0x39, 0x84, 0x3C, 0x41, 0xA2, 0x6D, 0x47, 0x14, 0x2A, 0x9E, 0x5D, 0x56, 0xF2, 0xD3, 0xAB,
    0x44, 0x11, 0x92, 0xD9, 0x23, 0x20, 0x2E, 0x89, 0xB4, 0x7C, 0xB8, 0x26, 0x77, 0x99, 0xE3, 0xA5,
    0x67, 0x4A, 0xED, 0xDE, 0xC5, 0x31, 0xFE, 0x18, 0x0D, 0x63, 0x8C, 0x80, 0xC0, 0xF7, 0x70, 0x07 };

/* input transformation (convert to matrix) byte order */
uint8_t g_AesBeginTrm[] = { 12, 8, 4, 0,  13, 9, 5, 1,  14, 10, 6, 2,  15, 11, 7, 3 };

/* output transformation (revert from matrix) byte order */
uint8_t g_AesFinishTrm[] = { 3, 7, 11, 15,  2, 6, 10, 14,  1, 5, 9, 13,  0, 4, 8, 12 };

/* table shift byte order */
uint8_t g_AesShftTblTrm[] = { 0, 1, 2, 3,  7, 4, 5, 6,  10, 11, 8, 9,  13, 14, 15, 12 };

/* inverse table shift byte order */
uint8_t g_AesShftTblM1Trm[] = { 0, 1, 2, 3,  5, 6, 7, 4,  10, 11, 8, 9,  15, 12, 13, 14 };

/** @} */ /* End of group CRYPTOAES_Private_Constants */

/** @defgroup CRYPTOAES_Private_Functions_Declarations
  * @{
  */

/**
  * @brief  fill element with fixed value for CCPU initialization
  * @param  value - value that should be filled (LSB is only used)
  * @return filled value
  */
static uint32_t aesLinearFill(uint32_t value);

/**
  * @brief  precalculate matrix multiplication results as an S-boxes
  * @param  block - pointer to S-block to be initialized
  * @param  elth - element to be used
  * @param  opt - multiplication parameter
  */
static void aesGFM(MDR_SBLOCK_TypeDef* block, uint8_t elth, uint8_t opt);

#ifdef CRYPTO_AES_C

/**
  * @brief  copy 4 words from one location to another
  * @param  dst - pointer where data should be copied
  * @param  src - pointer to data that should be copied
  */
static inline void aesCpyw4(volatile uint32_t* dst, volatile uint32_t* src);

/**
  * @brief  xor 4 words with data at specified position and store result as first op
  * @param  op1res - pointer to first operand and result
  * @param  op2 - pointer to second operand
  */
static inline void aesXorw4(volatile uint32_t* op1res, volatile uint32_t* op2);

/**
 *  @brief  key expansion for AES processing, C-implementation
 *  @param  key [in] - pointer to compressed key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 *  @param  expKey [out] - pointer to store expanded key
 */
static inline void aesExpandKeyC(uint8_t* key, uint32_t type, uint32_t* expKey);

/**
 *  @brief  block encryption with AES, C-implementation
 *  @param  data [in/out] - data block to be encrypted, 16 bytes
 *  @param  expKey [in] - expanded key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 */
static inline void aesEncBlockC(uint8_t* data, uint32_t* expKey, uint32_t type);

/**
 *  @brief  block decryption with AES, C-implementation
 *  @param  data [in/out] - data block to be decrypted, 16 bytes
 *  @param  expKey [in] - expanded key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 */
static inline void aesDecBlockC(uint8_t* data, uint32_t* expKey, uint32_t type);

#else /* CRYPTO_AES_ASM */

/**
 *  @brief  key expansion for AES processing, ASM-implementation
 *  @param  key [in] - pointer to compressed key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 *  @param  expKey [out] - pointer to store expanded key
 *  @param  aesRcon [in] - pointer to round configuration constants
 */
void aesExpandKeyAsm(uint8_t* key, uint32_t type, uint32_t* expKey, uint8_t* aesRcon);

/**
 *  @brief  block encryption with AES, ASM implementation
 *  @param  data [in/out] - data block to be encrypted, 16 bytes
 *  @param  expKey [in] - expanded key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 */
void aesEncBlockAsm(uint8_t* data, uint32_t* expKey, uint32_t type);

/**
 *  @brief  block decryption with AES, ASM implementation
 *  @param  data [in/out] - data block to be decrypted, 16 bytes
 *  @param  expKey [in] - expanded key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 */
void aesDecBlockAsm(uint8_t* data, uint32_t* expKey, uint32_t type);

#endif /* CRYPTO_AES_C */

/** @} */ /* End of group CRYPTOAES_Private_Functions_Declarations */

/** @defgroup CRYPTOAES_Exported_Functions
  * @{
  */

/**
 *  @brief  initialize AES processing
 *          should be called only once before any number of AES operations
 *          if any user code re-init crypto processors (for example,
 *          other cipher initialization is called), update could be required
 */
void aesInitCCPU(void)
{
    uint32_t i, j;
    uint32_t tmp;

    /* S-boxes */
    for (i = 0; i < 256; ++i)
    {
        tmp = aesLinearFill(i);
        MDR_SBLOCK0->TRM_00 = tmp;
        MDR_SBLOCK0->TABLE_CHG = aesLinearFill(g_AesSBox[i]);
        MDR_SBLOCK1->TRM_00 = tmp;
        MDR_SBLOCK1->TABLE_CHG = aesLinearFill(g_AesSboxM1[i]);
    }

    /* precalculated Sbox for matrix multiplication on 0x02, 0x03, 0x09, 0x0B, 0x0D, 0x0E */
    for (i = 0; i < 256; ++i)
    {
        aesGFM(MDR_SBLOCK2, (uint8_t)i, 2);
        aesGFM(MDR_SBLOCK3, (uint8_t)i, 3);
        aesGFM(MDR_SBLOCK4, (uint8_t)i, 9);
        aesGFM(MDR_SBLOCK5, (uint8_t)i, 0x0B);
        aesGFM(MDR_SBLOCK6, (uint8_t)i, 0x0D);
        aesGFM(MDR_SBLOCK7, (uint8_t)i, 0x0E);
    }

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 8; j++) {
            tmp = ((i * 8 + j) << 8) | ((g_AesBeginTrm[i] * 8) + j);
            MDR_PBIT0->MUX_SET = tmp;
            tmp = ((i * 8 + j) << 8) | ((g_AesFinishTrm[i] * 8) + j);
            MDR_PBIT1->MUX_SET = tmp;
            tmp = ((i * 8 + j) << 8) | ((g_AesShftTblTrm[i] * 8) + j);
            MDR_PBIT2->MUX_SET = tmp;
            tmp = ((i * 8 + j) << 8) | ((g_AesShftTblM1Trm[i] * 8) + j);
            MDR_PBIT3->MUX_SET = tmp;
        }
    }

    /* p-byte for byte-order swapping */
    for (i = 0; i < 64; i += 4) {
        MDR_PBYTE->MUX_SET = (0 + i) + ((3 + i) << 8);
        MDR_PBYTE->MUX_SET = (1 + i) + ((2 + i) << 8);
        MDR_PBYTE->MUX_SET = (2 + i) + ((1 + i) << 8);
        MDR_PBYTE->MUX_SET = (3 + i) + ((0 + i) << 8);
    }
}

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
void aesExpandKey(uint8_t* key, uint32_t type, uint32_t* expKey)
{
#ifdef CRYPTO_AES_C
    aesExpandKeyC(key, type, expKey);
#else
    aesExpandKeyAsm(key, type, expKey, g_AesRcon);
#endif /* CRYPTO_AES_C */
}

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
void aesEncBlock(uint8_t* data, uint32_t* expKey, uint32_t type)
{
#ifdef CRYPTO_AES_C
    aesEncBlockC(data, expKey, type);
#else
    aesEncBlockAsm(data, expKey, type);
#endif /* CRYPTO_AES_C */
}

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
void aesDecBlock(uint8_t* data, uint32_t* expKey, uint32_t type)
{
#ifdef CRYPTO_AES_C
    aesDecBlockC(data, expKey, type);
#else
    aesDecBlockAsm(data, expKey, type);
#endif /* CRYPTO_AES_C */
}

/** @} */ /* End of group CRYPTOAES_Exported_Functions */

/** @defgroup CRYPTOAES_Private_Functions
  * @{
  */

/**
  *  @brief  fill element with fixed value for CCPU initialization
  *  @param  value - value that should be filled (LSB is only used)
  *  @return filled value
  */
static uint32_t aesLinearFill(uint32_t value)
{
    uint32_t res;
    memset(&res, (uint8_t)value, sizeof(uint32_t));
    return res;
}

/**
  * @brief  precalculate matrix multiplication results as an S-boxes
  * @param  block - pointer to S-block to be initialized
  * @param  elth - element to be used
  * @param  opt - multiplication parameter
  */
static void aesGFM(MDR_SBLOCK_TypeDef* block, uint8_t elth, uint8_t opt)
{
    uint32_t tmp;

    block->TRM_00 = aesLinearFill(elth);
    tmp = g_AesL[elth] + g_AesL[opt];
    if (tmp > 0xff) {
        tmp -= 0xff;
    }
    tmp = aesLinearFill((elth == 0) ? 0 : g_AesE[tmp]);

    block->TABLE_CHG = tmp;
}

#ifdef CRYPTO_AES_C

/**
  * @brief  copy 4 words from one location to another
  * @param  dst - pointer where data should be copied
  * @param  src - pointer to data that should be copied
  */
static inline void aesCpyw4(volatile uint32_t* dst, volatile uint32_t* src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}

/**
  * @brief  xor 4 words with data at specified position and store result as first op
  * @param  op1res - pointer to first operand and result
  * @param  op2 - pointer to second operand
  */

static inline void aesXorw4(volatile uint32_t* op1res, volatile uint32_t* op2)
{
    op1res[0] ^= op2[0];
    op1res[1] ^= op2[1];
    op1res[2] ^= op2[2];
    op1res[3] ^= op2[3];
}

/**
 *  @brief  key expansion for AES processing, C-implementation
 *  @param  key [in] - pointer to compressed key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 *  @param  expKey [out] - pointer to store expanded key
 */
static inline void aesExpandKeyC(uint8_t* key, uint32_t type, uint32_t* expKey)
{
    uint32_t i, Nk, tmp;

    /* convert from bits to number of words within plain key */
    type >>= 5;
    /* store number of words within plain key */
    Nk = type;
    /* calculate number of 4-words portions within expanded key (number of rounds) */
    type += 6 + 1;
    /* calculate number of words within expanded key */
    type <<= 2;

    /* at first key itself */
    for (i = 0; i < Nk; i++) {
        MDR_PBYTE->TRM_00 = *(uint32_t*)(key + i * 4);
        expKey[i] = MDR_PBYTE->TRM_00;
    }

    /* All other round keys are found from the previous round keys. */
    for (i = Nk; i < type; i++)
    {
        tmp = expKey[i - 1];
        if (i % Nk == 0)
        {
            tmp = (tmp << 8) | (tmp >> 24);
            MDR_SBLOCK0->TRM_00 = tmp;
            tmp = MDR_SBLOCK0->TRM_00;
            tmp ^= (uint32_t)g_AesRcon[i / Nk] << 24;
        }
        else if ((Nk > 6) && (i % Nk == 4)) {
            MDR_SBLOCK0->TRM_00 = tmp;
            tmp = MDR_SBLOCK0->TRM_00;
        }
        expKey[i] = expKey[i - Nk] ^ tmp;
    }

    /* pack key to matrix form */
    for (i = 0; i < type; i += 4) {
        aesCpyw4(&MDR_PBYTE->TRM_00, &expKey[i]);
        aesCpyw4(&MDR_PBIT0->TRM_00, &MDR_PBYTE->TRM_00);
        aesCpyw4(&expKey[i], &MDR_PBIT0->TRM_00);
    }
}

/**
 *  @brief  block encryption with AES, C-implementation
 *  @param  data [in/out] - data block to be encrypted, 16 bytes
 *  @param  expKey [in] - expanded key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 */
static inline void aesEncBlockC(uint8_t* data, uint32_t* expKey, uint32_t type)
{
    uint32_t t[4];
    uint32_t X1[4];

    /* transform to matrix */
    aesCpyw4(&MDR_PBIT0->TRM_00, (uint32_t*)data);
    aesCpyw4(t, &MDR_PBIT0->TRM_00);

    /* proceed number of conversions based on key length */
    type >>= 5;
    type += 6;
    while (1)
    {
        /* xor with key and shift key pointer */
        aesXorw4(t, expKey);
        expKey += 4;

        /* s-box */
        aesCpyw4(&MDR_SBLOCK0->TRM_00, t);
        aesCpyw4(t, &MDR_SBLOCK0->TRM_00);

        /* shift rows */
        aesCpyw4(&MDR_PBIT2->TRM_00, t);
        aesCpyw4(t, &MDR_PBIT2->TRM_00);

        /* within last cycle no mix columns should be proceeded */
        type--;
        if (type == 0) {
            break;
        }

        /* mix columns */
        /* X1 */
        aesCpyw4(X1, t);
        /* X2 */
        aesCpyw4(&MDR_SBLOCK2->TRM_00, t);
        /* X3 */
        aesCpyw4(&MDR_SBLOCK3->TRM_00, t);
        t[0] = MDR_SBLOCK2->TRM_00 ^ MDR_SBLOCK3->TRM_01 ^ X1[2] ^ X1[3];
        t[1] = X1[0] ^ MDR_SBLOCK2->TRM_01 ^ MDR_SBLOCK3->TRM_02 ^ X1[3];
        t[2] = X1[0] ^ X1[1] ^ MDR_SBLOCK2->TRM_02 ^ MDR_SBLOCK3->TRM_03;
        t[3] = MDR_SBLOCK3->TRM_00 ^ X1[1] ^ X1[2] ^ MDR_SBLOCK2->TRM_03;
    }
    /* xor with last portion of the key */
    aesXorw4(t, expKey);

    /* transform from matrix */
    aesCpyw4(&MDR_PBIT1->TRM_00, (uint32_t*)t);
    aesCpyw4((uint32_t*)data, &MDR_PBIT1->TRM_00);
}

/**
 *  @brief  block decryption with AES, C-implementation
 *  @param  data [in/out] - data block to be decrypted, 16 bytes
 *  @param  expKey [in] - expanded key
 *  @param  type - member of @AesType to indicate length of the key, valid AES128, AES192, AES256
 */
static inline void aesDecBlockC(uint8_t* data, uint32_t* expKey, uint32_t type)
{
    uint32_t wState[4];

    /* transform to matrix */
    aesCpyw4(&MDR_PBIT0->TRM_00, (uint32_t*)data);
    aesCpyw4(wState, &MDR_PBIT0->TRM_00);

    // Add the First round key to the state before starting the rounds.
    type >>= 5;
    type += 6;
    expKey += type * 4;

    aesXorw4(wState, expKey);

    // actual crypto conversion
    while (1)
    {
        // inv shift rows
        aesCpyw4(&MDR_PBIT3->TRM_00, wState);
        aesCpyw4(wState, &MDR_PBIT3->TRM_00);

        // in s-box
        aesCpyw4(&MDR_SBLOCK1->TRM_00, wState);
        aesCpyw4(wState, &MDR_SBLOCK1->TRM_00);

        expKey -= 4;

        aesXorw4(wState, expKey);

        type--;
        if (type == 0) {
            break;
        }

        // inv mix columns
        // X9
        aesCpyw4(&MDR_SBLOCK4->TRM_00, wState);
        // XB
        aesCpyw4(&MDR_SBLOCK5->TRM_00, wState);
        // XD
        aesCpyw4(&MDR_SBLOCK6->TRM_00, wState);
        // XE
        aesCpyw4(&MDR_SBLOCK7->TRM_00, wState);
        wState[0] = MDR_SBLOCK7->TRM_00 ^ MDR_SBLOCK5->TRM_01 ^ MDR_SBLOCK6->TRM_02 ^ MDR_SBLOCK4->TRM_03;
        wState[1] = MDR_SBLOCK4->TRM_00 ^ MDR_SBLOCK7->TRM_01 ^ MDR_SBLOCK5->TRM_02 ^ MDR_SBLOCK6->TRM_03;
        wState[2] = MDR_SBLOCK6->TRM_00 ^ MDR_SBLOCK4->TRM_01 ^ MDR_SBLOCK7->TRM_02 ^ MDR_SBLOCK5->TRM_03;
        wState[3] = MDR_SBLOCK5->TRM_00 ^ MDR_SBLOCK6->TRM_01 ^ MDR_SBLOCK4->TRM_02 ^ MDR_SBLOCK7->TRM_03;
    }

    // The decryption process is over. Copy the state array to output array.
    aesCpyw4(&MDR_PBIT1->TRM_00, (uint32_t*)wState);
    aesCpyw4((uint32_t*)data, &MDR_PBIT1->TRM_00);
}

#endif /* CRYPTO_AES_C */

/** @} */ /* End of group CRYPTOAES_Private_Functions */

/** @} */ /* End of group CRYPTOAES */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_cryptoAes.c
  */

