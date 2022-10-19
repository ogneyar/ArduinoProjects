/**
  * FILE MLDR187_gpio.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_gpio.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_GPIO_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO
  * @{
  */

/** @defgroup GPIO_Private_Defines
  * @{
  */

/** @} */ /* End of group GPIO_Private_Defines */

/** @defgroup GPIO_Private_Macros
  * @{
  */

/* assert GPIO port */
#define IS_GPIO_PORT(PORT)			(((uint32_t)(PORT) == MDR_GPIO1_BASE) || \
									 ((uint32_t)(PORT) == MDR_GPIO2_BASE) || \
									 ((uint32_t)(PORT) == MDR_GPIO3_BASE) || \
									 ((uint32_t)(PORT) == MDR_GPIO4_BASE))

/* assert GPIO any pin */
#define IS_GPIO_ANY_PIN(PORT, PIN) (((PORT) == MDR_PORTA) || \
									(((PORT) == MDR_PORTB) && (((PIN) & 0x8000) == 0)) || \
									(((PORT) == MDR_PORTC) && (((PIN) & 0xFF00) == 0)) || \
									((PORT) == MDR_PORTD))

/* assert GPIO single pin */
#define IS_GPIO_SINGLE_PIN(PIN)     (((PIN) == PORT_Pin_0 ) || \
                                     ((PIN) == PORT_Pin_1 ) || \
                                     ((PIN) == PORT_Pin_2 ) || \
                                     ((PIN) == PORT_Pin_3 ) || \
                                     ((PIN) == PORT_Pin_4 ) || \
                                     ((PIN) == PORT_Pin_5 ) || \
                                     ((PIN) == PORT_Pin_6 ) || \
                                     ((PIN) == PORT_Pin_7 ) || \
                                     ((PIN) == PORT_Pin_8 ) || \
                                     ((PIN) == PORT_Pin_9 ) || \
                                     ((PIN) == PORT_Pin_10) || \
                                     ((PIN) == PORT_Pin_11) || \
                                     ((PIN) == PORT_Pin_12) || \
                                     ((PIN) == PORT_Pin_13) || \
                                     ((PIN) == PORT_Pin_14) || \
                                     ((PIN) == PORT_Pin_15))

/* assert GPIO OE options */
#define IS_PORT_OE(OE)				(((OE) == GPIO_PORTx_OE_INPUT) || \
									 ((OE) == GPIO_PORTx_OE_OUTPUT))

/* assert GPIO ANALOG or DIGITAL mode */
#define IS_PORT_MODE(MODE)			(((MODE) == GPIO_PORTx_ANALOG_ANALOG) || \
									 ((MODE) == GPIO_PORTx_ANALOG_DIGITAL))

/* assert GPIO PULL DOWN */
#define IS_PORT_PD(PULL_DOWN)		(((PULL_DOWN) == GPIO_PORTx_PULL_NO) || \
                                     ((PULL_DOWN) == GPIO_PORTx_PULL_DOWN))

/* assert GPIO SPEED */
#define IS_PORT_SPEED(SPEED)		(((SPEED) == GPIO_PORTx_PWR_4mA) || \
									 ((SPEED) == GPIO_PORTx_PWR_2mA))

/* assert GPIO PORT function */
#define IS_PORT_FUNC(FUNC)			(((FUNC) == GPIO_PORTx_FUNC_PORT) || \
									 ((FUNC) == GPIO_PORTx_FUNC_MAIN) || \
									 ((FUNC) == GPIO_PORTx_FUNC_ALT) || \
									 ((FUNC) == GPIO_PORTx_FUNC_REMAP))

/** @} */ /* End of group GPIO_Private_Macros */

/** @defgroup GPIO_Private_Functions_Declarations
  * @{
  */

/** @} */ /* End of group GPIO_Private_Functions_Declarations */

/** @defgroup GPIO_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize GPIO port pins, enable peripheral clock source
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	pins - bit mask of @ref gpioPins
 * 	@param	initStruct - initalization structure
 */
