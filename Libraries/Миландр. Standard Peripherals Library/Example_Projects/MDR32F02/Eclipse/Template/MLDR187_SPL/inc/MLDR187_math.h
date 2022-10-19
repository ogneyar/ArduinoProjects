/**
  * FILE MLDR187_math.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SPL_INC_MLDR187_MATH_H_
#define SPL_INC_MLDR187_MATH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup MATH
  * @{
  */

/** @defgroup MATH_Exported_Types
  * @{
  */

/** @} */ /* End of group MATH_Exported_Types */

/** @defgroup MATH_Exported_Constants
  * @{
  */

/* tables are actually located within MLDR187_mathTables.c */
extern const uint16_t MATH_fftReorderTbl[];
extern const int32_t MATH_fftCosSinLookupTable[];
extern const int32_t MATH_TABLE_SIN_PREC[];

/** @} */ /* End of group MATH_Exported_Constants */

/** @defgroup MATH_Exported_Macros
  * @{
  */

/* selection between ASM and C implementation of the FFT */
#define MATH_FFTC_ASM
#ifndef MATH_FFTC_ASM
#define MATH_FFTC_C
#endif

/* selection between ASM and C implementation of the sqrt(x^2 + y^2) calculation */
#define MATH_SQRT2P2_ASM
#ifndef MATH_SQRT2P2_ASM
#define MATH_SQRT2P2_C
#endif

/** @} */ /* End of group MATH_Exported_Macros */

/** @defgroup MATH_Exported_Functions
  * @{
  */

/**
  * @brief  absolute value calculation
  * @param  x - signed value
  * @return absolute value of the x
  */
int32_t MATH_ABS(int32_t x);

/**
  * @brief  Newton algorithm of Sqrt(q) calculation
            This function do Sqrt calculation for q with s as first approximation
  * @param  q: argument for sqrt calculation
  * @param  s: first approximation
  * @return Sqrt(q)
  */
int32_t MATH_SQRT(int64_t q, int32_t s);

/**
  * @brief  Oversample input data flow to another rate
  * @param  in - pointer to input data buffer
  * @param  inLen - number of items within input buffer
  * @param  out - pointer to output data buffer
  * @param  outLen - number of items within output buffer
  */
void MATH_oversample(int32_t* in, int32_t inLen, int32_t* out, int32_t outLen);

/**
 *  @brief  radix 2 butterfly implementation of the Fast Fourier Transform
 *          use MATH_FFTC_C / MATH_FFTC_ASM defines to switch between ASM and C implementation
 *          approximate performance (depends on compiler):
 *          numb.of points | ASM cycles / ms @60MHz | C cycles / ms @60MHz
 *                      64 |         8K / 0.13      |      50K / 0.83
 *                     128 |        18K / 0.3       |     120K / 2.0
 *                     256 |        40K / 0.66      |     290K / 4.8
 *                     512 |        90K / 1.5       |     650K / 10.8
 *                    1024 |       200K / 3.3       |    1450K / 24.2
 *                    2048 |       440K / 7.3       |    3200K / 53.3
 *
  * @param  pSrc - pointer to source / destination (in-place) data
  * @param  fftLen - number of points
 */
void MATH_FFT(int32_t * pSrc, uint32_t fftLen);

/**
  * @brief  calculate magnitudes for array of complex values
  *         use MATH_SQRT2P2_C and MATH_SQRT2P2_ASM defines to select between C and ASM implementation
  * @param  pSrc - pointer to source data
  * @param  pDst - pointer to destination data
  * @param  numSamples - number of points
  */
void MATH_ComplexMagnitude(const int32_t * pSrc, int32_t * pDst, uint32_t numSamples);

/**
  * @brief  Ku calculation (in scale of 0.01%) by Newton algorithm of Sqrt calculation for sum x[i]^2, i=1..N-1
  *         This function do Sqrt calculation for sum x[1]^2+...+x[N-1]^2 by Newton method using x[1] or x[2]
  *         as first approximation, then calulate integer value of Ku in scale of 0.01% by dividing result of Sqrt to x[0]
  * @param  x: pointer to array of frequency components of signal
  * @param  N: number of max frequency component to calculate
  * @return harmonic distorsion Koefficient K=10000*Sqrt(x[1]^2+...+x[N-1]^2)/x[0]
  */
int32_t MATH_KhdCalc(int32_t* x, int32_t N);

/**
  * @brief  Calculate the TRUE RMS value of voltage
  *         NOTE: this function is optimized to work with up to 24-bit input values,
  *         if 32-bit input values is used, overflow should be checked
  * @param  in - Input buffer pointer
  * @param  Num - Number of values for processing (size of buffer), <= 65535
  * @return True RMS value
  */
int32_t MATH_TrueRMS(int32_t* in, int32_t Num);

/**
  * @brief  Triangle side length calculation using 2 sides length and angle alfa
  *         This function do Triangle side calculation using 2 sides and angle alfa
  *         by formula Sqrt(b^2+c^2-2*b*c*cos(alfa))
  * @param  b: first side integer parameter
  * @param  c: second side integer parameter
  * @param  alfa: angle integer parameter in interval [-180, 180]
  * @return Sqrt(b^2+c^2-2*b*c*cos(alfa))
  */
int32_t MATH_TriangleSideCalc(int32_t b, int32_t c, int32_t alfa);

/**
  * @brief  Arctan calculation for ratio x/y
  *         This function calling while UI phase angle calculation (arguments is active and reactive power)
  * @param  x: integer argument
  * @param  y: integer argument
  * @return arctan(x/y) in hundreds of degree unit
  */
int32_t MATH_arcTan(int32_t x, int32_t y);

/** @} */ /* End of group MATH_Exported_Functions */

/** @} */ /* End of group MATH */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* SPL_INC_MLDR187_MATH_H_ */

/**
  * END OF FILE MLDR187_math.h
  */

