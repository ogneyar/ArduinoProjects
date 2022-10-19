/**
  * FILE MLDR187_math.c
  */

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include "MLDR187_math.h"
#include <stdlib.h>

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup MATH
  * @{
  */

/** @defgroup MATH_Private_Constants_Declarations
  * @{
  */

/* integer equivalent of float value 1.00000, the value means 26-bit accuracy of sine calculation */
#define MATH_INT_SCALE          0x04000000l
/* integer equivalent of float value 2*3.1415926 in angles calculation */
#define MATH_ANGLE_SCALE_2PI    0x10000000l
/* integer equivalent of float value 3.1415926 in angles calculation */
#define MATH_ANGLE_SCALE_PI     0x08000000l
/* integer equivalent of float value 3.1415926/2 in angles calculation */
#define MATH_ANGLE_SCALE_PI2    0x04000000l
/* conversion factor to find table index = ANGLE_SCALE_PI2/TABLE_QUARTER_PERIOD */
#define TABLE_INDEX_FACTOR      0x00008000l
/* conversion factor to find table index in Right Shift Units */
#define MATH_TABLE_INDEX_RSU    15

/** @} */ /* End of group MATH_Private_Constants_Declarations */

/** @defgroup MATH_Private_Functions_Declarations
  * @{
  */

#ifdef MATH_FFTC_C

/**
  * @brief  C radix 2 butterfly implementation of the Fast Fourier Transform  *
  * @param  pSrc - pointer to source / destination (in-place) data
  * @param  fftLen - number of points
  * @param  cosSinTable - pointer to lookup table with cos and sin values
  * @param  reorderTbl - pointer to reorder indexes lookup table
  */
void MATH_FFT_C(int32_t* pSrc, uint32_t fftLen, const int32_t* cosSinTbl, const uint16_t* reorderTbl);

#else /* MATH_FFTC_ASM */

/**
  * @brief  ASM radix 2 butterfly implementation of the Fast Fourier Transform
  * @param  pSrc - pointer to source / destination (in-place) data
  * @param  fftLen - number of points
  * @param  cosSinTable - pointer to lookup table with cos and sin values
  * @param  reorderTbl - pointer to reorder indexes lookup table
  */
void MATH_FFT_ASM(int32_t* pSrc, uint32_t fftLen, const int32_t* cosSinTbl, const uint16_t* reorderTbl);

#endif /* MATH_FFTC_C */

#ifdef MATH_SQRT2P2_C
/**
  * @brief  calculate SQRT (X^2 + Y^2) with 64-bit precision using Newton algorithm
  * @param  x - first operand
  * @param  y - second operand
  * @return SQRT(X^2 + Y^2)
  */
int32_t MATH_sqrtX2pY2(int32_t x, int32_t y);

#else /* MATH_SQRT2P2_C */
/**
 *  @brief  ASM implementation of the SQRT(x^2 + y^2) calculation
 *  @param  x - operand 1
 *  @param  y - operand 2
 *  @return SQRT(x^2 + y^2)
 */
int32_t MATH_sqrtX2pY2FastASM(int32_t x, int32_t y);

#endif /* MATH_SQRT2P2_C */

/**
  * @brief  Fast sine calculation using interpolation of table values
  * @note   This function calling while DFT calculations
  * @param  alfaP: integer argument of sine in interval [0, ANGLE_SCALE_2PI) converted to
  *         interval 0 <= alfaP < 2*PI in calculations
  * @return sin(2*PI*alfaP/ANGLE_SCALE_2PI)*INT_SCALE - sine of alfaP value multiplied to INT_SCALE
  */
int32_t MATH_FastSinA(int32_t alfaP);

/**
  * @brief  Fast cosine calculation using interpolation of table values
  * @note   This function calling while DFT calculations
  * @param  alfaP: integer argument of cosine in interval [0, ANGLE_SCALE_2PI) converted to
  *         interval 0 <= alfaP < 2*PI in calculations
  * @return cos(2*PI*alfaP/ANGLE_SCALE_2PI)*INT_SCALE - cosine of alfaP value multiplied to INT_SCALE
  */
int32_t MATH_FastCosA(int32_t alfaP);

/**
  * @breif  float implemenation of the arctg() calculation
  * @param  x - tg value
  * @return arctg(x)
  */
float MATH_AtanF(float x);

/** @} */ /* End of group MATH_Private_Functions_Declarations */

/** @defgroup MATH_Exported_Functions
  * @{
  */

/**
  * @brief  absolute value calculation
  * @param  x - signed value
  * @return absolute value of the x
  */
int32_t MATH_ABS(int32_t x)
{
    if (x < 0) {
        x = -x;
    }
    return x;
}

/**
  * @brief  Newton algorithm of Sqrt(q) calculation
            This function do Sqrt calculation for q with s as first approximation
  * @param  q: argument for sqrt calculation
  * @param  s: first approximation
  * @return Sqrt(q)
  */
int32_t MATH_SQRT(int64_t q, int32_t s)
{
    int32_t tmp, d, q32;

    /* first approximation should be non-zero */
    if (s == 0) {
        s = q / 2;
    }

    /* Newton algorithm */
    tmp = 0;
    q32 = (uint32_t)(q >> 32);
    if (q32 != 0) {
        /* 64-bit calculation */
        while (1) {
            tmp = (s + q / s) / 2;
            // calc positive difference with previous step
            if (tmp > s) {
                d = tmp - s;
            }
            else
            {
                d = s - tmp;
            }
            // exit condition
            if (d < 2) {
                break;
            }

            s = tmp;
        }

    } else if (q != 0) {
        /* 32-bit calculation */
        q32 = (uint32_t)q;
        while (1) {
            tmp = (s + q32 / s) / 2;
            // calc positive difference with previous step
            if (tmp > s) {
                d = tmp - s;
            }
            else
            {
                d = s - tmp;
            }
            // exit condition
            if (d < 2) {
                break;
            }

            s = tmp;
        }
    }

    return tmp;
}

/**
  * @brief  Oversample input data flow to another rate
  * @param  in - pointer to input data buffer
  * @param  inLen - number of items within input buffer
  * @param  out - pointer to output data buffer
  * @param  outLen - number of items within output buffer
  */
void MATH_oversample(int32_t* in, int32_t inLen, int32_t* out, int32_t outLen)
{
    int32_t i, leftIdx, a, b;
    float resampleIdx, value;

    /* if input and output rates are the same, we should just copy data */
    if (inLen == outLen) {
        for (i = 0; i < outLen; i++) {
            out[i] = in[i];
        }
    }
    /* otherwise we should oversample data */
    else
    {
        /* first and last items always are same */
        out[0] = in[0];
        out[outLen - 1] = in[inLen - 1];

        /* all other items should be oversampled */
        for (i = 1; i < outLen - 1; i++)
        {
            resampleIdx = (float)i * (float)inLen / (float)outLen;
            leftIdx = (int32_t)resampleIdx;
            resampleIdx -= (float)leftIdx;
            a = in[leftIdx];
            b = in[leftIdx + 1];
            value = resampleIdx * (b - a) + a;
            out[i] = (int32_t)value;
        }
    }
}

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
void MATH_FFT(int32_t * pSrc, uint32_t fftLen)
{
#ifdef MATH_FFTC_C
    MATH_FFT_C(pSrc, fftLen, MATH_fftCosSinLookupTable, MATH_fftReorderTbl);
#else /* MATH_FFTC_C */
    MATH_FFT_ASM(pSrc, fftLen, MATH_fftCosSinLookupTable, MATH_fftReorderTbl);
#endif /* MATH_FFTC_C */
}

/**
  * @brief  calculate magnitudes for array of complex values
  *         use MATH_SQRT2P2_C and MATH_SQRT2P2_ASM defines to select between C and ASM implementation
  * @param  pSrc - pointer to source data
  * @param  pDst - pointer to destination data
  * @param  numSamples - number of points
  */
void MATH_ComplexMagnitude(const int32_t * pSrc, int32_t * pDst, uint32_t numSamples)
{
    while (numSamples > 0)
    {
        /* calculate Magnitude */
#ifdef MATH_SQRT2P2_C
        *pDst = MATH_sqrtX2pY2(pSrc[0], pSrc[1]);
#else /* MATH_SQRT2P2_C */
        *pDst = MATH_sqrtX2pY2FastASM(pSrc[0], pSrc[1]);
#endif /* MATH_SQRT2P2_C */

        pDst++;
        pSrc += 2;

        /* Decrement loop counter */
        numSamples--;
    }
}

/**
  * @brief  Ku calculation (in scale of 0.01%) by Newton algorithm of Sqrt calculation for sum x[i]^2, i=1..N-1
  *         This function do Sqrt calculation for sum x[1]^2+...+x[N-1]^2 by Newton method using x[1] or x[2]
  *         as first approximation, then calulate integer value of Ku in scale of 0.01% by dividing result of Sqrt to x[0]
  * @param  x: pointer to array of frequency components of signal
  * @param  N: number of max frequency component to calculate
  * @return harmonic distorsion Koefficient K=10000*Sqrt(x[1]^2+...+x[N-1]^2)/x[0]
  */
int32_t MATH_KhdCalc(int32_t* x, int32_t N) {
    int64_t q;
    int32_t s, i;

    q = 0;
    for (i = 1; i < N; i++) {
        q += (int64_t) x[i] * x[i];
    }

    s = labs(x[1]);  // first approximation of sqrt (x[1]^2+...+x[N-1]^2)

    if (s == 0)
        s = 1;  // in case when all x[i]==0

    return MATH_SQRT(q, s);
}

/**
  * @brief  Calculate the TRUE RMS value of voltage
  *         NOTE: this function is optimized to work with up to 24-bit input values,
  *         if 32-bit input values is used, overflow should be checked
  * @param  in - Input buffer pointer
  * @param  Num - Number of values for processing (size of buffer), <= 65535
  * @return True RMS value
  */
int32_t MATH_TrueRMS(int32_t* in, int32_t Num) {
    int64_t rms2 = 0;
    int32_t v, i;

    /* thus we have only 24-bit signed values, it's square could not reach 48-bit value,
     * so there is up to 16 additional bits within int64_t, so multiplication and addition could be
     * processed within overflow checks */

    /* calculate summ of the square roots */
    for (i = 0; i < Num; i++) {
        v = in[i];
        rms2 += v * v;
    }

    rms2 /= Num;
    v = MATH_SQRT(rms2, rms2 >> 1); // TODO can overflow
    return v;
}

/**
  * @brief  Triangle side length calculation using 2 sides length and angle alfa
  *         This function do Triangle side calculation using 2 sides and angle alfa
  *         by formula Sqrt(b^2+c^2-2*b*c*cos(alfa))
  * @param  b: first side integer parameter
  * @param  c: second side integer parameter
  * @param  alfa: angle integer parameter in interval [-180, 180]
  * @return Sqrt(b^2+c^2-2*b*c*cos(alfa))
  */
int32_t MATH_TriangleSideCalc(int32_t b, int32_t c, int32_t alfa)
{
    int64_t q;
    int32_t s, tmp;

    if (alfa < 0) {
        /* cosine is symmetrical */
        alfa *= -1;
    }
    /* convert to scale [0, ANGLE_SCALE_PI) */
    s = alfa * 0x000B60B6; /* ANGLE_SCALE_PI/180 */

    tmp = MATH_FastCosA(s);
    if (b > c) {
        tmp *= b;
        tmp /= MATH_INT_SCALE;
        tmp *= 2 * c;
    } else {
        tmp *= c;
        tmp /= MATH_INT_SCALE;
        tmp *= 2 * b;
    }

    q = (int64_t)b * b + (int64_t)c * c - tmp;
    s = 1 + (b + c) / 4;
    s = MATH_SQRT(q, s);

    return s;
}

/**
  * @brief  Arctan calculation for ratio x/y
  *         This function calling while UI phase angle calculation (arguments is active and reactive power)
  * @param  x: integer argument
  * @param  y: integer argument
  * @return arctan(x/y) in hundreds of degree unit
  */
int32_t MATH_arcTan(int32_t x, int32_t y)
{
    int32_t outputValue = 0;

    if (x == 0) {
        if (y > 0) {
            outputValue = 9000;
        } else if (y < 0) {
            outputValue = -9000;
        } else {
            outputValue = 0;
        }
    } else if (y == 0) {
        if (x < 0) {
            outputValue = 18000;
        }
    } else {
        float ratio, angle;
        ratio = (float) y / (float) x;
        angle = MATH_AtanF(ratio);
        angle *= 5729.5;
        outputValue = (int32_t) (angle + 0.5f);
        if (x < 0) {
            outputValue = (y < 0) ? outputValue - 18000 : 18000 + outputValue;
        }
    }
    return outputValue;
}

/** @} */ /* End of group MATH_Exported_Functions */

/** @defgroup MATH_Private_Functions
  * @{
  */

#ifdef MATH_FFTC_C

/**
  * @brief  C radix 2 butterfly implementation of the Fast Fourier Transform  *
  * @param  pSrc - pointer to source / destination (in-place) data
  * @param  fftLen - number of points
  * @param  cosSinTable - pointer to lookup table with cos and sin values
  * @param  reorderTbl - pointer to reorder indexes lookup table
  */
void MATH_FFT_C(int32_t* pSrc, uint32_t fftLen, const int32_t* cosSinTbl, const uint16_t* reorderTbl)
{
    uint32_t i, j, k;
    int32_t xt, yt, cosVal, sinVal, tmp1, tmp2;

    int32_t* lookupTable;
    int32_t lookupOffset;

    int32_t* fstPtr; /*<! pointer to element within source array */
    int32_t* scdPtr; /*<! pointer to element within source array */

    lookupOffset = (2048 << 1) / fftLen;
    lookupTable = (int32_t*)cosSinTbl;

    /* first phase */
    fstPtr = pSrc;
    scdPtr = &pSrc[fftLen];

    for (i = 0; i < (fftLen / 2); i++)
    {
        tmp1 = *fstPtr;
        tmp1 >>= 2;
        tmp2 = *scdPtr;
        tmp2 >>= 2;
        xt = tmp1 - tmp2;
        *fstPtr = (tmp1 + tmp2) >> 1;

        fstPtr++;
        scdPtr++;

        tmp1 = *fstPtr;
        tmp1 >>= 2;
        tmp2 = *scdPtr;
        tmp2 >>= 2;
        yt = tmp1 - tmp2;
        *fstPtr = (tmp1 + tmp2) >> 1;

        fstPtr++;
        scdPtr--;

        cosVal = *lookupTable;
        lookupTable++;
        sinVal = *lookupTable;
        lookupTable--;
        lookupTable += lookupOffset;

        tmp1 = (int32_t)(((int64_t)xt * cosVal) >> 32);
        tmp2 = (int32_t)(((int64_t)yt * sinVal) >> 32);
        *scdPtr = (tmp1 + tmp2);
        scdPtr++;

        tmp1 = (int32_t)(((int64_t)yt * cosVal) >> 32);
        tmp2 = (int32_t)(((int64_t)xt * sinVal) >> 32);
        *scdPtr = tmp1 - tmp2;
        scdPtr++;
    }

    /* middle phase */
    for (k = fftLen / 2; k > 2; k >>= 1)
    {
        lookupTable = (int32_t*)cosSinTbl;
        lookupOffset <<= 1;

        // loop for groups
        for (j = 0; j < (k / 2); j++)
        {
            cosVal = *lookupTable;
            lookupTable++;
            sinVal = *lookupTable;
            lookupTable--;
            lookupTable += lookupOffset;

            // loop for butterfly
            fstPtr = &pSrc[2 * j];
            for (i = j; i < fftLen; i += k)
            {
                scdPtr = fstPtr + k;
                tmp1 = *fstPtr;
                tmp2 = *scdPtr;
                xt = tmp1 - tmp2;
                *fstPtr = (tmp1 + tmp2) >> 1u;

                fstPtr++;
                scdPtr++;

                tmp1 = *fstPtr;
                tmp2 = *scdPtr;
                yt = tmp1 - tmp2;
                *fstPtr = (tmp1 + tmp2) >> 1u;

                scdPtr--;

                tmp1 = (int32_t)(((int64_t)xt * cosVal) >> 32);
                tmp2 = (int32_t)(((int64_t)yt * sinVal) >> 32);
                *scdPtr = (tmp1 + tmp2);
                scdPtr++;

                tmp1 = (int32_t)(((int64_t)yt * cosVal) >> 32);
                tmp2 = (int32_t)(((int64_t)xt * sinVal) >> 32);
                *scdPtr = tmp1 - tmp2;

                fstPtr--;
                fstPtr += (k * 2);
            }
        }
    }

    /* finalization phase */
    fstPtr = pSrc;
    for (i = 0; i < fftLen; i += 4)
    {
        scdPtr = fstPtr + 2;
        tmp1 = *fstPtr;
        tmp2 = *scdPtr;

        xt = tmp1 - tmp2;
        *fstPtr = tmp1 + tmp2;

        fstPtr++;
        scdPtr++;
        tmp1 = *fstPtr;
        tmp2 = *scdPtr;

        yt = tmp1 - tmp2;
        *fstPtr = tmp1 + tmp2;

        *scdPtr = yt;
        scdPtr--;
        *scdPtr = xt;
        fstPtr--;

        fstPtr += 4;
        scdPtr = fstPtr + 2;
        tmp1 = *fstPtr;
        tmp2 = *scdPtr;

        xt = tmp1 - tmp2;
        *fstPtr = tmp1 + tmp2;

        fstPtr++;
        scdPtr++;
        tmp1 = *fstPtr;
        tmp2 = *scdPtr;

        yt = tmp1 - tmp2;
        *fstPtr = tmp1 + tmp2;
        fstPtr--;
        *scdPtr = yt;
        scdPtr--;
        *scdPtr = xt;

        fstPtr += 4;
    }

    /* order reversing */
    lookupOffset = 2048U / fftLen;
    reorderTbl = (uint16_t *)&reorderTbl[lookupOffset - 1];
    fstPtr = pSrc;
    scdPtr = pSrc;
    for (i = 0, j = 0; i < (fftLen >> 1); i += 2u)
    {
        if (i < j)
        {
            /*  pSrc[i] <-> pSrc[j]; */
            tmp1 = *fstPtr;
            *fstPtr = *scdPtr;
            *scdPtr = tmp1;

            /*  pSrc[i+1u] <-> pSrc[j+1u] */
            fstPtr++;
            scdPtr++;
            tmp1 = *fstPtr;
            *fstPtr = *scdPtr;
            *scdPtr = tmp1;

            /*  pSrc[i+fftLenBy2p1] <-> pSrc[j+fftLenBy2p1] */
            fstPtr++;
            fstPtr += fftLen;
            scdPtr++;
            scdPtr += fftLen;
            tmp1 = *fstPtr;
            *fstPtr = *scdPtr;
            *scdPtr = tmp1;

            /*  pSrc[i+fftLenBy2p1+1u] <-> pSrc[j+fftLenBy2p1+1u] */
            fstPtr++;
            scdPtr++;
            tmp1 = *fstPtr;
            *fstPtr = *scdPtr;
            *scdPtr = tmp1;

            //tPtr
            fstPtr = fstPtr - fftLen - 1;//&pSrc[(2 * i) + 2];
            scdPtr -= 3;
        } else {
            fstPtr += 2;
            scdPtr += fftLen;
        }

        /*  pSrc[i+1u] <-> pSrc[j+1u] */
        tmp1 = *fstPtr;
        *fstPtr = *scdPtr;
        *scdPtr = tmp1;

        /*  pSrc[i+2u] <-> pSrc[j+2u] */
        fstPtr++;
        scdPtr++;
        tmp1 = *fstPtr;
        *fstPtr = *scdPtr;
        *scdPtr = tmp1;

        /*  next index */
        j = *reorderTbl;
        reorderTbl += lookupOffset;

        /* point next items */
        fstPtr++;
        scdPtr = &pSrc[2 * j];
    }
}

#endif /* MATH_FFTC_C */

#ifdef MATH_SQRT2P2_C
/**
  * @brief  calculate SQRT (X^2 + Y^2) with 64-bit precision using Newton algorithm
  * @param  x - first operand
  * @param  y - second operand
  * @return SQRT(X^2 + Y^2)
  */
int32_t MATH_sqrtX2pY2(int32_t x, int32_t y)
{
    int64_t q;
    int32_t s;

    x = MATH_ABS(x);
    y = MATH_ABS(y);

    if (y == 0)
        return x;
    if (x == 0)
        return y;

    q = (int64_t) x * x + (int64_t) y * y;
    s = x / 2 + y / 2;

    s = MATH_SQRT(q, s);

    return s;
}
#endif /* MATH_SQRT2P2_C */

/**
  * @brief  Fast sine calculation using interpolation of table values
  * @note   This function calling while DFT calculations
  * @param  alfaP: integer argument of sine in interval [0, ANGLE_SCALE_2PI) converted to
  *         interval 0 <= alfaP < 2*PI in calculations
  * @return sin(2*PI*alfaP/ANGLE_SCALE_2PI)*INT_SCALE - sine of alfaP value multiplied to INT_SCALE
  */
int32_t MATH_FastSinA(int32_t alfaP)
{
    int32_t tableIndex, tableRem, sign, sinVal;

    /* cut alfaP to interval 0 <= alfaP < PI */
    sign = 1;
    if (alfaP >= MATH_ANGLE_SCALE_PI) {
        alfaP -= MATH_ANGLE_SCALE_PI;
        sign = -1;
    }

    /* cut alfaP to interval 0 <= alfaP <= PI/2 */
    if (alfaP > MATH_ANGLE_SCALE_PI2)
        alfaP = MATH_ANGLE_SCALE_PI - alfaP;

    /* here we have 0 <= alfaP <= PI/2 and table in same interval
     * let's do linear interpolation */
    tableIndex = alfaP >> MATH_TABLE_INDEX_RSU;
    tableRem = alfaP % TABLE_INDEX_FACTOR;

    sinVal = MATH_TABLE_SIN_PREC[tableIndex];
    if (tableRem != 0)
    {
        sinVal += ((MATH_TABLE_SIN_PREC[tableIndex + 1] - sinVal) * tableRem) >> MATH_TABLE_INDEX_RSU;
    }

    return sinVal * sign;
}

/**
  * @brief  Fast cosine calculation using interpolation of table values
  * @note   This function calling while DFT calculations
  * @param  alfaP: integer argument of cosine in interval [0, ANGLE_SCALE_2PI) converted to
  *         interval 0 <= alfaP < 2*PI in calculations
  * @return cos(2*PI*alfaP/ANGLE_SCALE_2PI)*INT_SCALE - cosine of alfaP value multiplied to INT_SCALE
  */
int32_t MATH_FastCosA(int32_t alfaP)
{
    /* convert to sine and return */
    alfaP += MATH_ANGLE_SCALE_PI2;
    return MATH_FastSinA(alfaP);
}

/**
  * @breif  float implemenation of the arctg() calculation
  * @param  x - tg value
  * @return arctg(x)
  */
float MATH_AtanF(float x)
{
    int32_t signChange;
    int32_t inversion;
    int32_t steps;
    float x2, a;

    /* check up the sign change */
    if (x < 0.F)
    {
        x = -x;
        signChange = 1;
    }
    else {
        signChange = 0;
    }
    /* inversion */
    if (x > 1.0f)
    {
        x = 1.0f / x;
        inversion = 1;
    } else {
        inversion = 0;
    }
    /* process shrinking until x < PI/12 */
    steps = 0;
    while (x > 0.26179938f) {
        steps++;
        a = x + 1.73205080f; /* SQRT3 */
        a = 1.f / a;
        x *= 1.73205080f; /* SQRT3 */
        x -= 1.F;
        x *= a;
    }
    /* calculation core */
    x2 = x*x;
    a = x2 + 1.4087812f;
    a = 0.55913709f / a;
    a += 0.60310579f;
    a -= 0.05160454f * x2;
    a *= x;
    /* roll shrinking back */
    while (steps > 0)
    {
        /* a += PI / 6 */
        a += 0.52359877f;
        steps--;
    }
    /* inversion */
    if (inversion != 0)
    {
        /* a = (PI / 2) - a */
        a = 1.57079632f - a;
    }
    /* sign change */
    if (signChange != 0)
    {
        a = -a;
    }
    return a;
}

/** @} */ /* End of group MATH_Private_Functions */

/** @} */ /* End of group MATH */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_math.c
  */