void PORT_Init(MDR_GPIO_TypeDef* GPIOx, uint16_t pins, PORT_InitTypeDef* initStruct)
{
	RST_CLK_Peripherals rccPort;
	uint16_t testPin;
	uint32_t twoBitMask;
	int i;

	/* test input parameters */
	assert_param(IS_GPIO_PORT(GPIOx));
	assert_param(IS_GPIO_ANY_PIN(GPIOx, pins));
	assert_param(IS_PORT_OE(initStruct->PORT_OE));
	assert_param(IS_PORT_MODE(initStruct->PORT_MODE));
	assert_param(IS_PORT_PD(initStruct->PORT_PULL_DOWN));
	assert_param(IS_PORT_SPEED(initStruct->PORT_SPEED));
	assert_param(IS_PORT_FUNC(initStruct->PORT_FUNC));

	/* activate peripheral clock */
	if (GPIOx == MDR_PORTA) {
		rccPort = RST_CLK_PORTA;
	} else if (GPIOx == MDR_PORTB) {
		rccPort = RST_CLK_PORTB;
	} else if (GPIOx == MDR_PORTC) {
		rccPort = RST_CLK_PORTC;
	} else {
		rccPort = RST_CLK_PORTD;
	}
	RST_CLK_EnablePeripheralClock(rccPort, RST_CLK_Div1);

	/* for all pins do */
	testPin = 1;
	twoBitMask = 0x3U;
	for (i = 0; i < 16; i++) {
		if ((pins & testPin) != 0) {
			/* write output enable state */
			GPIOx->OE &= ~testPin;
			GPIOx->OE |= (initStruct->PORT_OE << i);
			/* write analog / digital function */
			GPIOx->ANALOG &= ~testPin;
			GPIOx->ANALOG |= (initStruct->PORT_MODE << i);
			/* write pull down */
			GPIOx->PULL &= ~testPin;
			GPIOx->PULL |= (initStruct->PORT_PULL_DOWN << i);
			/* write power/speed */
			GPIOx->PWR &= ~twoBitMask;
			GPIOx->PWR |= (initStruct->PORT_SPEED << (i * 2));
			/* setup function */
			GPIOx->FUNC &= ~twoBitMask;
			GPIOx->FUNC |= (initStruct->PORT_FUNC << (i * 2));
		}
		testPin <<= 1;
		twoBitMask <<= 2;
	}
}

/**
  * @brief  fill initialization structure with default values
  * @param  initStruct - @ref PORT_InitTypeDef - pointer to structure to be filled
  */
void PORT_StructInitDefault(PORT_InitTypeDef* initStruct)
{
    initStruct->PORT_OE = GPIO_PORTx_OE_INPUT;
    initStruct->PORT_FUNC = GPIO_PORTx_FUNC_PORT;
    initStruct->PORT_MODE = GPIO_PORTx_ANALOG_ANALOG;
    initStruct->PORT_PULL_DOWN = GPIO_PORTx_PULL_NO;
    initStruct->PORT_SPEED = GPIO_PORTx_PWR_2mA;
}

/**
 * 	@brief	deinitialize GPIO port pins
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	pins - bit mask of @ref gpioPins
 */
void PORT_DeInit(MDR_GPIO_TypeDef* GPIOx, uint16_t pins)
{
	PORT_InitTypeDef initStruct;

	/* test input parameters */
	assert_param(IS_GPIO_PORT(GPIOx));
	assert_param(IS_GPIO_ANY_PIN(GPIOx, pins));

	/* fill default init structure: input, port, analog, no pull down, fast */
	initStruct.PORT_OE = PORT_OE_IN;
	initStruct.PORT_FUNC = PORT_FUNC_PORT;
	initStruct.PORT_MODE = PORT_MODE_ANALOG;
	initStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	initStruct.PORT_SPEED = PORT_SPEED_FAST_2mA;

	/* initialize GPIO */
	PORT_Init(GPIOx, pins, &initStruct);
}

