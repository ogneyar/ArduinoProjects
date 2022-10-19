/**
  * FILE MLDR187_cryptoKuz.c
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_crypto.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_CRYPTOKUZ_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup CRYPTOKUZ
  * @{
  */


/** @defgroup CRYPTOKUZ_Private_Constants
  * @{
  */

static const uint8_t g_KuzPi[256] = {
    0xFC, 0xEE, 0xDD, 0x11, 0xCF, 0x6E, 0x31, 0x16,    0xFB, 0xC4, 0xFA, 0xDA, 0x23, 0xC5, 0x04, 0x4D,     /* 00..0F */
    0xE9, 0x77, 0xF0, 0xDB, 0x93, 0x2E, 0x99, 0xBA,    0x17, 0x36, 0xF1, 0xBB, 0x14, 0xCD, 0x5F, 0xC1,     /* 10..1F */
    0xF9, 0x18, 0x65, 0x5A, 0xE2, 0x5C, 0xEF, 0x21,    0x81, 0x1C, 0x3C, 0x42, 0x8B, 0x01, 0x8E, 0x4F,     /* 20..2F */
    0x05, 0x84, 0x02, 0xAE, 0xE3, 0x6A, 0x8F, 0xA0,    0x06, 0x0B, 0xED, 0x98, 0x7F, 0xD4, 0xD3, 0x1F,     /* 30..3F */
    0xEB, 0x34, 0x2C, 0x51, 0xEA, 0xC8, 0x48, 0xAB,    0xF2, 0x2A, 0x68, 0xA2, 0xFD, 0x3A, 0xCE, 0xCC,     /* 40..4F */
    0xB5, 0x70, 0x0E, 0x56, 0x08, 0x0C, 0x76, 0x12,    0xBF, 0x72, 0x13, 0x47, 0x9C, 0xB7, 0x5D, 0x87,     /* 50..5F */
    0x15, 0xA1, 0x96, 0x29, 0x10, 0x7B, 0x9A, 0xC7,    0xF3, 0x91, 0x78, 0x6F, 0x9D, 0x9E, 0xB2, 0xB1,     /* 60..6F */
    0x32, 0x75, 0x19, 0x3D, 0xFF, 0x35, 0x8A, 0x7E,    0x6D, 0x54, 0xC6, 0x80, 0xC3, 0xBD, 0x0D, 0x57,     /* 70..7F */
    0xDF, 0xF5, 0x24, 0xA9, 0x3E, 0xA8, 0x43, 0xC9,    0xD7, 0x79, 0xD6, 0xF6, 0x7C, 0x22, 0xB9, 0x03,     /* 80..8F */
    0xE0, 0x0F, 0xEC, 0xDE, 0x7A, 0x94, 0xB0, 0xBC,    0xDC, 0xE8, 0x28, 0x50, 0x4E, 0x33, 0x0A, 0x4A,     /* 90..9F */
    0xA7, 0x97, 0x60, 0x73, 0x1E, 0x00, 0x62, 0x44,    0x1A, 0xB8, 0x38, 0x82, 0x64, 0x9F, 0x26, 0x41,     /* A0..AF */
    0xAD, 0x45, 0x46, 0x92, 0x27, 0x5E, 0x55, 0x2F,    0x8C, 0xA3, 0xA5, 0x7D, 0x69, 0xD5, 0x95, 0x3B,     /* B0..BF */
    0x07, 0x58, 0xB3, 0x40, 0x86, 0xAC, 0x1D, 0xF7,    0x30, 0x37, 0x6B, 0xE4, 0x88, 0xD9, 0xE7, 0x89,     /* C0..CF */
    0xE1, 0x1B, 0x83, 0x49, 0x4C, 0x3F, 0xF8, 0xFE,    0x8D, 0x53, 0xAA, 0x90, 0xCA, 0xD8, 0x85, 0x61,     /* D0..DF */
    0x20, 0x71, 0x67, 0xA4, 0x2D, 0x2B, 0x09, 0x5B,    0xCB, 0x9B, 0x25, 0xD0, 0xBE, 0xE5, 0x6C, 0x52,     /* E0..EF */
    0x59, 0xA6, 0x74, 0xD2, 0xE6, 0xF4, 0xB4, 0xC0,    0xD1, 0x66, 0xAF, 0xC2, 0x39, 0x4B, 0x63, 0xB6      /* F0..FF */
};

