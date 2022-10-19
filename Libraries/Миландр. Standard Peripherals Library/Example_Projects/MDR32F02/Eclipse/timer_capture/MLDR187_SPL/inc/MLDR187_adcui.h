/**
  * FILE MLDR187_adcui.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_ADCUI_H
#define __MLDR187_ADCUI_H

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

/** @addtogroup ADCUI
  * @{
  */

/** @defgroup ADCUI_Exported_Types
  * @{
  */

/**
  * @brief ADCUI U/I channel enumeration
  */
typedef enum
{
    adcuiCh0,
    adcuiCh1,
    adcuiCh2
} adcuiChannel;

/**
  * @brief ADCUI current channel enumeration (adcuiChannel + I3)
  */
typedef enum
{
    adcuiCurCh0 = adcuiCh0,
    adcuiCurCh1 = adcuiCh1,
    adcuiCurCh2 = adcuiCh2,
    adcuiCurCh3
} adcuiCurrentChannel;

/**
  * @brief ADCUI lines
  */
typedef enum
{
    adcuiV0DAT,
    adcuiI0DAT,
    adcuiI3DAT,
    adcuiV1DAT,
    adcuiI1DAT,
    adcuiV2DAT,
    adcuiI2DAT
} adcuiLine;

/**
  * @brief Energy options enumeration
  */
typedef enum
{
    adcuiActivePositiveEnergy,
    adcuiActiveNegativeEnergy,
    adcuiReactivePositiveEnergy,
    adcuiReactiveNegativeEnergy,
    adcuiFullEnergy,
} adcuiEnergyType;

/**
  * @brief Calibration energy options enumeration
  */
typedef enum
{
    adcuiActiveEnergyCal	= 0x1U,
    adcuiReactiveEnergyCal	= 0x2U,
    adcuiFullEnergyCal		= 0x4U
} adcuiEnergyCalibration;

/**
  * @brief oversampling ratio
  */
typedef enum
{
    adcuiOvrsmpl4KHz	= ADCUI_CTRL1_OSR_CONF_4KHZ,
    adcuiOvrsmpl8KHz	= ADCUI_CTRL1_OSR_CONF_8KHZ,
    adcuiOvrsmpl16KHz	= ADCUI_CTRL1_OSR_CONF_16KHZ,
} adcuiOsr;

/**
  * @brief no-load setup, specify % of full scale that will not be included within accumulator
  */
typedef enum
{
    adcuiNoload0		= ADCUI_CTRL1_THRESHOLD_0,
    adcuiNoLoad0_00305	= ADCUI_CTRL1_THRESHOLD_0012,
    adcuiNoLoad0_0061	= ADCUI_CTRL1_THRESHOLD_00061,
    adcuiNoLoad0_012	= ADCUI_CTRL1_THRESHOLD_000305
} adcuiNoLoad;

/**
  * @brief period calculation time, in periods, 1..128
  */
typedef enum
{
    adcuiPerTime1		= ADCUI_CTRL1_PER_LENGTH_1,
    adcuiPerTime2		= ADCUI_CTRL1_PER_LENGTH_2,
    adcuiPerTime4		= ADCUI_CTRL1_PER_LENGTH_4,
    adcuiPerTime8		= ADCUI_CTRL1_PER_LENGTH_8,
    adcuiPerTime16		= ADCUI_CTRL1_PER_LENGTH_16,
    adcuiPerTime32		= ADCUI_CTRL1_PER_LENGTH_32,
    adcuiPerTime64		= ADCUI_CTRL1_PER_LENGTH_64,
    adcuiPerTime128		= ADCUI_CTRL1_PER_LENGTH_128
} adcuiPerTime;

/**
  * @brief output resolution
  */
typedef enum
{
    adcuiRes16bit		= ADCUI_CTRL1_RESOL_16BIT,
    adcuiRes24bit		= ADCUI_CTRL1_RESOL_24BIT
} adcuiResol;

/**
  * @brief channel gain selector
  */
