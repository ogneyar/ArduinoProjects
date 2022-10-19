/**
  ******************************************************************************
  * @file    MDR32FxQI_audio.h
  * @author  Milandr Application Team
  * @version V2.0.2i
  * @date    10/03/2022
  * @brief   This file contains all the functions prototypes for the AUDIO_IP
  *          firmware library.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MDR32FxQI_AUDIO_H_
#define MDR32FxQI_AUDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MDR32FxQI_config.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Driver MDR32FxQI Standard Peripherial Driver
  * @{
  */

#if defined (USE_MDR32FG16S1QI)
/** @addtogroup AUDIO_IP
  * @warning This module can be used only for MDR32FG16S1QI microcontroller's.
  * @{
  */

/** @defgroup AUDIO_IP_Exported_Types AUDIO_IP Exported Types
  * @{
  */

/**
  * @brief AUDIO_IP AUC_C1
  */
typedef enum
{
    AUDIO_IP_AUC_C1_HSI   = 0x00,
    AUDIO_IP_AUC_C1_HSI_2 = 0x01,
    AUDIO_IP_AUC_C1_HSE   = 0x02,
    AUDIO_IP_AUC_C1_HSE_2 = 0x03
} AUDIO_IP_AUC_C1;

#define IS_AUDIO_IP_AUC_C1(AUC_C1)  (((AUC_C1) == AUDIO_IP_AUC_C1_HSI)   || \
                                     ((AUC_C1) == AUDIO_IP_AUC_C1_HSI_2) || \
                                     ((AUC_C1) == AUDIO_IP_AUC_C1_HSE)   || \
                                     ((AUC_C1) == AUDIO_IP_AUC_C1_HSE_2))

/**
  * @brief AUDIO_IP AUC_C2
  */
typedef enum
{
    AUDIO_IP_AUC_C2_AUC_C1      = 0x00,
    AUDIO_IP_AUC_C2_AUC_PLLCPU0 = 0x01,
    AUDIO_IP_AUC_C2_AUC_PLLUSB0 = 0x02
} AUDIO_IP_AUC_C2;

#define IS_AUDIO_IP_AUC_C2(AUC_C2)  (((AUC_C2) == AUDIO_IP_C2_AUC_C1)      || \
                                     ((AUC_C2) == AUDIO_IP_C2_AUC_PLLCPU0) || \
                                     ((AUC_C2) == AUDIO_IP_C2_AUC_PLLUSB0))

/**
  * @brief AUDIO_IP AUDIO_C3
  */
typedef enum
{
    AUDIO_IP_AUDIO_CLK_DIV1   = ((uint32_t)0x00),
    AUDIO_IP_AUDIO_CLK_DIV2   = ((uint32_t)0x08),
    AUDIO_IP_AUDIO_CLK_DIV4   = ((uint32_t)0x09),
    AUDIO_IP_AUDIO_CLK_DIV8   = ((uint32_t)0x0A),
    AUDIO_IP_AUDIO_CLK_DIV16  = ((uint32_t)0x0B),
    AUDIO_IP_AUDIO_CLK_DIV32  = ((uint32_t)0x0C),
    AUDIO_IP_AUDIO_CLK_DIV64  = ((uint32_t)0x0D),
    AUDIO_IP_AUDIO_CLK_DIV128 = ((uint32_t)0x0E),
    AUDIO_IP_AUDIO_CLK_DIV256 = ((uint32_t)0x0F)
} AUDIO_IP_AUDIO_C3;

#define IS_AUDIO_IP_AUDIO_CLK_DIV(CLK_DIV)  (((CLK_DIV) >= AUDIO_IP_AUDIO_CLK_DIV1) && \
                                             ((CLK_DIV) <= AUDIO_IP_AUDIO_CLK_DIV256))

/**
  * @brief AUDIO_IP Filter Mode
  */
typedef enum
{
    AUDIO_IP_FILTER_MODE_FIR_FILTER = ((uint32_t)0x0),
    AUDIO_IP_FILTER_MODE_IIR_FILTER = ((uint32_t)0x4)
} AUDIO_IP_Filter_Mode;

#define IS_AUDIO_IP_FILTER_MODE(FILTER_MODE)  (((FILTER_MODE) == AUDIO_IP_FILTER_MODE_FIR_FILTER) || \
                                               ((FILTER_MODE) == AUDIO_IP_FILTER_MODE_IIR_FILTER))

