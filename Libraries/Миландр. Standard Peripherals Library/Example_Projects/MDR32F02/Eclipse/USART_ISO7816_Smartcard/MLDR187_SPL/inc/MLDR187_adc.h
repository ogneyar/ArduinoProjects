/**
  * FILE MLDR187_adc.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_ADC_H
#define __MLDR187_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_rst_clk.h"

#include <stdint.h>

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/** @defgroup ADC_Exported_Types
  * @{
  */

/**
  * @brief ADC channel numbers
  */
typedef enum
{
    ADC_ChTemp      = ADC_CHNL_TEMP,
    ADC_ChAin1      = ADC_CHNL_AIN1,
    ADC_ChAin2      = ADC_CHNL_AIN2,
    ADC_ChAin3      = ADC_CHNL_AIN3,
    ADC_ChVbat      = ADC_CHNL_VBAT,
    ADC_ChVref      = ADC_CHNL_VREF
} ADC_ChannelNumber;

/**
  * @brief enumeration of the valid channels for channel selection
  */
typedef enum
{
    ADC_ChSelTemp   = ADC_CHSEL_TEMP,
    ADC_ChSelAin1   = ADC_CHSEL_AIN1,
    ADC_ChSelAin2   = ADC_CHSEL_AIN2,
    ADC_ChSelAin3   = ADC_CHSEL_AIN3,
    ADC_ChSelVbat   = ADC_CHSEL_VB,
    ADC_ChSelVref   = ADC_CHSEL_2p4V
} ADC_ChannelSelection;

/**
  * @brief ADC frequency divisor
  */
typedef enum
{
    ADC_Div1        = ADC_CFG_DIVCLK_1,
    ADC_Div2        = ADC_CFG_DIVCLK_2,
    ADC_Div4        = ADC_CFG_DIVCLK_4,
    ADC_Div8        = ADC_CFG_DIVCLK_8,
    ADC_Div16       = ADC_CFG_DIVCLK_16,
    ADC_Div32       = ADC_CFG_DIVCLK_32,
    ADC_Div64       = ADC_CFG_DIVCLK_64,
    ADC_Div128      = ADC_CFG_DIVCLK_128,
    ADC_Div256      = ADC_CFG_DIVCLK_256,
    ADC_Div512      = ADC_CFG_DIVCLK_512,
    ADC_Div1024     = ADC_CFG_DIVCLK_1024,
    ADC_Div2048     = ADC_CFG_DIVCLK_2048
} ADC_Divisor;

/**
  * @brief  ADC Init Structure definition
  */
typedef struct
{
    RST_CLK_HsClkSrc clkSrc;        /*!< @ref rccHsClkSrc - ADC clock source */
    RST_CLK_ClkDiv clkDiv;          /*!< @ref rccClkDiv - clock divisor 1 .. 256 */
    ADC_Divisor prescaler;      /*!< ADC frequency prescaler */
    FunctionalState use2p4V;    /*!< @ref FunctionalState - use VR_2p4V as reference voltage */
    FunctionalState enAlarm;    /*!< @ref FunctionalState - enable automatic margins control */
    FunctionalState chChange;   /*!< @ref FunctionalState - ENABLE multichannel mode - will be converted
                                     every selected channels one-by-one, list of the channels to be converted
                                     is specified within CHSEL register (use ADC_SetConversionChannelMask()) */
    FunctionalState autoCont;   /*!< @ref FunctionalState - ENABLE autocontinue mode - next conversion will
                                     start immediately after all channels conversion will be complete */
    ADC_ChannelNumber chnl;     /*!< number of channel to be used */
    uint8_t interchannelDelay;  /*!< number of clock cycles that should be delayed between
                                     2 different channels conversions, 0 .. 7 cycles */
} ADC_InitTypeDef;

/** @} */ /* End of group ADC_Exported_Types */

/** @defgroup ADC_Exported_Functions
  * @{
  */

/**
  * @brief  init ADC with initialization structure
  * @param  initStruct - @ref ADC_InitTypeDef - initialization structure
  */
void ADC_Init(ADC_InitTypeDef* initStruct);

/**
  * @brief  fill initialization structure with default values
  * @param  initStruct - @ref ADC_InitTypeDef - pointer to structure to be filled
  */
void ADC_StructInitDefault(ADC_InitTypeDef* initStruct);

/**
  * @brief  de-initialize ADC module, setup default values and deactivate peripheral clock
  */
void ADC_DeInit(void);

/**
  * @brief  setup new channel number to be used
  * @param  chnl - @ref ADC_ChannelNumber - channel to be used
  */
void ADC_SetChannel(ADC_ChannelNumber chnl);

/**
  * @brief  enable or disable ADC module
  * @param  newState - @ref FunctionalState - ENABLE or DISABLE ADC
  */
void ADC_Cmd(FunctionalState NewState);

/**
  * @brief  start ADC conversion
  */
void ADC_Start(void);

/**
  * @brief  get ADC conversion result
  * @return ADC conversion result
  */
uint16_t ADC_GetResult(void);

/**
  * @brief  get number of channel that was converted last
  * @return @ref ADC_ChannelNumber - ADC channel number
  */
ADC_ChannelNumber ADC_GetResultChannel(void);

/**
  * @brief  set channels conversion mask
  * @param  chnls - @ref ADC_ChannelSelection - channel conversion selection mask
  */
void ADC_SetConversionChannelMask(uint32_t chnls);

/**
  * @brief  sets valid converted value margins to avto-compare feature
  * @param  hLevel - high valid level
  * @param  lLevel - low valid level
  */
void ADC_SetValidMargins(uint16_t hLevel, uint16_t lLevel);

/**
  * @brief  trim bandgap
  * @param  trimValue - trim value for bandgap
  */
void ADC_BandgapTrim(uint8_t trimValue);

/**
  * @brief  enable / disable noise generator
  * @param  NewState - @ref FunctionalState - new ENABLE / DISABLE state for noise generator
  */
void ADC_CmdNoiseGen(FunctionalState NewState);

/** @} */ /* End of group ADC_Exported_Functions */

/** @} */ /* End of group ADC */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} /* extern "C" block end */
#endif

#endif /* __MLDR187_ADC_H */

/**
 * END OF FILE MLDR187_adc.h
 */