typedef enum
{
    adcuiPGA_0dB		= ADCUI_PGA_0dB,
    adcuiPGA_6dB		= ADCUI_PGA_6dB,
    adcuiPGA_12dB		= ADCUI_PGA_12dB,
    adcuiPGA_18dB		= ADCUI_PGA_18dB
} adcuiChannelPGA;

/**
  * @brief channel additional gain
  */
typedef enum
{
    adcuiGain_0dB		= ADCUI_GAIN_0dB,
    adcuiGain_6dB		= ADCUI_GAIN_6dB
} adcuiChannelGain;

/**
  * @brief alternate channel selection
  */
typedef enum
{
    adcuiF0Isel_Auto	= ADCUI_F0MD0_F0SEL_I_CH_AUTO,
    adcuiF0Isel_I0		= ADCUI_F0MD0_F0SEL_I_CH_I0,
    adcuiF0Isel_I3		= ADCUI_F0MD0_F0SEL_I_CH_I3
} adcuiAdditCurSel;

/**
  * @brief full energy source selection
  */
typedef enum
{
    adcuiVaSel_FullPower= ADCUI_F0CTR_F0VASEL_FULLPOWER,
    adcuiVaSel_IRMS		= ADCUI_F0CTR_F0VASEL_IRMS,
} adcuiVaSel;

/**
  * @brief FIFO register selection
  */
typedef enum
{
    adcuiFifo_RAW		= ADCUI_FIFO_RAW,
    adcuiFifo_ActPower	= ADCUI_FIFO_ACT_POWER,
    adcuiFifo_ReactPower= ADCUI_FIFO_REACT_POWER,
    adcuiFifo_FullPower	= ADCUI_FIFO_FULL_POWER
} adcuiFifoSrc;

/**
  * @brief ADCUI status flags
  */
typedef enum
{
    adcuiFlagVoltageFifoEmpty		= ADCUI_F0STAT_F0VF_EMP,
    adcuiFlagVoltageFifoFull		= ADCUI_F0STAT_F0VF_FLL,
    adcuiFlagVoltageFifoOverflow	= ADCUI_F0STAT_F0VF_OVR,

    adcuiFlagCurrentFifoEmpty		= ADCUI_F0STAT_F0IF_EMP,
    adcuiFlagCurrentFifoFull		= ADCUI_F0STAT_F0IF_FLL,
    adcuiFlagCurrentFifoOverflow	= ADCUI_F0STAT_F0IF_OVR,

    adcuiFlagOvercurrnet			= ADCUI_F0STAT_F0PEAKIF,

    adcuiFlagOvervoltage			= ADCUI_F0STAT_F0PEAKVF,
    adcuiFlagVoltageDrop			= ADCUI_F0STAT_F0SAGF,

    adcuiFlagZeroCross				= ADCUI_F0STAT_F0ZEROCRS,
    adcuiFlagNovoltageTimeout		= ADCUI_F0STAT_F0ZXTOF,

    adcuiFlagFullPowerUnderflow		= ADCUI_F0STAT_F0ANLDFL,
    adcuiFlagFullEnergyOverflow		= ADCUI_F0STAT_F0VAOV,

    adcuiFlagReactivePowerDirChange	= ADCUI_F0STAT_F0VARSIGN,
    adcuiFlagReactivePowerUnderflow	= ADCUI_F0STAT_F0VARNLDFL,
    adguiFlagReactEnergyPOverflow	= ADCUI_F0STAT_F0VAROVP,
    adcuiFlagReactEnergyNOverflow	= ADCUI_F0STAT_F0VAROVN,

    adcuiFlagActivePowerDirChange	= ADCUI_F0STAT_F0APSIGN,
    adcuiFlagActivePowerUnderflow	= ADCUI_F0STAT_F0APNLDFL,
    adcuiFlagActivEnergyPOverflow	= ADCUI_F0STAT_F0WATTOVP,
    adcuiFlagActivEnergyNOverflow	= ADCUI_F0STAT_F0WATTOVN,

    /* flags, valid only for channel 0/3 */
    adcuiFlag_AlternateIOverflow	= ADCUI_F0STAT_C3IF_OVR,
    adcuiFlag_AlternateIFull		= ADCUI_F0STAT_C3IF_FLL,
    adcuiFlag_AlternateIEmpty		= ADCUI_F0STAT_C3IF_EMP,
    adcuiFlag_AlternateIChange		= ADCUI_F0STAT_F0FAULTCON,
    adcuiFlag_AlternateI3			= ADCUI_F0STAT_F0ICHANNEL_I3
} adcuiFlag;