static const uint8_t g_KuzPiM1[256] = {
    0xA5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0,    0x54, 0xE6, 0x9E, 0x39, 0x55, 0x7E, 0x52, 0x91,     /* 00..0F */
    0x64, 0x03, 0x57, 0x5A, 0x1C, 0x60, 0x07, 0x18,    0x21, 0x72, 0xA8, 0xD1, 0x29, 0xC6, 0xA4, 0x3F,     /* 10..1F */
    0xE0, 0x27, 0x8D, 0x0C, 0x82, 0xEA, 0xAE, 0xB4,    0x9A, 0x63, 0x49, 0xE5, 0x42, 0xE4, 0x15, 0xB7,     /* 20..2F */
    0xC8, 0x06, 0x70, 0x9D, 0x41, 0x75, 0x19, 0xC9,    0xAA, 0xFC, 0x4D, 0xBF, 0x2A, 0x73, 0x84, 0xD5,     /* 30..3F */
    0xC3, 0xAF, 0x2B, 0x86, 0xA7, 0xB1, 0xB2, 0x5B,    0x46, 0xD3, 0x9F, 0xFD, 0xD4, 0x0F, 0x9C, 0x2F,     /* 40..4F */
    0x9B, 0x43, 0xEF, 0xD9, 0x79, 0xB6, 0x53, 0x7F,    0xC1, 0xF0, 0x23, 0xE7, 0x25, 0x5E, 0xB5, 0x1E,     /* 50..5F */
    0xA2, 0xDF, 0xA6, 0xFE, 0xAC, 0x22, 0xF9, 0xE2,    0x4A, 0xBC, 0x35, 0xCA, 0xEE, 0x78, 0x05, 0x6B,     /* 60..6F */
    0x51, 0xE1, 0x59, 0xA3, 0xF2, 0x71, 0x56, 0x11,    0x6A, 0x89, 0x94, 0x65, 0x8C, 0xBB, 0x77, 0x3C,     /* 70..7F */
    0x7B, 0x28, 0xAB, 0xD2, 0x31, 0xDE, 0xC4, 0x5F,    0xCC, 0xCF, 0x76, 0x2C, 0xB8, 0xD8, 0x2E, 0x36,     /* 80..8F */
    0xDB, 0x69, 0xB3, 0x14, 0x95, 0xBE, 0x62, 0xA1,    0x3B, 0x16, 0x66, 0xE9, 0x5C, 0x6C, 0x6D, 0xAD,     /* 90..9F */
    0x37, 0x61, 0x4B, 0xB9, 0xE3, 0xBA, 0xF1, 0xA0,    0x85, 0x83, 0xDA, 0x47, 0xC5, 0xB0, 0x33, 0xFA,     /* A0..AF */
    0x96, 0x6F, 0x6E, 0xC2, 0xF6, 0x50, 0xFF, 0x5D,    0xA9, 0x8E, 0x17, 0x1B, 0x97, 0x7D, 0xEC, 0x58,     /* B0..BF */
    0xF7, 0x1F, 0xFB, 0x7C, 0x09, 0x0D, 0x7A, 0x67,    0x45, 0x87, 0xDC, 0xE8, 0x4F, 0x1D, 0x4E, 0x04,     /* C0..CF */
    0xEB, 0xF8, 0xF3, 0x3E, 0x3D, 0xBD, 0x8A, 0x88,    0xDD, 0xCD, 0x0B, 0x13, 0x98, 0x02, 0x93, 0x80,     /* D0..DF */
    0x90, 0xD0, 0x24, 0x34, 0xCB, 0xED, 0xF4, 0xCE,    0x99, 0x10, 0x44, 0x40, 0x92, 0x3A, 0x01, 0x26,     /* E0..EF */
    0x12, 0x1A, 0x48, 0x68, 0xF5, 0x81, 0x8B, 0xC7,    0xD6, 0x20, 0x0A, 0x08, 0x00, 0x4C, 0xD7, 0x74      /* F0..FF */
};