/**
  * @brief AUDIO_IP ADC Input Amplifier Level
  */
typedef enum
{
    AUDIO_IP_ADC_INPUT_AMPLIFIER_LEVEL_0_DB  = ((uint32_t)0x00),
    AUDIO_IP_ADC_INPUT_AMPLIFIER_LEVEL_6_DB  = ((uint32_t)0x01),
    AUDIO_IP_ADC_INPUT_AMPLIFIER_LEVEL_12_DB = ((uint32_t)0x02),
    AUDIO_IP_ADC_INPUT_AMPLIFIER_LEVEL_24_DB = ((uint32_t)0x03)
} AUDIO_IP_ADC_Input_Ampl;

#define IS_AUDIO_IP_INPUT_AMPLIFIER_LEVEL(AMPLIFIER_LEVEL) \
            (((AMPLIFIER_LEVEL) == AUDIO_IP_ADC_INPUT_AMPLIFIER_LEVEL_0_DB)  || \
             ((AMPLIFIER_LEVEL) == AUDIO_IP_ADC_INPUT_AMPLIFIER_LEVEL_6_DB)  || \
             ((AMPLIFIER_LEVEL) == AUDIO_IP_ADC_INPUT_AMPLIFIER_LEVEL_12_DB) || \
             ((AMPLIFIER_LEVEL) == AUDIO_IP_ADC_INPUT_AMPLIFIER_LEVEL_24_DB))

/**
  * @brief AUDIO_IP ADC Analog Input Source
  */
typedef enum
{
    AUDIO_IP_ANALOG_INPUT_SOURCE_INP1      = ((uint32_t)0x00),
    AUDIO_IP_ANALOG_INPUT_SOURCE_MICIN_INT = ((uint32_t)0x01),
    AUDIO_IP_ANALOG_INPUT_SOURCE_MICIN_EXT = ((uint32_t)0x02),
    AUDIO_IP_ANALOG_INPUT_SOURCE_INP2      = ((uint32_t)0x03)
} AUDIO_IP_ADC_Input_Src;

#define IS_AUDIO_IP_ANALOG_INPUT_SOURCE(INPUT_SOURCE) \
                (((INPUT_SOURCE) == AUDIO_IP_ANALOG_INPUT_SOURCE_INP1)      || \
                 ((INPUT_SOURCE) == AUDIO_IP_ANALOG_INPUT_SOURCE_MICIN_INT) || \
                 ((INPUT_SOURCE) == AUDIO_IP_ANALOG_INPUT_SOURCE_MICIN_EXT) || \
                 ((INPUT_SOURCE) == AUDIO_IP_ANALOG_INPUT_SOURCE_INP2))

/**
  * @brief AUDIO_IP DAC_SIDE_TONE_LOOP_BACK
  */
typedef enum
{
    AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK_MUTE = ((uint32_t)0x7),
    AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK_21dB = ((uint32_t)0x6),
    AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK_18dB = ((uint32_t)0x5),
    AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK_15dB = ((uint32_t)0x4),
    AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK_12dB = ((uint32_t)0x3),
    AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK_9dB  = ((uint32_t)0x2),
    AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK_6dB  = ((uint32_t)0x1),
    AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK_3dB  = ((uint32_t)0x0)
} AUDIO_IP_DAC_Side_Tone;

#define IS_AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK(SIDE_TONE_LOOP_BACK) \
                ((SIDE_TONE_LOOP_BACK) <= AUDIO_IP_DAC_SIDE_TONE_LOOP_BACK_MUTE)

/**
  * @brief AUDIO_IP AUDIO_IP Interrupt Masks
  */
typedef enum
{
    AUDIO_IP_IT_DAOVFM   = ((uint32_t)0x01), /*!< Mask of DAC overflow interrupt */
    AUDIO_IP_IT_ADCVFM   = ((uint32_t)0x02), /*!< Mask of ADC overflow interrupt */
    AUDIO_IP_IT_ADCNSM   = ((uint32_t)0x04), /*!< Mask of ADC FIFO interrupt */
    AUDIO_IP_IT_DACNSM   = ((uint32_t)0x08), /*!< Mask of DAC FIFO interrupt */
    AUDIO_IP_IT_OVERCURM = ((uint32_t)0x10)  /*!< Mask DAC of output short circuit interrupt */
} AUDIO_IP_ITMask;