/**
  * @brief  ADCUI Init Structure definition
  */
typedef struct
{
    RST_CLK_HsClkSrc hsClkSrc;		/*!< @ref rccHsClkSrc - clock source for ADCUI module */
    RST_CLK_ClkDiv clkDiv;			/*!< @ref rccClkDiv - clock divisor for ADCUI module (1 .. 256) */

    adcuiOsr oversamplingRatio;		/*!< @ref adcuiOsr - oversampling ratio, 4/8/16 kHz */
    adcuiResol resolution;			/*!< @ref adcuiResol - ADCUI resolution 16/24 bit */

    FunctionalState i0En;			/*!< @ref FunctionalState - ENABLE I0 channel */
    FunctionalState i3En;			/*!< @ref FunctionalState - ENABLE I3 channel */
    FunctionalState v0En;			/*!< @ref FunctionalState - ENABLE V0 channel */
    FunctionalState i1En;			/*!< @ref FunctionalState - ENABLE I1 channel */
    FunctionalState v1En;			/*!< @ref FunctionalState - ENABLE V1 channel */
    FunctionalState i2En;			/*!< @ref FunctionalState - ENABLE I2 channel */
    FunctionalState v2En;			/*!< @ref FunctionalState - ENABLE V2 channel */

    FunctionalState enableDSP;		/*!< @ref FunctionalState - ENABLE or DISABLE (reset) DSP */
    FunctionalState enableIntVref;	/*!< @ref FunctionalState - ENABLE internal voltage reference */

    FunctionalState enableFreqCalc;	/*!< @ref FunctionalState - ENABLE frequency (period) calculation */
    adcuiPerTime periodCalcTime;	/*!< @ref adcuiPerTime - period and phase-shift calculation time */
    FunctionalState zeroCrossFilter;/*!< @ref FunctionalState - ENABLE low-pass filter for zero-cross detection */
    FunctionalState	zeroCrossRms;	/*!< @ref FunctionalState - if ENABLE RMS will be updated only on zero-crossing event */

    adcuiNoLoad fullEnergyNoLoad;	/*!< @ref adcuiNoLoad - full energy "no-load" feature selection */
    adcuiNoLoad reactEnergyNoLoad;	/*!< @ref adcuiNoLoad - reactive energy "no-load" feature selection */
    adcuiNoLoad actEnergyNoLoad;	/*!< @ref adcuiNoLoad - active energy "no-load" feature selection */
} ADCUI_InitTypeDef;

/**
  * @brief  ADCUI channel init structure definition
  */