static const uint8_t kB[16] = { 0x94, 0x20, 0x85, 0x10, 0xC2, 0xC0, 0x01, 0xFB,  0x01, 0xC0, 0xC2, 0x10, 0x85, 0x20, 0x94, 0x01 };

/** @} */ /* End of group CRYPTOKUZ_Private_Constants */

/** @defgroup CRYPTOKUZ_Private_Functions_Declarations
  * @{
  */

/**
  * @brief  Galois field multiplication
  * @param  x - first multiplier
  * @param  y - second multiplier
  * @return multiplication result
  */
static uint8_t kuzMulGF256_1(uint8_t x, uint8_t y);

#ifdef CRYPTO_KUZNECHIK_C

/**
  *  @breif  C-implementation of the Kuznechik key expansion algorithm
  *  @param  key - pointer to key in normal big-endian format
  *  @param  expKey - pointer to expanded key in little-endian format
  */
void kuzExpandKeyC(uint8_t* key, uint32_t* expKey);

/**
  *  @breif  C-implementation of the Kuznechik encryption
  *  @param  expKey - pointer to expanded key in little-endian format
  *  @param  inout - pointer to input / output data in normal big-endian format
  */
static void kuzBlockEncC(uint32_t* expKey, uint32_t* inout);

/**
  *  @breif  C-implementation of the Kuznechik decryption
  *  @param  expKey - pointer to expanded key in little-endian format
  *  @param  inout - pointer to input / output data in normal big-endian format
  */
static void kuzBlockDecC(uint32_t* expKey, uint32_t* inout);

/**
  * @brief  common part of the kuznechik algorithm encryption (C-implementation)
  * @param  expKey - pointer to first block of the expanded key (first for encryption, last for decryption)
  *         (40 words = 160 bytes) in CPU little-endian format
  * @param  inout - pointer to input/output data block in CPU little-endian format
  * @param  sBoxPtr - pointer to selected (direct / inverted) S-box block
  * @param  koffs - expanded key step offset (-4 for decryption, +4 for encryption)
  */
static void kuzBlockCommon(uint32_t* expKey, uint32_t* inout, __IO uint32_t* sBoxPtr, int8_t koffs);

/**
  *  @breif  C-implementation of the byte order swap algorithm
  *  @param  sw - pointer to value in memory to be endians-switched
  */
static void u32swapinplace4(uint32_t* sw);

/**
  * @brief  L and L-1 op
  *         to select L or L-1 configure direction within SETUP register
  * @param  t - pointer to temporary value
  */
static void kuzLBlock(uint32_t* t);

/**
  * @breif  S-Box transformation
  * @param  sblock - pointer to SBLOCK that should be used
  * @param  data - pointer to data block
  */
static void kuzSBox(__IO uint32_t* sblock, uint32_t* data);

#else /* CRYPTO_KUZNECHIK_ASM */

/**
  *  @breif  ASM-implementation of the Kuznechik key expansion algorithm
  *  @param  key - pointer to key in normal big-endian format
  *  @param  expKey - pointer to expanded key in little-endian format
  */
void kuzExpandKeyAsm(uint8_t* key, uint32_t* expKey);

/**
  *  @brief  link to ASM-implementation of the Kuznechik encryption
  *  @param  expKey - pointer to expanded key in little-endian format
  *  @param  inout - pointer to input / output data in normal big-endian format
  */
