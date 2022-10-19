/**
  ******************************************************************************
  * @file    MDR32FxQI_config.h
  * @author  Milandr Application Team
  * @version V2.0.2i
  * @date    10/03/2022
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
  * @mainpage MDR32FxQI Standard Peripherals Library.
  * MDR32FxQI Standard Peripherals Library is a package consisting of
  * all standard peripheral device drivers for MDR32F1QI, MDR32F9Q2I,
  * MDR32FG16S1QI microcontrollers.
  * This library is a firmware package which contains a collection of routines,
  * data structures and macros covering the features of Milandr MDR32FxQI
  * peripherals. It includes a description of the device drivers plus a set of
  * examples for each peripheral. The firmware library allows any device to be
  * used in the user application without the need for in-depth study of each
  * peripherals specifications. Using the Standard Peripherals Library has two
  * advantages: it saves significant time that would otherwise be spent in
  * coding, while simultaneously reducing application development and
  * integration costs.
  *
  * The MDR32FxQI Standard Peripherals Library is full CMSIS compliant.
  */

/* <<< Use Configuration Wizard in Context Menu >>> */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR32FxQI_CONFIG_H
#define __MDR32FxQI_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <RTE_Components.h> /* Keil uVision specific inclusion */

/* Uncomment the line corresponding to the target microcontroller */
/* When using Keil uVision, the definition is set automatically
   (when RTE_Components.h included) according to the selected
   microcontroller in "Options for Target->Device" window.
   For MDR32F1QI revision is selected in 
   "Device->Startup" variant in "Manage Run-Time Environment" window */
#define USE_MDR32F9Q2I
/* #define USE_MDR32F1QI_REV3_4
#define USE_MDR32F1QI_REV6
#define USE_MDR32FG16S1QI*/

/* Select the header file for target microcontroller */
#if defined (USE_MDR32F9Q2I)
    #include "MDR32F9Q2I.h"
#elif defined (USE_MDR32F1QI_REV3_4) || defined (USE_MDR32F1QI_REV6)
    #define USE_MDR32F1QI
    #include "MDR32F1QI.h"
#elif defined (USE_MDR32FG16S1QI)
    #include "MDR32FG16S1QI.h"
#else
    #error "Microcontroller not selected in MDR32FxQI_config.h file"
#endif


#if (defined(USE_MDR32F9Q2I) || defined (USE_MDR32FG16S1QI))

     /*#define USE_JTAG_A*/
	 
    #define USE_JTAG_B
#endif

#define HSI_Value       ((uint32_t)8000000)

#define HSE_Value       ((uint32_t)8000000)

#define HSE2_Value      ((uint32_t)25000000)

#define LSI_Value       ((uint32_t)40000)

#define LSE_Value       ((uint32_t)32768)

#define HSEonTimeOut    ((uint16_t)0x0600)

#define HSE2onTimeOut   ((uint16_t)0x8000)

#define LSEonTimeOut    ((uint16_t)0x0600)

#define HSIonTimeOut    ((uint16_t)0x0600)

#define LSIonTimeOut    ((uint16_t)0x0600)

#define PLLCPUonTimeOut ((uint16_t)0x0600)

#define PLLUSBonTimeOut ((uint16_t)0x0600)

#define PLLDSPonTimeOut ((uint16_t)0x0600)

#define FLASH_PROG_FREQ_MHZ     (8.0)

#define DMA_Channels_Number   32

#define DMA_AlternateData     1

#if defined (_USE_DEBUG_UART_)

#if defined (USE_MDR32F1QI)
    #define DEBUG_UART                  MDR_UART1
    #define DEBUG_UART_PORT             MDR_PORTC
    #define DEBUG_UART_PINS             (PORT_Pin_3 | PORT_Pin_4)
    #define DEBUG_UART_PINS_FUNCTION    PORT_FUNC_MAIN
    #define DEBUG_BAUD_RATE             115200
#elif defined (USE_MDR32F9Q2I)
    #define DEBUG_UART                  MDR_UART2
    #define DEBUG_UART_PORT             MDR_PORTF
    #define DEBUG_UART_PINS             (PORT_Pin_0 | PORT_Pin_1)
    #define DEBUG_UART_PINS_FUNCTION    PORT_FUNC_OVERRID
    #define DEBUG_BAUD_RATE             115200
#elif defined (USE_MDR32FG16S1QI)
    #define DEBUG_UART                  MDR_UART3
    #define DEBUG_UART_PORT             MDR_PORTF
    #define DEBUG_UART_PINS             (PORT_Pin_0 | PORT_Pin_1)
    #define DEBUG_UART_PINS_FUNCTION    PORT_FUNC_ALTER
    #define DEBUG_BAUD_RATE             115200
#endif

#endif /* #if defined (_USE_DEBUG_UART_) */


#if defined (USE_MDR32F1QI)

    #define MIL_STD_1553_TERMINAL_ADDRESS    0x01
#endif /* #if defined (USE_MDR32F1QI) */

#define RTC_CalibratorValue     0

#define RTC_PRESCALER_VALUE     32768

/* ---------------------- USB configuration parameters -----------------------*/
/* Supported USB Device Classes */
#define USB_DEVICE_CLASS_CDC 2

/* Uncomment one of the lines below to select the Device Class. Leave all commented
 * if the desired device class is not currently supported by USB library */
#define USB_DEVICE_CLASS  USB_DEVICE_CLASS_CDC

#define USB_INT_HANDLE_REQUIRED

#define USB_CDC_LINE_CODING_SUPPORTED

#define WORKAROUND_MDR32F9QX_ERROR_0002

#if defined (__ICCARM__)
    #define __attribute__(name_section)
    #if defined (USE_MDR32F1QI)
        #pragma section = "EXECUTABLE_MEMORY_SECTION"
        #define IAR_SECTION(section) @ section
    #elif defined (USE_MDR32F9Q2I)
        #define IAR_SECTION(section)
    #endif
#endif
#if defined (__CMCARM__)
    #define __attribute__(name_section)
    #define IAR_SECTION(section)
#endif
#if defined (__ARMCC_VERSION)
    #define IAR_SECTION(section)
#endif

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


#ifdef __cplusplus
}
#endif

#endif /* __MDR32FxQI_CONFIG_H */

/*********************** (C) COPYRIGHT 2022 Milandr ****************************
*
* END OF FILE MDR32FxQI_config.h */