typedef struct
{
    /* PGA setup */
    adcuiChannelPGA IPGA;			/*!< @ref adcuiChannelPGA - channel current PGA value (0dB .. 18dB) */
    adcuiChannelPGA VPGA;			/*!< @ref adcuiChannelPGA - channel voltage PGA value (0dB .. 18dB) */
    adcuiChannelPGA IaltPGA;		/*!< @ref adcuiChannelPGA - channel alternate current PGA value (0dB .. 18dB)
	 	 	 	 	 	 	 	 	 	 NOTE: valid only for channel 0 and setup I3 PGA, for other channels ignored */
    adcuiChannelGain IGain;			/*!< @ref adcuiChannelGain - channel current additional gain (0dB .. 6dB) */
    adcuiChannelGain VGain;			/*!< @ref adcuiChannelGain - channel voltage additional gain (0dB .. 6dB) */
    adcuiChannelGain IaltGain;		/*!< @ref adcuiChannelGain - additional channel current additional gain (0dB .. 6dB)
										 NOTE: valid only for channel 0 and setup I3 Gain, for other channels ignored */
    adcuiAdditCurSel IaltSel;		/*!< @ref adcuiAdditCurSel - additional current channel selection
										 NOTE: valid only for channel 0, for other channels ignored */
    /* integration setup */
    FunctionalState IEnInt;			/*!< @ref FunctionalState - channel current integrator enable */
    FunctionalState IaltEnInt;		/*!< @ref FunctionalState - channel alternate current integrator enable
	 	 	 	 	 	 	 	 	 	 NOTE: valid only for channel 0 and setup I3 PGA, for other channels ignored */
    FunctionalState storeIRms;		/*!< @ref FunctionalState - ENABLE to store I RMS instead of full energy */
    /* fifo data source */
    adcuiFifoSrc	IDATsrc;		/*!< @ref adcuiFifoSrc - source for I FIFO: current / power (active/reactive/full) */
    adcuiFifoSrc	VDATsrc;		/*!< @ref adcuiFifoSrc - source for I FIFO: voltage / power (active/reactive/full) */
    /* overcurrent and overvoltage limits */
    uint16_t		overvoltageLim;	/*!< overvoltage limit */
    uint16_t		overcurrentLim;	/*!< overcurrent limit */
    /* calibration values */
    int8_t			Vphase;			/*!< Channel voltage vs current phase correction (-123 us .. +124 us) */
    uint16_t		IRMScal;		/*!< Calibration for I RMS */
} ADCUI_CH_InitTypeDef;

/** @} */ /* End of group ADCUI_Exported_Types */

/** @defgroup ADCUI_Exported_Functions
  * @{
  */

/**
  * @brief  init ADCUI with initialization structure
  * @param  initStruct - @ref ADCUI_InitTypeDef - initialization structure
  */
void ADCUI_Init(ADCUI_InitTypeDef* initStruct);

/**
  * @brief  fill initialization structure with default values
  * @param  initStruct - @ref ADCUI_InitTypeDef - pointer to structure to be filled
  */
void ADCUI_StructInitDefault(ADCUI_InitTypeDef* initStruct);

/**
  * @brief  de-initialize ADCUI module, setup default values and deactivate peripheral clock
  */
void ADCUI_DeInit(void);

/**
  * @brief  setup voltage drop control - voltage drop will be indicated if voltage is below threshold
  *         during specified number of half-periods
  * @param  interval - number of the hafl-periods
  * @param  dropThreshold - voltage threshold
  */
void ADCUI_SetupVoltageDropControl(uint8_t interval, uint16_t dropThreshold);

/**
  * @brief  setup time interval without zero-crossing condition that will cause "no-voltage" case
  * @param  noVoltageInterval - time interval
  */
void ADCUI_NoVoltageDetectionTimeout(uint16_t noVoltageInterval);

/**
  * @brief  init ADCUI for specified channel with initialization structure
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  * @param  initStruct - @ref ADCUI_CH_InitTypeDef - channel initialization structure
  */
void ADCUI_InitChannel(adcuiChannel chnl, ADCUI_CH_InitTypeDef* initStruct);

/**
  * @brief  fill initialization structure with default values
  * @param  initStruct - @ref ADCUI_CH_InitTypeDef - pointer to structure to be filled
  */
void ADCUI_ChannelStructInitDefault(ADCUI_CH_InitTypeDef* initStruct);

/**
  * @brief  channel calbiration
  * @param  chnl - @ref adcuiCurrentChannel - channel selection (0,1,2,3)
  * @param  IGainCal - gain calibration for current
  * @param  VGainCal - gain calibration for voltage (has sense only for channels 0,1,2)
  */
void ADCUI_ChannelCalibration(adcuiCurrentChannel chnl, int16_t IGainCal, int16_t VGainCal);

/**
  * @brief  get phase shift between CH1 / CH2 and CH0
  * @param  chnl - @ref adcChannel - channel selection, NOTE: only 1 or 2 channel
  * @return phaseShift - phase shift
  */
uint16_t ADCUI_GetPhaseShift(adcuiChannel chnl);