#define IS_AUDIO_IP_IT(IT)          (((IT) & (~0x000001F)) == 0)

#define IS_AUDIO_IP_CLEAR_IT(IT)    (((IT) & (~0x00000003)) == 0)

/**
  * @brief AUDIO_IP Flags
  */
typedef enum
{
    AUDIO_IP_FLAG_DAOVF   = ((uint32_t)0x01), /*!< DAC overflow interrupt flag */
    AUDIO_IP_FLAG_ADCVF   = ((uint32_t)0x02), /*!< ADC overflow interrupt flag */
    AUDIO_IP_FLAG_ADCNS   = ((uint32_t)0x04), /*!< ADC FIFO interrupt flag */
    AUDIO_IP_FLAG_DACNS   = ((uint32_t)0x08), /*!< DAC FIFO interrupt flag */
    AUDIO_IP_FLAG_OVERCUR = ((uint32_t)0x10)  /*!< DAC of output short circuit interrupt flag */
} AUDIO_IP_Flags;

#define IS_AUDIO_IP_FLAG(FLAG)  (((FLAG) == AUDIO_IP_FLAG_DAOVF) || \
                                 ((FLAG) == AUDIO_IP_FLAG_ADCVF) || \
                                 ((FLAG) == AUDIO_IP_FLAG_ADCNS) || \
                                 ((FLAG) == AUDIO_IP_FLAG_DACNS) || \
                                 ((FLAG) == AUDIO_IP_FLAG_OVERCUR))

/**
  * @brief AUDIO_IP Short Circuit Detection
  */
typedef enum
{
    AUDIO_IP_SHORT_CIRCUIT_DETECTION_OUTPUT_BUFFER = ((uint32_t)0x100),
    AUDIO_IP_SHORT_CIRCUIT_DETECTION_BIAS_CIRCUIT  = ((uint32_t)0x200)
} AUDIO_IP_Short_Circ_Detect_Out_Buff;

#define IS_AUDIO_IP_SHORT_CIRCUIT_DETECTION(SC) \
                    (((SC) == AUDIO_IP_SHORT_CIRCUIT_DETECTION_OUTPUT_BUFFER) || \
                     ((SC) == AUDIO_IP_SHORT_CIRCUIT_DETECTION_BIAS_CIRCUIT))

#define SHORT_CIRCUIT_DETECTION(SC) (((SC) == AUDIO_IP_DACCTL_OVECBA) || \
                                     ((SC) == AUDIO_IP_DACCTL_OVECBS))


/**
  * @brief AUDIO IP Structure defintion
  * @note  The user should not configure all the AUDIO_IP_InitTypeDef structure's fields.
  *        By calling the AUDIO_IP_StructInit function the structure's fields are set to their default values.
  *        Only the parameters that will be set to a non-default value should be configured.
  */