extern void kuzBlockEncAsm(uint32_t* expKey, uint32_t* inout);

/**
  *  @brief  link to ASM-implementation of the Kuznechik decryption
  *  @param  expKey - pointer to expanded key in little-endian format
  *  @param  inout - pointer to input / output data in normal big-endian format
  */
extern void kuzBlockDecAsm(uint32_t* expKey, uint32_t* inout);

#endif /* CRYPTO_KUZNECHIK_C */

/** @} */ /* End of group CRYPTOKUZ_Private_Functions_Declarations */

/** @defgroup CRYPTOKUZ_Exported_Functions
  * @{
  */

/**
 *  @brief  initialize GOST R34.12-2015 (Kuznechik) processing
 *          should be called only once before any number of Kuznechik operations
 *          if any user code re-init L-block, S-block#1/2 or P-byte co-processors (for example,
 *          other cipher initialization is called), update could be required
 */
void kuzInitCCPU(void)
{
    uint32_t i, j, k;
    uint32_t tmp[4];

    /* L-block */
    MDR_LBLOCK->SETUP = 0;
    for (i = 0; i < 256; i++)
    {
        memset((uint8_t*)tmp, (uint8_t)i, 16);
        MDR_LBLOCK->TRM_00 = tmp[0];
        MDR_LBLOCK->TRM_01 = tmp[1];
        MDR_LBLOCK->TRM_02 = tmp[2];
        MDR_LBLOCK->TRM_03 = tmp[3];
        for (j = 0; j < 4; j++)
        {
            tmp[j] = 0;
            for (k = 0; k < 4; k++)
            {
                tmp[j] |= (kuzMulGF256_1((uint8_t)i, kB[((3 - j) << 2) + (3 - k)]) << (k << 3));
            }
        }
        MDR_LBLOCK->TABLE_CNG_00 = tmp[0];
        MDR_LBLOCK->TABLE_CNG_01 = tmp[1];
        MDR_LBLOCK->TABLE_CNG_02 = tmp[2];
        MDR_LBLOCK->TABLE_CNG_03 = tmp[3];
    }

    /* S-blocks */
    for (i = 0; i < 256; i++)
    {
        memset((uint8_t*)&tmp[0], (uint8_t)i, 4);
        memset((uint8_t*)&tmp[1], g_KuzPi[i], 4);
        memset((uint8_t*)&tmp[2], g_KuzPiM1[i], 4);

        /* encryption */
        MDR_SBLOCK0->TRM_00 = tmp[0];
        MDR_SBLOCK0->TABLE_CHG = tmp[1];

        /* decryption */
        MDR_SBLOCK1->TRM_00 = tmp[0];
        MDR_SBLOCK1->TABLE_CHG = tmp[2];
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
 *  @brief  key expansion for Kuznechik processing
 *          approximate performance (depends on compiler):
 *          5600  CPU clock cycles - ASM implementation
 *          24140 CPU clock cycles - C implementation
 *          to select implementation use definitions above
 *  @param  key [in] - pointer to compressed key
 *  @param  expKey [out] - pointer to store expanded key in system little-endian format
 */
void kuzExpandKey(uint8_t* key, uint32_t* expKey)
{
#ifdef CRYPTO_KUZNECHIK_C
    kuzExpandKeyC(key, expKey);
#else
    kuzExpandKeyAsm(key, expKey);
#endif
}

/**
 *  @brief  block encryption with Kuznechik
 *          approximate performance (depends on compiler):
 *          920  CPU clock cycles - ASM implementation
 *          2700 CPU clock cycles - C implementation
 *          to select implementation use definitions above
 *  @param  data [in/out] - data block to be encrypted, 16 bytes
 *  @param  expKey [in] - expanded key in system little-endian format
 */
void kuzEncBlock(uint8_t* data, uint32_t* expKey)
{
#ifdef CRYPTO_KUZNECHIK_C
    kuzBlockEncC(expKey, (uint32_t*)data);
#else
    kuzBlockEncAsm(expKey, (uint32_t*)data);
#endif
}

/**
 *  @brief  block decryption with Kuznechik
 *          approximate performance (depends on compiler):
 *          920  CPU clock cycles - ASM implementation
 *          2700 CPU clock cycles - C implementation
 *          to select implementation use definitions above
 *  @param  data [in/out] - data block to be decrypted, 16 bytes
 *  @param  expKey [in] - expanded key in system little-endian format
 */
void kuzDecBlock(uint8_t* data, uint32_t* expKey)
{
#ifdef CRYPTO_KUZNECHIK_C
    kuzBlockDecC(expKey, (uint32_t*)data);
#else
    kuzBlockDecAsm(expKey, (uint32_t*)data);
#endif
}


/** @} */ /* End of group CRYPTOKUZ_Exported_Functions */

/** @defgroup CRYPTOKUZ_Private_Functions
  * @{
  */

/**
  * @brief  Galois field multiplication
  * @param  x - first multiplier
  * @param  y - second multiplier
  * @return multiplication result
  */
static uint8_t kuzMulGF256_1(uint8_t x, uint8_t y)
{
    uint8_t z = 0;
    while (y != 0)
    {
        if ((y & 1) != 0)
        {
            z = z ^ x;
        }
        x = (x << 1) ^ (x & 0x80 ? 0xC3 : 0x00);
        y = y >> 1;
    }
    return z;
};



#ifdef CRYPTO_KUZNECHIK_C

/**
  *  @breif  C-implementation of the Kuznechik key expansion algorithm
  *  @param  key - pointer to key in normal big-endian format
  *  @param  expKey - pointer to expanded key in little-endian format
  */
void kuzExpandKeyC(uint8_t* key, uint32_t* expKey)
{
    uint32_t t[4];
    uint8_t j, i, k;

    memcpy((uint8_t*)expKey, key, 32);
    u32swapinplace4(expKey + 0);
    u32swapinplace4(expKey + 4);

    MDR_LBLOCK->SETUP = 0x10;

    for (j = 0; j < 32; j += 8)
    {
        memcpy((uint8_t*)(expKey + j + 8), (uint8_t*)(expKey + j), 32);

        for (i = 1; i < 9; i++)
        {
            // func C
            t[0] = 0;
            t[1] = 0;
            t[2] = 0;
            t[3] = j + i;

            // L
            kuzLBlock(t);

            for (k = 0; k < 4; k++) {
                t[k] ^= expKey[j + 8 + k];
            }

            kuzSBox(&MDR_SBLOCK0->TRM_00, t);
            kuzLBlock(t);

            for (k = 0; k < 4; k++) {
                t[k] ^= expKey[j + 12 + k];
            }

            memcpy((uint8_t*)(expKey + j + 12), (uint8_t*)(expKey + j + 8), 16);
            memcpy((uint8_t*)(expKey + j + 8), (uint8_t*)t, 16);
        }
    }
}

/**
  *  @breif  C-implementation of the Kuznechik encryption
  *  @param  expKey - pointer to expanded key in little-endian format
  *  @param  inout - pointer to input / output data in normal big-endian format
  */
static void kuzBlockEncC(uint32_t* expKey, uint32_t* inout)
{
    MDR_LBLOCK->SETUP = 16 + LBLOCK_SETUP_DIRECT;

    kuzBlockCommon(expKey, inout, &MDR_SBLOCK0->TRM_00, 4);
}

/**
  *  @breif  C-implementation of the Kuznechik decryption
  *  @param  expKey - pointer to expanded key in little-endian format
  *  @param  inout - pointer to input / output data in normal big-endian format
  */
static void kuzBlockDecC(uint32_t* expKey, uint32_t* inout)
{
    MDR_LBLOCK->SETUP = 16 + LBLOCK_SETUP_INVERSE; // 65552

    kuzBlockCommon(expKey + 9 * 4, inout, &MDR_SBLOCK1->TRM_00, -4);
}

/**
  * @brief  common part of the kuznechik algorithm encryption (C-implementation)
  * @param  expKey - pointer to first block of the expanded key (first for encryption, last for decryption)
  *         (40 words = 160 bytes) in CPU little-endian format
  * @param  inout - pointer to input/output data block in CPU little-endian format
  * @param  sBoxPtr - pointer to selected (direct / inverted) S-box block
  * @param  koffs - expanded key step offset (-4 for decryption, +4 for encryption)
  */
static void kuzBlockCommon(uint32_t* expKey, uint32_t* inout, __IO uint32_t* sBoxPtr, int8_t koffs)
{
    uint32_t t[4];
    uint8_t i;

    u32swapinplace4(inout);
    t[0] = inout[0];
    t[1] = inout[1];
    t[2] = inout[2];
    t[3] = inout[3];
    i = 9;
    while (1) {
        t[0] ^= expKey[0];
        t[1] ^= expKey[1];
        t[2] ^= expKey[2];
        t[3] ^= expKey[3];
        expKey += koffs;

        if (i == 0) {
            break;
        }
        i--;

        if (koffs > 0) {
            /* S-box */
            kuzSBox(sBoxPtr, t);
        }

        /* L and L-1 ops */
        kuzLBlock(t);

        if (koffs < 0) {
            /* S-box */
            kuzSBox(sBoxPtr, t);
        }
    }

    inout[0] = t[0];
    inout[1] = t[1];
    inout[2] = t[2];
    inout[3] = t[3];
    u32swapinplace4(inout);
}

/**
  *  @breif  C-implementation of the byte order swap algorithm
  *  @param  sw - pointer to value in memory to be endians-switched
  */
static void u32swapinplace4(uint32_t* sw) {
    MDR_PBYTE->TRM_00 = sw[0];
    sw[0] = MDR_PBYTE->TRM_00;
    MDR_PBYTE->TRM_01 = sw[1];
    sw[1] = MDR_PBYTE->TRM_01;
    MDR_PBYTE->TRM_02 = sw[2];
    sw[2] = MDR_PBYTE->TRM_02;
    MDR_PBYTE->TRM_03 = sw[3];
    sw[3] = MDR_PBYTE->TRM_03;
}

/**
  * @brief  L and L-1 op
  *         to select L or L-1 configure direction within SETUP register
  * @param  t - pointer to temporary value
  */
static void kuzLBlock(uint32_t* t)
{
    /* load data to transformation registers */
    MDR_LBLOCK->TRM_00 = t[3];
    MDR_LBLOCK->TRM_01 = t[2];
    MDR_LBLOCK->TRM_02 = t[1];
    MDR_LBLOCK->TRM_03 = t[0];

    /* wait while data is proceeding */
    while ((MDR_LBLOCK->SETUP & LBLOCK_SETUP_GET_R_LEFT_Msk) != 0) { ; }

    /* read data from transformation registers */
    t[3] = MDR_LBLOCK->TRM_00;
    t[2] = MDR_LBLOCK->TRM_01;
    t[1] = MDR_LBLOCK->TRM_02;
    t[0] = MDR_LBLOCK->TRM_03;
}

/**
  * @breif  S-Box transformation
  * @param  sblock - pointer to SBLOCK that should be used
  * @param  data - pointer to data block
  */
static void kuzSBox(__IO uint32_t* sblock, uint32_t* data) {
    sblock[0] = data[0];
    sblock[1] = data[1];
    sblock[2] = data[2];
    sblock[3] = data[3];
    data[0] = sblock[0];
    data[1] = sblock[1];
    data[2] = sblock[2];
    data[3] = sblock[3];
}

#endif /* CRYPTO_KUZNECHIK_C */

/** @} */ /* End of group CRYPTOKUZ_Private_Functions */

/** @} */ /* End of group CRYPTOKUZ */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_cryptoKuz.c
  */