/**
  * @brief  get next voltage value from the ADCUI fifo buffer
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  */
uint32_t ADCUI_GetNextVoltageFifoValue(adcuiChannel chnl);

/**
  * @brief  get next current value from the ADCUI fifo buffer
  * @param  chnl - @ref adcuiCurrentChannel - channel selection (0,1,2,3)
  */
uint32_t ADCUI_GetNextCurrentFifoValue(adcuiCurrentChannel chnl);

/**
  * @brief  get peak voltage for specified channel
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  */
uint32_t ADCUI_GetPeakVoltage(adcuiChannel chnl);

/**
  * @brief  get peak current for specified channel
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  */
uint32_t ADCUI_GetPeakCurrent(adcuiChannel chnl);

/**
  * @brief  get RMS voltage for specified channel
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  */
uint32_t ADCUI_GetRMSVoltage(adcuiChannel chnl);

/**
  * @brief  get RMS current for specified channel
  * @param  chnl - @ref adcuiCurrentChannel - channel selection (0,1,2,3)
  */
uint32_t ADCUI_GetRMSCurrent(adcuiCurrentChannel chnl);

/**
  * @brief  get voltage square for specified channel
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  */
uint32_t ADCUI_GetRMS2Voltage(adcuiChannel chnl);

/**
  * @brief  get current square for specified channel
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  */
uint32_t ADCUI_GetRMS2Current(adcuiChannel chnl);

/**
  * @brief  calibrate channel offsets and gains for energy accumulators
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  * @param  energy - @ref adcEnergyCalibration - energy selection (active/reactive/full)
  * @param  gainCal - gain calibration
  * @param  offsetCal - offset calibration
  */
void ADCUI_Calibrate(adcuiChannel chnl, adcuiEnergyCalibration energy, int16_t gainCal, int16_t offsetCal);

/**
  * @brief  get energy accumulator value
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  * @param  energy - @ref adcEnergyType - energy selection (activeP(N)/reactiveP(N)/full)
  */
uint64_t ADCUI_GetEnergyAccumulator(adcuiChannel chnl, adcuiEnergyType energy);

/**
  * @brief  get only most-significant 32-bits of the 57-bits energy accumulator for coarse measurement
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  * @param  energy - @ref adcEnergyType - energy selection (activeP(N)/reactiveP(N)/full)
  */
uint32_t ADCUI_GetEnergyAccumulatorHigh32(adcuiChannel chnl, adcuiEnergyType energy);

/**
  * @brief  reset specified energy accumulator to zero
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  * @param  energy - @ref adcEnergyCalibration - energy selection (active/reactive/full)
  */
void ADCUI_ResetEnergyAccumulator(adcuiChannel chnl, uint32_t energy);

/**
  * @brief  get channel status
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  * @return @ref adcuiFlag - flags
  */
uint32_t ADCUI_GetStatus(adcuiChannel chnl);

/**
  * @brief  get signle channel flag status
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  * @param  flag - @ref adcuiFlag - flag to be checked
  * @retval @ref FlagStatus - flag SET or RESET
  */
FlagStatus ADCUI_GetFlag(adcuiChannel chnl, adcuiFlag flag);

/**
  * @brief  clear channel flags
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  * @param  flags - @ref adcuiFlag - flags combination to be reset
  */
void ADCUI_ClearFlag(uint32_t chnl, uint32_t flags);

/**
  * @brief  set channel condition mask
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  * @param  flags - @ref adcuiFlag - flags combination to be masked
  */
void ADCUI_SetMask(uint32_t chnl, uint32_t flags);

/**
  * @brief  set single channel condition mask bit
  * @param  chnl - @ref adcChannel - channel selection (0,1,2)
  * @param  flag - @ref adcuiFlag - flag to be masked
  */
void ADCUI_SetSingleMask(uint32_t chnl, adcuiFlag flag);

/** @} */ /* End of group ADCUI_Exported_Functions */

/** @} */ /* End of group ADCUI */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_ADCUI_H */

/**
 * END OF FILE MLDR187_adcui.h
 */

