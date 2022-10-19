/**
  ******************************************************************************
  * @file    MDR1986VK01_config.h
  * @author  Milandr Application Team
  * @version V1.3.0
  * @date    14/04/2022
  * @brief   Library configuration file.
  ******************************************************************************
  * <br><br>
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  */

/**
  * @mainpage MDR1986VK01 Standard Peripherals Library.
  * MDR1986VK01 Standard Peripherals Library is a package consisting of
  * all standard peripheral device drivers for 1986VK01 microcontrollers.
  * This library is a firmware package which contains a collection of routines,
  * data structures and macros covering the features of Milandr MDR1986VK01
  * peripherals. It includes a description of the device drivers plus a set of
  * examples for each peripheral. The firmware library allows any device to be
  * used in the user application without the need for in-depth study of each
  * peripherals specifications. Using the Standard Peripherals Library has two
  * advantages: it saves significant time that would otherwise be spent in
  * coding, while simultaneously reducing application development and
  * integration costs.
  *
  * The MDR1986VK01 Standard Peripherals Library is compatible with Milandr
  * demo board for MCU 1986VK01.
  *
  * The MDR1986VK01 Standard Peripherals Library is full CMSIS compliant.
  */

// <<< Use Configuration Wizard in Context Menu >>>

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR1986VK01_CONFIG_H
#define __MDR1986VK01_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

// <c2> Use legacy support
// <i> Definition provides legacy support for previous versions of SPL for MCU.
// <i> Should be defined for 1.x.x version. Will be completely removed in 2.0 with backward compatibility break.
#define MDR_LEGACY_SUPPORT
// </c>


#include "MDR1986VK01.h"


/* USB parameters */
#define USB_CDC_STATE_REPORTING_SUPPORTED
#define USB_CDC_LINE_CODING_SUPPORTED
#define USB_CDC_CONTROL_LINE_STATE_SUPPORTED


// <h> Target system parameters
// <h> CLK generators frequencies
// <o> HSI clock value [Hz]
// <i> Default: 8000000 (8MHz)
#define HSI_Value       ((uint32_t)8000000)
// <o> HSE0 clock value [Hz]
// <i> Default: 8000000 (8MHz)
#define HSE0_Value      ((uint32_t)8000000)
// <o> HSE1 clock value [Hz]
// <i> Default: 25000000 (25MHz)
#define HSE1_Value      ((uint32_t)25000000)
// <o> LSI clock value [Hz]
// <i> Default: 40000 (40kHz)
#define LSI_Value       ((uint32_t)40000)
// <o> LSE clock value [Hz]
// <i> Default: 32768 (32.768kHz)
#define LSE_Value       ((uint32_t)32768)
// </h>

// <h> CLK frequencies startup timeouts settings
// <o> HSE0 timeout startup value
// <i> Default: 0x0600
#define HSE0onTimeOut   ((uint16_t)0x0600)
// <o> HSE1 timeout startup value
// <i> Default: 0x8000
#define HSE1onTimeOut   ((uint16_t)0x8000)
// <o> LSE timeout startup value
// <i> Default: 0x0600
#define LSEonTimeOut    ((uint16_t)0x0600)
// <o> HSI timeout startup value
// <i> Default: 0x0600
#define HSIonTimeOut    ((uint16_t)0x0600)
// <o> LSI timeout startup value
// <i> Default: 0x0600
#define LSIonTimeOut    ((uint16_t)0x0600)
// <o> PLL timeout startup value
// <i> Default: 0x0600
#define PLLonTimeOut    ((uint16_t)0x0600)
// </h>

// <o> FLASH controller freq [MHz]
 //<i> Default: 8MHz
#define FLASH_PROG_FREQ_MHZ     (8.0)
// </h>


// <h> RTC configuration parameters
// <o> RTC calibration value
// <i> Default: 0
#define RTC_CalibratorValue     0
// <o> RTC prescaler value
// <i> Default: 32768
#define RTC_PRESCALER_VALUE     32768
// </h>


// <h> Controller blocks settings
// <h> DMA configuration parameters
// <o.0..5> Number of DMA channels to use
// <i> This parameter is in range 1..32
// <i> Default: 32
#define DMA_Channels_Number   32

// <o> Alternate Control Data Structure Usage
//   <0=> 0: DMA_ALternateDataDisabled
//   <1=> 1: DMA_ALternateDataEnabled
// <i> Default: 1 (DMA_ALternateDataEnabled)
#define DMA_AlternateData     1
// </h>

// </h>


// <h> Parameter run-time check support

// <o> Paramater checking level
//   <0=> 0: no parameter checks ("assert_param" macro is disabled)
//   <1=> 1: check enabled, source file ID and line number are available
//   <2=> 2: check enabled, source file ID, line number and checking expression (as string) are available (increased code size)
// <i> Default: 0 ("assert_param" macro is disabled)
#define USE_ASSERT_INFO    0

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed user's function which 
  *         reports the name of the source file, source line number
  *         and expression text (if USE_ASSERT_INFO == 2) of the call that failed.
  *         That function should not return. If expr is true, nothing is done.
  * @retval None
  */
#if (USE_ASSERT_INFO == 0)
    #define assert_param(expr) ((void)0U)
#elif (USE_ASSERT_INFO == 1)
    #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
    void assert_failed(uint8_t* file, uint32_t line);
#elif (USE_ASSERT_INFO == 2)
    #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__, (const uint8_t*) #expr))
    void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr);
#else
    #error "Unsupported USE_ASSERT_INFO level"
#endif /* USE_ASSERT_INFO */

// </h>


// #if defined (__ICCARM__)
	// #define __attribute__(name_section)
// #endif
// #if defined (__CMCARM__)
	// #define __attribute__(name_section)
	// #define IAR_SECTION(section)
// #endif
// #if defined ( __CC_ARM )  /* MDK ARM Compiler 5 */
  // #define 	__ramfunc
// #endif

/* Define RAMFUNC attribute */
/* "ram_section" should be defined in scatter to use it
(see https://www.keil.com/support/man/docs/armlink/armlink_pge1407248176212.htm) */
#if defined   ( __CC_ARM ) /* Keil µVision */
  #define RAMFUNC __attribute__ ((section("ram_section")))
#elif defined (  __GNUC__ ) /* GCC CS3 2009q3-68 */
  #define RAMFUNC __attribute__ ((section("ram_section")))
#elif defined ( __ICCARM__ ) /* IAR EW ARM 5.41+ */
  #define RAMFUNC __attribute__(ram_section)
#elif defined (__CMCARM__)
  #define __attribute__(ram_section)
  #define IAR_SECTION(ram_section)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MDR1986VK01_CONFIG_H */

/*********************** (C) COPYRIGHT 2022 Milandr ****************************
*
* END OF FILE MDR1986VK01_config.h */