typedef struct
{
    /**
      * @brief POWCTL The general codec control.
      */
    AUDIO_IP_Filter_Mode    FilterMode;                 /*!< Defines the used filter for inderpolation/decimation.
                                                             This parameter can be a value of @ref AUDIO_IP_Filter_Mode. */
    FunctionalState         AnalogLoopBackMode;         /*!< Enable or disable addition the analog loop back.
                                                             This parameter can be a value of @ref FunctionalState */
    FunctionalState         DigitalLoopBackMode;        /*!< Enable or disable addition the digital loop back.
                                                             This parameter can be a value of @ref FunctionalState */
    /**
      * @brief ADCCTL    The ADC control.
      */

    uint32_t                ADGain;                     /*!< Defines recording level of the input signal.
                                                             This parameter can be of a value from 0 to 0x3F. */
    AUDIO_IP_ADC_Input_Ampl ADCInputAmplifier;          /*!< Defines the level of input preamplifier.
                                                             This parameter can be value of the@ref AUDIO_IP_ADC_Input_Ampl. */
    AUDIO_IP_ADC_Input_Src  ADCAnalogInput;             /*!< Select the ADC source of the input signal.
                                                             This parameter can be a value of the @ref AUDIO_IP_ADC_Input_Src. */
    FunctionalState         ADCInputControl;            /*!< Control of analog filter and ADC.
                                                             This parameter can be a value of @ref FunctionalState */
    /**
      * @brief DACCTL    The DAC control.
      */

    uint32_t                DAGain;                     /*!< Defines the level of playback output signal.
                                                             This parameter can be of a value from 0 to 0x3F. */
    FunctionalState         DACMute;                    /*!< Enable or disable the DAC output mute.
                                                             This parameter can be a value of @ref FunctionalState */
    FunctionalState         DACOutputAmplifier;         /*!< Enable or disable DAC analog output amplifier.
                                                             This parameter can be a value of @ref FunctionalState */
    FunctionalState         DACBIASOffsetSchemeState;   /*!< Enable or disable offset scheme BIAS.
                                                             This parameter can be a value of @ref FunctionalState */
    FunctionalState         DACAnalogState;             /*!< Enable or disable analogue DAC and filters.
                                                             This parameter can be a value of @ref FunctionalState */
    FunctionalState         DACOverCurrentBufferDet;    /*!< Determines the resolution of a short-circuit detection circuit output buffer.
                                                             This parameter can be a value of @ref FunctionalState */
    FunctionalState         DACOverCurrentNetOffsetDet; /*!< Determines the resolution of a short-circuit detection circuit bias circuitry.
                                                             This parameter can be a value of @ref FunctionalState */
    AUDIO_IP_DAC_Side_Tone  DACSideToneLoopBack;        /*!< Set the value of the side tone loob back.
                                                             This parameter can be a value if the @ref AUDIO_IP_DAC_Side_Tone. */
    FunctionalState         DACState;                   /*!< Determines the work mode of the AUDIO DAC.
                                                             This parameter can be a value of @ref FunctionalState */
} AUDIO_IP_InitTypeDef;

/** @} */ /* End of group AUDIO_IP_Exported_Types */


/** @defgroup AUDIO_IP_Exported_Constants AUDIO_IP Exported Constants
  * @{
  */

#define IS_AUDIO_IP_AD_GAIN(AD_GAIN)  (((AD_GAIN) & (~0x0000003F)) == 0)
#define IS_AUDIO_IP_DA_GAIN(DA_GAIN)  (((DA_GAIN) & (~0x0000003F)) == 0)

/** @} */ /* End of group AUDIO_IP_Exported_Constants */


/** @defgroup AUDIO_IP_Exported_Functions AUDIO_IP Exported Functions
  * @{
  */
void AUDIO_IP_DeInit(void);
void AUDIO_IP_StructInit(AUDIO_IP_InitTypeDef * AUDIO_IP_InitStruct);
void AUDIO_IP_Init(AUDIO_IP_InitTypeDef * AUDIO_IP_InitStruct);
void AUDIO_IP_ADCCmd(FunctionalState NewState);
void AUDIO_IP_DACCmd(FunctionalState NewState);
void AUDIO_IP_SetADGain(uint32_t GainValue);
void AUDIO_IP_SetDAGain(uint32_t GainValue);
void AUDIO_IP_SetADCInputAmplifierLevel(AUDIO_IP_ADC_Input_Ampl InputAmplifierLevel);
void AUDIO_IP_SetADCInputSource(AUDIO_IP_ADC_Input_Src ADCInputSource);
void AUDIO_IP_DACMuteCmd(FunctionalState NewState);
void AUDIO_IP_DACOutputAmplifierCmd(FunctionalState NewState);
void AUDIO_IP_OverCurCmd(AUDIO_IP_Short_Circ_Detect_Out_Buff value, FunctionalState NewState);
void AUDIO_IP_ITConfig(AUDIO_IP_ITMask AUDIO_IT, FunctionalState NewState);
ITStatus AUDIO_IP_GetITStatus(AUDIO_IP_Flags AUDIO_IP_FLAG);
void AUDIO_IP_ClearITFlag(AUDIO_IP_ITMask AUDIO_IT);
uint16_t AUDIO_IP_ReceiveData(void);
void AUDIO_IP_SendData(uint16_t AudioData);

/** @} */ /* End of group AUDIO_IP_Exported_Functions */

/** @} */ /* End of group AUDIO_IP */
#endif /* #if defined (USE_MDR32FG16S1QI) */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* MDR32FxQI_AUDIO_H_ */

/*********************** (C) COPYRIGHT 2022 Milandr ****************************
*
* END OF FILE MDR32FxQI_audio.h */