/**
 * 	@brief	write all output pins
 * 			NOTE: only pins configured as outputs will be set
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	newOutput - new output state, every bit dedicated to single pin
 */
void PORT_Write(MDR_GPIO_TypeDef* GPIOx, uint16_t newOutput)
{
	uint32_t regValue, regOutputMask;

	/* test input parameters */
	assert_param(IS_GPIO_PORT(GPIOx));

	/* read current port state */
	regValue = GPIOx->RXTX;
	regOutputMask = GPIOx->OE;

	/* clear output pins and place it with newOutput values */
	regValue &= ~regOutputMask;
	regValue |= (newOutput & regOutputMask);

	/* write back new value */
	GPIOx->RXTX = regValue;
}

/**
 * 	@brief	read all input pins
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@return	input state, every bit dedicated to single pin
 */
uint16_t PORT_Read(MDR_GPIO_TypeDef* GPIOx)
{
	/* test input parameters */
	assert_param(IS_GPIO_PORT(GPIOx));

	/* return state */
	return (uint16_t)GPIOx->RXTX;
}

/**
 * 	@brief	read state of the input pin
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	pin - @ref gpioPins - single specified GPIO pin
 * 	@retval	@BitStatus - input pin state
 */
BitStatus PORT_ReadPin(MDR_GPIO_TypeDef* GPIOx, uint16_t pin)
{
	BitStatus result;

	/* test input parameters */
	assert_param(IS_GPIO_PORT(GPIOx));
	assert_param(IS_GPIO_ANY_PIN(GPIOx, pin));
	assert_param(IS_GPIO_SINGLE_PIN(pin));

	/* read pin state */
	result = RESET;
	if (((GPIOx->RXTX) & pin) != 0)  {
		result = SET;
	}

	return result;
}

/**
 * 	@brief	set new output state for specified pins, all other pins doesn't change it's state
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	pins - bit mask of @ref gpioPins
 * 	@param	newState - @ref BitStatus - new pin state
 */
void PORT_SetReset(MDR_GPIO_TypeDef* GPIOx, uint16_t pins, BitStatus newState)
{
	/* test input parameters */
	assert_param(IS_GPIO_PORT(GPIOx));
	assert_param(IS_GPIO_ANY_PIN(GPIOx, pins));
	assert_param(IS_FLAG_STATUS(newState));

	/* update ouput pin state */
	if (newState != RESET) {
		GPIOx->SETTX = pins;
	} else {
		GPIOx->CLRTX = pins;
	}
}

/**
 * 	@brief	read back state of the all output pins
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@return	state of the GPIOx output data
 */
uint16_t PORT_ReadBackPort(MDR_GPIO_TypeDef* GPIOx)
{
	/* test input parameters */
	assert_param(IS_GPIO_PORT(GPIOx));

	/* return state */
	return (uint16_t)GPIOx->RDTX;
}

/**
 * 	@brief	read back state of the single output pin
 * 	@param	GPIOx - base address of the PORT, item of @ref gpioPorts
 * 	@param	pin - @ref gpioPins - single specified GPIO pin
 * 	@retval	@BitStatus - pin output state
 */
BitStatus PORT_ReadBackPin(MDR_GPIO_TypeDef* GPIOx, uint16_t pin)
{
	BitStatus result;

	/* test input parameters */
	assert_param(IS_GPIO_PORT(GPIOx));
	assert_param(IS_GPIO_ANY_PIN(GPIOx, pin));
	assert_param(IS_GPIO_SINGLE_PIN(pin));

	/* read state */
	result = RESET;
	if (((GPIOx->RDTX) & pin) != 0) {
		result = SET;
	}

	return result;
}

/** @} */ /* End of group GPIO_Exported_Functions */

/** @} */ /* End of group GPIO */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_gpio.c
  */

