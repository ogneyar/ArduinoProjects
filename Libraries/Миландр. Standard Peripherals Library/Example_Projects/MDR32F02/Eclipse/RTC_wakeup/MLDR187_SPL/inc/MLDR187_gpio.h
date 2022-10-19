/**
  * FILE MLDR187_gpio.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_PORT_H
#define __MLDR187_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#include "MLDR187.h"
#include "MLDR187_lib.h"

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup PORT
  * @{
  */

/** @defgroup PORT_Exported_Types PORT Exported Types
  * @{
  */

/* Configuration OE enumeration */
typedef enum
{
	PORT_OE_IN			= GPIO_PORTx_OE_INPUT,
	PORT_OE_OUT			= GPIO_PORTx_OE_OUTPUT
} PORT_OE_TypeDef;

/* Configuration port function enumeration */
typedef enum
{
	PORT_FUNC_PORT		= GPIO_PORTx_FUNC_PORT,
	PORT_FUNC_MAIN		= GPIO_PORTx_FUNC_MAIN,
	PORT_FUNC_ALTER		= GPIO_PORTx_FUNC_ALT,
	PORT_FUNC_OVERRID	= GPIO_PORTx_FUNC_REMAP
} PORT_FUNC_TypeDef;

/* Configuration analog/digital mode enumeration */
typedef enum
{
	PORT_MODE_ANALOG	= GPIO_PORTx_ANALOG_ANALOG,
	PORT_MODE_DIGITAL	= GPIO_PORTx_ANALOG_DIGITAL
} PORT_A_D_MODE_TypeDef;

/* Configuration PULL_DOWN enumeration */
typedef enum
{
	PORT_PULL_DOWN_OFF	= GPIO_PORTx_PULL_NO,
	PORT_PULL_DOWN_ON	= GPIO_PORTx_PULL_DOWN
} PORT_PULL_DOWN_TypeDef;

/* Configuration Speed / power enumeration */
typedef enum
{
	PORT_SPEED_FAST_2mA = GPIO_PORTx_PWR_2mA,
	PORT_SPEED_SLOW_4mA	= GPIO_PORTx_PWR_4mA
} PORT_SPEED_TypeDef;

/**
  * @brief  PORT Init structure definition
  */
typedef struct
{
	PORT_OE_TypeDef PORT_OE;               /*!< Specifies in/out mode for the selected pins.
                                                This parameter is one of @ref PORT_OE_TypeDef values. */
	PORT_FUNC_TypeDef PORT_FUNC;           /*!< Specifies operating function for the selected pins.
                                                This parameter is one of @ref PORT_FUNC_TypeDef values. */
	PORT_A_D_MODE_TypeDef PORT_MODE;       /*!< Analog / digital mode for the selected pins.
                                                This parameter is one of @ref PORT_MODE_TypeDef values. */
	PORT_PULL_DOWN_TypeDef PORT_PULL_DOWN; /*!< Specifies pull down state for the selected pins.
                                                This parameter is one of @ref PORT_PULL_DOWN_TypeDef values. */
	PORT_SPEED_TypeDef PORT_SPEED;         /*!< Specifies the speed for the selected pins.
                                              	This parameter is one of @ref PORT_SPEED_TypeDef values. */
} PORT_InitTypeDef;

/* GPIO ports base addresses */
typedef enum
{
	gpioA				= MDR_GPIO1_BASE,
	gpioB				= MDR_GPIO2_BASE,
	gpioC				= MDR_GPIO3_BASE,
	gpioD				= MDR_GPIO4_BASE
} gpioPorts;

/* GPIO pin enumeration */
typedef enum
{
	pin0				= PORT_Pin_0,
	pin1				= PORT_Pin_1,
	pin2				= PORT_Pin_2,
	pin3				= PORT_Pin_3,
	pin4				= PORT_Pin_4,
	pin5				= PORT_Pin_5,
	pin6 				= PORT_Pin_6,
	pin7				= PORT_Pin_7,
	pin8				= PORT_Pin_8,
	pin9				= PORT_Pin_9,
	pin10				= PORT_Pin_10,
	pin11				= PORT_Pin_11,
	pin12				= PORT_Pin_12,
	pin13				= PORT_Pin_13,
	pin14				= PORT_Pin_14,
	pin15				= PORT_Pin_15
} gpioPins;

/** @} */ /* End of group PORT_Exported_Types */

/** @defgroup PORT_Exported_Functions PORT Exported Functions
  * @{
  */

/**
 * 	@brief	initialize GPIO port pins, enable peripheral clock source
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	pins - bit mask of @ref gpioPins
 * 	@param	initStruct - initalization structure
 */
void PORT_Init(MDR_GPIO_TypeDef* GPIOx, uint16_t pins, PORT_InitTypeDef* initStruct);

/**
  * @brief  fill initialization structure with default values
  * @param  initStruct - @ref PORT_InitTypeDef - pointer to structure to be filled
  */
void PORT_StructInitDefault(PORT_InitTypeDef* initStruct);

/**
 * 	@brief	deinitialize GPIO port pins
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	pins - bit mask of @ref gpioPins
 */
void PORT_DeInit(MDR_GPIO_TypeDef* GPIOx, uint16_t pins);

/**
 * 	@brief	write all output pins
 * 			NOTE: only pins configured as outputs will be set
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	newOutput - new output state, every bit dedicated to single pin
 */
void PORT_Write(MDR_GPIO_TypeDef* GPIOx, uint16_t newOutput);

/**
 * 	@brief	read all input pins
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@return	input state, every bit dedicated to single pin
 */
uint16_t PORT_Read(MDR_GPIO_TypeDef* GPIOx);

/**
 * 	@brief	read state of the input pin
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	pin - @ref gpioPins - single specified GPIO pin
 * 	@retval	@BitStatus - input pin state
 */
BitStatus PORT_ReadPin(MDR_GPIO_TypeDef* GPIOx, uint16_t pin);

/**
 * 	@brief	set new output state for specified pins, all other pins doesn't change it's state
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	pins - bit mask of @ref gpioPins
 * 	@param	newState - @ref BitStatus - new pin state
 */
void PORT_SetReset(MDR_GPIO_TypeDef* GPIOx, uint16_t pins, BitStatus newState);

/**
 * 	@brief	read back state of the all output pins
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@return	state of the GPIOx output data
 */
uint16_t PORT_ReadBackPort(MDR_GPIO_TypeDef* GPIOx);

/**
 * 	@brief	read back state of the single output pin
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	pin - @ref gpioPins - single specified GPIO pin
 * 	@retval	@BitStatus - pin output state
 */
BitStatus PORT_ReadBackPin(MDR_GPIO_TypeDef* GPIOx, uint16_t pin);

/** @} */ /* End of group PORT_Exported_Functions */

/** @} */ /* End of group PORT */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_PORT_H */

/**
 * END OF FILE MLDR187_port.h
 */

